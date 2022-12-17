#ifndef ACCEL_H_
#define ACCEL_H_

#include "i2c.h"

#define I2C_ADDR 0x1D
#define WHO_AM_I_VAL 0xC7

#define STATUS 0x00
#define OUT_X_MSB 0x01
#define OUT_X_LSB 0x02
#define OUT_Y_MSB 0x03
#define OUT_Y_LSB 0x04
#define OUT_Z_MSB 0x05
#define OUT_Z_LSB 0x06

#define SYSMOD 0x0B
#define WHO_AM_I 0x0D

#define CTRL_REG1 0x2A
#define CTRL_REG2 0x2B
#define CTRL_REG3 0x2C
#define CTRL_REG4 0x2D
#define CTRL_REG5 0x2E

typedef struct accel_s
{
	int x;
	int y;
	int z;
} accel;

void accel_init(void);
void get_accel(accel* acc);

#endif /* ACCEL_H_ */
