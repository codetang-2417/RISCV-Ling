// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <gj@denx.de>
 *
 * Copyright (C) 2011 Andes Technology Corporation
 * Shawn Lin, Andes Technology Corporation <nobuhiro@andestech.com>
 * Macpaul Lin, Andes Technology Corporation <macpaul@andestech.com>
 */

/* CPU specific code */
#include <common.h>
#include <command.h>
#include <cpu_func.h>
#include <irq_func.h>
#include <watchdog.h>
#include <asm/cache.h>

#include <faraday/ftwdt010_wdt.h>

/*
 * cleanup_before_linux() is called just before we call linux
 * it prepares the processor for linux
 *
 * we disable interrupt and caches.
 */
int cleanup_before_linux(void)
{
	disable_interrupts();

	/* turn off I/D-cache */
	cache_flush();
	icache_disable();
	dcache_disable();
	return 0;
}

int do_reset(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	disable_interrupts();

	/*
	 * reset to the base addr of andesboot.
	 * currently no ROM loader at addr 0.
	 * do not use reset_cpu();
	 */
#ifdef CONFIG_FTWDT010_WATCHDOG
	/*
	 * workaround: if we use CONFIG_HW_WATCHDOG with ftwdt010, will lead
	 * automatic hardware reset when booting Linux.
	 * Please do not use CONFIG_HW_WATCHDOG and WATCHDOG_RESET() here.
	 */
	ftwdt010_wdt_reset();
	while (1)
		;
#endif /* CONFIG_FTWDT010_WATCHDOG */

	/*NOTREACHED*/
}
