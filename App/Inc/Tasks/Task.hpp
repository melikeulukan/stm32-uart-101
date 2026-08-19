#pragma once
#include "cmsis_os2.h"
#include <cstdint>

class Task{
    public:
        explicit Task(const char* name, uint32_t StackDepth, osPriority_t priority);
        virtual ~Task() = default;

        Task(const Task&) = delete;
        Task& operator=(const Task&) = delete;

        void start();

        virtual void operator()()=0;
    private:
        const char* name_;
        uint32_t StackDepth_;
        osPriority_t priority_;
        osThreadId_t handle_{nullptr};

        static void trampoline(void* argument);
};