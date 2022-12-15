/*
 * i2c.c
 *
 *  Created on: Dec 15, 2022
 *      Author: liangj
 */


#include "i2c.h"




static int i = 0;

// i2c slave device address
static char dev_addr;

// i2c slave register address
static char reg_addr;

// byte read from slave
static char rd_byte;

// one byte read finished
static int rd_done = 0;

// how many byte need to send from master to slave
static int byte_to_send = 0;

// Switch to Rx mode when transmit mode
static int switch_Rx = 0;

// Master in Tx or Rx mode
static int Tx = 0;

enum mode
{
	Single_read,
	Multiple_read,
	Single_write,
	Multiple_write
};

static int i2c_access_mode;

void I2C0_DriverIRQHandler(void)
{
	i++;
	// Clear interrupt
	I2C0->S |= I2C_S_IICIF(1);


	// In receive mode
	if (Tx == 0) //4
	{
		// STOP (When i2c read last data need stop first then read, need dummy read and no ack before last read)
		I2C0->C1 &= ~I2C_C1_MST(1);
		rd_byte = I2C0->D;
		rd_done = 1;
	}

//	if (i == 3)
//	{
//
//		// Transmit mode select, Receive
//		I2C0->C1 &= ~I2C_C1_TX(1);
//
//		// No ack
//		I2C0->C1 |= I2C_C1_TXAK(1);
//
//		// dummy read
//		rd_byte = I2C0->D;
//
//		Tx = 0;
//	}

	// In Transmit mode
	if (Tx == 1)
	{
		// Last byte yet transmitted
		if (byte_to_send != 0) // 1
		{
			if ((I2C0->S & I2C_S_RXAK(1)) == 0)
			{
				if (switch_Rx) // 3
				{
					// Transmit mode select, Receive
					I2C0->C1 &= ~I2C_C1_TX(1);

					// No ack
					I2C0->C1 |= I2C_C1_TXAK(1);

					// dummy read
					rd_byte = I2C0->D;

					Tx = 0;
				}
				else
				{ // 1
					byte_to_send--;
					I2C0->D = reg_addr;
				}

			}
			else
			{
				// STOP
				I2C0->C1 &= ~I2C_C1_MST(1);
			}
		}
		else	// Last byte transmitted
		{
			if (i2c_access_mode == Single_read) // 2
			{
				byte_to_send = 2;
				switch_Rx = 1;
				// Re-start
				I2C0->C1 |= I2C_C1_RSTA(1);
				byte_to_send--;
				I2C0->D = I2C_D_DATA(dev_addr << 1 | 1);
			}
			i = i;
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
	i2c_access_mode = Single_read;

	dev_addr = dev_addr_i;
	reg_addr = reg_addr_i;

	rd_done = 0;
	Tx = 1;
	byte_to_send = 2;

	// Transmit mode select, Transmit
	I2C0->C1 |= I2C_C1_TX(1);

	// Master mode, start signal
	I2C0->C1 |= I2C_C1_MST(1);

	byte_to_send--;
	// Send slave address
	I2C0->D = I2C_D_DATA(dev_addr << 1 | 0);

	while (!rd_done);

	*byte = rd_byte;
}


