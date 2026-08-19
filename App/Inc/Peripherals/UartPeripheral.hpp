#pragma once
#include "main.h"
#include <cstddef>
#include <cstdint>
#include <array>

class UartPeripheral {
    public:
        using HalHandle = UART_HandleTypeDef;

        explicit UartPeripheral(HalHandle* huart);
        virtual ~UartPeripheral() = default;

        UartPeripheral(const UartPeripheral&) = delete;
        UartPeripheral& operator=(const UartPeripheral&) = delete;  

        virtual void onTxComplete() {}
        virtual void onRxEvent(uint16_t size) {}
        virtual void onError(std::uint32_t errorCode) {}

        HalHandle* handle() const { return huart_; }

        static UartPeripheral* find(HalHandle* huart);

    protected:
        HalHandle* huart_;

        // Ham HAL cagrilarina kisa, okunakli isimler.
        void transmitDma(const uint8_t* data, std::size_t len)
        {
            HAL_UART_Transmit_DMA(huart_, data, static_cast<uint16_t>(len));
        }

        void receiveDma(uint8_t* buffer, std::size_t len)
        {
            HAL_UARTEx_ReceiveToIdle_DMA(huart_, buffer, static_cast<uint16_t>(len));
        }

        void stopDma()
        {
            HAL_UART_DMAStop(huart_);
        }

    private:
        static constexpr std::size_t MAX_UARTS = 3;
        static inline std::array<UartPeripheral*, MAX_UARTS> table_{};
};