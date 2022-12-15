
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
#define OUT_X_MSB 0x01
#define OUT_X_LSB 0x02
#define OUT_Y_MSB 0x03
#define OUT_Y_LSB 0x04
#define OUT_Z_MSB 0x05
#define OUT_Z_LSB 0x06

#define SYSMOD 0x0B

#define CTRL_REG1 0x2A
#define CTRL_REG2 0x2B
#define CTRL_REG3 0x2C
#define CTRL_REG4 0x2D
#define CTRL_REG5 0x2E


int main(void) {
	printf("Test\n\r");

	key_delay();

	i2c_init();

	char byte;
	i2c_single_byte_read(I2C_ADDR, WHO_AM_I, &byte);

	byte = 1;

	i2c_single_byte_write(I2C_ADDR, CTRL_REG1, byte);

	byte = 0;

	i2c_single_byte_read(I2C_ADDR, CTRL_REG1, &byte);

	byte = 1;



	while (1)
	{
		i2c_single_byte_read(I2C_ADDR, STATUS, &byte);

		byte = 1;

		i2c_single_byte_read(I2C_ADDR, OUT_X_MSB, &byte);

		printf("%d\n\r", byte);
	}

    return 0 ;
}
