#include <Arduino.h>
#include <Wire.h>
#include <SdFat.h>
/**************************************************************************
  This is a test file for adafruit playground express sensors over tft gizmo

  Works with the Adafruit TFT Gizmo
    ----> http://www.adafruit.com/products/4367

  Check out the links above for our tutorials and wiring diagrams.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/
#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Because of the limited number of pins available on the Circuit Playground Boards
// Software SPI is used
#define TFT_CS        0
#define TFT_RST       -1 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        1
#define TFT_BACKLIGHT PIN_A3 // Display backlight pin

// You will need to use Adafruit's CircuitPlayground Express Board Definition
// for Gizmos rather than the Arduino version since there are additional SPI
// ports exposed.
#if (SPI_INTERFACES_COUNT == 1)
  SPIClass* spi = &SPI;
#else
  SPIClass* spi = &SPI1;
#endif

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable.
Adafruit_ST7789 tft = Adafruit_ST7789(spi, TFT_CS, TFT_DC, TFT_RST);


void setup(void) {
  
  CircuitPlayground.begin();

  Serial.begin(9600);
  
  Serial.print(F("Hello! ST77xx TFT Test"));

  tft.init(240, 240);                // Init ST7789 240x240
  tft.setRotation(2);  
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH); // Backlight on

  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_GREEN);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  tft.setTextSize(2);



}

void loop() {

  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);

  tft.print("Temp: ");
  tft.print(CircuitPlayground.temperature());
  tft.println("C");

  tft.print("Light: ");
  tft.println(CircuitPlayground.lightSensor());

  tft.print("Accel X: ");
  tft.println(CircuitPlayground.motionX());

  tft.print("Accel Y: ");
  tft.println(CircuitPlayground.motionY());

  tft.print("Accel Z: ");
  tft.println(CircuitPlayground.motionZ());

  tft.print("Mic sound: ");
  tft.println(CircuitPlayground.mic.soundPressureLevel(50)); 

  delay(500);
}