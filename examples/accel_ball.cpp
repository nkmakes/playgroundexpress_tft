/**************************************************************************
  This is a test file for adafruit playground express accel and tft

  Displays a ball on the screen that moves depending on accel values

  Written by nkmakes.github.io
 **************************************************************************/

#include <Arduino.h>
#include <Wire.h>
#include <SdFat.h>
#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 
#include <SPI.h>

#define TFT_CS        0
#define TFT_RST       -1 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        1
#define TFT_BACKLIGHT PIN_A3 // Display backlight pin

SPIClass* spi = &SPI1;

Adafruit_ST7789 tft = Adafruit_ST7789(spi, TFT_CS, TFT_DC, TFT_RST);

int xPos = 120;
int yPos = 120;
int motionX;
int motionY;



void setup(void) {
  
  CircuitPlayground.begin();

  Serial.begin(9600);
  
  Serial.print(F("Hello! ST77xx TFT Test"));

  tft.init(240, 240);                
  tft.setRotation(2);  
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH); 

  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_GREEN);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  tft.setTextSize(30);
  tft.fillScreen(ST77XX_BLACK);

  for (int i=3; i>=1; i--) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(50, 20);
    tft.print(i);
    delay(1000);
  }


}

void loop() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(xPos, yPos);

  tft.drawCircle(xPos, yPos, 10, ST77XX_RED);
  tft.fillCircle(xPos, yPos, 10, ST77XX_RED);

  delay(10);

  motionX=CircuitPlayground.motionX();
  motionY=CircuitPlayground.motionY();

  xPos+=motionX;
  yPos+=motionY;
  if (xPos >= 230) xPos=230;
  else if (xPos<=10) xPos=10;

  if (yPos >= 230) yPos=230;
  else if (yPos<=10) yPos=10;

}