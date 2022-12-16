
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"


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

#define SYSTEM_CLOCK 120000000
#define BAUD_RATE 115200
static int sbr = SYSTEM_CLOCK / BAUD_RATE / 16;

int main(void) {

	key_delay();

	// Enable clock for port B
	SIM->SCGC5 |= SIM_SCGC5_PORTB(1);

	// PortA Mux as UART0, p248
	PORTB->PCR[16] |= PORT_PCR_MUX(3); // UART_Rx
	PORTB->PCR[17] |= PORT_PCR_MUX(3); // UART_Tx

	// Enable UART clock
	SIM->SCGC4 |= SIM_SCGC4_UART1(1);

	// Baud rate, BDH first, BDL last
	UART1->BDH |= UART_BDH_SBR(sbr >> 8);
	UART1->BDL |= UART_BDL_SBR(sbr);

	// Enable receive and transmit
	UART1->C2 |= UART_C2_TE(1);// | UART_C2_RE(1);

	UART1->D = 'A';

	while (1)
	{
		UART1->D = 'A';
	}

	accel_init();
	accel acc;

	while (1)
	{
		get_accel(&acc);
//		printf("x:%d， y:%d， z:%d\n\r", acc.x, acc.y, acc.z);
		for (int i = 0; i < 655360; i++)
		{

		}

	}

    return 0 ;
}
