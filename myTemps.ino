#include <DHT.h>
#include <TFT_eSPI.h>
#include <SPI.h>

///////////////////////// SET VARIABLES /////////////////////////

// SET THE PIN FOR THE DHT22
#define DHTPIN 17
#define DHTTYPE DHT22

// SET THE HIGHS TO THE MINIMUM AND LOWS TO THE MAXIMUM
// SO THAT FOR THE FIRST LOOP THE CURRENT TEMP IS BOTH > LOW AND < HIGH
int high_temp = -40;
int low_temp = 257;

int high_rh = 0;
int low_rh = 100;

// USED TO REFRESH THE HIGHS AND LOWS EVERY 24 HOURS
int refresh = 0;

///////////////////////// CREATE INSTANCES /////////////////////////

TFT_eSPI tft = TFT_eSPI();
DHT dht(DHTPIN, DHTTYPE);

///////////////////////// GET BATTERY VOLTAGE /////////////////////////
#define ADC_PIN 34 // Battery Voltage Pin
int vref = 1100;
float voltage = 0.0;

void show_battery(){
  uint16_t v = analogRead(ADC_PIN);
  float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
  String voltage = "Voltage " + String(battery_voltage) + "V";

  // Clear the title and show the battery for a few seconds
  tft.setTextDatum(TL_DATUM);
  tft.fillRect(0, 0, tft.width(), 24, TFT_BLACK);
  tft.fillRect(4, 4, 28, 2, TFT_DARKGREY);   //TOP OF BATTERY
  tft.fillRect(4, 16, 28, 2, TFT_DARKGREY);  //BOTTOM
  tft.fillRect(4, 4, 2, 12, TFT_DARKGREY);   //LEFT
  tft.fillRect(32, 4, 2, 14, TFT_DARKGREY);  //RIGHT
  tft.fillRect(34, 8, 3, 6, TFT_DARKGREY);   //TIP
  
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  if(battery_voltage <= 2.99){
    tft.fillRect(4, 4, 28, 2, TFT_RED);
    tft.fillRect(4, 16, 28, 2, TFT_RED);
    tft.fillRect(4, 4, 2, 14, TFT_RED);
    tft.fillRect(32, 4, 2, 14, TFT_RED);
    tft.fillRect(34, 8, 3, 6, TFT_RED);
    tft.drawString(voltage, 45, 8, 1);
  }
  if(battery_voltage >= 3.0){
    tft.fillRect(6, 6, 4, 10, TFT_RED);
    tft.drawString(voltage, 45, 8, 1);
  }
  if(battery_voltage >= 3.2){
    tft.fillRect(6, 6, 6, 10, TFT_RED);
    tft.drawString(voltage, 45, 8, 1);
  }
  if(battery_voltage >= 3.4){
    tft.fillRect(6, 6, 11, 10, TFT_YELLOW);
    tft.drawString(voltage, 45, 8, 1);
  }
  if(battery_voltage >= 3.6){
    tft.fillRect(6, 6, 16, 10, TFT_YELLOW);
    tft.drawString(voltage, 45, 8, 1);
  }
  if(battery_voltage >= 3.8){
    tft.fillRect(6, 6, 21, 10, TFT_GREEN);
    tft.drawString(voltage, 45, 8, 1);
  }
  if(battery_voltage >= 4.0){
    tft.fillRect(6, 6, 26, 10, TFT_GREEN);
    tft.drawString(voltage, 45, 8, 1);
  }
  if(battery_voltage >= 4.60){
    tft.fillRect(6, 6, 26, 10, TFT_GREEN);
    tft.setTextColor(TFT_BLACK, TFT_GREEN);
    tft.drawString("CHG", 10, 7, 1);
  }
  if(battery_voltage >= 4.85){
    tft.fillRect(6, 6, 26, 10, TFT_SKYBLUE);
    tft.setTextColor(TFT_BLACK, TFT_SKYBLUE);
    tft.drawString("USB", 10, 7, 1);
  }  
  
  delay(5*1000);
  // add the title back
  tft.fillRect(0, 0, tft.width(), 24, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN, TFT_BLACK); 
  tft.drawString("TEMPERATURE", tft.width() / 2, 15);
}

///////////////////////// SET COLOR FUNTIONS /////////////////////////

void temp_color(int x){
  if ( x >= 104 ){tft.setTextColor(TFT_WHITE, TFT_BLACK);}
  else if ( x >= 95 ){tft.setTextColor(TFT_PINK, TFT_BLACK);}
  else if ( x >= 85 ){tft.setTextColor(TFT_MAGENTA, TFT_BLACK);}
  else if ( x >= 77 ){tft.setTextColor(TFT_RED, TFT_BLACK);}
  else if ( x >= 68 ){tft.setTextColor(TFT_ORANGE, TFT_BLACK);}
  else if ( x >= 59 ){tft.setTextColor(TFT_YELLOW, TFT_BLACK);}
  else if ( x >= 50 ){tft.setTextColor(TFT_GREENYELLOW, TFT_BLACK);}
  else if ( x >= 41 ){tft.setTextColor(TFT_GREEN, TFT_BLACK);}
  else if ( x >= 23 ){tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);}
  else if ( x >= 5 ){tft.setTextColor(TFT_BLUE, TFT_BLACK);}
  else if ( x < 5 ){tft.setTextColor(TFT_VIOLET, TFT_BLACK);}
}

void rh_color(int x){
  if ( x >= 70 ){tft.setTextColor(TFT_RED, TFT_BLACK);}
  else if (x >= 60 ){tft.setTextColor(TFT_ORANGE, TFT_BLACK);}
  else if (x >= 30 ){tft.setTextColor(TFT_GREEN, TFT_BLACK);}
  else if (x < 30 ){tft.setTextColor(TFT_BLUE, TFT_BLACK);}
}

///////////////////////// LIGHT SLEEP FUNTIONS /////////////////////////

// Sleep timer is measured in MICRO-seconds
// USES THE RIGHT BUTTON (PIN 35) TO WAKE FROM SLEEP IF NEEDED
void go_to_sleep(int ms){
  Serial.println("Going to sleep.\n");
  delay(200);
  esp_sleep_enable_timer_wakeup(ms * 1000);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, 0);
  esp_light_sleep_start();
}

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason){
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO");
    //show_battery();
    break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  } 
}

/////////////////////////////////////////////////////////////////////////

void setup() {
  ///////////////////////// INITIALIZE LIBRARIES /////////////////////////

  Serial.begin(9600);
  tft.init();
  dht.begin();
  
  ///////////////////////// SET STATIC SCREEN ELEMENTS /////////////////////////
  
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  
  tft.drawString("TEMPERATURE", tft.width() / 2, 15);
  tft.drawLine(0, 25, 250, 25, TFT_BLUE);
  tft.drawString("H:", 15, 105);
  tft.drawString("L:", tft.width() / 2 + 15, 105);
  
  tft.drawString("HUMIDITY", tft.width() / 2, tft.height() / 2 + 15);
  tft.drawLine(0, 145, 250, 145, TFT_BLUE);
  tft.drawString("H:", 15, 230);
  tft.drawString("L:", tft.width() / 2 + 10, 230);
}

//////////////////////////////////////////////////////////////////////

void loop() {
  
  print_wakeup_reason();
  delay(200);   // THIS PREVENTS THE DEBOUNCE FROM THE SLEEP INTERUPT
  Serial.println("Getting temps.");
  
  int temp = dht.readTemperature(true); // range of -40 to 257 true = F
  int rh = dht.readHumidity(); // range of 0 to 100
  
  // Check if any reads failed.
  if (isnan(rh) || isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  ///////////////////////// SET HIGHS AND LOWS /////////////////////////

  if (millis() >= refresh + (24*60*60*1000)){        // Reset High and Low after 24 hours, 86400000 milliseconds in a day
    high_temp = temp;
    low_temp = temp;
    high_rh = rh;
    low_rh = rh;
    refresh = millis();}
  else {
    if(temp >= high_temp){high_temp = temp;}
    if(temp <= low_temp){low_temp = temp;}
    if(rh >= high_rh){high_rh = rh;}
    if(rh <= low_rh){low_rh = rh;}
  }
 
  //////////////////////////////////////////////////////////////////////
  Serial.printf("TEMP: %d, HIGH: %d, LOW:, %d\n", temp, high_temp, low_temp);
  Serial.printf("RH: %d, HIGH: %d, LOW:, %d\n", rh, high_rh, low_rh);
  //////////////////////////////////////////////////////////////////////
  
  // PRINT THE CURRENT DATA IN BIG FONTS
  tft.setTextSize(8);
    
  // CLEAR THE TEXT
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("   ", tft.width() / 2, 65);
  tft.drawString("   ", tft.width() / 2, 185);
  
  // PRINT DATA
  temp_color(temp);
  tft.drawNumber(temp, tft.width() / 2, 65);
  rh_color(rh);
  tft.drawNumber(rh, tft.width() / 2, 185);

  //////////////////////////////////////////////////////////////////////
  
  // PRINT HIGHS AND LOWS IN SMALL FONTS
  tft.setTextSize(2);
  
  // CLEAR THE TEXT
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("   ", 45, 105);
  tft.drawString("   ", tft.width() / 2 + 45, 105);

  tft.drawString("   ", 40, 230);
  tft.drawString("   ", tft.width() / 2 + 35, 230);
  
  // PRINT THE DATA
  temp_color(high_temp);
  tft.drawNumber(high_temp, 45, 105);
  temp_color(low_temp);
  tft.drawNumber(low_temp, tft.width() / 2 + 45, 105);

  rh_color(high_rh);
  tft.drawNumber(high_rh, 40, 230);
  rh_color(low_rh);
  tft.drawNumber(low_rh, tft.width() / 2 + 35, 230);

  //////////////////////////////////////////////////////////////////////
  
  go_to_sleep(15 * 60000); // GET NEW DATA EVERY 15 MINUTES

}
