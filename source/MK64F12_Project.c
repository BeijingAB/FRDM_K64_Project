
#include <stdio.h>
#include "MK64F12.h"

#include "clock.h"
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

void SDHC_DriverIRQHandler()
{

}

int main(void) {

//	key_delay();

	clock_init();


	// Enable clock for Port E
	SIM->SCGC5 |= SIM_SCGC5_PORTE(1);

	// Alt 4, p250 ref manual
	PORTE->PCR[0] |= PORT_PCR_MUX(4);
	PORTE->PCR[1] |= PORT_PCR_MUX(4);
	PORTE->PCR[2] |= PORT_PCR_MUX(4);
	PORTE->PCR[3] |= PORT_PCR_MUX(4);
	PORTE->PCR[4] |= PORT_PCR_MUX(4);
	PORTE->PCR[5] |= PORT_PCR_MUX(4);

	// Enable clock for SDHC
	SIM->SCGC3 |= SIM_SCGC3_SDHC(1);

	// Enable interrupt for SDHC
	//	NVIC_EnableIRQ(I2C0_IRQn);// P78 k64 ref manual
	NVIC->ISER[SDHC_IRQn >> 5] |= 1 << (SDHC_IRQn & 0x1F);

	while (1);



	uart_init();
	while (1)
	{
		uart_print("Hello");
	}


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
