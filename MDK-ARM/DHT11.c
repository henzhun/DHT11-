 
/* USER CODE BEGIN 0 */

#include "gpio.h"
#include "DHT11.h"
#include "math.h"

extern int num;
float tem=0,hum=0,tem1=0,hum1=0;

 void delay_us(int t)  //��ʱ������΢�룩
 {
	 for(int i=0;i<t*9;i++);
 }
 
 void delay_ms(int t)  //��ʱ���������룩
 {
	for(int i=0;i<t;i++)
	for(int j=0;j<9143;j++);
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
	//MX_GPIO_IN_Init();  //����Data��IO��Ϊ����
  for(int i=0;i<8;i++)    
   {          
      while(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5));  //
      delay_us(60);  //���60us���Ǹߵ�ƽ����Ϊ1������Ϊ0           
     dat<<=1; //����Ϊ��ʱֱ����λ  
		 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==1)    
				{   	
					dat+=1;
				}
      while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5));     
    }  
    return dat;
}

void DHT11_receive()      //������������
{		
    char R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise; 
    DHT11_start();
		MX_GPIO_IN_Init();  //����Data��IO��Ϊ����
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0)
    {
        while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0)   //
				{
				}
				while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)!=0)
				{
				}
        R_H=DHT11_rec_byte();    //  �¶ȸ�λ
        R_L=DHT11_rec_byte();    //  �¶ȵ�λ
        T_H=DHT11_rec_byte();    //  ʪ�ȸ�λ
        T_L=DHT11_rec_byte();    //  ʪ�ȵ�λ
        revise=DHT11_rec_byte(); //  У��
		

				/* ʪ������ */
				if((R_H&0x01)==0x01)
				{
					hum=1*pow(2,0);
				}
				else
				{
					hum=0*pow(2,0);
				}
				if((R_H&0x02)==0x02)
				{
					hum=hum+1*pow(2,1);
				}
				else
				{
					hum=hum+0*pow(2,1);
				}
				if((R_H&0x04)==0x04)
				{
					hum=hum+1*pow(2,2);
				}
				else
				{
					hum=hum+0*pow(2,2);
				}
				if((R_H&0x08)==0x08)
				{
					hum=hum+1*pow(2,3);
				}
				else
				{
					hum=hum+0*pow(2,3);
				}
				if((R_H&0x10)==0x10)
				{
					hum=hum+1*pow(2,4);
				}
				else
				{
					hum=hum+0*pow(2,4);
				}
				if((R_H&0x20)==0x20)
				{
					hum=hum+1*pow(2,5);
				}
				else
				{
					hum=hum+0*pow(2,5);
				}
				if((R_H&0x40)==0x40)
				{
					hum=hum+1*pow(2,6);
				}
				else
				{
					hum=hum+0*pow(2,6);
				}
				if((R_H&0x80)==0x80)
				{
					hum=hum+1*pow(2,7);
				}
				else
				{
					hum=hum+0*pow(2,7);
				}
		/*�¶�����*/
				if((T_H&0x01)==0x01)
				{
					tem=1*pow(2,0);
				}
				else
				{
					tem=0*pow(2,0);
				}
				if((T_H&0x02)==0x02)
				{
					tem=tem+1*pow(2,1);
				}
				else
				{
					tem=tem+0*pow(2,1);
				}
				if((T_H&0x04)==0x04)
				{
					tem=tem+1*pow(2,2);
				}
				else
				{
					tem=tem+0*pow(2,2);
				}
				if((T_H&0x08)==0x08)
				{
					tem=tem+1*pow(2,3);
				}
				else
				{
					tem=tem+0*pow(2,3);
				}
				if((T_H&0x10)==0x10)
				{
					tem=tem+1*pow(2,4);
				}
				else
				{
					tem=tem+0*pow(2,4);
				}
				if((T_H&0x20)==0x20)
				{
					tem=tem+1*pow(2,5);
				}
				else
				{
					tem=tem+0*pow(2,5);
				}
				if((T_H&0x40)==0x40)
				{
					tem=tem+1*pow(2,6);
				}
				else
				{
					tem=tem+0*pow(2,6);
				}
				if((T_H&0x80)==0x80)
				{
					tem=tem+1*pow(2,7);
				}
				else
				{
					tem=tem+0*pow(2,7);
				}
				
				/* ʪ��С�� */
				if((R_L&0x01)==0x01)
				{
					hum1=1*pow(2,0);
				}
				else
				{
					hum1=0*pow(2,0);
				}
				if((R_L&0x02)==0x02)
				{
					hum1=hum1+1*pow(2,1);
				}
				else
				{
					hum1=hum1+0*pow(2,1);
				}
				if((R_L&0x04)==0x04)
				{
					hum1=hum1+1*pow(2,2);
				}
				else
				{
					hum1=hum1+0*pow(2,2);
				}
				if((R_L&0x08)==0x08)
				{
					hum1=hum1+1*pow(2,3);
				}
				else
				{
					hum1=hum1+0*pow(2,3);
				}
				if((R_L&0x10)==0x10)
				{
					hum1=hum1+1*pow(2,4);
				}
				else
				{
					hum1=hum1+0*pow(2,4);
				}
				if((R_L&0x20)==0x20)
				{
					hum1=hum1+1*pow(2,5);
				}
				else
				{
					hum1=hum1+0*pow(2,5);
				}
				if((R_L&0x40)==0x40)
				{
					hum1=hum1+1*pow(2,6);
				}
				else
				{
					hum1=hum1+0*pow(2,6);
				}
				if((R_L&0x80)==0x80)
				{
					hum1=hum1+1*pow(2,7);
				}
				else
				{
					hum1=hum1+0*pow(2,7);
				}
		/*�¶�С��*/
				if((T_L&0x01)==0x01)
				{
					tem1=1*pow(2,0);
				}
				else
				{
					tem1=0*pow(2,0);
				}
				if((T_L&0x02)==0x02)
				{
					tem1=tem1+1*pow(2,1);
				}
				else
				{
					tem1=tem1+0*pow(2,1);
				}
				if((T_L&0x04)==0x04)
				{
					tem1=tem1+1*pow(2,2);
				}
				else
				{
					tem1=tem1+0*pow(2,2);
				}
				if((T_L&0x08)==0x08)
				{
					tem1=tem1+1*pow(2,3);
				}
				else
				{
					tem1=tem1+0*pow(2,3);
				}
				if((T_L&0x10)==0x10)
				{
					tem1=tem1+1*pow(2,4);
				}
				else
				{
					tem1=tem1+0*pow(2,4);
				}
				if((T_L&0x20)==0x20)
				{
					tem1=tem1+1*pow(2,5);
				}
				else
				{
					tem1=tem1+0*pow(2,5);
				}
				if((T_L&0x40)==0x40)
				{
					tem1=tem1+1*pow(2,6);
				}
				else
				{
					tem1=tem1+0*pow(2,6);
				}
				if((T_L&0x80)==0x80)
				{
					tem1=tem1+1*pow(2,7);
				}
				else
				{
					tem1=tem1+0*pow(2,7);
				}
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
 