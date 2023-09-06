/*
 * rtc.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Admin
 */

#include "rtc.h"

void rtc_init(uint32_t time) {
	// select external 32.768kHz OSC
	SIM->SOPT1 &= ~SIM_SOPT1_OSC32KSEL_MASK;
	SIM->SOPT1 |= SIM_SOPT1_OSC32KSEL(2);
	// enable clock gate
	SIM->SCGC6 |= SIM_SCGC6_RTC(1);

	// Enable OSC, without this line, the TSR does not increase
	RTC->CR |= RTC_CR_OSCE(1);

	// Disable counter, Originally enabled, need disabled to clear SR[TIF] by update TSR
	RTC->SR &= ~RTC_SR_TCE_MASK;
	// Set the current time
	RTC->TSR = time;

	// Enable counter
	RTC->SR |= RTC_SR_TCE(1);

}

uint32_t rtc_read() {
	return RTC->TSR;
}
