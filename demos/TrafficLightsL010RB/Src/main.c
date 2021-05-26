/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "UVWMonitor.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void fatal_error(); // Declaration only

/** Monitoring **/
uint32_t currentAPValues = 0; // Atomic propositions for monitoring;
// Bits 0-1: First traffic light
// Bits 2-3: Second traffic light
// Bits 4-5: Third traffic light
// Bits 6-7: Fourth traffic light
// Bits   8: Button A

void logViolationExplanation(uint32_t dfaState,void *violationBuffer,uint32_t sizeBuffer) {
  char text[256];
  snprintf(text,256,"Violation in DFA state %d %d ",(int)dfaState,(int)sizeBuffer);
  // Hex print
  int pos = strlen(text);
  for (uint32_t index=0;index<sizeBuffer;index++) {
    text[pos] = "0123456789ABCDEF"[((uint8_t*)violationBuffer)[index]/16];
    text[pos+1] = "0123456789ABCDEF"[((uint8_t*)violationBuffer)[index]%16];
    pos+=2;
    if (pos>250) fatal_error();
  }
  text[pos] = '\n';
  text[pos+1] = 0;
  HAL_UART_Transmit(&huart2,(uint8_t*)text,strlen(text),10000);
}


void logLivenessStarvation(uint32_t uvwState,uint32_t counter,void *violationBuffer,uint32_t sizeBuffer) {
char text[256];
  snprintf(text,256,"Logging starvation in UVW state %d for %d cycles ",(int)uvwState,(int)counter);
  // Hex print
  int pos = strlen(text);
  for (uint32_t index=0;index<sizeBuffer;index++) {
    text[pos] = "0123456789ABCDEF"[((uint8_t*)violationBuffer)[index]/16];
    text[pos+1] = "0123456789ABCDEF"[((uint8_t*)violationBuffer)[index]%16];
    pos+=2;
    if (pos>250) fatal_error();
  }
  text[pos] = '\n';
  text[pos+1] = 0;
  HAL_UART_Transmit(&huart2,(uint8_t*)text,strlen(text),10000);



}



void updateButtonAPs() {
  if (GPIOA->IDR & 2) {
    currentAPValues &= ~256;
  } else {
    currentAPValues |= 256;
  }
  monitorUpdate(currentAPValues);
}

void setLEDs(uint8_t val) {

  val = ~val;

  if (val & 1) {
    GPIOA->ODR |= GPIO_PIN_5;
  } else {
    GPIOA->ODR &= ~GPIO_PIN_5;
  }

  if (val & 2) {
    GPIOA->ODR |= GPIO_PIN_6;
  } else {
    GPIOA->ODR &= ~GPIO_PIN_6;
  }

  if (val & 4) {
    GPIOA->ODR |= GPIO_PIN_7;
  } else {
    GPIOA->ODR &= ~GPIO_PIN_7;
  }

  if (val & 8) {
    GPIOB->ODR |= GPIO_PIN_6;
  } else {
    GPIOB->ODR &= ~GPIO_PIN_6;
  }

}

void fatal_error() {
  // Flash all LEDs
  while(1) {
    uint32_t ticks = HAL_GetTick();
    setLEDs(15);
    while (HAL_GetTick()-ticks<500) {};
    setLEDs(0);
    while (HAL_GetTick()-ticks<1000) {};
  }
}

#define WRITE_PIN_DISP_CS(v) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,v);
#define WRITE_PIN_DISP_CK(v) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,v);
#define WRITE_PIN_DISP_DO(v) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,v);

const uint8_t segmap [] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80 ,0x90};
const uint8_t segsel [] = {0xf1, 0xf2, 0xf4, 0xf8};
const uint8_t dead [] = {0xa1, 0x86, 0x88, 0xa1 };

void displayShiftOut(uint8_t data) {
  for (int i=0;i<8;i++) {
    WRITE_PIN_DISP_DO(data & 128?GPIO_PIN_SET:GPIO_PIN_RESET);
    data = data << 1;
    WRITE_PIN_DISP_CK(GPIO_PIN_SET);
    volatile int m = 0;
    for (volatile int k=0;k<10;k++) { m+=k; }
    WRITE_PIN_DISP_CK(GPIO_PIN_RESET);
  }



}


void displayNum(uint16_t num) {

  if (num>=9999) {
    for (uint8_t i=0;i<4;i++) {
      WRITE_PIN_DISP_CS(GPIO_PIN_RESET);
      displayShiftOut(dead[3-i]);
      displayShiftOut(segsel[3-i]);
      num = num / 10;
      WRITE_PIN_DISP_CS(GPIO_PIN_SET);
    }

  } else {
    for (uint8_t i=0;i<4;i++) {
      WRITE_PIN_DISP_CS(GPIO_PIN_RESET);
      displayShiftOut(segmap[num % 10]);
      displayShiftOut(segsel[3-i]);
      num = num / 10;
      WRITE_PIN_DISP_CS(GPIO_PIN_SET);
    }
  }
  WRITE_PIN_DISP_CS(GPIO_PIN_RESET);
  displayShiftOut(0x00);
  WRITE_PIN_DISP_CS(GPIO_PIN_SET);
}


/* Traffic Light Display */
const uint8_t trafficSegMap [] = {0xff-80, 64+128, 130, 0x99 ,0xff-64};


void displayTL(uint8_t *modes) {
  for (uint8_t i=0;i<4;i++) {
    WRITE_PIN_DISP_CS(GPIO_PIN_RESET);
    
    // Sanity check, check APs
    if (modes[i]>=4) fatal_error();
    currentAPValues &= ~(3 << (2*i));
    currentAPValues |= modes[i] << (2*i);
    displayShiftOut(trafficSegMap[modes[i]]);
    displayShiftOut(segsel[i]);
    WRITE_PIN_DISP_CS(GPIO_PIN_SET);
  }
  monitorUpdate(currentAPValues);
}



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Transmit(&huart2,(uint8_t*)"\nBegin execution.\n",18,10000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t modes[4] = {0,0,0,0};
  setLEDs(0);

  int currentMode = 0;
  int nextDelay = 1000;
  uint32_t lastTick = HAL_GetTick();

  while (1)
  {
    /* USER CODE END WHILE */
    while ((HAL_GetTick()-lastTick)<nextDelay) {
      displayTL(modes);

      // Button for emergency van
      updateButtonAPs();
      if (!(GPIOA->IDR & 2)) {
        if (currentMode<10) {
          currentMode = 10;
          nextDelay = 500; // Faster backup
        }
      }


    }
    lastTick = HAL_GetTick();

    switch(currentMode) {
      case 0:
        modes[0] = 1;
        modes[2] = 1;
        currentMode = 1;
        nextDelay = 1000;
        break;
      case 1:
        modes[0] = 2;
        modes[2] = 2;
        currentMode = 2;
        nextDelay = 5000;
        break;
      case 2:
        modes[0] = 3;
        modes[2] = 3;
        currentMode = 3;
        nextDelay = 1000;
        break;
      case 3:
        modes[0] = 0;
        modes[2] = 0;
        modes[1] = 1;
        modes[3] = 1;
        currentMode = 4;
        nextDelay = 1000;
        break;
      case 4:
        modes[1] = 2;
        modes[3] = 2;
        currentMode = 5;
        nextDelay = 5000;
        break;
      case 5:
        modes[1] = 3;
        modes[3] = 3;
        currentMode = 6;
        nextDelay = 1000;
        break;
      case 6:
        modes[1] = 0;
        modes[3] = 0;
        modes[0] = 1;
        modes[2] = 1;
        currentMode = 1;
        nextDelay = 1000;
        break;
      case 10:
      case 11:
      case 12:
      case 13:
        // Switching to emergency mode
        // TOWARS GREEN
        if ((modes[1]==0) && (modes[3]==0)) {
          if (modes[0]==3) modes[0] = 0;  
          else if (modes[0]==1) modes[0] = 2;
          else if (modes[0]==0) modes[0] = 1;
        }
        // Y -> R
        if (modes[1]==3) modes[1] = 0;
        if (modes[2]==3) modes[2] = 0;
        if (modes[3]==3) modes[3] = 0;
        // G -> Y
        if (modes[1]==2) modes[1] = 3;
        // Artificial bug
        if (modes[2]>0) modes[2] = 3;
        // Correct version
        // if (modes[2]==2) modes[2] = 3;
        if (modes[3]==2) modes[3] = 3;
        // Orange -> G
        if (modes[1]==1) modes[1] = 2;
        if (modes[2]==1) modes[2] = 2;
        if (modes[3]==1) modes[3] = 2;
        currentMode++;
        nextDelay = 1000;
        break;
      case 14:
        if ((GPIOA->IDR & 2)) {
          currentMode = 0;
        }
        updateButtonAPs();
        nextDelay = 1000;
        break;

    }

    // Two bugs: 
    // - When starting the button press with RORO, the traffic light gets stuck at ORRR
    // - When starting the button press with GRGR, we get G->O->G on the first traffic light

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
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
  __disable_irq();
  while (1)
  {
  }
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
