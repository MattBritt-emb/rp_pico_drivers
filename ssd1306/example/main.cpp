/**
 * @brief Simple example program using SSD1306 library. 
 */

#include <pico/stdlib.h>
#include <hardware/spi.h>
#include <pico/time.h>

#include <font.hpp>
#include <framebuffer.hpp>
#include <ssd1306.hpp>

const int RESET_PIN = 9;
const int DC_PIN = 15;
const size_t WIDTH = 128;
const size_t HEIGHT = 64;

const int SCK_PIN = 10;
const int SDI_PIN = 11;
const int CS_PIN = 13;

const int BAUD = 1'000'000;

/**
 * @brief Set pin state high/low
 * 
 * @param pin - pin number to set
 * @param state - if true set high, if false set low
 */
void setPin(const uint8_t pin, const bool state)
{
    gpio_put(pin, state);
}

/**
 * @brief Delay / no-op for number of milliseconds
 * 
 * @param ms - milliseconds to delay
 */
void delayMs(const uint32_t ms)
{
    sleep_ms(ms);
}

/**
 * @brief Write to SSD1306
 * 
 * @param pData - pointer to data being written
 * @param size - size of data being written
 */
void write(const uint8_t* pData, const size_t size)
{
    setPin(CS_PIN, false);
    spi_write_blocking(spi1, pData, size);
    setPin(CS_PIN, true);
}

/**
 * @brief Initialize GPIO & SPI
 */
void initialize()
{
    stdio_init_all();

    gpio_init(RESET_PIN);
    gpio_set_dir(RESET_PIN, GPIO_OUT);

    gpio_init(DC_PIN);
    gpio_set_dir(DC_PIN, GPIO_OUT);

    gpio_init(CS_PIN);
    gpio_set_dir(CS_PIN, GPIO_OUT);
    gpio_put(CS_PIN, 1);

    spi_init(spi1, BAUD);
    spi_set_format(spi1, 8, SPI_CPOL_0 , SPI_CPHA_0, SPI_MSB_FIRST);

    gpio_set_function(SDI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SCK_PIN, GPIO_FUNC_SPI);
}

int main()

    {
    // Setup GPIO & SPI
    initialize();

    // Create object that uses write, setPin, delayMs functions defined above
    SSD1306 oled(&write, &setPin, &delayMs, DC_PIN, RESET_PIN, WIDTH, HEIGHT);

    Framebuffer fb(128, 64);
    fb.setFont(&font);

    // Scroll "Hello World!" up and down    
    size_t y = 0;
    int step = 1;

    while(true)
    {
        if(y > 60)
        { 
            step = -1;  
        }
        else if(y == 0)
        {
            step = 1;
        }

        char text4[] = "HELLO WORLD!";
        fb.clearScreen();
        fb.setText(0,y,text4,sizeof(text4) - 1);
        oled.writeData(fb.getBuffer(), fb.getBufSize());

        sleep_ms(20);
        y += step;
    }

    // Put framebuffer pixels on screen
    oled.writeData(fb.getBuffer(), 128 * 64 / 8);

    return 0;
}