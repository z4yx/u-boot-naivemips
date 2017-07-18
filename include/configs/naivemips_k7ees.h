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
#define CONFIG_CMDLINE_EDITING

/*------------------------------------------------------------
 * Console Configuration
 */
#define CONFIG_SYS_CBSIZE		1024 /* Console I/O Buffer Size   */
#define CONFIG_SYS_MAXARGS		16   /* max number of command args*/

/* -------------------------------------------------
 * Environment
 */
#define CONFIG_ENV_IS_IN_FLASH  1
#define CONFIG_ENV_ADDR         0xBE7E0000  /* last sector of 8M flash */
#define CONFIG_ENV_SECT_SIZE    0x20000
#define CONFIG_ENV_SIZE		0x4000
#define CONFIG_EXTRA_ENV_SETTINGS \
    "autoload=no\0" \
    "s_linux=setenv bootfile mips-linux.ub;setenv loadaddr 0x800FFFC0\0" \
    "s_ucore=setenv bootfile ucore.ub;setenv loadaddr 0x80000000\0" \
    "serverip=192.168.1.30\0" \
    "ipaddr=192.168.1.60\0" \
    "netmask=255.255.255.0\0"

/* ---------------------------------------------------------------------
 * Board boot configuration
 */
#define CONFIG_TIMESTAMP	/* Print image info with timestamp */

/* Flash */
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE
#define CONFIG_SYS_MAX_FLASH_BANKS_DETECT   1
#define CONFIG_SYS_MAX_FLASH_SECT           64

// #define DEBUG

#endif /* __NAIVEMIPS_THINPAD_CONFIG_H */

