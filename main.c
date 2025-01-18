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

int debug = 0;

/******************************************************************************/
/* RTOS */
/******************************************************************************/
static OS_STK management_thread_stack[STACK_SIZE];

void osdie(int err, int line)
{
	OS_CPU_SR cpu_sr;

	OS_ENTER_CRITICAL();
#if _BUG_328_NANO_
	/* 
	 * Clone 328 Nano bootloader doesn't clear the WD when coming up and keeps reloading evey 16msec
	 * Here we are branching back to RESET vector directly.
	 * 	- Punch the WD ASAP to avoid going in a bootloop at the bootloaded level
	 * 	- Add timeout in the WD to make sure we can survived thru the bootload all the way back to main()
	 * 	- Stack and memory will get cleaned up OK
	 * 	- I/O won't comeback to default reset value but we are doing clone_all_io() in all cases.
	 * 	- We must stop all the timers manually here.
	 */
	wdt_reset();
	watchdog_enable(WATCHDOG_2S);
	fprintf(stderr, "DIE %d : %d\n", err, line);
	{
		/* timer1_disable */
		unsigned char t;
		t = TCCR1B;
		t &= ~(1<<CS02   | 1<<CS01  | 1<<CS00);
		TCCR1B = t;
	}
	__asm__ __volatile__ (  "jmp __ctors_end \n\t" );
#endif
	fprintf(stderr, "DIE %d : %d\n", err, line); 
	close_all_io();
	/* Wait for WD to reset */
	while(1){};
	OS_EXIT_CRITICAL();
}

int main(void)
{
	OS_CPU_SR cpu_sr = 0;

	/* Don't let any IRQ come */
	OS_ENTER_CRITICAL();

	watchdog_enable(WATCHDOG_2S);
	wdt_reset();

	lib_init();

	io_init();

#ifdef __UNIT_TEST__
	unit_test();
#endif

	PRINT("ENTER\n");

	OSInit();

	/* Low priority Management thread: GUI, gaz pump, watchdog, engine state */
	OSTaskCreate(management_thread, NULL, &management_thread_stack[STK_HEAD(STACK_SIZE)], 3);

	/* IRQ are enabled when the first thread is started */
	OSStart();

	/* Never reach */
	DIE(-1);
	OS_EXIT_CRITICAL();
	return 0;
}

