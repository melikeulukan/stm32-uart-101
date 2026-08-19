
#include "main.h"
#include "cmsis_os.h"

#include "task.h"

#include "HardwareInit.hpp"
#include "Peripherals/UartPeripheral.hpp"
#include "Peripherals/UartSendTransport.hpp"
#include "Peripherals/UartReceiveTransport.hpp"
#include "Tasks/DefaultTask.hpp"
#include "Tasks/TxTask.hpp"
#include "Tasks/RxTask.hpp"

#include <string.h>
#include <stdio.h>


/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart2_rx;

osMessageQueueId_t rxQueueHandle;
osSemaphoreId_t txDoneSemHandle;

int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Clock config + GPIO/DMA/RTC/USART bring-up */
  HardwareInit_Run();

  /* Init scheduler */
  osKernelInitialize();

  txDoneSemHandle = osSemaphoreNew(1,0,NULL);

  if(NULL == txDoneSemHandle)
  {
     HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD2_Pin|LD3_Pin, GPIO_PIN_SET);
  }

  rxQueueHandle = osMessageQueueNew(8, sizeof(uint16_t), NULL);
  //Capacity: 8 messages, Size, Attr: default memory allocation

  if (rxQueueHandle == NULL)
  {
    HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD2_Pin|LD3_Pin, GPIO_PIN_SET);
  }

  static UartSendTransport uart1(&huart1, txDoneSemHandle);
  static UartReceiveTransport uart2(&huart2, &hdma_usart2_rx, rxQueueHandle);
  uart2.startListening();

  
  static DefaultTask defaultTask; // static olmalı, yoksa main() bittiğinde yok olur
  static TxTask<UartSendTransport> txTask(uart1);
  static RxTask<UartReceiveTransport> rxTask(uart2, &huart3);

  defaultTask.start();
  txTask.start();
  rxTask.start();


  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
  if (strcmp(pcTaskName, "TxTask") == 0)
  {
    HAL_GPIO_WritePin(GPIOB, LD1_Pin, GPIO_PIN_SET);   // yeşil = TxTask taştı
  }
  else if (strcmp(pcTaskName, "RxTask") == 0)
  {
    HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET);   // mavi = RxTask taştı
  }
  else
  {
    HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET);   // kırmızı = defaultTask ya da başka
  }
  while(1) { }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }
}

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
#ifdef USE_FULL_ASSERT
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
