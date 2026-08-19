#include "Led.hpp"

extern "C" void App_LedTest(void)
{
    static Led led2(GPIOB, LD2_Pin);
    led2();  // operator() -> toggle()
}