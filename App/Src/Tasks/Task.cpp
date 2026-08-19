#include "Tasks/Task.hpp"

Task::Task(const char* name, uint32_t StackDepth, osPriority_t priority)
    : name_(name), StackDepth_(StackDepth), priority_(priority){
}

void Task::start()
{
    osThreadAttr_t attr = {};
    attr.name = name_;
    attr.stack_size = StackDepth_ * sizeof(uint32_t);
    attr.priority = priority_;

    handle_ = osThreadNew(trampoline, this, &attr);
}

void Task::trampoline(void* argument)
{
    auto* self = static_cast<Task*>(argument);
    
    if(self != nullptr)
    {
        (*self)();
    }

    osThreadTerminate(osThreadGetId());
}