
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"


#include "led.h"

#define I2C_ADDR 0x1D
#define I2C_WHOAMI 0x0D


static char a;


static int i = 0;
static char rd_data = 0;

void I2C0_DriverIRQHandler(void);
void I2C0_DriverIRQHandler(void)
{
	i++;


	if (i == 3)
	{

		// Clear interrupt
		I2C0->S |= I2C_S_IICIF(1);


		// Transmit mode select, Transmit
		I2C0->C1 &= ~I2C_C1_TX(1);

//		I2C0->C1 &= ~I2C_C1_MST(1);

		a = I2C0->D;
		a = 0;

		// i2c who am i successful here, need to restart the board power
	}

	if (i == 2)
	{
		// Clear interrupt
		I2C0->S |= I2C_S_IICIF(1);

		// Re-start
		I2C0->C1 |= I2C_C1_RSTA(1);

		I2C0->D = I2C_D_DATA(I2C_ADDR << 1 | 1);

	}

	if (i == 1)
	{
		for (int i = 0; i < 100; i++)
		{

		}

		// Clear interrupt
		I2C0->S |= I2C_S_IICIF(1);

		// Tx-> !Last Byte Transmitted
		if ((I2C0->S & I2C_S_RXAK(1)) == 0)
		{
			I2C0->D = I2C_WHOAMI;
		}
		else
		{
			// STOP
			I2C0->C1 &= ~I2C_C1_MST(1);
		}
	}


}

int main(void) {
//	NVIC_EnableIRQ(I2C0_IRQn);
	// P78 k64 ref manual
	NVIC->ISER[I2C0_IRQn >> 5] |= 1 << (I2C0_IRQn & 0x1F);


	// Enable I2C_0 clock
	SIM->SCGC4 |= SIM_SCGC4_I2C0(1);

	// Enable PORT_E clock
	SIM->SCGC5 |= SIM_SCGC5_PORTE(1);

	// PORT E Mux I2C, P251
	PORTE->PCR[24] |= PORT_PCR_MUX(5); // SCL
	PORTE->PCR[25] |= PORT_PCR_MUX(5); // SDA

	// I2C_0 Freq divider = 576
	I2C0->F = I2C_F_MULT(0) | I2C_F_ICR(0x2C);

	// Enable I2C and interrupt
	I2C0->C1 |= I2C_C1_IICEN(1) | I2C_C1_IICIE(1);

	// Transmit mode select, Transmit
	I2C0->C1 |= I2C_C1_TX(1);

	// Master mode, start signal
	I2C0->C1 |= I2C_C1_MST(1);

	// Send slave address
	I2C0->D = I2C_D_DATA(I2C_ADDR << 1 | 0);





	while (1);

    return 0 ;
}
