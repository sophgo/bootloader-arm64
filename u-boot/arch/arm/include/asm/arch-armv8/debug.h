#ifndef __ASM_ARCH_DEBUG_H__
#define __ASM_ARCH_DEBUG_H__

#define error(fmt, args...) printf("ERROR: " pr_fmt(fmt) "\nat %s:%d/%s()\n",	\
				    ##args, __FILE__, __LINE__, __func__)

#endif
