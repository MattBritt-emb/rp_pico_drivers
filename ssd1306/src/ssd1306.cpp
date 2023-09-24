#include "SSD1306.hpp"

SSD1306::SSD1306
(
    std::function<void(const uint8_t*, const size_t)> writeFunc,
    std::function<void(const uint8_t pint, const bool)> setPinFunc,
    std::function<void(const uint32_t)> delayMsFunc,
    const uint8_t dcPin,
    const uint8_t resetPin,
    const size_t width, 
    const size_t height
)
:   mWrite(writeFunc),
    mSetPin(setPinFunc),
    mDelayMs(delayMsFunc),
    mDcPin(dcPin),
    mResetPin(resetPin),
    mWidth(width),
    mHeight(height)
{
    init();
}

void SSD1306::init()
{
    mSetPin(mDcPin, true);

    // Turn off display before configuring
    setDisplayOn(false);

    // Reset display to defaults
    reset();

    // Set memory address mode to horizontal
    setMemAddrMode(1);

    // Set starting line/row to 0
    setStartLine(0);

    // Set reverse segment remap
    setSegRemap(true);

    // Set mux ratio (height?) to 64 lines
    setMuxRatio(63);

    // Reverse COM dir
    setComDir(false);

    // Set display offset to first line
    setDisplayOffset(0);

    // Set COM pin config - alternative com pin, remap disabled
    setComPinConfig(true, false);

    // Set oscillator frequency to 0x8, divide ratio to 0
    setOscillator(0, 0x8);

    // Set pre-charge period, 0x1 for phase 1, 0xF for phase 2
    setPreChargePeriod(0x1, 0xF);

    // Set VCOM deselect level to 0.83 x Vcc
    setVcomDeselectLevel(0b11);

    // Set contrast
    setContrast(0xFF);

    // Display RAM
    setMode(false);

    // Set normal (no invert)
    setInvert(false);
    
    // Enable charge pump
    enableChargePump(true);

    // Turn display on
    setDisplayOn(true);
}

void SSD1306::writeCmd(const uint8_t cmd)
{
    mSetPin(mDcPin, false);
    mWrite(&cmd, sizeof(cmd));
}

void SSD1306::writeData(const uint8_t* pData, const size_t size)
{
    mSetPin(mDcPin, true);
    mWrite(pData, size);
}

void SSD1306::setDisplayOn(const bool isOn)
{
    uint8_t displayCmd = 0xAE;
    displayCmd |= (isOn) ? 0b1 : 0;
    
    writeCmd(displayCmd);
}

void SSD1306::setMode(const bool isTest)
{
    uint8_t modeCmd = 0xA4;
    modeCmd |= (isTest) ? 0b1 : 0;
    writeCmd(modeCmd);
}

void SSD1306::reset()
{
    mSetPin(mResetPin, false);
    mDelayMs(1);
    mSetPin(mResetPin, true);
}

bool SSD1306::setMemAddrMode(const uint8_t mode)
{
    // Check for valid mode (00, 01, 10)
    if(mode > 0b10)
    {
        return false;
    }

    writeCmd(0x20);
    writeCmd(mode);

    return true;
}   

bool SSD1306::setStartLine(const uint8_t line)
{
    // Bounds check
    if(line > 63)
    {
        return false;
    }

    uint8_t startCmd = 0b100'0000 | line;
    writeCmd(startCmd);
    return true;
}

void SSD1306::setSegRemap(const bool isReversed)
{
    uint8_t cmd = 0xA0;
    cmd |= (isReversed) ? 0b1 : 0;
    writeCmd(cmd);
}

bool SSD1306::setMuxRatio(const uint8_t ratio)
{
    // Bounds check
    if(ratio < 16 || ratio > 63)
    {
        return false;
    }

    writeCmd(0xA8);
    writeCmd(ratio);
    return true;
}

void SSD1306::setComDir(const bool isReversed)
{
    uint8_t cmd = 0xC0;
    cmd |= (isReversed) ? 0b1000 : 0;
    writeCmd(cmd);
}

bool SSD1306::setDisplayOffset(const uint8_t offset)
{
    if(offset > 63)
    {
        return false;
    }

    writeCmd(0xD3);
    writeCmd(offset);
    return true;
}

void SSD1306::setComPinConfig(const bool isAlternative, const bool enableRemap)
{
    uint8_t config = 0b10;
    config |= (isAlternative) ? 0b1'0000 : 0;
    config |= (enableRemap) ? 0b10'0000 : 0;
    writeCmd(0xDA);
    writeCmd(config);
}

bool SSD1306::setOscillator(const uint8_t divRatio, const uint8_t freq)
{
    if(divRatio > 0b1111 || freq > 0b1111)
    {
        return false;
    }

    uint8_t data = (freq << 4) | divRatio;
    writeCmd(0xD5);
    writeCmd(data);
    return true;
}

bool SSD1306::setPreChargePeriod
(
    const uint8_t phase1Period, 
    const uint8_t phase2Period
)
{
    if(phase1Period == 0 || phase2Period == 0)
    {
        return false;
    }

    uint8_t data = (phase2Period << 4) | phase1Period;
    writeCmd(0xD9);
    writeCmd(data);
    return true;
}

bool SSD1306::setVcomDeselectLevel(const uint8_t level)
{
    if(level > 0b11)
    {
        return false;
    }

    writeCmd(0xDB);
    writeCmd(level << 4);
    return true;
}

void SSD1306::setContrast(const uint8_t level)
{
    writeCmd(0x81);
    writeCmd(level);
}

void SSD1306::setInvert(const bool isInverted)
{
    uint8_t cmd = 0xA6; 
    cmd |= (isInverted) ? 0b1 : 0;
    writeCmd(cmd);
}

void SSD1306::enableChargePump(const bool isEnabled)
{
    uint8_t data = 0b1'0000;
    data |= (isEnabled) ? 0b100 : 0;
    writeCmd(0x8D);
    writeCmd(data);
}