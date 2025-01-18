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
#include <ecu.h>

/******************************************************************************/
/* SPA controller mapping */
/******************************************************************************/
/*
 * Heater
 * OUT1: Pump1
 * 	Relay K1 = Fast, Relay K2 = slow
 * OUT2: Pump2
 * 	Relay K3 = Fast, Relay K4 = slow
 * OUT3: NC
 * 	Relay K5
 * OUT4: ?? Small Red
 * 	Relay K6
 * OUT5: Blower
 * 	Relay K7
 * OUT6: Circulation Pump
 * 	Relay K8
 * Heater:
 * 	Some 24V
 * Main Relay ON PULSE
 * Main Relay OFF PULSE
 */


/******************************************************************************/
/* IO MAPPING 328 */
/******************************************************************************/
/* 
 *
 *								PORTB
 * 					0,  1,  2,  3,  4,  5,  6,  7
 *  Digital PIN:	8,  9,  10, 11, 12, 13  NC  NC XTAL
 *  ISP PIN:					XX, XX, XX
 *  MAIN ON:		#
 *  MAIN OFF:			#
 *  Heater:					#
 *
 *								PORTC
 * 					0,  1,  2,  3,  4,  5,  6,  7
 *  Analog  PIN:	0,  1,  2,  3,  4,  5,  NC  NC RESET
 *     OR
 *  Digital PIN:   A0, A1, A2, A3, A4, A5,
 *
 *								PORTD
 * 					0,  1,  2,  3,  4,  5,  6,  7
 *  Digital PIN:	0,  1,  2,  3,  4,  5,  6,  7
 *  UART		    XX XX
 *  Relay K1:				#
 *  Relay K2:					#
 *  Relay K3:						#
 *  Relay K4:							#
 *  Relay K7:								#
 *  Relay K8:									#
 */

#define CFG_OUTPUT() do { \
	DDRD |= _BV(DDD2); \
	DDRD |= _BV(DDD3); \
	DDRD |= _BV(DDD4); \
	DDRD |= _BV(DDD5); \
	DDRD |= _BV(DDD6); \
	DDRD |= _BV(DDD7); \
	DDRB |= _BV(DDB0); \
	DDRB |= _BV(DDB1); \
	DDRB |= _BV(DDB2); \
} while(0)

void main_relay_on(void)
{
	MAIN_ON_PULSE_UP();
	_delay_ms(500);
	MAIN_ON_PULSE_DOWN();
	PRINT("Main relay ON\n");
}

void main_relay_off(void)
{
	MAIN_OFF_PULSE_UP();
	_delay_ms(500);
	MAIN_OFF_PULSE_DOWN();
	PRINT("Main relay OFF\n");
}

void close_all_io(void)
{
	HEATER_OFF();
	CIRCULATION_OFF();
	BLOWER_OFF();
	PUMP2_SLOW_OFF();
	PUMP2_FAST_OFF();
	PUMP1_SLOW_OFF();
	PUMP1_FAST_OFF();
	main_relay_off();
	//	analogDisable();
}

void io_init(void)
{
	CFG_OUTPUT();
	//	CFG_INPUT();
	close_all_io();
	//	analogEnable();
}

