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
- Screen brightness adjusts to the ambient light.


## Screenshots
- **Libraries Used**
- ![TFT_eSPI](https://user-images.githubusercontent.com/94538153/162488633-a6887fd5-325b-4ed0-ba23-afcef23e9872.png "TFT_eSPI Library Image")
- ![AdafruitUnifiedSensor](https://user-images.githubusercontent.com/94538153/162489075-3b57403f-0405-49c1-aa66-3387ea798d48.png "Adafruit Unified Sensor Image")
- ![DHTsensorLibrary](https://user-images.githubusercontent.com/94538153/162488862-89af9448-5ba8-4e7a-a414-3fb66ad52b57.png "DHT sensor Library Image")
- **Wiring Diagram**
- <img src="https://user-images.githubusercontent.com/94538153/181092689-0da6602f-4508-4ad2-801a-42542cd5b229.png" width="800" height="450" />
- **Screen Layout**
- <img src="https://user-images.githubusercontent.com/94538153/181081335-64b259d9-553c-445c-910a-efe8e99b0fa5.jpg" width="250" height="400" />


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


## Usage
- Once the IDE is set up, and the components wired.
- Plug in your T-Display.
- Verify your Port.
- Click the Upload arrow.
- And I think that's it.


## Project Status
Project is: _Completed_.


## Acknowledgements
- Big thanks to [Retro Tech & Electronics](https://www.youtube.com/channel/UC_HRlflCd1ogZBmCu3_Mr0g) for the [TTGO](https://youtu.be/UE1mtlsxfKM) and [DHT22](https://youtu.be/u7277VShso4) information.
- Got the Battery info from [oxinon](https://github.com/oxinon/TTGO-T-Display-Name-Badge).
- Got the README template from [ritaly](https://github.com/ritaly/README-cheatsheet).
