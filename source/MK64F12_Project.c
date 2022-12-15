
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
#define WHO_AM_I 0x0D

#define STATUS 0x00
#define SYSMOD 0x0B

#define CTRL_REG1 0x2A


int main(void) {

	key_delay();

	i2c_init();

	char byte;
	i2c_single_byte_read(I2C_ADDR, WHO_AM_I, &byte);

	byte = 1;

	i2c_single_byte_write(I2C_ADDR, CTRL_REG1, byte);

	byte = 0;

	i2c_single_byte_read(I2C_ADDR, CTRL_REG1, &byte);

	byte = 1;



	while (1);

    return 0 ;
}
