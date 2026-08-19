#include "Peripherals/UartPeripheral.hpp"

UartPeripheral::UartPeripheral(HalHandle* huart) : huart_(huart)
{
    for(auto& entry : table_)
    {
        if(entry == nullptr)
        {
            entry = this;
            break;
        }
    }
}

UartPeripheral* UartPeripheral::find(HalHandle* huart)
{
    for(auto* entry : table_)
    {
        if(entry != nullptr && entry->handle() == huart)
        {
            return entry;
        }
    }
    return nullptr;
}

void HAL_UARTEx_RxEventCallback(UartPeripheral::HalHandle *huart, uint16_t Size)
{
    if (UartPeripheral* peripheral = UartPeripheral::find(huart))
    {
        peripheral->onRxEvent(Size);
    }
}

void HAL_UART_TxCpltCallback(UartPeripheral::HalHandle *huart)
{
    if (UartPeripheral* peripheral = UartPeripheral::find(huart))
    {
        peripheral->onTxComplete();
    }
}