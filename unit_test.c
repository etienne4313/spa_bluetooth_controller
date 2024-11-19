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

#ifdef __UNIT_TEST__

void flip_io(void)
{
	int x;
	for(x=0; x<5; x++){
		PUMP1_FAST_ON();
		_delay_ms(200);
		PUMP1_FAST_OFF();
		_delay_ms(200);
	}

	for(x=0; x<5; x++){
		PUMP1_SLOW_ON();
		_delay_ms(200);
		PUMP1_SLOW_OFF();
		_delay_ms(200);
	}

	for(x=0; x<5; x++){
		PUMP2_FAST_ON();
		_delay_ms(200);
		PUMP2_FAST_OFF();
		_delay_ms(200);
	}

	for(x=0; x<5; x++){
		PUMP2_SLOW_ON();
		_delay_ms(200);
		PUMP2_SLOW_OFF();
		_delay_ms(200);
	}

	for(x=0; x<5; x++){
		BLOWER_ON();
		_delay_ms(200);
		BLOWER_OFF();
		_delay_ms(200);
	}

	for(x=0; x<5; x++){
		CIRCULATION_ON();
		_delay_ms(200);
		CIRCULATION_OFF();
		_delay_ms(200);
	}

	for(x=0; x<5; x++){
		MAIN_ON_PULSE_UP();
		_delay_ms(200);
		MAIN_ON_PULSE_DOWN();
		_delay_ms(200);
	}

	for(x=0; x<5; x++){
		MAIN_OFF_PULSE_UP();
		_delay_ms(200);
		MAIN_OFF_PULSE_DOWN();
		_delay_ms(200);
	}

	for(x=0; x<5; x++){
		HEATER_ON();
		_delay_ms(200);
		HEATER_OFF();
		_delay_ms(200);
	}
}

void unit_test(void)
{
	unsigned char i;

	/* Disable WD for UT */
	wdt_reset();
	watchdog_enable(WATCHDOG_OFF);
again:
	USART_Flush();
	close_all_io();
	FORCE_PRINT( "Going into debug mode, Enter TC, x to continue to main loop\n");
	i = getchar();
	switch(i){
		case 'v':
			flip_io();
			break;
		case 'x':
			watchdog_enable(WATCHDOG_2S); /* Set the WD back to original setting before leaving UT */
			wdt_reset();
			return;
		default:
			FORCE_PRINT( "Error\n");
			break;
	}
	goto again;
}

#endif /* __UNIT_TEST__ */

