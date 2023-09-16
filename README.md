# rp_pico_drivers
This is an experiment with creating various "driver" libraries for the rp2040 / Raspberry Pi Pico.


# Setup

This code uses the Raspberry Pi Pico SDK.

I've built this on Windows using VS Code and the Raspberry Pi Debug Probe.
My setup is based on https://www.raspberrypi.com/news/raspberry-pi-pico-windows-installer/

The specific VS Code setup is in the .vscode dir

# Drivers

## SSD1306 OLED Display Driver

This is a common OLED driver chip.

I used this specific display (the Blue & Yellow): [UMLIFE 0.96" 7 Pin SPI 128x64 OLED Display](https://www.amazon.com/dp/B08SJY4RC4?ref=ppx_yo2ov_dt_b_product_details&th=1)

Note: This is really a monochrome display with top ~20% showing up yellow and the rest blue.  The pictures on Amazon are *misleading* to say the least.