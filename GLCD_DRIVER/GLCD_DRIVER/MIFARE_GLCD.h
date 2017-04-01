/*
 * MIFARE_GLCD.h
 *
 * Created: 8/11/2016 3:45:18 PM
 *  Author: ASUS
 */ 


#ifndef MIFARE_GLCD_H_
#define MIFARE_GLCD_H_

#include "SIAM_GLCD.h"

char ID_show[12];
char Temp_and_RH[] = "14.5'C 68.5%RH";
 
void Mifare_GLCD_init();
void Mifare_GLCD_Idle(char date[], char time[], float Temp, float RH);
void Mifare_GLCD_Access_Granted(char ID[]);
void Mifare_GLCD_Invalid_ID(char ID[]);
void Mifare_GLCD_Invalid_Time(char ID[]);
void Mifare_GLCD_Data_Transfer(char event_ID[], int length_str);
void Mifare_GLCD_Mem_full();
void Mifare_GLCD_CREATOR();

void Mifare_GLCD_init()
{
	ID_show[0] = 'I';
	ID_show[1] = 'D';
	ID_show[2] = ':';
	ID_show[3] = ' ';
	GLCD_initialize();
	GLCD_ClearScreen();	
	WritePattern( ra_logo , 8, 128, false);
	_delay_ms(2000);
	
}

void Mifare_GLCD_Access_Granted(char ID[])
{
	GLCD_ClearScreen();
	WriteString("www.2ra-bd.com",14,0,23, false, false);
	Write2XString("ACCESS",6,2,22, false, false);
	Write2XString("GRANTED",7,4,12, false, false);
	WriteString("~~~~~~~~~~~~~~",14,6,12, false, false);
	for (char x=0;x<8;x++)
	{
		ID_show[4+x]=ID[x];
	}
	WriteString(ID_show,12,7,25, false, false);
}
void Mifare_GLCD_Invalid_ID(char ID[])
{
	GLCD_ClearScreen();
	WriteString("www.2ra-bd.com",14,0,23, false, false);
	
	GLCD_goto(1,8);
	for (char x = 0;x<108;x++)
	{
		GLCD_Send_Data(0b11000000);
	}
	
	Write2XString(" ACCESS ",8,2,8, true, false);
	Write2XString(" DENIED ",8,4,8, true, false);
	GLCD_goto(6,8);
	for (char x = 8;x<116;x++)
	{
		GLCD_Send_Data(0xFF);
	}
	WriteString("INVALID ID",10,6,29, true, false);
	GLCD_goto(7,8);
	for (char x = 0;x<108;x++)
	{
		GLCD_Send_Data(0xFF);
	}
	for (char x=0;x<8;x++)
	{
		ID_show[4+x]=ID[x];
	}
	WriteString(ID_show,12,7,25, true, false);
}
void Mifare_GLCD_Invalid_Time(char ID[])
{
	GLCD_ClearScreen();
	WriteString("www.2ra-bd.com",14,0,23, false, false);
	
	GLCD_goto(1,8);
	for (char x = 0;x<108;x++)
	{
		GLCD_Send_Data(0b11000000);
	}
	
	Write2XString(" ACCESS ",8,2,8, true, false);
	Write2XString(" DENIED ",8,4,8, true, false);
	GLCD_goto(6,8);
	for (char x = 8;x<116;x++)
	{
		GLCD_Send_Data(0xFF);
	}
	WriteString("INVALID TIME",12,6,22, true, false);
	GLCD_goto(7,8);
	for (char x = 8;x<116;x++)
	{
		GLCD_Send_Data(0xFF);
	}
	for (char x=0;x<8;x++)
	{
		ID_show[4+x]=ID[x];
	}
	WriteString(ID_show,12,7,25, true, false);
}
void Mifare_GLCD_Idle(char date[], char time[], float Temp, float RH)
{
	int Tempo_calculation;
	

	Tempo_calculation = (int)((((int)Temp)%100)/10);		// Only doshomangsho
	Temp_and_RH[0] = Tempo_calculation +  0x30;
	Tempo_calculation = (int)(((int)Temp)%10);
	Temp_and_RH[1] = Tempo_calculation +  0x30;	
	Tempo_calculation = (int)(((int)(Temp*10))%10);
	Temp_and_RH[3] = Tempo_calculation +  0x30;
	

	Tempo_calculation = (int)((((int)RH)%100)/10);		// Only doshomangsho
	Temp_and_RH[7] = Tempo_calculation +  0x30;
	Tempo_calculation = (int)(((int)RH)%10);
	Temp_and_RH[8] = Tempo_calculation +  0x30;	
	Tempo_calculation = (int)(((int)(RH*10))%10);
	Temp_and_RH[10] = Tempo_calculation +  0x30;
	
	GLCD_ClearScreen();
	WriteString("www.2ra-bd.com",14,0,23, false, false);
	WriteString(date,8,2,44, false, false);
	Write2XString(time,8,4,30, false, false);
	WriteString(Temp_and_RH,14,7,25, false, false);
}

void Mifare_GLCD_Mem_full()
{
	GLCD_ClearScreen();
	WriteString("www.2ra-bd.com",14,0,23, false, false);
	
	GLCD_goto(2,8);
	for (char x = 0;x<114;x++)
	{
		GLCD_Send_Data(0b11000000);
	}
	
	Write2XString(" MEMORY ",8,3,8, true, false);
	Write2XString("  FULL  ",8,5,8, true, false);
	
	GLCD_goto(3,122);
	GLCD_Send_Data(0x00);
	GLCD_Send_Data(0x00);
	GLCD_goto(4,122);
	GLCD_Send_Data(0x00);
	GLCD_Send_Data(0x00);
	
	_delay_ms(200);
	
	GLCD_ClearScreen();
	WriteString("www.2ra-bd.com",14,0,23, false, false);
	Write2XString(" MEMORY ",8,3,8, false, false);
	Write2XString("  FULL  ",8,5,8, false, false);

	_delay_ms(200);
	
	GLCD_ClearScreen();
	WriteString("www.2ra-bd.com",14,0,23, false, false);
	
	GLCD_goto(2,8);
	for (char x = 0;x<114;x++)
	{
		GLCD_Send_Data(0b11000000);
	}
	
	Write2XString(" MEMORY ",8,3,8, true, false);
	Write2XString("  FULL  ",8,5,8, true, false);
	
	GLCD_goto(3,122);
	GLCD_Send_Data(0x00);
	GLCD_Send_Data(0x00);
	GLCD_goto(4,122);
	GLCD_Send_Data(0x00);
	GLCD_Send_Data(0x00);
	
	_delay_ms(200);
	
	GLCD_ClearScreen();
	WriteString("www.2ra-bd.com",14,0,23, false, false);
	Write2XString(" MEMORY ",8,3,8, false, false);
	Write2XString("  FULL  ",8,5,8, false, false);

	_delay_ms(200);
	
	GLCD_ClearScreen();
	WriteString("www.2ra-bd.com",14,0,23, false, false);
	
	GLCD_goto(2,8);
	for (char x = 0;x<114;x++)
	{
		GLCD_Send_Data(0b11000000);
	}
	
	Write2XString(" MEMORY ",8,3,8, true, false);
	Write2XString("  FULL  ",8,5,8, true, false);
	
	GLCD_goto(3,122);
	GLCD_Send_Data(0x00);
	GLCD_Send_Data(0x00);
	GLCD_goto(4,122);
	GLCD_Send_Data(0x00);
	GLCD_Send_Data(0x00);
	
	_delay_ms(200);
	
	GLCD_ClearScreen();
	WriteString("www.2ra-bd.com",14,0,23, false, false);
	Write2XString(" MEMORY ",8,3,8, false, false);
	Write2XString("  FULL  ",8,5,8, false, false);

	_delay_ms(200);
	
	GLCD_ClearScreen();
	WriteString("www.2ra-bd.com",14,0,23, false, false);
	
	GLCD_goto(2,8);
	for (char x = 0;x<114;x++)
	{
		GLCD_Send_Data(0b11000000);
	}
	
	Write2XString(" MEMORY ",8,3,8, true, false);
	Write2XString("  FULL  ",8,5,8, true, false);
	
	GLCD_goto(3,122);
	GLCD_Send_Data(0x00);
	GLCD_Send_Data(0x00);
	GLCD_goto(4,122);
	GLCD_Send_Data(0x00);
	GLCD_Send_Data(0x00);
	
	_delay_ms(1000);
	
}

void Mifare_GLCD_Data_Transfer(char event_ID[], int length_str)
{
	GLCD_ClearScreen();
	WriteString("www.2ra-bd.com",14,0,23, false, false);
	Write2XString("DATA",4,2,35, false, false);
	Write2XString("EXCHANGE",8,4,7, false, false);
	
	for (char x=0;x<128;x++)
	{
	GLCD_goto(6,x);
	GLCD_Send_Data(0xFF);
	GLCD_goto(7,(127-x));
	GLCD_Send_Data(0xFF);	
	_delay_ms(15);
	}
	int pos = 64 - (length_str/2)*6;
	WriteString(event_ID,length_str,7,pos, true, false);
	_delay_ms(500);	
}

void Mifare_GLCD_CREATOR()
{
	WritePattern( foot_print , 8, 128, false);
	_delay_ms(2000);
}
#endif /* MIFARE_GLCD_H_ */