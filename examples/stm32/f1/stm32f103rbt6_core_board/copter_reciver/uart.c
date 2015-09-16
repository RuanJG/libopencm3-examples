#define USART1_USE_IRQ
#define USART2_USE_IRQ
#define USART3_USE_IRQ

#define RX_BUFF_SIZE 1024
typedef struct __usart_buffer
{
	uint8_t irq_rx_buffer[RX_BUFF_SIZE];
	uint16_t irq_rx_index;
	uint8_t rx_buffer[RX_BUFF_SIZE];
	uint16_t rx_index;

}usart_buffer_t

usart_buffer_t usart1_buffer;
usart_buffer_t usart2_buffer;
usart_buffer_t usart3_buffer;

static void usart1_setup(void)
{
	/* Enable clocks for GPIO port A (for GPIO_USART1_TX) and USART1. */
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_USART1);

	/* Enable the USART1 interrupt. */
	nvic_enable_irq(NVIC_USART1_IRQ);

	/* Setup GPIO pin GPIO_USART1_RE_TX on GPIO port B for transmit. */
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);
	/* Setup GPIO pin GPIO_USART1_RE_RX on GPIO port B for receive. */
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT,
		      GPIO_CNF_INPUT_FLOAT, GPIO_USART1_RX);

	/* Setup UART parameters. */
	usart_set_baudrate(USART1, 115200);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
	usart_set_mode(USART1, USART_MODE_TX_RX);

	#ifdef USART1_USE_IRQ
	/* Enable USART1 Receive interrupt. */
	USART_CR1(USART1) |= USART_CR1_RXNEIE;
	#endif

	/* Finally enable the USART. */
	usart_enable(USART1);
}
#ifdef USART1_USE_IRQ
void usart1_isr(void)
{
	uint8_t data = 'A';
	int rx_index;
	int irq_index;
	uint8_t *irq_buff;
	uint8_t *rx_buff;
	int i;

	irq_index = usart1_buffer.irq_rx_index;  
	rx_index = usart1_buffer.rx_index;  
	irq_buff = usart1_buffer.irq_rx_buffer;
	rx_buff = usart1_buffer.rx_buffer;
	/* Check if we were called because of RXNE. */
	if (((USART_CR1(USART1) & USART_CR1_RXNEIE) != 0) &&
	    ((USART_SR(USART1) & USART_SR_RXNE) != 0)) {
		/* Retrieve the data from the peripheral. */

		data = usart_recv(USART1);
		if( irq_index < RX_BUFF_SIZE)
			irq_buffer[irq_index++]= data;
		if(rx_index == 0 )
		{
			for( i = 0 ; i< irq_index; i++)
				rx_buff[i] = irq_buff[i];
			usart1_buffer.rx_index = irq_index;
			usart1_buffer.irq_index = 0;
		}
	}
}
#endif
