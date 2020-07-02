/* USER CODE BEGIN 0 */

#ifndef __DHT11_H
#define __DHT11_H

#include "gpio.h"


void delay_us(int t);
void delay_ms(int t);
void DHT11_start(void);
char DHT11_rec_byte();
void DHT11_receive(void);


#endif

/* USER CODE END 0 */

