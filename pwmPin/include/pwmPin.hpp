#pragma once

#include <pico/stdlib.h>

/**
 * @brief Control PWM pin for rp2040.
 */
class PwmPin
{
public:

    /**
     * @brief Construct PwmPin object.
     * 
     * @param gpioPin - GPIO pin number
     * @param initFreq - Initial frequency (effects both channels for PWM generator)
     * @param initDuty - Initial duty cycle (percent)
     * @param enable - If true, enable PWM for pin
     */
    PwmPin( const uint8_t gpioPin, 
            const uint16_t initFreq = 0xFFFF, 
            const uint8_t initDuty = 0, 
            const bool enable = true);

    /**
     * @brief Enable/Disable PWM pin
     * 
     * @param shouldEnable - If true enable pin, if false disable pin
     */
    void enablePin(const bool shouldEnable = true);

    /**
     * @brief Set frequency of PWM generator (Effects both pins of PWM generator)
     * 
     * @param freq - Frequency (Hz)
     */
    void setFreq(const uint16_t freq);
    
    /**
     * @brief Get PWM generator frequency
     * 
     * @return uint16_t - Frequency (Hz)
     */
    uint16_t getFreq()
    { return mFreq; }

    /**
     * @brief Set duty cycle of PWM pin
     * 
     * @param percent - Duty cycle 0 - 100
     */
    void setDuty(const uint8_t percent);

    /**
     * @brief Get duty cycle of PWM pin
     * 
     * @return uint8_t - Duty cycle (%)
     */
    uint8_t getDuty()
    { return mDuty; }

    /**
     * @brief Set the system clock frequency used to calculate PWM parameters
     * 
     * @param clockFreq - System clock frequency (Hz)
     */
    void setClockFreq(const uint32_t clockFreq)
    { mClockFreq = clockFreq; }

    /**
     * @brief Get the system clock frequency being used for PWM calculations
     * 
     * @return uint32_t - System clock frequency (Hz)
     */
    uint32_t getClockFreq()
    { return mClockFreq; }

protected:

    /// GPIO Pin
    uint8_t mPin;
    /// PWM generator
    uint mSlice;
    /// PWM channel
    uint mChan;
    /// PWM frequency (Hz)
    uint16_t mFreq;
    /// PWM Duty Cycle (%)
    uint8_t mDuty;
    /// Wrap value for PWM counter
    uint32_t mWrap;
    /// System Clock Frequency (Hz)
    uint32_t mClockFreq = 125'000'000;

}; // End class PwmPin