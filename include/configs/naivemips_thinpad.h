#ifndef __NAIVEMIPS_THINPAD_CONFIG_H
#define __NAIVEMIPS_THINPAD_CONFIG_H

/* BootROM + MIG is pretty smart. DDR and Cache initialized */
#define CONFIG_SKIP_LOWLEVEL_INIT

/*--------------------------------------------
 * CPU configuration
 */
/* CPU Timer rate */
#define CONFIG_SYS_MIPS_TIMER_FREQ	8000000

/* Cache Configuration */
#define CONFIG_SYS_MIPS_CACHE_MODE	CONF_CM_CACHABLE_NONCOHERENT

/*----------------------------------------------------------------------
 * Memory Layout
 */

/* SDRAM Configuration (for final code, data, stack, heap) */
#define CONFIG_SYS_SDRAM_BASE		0x80000000
#define CONFIG_SYS_SDRAM_SIZE		0x00800000	/* 8 Mbytes */
#define CONFIG_SYS_INIT_SP_ADDR		\
	(CONFIG_SYS_SDRAM_BASE + CONFIG_SYS_SDRAM_SIZE - 0x1000)

#define CONFIG_SYS_MALLOC_LEN		(256 << 10)
#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_LOAD_ADDR		0x80000000 /* default load address */

/*----------------------------------------------------------------------
 * Commands
 */
//#define CONFIG_SYS_LONGHELP		/* undef to save memory */

/*------------------------------------------------------------
 * Console Configuration
 */
#define CONFIG_SYS_CBSIZE		1024 /* Console I/O Buffer Size   */
#define CONFIG_SYS_MAXARGS		16   /* max number of command args*/

/* -------------------------------------------------
 * Environment
 */
#define CONFIG_ENV_IS_NOWHERE	1
#define CONFIG_ENV_SIZE		0x4000

/* ---------------------------------------------------------------------
 * Board boot configuration
 */
#define CONFIG_TIMESTAMP	/* Print image info with timestamp */

/* Ethernet */
#define CONFIG_DRIVER_DM9000
#define CONFIG_DM9000_BASE      0xbc020100
#define DM9000_IO           CONFIG_DM9000_BASE
#define DM9000_DATA         (CONFIG_DM9000_BASE + 4)
#define CONFIG_DM9000_USE_16BIT
#define CONFIG_DM9000_NO_SROM
#define CONFIG_NET_RETRY_COUNT      20
#define CONFIG_RESET_PHY_R

// #define CONFIG_DM9000_DEBUG

#endif /* __NAIVEMIPS_THINPAD_CONFIG_H */

