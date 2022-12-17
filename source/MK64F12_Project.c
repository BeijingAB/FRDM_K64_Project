
#include <stdio.h>
#include "MK64F12.h"


#include "led.h"
#include "i2c.h"
#include "accel.h"




// press SW2 to  init i2c
void key_delay()
{
	// Enable clock for port C
	SIM->SCGC5 |= SIM_SCGC5_PORTC(1);

	// Set as GPIO
	PORTC->PCR[6] |= PORT_PCR_MUX(1);

	// Set as input
	GPIOC->PDDR &= ~GPIO_PDDR_PDD(6);

	while (GPIOC->PDIR & GPIO_PDIR_PDI(1 << 6))
	{

	}

//	led_init();
//	red_led_on();
}

#ifndef UART_CLK
#define UART_CLK 15000000
#endif

#define UART_BAUD_RATE 115200

static char* tx_str;
static int tx_str_index = 0;
static int tx_done = 0;

void UART0_RX_TX_DriverIRQHandler()
{

}

void print(char* str)
{
	tx_str = str;
	tx_done = 0;

	// Enable Transmission Complete interrupt
	UART0->C2 |= UART_C2_TCIE(1);
	UART0->D = tx_str[tx_str_index++];

	while (!tx_done);

	// Disable Transmission Complete interrupt
	UART0->C2 &= ~UART_C2_TCIE(1);
}

int main(void) {

	key_delay();

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

//	print("Hello");
//
//	while (1)
//	{
//		//for (int i = 0; i < 100000; i++);
//	}
//
//
//while(1);

	accel_init();
	accel acc;

	while (1)
	{
		get_accel(&acc);
		printf("x:%d， y:%d， z:%d\n\r", acc.x, acc.y, acc.z);
		for (int i = 0; i < 655360; i++)
		{

		}

	}

    return 0 ;
}
