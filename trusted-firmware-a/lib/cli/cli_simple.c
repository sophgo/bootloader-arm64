// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Add to readline cmdline-editing by
 * (C) Copyright 2005
 * JinHua Luo, GuangDong Linux Center, <luo.jinhua@gd-linux.com>
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <drivers/delay_timer.h>
#include <lib/mmio.h>
#include <cli.h>
#include <ymodem.h>

#define DEBUG_PARSER	0	/* set to 1 to debug */

#define debug_parser(fmt, args...)	do {	\
		if (DEBUG_PARSER)		\
			printf(fmt, ##args);	\
	} while (0)

/*
 * TFA does not have a tstc function, so emulate here:
 * return -1 if not get any character, otherwise just
 * return the character.
 */
int console_try_getc(void)
{
	console_t *console;

	for (console = console_list; console != NULL; console = console->next)
		if ((console->flags & console_state) && (console->getc != NULL))
			return console->getc(console);

	return 0;
}

unsigned long simple_strtoul(const char *cp, char **endp,
			     unsigned int base)
{
	unsigned long result = 0;
	unsigned long value;

	if (*cp == '0') {
		cp++;
		if ((*cp == 'x') && isxdigit(cp[1])) {
			base = 16;
			cp++;
		}

		if (!base)
			base = 8;
	}

	if (!base)
		base = 10;

	while (isxdigit(*cp) && (value = isdigit(*cp) ? *cp - '0' : (islower(*cp)
	    ? toupper(*cp) : *cp) - 'A' + 10) < base) {
		result = result * base + value;
		cp++;
	}

	if (endp)
		*endp = (char *)cp;

	return result;
}

#pragma weak plat_sys_reset
#pragma weak plat_spif_program
#pragma weak plat_cli_prepare
#pragma weak plat_cli_cmd_process

void __dead2 plat_sys_reset(int is_warm_reset)
{
	while (1)
		wfi();
}

void plat_spif_program(uint64_t addr, uint32_t offset, uint32_t size)
{
	;
}

void plat_cli_prepare(void)
{
	;
}

int plat_cli_cmd_process(int flag, int argc, char *const argv[])
{
	return -1;
}

/*
 * return non-zero will exit command line
 */
static int cmd_process(int flag, int argc, char *const argv[])
{
	int ret = 0;

	if (test_cmd("exit")) {
		ret = -1;
	} else if (test_cmd("ymodem")) {
		unsigned long addr;

		if (argc < 2)
			goto out;
		addr = simple_strtoul(argv[1], NULL, 16);
		load_serial_ymodem(addr);
	} else if (test_cmd("jump")) {
		unsigned long addr;
		typedef void (*entry_t)(void);
		entry_t entry;

		if (argc < 2)
			return -1;
		addr = simple_strtoul(argv[1], NULL, 16);
		NOTICE("jump to 0x%lx\n", addr);
		entry = (entry_t)addr;
		entry();
	} else if (test_cmd("mw")) {
		unsigned long addr;
		uint32_t value;

		if (argc < 3)
			goto out;
		addr = simple_strtoul(argv[1], NULL, 16);
		value = simple_strtoul(argv[2], NULL, 16);
		mmio_write_32(addr, value);
		flush_dcache_range(addr, 4);
		NOTICE("0x%lx: 0x%08x\n", addr, value);
	} else if (test_cmd("mr")) {
		unsigned long addr;

		if (argc < 2)
			goto out;
		addr = simple_strtoul(argv[1], NULL, 16);
		NOTICE("0x%lx: 0x%08x\n", addr, mmio_read_32(addr));
	} else if (test_cmd("reset")) {
		if (argc < 2)
			plat_sys_reset(1);
		else
			plat_sys_reset(0);
	} else if (test_cmd("spif")) {
		unsigned long addr, size, offset;

		if (argc < 4)
			goto out;

		addr = simple_strtoul(argv[1], NULL, 16);
		offset = simple_strtoul(argv[2], NULL, 16);
		size = simple_strtoul(argv[3], NULL, 16);
		plat_spif_program(addr, offset, size);
	} else {
		if (plat_cli_cmd_process(flag, argc, argv) < 0)
			ERROR("Cmd (%s) not supported\n", argv[0]);
	}
out:
	return ret;
}

static int cli_simple_parse_line(char *line, char *argv[])
{
	int nargs = 0;

	debug_parser("%s: \"%s\"\n", __func__, line);
	while (nargs < CONFIG_SYS_MAXARGS) {
		/* skip any white space */
		while (isblank(*line))
			++line;

		if (*line == '\0') {	/* end of line, no more args	*/
			argv[nargs] = NULL;
			debug_parser("%s: nargs=%d\n", __func__, nargs);
			return nargs;
		}

		argv[nargs++] = line;	/* begin of argument string	*/

		/* find end of string */
		while (*line && !isblank(*line))
			++line;

		if (*line == '\0') {	/* end of line, no more args	*/
			argv[nargs] = NULL;
			debug_parser("parse_line: nargs=%d\n", nargs);
			return nargs;
		}

		*line++ = '\0';		/* terminate current arg	 */
	}

	printf("** Too many args (max. %d) **\n", CONFIG_SYS_MAXARGS);

	debug_parser("%s: nargs=%d\n", __func__, nargs);
	return nargs;
}

static int cli_simple_run_command(char *cmd, int flag)
{
	char *token;			/* start of token in cmdbuf	*/
	char *sep;			/* end of token (separator) in cmdbuf */
	char *str = cmd;
	char *argv[CONFIG_SYS_MAXARGS + 1];	/* NULL terminated	*/
	int argc, inquotes;
	int rc = 0;

	debug_parser("[RUN_COMMAND] cmd[%p]=\"", cmd);
	if (DEBUG_PARSER) {
		/* use puts - string may be loooong */
		puts("%s", cmd ? cmd : "NULL");
		puts("\"\n");
	}

	if (!cmd || !*cmd)
		return -1;	/* empty command */

	if (strlen(cmd) >= CONFIG_SYS_CBSIZE) {
		puts("## Command too long!\n");
		return -1;
	}

	/* Process separators and check for invalid
	 * repeatable commands
	 */

	debug_parser("[PROCESS_SEPARATORS] %s\n", cmd);
	while (*str) {
		/*
		 * Find separator, or string end
		 * Allow simple escape of ';' by writing "\;"
		 */
		for (inquotes = 0, sep = str; *sep; sep++) {
			if ((*sep == '\'') &&
			    (*(sep - 1) != '\\'))
				inquotes = !inquotes;

			if (!inquotes &&
			    (*sep == ';') &&	/* separator		*/
			    (sep != str) &&	/* past string start	*/
			    (*(sep - 1) != '\\'))	/* and NOT escaped */
				break;
		}

		/*
		 * Limit the token to data between separators
		 */
		token = str;
		if (*sep) {
			str = sep + 1;	/* start of command for next pass */
			*sep = '\0';
		} else {
			str = sep;	/* no more commands for next pass */
		}
		debug_parser("token: \"%s\"\n", token);

		/* Extract arguments */
		argc = cli_simple_parse_line(token, argv);
		if (argc == 0) {
			rc = -1;	/* no command at all */
			continue;
		}

		if (cmd_process(flag, argc, argv)) {
			rc = 0xE0F;	/* exit command line */
			break;
		}
	}

	return rc;
}

void cli_simple_loop(void)
{
	int len;
	int flag;
	int rc;

	plat_cli_prepare();
	for (;;) {
		len = cli_readline(CONFIG_SYS_PROMPT);

		flag = 0;	/* assume no special flags for now */

		if (len == -1)
			puts("<INTERRUPT>\n");
		else
			rc = cli_simple_run_command(console_buffer, flag);

		if (rc == 0xE0F) {
			puts("<EXIT>\n");
			break;
		}
	}
}

int abortboot_single_key(int bootdelay)
{
	int abort = 0;
	uint64_t ts;
	/*
	 * Check if key already pressed
	 */
	if (getchar() == CLI_HOT_KEY || bootdelay == 0) {	/* we got a key press	*/
		abort = 1;	/* don't auto boot	*/
		goto out;
	}

	if (bootdelay == -1)
		goto out;	/* don't wait, just boot	*/

	printf("Hit key to stop autoboot: %02d ", bootdelay);

	while ((bootdelay > 0) && (!abort)) {
		--bootdelay;
		/* delay 1000 ms */
		ts = timeout_init_us(1000 * 1000);
		do {
			if (getchar() == CLI_HOT_KEY) {	/* we got a key press	*/
				abort  = 1;	/* don't auto boot	*/
				bootdelay = 0;	/* no more delay	*/
				break;
			}
			mdelay(10);
		} while (!abort && !timeout_elapsed(ts));

		printf("\b\b\b%02d ", bootdelay);
	}

	putc('\n');
out:
	return abort;
}
