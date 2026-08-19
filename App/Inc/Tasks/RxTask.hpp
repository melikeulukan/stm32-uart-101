#pragma once
#include "Task.hpp"
#include "main.h"
#include "task.h"
#include <cstdio>

// debugUart_: alinan veriyi nereye raporladigimiz (log ciktisi), receive mekanizmasiyla ilgisi yok.
template<typename Transport>
class RxTask : public Task {
    private:
        Transport& transport_;
        UART_HandleTypeDef* debugUart_;
        uint32_t rxCounter_{0};

    public:
        explicit RxTask(Transport& transport, UART_HandleTypeDef* debugUart)
            : Task("RxTask", 512, osPriorityAboveNormal), transport_(transport), debugUart_(debugUart) {

        }

        void operator()() override {

            while(true)
            {
                uint16_t receivedLen;
                const uint8_t* packet = transport_.receive(receivedLen);
                rxCounter_++;

                char status_msg[128];
                int len = snprintf(status_msg, sizeof(status_msg), "[packet %lu] (len: %u) - usart2 received: %s", rxCounter_, receivedLen, packet);
                HAL_UART_Transmit(debugUart_, (uint8_t*)status_msg, len, HAL_MAX_DELAY);

                UBaseType_t freeStack = uxTaskGetStackHighWaterMark(NULL); // NULL = kendi task'ı
                char stack_msg[64];
                int stackLen = snprintf(stack_msg, sizeof(stack_msg), "[RxTask] free stack: %lu words (%lu bytes)\r\n", (unsigned long)freeStack, (unsigned long)(freeStack * 4));
                HAL_UART_Transmit(debugUart_, (uint8_t*)stack_msg, stackLen, HAL_MAX_DELAY);

                osDelay(1000);
            }
        };

};
