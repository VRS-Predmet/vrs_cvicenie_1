/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"


int main(void)
{
  /*
   * DO NOT WRITE TO THE WHOLE REGISTER!!!
   *
   * Write to bits, that are meant for change.
   */

  /*Enables clock for GPIO port B*/
  *((volatile uint32_t *) (uint32_t)(0x40021000 + 0x00000014U)) |= (uint32_t)(1 << 18);

  /*GPIOB pin 3 and 6 setup*/
  /*GPIO MODER register*/
  //Set mode for pin 3
  *((volatile uint32_t *)((uint32_t)0x48000400)) &= ~(uint32_t)(0x3 << 6);
  *((volatile uint32_t *)((uint32_t)0x48000400)) |= (uint32_t)(1 << 6);
  //Set mode for pin 6
  *((volatile uint32_t *)((uint32_t)0x48000400)) &= ~(uint32_t)(0x3 << 12);

  /*GPIO OTYPER register*/
  *((volatile uint32_t *)((uint32_t)(0x48000400 + 0x04U))) &= ~(1 << 3);

  /*GPIO OSPEEDR register*/
  //Set Low speed for GPIOB pin 3
  *((volatile uint32_t *)((uint32_t)(0x48000400 + 0x08U))) &= ~(0x3 << 6);

  /*GPIO PUPDR register, reset*/
  //Set pull up for GPIOB pin 6 (input)
  *((volatile uint32_t *)((uint32_t)(0x48000400 + 0x0CU))) |= (1 << 12);
  //Set no pull for GPIOB pin 3
  *((volatile uint32_t *)((uint32_t)(0x48000400 + 0x0CU))) &= ~(0x3 << 6);

  while (1)
  {
	  //GPIO IDR, read input from pin 6
	  if(!(*((volatile uint32_t *)((uint32_t)(0x48000400 + 0x10U))) & (1 << 6)))
	  {
		  //GPIO BSRR register, set output pin 3
		  LED_ON;
		  //delay
		  for(uint16_t i = 0; i < 0xFF00; i++){}
		  //GPIO BRR, reset output pin 3
		  LED_OFF;
		  //delay
		  for(uint16_t i = 0; i < 0xFF00; i++){}
	  }
	  else
	  {
		  //GPIO BSRR register, set output pin 3
		  LED_ON;
		  //delay
		  for(uint32_t i = 0; i < 0xFFFF0; i++){}
		  //GPIO BRR, reset output pin 3
		  LED_OFF;
		  //delay
		  for(uint32_t i = 0; i < 0xFFF00; i++){}
	  }
  }

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
