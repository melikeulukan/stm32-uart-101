#include "UartPeripheralTest.hpp"
#include "UartPeripheral.hpp"
#include "main.h"

extern UART_HandleTypeDef huart1;

extern "C" int App_UartPeripheralTest(void)
{
    static UartPeripheral testPeripheral(&huart1);

    UartPeripheral* found = UartPeripheral::find(&huart1);
    return (found == &testPeripheral) ? 1 : 0;
}