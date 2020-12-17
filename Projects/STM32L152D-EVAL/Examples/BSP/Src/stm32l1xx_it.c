/**
  ******************************************************************************
  * @file    BSP/BSP/Src/stm32l1xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_it.h"

/** @addtogroup STM32L1xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern I2S_HandleTypeDef hAudioOutI2s;
extern ADC_HandleTypeDef  hAudioInAdc;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler( void )
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler( void )
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while( 1 )
    {
    }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler( void )
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while( 1 )
    {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler( void )
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while( 1 )
    {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler( void )
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while( 1 )
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler( void )
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler( void )
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler( void )
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler( void )
{
    HAL_IncTick();
    Toggle_Leds();
}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx.s).                                               */
/******************************************************************************/


/**
  * @brief  This function handles External line 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( DOWN_JOY_PIN );
}

/**
  * @brief  This function handles External line 10 to 15 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( UP_JOY_PIN );
    HAL_GPIO_EXTI_IRQHandler( SEL_JOY_PIN );
}

/**
  * @brief  This function handles I2S DMA TX interrupt request.
  * @param  None
  * @retval None
  */
void I2SOUT_IRQHandler( void )
{
    HAL_DMA_IRQHandler( hAudioOutI2s.hdmatx );
}


/**
  * @brief  This function handles ADC DMA interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel1_IRQHandler( void )
{
    HAL_DMA_IRQHandler( hAudioInAdc.DMA_Handle );
}
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
