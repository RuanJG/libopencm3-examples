/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>


static void clock_setup(void)
{
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
}
#include "uart.c"
#include "led.c"


void setup()
{
	clock_setup();
	led_setup();
	usart1_setup();
}
void loop()
{
}
int main(void)
{

	setup();
	while(1){
		loop();
		__asm__("nop");
	}
	/* Wait forever and do nothing. 
	while (1)
		__asm__("nop");
	*/
	return 0;
}

