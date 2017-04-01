/*
 * GLCD_DRIVER.cpp
 *
 * Created: 8/2/2016 10:11:44 AM
 * Author : ASUS
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>


#include "MIFARE_GLCD.h"


int main(void)
{
	Mifare_GLCD_init();

    while (1) 
    {
		
		Mifare_GLCD_Idle("11/08/16","03:56:17");
		_delay_ms(2000);
		
		Mifare_GLCD_Invalid_ID("0A3F9D");
		_delay_ms(5000);
		
		Mifare_GLCD_Access_Granted("0A3F9D");
		_delay_ms(5000);
		
		Mifare_GLCD_Invalid_Time("0A3F9D");
		_delay_ms(5000);
		
    }
}

