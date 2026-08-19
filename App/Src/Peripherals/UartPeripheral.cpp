#include "Peripherals/UartPeripheral.hpp"

UartPeripheral::UartPeripheral(UART_HandleTypeDef* huart) : huart_(huart)
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

UartPeripheral* UartPeripheral::find(UART_HandleTypeDef* huart)
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