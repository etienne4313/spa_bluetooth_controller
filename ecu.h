/*
 * Copyright 2024, Etienne Martineau etienne4313@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __ECU_H_
#define __ECU_H_

//#define __UNIT_TEST__ /* Basic IO test */

#include <ucos_ii.h>

/******************************************************************************/
/* RTOS */
/******************************************************************************/
void management_thread(void *p);

/******************************************************************************/
/* IO */
/******************************************************************************/
void main_relay_on(void);
void main_relay_off(void);
void io_init(void);
void close_all_io(void);
#ifdef __UNIT_TEST__
void unit_test(void);
#endif

#define PUMP1_FAST_ON() 		do {PORTD |= _BV(DDD2) ; } while(0)
#define PUMP1_FAST_OFF() 		do {PORTD &= ~_BV(DDD2) ; } while(0)

#define PUMP1_SLOW_ON() 		do {PORTD |= _BV(DDD3) ; } while(0)
#define PUMP1_SLOW_OFF() 		do {PORTD &= ~_BV(DDD3) ; } while(0)

#define PUMP2_FAST_ON() 		do {PORTD |= _BV(DDD4) ; } while(0)
#define PUMP2_FAST_OFF() 		do {PORTD &= ~_BV(DDD4) ; } while(0)

#define PUMP2_SLOW_ON() 		do {PORTD |= _BV(DDD5) ; } while(0)
#define PUMP2_SLOW_OFF() 		do {PORTD &= ~_BV(DDD5) ; } while(0)

#define BLOWER_ON() 			do {PORTD |= _BV(DDD6) ; } while(0)
#define BLOWER_OFF() 			do {PORTD &= ~_BV(DDD6) ; } while(0)

#define CIRCULATION_ON() 		do {PORTD |= _BV(DDD7) ; } while(0)
#define CIRCULATION_OFF() 		do {PORTD &= ~_BV(DDD7) ; } while(0)

#define MAIN_ON_PULSE_UP() 		do {PORTB |= _BV(DDB0) ; } while(0)
#define MAIN_ON_PULSE_DOWN() 	do {PORTB &= ~_BV(DDB0) ; } while(0)

#define MAIN_OFF_PULSE_UP() 	do {PORTB |= _BV(DDB1) ; } while(0)
#define MAIN_OFF_PULSE_DOWN() 	do {PORTB &= ~_BV(DDB1) ; } while(0)

#define HEATER_ON() 			do {PORTB |= _BV(DDB2) ; } while(0)
#define HEATER_OFF() 			do {PORTB &= ~_BV(DDB2) ; } while(0)

#endif

