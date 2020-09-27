/*
 * menu-templets.c
 *
 * Created: 2/5/2018 2:09:48 PM
 * Author : Hamza
 */ 
#include "templets.h"

const uint8_t ArabicLetters[258] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x01, 0x01, 0x01, 0x00, 0x00,  //0
	0x00, 0x00, 0x81, 0xFF, 0x00, 0x10,  //1
	0x00, 0x24, 0x81, 0xFF, 0x00, 0x00,  //2
	0x10, 0x28, 0x81, 0xFF, 0x00, 0x00,  //3
	0x00, 0x1F, 0x01, 0xFF, 0x00, 0x04,  //4
	0x00, 0x1F, 0x01, 0xFF, 0x00, 0x00,  //5
	0x20, 0x1F, 0x01, 0xFF, 0x00, 0x00,  //6
	0x00, 0x01, 0x01, 0x0F, 0x00, 0x00,  //7
	0x02, 0x01, 0x01, 0x0F, 0x00, 0x00,  //8
	0x00, 0x01, 0x01, 0x01, 0x02, 0x1C,  //9
	0x04, 0x01, 0x01, 0x01, 0x02, 0x1C,  //10
	0x00, 0x00, 0x15, 0xFF, 0x00, 0x00,  //11
	0x04, 0x0A, 0x15, 0xFF, 0x00, 0x00,  //12
	0x03, 0x05, 0x19, 0xFF, 0x00, 0x00,  //13
	0x13, 0x05, 0x19, 0xFF, 0x00, 0x00,  //14
	0x23, 0x25, 0x29, 0xFF, 0x00, 0x00,  //15
	0x2b, 0x25, 0x29, 0xFF, 0x00, 0x00,  //16
	0x00, 0x03, 0x02, 0xFF, 0x00, 0x00,  //17
	0x08, 0x07, 0x03, 0xFF, 0x00, 0x00,  //18
	0x08, 0x02, 0x85, 0xFF, 0x00, 0x00,  //19
	0x05, 0x02, 0x85, 0xFF, 0x00, 0x00,  //20
	0x1F, 0x0C, 0x03, 0xFF, 0x00, 0x00,  //21
	0x01, 0x01, 0x01, 0xFF, 0x00, 0x00,  //22
	0x00, 0x02, 0x05, 0xFD, 0x02, 0x00,  //23
	0x00, 0x10, 0x81, 0xFF, 0x00, 0x00,  //24
	0x06, 0x01, 0x05, 0xFF, 0x00, 0x00,  //25
	0x02, 0x05, 0x07, 0x01, 0x02, 0x1C,  //26
	0x00, 0x00, 0x81, 0xFF, 0x00, 0x24,  //27
	0x00, 0x0F, 0x01, 0x0F, 0x0A, 0x0F,  //28
	0x00, 0x0F, 0x01, 0x0F, 0x08, 0x0F,  //29
	0x04, 0x0F, 0x01, 0x0F, 0x08, 0x0F,  //30
	0x00, 0x00, 0x15, 0X9F, 0x90, 0x60,  //31
	0X04, 0X0A, 0X15, 0X9F, 0X90, 0X60,  //32
	0x03, 0x05, 0x19, 0x9F, 0x90, 0x60,  //33
	0x13, 0x05, 0x19, 0x9F, 0x90, 0x60,  //34
	0x03, 0x04, 0x03, 0x07, 0x04, 0x07,  //35
	0x13, 0x04, 0x03, 0x07, 0x04, 0x07,	 //36
	0x0D, 0x09, 0x5D, 0x7F, 0x00, 0x00,  //37
	0x01, 0x01, 0x01, 0x09, 0x09, 0x06,  //38
	0x00, 0x02, 0x05, 0x1D, 0x16, 0x10,	 //39
	0x0F, 0x09, 0x0F, 0x01, 0x00, 0x00,	 //40				
	0x00, 0x00, 0x07, 0x25, 0x24, 0x18   //41
										  
};

u8g_t u8g;

//Function should be re-written using signed numbers, so it returns the number and it's sign
void tostring( char str[],  int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

uint8_t calc_eng_width (char *word){
	uint8_t size=0,width=0;
	while(*word != '\0')
	{
		size = size +1;
		word++;
	}	
	width = size*5+(size-1)+4;
	return width;
}

//possible updates:when Arabic words are treated well (UTF-8) this function should be changed to match the English width one (NO "IF" OR CNT0, END OF STRING MARKED BY \0)
uint8_t calc_arb_width (char *ArabicStr){
	
	int8_t width=0,cnt0=0,cnt1=0,cnt2=0,cnt3=0,i=0,test1=0,test2=0;
	
	//Calculating number of letters
	while (ArabicStr[cnt0] != '\0')
	{
		cnt0++;
	}
	i=cnt0;
	//Finding how many letters from each group in the word
	while(cnt0 > 0)
	{
		if(*ArabicStr == 1)
		{
			cnt1++;
		}
		else if ((*ArabicStr >=8) && (*ArabicStr <=11))
		{
			cnt2++;
		}
		else if (*ArabicStr == 32)
		{
			cnt3++;
		}
		cnt0--;
		ArabicStr++;
	}
// 	if ((cnt1>0)||(cnt2 >0))
// 		test1=1;
	//Calculating the required width (number of pixels) required to draw the string and the outlining box (if required).
	width = i*7-(5*cnt1)-(2*cnt2)+(cnt3*3)+7;
	//width = i*7-(5*cnt1)-(2*cnt2)+(cnt3*3)-(test1)+7;	
	
	//Re-Check the last letter
	ArabicStr--;
	if ( ((*ArabicStr >=5) && (*ArabicStr <=7)) || ((*ArabicStr >=18) && (*ArabicStr <=19)) || (*ArabicStr == 24) || (*ArabicStr == 26) || (*ArabicStr == 28) )
	{
		width -= 3;
	}
	
	return width;	
	
}

// function to generalize the treatment of arabic and english words as a box with caculated size
void draw_english_str(uint8_t x,uint8_t y,char word [])
{
	u8g_DrawStr(&u8g, x+2, y+9,word);
}

//Shallow is not related find another word meaningful (Ex.With boarder)
void draw_english_boarder (uint8_t x,uint8_t y,char word [])
{
	uint8_t width = calc_eng_width(word);
	u8g_SetDefaultForegroundColor(&u8g);
	u8g_DrawFrame(&u8g,x,y,width,12);
	u8g_DrawStr(&u8g, x+2, y+9,word); //use the  draw_english_str function
}

//Full is not related find another word meaningful (Ex.Filled,Shadowed)
void draw_english_Shadowed(uint8_t x,uint8_t y,char word []){
	
	//Use calc_eng_width function
	uint8_t size =0,
	width=calc_eng_width(word);
	u8g_SetDefaultForegroundColor(&u8g);
	u8g_DrawBox(&u8g,x, y, width, 12);
	u8g_SetDefaultBackgroundColor(&u8g);
	u8g_DrawStr(&u8g, x+2, y+9,word);
	u8g_SetDefaultForegroundColor(&u8g);
}

//possible update: When Arabic is treated well no counters will be required ?
void draw_arabic_str (uint8_t x ,uint8_t y,char *ArabicStr)
{
	uint8_t width = calc_arb_width(ArabicStr);			//edit done here
	u8g_DrawArabicStr(x+width-3-8,y+3,ArabicStr);	
}

//Shallow is not related find another word meaningful (Ex.With boarder)
void draw_arabic_boarder (uint8_t x ,uint8_t y,char *ArabicStr)
{
	uint8_t width = calc_arb_width(ArabicStr);
	u8g_SetDefaultForegroundColor(&u8g);
	u8g_DrawFrame(&u8g,x,y,width,12);
	u8g_DrawArabicStr(x+(width-3-8),y+3,ArabicStr); //use draw_arabic_str function
}

//Full is not related find another word meaningful (Ex.Filled,Shadowed)
void draw_arabic_Shadowed (uint8_t x ,uint8_t y,char *ArabicStr)
{
	uint8_t width = calc_arb_width(ArabicStr);
	u8g_SetDefaultForegroundColor(&u8g);
	u8g_DrawBox(&u8g,x,y,width,12);
	u8g_SetDefaultBackgroundColor(&u8g);
	u8g_DrawArabicStr(x+(width-3-8),y+3,ArabicStr);
	u8g_SetDefaultForegroundColor(&u8g);
}

//L should be changed to global variable saved in EEPROM
//Arabic section is not fully done yet (ie.The Arabic words are considered to be constantly of 3 letters as test case)
//The Arabic words should be treated well first and the get Arabic width function is updated before finishing the Arabic section
//Possible update: Position of each option can be dynamically calculated based on the width of all of them and available width of screen
//Should consider using switch cases instead of if..elseif statements (check advantages and disadvantages before doing this)
//Consider changing the names of functions (Ex.TwoOptionsMenu)
//u8g_SetFont call should be globalized in the system setup rather than calling it multiple times
void draw_two_item_selector (unsigned char L,uint8_t B,uint8_t select,char Title [],char op_one [],char op_two [])
{
	uint8_t width_title=0,width_op_one=0,width_op_two=0;
	u8g_FirstPage(&u8g);
	do
	{
		u8g_SetFont(&u8g, u8g_font_6x10);
	if (L == 'E')
	{
		width_title=calc_eng_width(Title);
		width_op_one=calc_eng_width(op_one);
		width_op_two=calc_eng_width(op_two);
		
		u8g_DrawStr(&u8g, 63-(width_title/2), 14, Title);
		if (select == 1)
		{
			draw_english_Shadowed(31-(width_op_one/2),25,op_one);
			draw_english_boarder(93-(width_op_two/2),25,op_two);
			if (B)
			{
				draw_english_boarder(100,51,"Back");	
			}
		}
		else if (select == 2)
		{
			draw_english_boarder(31-(width_op_one/2),25,op_one);
			draw_english_Shadowed(93-(width_op_two/2),25,op_two);
			if (B)
			{
				draw_english_boarder(100,51,"Back");
			}	
		}
		else if (select == 3)
		{
			draw_english_boarder(31-(width_op_one/2),25,op_one);
			draw_english_boarder(93-(width_op_two/2),25,op_two);	
			if (B)
			{
				draw_english_Shadowed(100,51,"Back");
			}		
		}
	}
	else if (L == 'A')
	{
		
		width_title=calc_arb_width(Title);
		width_op_one=calc_arb_width(op_one);
		width_op_two=calc_arb_width(op_two);

		draw_arabic_str(63-(width_title/2),7,Title);
		
		if (select == 1)
		{
			draw_arabic_Shadowed(31-(width_op_one/2),25,op_one);
			draw_arabic_boarder(93-(width_op_two/2),25,op_two);	
			if(B)
			{
				u8g_DrawArabicStr(15,58,"����");
			}
		}
		else if (select == 2)
		{
			draw_arabic_boarder(31-(width_op_one/2),25,op_one);
			draw_arabic_Shadowed(93-(width_op_two/2),25,op_two);
			if(B)
			{
				u8g_DrawArabicStr(15,58,"����");
			}
		}
		else if (select == 3)
		{
			draw_arabic_boarder(31-(width_op_one/2),25,op_one);
			draw_arabic_boarder(93-(width_op_two/2),25,op_two);
			if(B)
			{
				draw_arabic_Shadowed(0,55,"����");
			}
		}	
	}
	} while ( u8g_NextPage(&u8g) );
	u8g_Delay(100);
}

void draw_three_item_selector (unsigned char L,uint8_t B,uint8_t select,char Title [],char op_one [],char op_two [],char op_three [])
{
	uint8_t width_title,width_op_one,width_op_two,width_op_three;
	u8g_FirstPage(&u8g);
	do
	{
		u8g_SetFont(&u8g, u8g_font_6x10);
		if (L == 'E')
		{
			width_title     =  calc_eng_width(Title);
			width_op_one    =  calc_eng_width(op_one);
			width_op_two    =  calc_eng_width(op_two);
			width_op_three  =  calc_eng_width(op_three);
			
			u8g_DrawStr(&u8g, 63-(width_title/2), 14, Title);
			if (select==1)
			{
				draw_english_Shadowed(20-(width_op_one/2),25,op_one);
				draw_english_boarder(63-(width_op_two/2),25,op_two);
				draw_english_boarder(105-(width_op_three/2),25,op_three);
				if(B)
				{
					draw_english_boarder(100,51,"Back");
				}
			}
			else if (select==2)
			{
				draw_english_boarder(20-(width_op_one/2),25,op_one);
				draw_english_Shadowed(63-(width_op_two/2),25,op_two);
				draw_english_boarder(105-(width_op_three/2),25,op_three);
				if(B)
				{
					draw_english_boarder(100,51,"Back");
				}
			}
			else if (select==3)
			{
				draw_english_boarder(20-(width_op_one/2),25,op_one);
				draw_english_boarder(63-(width_op_two/2),25,op_two);
				draw_english_Shadowed(105-(width_op_three/2),25,op_three);
				if(B)
				{
					draw_english_boarder(100,51,"Back");
				}
			}
			else if (select==4)
			{
				draw_english_boarder(20-(width_op_one/2),25,op_one);
				draw_english_boarder(63-(width_op_two/2),25,op_two);
				draw_english_boarder(105-(width_op_three/2),25,op_three);
				if(B)
				{
					draw_english_Shadowed(100,51,"Back");
				}
			}
		}
		
		else if (L == 'A')
		{
			
			width_title=calc_arb_width(Title);
			width_op_one=calc_arb_width(op_one);
			width_op_two=calc_arb_width(op_two);
			width_op_three=calc_arb_width(op_three);
			
			draw_arabic_str(63-(width_title/2),7,Title);
			if (select == 1)
			{
				draw_arabic_Shadowed(20-(width_op_one/2),25,op_one);
				draw_arabic_boarder(63-(width_op_two/2),25,op_two);
				draw_arabic_boarder(105-(width_op_three/2),25,op_three);
				if(B)
				{
					u8g_DrawArabicStr(15,58,"����");
				}
			}
			else if (select == 2)
			{
				draw_arabic_boarder(20-(width_op_one/2),25,op_one);
				draw_arabic_Shadowed(63-(width_op_two/2),25,op_two);
				draw_arabic_boarder(105-(width_op_three/2),25,op_three);
				if(B)
				{
					u8g_DrawArabicStr(15,58,"����");
				}
			}
			else if (select == 3)
			{
				draw_arabic_boarder(20-(width_op_one/2),25,op_one);
				draw_arabic_boarder(63-(width_op_two/2),25,op_two);
				draw_arabic_Shadowed(105-(width_op_three/2),25,op_three);
				if(B)
				{
					u8g_DrawArabicStr(15,58,"����");
				}
			}
			else if (select == 4)
			{
				draw_arabic_boarder(20-(width_op_one/2),25,op_one);
				draw_arabic_boarder(63-(width_op_two/2),25,op_two);
				draw_arabic_boarder(105-(width_op_three/2),25,op_three);
				if(B)
				{
					draw_arabic_Shadowed(0,55,"����");
				}
			}
		}
	} while ( u8g_NextPage(&u8g) );
	u8g_Delay(100);
}

void draw_four_item_selector (unsigned char L,uint8_t B,uint8_t select,char Title [],char op_one [],char op_two [],char op_three [],char op_four [])
{
	uint8_t width_title,width_op_one,width_op_two,width_op_three,width_op_four;		
	u8g_FirstPage(&u8g);
	do
	{
		u8g_SetFont(&u8g, u8g_font_6x10);
		if (L == 'E')
		{
			width_title     =  calc_eng_width(Title);
			width_op_one    =  calc_eng_width(op_one);
			width_op_two    =  calc_eng_width(op_two);
			width_op_three  =  calc_eng_width(op_three);
			width_op_four   =  calc_eng_width(op_four);
			
			u8g_DrawStr(&u8g, 63-(width_title/2), 14, Title);
			
			if(select == 1)
			{
				draw_english_Shadowed(15-(width_op_one/2),25,op_one);
				draw_english_boarder(47-(width_op_two/2),25,op_two);
				draw_english_boarder(79-(width_op_three/2),25,op_three);
				draw_english_boarder(111-(width_op_four/2),25,op_four);
				if(B)
				{
					draw_english_boarder(100,51,"Back");
				}
			}
			
			else if(select == 2)
			{	
				draw_english_boarder(15-(width_op_one/2),25,op_one);
				draw_english_Shadowed(47-(width_op_two/2),25,op_two);
				draw_english_boarder(79-(width_op_three/2),25,op_three);
				draw_english_boarder(111-(width_op_four/2),25,op_four);
				if(B)
				{
					draw_english_boarder(100,51,"Back");
				}
			}
			else if(select == 3)
			{	
				draw_english_boarder(15-(width_op_one/2),25,op_one);
				draw_english_boarder(47-(width_op_two/2),25,op_two);
				draw_english_Shadowed(79-(width_op_three/2),25,op_three);
				draw_english_boarder(111-(width_op_four/2),25,op_four);
				if(B)
				{
					draw_english_boarder(100,51,"Back");
				}
			}
			else if(select == 4)
			{	
				draw_english_boarder(15-(width_op_one/2),25,op_one);
				draw_english_boarder(47-(width_op_two/2),25,op_two);
				draw_english_boarder(79-(width_op_three/2),25,op_three);
				draw_english_Shadowed(111-(width_op_four/2),25,op_four);
				if(B)
				{
					draw_english_boarder(100,51,"Back");
				}
			}
			else if(select == 5)
			{	
				draw_english_boarder(15-(width_op_one/2),25,op_one);
				draw_english_boarder(47-(width_op_two/2),25,op_two);
				draw_english_boarder(79-(width_op_three/2),25,op_three);
				draw_english_boarder(111-(width_op_four/2),25,op_four);
				if(B)
				{
					draw_english_Shadowed(100,51,"Back");
				}
			}
			
		}
		
		else if (L == 'A')
		{
			
			width_title=calc_arb_width(Title);
			width_op_one=calc_arb_width(op_one);
			width_op_two=calc_arb_width(op_two);
			width_op_three=calc_arb_width(op_three);
			width_op_four=calc_arb_width(op_four);
			
			draw_arabic_str(63-(width_title/2),7,Title);
			if (select == 1)
			{
				draw_arabic_Shadowed(15-(width_op_one/2),25,op_one);
				draw_arabic_boarder(47-(width_op_two/2),25,op_two);
				draw_arabic_boarder(79-(width_op_three/2),25,op_three);
				draw_arabic_boarder(111-(width_op_four/2),25,op_four);
				if(B)
				{
					u8g_DrawArabicStr(15,58,"����");
				}
			}
			
			else if (select == 2)
			{
				draw_arabic_boarder(15-(width_op_one/2),25,op_one);
				draw_arabic_Shadowed(47-(width_op_two/2),25,op_two);
				draw_arabic_boarder(79-(width_op_three/2),25,op_three);
				draw_arabic_boarder(111-(width_op_four/2),25,op_four);
				if(B)
				{
					u8g_DrawArabicStr(15,58,"����");
				}
			}
			else if (select == 3)
			{
				draw_arabic_boarder(15-(width_op_one/2),25,op_one);
				draw_arabic_boarder(47-(width_op_two/2),25,op_two);
				draw_arabic_Shadowed(79-(width_op_three/2),25,op_three);
				draw_arabic_boarder(111-(width_op_four/2),25,op_four);
				if(B)
				{
					u8g_DrawArabicStr(15,58,"����");
				}
			}
			else if (select == 4)
			{
				draw_arabic_boarder(15-(width_op_one/2),25,op_one);
				draw_arabic_boarder(47-(width_op_two/2),25,op_two);
				draw_arabic_boarder(79-(width_op_three/2),25,op_three);
				draw_arabic_Shadowed(111-(width_op_four/2),25,op_four);
				if(B)
				{
					u8g_DrawArabicStr(15,58,"����");
				}
			}
			else if (select == 5)
			{
				draw_arabic_boarder(15-(width_op_one/2),25,op_one);
				draw_arabic_boarder(47-(width_op_two/2),25,op_two);
				draw_arabic_boarder(79-(width_op_three/2),25,op_three);
				draw_arabic_boarder(111-(width_op_four/2),25,op_four);
				if(B)
				{
					draw_arabic_Shadowed(0,55,"����");
				}
			}
		}
	} while ( u8g_NextPage(&u8g) );
	u8g_Delay(100);
}

//Consider changing the names of functions(Ex.OneValueMenu)
//Needs to be tested again
void OneValueMenu(unsigned char L,uint8_t B, uint8_t Current_Value,char Title [])
{
	uint8_t width_title;
		
	char Value[4];
	tostring(Value,Current_Value);
	
	u8g_FirstPage(&u8g);
	do
	{
		u8g_SetFont(&u8g, u8g_font_6x10);
		if (L == 'E')
		{	
			width_title=calc_eng_width(Title);	
			u8g_DrawStr(&u8g, 63-(width_title/2), 14, Title);
			if(B)
			{
				draw_english_boarder(100,51,"Back");
			}
		}
		else if (L == 'A')
		{
			width_title=calc_arb_width(Title);
			draw_arabic_str(63-(width_title/2),7,Title);	
			if(B)
			{	
				u8g_DrawArabicStr(15,58,"����");
			}
		}
		u8g_DrawBox(&u8g,63-11,36,23,7);
		u8g_SetDefaultBackgroundColor(&u8g);
		u8g_DrawStr(&u8g, (63-11),43,"<  >");
		if (Current_Value <= 0)
		{
			u8g_DrawStr(&u8g, (63-5),43,"0");	
		}
		else 
		{
			u8g_DrawStr(&u8g, (63-5),43,Value);	
		}
		u8g_SetDefaultForegroundColor(&u8g);	
	} while ( u8g_NextPage(&u8g) );
	u8g_Delay(100);

}
//Function should be re-written using signed numbers instead of getting number and it's sign
//Needs to be tested again
//void draw_two_item_editing_value(unsigned char L,uint8_t B,uint8_t select, int Current_Value_1, int Current_Value_2, char Title [],char op_one [],char op_two [])
void TwoValueMenu(unsigned char L,uint8_t B,uint8_t select, int Current_Value_1,uint8_t Value_1_sign, int Current_Value_2,uint8_t Value_2_sign, char Title [],char op_one [],char op_two [])
{	
	uint8_t width_title,width_op_one,width_op_two;
	char Value_1[4],Value_2 [4];
	tostring(Value_1,Current_Value_1);
	tostring(Value_2,Current_Value_2);
	u8g_FirstPage(&u8g);
	do
	{
		u8g_SetFont(&u8g, u8g_font_6x10);
		if (L == 'E')
		{
			width_title=calc_eng_width(Title);
			width_op_one=calc_eng_width(op_one);
			width_op_two=calc_eng_width(op_two);
			
			u8g_DrawStr(&u8g, 63-(width_title/2), 14, Title);
			if (select == 1)
			{	
				draw_english_Shadowed(31-(width_op_one/2),20,op_one);
				draw_english_str(93-(width_op_two/2),20,op_two);
				u8g_DrawStr(&u8g, (31-(width_op_one/2)-4),43,"<   >");
				u8g_DrawStr(&u8g, (93-(width_op_two/2)-4),43,"<   >");
				if (Current_Value_1 == 0)
				{
				u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,"0");		
				}
				else
				{
					if (Value_1_sign)
					{
						u8g_DrawStr(&u8g, (31-(width_op_one/2)+2),43,"-");
					}
				u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,Value_1);		
				}
				if (Current_Value_2 == 0)
				{
					u8g_DrawStr(&u8g, (93-(width_op_two/2)+8),43,"0");
				}
				else 
				{
					if(Value_2_sign)
					{
						u8g_DrawStr(&u8g, (93-(width_op_two/2)+2),43,"-");
					}
					u8g_DrawStr(&u8g, (93-(width_op_two/2)+8),43,Value_2);
				}		
			}
			else if (select == 2)
			{
				draw_english_str(31-(width_op_one/2),20,op_one);
				draw_english_str(93-(width_op_two/2),20,op_two);
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawBox(&u8g, (31-(width_op_one/2)-3),36,29,7);
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g, (31-(width_op_one/2)-4),43,"<   >");
				if (Current_Value_1 == 0)
				{
					u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,"0");	
				}
				else
				{
					if (Value_1_sign)
					{
						u8g_DrawStr(&u8g, (31-(width_op_one/2)+2),43,"-");
					}	
					u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,Value_1);					
				}
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawStr(&u8g, (93-(width_op_one/2)-4),43,"<   >");
				if (Current_Value_2 == 0)
				{
				u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,"0");
				}
				else 
				{
					if (Value_2_sign)
					{
						u8g_DrawStr(&u8g, (93-(width_op_one/2)+2),43,"-");
					}
					u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,Value_2);
				}

			}
			else if (select == 3 )
			{
				draw_english_str(31-(width_op_one/2),20,op_one);
				draw_english_Shadowed(93-(width_op_two/2),20,op_two);
				u8g_DrawStr(&u8g, (31-(width_op_one/2)-4),43,"<   >");
				u8g_DrawStr(&u8g, (93-(width_op_one/2)-4),43,"<   >");
				if (Current_Value_1 == 0)
				{
					u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,"0");
				}
				else 
				{
					if (Value_1_sign)
						{
							u8g_DrawStr(&u8g, (31-(width_op_one/2)+2),43,"-");
						}
					u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,Value_1);
				}
				if (Current_Value_2 == 0)
				{
					u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,"0");
				}
				else 
				{
					if (Value_2_sign)
					{
						u8g_DrawStr(&u8g, (93-(width_op_one/2)+2),43,"-");
					}
					u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,Value_2);
				}
			
			}
			else if (select == 4)
			{	
				draw_english_str(31-(width_op_one/2),20,op_one);
				draw_english_str(93-(width_op_two/2),20,op_two);
				u8g_DrawStr(&u8g, (31-(width_op_one/2)-4),43,"<   >");
				if (Current_Value_1 == 0)
				{
					u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,"0");
				}
				else 
				{
					if (Value_1_sign)
					{
						u8g_DrawStr(&u8g, (31-(width_op_one/2)+2),43,"-");
					}
					u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,Value_1);					
				}				
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawBox(&u8g,(93-(width_op_one/2)-3),36,28,7);
				u8g_DrawStr(&u8g, (93-(width_op_one/2)-4),43,"<   >");
				u8g_SetDefaultBackgroundColor(&u8g);
				if (Current_Value_2==0)
				{
					u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,"0");	
				}
				else 
				{
					if (Value_2_sign)
						{
							u8g_DrawStr(&u8g, (93-(width_op_one/2)+2),43,"-");
						}
					u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,Value_2);	
				}				
				u8g_SetDefaultForegroundColor(&u8g);	
			}
		if(B)
		{
			
			draw_english_boarder(100,51,"Back");
		}
	}
	else if (L == 'A')
	{	
		width_title=calc_arb_width(Title);
		width_op_one=calc_arb_width(op_one);
		width_op_two=calc_arb_width(op_two);
		
		draw_arabic_str(63-(width_title/2),7,Title);
		draw_arabic_str(31-(width_op_one/2),20,op_one);
		draw_arabic_str(93-(width_op_two/2),20,op_two);		
		if (select == 1)
		{
			draw_arabic_Shadowed(31-(width_op_one/2),20,op_one);
			draw_arabic_str(93-(width_op_two/2),20,op_two);
			u8g_DrawStr(&u8g, (31-(width_op_one/2)-4),43,"<   >");
			u8g_DrawStr(&u8g, (93-(width_op_one/2)-4),43,"<   >");
			if (Current_Value_1 == 0)
			{
				u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,"0");
			}
			else
			{
				if (Value_1_sign)
				{
					u8g_DrawStr(&u8g, (31-(width_op_one/2)+2),43,"-");
				}
				u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,Value_1);
			}
			if (Current_Value_2 == 0)
			{
				u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,"0");
			}
			else
			{
				if(Value_2_sign)
				{
					u8g_DrawStr(&u8g, (93-(width_op_one/2)+2),43,"-");
				}
				u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,Value_2);	
			}
		}
		else if (select == 2)
		{
			draw_arabic_str(31-(width_op_one/2),20,op_one);
			draw_arabic_str(93-(width_op_two/2),20,op_two);
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawBox(&u8g, (31-(width_op_one/2)-3),36,29,7);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, (31-(width_op_one/2)-4),43,"<   >");
			if (Current_Value_1 == 0)
			{
				u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,"0");	
			}
			else
			{
				if (Value_1_sign)
				{
					u8g_DrawStr(&u8g, (31-(width_op_one/2)+2),43,"-");
				}
				u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,Value_1);	
			}
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawStr(&u8g, (93-(width_op_one/2)-4),43,"<   >");
			if (Current_Value_2 == 0)
			{
				u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,"0");
			}
			else
			{
				if (Value_2_sign)
				{
					u8g_DrawStr(&u8g, (93-(width_op_one/2)+2),43,"-");
				}
				u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,Value_2);				
			}
		}
		else if (select == 3 )
		{
			draw_arabic_str(31-(width_op_one/2),20,op_one);
			draw_arabic_Shadowed(93-(width_op_two/2),20,op_two);
			u8g_DrawStr(&u8g, (31-(width_op_one/2)-4),43,"<   >");
			u8g_DrawStr(&u8g, (93-(width_op_one/2)-4),43,"<   >");
			if (Current_Value_1 == 0)
			{
				u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,"0");
			}
			else
			{
				if (Value_1_sign)
				{
					u8g_DrawStr(&u8g, (31-(width_op_one/2)+2),43,"-");
				}
				u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,Value_1);	
			}
			if (Current_Value_2 == 0)
			{
				u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,"0");
			}
			else 
			{
				if (Value_2_sign)
				{
					u8g_DrawStr(&u8g, (93-(width_op_one/2)+2),43,"-");
				}
				u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,Value_2);				
			}
		}
		else if (select == 4)
		{
			draw_arabic_str(31-(width_op_one/2),20,op_one);
			draw_arabic_str(93-(width_op_two/2),20,op_two);
			u8g_DrawStr(&u8g, (31-(width_op_one/2)-4),43,"<   >");
			if(Current_Value_1 == 0)
			{
				u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,"0");	
			}
			else
			{
				if (Value_1_sign)
				{
					u8g_DrawStr(&u8g, (31-(width_op_one/2)+2),43,"-");
				}
				u8g_DrawStr(&u8g, (31-(width_op_one/2)+8),43,Value_1);				
			}
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawBox(&u8g,(93-(width_op_one/2)-3),36,28,7);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, (93-(width_op_one/2)-4),43,"<   >");
			if (Current_Value_2 == 0)
			{
				u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,"0");
			}
			else
			{
				if (Value_2_sign)
				{
					u8g_DrawStr(&u8g, (93-(width_op_one/2)+2),43,"-");
				}
				u8g_DrawStr(&u8g, (93-(width_op_one/2)+8),43,Value_2);			
			}
			u8g_SetDefaultForegroundColor(&u8g);	
		}
		if(B)
		{
			u8g_DrawArabicStr(15,58,"����");
		}
	}
	} while ( u8g_NextPage(&u8g) );
	u8g_Delay(100);
	
}


char IP_1 [4],IP_2 [4],IP_3[4],IP_4[4];

void IP_Address (uint8_t select,char number)
{	if (select <= 2)
	{
		IP_1[select]=number;
		if (select==2){IP_1[3]='\0';}
	}
	else if ((2<select) && (select<6))
	{
		IP_2[select-3]=number;
		if (select==5){IP_2[3]='\0';}	
	}
	else if ((5<select) && (select<9))
	{
		IP_3[select-6]=number;
		if (select==8){IP_3[3]='\0';}
	}
	else if ((8<select) && (select<12))
	{
		IP_4[select-9]=number;
		if (select==11){IP_1[3]='\0';}
	}
	u8g_FirstPage(&u8g);
	do
	{u8g_SetFont(&u8g, u8g_font_6x10);	
	uint8_t width_title;
	char title []={"IP Address"};
	width_title=calc_eng_width(title);
	u8g_SetDefaultForegroundColor(&u8g);
	u8g_DrawStr(&u8g, 63-(width_title/2), 14, title);
			if (select == 0)
			{
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawBox(&u8g,18,28,7,9);		
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g,19,36,IP_1);		
				u8g_SetDefaultForegroundColor(&u8g);
			}
			else if (select == 1)
			{
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawStr(&u8g,19,36,IP_1);
				u8g_DrawBox(&u8g,24,28,7,9);
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g, 25,36,IP_1+1);
				u8g_SetDefaultForegroundColor(&u8g);
			}
			else if (select == 2)
			{
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawStr(&u8g, 19,36,IP_1);
				u8g_DrawBox(&u8g,30,28,7,9);
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g, 31,36,IP_1+2);
				u8g_SetDefaultForegroundColor(&u8g);
			}
			else if (select == 3)
			{
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawStr(&u8g, 19,36,IP_1);
				u8g_DrawBox(&u8g,40,28,7,9);
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g, 41,36,IP_2);
				u8g_SetDefaultForegroundColor(&u8g);
			}
			else if (select == 4)
			{
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawStr(&u8g, 19,36,IP_1);
				u8g_DrawStr(&u8g, 41,36,IP_2);
				u8g_DrawBox(&u8g,45,28,7,9);
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g, 46,36,IP_2+1);
				u8g_SetDefaultForegroundColor(&u8g);
			}
			else if (select == 5)
			{
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawStr(&u8g,19,36,IP_1);
				u8g_DrawStr(&u8g,41,36,IP_2);
				u8g_DrawBox(&u8g,51,28,7,9);
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g, 52,36,IP_2+2);
				u8g_SetDefaultForegroundColor(&u8g);
			}
			 else if (select == 6)
			{
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawStr(&u8g,19,36,IP_1);
				u8g_DrawStr(&u8g,41,36,IP_2);
				u8g_DrawBox(&u8g,62,28,7,9);
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g,63,36,IP_3);
				u8g_SetDefaultForegroundColor(&u8g);
			}
			else if (select == 7)
			{
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawStr(&u8g,19,36,IP_1);
				u8g_DrawStr(&u8g,41,36,IP_2);
				u8g_DrawStr(&u8g,63,36,IP_3);
				u8g_DrawBox(&u8g,68,28,7,9);
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g,69,36,IP_3+1);
				u8g_SetDefaultForegroundColor(&u8g);
			}
			else if (select == 8)
			{
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawStr(&u8g,19,36,IP_1);
				u8g_DrawStr(&u8g,41,36,IP_2);
				u8g_DrawStr(&u8g,63,36,IP_3);
				u8g_DrawBox(&u8g,74,28,7,9);
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g,75,36,IP_3+2);
				u8g_SetDefaultForegroundColor(&u8g);
			}
			else if (select == 9)
			{
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawStr(&u8g,19,36,IP_1);
				u8g_DrawStr(&u8g,41,36,IP_2);
				u8g_DrawStr(&u8g,63,36,IP_3);
				u8g_DrawBox(&u8g,85,28,7,9);
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g,86,36,IP_4);
				u8g_SetDefaultForegroundColor(&u8g);
			}
			else if (select == 10)
			{
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawStr(&u8g,19,36,IP_1);
				u8g_DrawStr(&u8g,41,36,IP_2);
				u8g_DrawStr(&u8g,63,36,IP_3);				
				u8g_DrawStr(&u8g,86,36,IP_4);
				u8g_DrawBox(&u8g,91,28,7,9);
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g,92,36,IP_4+1);
				u8g_SetDefaultForegroundColor(&u8g);
			}
			else if (select == 11)
			{
				u8g_SetDefaultForegroundColor(&u8g);
				u8g_DrawStr(&u8g,19,36,IP_1);
				u8g_DrawStr(&u8g,41,36,IP_2);
				u8g_DrawStr(&u8g,63,36,IP_3);
				u8g_DrawStr(&u8g,86,36,IP_4);
				u8g_DrawBox(&u8g,96,28,7,9);
				u8g_SetDefaultBackgroundColor(&u8g);
				u8g_DrawStr(&u8g,97,36,IP_4+2);
				u8g_SetDefaultForegroundColor(&u8g);
			}
			else if (select == 12)
			{
				u8g_DrawStr(&u8g,19,36,IP_1);
				u8g_DrawStr(&u8g,41,36,IP_2);
				u8g_DrawStr(&u8g,63,36,IP_3);
				u8g_DrawStr(&u8g,86,36,IP_4);
			}
	u8g_DrawPixel(&u8g,38,36);
	u8g_DrawPixel(&u8g,60,36);
	u8g_DrawPixel(&u8g,83,36);	
	} while ( u8g_NextPage(&u8g) );
	u8g_Delay(100);	
}


char F_number [12];
//Consider re-arranging the condition codes for shorter implementation 
void mobile_Number (uint8_t select,char number)
{
	uint8_t width_title;
	char title []={"Mobile Number"};
	width_title=calc_eng_width(title);			
	if (select <11)
	F_number[select]=number;
	else 
	F_number[11]= '\0';	
	u8g_FirstPage(&u8g);
	do
	{	
		u8g_SetFont(&u8g, u8g_font_6x10);
		u8g_SetDefaultForegroundColor(&u8g);
		u8g_DrawStr(&u8g, 63-(width_title/2), 14, title);	
		if (select == 0)
		{
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawBox(&u8g,27,23,7,9);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, 28, 31, F_number+select);
			u8g_SetDefaultForegroundColor(&u8g);
		}
		else if (select == 1)
		{
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawStr(&u8g, 28, 31, F_number);
			u8g_DrawBox(&u8g,32,23,7,9);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, 33, 31, F_number+select);
			u8g_SetDefaultForegroundColor(&u8g);			
		}
		else if (select == 2)
		{
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawStr(&u8g, 28, 31, F_number);
			u8g_DrawBox(&u8g,38,23,7,9);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, 39, 31, F_number+select);
			u8g_SetDefaultForegroundColor(&u8g);
		}
		else if (select == 3)
		{
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawStr(&u8g, 28, 31, F_number);
			u8g_DrawBox(&u8g,44,23,7,9);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, 45, 31, F_number+select);
			u8g_SetDefaultForegroundColor(&u8g);
		}		
		else if (select == 4)
		{
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawStr(&u8g, 28, 31, F_number);
			u8g_DrawBox(&u8g,50,23,7,9);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, 51, 31, F_number+select);
			u8g_SetDefaultForegroundColor(&u8g);
		}
		else if (select == 5)
		{
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawStr(&u8g, 28, 31, F_number);
			u8g_DrawBox(&u8g,56,23,7,9);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, 57, 31, F_number+select);
			u8g_SetDefaultForegroundColor(&u8g);
		}
		else if (select == 6)
		{
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawStr(&u8g, 28, 31, F_number);
			u8g_DrawBox(&u8g,62,23,7,9);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, 63, 31, F_number+select);
			u8g_SetDefaultForegroundColor(&u8g);
		}
		else if (select == 7)
		{
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawStr(&u8g, 28, 31, F_number);
			u8g_DrawBox(&u8g,68,23,7,9);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, 69, 31, F_number+select);
			u8g_SetDefaultForegroundColor(&u8g);
		}
		else if (select == 8)
		{
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawStr(&u8g, 28, 31, F_number);
			u8g_DrawBox(&u8g,74,23,7,9);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, 75, 31, F_number+select);
			u8g_SetDefaultForegroundColor(&u8g);
		}
		else if (select == 9)
		{
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawStr(&u8g, 28, 31, F_number);
			u8g_DrawBox(&u8g,80,23,7,9);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, 81, 31, F_number+select);
			u8g_SetDefaultForegroundColor(&u8g);
		}
		else if (select == 10)
		{
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawStr(&u8g, 28, 31, F_number);
			u8g_DrawBox(&u8g,86,23,7,9);
			u8g_SetDefaultBackgroundColor(&u8g);
			u8g_DrawStr(&u8g, 87, 31, F_number+select);
			u8g_SetDefaultForegroundColor(&u8g);	
		}
		else if (select == 11)
		{
			u8g_SetDefaultForegroundColor(&u8g);
			u8g_DrawStr(&u8g, 28, 31, F_number);
		}
	} while ( u8g_NextPage(&u8g) );
	u8g_Delay(100);
	if (select == 11)
	{
		for (int i=0;i<11;i++)
		{
			F_number[i] = '\0';
		}
	}
}


void operation_screen(unsigned char L,uint8_t B,char Title [])
{	
	uint8_t width_title;
	u8g_FirstPage(&u8g);
	do
	{
		u8g_SetFont(&u8g, u8g_font_6x10);
	if (L == 'E')
	{
		width_title=calc_eng_width(Title);	
		u8g_DrawStr(&u8g, 63-(width_title/2), 31, Title);	
	if(B)
		{
			draw_english_Shadowed(100,51,"Back");
		}
	}
	else if (L == 'A')
	{
		width_title=calc_arb_width(Title);	
		draw_arabic_str(63-(width_title/2),7,Title);
		if(B)
		{
			u8g_DrawArabicStr(0,55,"����");
		}
	}
	} while ( u8g_NextPage(&u8g) );
	u8g_Delay(100);
}		
		
void u8g_DrawArabicStr(uint8_t x,uint8_t y, char ArabicStr[])
{
	uint8_t cnt = 0, Index = 0, temp = 0;
	//get number of letters in the string
	while(ArabicStr[cnt] != '\0' )
	{
		cnt++;
	}
	//Decode the string 
 	for (Index = 0;Index < cnt;Index++)
 	{
 		
 		if(ArabicStr[Index] == 199)
 			ArabicStr[Index] -= 198;
 		else if(ArabicStr[Index] == 200)
 			ArabicStr[Index] -= 198;
 		else if((ArabicStr[Index] >= 202) && (ArabicStr[Index] <= 214))
 			ArabicStr[Index] -= 199;
 		else if((ArabicStr[Index] >= 216) && (ArabicStr[Index] <= 219))
 			ArabicStr[Index] -= 200;
 		else if((ArabicStr[Index] >= 221) && (ArabicStr[Index] <= 223))
 			ArabicStr[Index] -= 201;
 		else if(ArabicStr[Index] == 225)
 			ArabicStr[Index] -= 202;
 		else if((ArabicStr[Index] >= 227) && (ArabicStr[Index] <= 230))
 			ArabicStr[Index] -= 203;
 		else if(ArabicStr[Index] == 237)
 			ArabicStr[Index] -= 209;
 		else if(ArabicStr[Index] == 32)
 			ArabicStr[Index] += 11;
			 
		if (Index == cnt-1 || ArabicStr[Index+1] == 43)
		{
			if ((ArabicStr[Index] >= 5) && (ArabicStr[Index] <= 7))
				temp = (ArabicStr[Index]+24)*6;
			else if ((ArabicStr[Index] >= 12) && (ArabicStr[Index] <= 15))
				temp = (ArabicStr[Index]+20)*6;
			else if ((ArabicStr[Index] >= 18) && (ArabicStr[Index] <= 19))
				temp = (ArabicStr[Index]+18)*6;
			else if ((ArabicStr[Index] >= 22) && (ArabicStr[Index] <= 24))
				temp = (ArabicStr[Index]+16)*6;	
			else if (ArabicStr[Index] == 26)
				temp = (ArabicStr[Index]+15)*6;
			else if (ArabicStr[Index] == 28)
				temp = (ArabicStr[Index]+14)*6;
			else
				temp = ArabicStr[Index]*6;
		}
		else
			temp = ArabicStr[Index]*6;
		
		if (ArabicStr[Index] != 43) //If not space
			u8g_DrawBitmap(&u8g, x, y,1 ,6, &ArabicLetters[temp]);
			
		if (ArabicStr[Index] == 1)	//if the last printed letter is ?
			x-=2;
		else if (ArabicStr[Index] >= 8 && ArabicStr[Index] <= 11)	//if the last printed letter is ? or ? or ? or ?
			x-=5;
		else if (ArabicStr[Index] == 43)
			x-=3;
		else
			x-=7;
 	}

}

// an old version of u8g_DrawArabicStr

// void u8g_DrawArabicStr(uint8_t x,uint8_t y,uint8_t cnt, uint8_t *ArabicStr)
// {
// 	uint8_t Index;
// 	while( cnt > 0)
// 	{
// 		if (cnt == 1)
// 		{
// 			if (*ArabicStr >= 4 && *ArabicStr <= 6)
// 			Index = (*ArabicStr+24)*6;
// 			else if (*ArabicStr >= 11 && *ArabicStr <= 14)
// 			Index = (*ArabicStr+20)*6;
// 			else if (*ArabicStr >= 17 && *ArabicStr <= 18)
// 			Index = (*ArabicStr+18)*6;
// 			else if (*ArabicStr >= 21 && *ArabicStr <= 23)
// 			Index = (*ArabicStr+16)*6;
// 			else if (*ArabicStr == 27)
// 			Index = (*ArabicStr+13)*6;
// 			else
// 			Index = *ArabicStr*6;
// 		}
// 		else
// 		Index = *ArabicStr*6;
// 		u8g_DrawBitmap(&u8g, x, y,1 ,6, &ArabicLetters[Index]);
// 		cnt--;
// 		if (*ArabicStr == 0)	//if the last printed letter is ?
// 		x-=2;
// 		else if (*ArabicStr >= 7 && *ArabicStr <= 10)	//if the last printed letter is ? or ? or ? or ?
// 		x-=5;
// 		else
// 		x-=7;
// 		
// 		ArabicStr++;
// 	}
// }