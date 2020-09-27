/*
 * Navigation_new.c
 *
 * Created: 2/13/2018 1:48:50 PM
 * Author : Hamza
 * 
 */ 


/*
 * 
 *
 * 
 * 
 * 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "u8g.h"
#include "templets.h"
u8g_t u8g;
extern const uint8_t ArabicLetters[252];
// defining the variables and giving it the suitable initialization 
int		 Min_temp					,
		 Max_temp					,
		 Min_heating_time			,			//	variable represents the value of the min heating time
		 Max_heating_time			,			//	variable represents the value of the max heating time
		 Cooling_time				,		// variables to store the temperatures in the EEPROM
		 OFF_time					,
		 Alarm_time					,
		 Logging_time				;			// variable holds the period frequency of storing the data in the sd card
uint8_t	current_selector		=1	,			//	variable passed to the draw function to select item on the screen based on the action done by the encoder switch
		current_screen			=1	,			//	variable represents the current displayed screen
		x							,			//	de-bouncing variable 
		check						,			//	variable to mark the repeated display of a screen
		sign_3_min					,			//	variable to mark the sign of the min number in screen 3
		sign_3_max					,			//	variable to mark the sign of the max number in screen 3
		sign_4_min					,			//	variable to mark the sign of the min number in screen 4
		sign_4_max					;			//	variable to mark the sign of the max number in screen 4

char number=48,ip=48;
unsigned char Lang ='E';


//making the function calling of the templates screen functions
 #define screen_1			operation_screen					('E',0,"About Screen")
 #define screen_2			draw_two_item_selector				('E',0,current_selector,"Language","English","Arabic")
 #define screen_3			TwoValueMenu						(Lang,0,current_selector,Min_temp,sign_3_min,Max_temp,sign_3_max,"TEMP","MIN","MAX")
 //#define screen_3			TwoValueMenu						(Lang,0,current_selector,Min_temp,sign_3_min,Max_temp,sign_3_max,"���� �������","����","����")
 #define screen_4			TwoValueMenu						(Lang,0,current_selector,Min_heating_time,sign_4_min,Max_heating_time,sign_4_max,"Heating Time","MIN","MAX")
 //#define screen_4			TwoValueMenu						(Lang,0,current_selector,Min_heating_time,sign_4_min,Max_heating_time,sign_4_max,"���� ��� ��������","���","����")
 #define screen_5			OneValueMenu						(Lang,0,Cooling_time,"Cooling Time")
 //#define screen_5			OneValueMenu						(Lang,0,Cooling_time,"��� �������")
 #define screen_6			OneValueMenu						(Lang,0,OFF_time,"OFF Time")
 //#define screen_6			OneValueMenu						(Lang,0,OFF_time,"��� �������")
#define screen_7			OneValueMenu						(Lang,0,Alarm_time,"Alarm Time")
 //#define screen_7			OneValueMenu						(Lang,0,Alarm_time,"��� �������")
 #define screen_8			draw_two_item_selector				(Lang,0,current_selector,"Operation Voltage","220","380")
 //#define screen_8			draw_two_item_selector				(Lang,0,current_selector,"���� �������","����","����")
 #define screen_9			draw_two_item_selector				(Lang,0,current_selector,"Cooling Type","cooling","Freezing")
 //#define screen_9			draw_two_item_selector				(Lang,0,current_selector,"��� �������","�����","�����")
#define screen_10			draw_two_item_selector				(Lang,0,current_selector,"Heaters","Yes","NO")
// #define screen_10			draw_two_item_selector				(Lang,0,current_selector,"������","���","��")
#define screen_11			draw_two_item_selector				(Lang,0,current_selector,"ThermoDesk","Yes","NO")
// #define screen_11			draw_two_item_selector				(Lang,0,current_selector,"���� ��������","���","��")
 #define screen_12			draw_two_item_selector				(Lang,0,current_selector,"Compressor Temp","Yes","NO")
// #define screen_12			draw_two_item_selector				(Lang,0,current_selector,"���� �����������","���","��")
#define screen_13			draw_two_item_selector				(Lang,0,current_selector,"Oil Pressure","Yes","NO")
// #define screen_13			draw_two_item_selector				(Lang,0,current_selector,"��� �����","���","��")
#define screen_14			draw_two_item_selector				(Lang,0,current_selector,"High Pressure","Yes","NO")
 //#define screen_14			draw_two_item_selector				(Lang,0,current_selector,"��� ����","���","��")
 #define screen_15			draw_two_item_selector				(Lang,0,current_selector,"Condenser Contactor","Yes","NO")
 //#define screen_15			draw_two_item_selector				(Lang,0,current_selector,"����� �����������","���","��")
 #define screen_16			draw_two_item_selector				(Lang,0,current_selector,"Door Fan","Yes","NO")
 //#define screen_16			draw_two_item_selector				(Lang,0,current_selector,"����� �����","���","��")
 #define screen_17			draw_two_item_selector				(Lang,0,current_selector,"Limit Switch","Yes","NO")
 //#define screen_17			draw_two_item_selector				(Lang,0,current_selector,"����� �����","���","��")
 #define screen_18			draw_two_item_selector				('E',0,current_selector,"Phase Correction","Yes","NO")
 //#define screen_18_ar		draw_two_item_selector				(Lang,0,current_selector,"Phase Correction","Yes","NO")
 #define screen_19			draw_two_item_selector				(Lang,0,current_selector,"Data Logging","Yes","NO")
 //#define screen_19			draw_two_item_selector				(Lang,0,current_selector,"����� ��������","���","��")
 #define screen_20			OneValueMenu			(Lang,0,Logging_time,"logging time")
 //#define screen_20			OneValueMenu						(Lang,0,Logging_time,"���� �������")
#define screen_21			draw_four_item_selector				(Lang,0,current_selector,"Comm Type","NO","Eath","Wifi","GSM")
// #define screen_21			draw_four_item_selector				(Lang,0,current_selector,"����� �������","��","��","������","��")
 #define screen_22			IP_Address							(current_selector,ip)
 #define screen_23			mobile_Number						(current_selector,number)
 #define screen_24			operation_screen					(Lang,0,"Running Screen")
 //#define screen_24			operation_screen					(Lang,0,"���� �����")
 #define screen_25			draw_two_item_selector				(Lang,1,current_selector,"Maintence","Basic","Advanced")
 //#define screen_25			draw_two_item_selector				(Lang,1,current_selector,"�����","������","�����")
 #define screen_26			draw_three_item_selector			(Lang,1,current_selector,"Basic","Temp","Cooling_T","Heating_T")
 //#define screen_26			draw_three_item_selector			(Lang,1,current_selector,"������","�����","�����","������")
 #define screen_27			draw_four_item_selector				(Lang,1,current_selector,"Advanced","F.C","F.Def","I\O","Setup")
 //#define screen_27			draw_four_item_selector				(Lang,1,current_selector,"�����","�","�","�","���")
 #define screen_28			operation_screen					(Lang,1,"Force Cooling")
 #define screen_29			operation_screen					(Lang,1,"Force Def")
 #define screen_30			operation_screen					(Lang,1,"View I\O")



 //the first interrupt (INT0) represents the rotating effect of the encoder switch 
 ISR(INT0_vect )
 {
 	switch (current_screen)
 	{
 		case 2 :	
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 						current_selector = 2;
 						screen_2;
 				}
 				
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 						current_selector = 1;
 						screen_2;						
 				}
 				break;
 		
 		case 3 :
 				if (current_selector==1)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						current_selector = 3;
 						screen_3;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						screen_3;	
 					}
 					
 				}
 				else if (current_selector == 2)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{	
 						if (sign_3_min)
 						{
 							Min_temp--;
 							if (Min_temp==0){sign_3_min=0;}
 							screen_3;	
 						}
 						else 
 						{
 							Min_temp++;
 							screen_3;	
 						}
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{	
 						if (sign_3_min)
 						{
 							Min_temp++;
 							screen_3;
 						}
 						else
 						{
							if (Min_temp == 0)
							{
								Min_temp ++;
								sign_3_min=1;
							}
							else 
							{
 								Min_temp--;
 								if (Min_temp==0){sign_3_min=1;}
							 }
 							screen_3;	
 						}
 						
 					}
 					
 				}
 				else if (current_selector==3)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{ 
 						screen_3;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						current_selector =1;
 						screen_3;
 					}
 					
 				}
 				else if (current_selector == 4)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						if(sign_3_max)
 						{
 							Max_temp--;
 							if (Max_temp==0){sign_3_max=0;}
 							screen_3;
 						}
 						else
 						{
 							Max_temp++;
 							screen_3;
 						}
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						if(sign_3_max)
 						{
 							Max_temp++;
 							screen_3;
 						}
 						else
 						{	
							 if (Max_temp == 0)
							 {	
								  Max_temp =1;
								  sign_3_max =1;
							 }
							 else 
							 {	 
 								Max_temp--;
 								if (Max_temp==0){sign_3_max=1;}
								 }
 							screen_3;
 						}
 					}
 				}
 				break;
 		case 4 :	
 
 				if (current_selector==1)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						current_selector = 3;
 						screen_4;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						screen_4;
 					}
 				}
 				else if (current_selector == 2)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						Min_heating_time++;
 						screen_4;	
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						Min_heating_time--;
						 if (Min_heating_time <= 0){Min_heating_time = 0;}
 						screen_4;
 					}
 					
 				}
 				else if (current_selector==3)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						screen_4;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						current_selector =1;
 						screen_4;
 					}
 					
 				}
 				else if (current_selector == 4)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						Max_heating_time++;
 						screen_4;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						Max_heating_time--;
						  if (Max_heating_time <= 0){Max_heating_time = 0;}
 						screen_4;
 					}
 				}
 				break;				
 		case 5 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					Cooling_time++;
 					screen_5;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					Cooling_time--;
					  if (Cooling_time < 0){Cooling_time = 0;}
 					screen_5;
 				}
 				break;
 		case 6 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					OFF_time++;
 					screen_6;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					OFF_time--;
					  if (OFF_time <= 0){OFF_time = 0;}
 					screen_6;
 				}
 				break;	
 				
 		case 7 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					Alarm_time++;
 					screen_7;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{	
 					Alarm_time--;
					  if (Alarm_time <= 0){Alarm_time = 0;}
 					screen_7;
 				}
 				break;		
 		case 8 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 	
 					current_selector =2;
 					screen_8;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=1;
 					screen_8;
 				}
 				break;
 		case 9 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=2;
 					screen_9;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=1;
 					screen_9;
 				}
 				break;
 		case 10 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=2;
 					screen_10;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=1;
 					screen_10;	
 				}
 				break;
 		case 11 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=2;
 					screen_11;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=1;
 					screen_11;
 				}
 				break;
 		case 12 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=2;
 					screen_12;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=1;
 					screen_12;
 				}
 				break;
 		case 13 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=2;
 					screen_13;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=1;
 					screen_13;
 				}
 				break;	
 		case 14 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=2;
 					screen_14;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=1;
 					screen_14;
 				}
 				break;	
 		case 15 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=2;
 					screen_15;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=1;
 					screen_15;
 				}
 				break;
 		case 16 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=2;
 					screen_16;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=1;
 					screen_16;
 				}
 				break;	
 		case 17 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=2;
 					screen_17;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=1;
 					screen_17;
 				}
 				break;
 		case 18 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=2;
 					screen_18;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=1;
 					screen_18;
 				}
 				break;
 		case 19 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=2;
 					screen_19;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector=1;
 					screen_19;
 				}
 				break;
 		case 20 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					Logging_time++;
 					screen_20;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					Logging_time--;
					 if (Logging_time <0){Logging_time=0;}
 					screen_20;
 				}
 				break;
 		case 21 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector++;
 					if (current_selector >4){current_selector = 4;}
 					screen_21;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector--;
 					if (current_selector <1){current_selector = 1;}
 					screen_21;
 				}
 				break;
 		case 22 :
 				if (current_selector == 0)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip++;
 						if (ip >57){ip =57;}
 						screen_22;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip--;
 						if (ip <48){ip = 48;}
 						screen_22;
 					}
 				}
 				else if (current_selector == 1)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip++;
 						if (ip >57){ip =57;}
 						screen_22;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip--;
 						if (ip <48){ip = 48;}
 						screen_22;
 					}
 				}
 				else if (current_selector == 2)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip++;
 						if (ip >57){ip =57;}
 						screen_22;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip--;
 						if (ip <48){ip = 48;}
 						screen_22;
 					}
 				}
 				else if (current_selector == 3)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip++;
 						if (ip >57){ip =57;}
 						screen_22;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip--;
 						if (ip <48){ip = 48;}
 						screen_22;
 					}
 				}
 				else if (current_selector == 4)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip++;
 						if (ip >57){ip =57;}
 						screen_22;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip--;
 						if (ip <48){ip = 48;}
 						screen_22;
 					}
 				}
 				else if (current_selector == 5)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip++;
 						if (ip >57){ip =57;}
 						screen_22;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip--;
 						if (ip <48){ip = 48;}
 						screen_22;
 					}
 				}
 				else if (current_selector == 6)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip++;
 						if (ip >57){ip =57;}
 						screen_22;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip--;
 						if (ip <48){ip = 48;}
 						screen_22;
 					}
 				}
 				else if (current_selector == 7)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip++;
 						if (ip >57){ip =57;}
 						screen_22;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip--;
 						if (ip <48){ip = 48;}
 						screen_22;
 					}
 				}
 				else if (current_selector == 8)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip++;
 						if (ip >57){ip =57;}
 						screen_22;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip--;
 						if (ip <48){ip = 48;}
 						screen_22;
 					}
 				}
 				else if (current_selector == 9)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip++;
 						if (ip >57){ip =57;}
 						screen_22;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip--;
 						if (ip <48){ip = 48;}
 						screen_22;
 					}
 				}
 				else if (current_selector == 10)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip++;
 						if (ip >57){ip =57;}
 						screen_22;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip--;
 						if (ip <48){ip = 48;}
 						screen_22;
 					}
 				}
 				else if (current_selector == 11)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip++;
 						if (ip >57){ip =57;}
 						screen_22;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						ip--;
 						if (ip <48){ip = 48;}
 						screen_22;
 					}
 				}
 				break;
 		case 23 :
 				if (current_selector == 0)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number++;
 						if (number >57){number =57;}
 						screen_23;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number--;
 						if (number <48){number = 48;}
 						screen_23;
 					}	
 				}
 				else if (current_selector == 1)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number++;
 						if (number >57){number =57;}
 						screen_23;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number--;
 						if (number <48){number = 48;}
 						screen_23;
 					}
 				}				
 				else if (current_selector == 2)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number++;
 						if (number >57){number =57;}
 						screen_23;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number--;
 						if (number <48){number = 48;}
 						screen_23;
 					}
 				}
 				else if (current_selector == 3)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number++;
 						if (number >57){number =57;}
 						screen_23;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number--;
 						if (number <48){number = 48;}
 						screen_23;
 					}
 				}
 				else if (current_selector == 4)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number++;
 						if (number >57){number =57;}
 						screen_23;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number--;
 						if (number <48){number = 48;}
 						screen_23;
 					}
 				}
 				else if (current_selector == 5)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number++;
 						if (number >57){number =57;}
 						screen_23;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number--;
 						if (number <48){number = 48;}
 						screen_23;
 					}
 				}
 				else if (current_selector == 6)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number++;
 						if (number >57){number =57;}
 						screen_23;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number--;
 						if (number <48){number = 48;}
 						screen_23;
 					}
 				}
 				else if (current_selector == 7)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number++;
 						if (number >57){number =57;}
 						screen_23;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number--;
 						if (number <48){number = 48;}
 						screen_23;
 					}
 				}
 				else if (current_selector == 8)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number++;
 						if (number >57){number =57;}
 						screen_23;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number--;
 						if (number <48){number = 48;}
 						screen_23;
 					}
 				}
 				else if (current_selector == 9)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number++;
 						if (number >57){number =57;}
 						screen_23;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number--;
 						if (number <48){number = 48;}
 						screen_23;
 					}
 				}
 				else if (current_selector == 10)
 				{
 					if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number++;
 						if (number >57){number =57;}
 						screen_23;
 					}
 					else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 					{
 						number--;
 						if (number <48){number = 48;}
 						screen_23;
 					}
 				}
 				break;
 		case 24 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					Alarm_time++;
 					screen_7;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					Alarm_time--;
 					screen_7;
 					
 				}
 				break;
 		case 25 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector++;
 					if (current_selector >3){current_selector = 3;}
 					screen_25;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector--;
 					if (current_selector <1){current_selector = 1;}
 					screen_25;	
 				}
 				break;
 		case 26 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector++;
 					if (current_selector>4){current_selector = 4;}
 					screen_26;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector--;
 					if (current_selector<1){current_selector = 1;}
 					screen_26;
 					
 				}
 				break;
 		case 27 :
 				if(( PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector++;
 					if (current_selector >5){current_selector=5;}
 					screen_27;
 				}
 				else if ((~PIND & (1 << PIND4)) && ((~PIND & (1 << PIND2))))
 				{
 					current_selector--;
 					if (current_selector<1){current_selector = 1;}
 					screen_27;
 					
 				}
 				break;
 				
 	}
 }
			
 // the second interrupt (INT1) represents the Bush Button effect of the encoder switch that makes the selection of an option on the current screen
 


 ISR(INT1_vect )
 {	
    x =(PIND &(1<<PIND3));
    _delay_ms(20);
    if (((PIND&(1<<PIND3))) == x)
    {
 	switch (current_screen)
 	{
 	case 1 :
 			current_screen =2;
 			current_selector = 1;
 			screen_2;
 			break;
 	case 2:
 		if (current_selector == 1)
 			{
 				current_screen = 3;
 				current_selector=1;
 				screen_3;
 			}
 			break;
 	case 3 :
 		if (current_selector == 1)
 			{
 				current_screen = 3;
 				current_selector=2;
 				screen_3;
 			}
 		else if (current_selector == 2)
 			{
 				current_screen = 3;
 				current_selector = 3;
 				screen_3;
 			}
 		else if (current_selector == 3)
 			{				
 				current_screen =3;
 				current_selector=4;
 				screen_3;
 			}
 		else if (current_selector == 4)
 			{	
 				if (check == 0)
 				{
 					current_screen = 4;
 					current_selector =1;
 					screen_4;	
 				}
 				else 
 				{
 					current_screen = 26;
 					current_selector =1;
 					screen_26;
 					check = 0;
 				}
 
 			}
 			break;
 	case 4 :
 		if (current_selector == 1)
 			{
 				current_screen =4;
 				current_selector=2;
 				screen_4;
 			}
 		else if (current_selector == 2)
 			{
 				current_screen=4;
 				current_selector=3;
 				screen_4;
 			}
 		else if (current_selector == 3)
 			{
 				
 				current_screen =4 ;
 				current_selector=4;
 				screen_4;
 			}
 		else if (current_selector == 4)
 			{
 				if (check == 0)
 				{
 					current_screen = 5;
 					current_selector =1;
 					screen_5;
 				}
 				else
 				{
 					current_screen = 26;
 					current_selector =1;
 					screen_26;
 					check = 1;
 				}
 			}
 			break;
 	case 5 :
 			if (check == 0)
 			{
 			current_screen = 6;
 			current_selector = 1;
 			screen_6;
 			}
 			else
 			{
 				current_screen = 26;
 				current_selector =1;
 				screen_26;
 				check = 0;
 			}
 			break;
 	case 6 :
 			current_screen=7;
 			current_selector = 1;
 			screen_6;
 			break;
 	case 7 :
 			current_screen = 8;
 			current_selector = 1;
 			screen_8;
 			break;
 	case 8 :
 			current_screen = 9;
 			current_selector = 1;
 			screen_9;
 			break;
 	case 9 :
 			current_screen = 10;
 			current_selector = 1;
 			screen_10;
 			break;
 	case 10 :
 			current_screen = 11;
 			current_selector =1 ;
 			screen_11;
 			break;
 	case 11 :
 			current_screen = 12;
 			current_selector =1 ;
 			screen_12;
 			break;
 	case 12 :
 			current_screen = 13;
 			current_selector=1;
 			screen_13;
 			break;
 	case 13 :
 			current_screen = 14;
 			current_selector=1;
 			screen_14;
 			break;
 	case 14 :
 			current_screen =15;
 			current_selector=1;
 			screen_15;
 			break;
 	case 15 :
 			current_screen = 16;
 			current_selector=1;
 			screen_16;
 			break;
 	case 16 : 
 			current_screen = 17;
 			current_selector=1;
 			screen_17;
 			break;
 	case 17 :
 			current_screen=18;
 			current_selector=1;
 			screen_18;
 			break;
 	case 18 :
 			current_screen = 19;
 			current_selector=1;
 			screen_19;
 			break;
 	case 19 :
 			if (current_selector ==1)
 			{	
 				current_screen = 20;
 				current_selector =1;
 				screen_20;
 			}
 			else if (current_selector == 2)
 			{
 				current_screen = 21;
 				current_selector = 1;
 				screen_21;
 			}
 			
 			break;
 	case 20 :
 			current_screen = 21;
 			current_selector =1;
 			screen_21;
 			break;
 	case 21 :
 			if (current_selector == 1)
 			{
 				current_screen=24;
 				current_selector=1;
 				screen_24;
 			}
 			else if (current_selector == 2)
 			{
 				current_screen=22;
 				current_selector=0;
 				screen_22;
 			}
 			else if (current_selector == 3)
 			{
 				current_screen = 24;
 				current_selector = 0;
 				screen_24;
 			}
 			else if ( current_selector == 4)
 			{
 				current_screen=23;
 				current_selector=0;
 				screen_23;
 			}
 			break;
 	case 22 :
 			if (current_selector == 0)
 			{
 				current_screen=22;
 				current_selector =1;
 				screen_22;
 			}
 			else if (current_selector == 1)
 			{
 				current_screen=22;
 				current_selector =2;
 				screen_22;
 			}
 			else if (current_selector == 2)
 			{
 				current_screen=22;
 				current_selector =3;
 				screen_22;
 			}
 			else if (current_selector == 3)
 			{
 				current_screen=22;
 				current_selector =4;
 				screen_22;
 			}
 			else if (current_selector == 4)
 			{
 				current_screen=22;
 				current_selector =5;
 				screen_22;
 			}
 			else if (current_selector == 5)
 			{
 				current_screen=22;
 				current_selector =6;
 				screen_22;
 			}
 			else if (current_selector == 6)
 			{
 				current_screen=22;
 				current_selector =7;
 				screen_22;
 			}
 			else if (current_selector == 7)
 			{
 				current_screen=22;
 				current_selector =8;
 				screen_22;
 			}
 			else if (current_selector == 8)
 			{
 				current_screen=22;
 				current_selector =9;
 				screen_22;
 			}
 			else if (current_selector == 9)
 			{
 				current_screen=22;
 				current_selector =10;
 				screen_22;
 			}
 			else if (current_selector == 10)
 			{
 				current_screen=22;
 				current_selector =11;
 				screen_22;
 			
 			}
 			else if (current_selector == 11)
 			{
 				current_selector=12;
 				current_screen=22;
 				screen_22;
 			}
 			else if (current_selector == 12)
 			{
 				current_selector=1;
 				current_screen=24;
 				screen_24;
 			}			
 			break;
 
 	case 23 :
 			if (current_selector == 0)
 			{
 				current_screen=23;
 				current_selector =1;
 				screen_23;
 			}
 			else if (current_selector == 1)
 			{
 				current_screen=23;
 				current_selector =2;
 				screen_23;				
 			}
 			else if (current_selector == 2)
 			{
 				current_screen=23;
 				current_selector =3;
 				screen_23;
 			}
 			else if (current_selector == 3)
 			{
 				current_screen=23;
 				current_selector =4;
 				screen_23;
 			}
 			else if (current_selector == 4)
 			{
 				current_screen=23;
 				current_selector =5;
 				screen_23;
 			}
 			else if (current_selector == 5)
 			{
 				current_screen=23;
 				current_selector =6;
 				screen_23;
 			}
 			else if (current_selector == 6)
 			{
 				current_screen=23;
 				current_selector =7;
 				screen_23;
 			}
 			else if (current_selector == 7)
 			{
 				current_screen=23;
 				current_selector =8;
 				screen_23;
 			}
 			else if (current_selector == 8)
 			{
 				current_screen=23;
 				current_selector =9;
 				screen_23;
 			}
 			else if (current_selector == 9)
 			{
 				current_screen=23;
 				current_selector =10;
 				screen_23;
 			}
 			else if (current_selector == 10)
 			{
				current_screen=23;
				current_selector=11;
 				screen_23;
 				
 			}
 			else if (current_selector == 11)
 			{
 			current_screen=24;
 			current_selector = 1;
 			screen_24;
 			}	
 
 			break;
 	case 24 :
 			current_screen=25;
 			current_selector=1;
 			screen_25;
 			break;
 	case 25 :
 			if (current_selector == 1)
 			{
 				current_screen=26;
 				current_selector=1;
 				screen_26;
 			}
 			else if (current_selector == 2)
 			{
 				current_screen = 27; 
 				current_selector=1;	
 				screen_27; 
 			}
 			else if (current_selector == 3)
 			{
 				current_screen =24;
 				current_selector=1;
 				screen_24;
 			}
 			break;
 	case 26 :
 			if (current_selector == 1)
 			{
 				current_screen=3;
 				current_selector=1;
 				screen_3;
 				check =1;//varibable change here
 			}
 			else if (current_selector == 2)
 			{
 				current_screen = 5;
 				current_selector =1;
 				screen_5;
 				check =1;//variable change here
 			}
 			else if (current_selector == 3)
 			{
 				current_screen = 4;
 				current_selector=1;
 				screen_4;
 				check =1;//variable change here
 			}
 			else if (current_selector == 4)
 			{
 				current_screen=25;
 				current_selector=1;
 				screen_25;
 			}
 			break;
 	case 27 :
 			if (current_selector == 1)
 			{
 				current_screen=28;
 				current_selector=1;
 				screen_28;	
 			}
 			else if (current_selector == 2)
 			{
 				current_screen = 29;
 				current_selector =1;
 				screen_29;
 			}
 			else if (current_selector == 3)
 			{
 				screen_30;
 				current_screen=30;
 				current_selector=1;
 			}
 			else if (current_selector == 4)
 			{
 				current_screen=2;
 				current_selector=1;
 				screen_2;
 				check = 0;// variable change here
 			}
 			else if ( current_selector == 5)
 			{
 				current_screen = 25;
 				current_selector=1;
 				screen_25;
 			}
 			break;
 	case 28 :
 			current_screen=27;
 			current_selector=1;
 			screen_27;
 			break;
 	case 29 :
 			current_screen =27;
 			current_selector=1;
 			screen_27;
 			break;
 	case 30 :
 			current_screen = 27;
 			current_selector=1;
 			screen_27;
 			break;
 	}
    
    }
    while ((~PIND & (1<<PIND3)));
 }



int main(void)
{
	
	u8g_InitSPI(&u8g, &u8g_dev_st7920_128x64_hw_spi, PN(1, 5), PN(1, 3), PN(1, 4), U8G_PIN_NONE, U8G_PIN_NONE);
	
	if ( u8g_GetMode(&u8g) == U8G_MODE_R3G3B2 )
	u8g_SetColorIndex(&u8g, 255);     /* white */
	else if ( u8g_GetMode(&u8g) == U8G_MODE_GRAY2BIT )
	u8g_SetColorIndex(&u8g, 3);         /* max intensity */
	else if ( u8g_GetMode(&u8g) == U8G_MODE_BW )
	u8g_SetColorIndex(&u8g, 1);         /* pixel on */
    
    /* set PD2,PD3 and PD4 as input */
    DDRD &=~ (1 << PIND2);
    DDRD &=~ (1 << PIND3);
    DDRD &=~ (1 << PIND4);
    PORTD |= (1 << PIND3)|(1 << PIND2)|(1 << PIND4);   /* PD2 and PD3 pull-up enabled   */

    
    EIMSK |= (1<<INT0)|(1<<INT1);		/* enable INT0 and INT1 */
    EICRA |= (0<<ISC00)|(1<<ISC01)|(0<<ISC10)|(1<<ISC11); /* INT0 - falling edge, INT1 - falling edge */

    /* enable interrupts */
    sei();
    
	screen_1;
    current_screen=1;
	//char x=0;
	char ArabicStr[] = "���";
	uint8_t x=25,y=25,width;
	
    while (1) 
    {
    }
}

