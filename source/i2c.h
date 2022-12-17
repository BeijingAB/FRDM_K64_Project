#ifndef I2C_H_
#define I2C_H_

#include "MK64F12.h"



void I2C0_DriverIRQHandler(void);

void i2c_init();
void i2c_single_byte_read(char dev_addr_i, char reg_addr_i, char* byte);
void i2c_single_byte_write(char dev_addr_i, char reg_addr_i, char byte);

#endif /* I2C_H_ */
