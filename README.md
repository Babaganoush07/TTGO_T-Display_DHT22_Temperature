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
- This is my **FIRST** esp32 project.
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
- **Libraries Used**
- ![TFT_eSPI](https://user-images.githubusercontent.com/94538153/162488633-a6887fd5-325b-4ed0-ba23-afcef23e9872.png "TFT_eSPI Library Image")
- ![AdafruitUnifiedSensor](https://user-images.githubusercontent.com/94538153/162489075-3b57403f-0405-49c1-aa66-3387ea798d48.png "Adafruit Unified Sensor Image")
- ![DHTsensorLibrary](https://user-images.githubusercontent.com/94538153/162488862-89af9448-5ba8-4e7a-a414-3fb66ad52b57.png "DHT sensor Library Image")
- **Wiring Diagram**
- ![DHT22Wire](https://user-images.githubusercontent.com/94538153/169334762-486ba0c7-edf3-4211-9f30-17b5da5965ed.png)
- **Screen Layout**
- ![ttgo-screen](https://user-images.githubusercontent.com/94538153/164036125-dc2f64c3-af49-40ee-814b-bac53565c991.jpg)


## Setup
- Manufacturer info: [Xinyuan-LilyGO](https://github.com/Xinyuan-LilyGO/TTGO-T-Display)
- You will need the Adruino IDE. (I am on windows)
- Add [esp32 support](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/) by adding `https://dl.espressif.com/dl/package_esp32_index.json` in the preferences
- Select the board: Tools -> Board: -> TTGO LoRa32-OLED V1
- Set the Serial at 921600
- **TFT_eSPI**
	- In Arduino/libraries/TFT_eSPI/User_Setup_Select.h
	- Comment out this line: `#include <User_Setup.h> // Default setup is root library folder`
	- Un-comment this line: `#include <User_Setups/Setup25_TTGO_T_Display.h>  // Setup file for ESP32 and TTGO T-Display ST7789V SPI bus TFT`
- I had an issue using the 3v3 pin where I would get a NAN value
or get a reading of 2147483647. Switching to the 5v solved this for me.


## Usage
- Once the IDE is set up, and the components wired.
- Plug in your T-Display.
- Verify your Port.
- Click the Upload arrow.
- And I think that's it.


## Project Status
Project is: _in progress_.


## Room for Improvement
To do:
- Add a startup message / icon.
- Still need an external battery.
- Need to make a case.


## Acknowledgements
- Big thanks to [Retro Tech & Electronics](https://www.youtube.com/channel/UC_HRlflCd1ogZBmCu3_Mr0g) for the [TTGO](https://youtu.be/UE1mtlsxfKM) and [DHT22](https://youtu.be/u7277VShso4) information.
- Got the Battery info from [oxinon](https://github.com/oxinon/TTGO-T-Display-Name-Badge).
- Got the README template from [ritaly](https://github.com/ritaly/README-cheatsheet).
