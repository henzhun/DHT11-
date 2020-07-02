 
/* USER CODE BEGIN 0 */

#include "gpio.h"
#include "DHT11.h"
#include "tim.h"

extern int num;

 void delay_us(int t)  //延时函数（微秒）
 {
	HAL_TIM_Base_Start_IT(&htim1);//打开TIM1定时器
		while(num<=t);
	 HAL_TIM_Base_Stop_IT(&htim1);//打开TIM1定时器
	 num=0;//num清零
 }
 
 void delay_ms(int t)  //延时函数（毫秒）
 {
	HAL_TIM_Base_Start_IT(&htim1);//打开TIM1定时器
	 while(num<=t*1000);
	 HAL_TIM_Base_Stop_IT(&htim1);//打开TIM1定时器
	 num=0;//num清零
 }
 
 void DHT11_start()  //DHT11开始工作
{
  MX_GPIO_OUT_H_Init();
	delay_us(10);
	MX_GPIO_OUT_L_Init();
	delay_ms(20);
	MX_GPIO_OUT_H_Init();
	delay_us(40);	
}

char DHT11_rec_byte()      //按字节读取每个字节
{
  char dat=0;
	MX_GPIO_IN_Init();  //设置Data的IO口为输入
  for(int i=0;i<8;i++)    
   {          
      while(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5));  //
      delay_us(60);  //如果60us后还是高电平，则为1，否则为0           
      if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==1)    
				{   
					dat<<=1; //数据为零时直接移位 
					dat+=1;
				}
				else
				{
					dat<<=1; //数据为零时直接移位 
				}
      while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5));     
    }  
    return dat;
}

void DHT11_receive()      //接收所有数据
{
		MX_GPIO_IN_Init();  //设置Data的IO口为输入
    char R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise; 
    DHT11_start();
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0)
    {
        while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0)   //
				{
				}
				while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)!=0)
				{
				}
        R_H=DHT11_rec_byte();    //  
        R_L=DHT11_rec_byte();    // 
        T_H=DHT11_rec_byte();    // 
        T_L=DHT11_rec_byte();    //
        revise=DHT11_rec_byte(); //

        delay_us(25);    //

        if((R_H+R_L+T_H+T_L)==revise)      //
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
        } 
				
			
    }
}


/* USER CODE END 0 */
 