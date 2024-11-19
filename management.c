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

static void user_cmd(void)
{
	unsigned char d;

	if(!USART_data_available())
		return;
	d = getchar();
	switch (d) {

		case 'q':
			PRINT("MAIN ON\n");
			main_relay_on();
			break;
		case 'a':
			PRINT("MAIN OFF\n");
			main_relay_off();
			CIRCULATION_OFF();
			HEATER_OFF();
			break;

		case 'w':
			PRINT("HEATER ON\n");
			CIRCULATION_ON();
			HEATER_ON();
			break;

		case 's':
			PRINT("HEATER OFF\n");
			CIRCULATION_OFF();
			HEATER_OFF();
			break;

		case 'y':
			PRINT("BLOWER ON\n");
			BLOWER_ON();
			break;
		case 'h':
			PRINT("BLOWER OFF\n");
			BLOWER_OFF();
			break;

		case 'r':
			PRINT("PUMP2 SLOW ON\n");
			PUMP2_FAST_OFF();
			wdt_reset();
			_delay_ms(1000);
			PUMP2_SLOW_ON();
			break;

		case 'f':
			PRINT("PUMP2 SLOW OFF\n");
			PUMP2_FAST_OFF();
			PUMP2_SLOW_OFF();
			break;

		case 't':
			PRINT("PUMP2 HIGH ON\n");
			PUMP2_SLOW_OFF();
			wdt_reset();
			_delay_ms(1000);
			PUMP2_FAST_ON();
			break;

		case 'g':
			PRINT("PUMP2 HIGH OFF\n");
			PUMP2_FAST_OFF();
			PUMP2_SLOW_OFF();
			break;

		case 'x':
			PRINT("KILL\n");
			DIE(-1);
			break;
		default:
			break;
	}
}

void management_thread(void *p)
{
	OS_CPU_SR cpu_sr;
	int loop = 0;

	//	watchdog_enable(WATCHDOG_250MS);
	wdt_reset();

	while(1){
		/* Feed the WD */
		wdt_reset();

		/* Run the User CLI */
		user_cmd();

		if(!(loop%20)){
			OS_ENTER_CRITICAL();
			OS_EXIT_CRITICAL();
		}

		loop++;

		OSTimeDlyHMSM(0,0,0,100);
	}
}

