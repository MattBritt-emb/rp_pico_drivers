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

    // Process letter lines in reverse to match screen RAM
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
} // End setChar

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
        bool result = setChar(pText[i], x + (i * 8), y);
        if(!result)
        {
            return false;
        }
    }

    return true;
}

void Framebuffer::setRect
(
    const size_t x0, 
    const size_t y0, 
    const size_t x1, 
    const size_t y1,
    const bool val
)
{
    for(size_t x = x0; x < x1; x++)
    {
        if(x >= mWidth)
        {
            // No more y pixels to write - bail
            return;
        }

        for(size_t y = y0; y < y1; y++)
        {
            if(y >= mHeight)
            {
                // Out of y pixels for this x, but there
                // may be more for other x
                continue;
            }

            setPixel(x, y, val);
        }
    }
}

// void Framebuffer::clearScreen()
// {
//     clearRect(0, 0, mWidth, mHeight);
// }