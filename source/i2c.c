/*
 * i2c.c
 *
 *  Created on: Dec 15, 2022
 *      Author: liangj
 */


#include "i2c.h"




static int i = 0;


static char dev_addr;
static char reg_addr;
static char rd_byte;

void I2C0_DriverIRQHandler(void)
{
	i++;
	// Clear interrupt
	I2C0->S |= I2C_S_IICIF(1);

	if (i == 4)
	{
		// STOP (When i2c read last data need stop first then read, need dummy read and no ack before last read)
		I2C0->C1 &= ~I2C_C1_MST(1);
		rd_byte = I2C0->D;
	}

	if (i == 3)
	{

		// Transmit mode select, Transmit
		I2C0->C1 &= ~I2C_C1_TX(1);

		// No ack
		I2C0->C1 |= I2C_C1_TXAK(1);

		// dummy read
		a = I2C0->D;
	}

	if (i == 2)
	{

		// Re-start
		I2C0->C1 |= I2C_C1_RSTA(1);

		I2C0->D = I2C_D_DATA(dev_addr << 1 | 1);

	}

	if (i == 1)
	{

		// Tx-> !Last Byte Transmitted
		if ((I2C0->S & I2C_S_RXAK(1)) == 0)
		{
			I2C0->D = reg_addr;
		}
		else
		{
			// STOP
			I2C0->C1 &= ~I2C_C1_MST(1);
		}
	}
}

void i2c_init()
{
	//	NVIC_EnableIRQ(I2C0_IRQn);// P78 k64 ref manual
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
}

void i2c_single_byte_read(char dev_addr_i, char reg_addr_i, char* byte)
{
	dev_addr = dev_addr_i;
	reg_addr = reg_addr_i;

	// Transmit mode select, Transmit
	I2C0->C1 |= I2C_C1_TX(1);

	// Master mode, start signal
	I2C0->C1 |= I2C_C1_MST(1);

	// Send slave address
	I2C0->D = I2C_D_DATA(dev_addr << 1 | 0);
}


