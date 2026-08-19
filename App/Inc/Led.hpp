#pragma once
#include "main.h"

#ifdef __cplusplus

class Led {
public:
    Led(GPIO_TypeDef* port, uint16_t pin) : port_(port), pin_(pin) {}

    void toggle() { HAL_GPIO_TogglePin(port_, pin_); }

    // functor: led() demek, led.toggle() demekle aynı
    void operator()() { toggle(); }

private:
    GPIO_TypeDef* port_;
    uint16_t pin_;
};

#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

void App_LedTest(void);

#ifdef __cplusplus
}
#endif