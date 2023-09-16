#include <pico/stdlib.h>
#include <hardware/spi.h>
#include <pico/time.h>

#include "SSD1306.hpp"

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

    // Put 'F' in lower left corner
    const size_t BUF_SIZE = HEIGHT * WIDTH / 8;
    uint8_t buf[BUF_SIZE] = {0};

    buf[0] =    0b0000'0000;
    buf[8] =    0b0111'1110;
    buf[16] =   0b0101'0000;
    buf[24] =   0b0101'0000;
    buf[32] =   0b0101'0000;
    buf[40] =   0b0000'0000;

    oled.writeData(buf, BUF_SIZE);

    return 0;
}