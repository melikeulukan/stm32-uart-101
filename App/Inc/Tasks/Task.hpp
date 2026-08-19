#pragma once
#include "cmsis_os2.h"
#include <cstdint>

class Task{
    public:
        explicit Task(const char* name, uint32_t StackDepth, osPriority_t priority);
        virtual ~Task() = default;

        Task(const Task&) = delete; //copy constructor disabled
        Task& operator=(const Task&) = delete; //copy assignment operator disabled

        void start();

        virtual void operator()()=0; //Pure Virtual Function
    private:
        const char* name_;
        uint32_t StackDepth_;
        osPriority_t priority_;
        osThreadId_t handle_{nullptr};

        static void trampoline(void* argument);
};