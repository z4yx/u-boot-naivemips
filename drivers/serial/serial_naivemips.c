
#include <common.h>
#include <clk.h>
#include <dm.h>
#include <serial.h>
#include <wait_bit.h>

DECLARE_GLOBAL_DATA_PTR;

/* Register offsets */
#define U_DR        0x00
#define U_SR        0x04

struct naivemips_uart_priv {
	void __iomem *base;
};

static int naivemips_serial_init(void __iomem *base, u32 baudrate)
{
	return 0;
}

/* Check whether any char pending in RX fifo */
static int naivemips_uart_pending_input(void __iomem *base)
{
	return readl(base + U_SR) & 2;
}

static int naivemips_uart_pending(struct udevice *dev, bool input)
{
	struct naivemips_uart_priv *priv = dev_get_priv(dev);

	if (input)
		return naivemips_uart_pending_input(priv->base);

	return !(readl(priv->base + U_SR) & 1);
}

static int naivemips_uart_setbrg(struct udevice *dev, int baudrate)
{
	struct naivemips_uart_priv *priv = dev_get_priv(dev);

	return naivemips_serial_init(priv->base, baudrate);
}

static int naivemips_uart_putc(struct udevice *dev, const char ch)
{
	struct naivemips_uart_priv *priv = dev_get_priv(dev);

	/* Check if Tx FIFO is full */
	if (!(readl(priv->base + U_SR) & 1))
		return -EAGAIN;

	/* pump the char to tx buffer */
	writel(ch, priv->base + U_DR);

	return 0;
}

static int naivemips_uart_getc(struct udevice *dev)
{
	struct naivemips_uart_priv *priv = dev_get_priv(dev);

	/* return error if RX fifo is empty */
	if (!naivemips_uart_pending_input(priv->base))
		return -EAGAIN;

	/* read the character from rx buffer */
	return readl(priv->base + U_DR) & 0xff;
}

static int naivemips_uart_probe(struct udevice *dev)
{
	struct naivemips_uart_priv *priv = dev_get_priv(dev);
	fdt_addr_t addr;
	fdt_size_t size;

	/* get address */
	addr = fdtdec_get_addr_size(gd->fdt_blob, dev_of_offset(dev), "reg",
				    &size);
	if (addr == FDT_ADDR_T_NONE)
		return -EINVAL;

	priv->base = ioremap(addr, size);

	/* initialize serial */
	return naivemips_serial_init(priv->base, CONFIG_BAUDRATE);
}

static const struct dm_serial_ops naivemips_uart_ops = {
	.putc		= naivemips_uart_putc,
	.pending	= naivemips_uart_pending,
	.getc		= naivemips_uart_getc,
	.setbrg		= naivemips_uart_setbrg,
};

static const struct udevice_id naivemips_uart_ids[] = {
	{ .compatible = "naivemips-uart" },
	{}
};

U_BOOT_DRIVER(naivemips_serial) = {
	.name		= "naivemips-uart",
	.id		= UCLASS_SERIAL,
	.of_match	= naivemips_uart_ids,
	.probe		= naivemips_uart_probe,
	.ops		= &naivemips_uart_ops,
	.flags		= DM_FLAG_PRE_RELOC,
	.priv_auto_alloc_size = sizeof(struct naivemips_uart_priv),
};

#ifdef CONFIG_DEBUG_UART_NAIVEMIPS
#include <debug_uart.h>

static inline void _debug_uart_init(void)
{
	// void __iomem *base = (void __iomem *)CONFIG_DEBUG_UART_BASE;

}

static inline void _debug_uart_putc(int ch)
{
	while(!(readl((void*)CONFIG_DEBUG_UART_BASE+U_SR) & 1));
	writel(ch, (void*)CONFIG_DEBUG_UART_BASE+U_DR);
}

DEBUG_UART_FUNCS
#endif
