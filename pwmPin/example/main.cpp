/**
 * @brief Example program that uses the PwmPin library to fade an LED
 *        in and out.
 */
#include <pico/time.h>

#include "pwmPin.hpp"

// LED S pin connected to pin 4(GPIO 2)
const uint8_t LED_PIN = 2;

int main()
{
    PwmPin led(LED_PIN);

    uint16_t level = 0;
    int step = 10;

    while(true)
    {   
        led.setDuty(level);
        sleep_ms(100);

        if(level < 10)
            step = 10;
        else if(level > 90)
            step = -10;

        level += step;
    }

    return 0;
}