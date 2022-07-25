#include <DHT.h>
#include <TFT_eSPI.h>

#define DHTPIN 17
#define DHTTYPE DHT22

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
DHT dht(DHTPIN, DHTTYPE);

#define tempButton 35
int tempButtonState;       // the current state of button
int lastTempButtonState;   // the previous state of button
bool showTemp = true;

#define photoTransistor 33
const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;

#define ADC_PIN 34 // Battery Voltage Pin
int vref = 1100;
//float voltage = 0.0;
float battery_voltage = 0.0;

// Setup for screen
int centerX = 135/2;
int centerY = 240/2;

// Variables for data
float temp = 0.0;
float rh = 0.0;

// Millis timer delay
int waitPeriod = 3000;
unsigned long start = 0;

int ball = 0;
int moveAmount = 1;

void setup() {
  Serial.begin(9600);
  dht.begin();
  tft.begin();
  tft.fillScreen(TFT_BLACK);

  pinMode(tempButton, INPUT_PULLUP);
  tempButtonState = digitalRead(tempButton);

  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT);
}

void loop(void) {
  // MILLIS timer in place of delay
  if(millis() - start >= waitPeriod){
    temp = dht.readTemperature(true);
    rh = dht.readHumidity();
    uint16_t v = analogRead(ADC_PIN);
    battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
    start = millis();
  } // END millis timer

  //uint16_t v = analogRead(ADC_PIN);
  //battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);

  int brightness = map(analogRead(photoTransistor), 0, 4095, 10, 255);
  ledcWrite(pwmLedChannelTFT, brightness);  
  drawScreen(temp, rh, battery_voltage);
}

void drawScreen(float temp, float rh, float battery_voltage){
  spr.createSprite(135, 280);
  spr.fillSprite(TFT_BLACK);

  //Show battery Voltage
  spr.setTextDatum(TR_DATUM);
  if(battery_voltage <= 3.3) spr.setTextColor(TFT_RED);
  if(battery_voltage >= 3.4) spr.setTextColor(TFT_YELLOW);
  if(battery_voltage >= 3.8) spr.setTextColor(TFT_GREEN);
  
  if(battery_voltage >= 4.60){ 
    spr.drawString("CHG", 130, 1, 2);
  }else if(battery_voltage >= 4.85){
    spr.drawString("USB", 130, 1, 2);
  }else{
    spr.drawFloat(battery_voltage, 2, 130, 1, 2);
  }
  
  // Write the temp centered in the screen
  spr.setTextDatum(MC_DATUM);
  spr.setTextColor(TFT_RED);
  spr.drawString("Temp", centerX, 40, 4);
  spr.drawNumber(int(temp), centerX, 90, 6);
  
  spr.setTextColor(TFT_BLUE);
  spr.drawString("Humidity", centerX, centerY + 20, 4);
  spr.drawNumber(int(rh), centerX, centerY + 70, 6);

  //move the ball
  tft.fillCircle(ball,230,2,TFT_WHITE);
  ball = ball + moveAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (ball <= 0 || ball >= 135) {
    moveAmount = -moveAmount;
  }
  
  // Now push the sprite to the TFT at position 0,0 on screen
  spr.pushSprite(0, 0);
  spr.deleteSprite();
  
} // END drawScreen(temp, rh, battery_voltage)
