
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

int main(void) {

//	key_delay();

//	// OSC0 -> OSCSELCLK
//	MCG->C7 |= MCG_C7_OSCSEL(0);
//
//	// OSCSELCLK -> MCGOUTCLK
//	MCG->C1 |= MCG_C1_CLKS(2);

/* Clock settings default
 * System clokc <- [SIM_CLKDIV1 (OUTDIV1 = 0) /1] <- MCGOUTCLK <- [MCG_C1 (CLKS = 0) Output of PLL/FLL]
 * <- [MCG_C6 (PLLS = 0) FLL selected] <- DCOOUT <- [MCG_C4 (DMX32 = 0, DRST_DRS = 0),
 * Ref Range = 31.25-2 ~ 39.0625 kHz, FLL Factor = 640, DCO Range = 20 ~ 25 MHz] <- [MCG_C1 (IREFS = 1)
 * Slow internal Ref clk] <- Slow Clock <-
 *
 *
 * */

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
