#include "uart.h"

static char* tx_str;
static int tx_str_index = 0;
static int tx_done = 0;

void UART0_RX_TX_DriverIRQHandler()
{
	// In Tx mode and Tx one byte done
	if (UART0->S1 & UART_S1_TC(1))
	{
		if (tx_str[tx_str_index] != 0x00)
		{
			// Last byte yet Tx
			UART0->D = tx_str[tx_str_index];
			tx_str_index++;
		}
		else
		{
			tx_done = 1;
			// Last byte already Tx
			// Disable Transmission Complete interrupt
			UART0->C2 &= ~UART_C2_TCIE(1);
		}
	}

}

// Unknown about the first interrupt
void uart_print(char* str)
{
	tx_str_index = 0;
	tx_str = str;
	tx_done = 0;

	// Enable Transmission Complete interrupt
	UART0->C2 |= UART_C2_TCIE(1);


	while (!tx_done);
}

void uart_init()
{

	unsigned int sbr;
	unsigned int brfa = 0;

	sbr = UART_CLK / UART_BAUD_RATE / 16;

	// Enable clock for port B
	SIM->SCGC5 |= SIM_SCGC5_PORTB(1);

	// PortB Mux as UART0, chip manual p248, board manual p15 error-> UART0
	PORTB->PCR[16] |= PORT_PCR_MUX(3); // UART_Rx
	PORTB->PCR[17] |= PORT_PCR_MUX(3); // UART_Tx


	// Enable Uart0 Interrupt
	//	NVIC_EnableIRQ(I2C0_IRQn);// P78 k64 ref manual
	NVIC->ISER[UART0_RX_TX_IRQn >> 5] |= 1 << (UART0_RX_TX_IRQn & 0x1F);

	// Enable UART clock
	SIM->SCGC4 |= SIM_SCGC4_UART0(1);

	// Baud rate, BDH first, BDL last
	UART0->BDH |= UART_BDH_SBR(sbr >> 8);
	UART0->BDL |= UART_BDL_SBR(sbr);
	UART0->C4 |= UART_C4_BRFA(brfa);

	// Enable receive and transmit
	UART0->C2 |= UART_C2_TE(1) | UART_C2_RE(1);

}
