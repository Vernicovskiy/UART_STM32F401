#include "main.h"



 void USART1_IRQHandler (void){

	 if (USART1->SR & USART_SR_RXNE){

		 if(USART1->DR == '1'){

			 GPIOA->BSRR |= GPIO_BSRR_BS5;
		 }

		 if(USART1->DR == '2'){

		 	GPIOA->BSRR |= GPIO_BSRR_BR5;

		 }
	 }
 }



int main(void)
{

  // Настраиваем порт A для работы с USART2
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Включаем тактирование порта A
  GPIOA->MODER |= GPIO_MODER_MODER5_0; /* set pin to output mode */
  GPIOA->MODER |= GPIO_MODER_MODER9_1; // Устанавливаем режим альтернативной функции для пина PA9 (TX)
  GPIOA->MODER |= GPIO_MODER_MODER10_1;
  GPIOA->AFR[1] |= (GPIO_AFRH_AFSEL9_2 | GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_0); // Выбираем альтернативную функцию 7 (USART1) для пина PA9
  GPIOA->AFR[1] |= (GPIO_AFRH_AFSEL10_2 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_0); // Выбираем альтернативную функцию 7 (USART1) для пина PA9
  // Настраиваем USART1 для передачи данных
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Включаем тактирование USART1
  USART1->BRR = 0x683; // Устанавливаем скорость передачи 9600 бод при частоте 16 МГц
  USART1->CR1 |= USART_CR1_TE; // Включаем передатчик
  USART1->CR1 |= USART_CR1_RE;
  USART1->CR1 |= USART_CR1_RXNEIE;
  NVIC_EnableIRQ(USART1_IRQn);
  USART1->CR1 |= USART_CR1_UE; // Включаем USART1



  // Отправляем строку "Hello" в терминал
  char *str = "Hello World\n"; // Объявляем строку
  char *str1 = str;




  while (1){

  while (*str) // Пока не достигнут конец строки
    {
	  while (!(USART1->SR & USART_SR_TXE)); //если TXE сброшен, значит данные записываются
	  USART1->DR = *str++;
	  //asm("NOP");
       // Передаем очередной символ
    }
  	  str = str1;
  	  for(long i=0; i<1000000;i++){}
  	}

}






