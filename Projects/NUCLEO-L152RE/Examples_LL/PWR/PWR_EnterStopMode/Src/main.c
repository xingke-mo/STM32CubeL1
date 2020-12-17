/**
  ******************************************************************************
  * @file    Examples_LL/PWR/PWR_EnterStopMode/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to  enter and exit the STOP mode
  *          through the STM32L1xx PWR LL API.
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

/** @addtogroup STM32L1xx_LL_Examples
  * @{
  */

/** @addtogroup PWR_EnterStopMode
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void     SystemClock_Config( void );
void     Configure_PWR( void );
void     LED_Init( void );
void     LED_Off( void );
void     LED_Blinking_5s( void );
void     EnterSTOPMode( void );

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main( void )
{
    /* Configure the system clock to 32 MHz */
    SystemClock_Config();

    /* Initialize LED2 */
    LED_Init();

    /* Configure Power IP */
    Configure_PWR();

    /* Led blinking during 5s in RUN mode */
    LED_Blinking_5s();

    /* Switch OFF LED2 */
    LED_Off();

    /* Enter STOP mode */
    EnterSTOPMode();

    /* Here Device is in STOP mode */

    /* Infinite loop */
    while( 1 )
    {
    }
}

/**
  * @brief  Initialize LED2.
  * @param  None
  * @retval None
  */
void LED_Init( void )
{
    /* Enable the LED2 Clock */
    LED2_GPIO_CLK_ENABLE();

    /* Configure IO in output push-pull mode to drive external LED2 */
    LL_GPIO_SetPinMode( LED2_GPIO_PORT, LED2_PIN, LL_GPIO_MODE_OUTPUT );
    /* Reset value is LL_GPIO_OUTPUT_PUSHPULL */
    //LL_GPIO_SetPinOutputType(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    /* Reset value is LL_GPIO_SPEED_FREQ_LOW */
    //LL_GPIO_SetPinSpeed(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_SPEED_FREQ_LOW);
    /* Reset value is LL_GPIO_PULL_NO */
    //LL_GPIO_SetPinPull(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_PULL_NO);
}

/**
  * @brief  Turn-off LED2.
  * @param  None
  * @retval None
  */
void LED_Off( void )
{
    /* Turn LED2 off */
    LL_GPIO_ResetOutputPin( LED2_GPIO_PORT, LED2_PIN );
}

/**
  * @brief  Set LED2 to Blinking mode during 5s.
  * @param  None

  * @retval None
  */
void LED_Blinking_5s( void )
{
    uint32_t i = 0;

    /* Toggle IO in during 5s (25*200ms) */
    for( i = 0; i < 25; i++ )
    {
        LL_GPIO_TogglePin( LED2_GPIO_PORT, LED2_PIN );
        LL_mDelay( 200 );
    }
}

/**
  * @brief  Function to configure and initialize PWR IP.
  * @param  None
  * @retval None
  */
void Configure_PWR( void )
{
    /* Enable Power Clock */
    LL_APB1_GRP1_EnableClock( LL_APB1_GRP1_PERIPH_PWR );

}

/**
  * @brief  Function to configure and enter in STOP Mode.
  * @param  None
  * @retval None
  */
void EnterSTOPMode( void )
{
    LL_GPIO_InitTypeDef gpio_initstruct = {LL_GPIO_PIN_ALL, LL_GPIO_MODE_ANALOG,
                                           LL_GPIO_SPEED_FREQ_HIGH, LL_GPIO_OUTPUT_PUSHPULL,
                                           LL_GPIO_PULL_NO, LL_GPIO_AF_0
                                          };

    /* Set all GPIO in analog state to reduce power consumption,                */
    /* Note: Debug using ST-Link is not possible during the execution of this   */
    /*       example because communication between ST-link and the device       */
    /*       under test is done through UART. All GPIO pins are disabled (set   */
    /*       to analog input mode) including  UART I/O pins.                    */
    LL_AHB1_GRP1_EnableClock( LL_AHB1_GRP1_PERIPH_GPIOA |
                              LL_AHB1_GRP1_PERIPH_GPIOB |
                              LL_AHB1_GRP1_PERIPH_GPIOC |
                              LL_AHB1_GRP1_PERIPH_GPIOD |
                              LL_AHB1_GRP1_PERIPH_GPIOE |
                              LL_AHB1_GRP1_PERIPH_GPIOF |
                              LL_AHB1_GRP1_PERIPH_GPIOG |
                              LL_AHB1_GRP1_PERIPH_GPIOH );

    LL_GPIO_Init( GPIOA, &gpio_initstruct );
    LL_GPIO_Init( GPIOB, &gpio_initstruct );
    LL_GPIO_Init( GPIOC, &gpio_initstruct );
    LL_GPIO_Init( GPIOD, &gpio_initstruct );
    LL_GPIO_Init( GPIOE, &gpio_initstruct );
    LL_GPIO_Init( GPIOF, &gpio_initstruct );
    LL_GPIO_Init( GPIOG, &gpio_initstruct );
    LL_GPIO_Init( GPIOH, &gpio_initstruct );

    LL_AHB1_GRP1_DisableClock( LL_AHB1_GRP1_PERIPH_GPIOA |
                               LL_AHB1_GRP1_PERIPH_GPIOB |
                               LL_AHB1_GRP1_PERIPH_GPIOC |
                               LL_AHB1_GRP1_PERIPH_GPIOD |
                               LL_AHB1_GRP1_PERIPH_GPIOE |
                               LL_AHB1_GRP1_PERIPH_GPIOF |
                               LL_AHB1_GRP1_PERIPH_GPIOG |
                               LL_AHB1_GRP1_PERIPH_GPIOH );

    /** Request to enter STOP mode
      * Following procedure describe in STM32L1xx Reference Manual
      * See PWR part, section Low-power modes, STOP mode
      */
    /* Enable ultra low power mode */
    LL_PWR_EnableUltraLowPower();

    /** Set the regulator to low power before setting MODE_STOP.
      * If the regulator remains in "main mode",
      * it consumes more power without providing any additional feature. */
    LL_PWR_SetRegulModeLP( LL_PWR_REGU_LPMODES_LOW_POWER );

    /* Set STOP mode when CPU enters deepsleep */
    LL_PWR_SetPowerMode( LL_PWR_MODE_STOP );

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    LL_LPM_EnableDeepSleep();

    /* Request Wait For Interrupt */
    __WFI();
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 32000000
  *            HCLK(Hz)                       = 32000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLLMUL                         = 6
  *            PLLDIV                         = 3
  *            Flash Latency(WS)              = 1
  * @retval None
  */
void SystemClock_Config( void )
{
    /* Enable ACC64 access and set FLASH latency */
    LL_FLASH_Enable64bitAccess();;
    LL_FLASH_SetLatency( LL_FLASH_LATENCY_1 );

    /* Set Voltage scale1 as MCU will run at 32MHz */
    LL_APB1_GRP1_EnableClock( LL_APB1_GRP1_PERIPH_PWR );
    LL_PWR_SetRegulVoltageScaling( LL_PWR_REGU_VOLTAGE_SCALE1 );

    /* Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 */
    while( LL_PWR_IsActiveFlag_VOSF() != 0 )
    {
    };

    /* Enable HSI if not already activated*/
    if( LL_RCC_HSI_IsReady() == 0 )
    {
        /* HSI configuration and activation */
        LL_RCC_HSI_Enable();

        while( LL_RCC_HSI_IsReady() != 1 )
        {
        };
    }

    /* Main PLL configuration and activation */
    LL_RCC_PLL_ConfigDomain_SYS( LL_RCC_PLLSOURCE_HSI, LL_RCC_PLL_MUL_6, LL_RCC_PLL_DIV_3 );

    LL_RCC_PLL_Enable();

    while( LL_RCC_PLL_IsReady() != 1 )
    {
    };

    /* Sysclk activation on the main PLL */
    LL_RCC_SetAHBPrescaler( LL_RCC_SYSCLK_DIV_1 );

    LL_RCC_SetSysClkSource( LL_RCC_SYS_CLKSOURCE_PLL );

    while( LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL )
    {
    };

    /* Set APB1 & APB2 prescaler*/
    LL_RCC_SetAPB1Prescaler( LL_RCC_APB1_DIV_1 );

    LL_RCC_SetAPB2Prescaler( LL_RCC_APB2_DIV_1 );

    /* Set systick to 1ms in using frequency set to 32MHz                             */
    /* This frequency can be calculated through LL RCC macro                          */
    /* ex: __LL_RCC_CALC_PLLCLK_FREQ (HSI_VALUE, LL_RCC_PLL_MUL_6, LL_RCC_PLL_DIV_3); */
    LL_Init1msTick( 32000000 );

    /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
    LL_SetSystemCoreClock( 32000000 );
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
       ex: printf("Wrong parameters value: file %s on line %d", file, line) */

    /* Infinite loop */
    while( 1 )
    {
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
