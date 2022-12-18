#ifndef UART_H_
#define UART_H_

#include "MK64F12.h"

#ifndef UART_CLK
#define UART_CLK 20000000
#endif

#define UART_BAUD_RATE 115200

void UART0_RX_TX_DriverIRQHandler(void);

void uart_init();
void uart_print(char* str);

#endif /* UART_H_ */
