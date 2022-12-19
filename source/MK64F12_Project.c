
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

int main(void) {

//	key_delay();

	clock_init();

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
