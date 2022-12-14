
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"


#include "led.h"
#include "i2c.h"





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

#define I2C_ADDR 0x1D
#define I2C_WHOAMI 0x0D

int main(void) {

	key_delay();

	i2c_init();

	char byte;
	i2c_single_byte_read(I2C_ADDR, I2C_WHOAMI, &byte);

	byte;




	while (1);

    return 0 ;
}
