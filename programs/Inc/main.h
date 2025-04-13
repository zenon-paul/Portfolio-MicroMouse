/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define indicator2_Pin GPIO_PIN_0
#define indicator2_GPIO_Port GPIOF
#define MoterB_DIR_Pin GPIO_PIN_1
#define MoterB_DIR_GPIO_Port GPIOF
#define ledA_pulse_TIM2_CH4_Pin GPIO_PIN_3
#define ledA_pulse_TIM2_CH4_GPIO_Port GPIOA
#define indicator1_Pin GPIO_PIN_6
#define indicator1_GPIO_Port GPIOA
#define ledB_pulse_TIM17_CH1_Pin GPIO_PIN_7
#define ledB_pulse_TIM17_CH1_GPIO_Port GPIOA
#define MoterA_PWM_TIM3_CH3_Pin GPIO_PIN_0
#define MoterA_PWM_TIM3_CH3_GPIO_Port GPIOB
#define encB_b_Pin GPIO_PIN_8
#define encB_b_GPIO_Port GPIOA
#define encB_b_EXTI_IRQn EXTI9_5_IRQn
#define MoterA_DIR_Pin GPIO_PIN_9
#define MoterA_DIR_GPIO_Port GPIOA
#define encA_b_Pin GPIO_PIN_10
#define encA_b_GPIO_Port GPIOA
#define encA_b_EXTI_IRQn EXTI15_10_IRQn
#define encB_a_Pin GPIO_PIN_11
#define encB_a_GPIO_Port GPIOA
#define encB_a_EXTI_IRQn EXTI15_10_IRQn
#define encA_a_Pin GPIO_PIN_12
#define encA_a_GPIO_Port GPIOA
#define encA_a_EXTI_IRQn EXTI15_10_IRQn
#define T_SWDIO_Pin GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define BNO055_SCL_Pin GPIO_PIN_15
#define BNO055_SCL_GPIO_Port GPIOA
#define indicator3_Pin GPIO_PIN_3
#define indicator3_GPIO_Port GPIOB
#define indicator4_Pin GPIO_PIN_4
#define indicator4_GPIO_Port GPIOB
#define user_sw_Pin GPIO_PIN_5
#define user_sw_GPIO_Port GPIOB
#define MoterB_PWM_TIM8_CH1_Pin GPIO_PIN_6
#define MoterB_PWM_TIM8_CH1_GPIO_Port GPIOB
#define BNO055_SDA_Pin GPIO_PIN_7
#define BNO055_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
