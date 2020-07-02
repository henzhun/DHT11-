/* USER CODE BEGIN 0 */

#ifndef __oled_H
#define __oled_H

#include "stdint.h"

//uint8_t OLED_GRAM[128][8];

void OLED_RESET();
void OLED_DC_Set();
void OLED_DC_Reset();
void OLED_CS_Set();
void OLED_CS_Reset();
void OLED_WR_Byte(char data,char cmd);
void OLED_Clear();
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_INIT();
void OLED_Display_On(void);
void OLED_Display_Off(void);
void DataOut();
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr);
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y,char *chr);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_ShowMH(unsigned char x,unsigned char y);
void OLED_ShowDH(unsigned char x,unsigned char y);
#endif

/* USER CODE END 0 */