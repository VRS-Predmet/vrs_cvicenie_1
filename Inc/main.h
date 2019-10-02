/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_ll_rcc.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_system.h"
#include "stm32f3xx_ll_exti.h"
#include "stm32f3xx_ll_cortex.h"
#include "stm32f3xx_ll_utils.h"
#include "stm32f3xx_ll_pwr.h"
#include "stm32f3xx_ll_dma.h"
#include "stm32f3xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

//GPIOA peripheral base address
#define	GPIOA_BASE_ADDR			(uint32_t)(0x48000000U)

//GPIOB peripheral base address
#define	GPIOB_BASE_ADDR			(uint32_t)(0x48000400U)
//MODER register
#define	GPIOB_MODER_REG			*(uint32_t *)(GPIOB_BASE_ADDR + 0x00U)
//OTYPER register
#define	GPIOB_OTYPER_REG		*(uint32_t *)(GPIOB_BASE_ADDR + 0x04U)
//OSPEEDER register
#define GPIOB_OSPEEDER_REG		*(uint32_t *)(GPIOB_BASE_ADDR + 0x08U)
//PUPDR register
#define GPIOB_PUPDR_REG			*(uint32_t *)(GPIOB_BASE_ADDR + 0x0CU)
//IDR register
#define GPIOB_IDR_REG			*(uint32_t *)(GPIOB_BASE_ADDR + 0x10U)
//ODR register
#define GPIOB_ODR_REG			*(uint32_t *)(GPIOB_BASE_ADDR + 0x14U)
//BSRR register
#define GPIOB_BSRR_REG			*(uint32_t *)(GPIOB_BASE_ADDR + 0x18U)
//BRR register
#define GPIOB_BRR_REG			*(uint32_t *)(GPIOB_BASE_ADDR + 0x28U)

//RCC base address
#define	RCC_BASE_ADDR			(uint32_t)(0x40021000U)
//AHBEN register
#define	RCC_AHBENR_REG			*((volatile uint32_t *) (uint32_t)(RCC_BASE_ADDR + 0x00000014U))

#define LED_ON					*((volatile uint32_t *)((uint32_t)(0x48000400 + 0x18U))) |= (1 << 3)   	//GPIOB pin 3
#define LED_OFF					*((volatile uint32_t *)((uint32_t)0x48000400 + 0x28U)) |= (1 << 3);		//GPIOB pin 3

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
