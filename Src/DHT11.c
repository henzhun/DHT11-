 
/* USER CODE BEGIN 0 */

#include "gpio.h"
#include "DHT11.h"
#include "tim.h"

extern int num;

 void delay_us(int t)  //��ʱ������΢�룩
 {
	HAL_TIM_Base_Start_IT(&htim1);//��TIM1��ʱ��
		while(num<=t);
	 HAL_TIM_Base_Stop_IT(&htim1);//��TIM1��ʱ��
	 num=0;//num����
 }
 
 void delay_ms(int t)  //��ʱ���������룩
 {
	HAL_TIM_Base_Start_IT(&htim1);//��TIM1��ʱ��
	 while(num<=t*1000);
	 HAL_TIM_Base_Stop_IT(&htim1);//��TIM1��ʱ��
	 num=0;//num����
 }
 
 void DHT11_start()  //DHT11��ʼ����
{
  MX_GPIO_OUT_H_Init();
	delay_us(10);
	MX_GPIO_OUT_L_Init();
	delay_ms(20);
	MX_GPIO_OUT_H_Init();
	delay_us(40);	
}

char DHT11_rec_byte()      //���ֽڶ�ȡÿ���ֽ�
{
  char dat=0;
	MX_GPIO_IN_Init();  //����Data��IO��Ϊ����
  for(int i=0;i<8;i++)    
   {          
      while(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5));  //
      delay_us(60);  //���60us���Ǹߵ�ƽ����Ϊ1������Ϊ0           
      if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==1)    
				{   
					dat<<=1; //����Ϊ��ʱֱ����λ 
					dat+=1;
				}
				else
				{
					dat<<=1; //����Ϊ��ʱֱ����λ 
				}
      while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5));     
    }  
    return dat;
}

void DHT11_receive()      //������������
{
		MX_GPIO_IN_Init();  //����Data��IO��Ϊ����
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
 