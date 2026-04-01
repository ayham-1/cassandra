/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_BIT2_Pin GPIO_PIN_13
#define LED_BIT2_GPIO_Port GPIOC
#define LED_BIT1_Pin GPIO_PIN_14
#define LED_BIT1_GPIO_Port GPIOC
#define LED_BIT0_Pin GPIO_PIN_15
#define LED_BIT0_GPIO_Port GPIOC
#define USB_CC2_READ_Pin GPIO_PIN_0
#define USB_CC2_READ_GPIO_Port GPIOC
#define USB_CC1_READ_Pin GPIO_PIN_1
#define USB_CC1_READ_GPIO_Port GPIOC
#define TGT_SWDIO_Pin GPIO_PIN_2
#define TGT_SWDIO_GPIO_Port GPIOC
#define TGT_SWO_Pin GPIO_PIN_3
#define TGT_SWO_GPIO_Port GPIOC
#define TGT_SWCLK_Pin GPIO_PIN_0
#define TGT_SWCLK_GPIO_Port GPIOA
#define TGT_RST_Pin GPIO_PIN_1
#define TGT_RST_GPIO_Port GPIOA
#define DISPLAY_ACTIVE_LOW_RESET_Pin GPIO_PIN_4
#define DISPLAY_ACTIVE_LOW_RESET_GPIO_Port GPIOA
#define DISPLAY_DC_Pin GPIO_PIN_4
#define DISPLAY_DC_GPIO_Port GPIOC
#define DISPLAY_ACTIVE_LOW_CS_Pin GPIO_PIN_5
#define DISPLAY_ACTIVE_LOW_CS_GPIO_Port GPIOC
#define uSD_DET_Pin GPIO_PIN_8
#define uSD_DET_GPIO_Port GPIOA
#define PBT_0_Pin GPIO_PIN_5
#define PBT_0_GPIO_Port GPIOB
#define PBT_1_Pin GPIO_PIN_6
#define PBT_1_GPIO_Port GPIOB
#define PBT_2_Pin GPIO_PIN_7
#define PBT_2_GPIO_Port GPIOB
#define LED_BIT3_Pin GPIO_PIN_9
#define LED_BIT3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
