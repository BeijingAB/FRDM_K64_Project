/*
 * rtc.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Admin
 */

#ifndef RTC_H_
#define RTC_H_

#include "MK64F12.h"

void rtc_init(uint32_t time);
uint32_t rtc_read();



#endif /* RTC_H_ */
