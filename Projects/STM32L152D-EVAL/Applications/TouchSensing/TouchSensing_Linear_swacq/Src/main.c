/**
  ******************************************************************************
  * @file    TouchSensing/TouchSensing_Linear_swacq/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright � 2017 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license SLA0044,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32L1xx_HAL_Examples
  * @{
  */

/** @addtogroup TouchSensing_Linear_swacq
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config( void );
static void Error_Handler( void );
void Process_Sensors( tsl_user_status_t status );

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main( void )
{
    tsl_user_status_t tsl_status;

    /* STM32L1xx HAL library initialization:
         - Configure the Flash prefetch
         - Systick timer is configured by default as source of time base, but user
           can eventually implement his proper time base source (a general purpose
           timer for example or other time source), keeping in mind that Time base
           duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
           handled in milliseconds basis.
         - Set NVIC Group Priority to 4
         - Low Level Initialization
       */
    HAL_Init();

    /* Configure LEDs */
    BSP_LED_Init( LED1 );
    BSP_LED_Init( LED2 );
    BSP_LED_Init( LED3 );
    BSP_LED_Init( LED4 );

    /* Configure the system clock to 32 MHz */
    SystemClock_Config();

    /* Initialize the STMTouch driver */
    tsl_user_Init();

    /* Just to indicate the fw is alive... */
    BSP_LED_On( LED1 );
    BSP_LED_On( LED2 );
    BSP_LED_On( LED3 );
    BSP_LED_On( LED4 );
    HAL_Delay( 200 );
    BSP_LED_Off( LED1 );
    BSP_LED_Off( LED2 );
    BSP_LED_Off( LED3 );
    BSP_LED_Off( LED4 );

    /* Infinite loop */
    while( 1 )
    {
        /* Execute STMTouch Driver state machine */
        tsl_status = tsl_user_Exec();

        if( tsl_status != TSL_USER_STATUS_BUSY )
        {
            Process_Sensors( tsl_status );
        }
    }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 32000000
  *            HCLK(Hz)                       = 32000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSI Frequency(Hz)              = 16000000
  *            PLLMUL                         = 12
  *            PLLDIV                         = 3
  *            Flash Latency(WS)              = 1
  * @retval None
  */
void SystemClock_Config( void )
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

    /* Enable HSE Oscillator and Activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState            = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL12;
    RCC_OscInitStruct.PLL.PLLDIV          = RCC_PLL_DIV3;

    if( HAL_RCC_OscConfig( &RCC_OscInitStruct ) != HAL_OK )
    {
        Error_Handler();
    }

    /* Set Voltage scale1 as MCU will run at 32MHz */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG( PWR_REGULATOR_VOLTAGE_SCALE1 );

    /* Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 */
    while( __HAL_PWR_GET_FLAG( PWR_FLAG_VOS ) != RESET ) {};

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
    clocks dividers */
    RCC_ClkInitStruct.ClockType = ( RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 );

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;

    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;

    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if( HAL_RCC_ClockConfig( &RCC_ClkInitStruct, FLASH_LATENCY_1 ) != HAL_OK )
    {
        Error_Handler();
    }
}
/**
  * @brief  Display sensors information on LEDs
  * @param  status TSL user status
  * @retval None
  */
void Process_Sensors( tsl_user_status_t status )
{
    BSP_LED_Off( LED1 );
    BSP_LED_Off( LED2 );
    BSP_LED_Off( LED3 );
    BSP_LED_Off( LED4 );

    if( MyLinRots[0].p_Data->Position >= 1 )
    {
        BSP_LED_On( LED1 );
    }

    if( MyLinRots[0].p_Data->Position >= 5 )
    {
        BSP_LED_On( LED2 );
    }

    if( MyLinRots[0].p_Data->Position >= 9 )
    {
        BSP_LED_On( LED3 );
    }

    if( MyLinRots[0].p_Data->Position >= 12 )
    {
        BSP_LED_On( LED4 );
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler( void )
{
    /* User may add here some code to deal with this error */
    BSP_LED_Off( LED1 );
    BSP_LED_Off( LED2 );
    BSP_LED_Off( LED4 );

    while( 1 )
    {
        BSP_LED_Toggle( LED3 );
        HAL_Delay( 100 );
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed( uint8_t *file, uint32_t line )
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    BSP_LED_Off( LED1 );
    BSP_LED_Off( LED2 );
    BSP_LED_Off( LED4 );

    while( 1 )
    {
        BSP_LED_Toggle( LED3 );
        HAL_Delay( 100 );
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
