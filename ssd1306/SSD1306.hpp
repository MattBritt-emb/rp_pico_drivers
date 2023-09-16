#pragma once

#include <functional>
#include <cstdint>

/**
 * @brief SSD1306 OLED Display Driver
 *        
 * The constructor takes function objects to abstract the underlying
 * hardware calls.
 * 
 */
class SSD1306
{

public:

    /**
     * @brief Construct a new SSD1306 object
     * 
     * @param writeFunc - Function to send data to SSD1306;
     *                    Signature:
     *                      pData - pointer to data being written
     *                      size - size of data being written
     * 
     * @param setPinFunc - Function to set pin high/low
     *                     Signature:
     *                      pin - pin to set
     *                      isOn - if true set pin on/high otherwise set pin off/low 
     * @param delayMsFunc - Function to delay number of milliseconds
     *                     Signature:
     *                      delayMs - Milliseconds to delay 
     * @param dcPin - Data/Command pin number
     * @param resetPin - Reset pin number
     * @param width - Screen width
     * @param height - Screen height
     */
    SSD1306
    (
        std::function<void(const uint8_t* pData, const size_t size)> writeFunc,
        std::function<void(const uint8_t pin, const bool isOn)> setPinFunc,
        std::function<void(const uint32_t delayMs)> delayMsFunc,
        const uint8_t dcPin,
        const uint8_t resetPin,
        const size_t width, 
        const size_t height
    );

    /**
     * @brief Turn display On/Off
     * 
     * @param isOn - If true turn display on, if false turn display off 
     */
    void setDisplayOn(const bool isOn);

    /**
     * @brief Reset SSD1306 to defaults
     */
    void reset();

    /**
     * @brief Display RAM or Test(all pixels on)
     * 
     * @param isTest - If true, display all pixels on, if false display RAM
     */
    void setMode(const bool isTest);

    /**
     * @brief Set the memory addressing mode
     * 
     * @param mode - 0b00(horizontal), 0b01(vertical), 0b10(page addressing)
     * 
     * @return true if valid mode; false if invalid mode
     */
    bool setMemAddrMode(const uint8_t mode);

    /**
     * @brief Set the starting row in RAM
     * 
     * @param line - RAM start line (0 - 63)
     * @return true if line valid, false if invalid
     */
    bool setStartLine(const uint8_t line);

    /**
     * @brief Set segment remap
     * 
     * @param isReversed - if true column 127 is mapped to SEG0, 
     *                     if false column 0 is mapped to SEG0
     */
    void setSegRemap(const bool isReversed);

    /**
     * @brief Set MUX ratio (height?)
     * 
     * @param ratio - MUX ratio (15 - 63) 
     * @return true if ratio valid, false if invalid
     */
    bool setMuxRatio(const uint8_t ratio);

    /**
     * @brief Set COM output direction
     * 
     * @param isReversed - if true scan from COM[mux ratio] to COM[0],
     *                     if false scan from COM[0] to COM[mux ratio]
     */
    void setComDir(const bool isReversed);

    /**
     * @brief Set the Display Offset (vertical shift)
     * 
     * @param offset - shift offset (0 - 63)
     * @return true if offset valid, false if invalid
     */
    bool setDisplayOffset(const uint8_t offset);

    /**
     * @brief Set the COM pin HW config
     * 
     * @param isAlternative - if true use alternative COM pin configuration,
     *                        if false use sequential COM pin configuration
     * @param enableRemap - if true enable COM left/right remap,
     *                      if false disable COM remap
     */
    void setComPinConfig(const bool isAlternative, const bool enableRemap);

    /**
     * @brief Set oscillator parameters
     * 
     * @param divRatio - clock divide ratio (0 - 15)
     * @param freq - frequency (0 - 15);
     * @return true if divRatio and freq valid, false if either invalid
     */
    bool setOscillator(const uint8_t divRatio, const uint8_t freq);

    /**
     * @brief Set pre-charge period
     * 
     * @param phase1Period - Number of clocks, cannot be 0
     * @param phase2Period - Number of clocks, cannot be 0
     * @return true if phase1Period and phase2Period valid,
     *         false if either invalid
     */
    bool setPreChargePeriod(const uint8_t phase1Period, const uint8_t phase2Period);

    /**
     * @brief Set Vcomh regulator output
     * 
     * @param level - 0b00(0.65xVcc), 0b01(0.77xVcc), 0b11(0.83xVcc)
     * @return true if level valid, false if invalid
     */
    bool setVcomDeselectLevel(const uint8_t level);

    /**
     * @brief Set contrast level
     * 
     * @param level
     */
    void setContrast(const uint8_t level);

    /**
     * @brief Set screen inversion
     * 
     * @param isInverted - if true screen will be inverted (0 pixels will 
     *                      be displayed instead of 1),
     *                      if false screen will be 'normal'
     */
    void setInvert(const bool isInverted);

    /**
     * @brief Enable/Disable charge pump
     * 
     * @param isEnabled - if true enable charge pump,
     *                    if false, disable
     */
    void enableChargePump(const bool isEnabled);

    void writeData(const uint8_t* pData, const size_t size);
protected:

    void init();

    void writeCmd(const uint8_t cmd);

    std::function<void(const uint8_t*, const size_t)> mWrite;
    std::function<void(const uint8_t pin, const bool)> mSetPin;
    std::function<void(const uint32_t)> mDelayMs;

    const uint8_t mDcPin;
    const uint8_t mResetPin;

    const size_t mWidth;
    const size_t mHeight;

}; // End class SSD1306