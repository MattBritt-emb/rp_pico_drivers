#include "framebuffer.hpp"


Framebuffer::Framebuffer(const size_t width, const size_t height)
:   mWidth(width),
    mHeight(height),
    mHeightBytes(height / 8),
    mBuf(width, std::vector<bool>(height, false)),
    mOutBuf(width * mHeightBytes, 0)
{

}

bool Framebuffer::getPixel(const size_t x, const size_t y)
{
    if(x >= mWidth || y >= mHeight)
    {
        return false;
    }

    return mBuf[x][y];
}

bool Framebuffer::setPixel(const size_t x, const size_t y, const bool val)
{
    if(x >= mWidth || y >= mHeight)
    {
        return false;
    }

    mBuf[x][y] = val;
    return true;
}

uint8_t* Framebuffer::getBuffer()
{
    // Convert 2d vector<bool> to vector of bytes
    size_t linearByte = 0;

    for(size_t x = 0; x < mWidth; x++)
    {
        uint8_t b = 0;

        for(size_t y = 0; y < mHeight; y++)
        {
            b = b >> 1;
            b |= (mBuf[x][y]) ? 0x80 : 0;

            if(y % 8 == 7)
            {
                mOutBuf[linearByte] = b;
                linearByte++;
                b = 0;             
            }
        }
    }

    return mOutBuf.data();
}

void Framebuffer::setBuffer(const uint8_t* pData, const size_t size)
{

}

bool Framebuffer::setChar(const char c, const size_t x, const size_t y)
{
    // Bounds check
    if(x >= mWidth || y >= mHeight)
    {
        return false;
    }

    // Ensure character font exists
    const auto it = mpFontMap->find(c);
    if(it == mpFontMap->end())
    {
        return false;
    }

    const std::vector<std::vector<bool>>* pCharVec = &(it->second);
    
    size_t yPos = y;

    // for(const std::vector<bool>& line : *pCharVec)
    for(int i = pCharVec->size() - 1; i >= 0; i--)
    {

        const auto& line = pCharVec->at(i);

        if(yPos >= mHeight)
        {
            break;
        }

        size_t xPos = x;

        for(const bool bit : line)
        {
            if(xPos >= mWidth)
            {
                continue;
            }

            mBuf[xPos][yPos] = bit;
            xPos++;
        }

        yPos++;
    }

    return true;
}

bool Framebuffer::setText
(
    const size_t x,
    const size_t y,
    const char* pText,
    const size_t size
)
{
    for(size_t i = 0; i < size; i++)
    {
        setChar(pText[i], x + (i * 8), y);
    }

    return true;
}