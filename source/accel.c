/*
 * accel.c
 *
 *  Created on: Dec 16, 2022
 *      Author: liangj
 */


#include "accel.h"

#define WAIT for(int i = 0; i < 1000; i++);

void accel_init()
{
	i2c_init();

	char whoami = 0;
	char ctrl_reg1 = 1;
	i2c_single_byte_read(I2C_ADDR, WHO_AM_I, &whoami);

	if (whoami == WHO_AM_I_VAL)
	{
		printf("find accel\r\n");
	}
	else
	{
		printf("accel not found\r\n");
	}

	i2c_single_byte_write(I2C_ADDR, CTRL_REG1, ctrl_reg1);
}


void get_accel(accel* acc)
{
	signed char x_msb, x_lsb, y_msb, y_lsb, z_msb, z_lsb; // fix signed issue by adding signed
	i2c_single_byte_read(I2C_ADDR, OUT_X_MSB, &x_msb);
	i2c_single_byte_read(I2C_ADDR, OUT_X_LSB, &x_lsb);

	i2c_single_byte_read(I2C_ADDR, OUT_Y_MSB, &y_msb);
	i2c_single_byte_read(I2C_ADDR, OUT_Y_LSB, &y_lsb);

	i2c_single_byte_read(I2C_ADDR, OUT_Z_MSB, &z_msb);
	i2c_single_byte_read(I2C_ADDR, OUT_Z_LSB, &z_lsb);

//	acc->x = x_msb << 8 | x_lsb;
//	acc->y = y_msb << 8 | y_lsb;
//	acc->z = z_msb << 8 | z_lsb;

	acc->x = x_msb;
	acc->y = y_msb;
	acc->z = z_msb;

}
