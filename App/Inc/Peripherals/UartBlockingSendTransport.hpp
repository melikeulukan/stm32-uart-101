#pragma once
#include "UartPeripheral.hpp"

class UartBlockingSendTransport : public UartPeripheral {
    public:
        explicit UartBlockingSendTransport(UART_HandleTypeDef* huart)
            : UartPeripheral(huart) {
        }

        void send(const uint8_t* data, std::size_t len)
        {
            HAL_UART_Transmit(huart_, data, static_cast<uint16_t>(len), HAL_MAX_DELAY);
        }
};
