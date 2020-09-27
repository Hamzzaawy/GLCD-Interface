#include <avr/io.h>
#include "u8g.h"
#include <util/delay.h>
#include <avr/interrupt.h>



void tostring( char str[], int num);
uint8_t calc_eng_width (char *word);
uint8_t calc_arb_width (char *Arabic);

void draw_english_str(uint8_t x,uint8_t y,char word []);
void draw_english_boarder (uint8_t x,uint8_t y,char word []);
void draw_english_Shadowed(uint8_t x,uint8_t y,char word []);

void draw_arabic_str (uint8_t x ,uint8_t y,char ArabicStr[]);
void draw_arabic_boarder (uint8_t x ,uint8_t y,char ArabicStr[]);
void draw_arabic_Shadowed (uint8_t x ,uint8_t y,char ArabicStr[]);

void draw_two_item_selector (unsigned char L,uint8_t B,uint8_t select,char Tiltle [],char op_one [],char op_two []);
void draw_three_item_selector (unsigned char L,uint8_t B,uint8_t select,char Tiltle [],char op_one [],char op_two [],char op_three []);
void draw_four_item_selector (unsigned char L,uint8_t B,uint8_t select,char Tiltle [],char op_one [],char op_two [],char op_three [],char op_four []);

void OneValueMenu(unsigned char L,uint8_t B, uint8_t Current_Value,char Tiltle []);
//void draw_two_item_editing_value(unsigned char L,uint8_t B,uint8_t select, int Current_Value_1, int Current_Value_2, char Tiltle [],char op_one [],char op_two []);
void TwoValueMenu(unsigned char L,uint8_t B,uint8_t select,int Current_Value_1,uint8_t Value_1_sign,int Current_Value_2,uint8_t Value_2_sign, char Tiltle [],char op_one [],char op_two []);

void IP_Address (uint8_t select,char number);
void mobile_Number (uint8_t select,char number);
void operation_screen(unsigned char L,uint8_t B,char Tiltle []);

void menu_1 (void);
void u8g_DrawArabicStr(uint8_t x,uint8_t y, char ArabicStr[]);