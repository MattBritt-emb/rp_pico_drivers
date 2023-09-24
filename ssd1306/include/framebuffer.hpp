#pragma once

#include <cstdint>
#include <map>
#include <vector>

/**
 * @brief Framebuffer represents SSD1306 RAM.
 */
class Framebuffer
{
public:

    /**
     * @brief Construct a new Framebuffer object
     * 
     * @param width - width of the screen in pixels
     * @param height - height of the screen in pixels
     */
    Framebuffer(const size_t width, const size_t height);

    /**
     * @brief Get the size of screen buffer, in bytes
     * 
     * @return size_t number of bytes
     */
    size_t getBufSize()
    { return mWidth * mHeight / 8; }

    /**
     * @brief Get the pixel value at a given location
     * 
     * @param x - x coordinate of pixel
     * @param y - y coordinate of pixel
     * @return Value of pixel
     */
    bool getPixel(const size_t x, const size_t y);
    
    /**
     * @brief Set the pixel value at given location
     * 
     * @param x - x coordinate of pixel
     * @param y - y coordinate of pixel
     * @param val - value to set
     * @return true if x,y valid, false if invalid
     */
    bool setPixel(const size_t x, const size_t y, const bool val);

    /**
     * @brief Get pointer to buffer
     * 
     * @return uint8_t* - pointer to buffer
     */
    uint8_t* getBuffer();

    /**
     * @brief Directly set buffer
     * 
     * @param pData - pointer to buffer data
     * @param size - size of buffer data
     */
    void setBuffer(const uint8_t* pData, const size_t size);

    /**
     * @brief Set the font map used to look up characters
     * 
     * @param pFontMap - pointer to font map
     */
    void setFont(const std::map<char,std::vector<std::vector<bool>>>* pFontMap)
    { mpFontMap = pFontMap; }

    /**
     * @brief Put a character at a given location
     * 
     * @param c - character
     * @param x - x coordinate of character
     * @param y - y coordinate of character
     * @return true if x,y valid, false if invalid
     */
    bool setChar(const char c, const size_t x, const size_t y);

    /**
     * @brief Set horizontal line of text at given location
     * 
     * @param x - x coordinate of text
     * @param y - y coordintate of text
     * @param pText - text
     * @param size - size of text
     * @return true if text fit onto screen, false otherwise
     */
    bool setText
    (
        const size_t x,
        const size_t y,
        const char* pText,
        const size_t size
    );

    void clearScreen()
    { setRect(0, 0, mWidth, mHeight, false); }

    void setRect
    (
        const size_t x0, 
        const size_t y0, 
        const size_t x1, 
        const size_t y1,
        const bool val
    );

protected:

    /// Screen width in pixels
    const size_t mWidth;
    /// Screen height in pixels
    const size_t mHeight;
    /// Screen height in bytes
    const size_t mHeightBytes;
    /// Buffer representing screen RAM
    std::vector<std::vector<bool>> mBuf;
    /// Output buffer in format ready to SSD1306
    std::vector<uint8_t> mOutBuf;
    /// Font map used to look up character data
    const std::map<char, std::vector<std::vector<bool>>>* mpFontMap;

}; // End class Framebuffer