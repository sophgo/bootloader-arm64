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
#include <cli.h>

char console_buffer[CONFIG_SYS_CBSIZE + 1];	/* console I/O buffer	*/

/*
 * cmdline-editing related codes from vivi.
 * Author: Janghoon Lyu <nandy@mizi.com>
 */

void putnstr(const char *str, int str_len)
{
	for (int i = 0; i < str_len; i++)
		putc(*(str + i));
}

#define CTL_CH(c)		((c) - 'a' + 1)
#define CTL_BACKSPACE		('\b')
#define DEL			((char)255)
#define DEL7			((char)127)
#define CREAD_HIST_CHAR		('!')

#define getcmd_putch(ch)	putc(ch)
#define getcmd_getch()		getchar()
#define getcmd_cbeep()		getcmd_putch('\a')

#define BEGINNING_OF_LINE() {			\
	while (num) {				\
		getcmd_putch(CTL_BACKSPACE);	\
		num--;				\
	}					\
}

#define ERASE_TO_EOL() {				\
	if (num < eol_num) {				\
		printf("%*s", (int)(eol_num - num), ""); \
		do {					\
			getcmd_putch(CTL_BACKSPACE);	\
		} while (--eol_num > num);		\
	}						\
}

#define REFRESH_TO_EOL() {			\
	if (num < eol_num) {			\
		wlen = eol_num - num;		\
		putnstr(buf + num, wlen);	\
		num = eol_num;			\
	}					\
}

static void cread_add_char(char ichar, int insert, unsigned long *num,
			   unsigned long *eol_num, char *buf, unsigned long len)
{
	unsigned long wlen;

	/* room ??? */
	if (insert || *num == *eol_num) {
		if (*eol_num > len - 1) {
			getcmd_cbeep();
			return;
		}
		(*eol_num)++;
	}

	if (insert) {
		wlen = *eol_num - *num;
		if (wlen > 1)
			memmove(&buf[*num + 1], &buf[*num], wlen - 1);

		buf[*num] = ichar;
		putnstr(buf + *num, wlen);
		(*num)++;
		while (--wlen)
			getcmd_putch(CTL_BACKSPACE);
	} else {
		/* echo the character */
		wlen = 1;
		buf[*num] = ichar;
		putnstr(buf + *num, wlen);
		(*num)++;
	}
}

static void cread_add_str(char *str, int strsize, int insert,
			  unsigned long *num, unsigned long *eol_num,
			  char *buf, unsigned long len)
{
	while (strsize--) {
		cread_add_char(*str, insert, num, eol_num, buf, len);
		str++;
	}
}

static int cread_line(const char *const prompt, char *buf, unsigned int *len,
		      int timeout)
{
	unsigned long num = 0;
	unsigned long eol_num = 0;
	unsigned long wlen;
	char ichar;
	int insert = 1;
	int esc_len = 0;
	char esc_save[8];
	int init_len = strlen(buf);
	int rc;

	if (init_len)
		cread_add_str(buf, init_len, 1, &num, &eol_num, buf, *len);

	while (1) {
		rc = getcmd_getch();
		if (rc == -1)
			continue;
		else
			ichar = rc;

		if ((ichar == '\n') || (ichar == '\r')) {
			putc('\n');
			break;
		}

		/*
		 * handle standard linux xterm esc sequences for arrow key, etc.
		 */
		if (esc_len != 0) {
			enum { ESC_REJECT, ESC_SAVE, ESC_CONVERTED } act = ESC_REJECT;

			if (esc_len == 1) {
				if (ichar == '[' || ichar == 'O')
					act = ESC_SAVE;
			} else if (esc_len == 2) {
				switch (ichar) {
				case 'D':	/* <- key */
					ichar = CTL_CH('b');
					act = ESC_CONVERTED;
					break;	/* pass off to ^B handler */
				case 'C':	/* -> key */
					ichar = CTL_CH('f');
					act = ESC_CONVERTED;
					break;	/* pass off to ^F handler */
				case 'H':	/* Home key */
					ichar = CTL_CH('a');
					act = ESC_CONVERTED;
					break;	/* pass off to ^A handler */
				case 'F':	/* End key */
					ichar = CTL_CH('e');
					act = ESC_CONVERTED;
					break;	/* pass off to ^E handler */
				case 'A':	/* up arrow */
					ichar = CTL_CH('p');
					act = ESC_CONVERTED;
					break;	/* pass off to ^P handler */
				case 'B':	/* down arrow */
					ichar = CTL_CH('n');
					act = ESC_CONVERTED;
					break;	/* pass off to ^N handler */
				case '1':
				case '3':
				case '4':
				case '7':
				case '8':
					if (esc_save[1] == '[') {
						/* see if next character is ~ */
						act = ESC_SAVE;
					}
					break;
				}
			} else if (esc_len == 3) {
				if (ichar == '~') {
					switch (esc_save[2]) {
					case '3':	/* Delete key */
						ichar = CTL_CH('d');
						act = ESC_CONVERTED;
						break;	/* pass to ^D handler */
					case '1':	/* Home key */
					case '7':
						ichar = CTL_CH('a');
						act = ESC_CONVERTED;
						break;	/* pass to ^A handler */
					case '4':	/* End key */
					case '8':
						ichar = CTL_CH('e');
						act = ESC_CONVERTED;
						break;	/* pass to ^E handler */
					}
				}
			}

			switch (act) {
			case ESC_SAVE:
				esc_save[esc_len++] = ichar;
				continue;
			case ESC_REJECT:
				esc_save[esc_len++] = ichar;
				cread_add_str(esc_save, esc_len, insert,
					      &num, &eol_num, buf, *len);
				esc_len = 0;
				continue;
			case ESC_CONVERTED:
				esc_len = 0;
				break;
			}
		}

		switch (ichar) {
		case 0x1b:
			if (esc_len == 0) {
				esc_save[esc_len] = ichar;
				esc_len = 1;
			} else {
				puts("impossible condition #876\n");
				esc_len = 0;
			}
			break;

		case CTL_CH('a'):
			BEGINNING_OF_LINE();
			break;
		case CTL_CH('c'):	/* ^C - break */
			*buf = '\0';	/* discard input */
			return -1;
		case CTL_CH('f'):
			if (num < eol_num) {
				getcmd_putch(buf[num]);
				num++;
			}
			break;
		case CTL_CH('b'):
			if (num) {
				getcmd_putch(CTL_BACKSPACE);
				num--;
			}
			break;
		case CTL_CH('d'):
			if (num < eol_num) {
				wlen = eol_num - num - 1;
				if (wlen) {
					memmove(&buf[num], &buf[num + 1], wlen);
					putnstr(buf + num, wlen);
				}

				getcmd_putch(' ');
				do {
					getcmd_putch(CTL_BACKSPACE);
				} while (wlen--);
				eol_num--;
			}
			break;
		case CTL_CH('k'):
			ERASE_TO_EOL();
			break;
		case CTL_CH('e'):
			REFRESH_TO_EOL();
			break;
		case CTL_CH('o'):
			insert = !insert;
			break;
		case CTL_CH('x'):
		case CTL_CH('u'):
			BEGINNING_OF_LINE();
			ERASE_TO_EOL();
			break;
		case DEL:
		case DEL7:
		case 8:
			if (num) {
				wlen = eol_num - num;
				num--;
				memmove(&buf[num], &buf[num + 1], wlen);
				getcmd_putch(CTL_BACKSPACE);
				putnstr(buf + num, wlen);
				getcmd_putch(' ');
				do {
					getcmd_putch(CTL_BACKSPACE);
				} while (wlen--);
				eol_num--;
			}
			break;
		case CTL_CH('p'):
		case CTL_CH('n'):
		{
			esc_len = 0;

			getcmd_cbeep();
			continue;
		}
		default:
			if (ichar >= ' ' && ichar <= '~') {
				cread_add_char(ichar, insert, &num, &eol_num,
					       buf, *len);
			}
			break;
		}
	}
	*len = eol_num;
	buf[eol_num] = '\0';	/* lose the newline */

	return 0;
}

static int cli_readline_into_buffer(const char *const prompt, char *buffer,
				    int timeout)
{
	char *p = buffer;
	unsigned int len = CONFIG_SYS_CBSIZE;
	int rc;

	if (prompt)
		puts("%s", prompt);

	rc = cread_line(prompt, p, &len, timeout);
	return rc < 0 ? rc : len;
}

int cli_readline(const char *const prompt)
{
	/*
	 * If console_buffer isn't 0-length the user will be prompted to modify
	 * it instead of entering it from scratch as desired.
	 */
	console_buffer[0] = '\0';

	return cli_readline_into_buffer(prompt, console_buffer, 0);
}
