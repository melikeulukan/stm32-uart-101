#pragma once
#include "UartPeripheral.hpp"
#include "cmsis_os2.h"
#include <cstddef>

class UartTransport : public UartPeripheral {
    public:
        UartTransport(UART_HandleTypeDef* huart, osSemaphoreId_t txDoneSem)
            : UartPeripheral(huart), txDoneSem_(txDoneSem) {
        }

        void send(const uint8_t* data, std::size_t len)
        {
            HAL_UART_Transmit_DMA(handle(), data, static_cast<uint16_t>(len));
            osSemaphoreAcquire(txDoneSem_, osWaitForever);
        }

    private:
        void onTxComplete() override
        {
            osSemaphoreRelease(txDoneSem_);
        }

        osSemaphoreId_t txDoneSem_;
};
