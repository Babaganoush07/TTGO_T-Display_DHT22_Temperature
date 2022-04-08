# TTGO T-Display with DHT22 Temperature Sensor
> Read and display Temperature and Humidity in my van.

## Table of Contents
* [General Info](#general-information)
* [Technologies Used](#technologies-used)
* [Features](#features)
* [Screenshots](#screenshots)
* [Setup](#setup)
* [Usage](#usage)
* [Project Status](#project-status)
* [Room for Improvement](#room-for-improvement)
* [Acknowledgements](#acknowledgements)


## General Information
- I could not find a digital thermaometer that met my needs.
- Wanted the Temp, the RH and the 24 hour Highs and Lows.
- TTGO T-Display: [Amazon](https://www.amazon.com/dp/B099MPFJ9M?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- DHT22: [Amazon](https://www.amazon.com/dp/B073F472JL?psc=1&ref=ppx_yo2ov_dt_b_product_details)


## Technologies Used
- [Adruino 1.8.19](https://www.arduino.cc/en/software)
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
- [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor) (Dependancy for DHT library)
- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library)


## Features
- Gets the Temperature and Humidity and displays it on the screen.
- Light sleeps for 15 minutes and then updates the temps.
- Wakes on a timer or a button.
- Pressing the wake button also gets the battery voltage and displays it on the screen.
- Resets the Highs and Lows every 24 hours.


## Screenshots
None yet.


## Setup
- Manufacturer info: [Xinyuan-LilyGO](https://github.com/Xinyuan-LilyGO/TTGO-T-Display)
- You will need the Adruino IDE. (I am on windows)
- Add [esp32 support](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/) by adding *https://dl.espressif.com/dl/package_esp32_index.json* in the preferences
- Select the board: Tools -> Board: -> TTGO LoRa32-OLED V1
- Set the Serial at 9600
- **TFT_eSPI**
	- In Arduino/libraries/TFT_eSPI/User_Setup_Select.h
	- Comment out this line: `#include <User_Setup.h> // Default setup is root library folder`
	- Un comment this line: `#include <User_Setups/Setup25_TTGO_T_Display.h>  // Setup file for ESP32 and TTGO T-Display ST7789V SPI bus TFT`


## Usage
- Once the IDE is set up, and the components wired.
- Just plug it in, that should be it.


## Project Status
Project is: _in progress_.


## Room for Improvement
To do:
- Add images.
- Still need an external battery.
- Need to make a case


## Acknowledgements
- Big thanks to [Retro Tech & Electronics](https://www.youtube.com/channel/UC_HRlflCd1ogZBmCu3_Mr0g) for the [TTGO](https://youtu.be/UE1mtlsxfKM) and [DHT22](https://youtu.be/u7277VShso4) information
- Got the Battery info from [oxinon](https://github.com/oxinon/TTGO-T-Display-Name-Badge/blob/master/oxinon-name-badge/oxinon-name-badge.ino)
- Got the README template from [ritaly](https://github.com/ritaly/README-cheatsheet)
