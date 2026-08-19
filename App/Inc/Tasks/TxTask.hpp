#pragma once
#include "Task.hpp"
#include "UartPeripheral.hpp"
#include <cstring>
#include <cstdio>

class TxTask : public Task{
    private:
        UartPeripheral* uart_;
        osSemaphoreId_t txDoneSem_;
        char buffer_[64];
        uint8_t simStep_{0};

    public:
        explicit TxTask(UartPeripheral* uart, osSemaphoreId_t txDoneSem)
            : Task("txTask", 128, osPriorityNormal), uart_(uart), txDoneSem_(txDoneSem) {

        }

        void operator()() override {

            while(true)
            {//messages of different length
                if(simStep_==0)
                {
                    sprintf(buffer_,  "short\r\n");
                }
                else if(simStep_==1)
                {
                    sprintf(buffer_, "this is a longer message\r\n");
                }
                else if(simStep_==2)
                {
                    sprintf(buffer_, "this is appearently a long long message, like really long\r\n");
                }
                simStep_++;

                if(simStep_>2)
                {
                    simStep_=0;
                }

                HAL_UART_Transmit_DMA(uart_->handle(), (uint8_t*)buffer_, strlen(buffer_));
                osSemaphoreAcquire(txDoneSem_, osWaitForever);

                osDelay(1000);
            }
        };
};