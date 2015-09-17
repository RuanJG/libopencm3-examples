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

#include "uart.h"
int usart1_id ;
int usart2_id ;
int usart3_id ;

void led_setup(void);
void heart_led_triggle();

#define DEBUG_APP 1
#define log(X...) if( DEBUG_APP ) printf(X...);



static void clock_setup(void)
{
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
}
void do_echo(int id)
{
	uint8_t buff[1024];
	int len,res;

	len = do_read_usart(id , buff, 1024);
	if( len > 0 ){
		do_write_usart(id,buff,len);
		heart_led_triggle();
	}
}
void do_usart1_func()
{
	do_echo(usart1_id);
}
void do_usart2_func()
{
	do_echo(usart2_id);
}
void do_usart3_func()
{
	do_echo(usart3_id);
}

void setup()
{
	clock_setup();
	led_setup();
	usart1_id = usart1_setup(115200,8, USART_STOPBITS_1, USART_PARITY_NONE, USART_MODE_TX_RX);
	usart2_id = usart2_setup(115200,8, USART_STOPBITS_1, USART_PARITY_NONE, USART_MODE_TX_RX);
	usart3_id = usart3_setup(115200,8, USART_STOPBITS_1, USART_PARITY_NONE, USART_MODE_TX_RX);
}
void loop()
{
	do_usart_buffer_check(usart1_id, 1);
	do_usart1_func();
	do_usart_buffer_check(usart2_id, 1);
	do_usart2_func();
	do_usart_buffer_check(usart3_id, 1);
	do_usart3_func();


}
int main(void)
{

	setup();
	while(1){
		loop();
		//__asm__("nop");
	}
	/* Wait forever and do nothing. 
	while (1)
		__asm__("nop");
	*/
	return 0;
}

