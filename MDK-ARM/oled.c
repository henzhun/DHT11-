/* USER CODE BEGIN 0 */
#include "gpio.h"
#include "DHT11.h"
#include "oled.h"
#include "spi.h"
#include "stdint.h"
#include "oledfont.h" 

#define OLED_CMD   0 
#define OLED_DATA  1
#define SIZE       16

void DataOut(char data)
{
	uint8_t d=data;
	HAL_SPI_Transmit(&hspi1, &d, 1, 100);
}

void OLED_RESET()
{
		/* 对OLED 屏幕进行复位*/
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	delay_ms(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
}


void OLED_DC_Set()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void OLED_DC_Reset()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
}

void OLED_CS_Set()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
}

void OLED_CS_Reset()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
}


void OLED_WR_Byte(char data,char cmd)
{       
    if(cmd)
      OLED_DC_Set();
    else 
      OLED_DC_Reset();           
    OLED_CS_Reset();
		DataOut(data); 
}

void OLED_Clear()  
{  
    uint8_t i,n;            
    for(i=0;i<8;i++)  
    {  
        OLED_WR_Byte (0xb0+i,OLED_CMD);    
        OLED_WR_Byte (0x00,OLED_CMD);      
        OLED_WR_Byte (0x10,OLED_CMD);        
        for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
    }   
}

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}

void OLED_INIT()
{
		OLED_RESET();
	
		OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
    OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
    OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0???? 0xa1??
    OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0???? 0xc8??
    OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset    Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00,OLED_CMD);//-not offset
    OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
    OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
    OLED_WR_Byte(0x12,OLED_CMD);
    OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
    OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
    OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x02,OLED_CMD);//
    OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
    OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
    OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
    OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
    OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
    
    OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
    OLED_Clear();
    OLED_Set_Pos(0,0);  
	
}

void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}        

uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)
		result*=m;    
	return result;
}	
/**
  * @brief 在指定位置显示一个字符,包括部分字符
	* @param x:0~127   y:0~63   mode:0,反白显示  1,正常显示	 size:选择字体 16/12 
	* @retval None
  */
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr)
{          
    unsigned char c=0,i=0;    
    c=chr-' ';           
    if(x>127)
    {
        x=0;
        y=y+2;
    }
    if(SIZE==16)
    {
        OLED_Set_Pos(x,y);    
        for(i=0;i<8;i++)
					OLED_WR_Byte(D8X16[c*16+i],OLED_DATA);
			
        OLED_Set_Pos(x,y+1);
        for(i=0;i<8;i++)
					OLED_WR_Byte(D8X16[c*16+i+8],OLED_DATA);
    }
    else
    {    
        OLED_Set_Pos(x,y+1);
        for(i=0;i<6;i++)
        {
            OLED_WR_Byte(D6X8[c][i],OLED_DATA);
        }
    }
}

void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t no)
{                      
    uint8_t t,adder=0;
    OLED_Set_Pos(x,y);    
    for(t=0;t<32;t++)
      {
         OLED_WR_Byte(SHOW[2*no][t],OLED_DATA);
         adder+=1;
      }    
    OLED_Set_Pos(x,y+1);    
    for(t=0;t<32;t++)
      {    
         OLED_WR_Byte(SHOW[2*no+1][t],OLED_DATA);
         adder+=1;
      }                    
}
/**
  * @brief 显示2个数字
	* @param x,y :起点坐标
	*				 len :数字的位数，即显示几位有效数字
  *				 size:字体大小
  *				 mode:模式	0,填充模式;1,叠加模式
  *        num:数值(0~4294967295);
	* @retval None
  */ 
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}
			else 
				enshow=1; 	 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 

void OLED_ShowString(uint8_t x,uint8_t y,char *chr)
{
	unsigned char j=0;
	while(chr[j]!='\0')
	{		
		OLED_ShowChar(x,y,chr[j]);
		x+=8;
		if(x>120)
			{
				x=0;
				y+=2;
			}
			j++;
	}
}

void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) 
		y=y1/8;      
  else 
		y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

void OLED_ShowMH(unsigned char x,unsigned char y)
{
	OLED_Set_Pos(x,y+1);
        for(char i=0;i<8;i++)
        {
            OLED_WR_Byte(MH[i],OLED_DATA);
        }
}
void OLED_ShowDH(unsigned char x,unsigned char y)
{
	OLED_Set_Pos(x,y+1);
        for(char i=0;i<4;i++)
        {
            OLED_WR_Byte(DH[i],OLED_DATA);
        }
}
/* USER CODE END 0 */