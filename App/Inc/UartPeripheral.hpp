#pragma once
#include "main.h"
#include <cstddef>
#include <cstdint>
#include <array>

class UartPeripheral {
    public:
        explicit UartPeripheral(UART_HandleTypeDef* huart);
        virtual ~UartPeripheral() = default;

        UartPeripheral(const UartPeripheral&) = delete;
        UartPeripheral& operator=(const UartPeripheral&) = delete;  

        virtual void onTxComplete() {}
        virtual void onRxEvent(uint16_t size) {}
        virtual void onError(std::uint32_t errorCode) {}

        UART_HandleTypeDef* handle() const { return huart_; }

        static UartPeripheral* find(UART_HandleTypeDef* huart);

    protected:
        UART_HandleTypeDef* huart_;
    
    private:
        static constexpr std::size_t MAX_UARTS = 3;
        static inline std::array<UartPeripheral*, MAX_UARTS> table_{};
};