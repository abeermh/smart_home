/*
 * main.c
 *
 *  Created on: Oct 22, 2020
 *      Author: Abeer
 */
#include"lib/STD_Types.h"
#include "lib/BIT_MATH.h"
#include "lib/AVR32_REG.h"
#include<util/delay.h>
#include"DIO/DIO_Interface.h"
#include "LCD/Lcd_Interface.h"
#include "KEYPAD/KPAD_Interface.h"
#include "ADC/ADC_Interface.h"
#include "UART/UART_Intereface.h"
/*
u8 Array_U8Comp(u8 * copy,u8* original){
	for (u8 i = 0; original[i]!='\0'; i++) {
		if(copy[i]!=original[i]){
			return 0;
		}
	}
	return 1;
}

void DcMotorPlay() {
	DIO_VidSetPinValue(PortA, DIO_Pin1,High);
	_delay_ms(1000);
	DIO_VidSetPinValue(PortA, DIO_Pin1,Low);

}
void LightSys(){

	DIO_VidSetPinValue(PortA, DIO_Pin2,High);
	_delay_ms(1000);
		DIO_VidSetPinValue(PortA, DIO_Pin2,Low);
}

void LM_Init(void)
{
	DIO_VidSetPinDirection(PortA,DIO_Pin0,Input);
	ADC_VidInit();
	ADC_VidSelectChannel(0);
	ADC_VidEnable();
}

void LM_VidRead(u16 * Copy_U16Read)
{
	u16 Temp,analog;
 	 Temp=ADC_VidRead();
 	analog=((Temp)*2500UL)/1024;
 	*Copy_U16Read=analog/10;
}

void smarthome() {
	u8 username[] = "1478";
	u8 password[] = "1111";
	u16 temp=1;
	u8 userinset[8]={0}, passinset[8]={0};
	u8 keyval,i=0,j=0,wrongpass=0;
	LCD_VidInit();
	KPAD_VidInit();
 	LM_Init();
 	DIO_VidSetPinDirection(PortA, DIO_Pin1, Output);	//for motor
	DIO_VidSetPinDirection(PortA, DIO_Pin2, Output);	//for light system
	DIO_VidSetPinDirection(PortA,DIO_Pin3,Output);		//for buzzar

//	***********************************************************************************

	LCD_VIDPrintString("UserName:");
	while (1) {
		if(wrongpass<3){
			keyval = KPAD_U8GetKey();
			if (keyval != KEY_NOT_PRESSED) {
				if(i<6){
					if (keyval == '=') {
						i=8;
						LCD_VidGoToXY(1,0);
						LCD_VIDPrintString("Password:");

					} else {
						LCD_VidSendData(keyval);
						userinset[i] = keyval;
						i++;
					}

				}else if(j<6){

					if (keyval == '=') {
						j=8;
					} else {
						LCD_VidSendData('*');
						passinset[j] =keyval;
						j++;
					}
				}
				else{

					if(Array_U8Comp(userinset,username)&&Array_U8Comp(passinset,password)){
						LCD_VidClearDisplay();
						LCD_VIDPrintString("welcome ");
						_delay_ms(100);
						LCD_VidClearDisplay();
						LCD_VIDPrintString("press number: ");
						while(1){
							keyval=KPAD_U8GetKey();
							LCD_VidClearDisplay();
							if (keyval != KEY_NOT_PRESSED) {

								LCD_VidClearDisplay();
								switch(keyval)
								{
								case '1'://door lock
									LCD_VIDPrintString("Door Opening");
									DcMotorPlay();break;
								case '2'://light system
									LCD_VIDPrintString("Light System");
									LightSys();break;
								case '3'://temperature
									LM_VidRead(&temp);
									LCD_VIDPrintString("temperature");
 									LCD_VidPrintIntNumber(temp);
 									LCD_VidSendData('C');
									_delay_ms(1000);
									break;
								case 0:break;

								}
								_delay_ms(1000);
							}}
					}else
					{
						LCD_VidClearDisplay();
						LCD_VIDPrintString("try again ");
						wrongpass++;
						LCD_VidClearDisplay();
						LCD_VIDPrintString("UserName:");
						i=0,j=0;
					}
				}



			}

		}
		else{LCD_VidClearDisplay();
		//buzzar alarm

		DIO_VidSetPinValue(PortA,DIO_Pin3,High);
		}}}
int main() {
	smarthome();
	return 0;
}

