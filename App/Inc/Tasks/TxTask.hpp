#pragma once
#include "Task.hpp"
#include <cstring>
#include <cstdio>

template<typename Transport>
class TxTask : public Task{
    private:
        Transport& transport_;
        char buffer_[64];
        uint8_t simStep_{0};

    public:
        explicit TxTask(Transport& transport)
            : Task("TxTask", 128, osPriorityNormal), transport_(transport) {

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

                transport_.send(reinterpret_cast<const uint8_t*>(buffer_), strlen(buffer_));

                osDelay(1000);
            }
        };
};
