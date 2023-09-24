#include "pwmPin.hpp"

#include <hardware/pwm.h>

PwmPin::PwmPin
( 
    const uint8_t gpioPin, 
    const uint16_t initFreq, 
    const uint8_t initDuty, 
    const bool enable
)
:
mPin(gpioPin),
mSlice(pwm_gpio_to_slice_num(gpioPin)),
mChan(pwm_gpio_to_channel(gpioPin)),
mFreq(initFreq),
mDuty(initDuty)
{
    gpio_set_function(mPin, GPIO_FUNC_PWM);
    setFreq(initFreq);
    setDuty(initDuty);
    enablePin(enable);
}

void PwmPin::enablePin(const bool shouldEnable)
{
    pwm_set_enabled(mSlice, shouldEnable);
}

void PwmPin::setFreq(const uint16_t freq)
{
    mFreq = freq;
    uint32_t divider16 = mClockFreq / mFreq / 4096 + 
                            (mClockFreq % (mFreq * 4096) != 0);
    if (divider16 / 16 == 0)
    {
        divider16 = 16;
    }
    
    mWrap = mClockFreq * 16 / divider16 / mFreq - 1;
    pwm_set_clkdiv_int_frac(mSlice, divider16/16,
                                        divider16 & 0xF);
    pwm_set_wrap(mSlice, mWrap);
}

void PwmPin::setDuty(const uint8_t percent)
{
    if(percent <= 100)
    {
        mDuty = percent;

        pwm_set_chan_level(mSlice, mChan, mWrap * mDuty / 100);
    }
}