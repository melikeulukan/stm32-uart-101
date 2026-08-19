#pragma once

// Clock config + GPIO/DMA/RTC/USART bring-up. HAL_Init() sonrasi, RTOS baslamadan once bir kere cagrilir.
void HardwareInit_Run();
