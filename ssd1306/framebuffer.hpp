#pragma once

#include <cstdint>
#include <map>
#include <vector>

class Framebuffer
{
public:
    Framebuffer(const size_t width, const size_t height);

    size_t getBufSize()
    { return mWidth * mHeight / 8; }

    bool getPixel(const size_t x, const size_t y);
    bool setPixel(const size_t y, const size_t x, const bool val);

    uint8_t* getBuffer();

    void setBuffer(const uint8_t* pData, const size_t size);

    void setFont(const std::map<char,std::vector<std::vector<bool>>>* pFontMap)
    { mpFontMap = pFontMap; }

    bool setChar(const char c, const size_t x, const size_t y);

    bool setText
    (
        const size_t x,
        const size_t y,
        const char* pText,
        const size_t size
    );

protected:

    const size_t mWidth;
    const size_t mHeight;
    const size_t mHeightBytes;

    std::vector<std::vector<bool>> mBuf;
    std::vector<uint8_t> mOutBuf;

    const std::map<char, std::vector<std::vector<bool>>>* mpFontMap;

}; // End class Framebuffer