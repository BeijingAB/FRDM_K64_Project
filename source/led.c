#include "led.h"

void led_init()
{
// Red
	// Enable clock for port B
	SIM->SCGC5 |= SIM_SCGC5_PORTB(1);

	// Port B as gpio
	PORTB->PCR[22] |= PORT_PCR_MUX(1);

	// Set 1 to turn off led
	GPIOB->PSOR |= GPIO_PSOR_PTSO(1 << 22);

	// Set as output
	GPIOB->PDDR |= GPIO_PDDR_PDD(1 << 22);

// Green
	SIM->SCGC5 |= SIM_SCGC5_PORTE(1);

	PORTE->PCR[26] |= PORT_PCR_MUX(1);


	GPIOE->PSOR |= GPIO_PSOR_PTSO(1 << 26);
	GPIOE->PDDR |= GPIO_PDDR_PDD(1 << 26);

// Blue
	SIM->SCGC5 |= SIM_SCGC5_PORTB(1);

	PORTB->PCR[21] |= PORT_PCR_MUX(1);


	GPIOB->PSOR |= GPIO_PSOR_PTSO(1 << 21);
	GPIOB->PDDR |= GPIO_PDDR_PDD(1 << 21);
}

void red_led_on()
{

	// Clear to turn on led
	GPIOB->PCOR |= GPIO_PCOR_PTCO(1 << 22);
}

void green_led_on()
{

	GPIOE->PCOR |= GPIO_PCOR_PTCO(1 << 26);
}

void blue_led_on()
{

	GPIOB->PCOR |= GPIO_PCOR_PTCO(1 << 21);
}

void red_led_off()
{
	// Set 1 to turn off led
	GPIOB->PSOR |= GPIO_PSOR_PTSO(1 << 22);
}

void green_led_off()
{
	GPIOE->PSOR |= GPIO_PSOR_PTSO(1 << 26);
}

void blue_led_off()
{
	GPIOB->PSOR |= GPIO_PSOR_PTSO(1 << 21);
}
