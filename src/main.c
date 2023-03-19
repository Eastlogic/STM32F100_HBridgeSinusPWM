#include "stm32f10x.h"
#include <stdio.h>
#include "user.h"





int main(void)
{

RCC_init();
GPIO_init();	
	
TIM1_init();
NVIC_init();	
	
while(1)
{
	
}



}



