#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128
#define OLED_RESET    -1

// XIAO ESP32C3 I2C pins
#define SDA_PIN 6   // D4
#define SCL_PIN 7   // D5

// SH1107 display
Adafruit_SH1107 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET,
  400000,
  100000
);

#define LOGO_HEIGHT 16
#define LOGO_WIDTH  16

static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };
 
 
void setup() {
  Serial.begin(115200);

  delay(500);

  // Initialize I2C using XIAO ESP32C3 pins
  Wire.begin(SDA_PIN, SCL_PIN);

  delay(100);

  // Initialize SH1107 OLED
  if (!display.begin(0x3C, true)) {
    Serial.println("SH1107 OLED not found!");

    while (1) {
      delay(10);
    }
  }

  Serial.println("SH1107 OLED initialized!");

  display.display();
  delay(2000);

  display.clearDisplay();

  display.drawPixel(10, 10, SH110X_WHITE);
  display.display();

  delay(2000);
  display.clearDisplay();

  testdrawline();
  testdrawrect();
  testfillrect();
  testdrawcircle();
  testfillcircle();
  testdrawroundrect();
  testfillroundrect();
  testdrawtriangle();
  testfilltriangle();
  testdrawchar();
  testdrawstyles();
  testdrawbitmap();

  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT);
}

void loop() {
}
 
void testdrawline() {
  int16_t i;
 
  display.clearDisplay(); // Clear display buffer
 
  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, SH110X_WHITE);
    display.display(); // Update screen with each newly-drawn line
    delay(1);
  }
  for(i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, SH110X_WHITE);
    display.display();
    delay(1);
  }
  delay(250);
 
  display.clearDisplay();
 
  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, SH110X_WHITE);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, SH110X_WHITE);
    display.display();
    delay(1);
  }
  delay(250);
 
  display.clearDisplay();
 
  for(i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, SH110X_WHITE);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, SH110X_WHITE);
    display.display();
    delay(1);
  }
  delay(250);
 
  display.clearDisplay();
 
  for(i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, SH110X_WHITE);
    display.display();
    delay(1);
  }
  for(i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, SH110X_WHITE);
    display.display();
    delay(1);
  }
 
  delay(2000); // Pause for 2 seconds
}
 
void testdrawrect(void) {
  display.clearDisplay();
 
  for(int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SH110X_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }
 
  delay(2000);
}
 
void testfillrect(void) {
  display.clearDisplay();
 
  for(int16_t i=0; i<display.height()/2; i+=3) {
    // The INVERSE color is used so rectangles alternate white/black
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, SH110X_INVERSE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }
 
  delay(2000);
}
 
void testdrawcircle(void) {
  display.clearDisplay();
 
  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, SH110X_WHITE);
    display.display();
    delay(1);
  }
 
  delay(2000);
}
 
void testfillcircle(void) {
  display.clearDisplay();
 
  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=3) {
    // The INVERSE color is used so circles alternate white/black
    display.fillCircle(display.width() / 2, display.height() / 2, i, SH110X_INVERSE);
    display.display(); // Update screen with each newly-drawn circle
    delay(1);
  }
 
  delay(2000);
}
 
void testdrawroundrect(void) {
  display.clearDisplay();
 
  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, SH110X_WHITE);
    display.display();
    delay(1);
  }
 
  delay(2000);
}
 
void testfillroundrect(void) {
  display.clearDisplay();
 
  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    // The INVERSE color is used so round-rects alternate white/black
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, SH110X_INVERSE);
    display.display();
    delay(1);
  }
 
  delay(2000);
}
 
void testdrawtriangle(void) {
  display.clearDisplay();
 
  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, SH110X_WHITE);
    display.display();
    delay(1);
  }
 
  delay(2000);
}
 
void testfilltriangle(void) {
  display.clearDisplay();
 
  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=5) {
    // The INVERSE color is used so triangles alternate white/black
    display.fillTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, SH110X_INVERSE);
    display.display();
    delay(1);
  }
 
  delay(2000);
}
 
void testdrawchar(void) {
  display.clearDisplay();
 
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
 
  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }
 
  display.display();
  delay(2000);
}
 
void testdrawstyles(void) {
  display.clearDisplay();
 
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));
 
  display.setTextColor(SH110X_BLACK, SH110X_WHITE); // Draw 'inverse' text
  display.println(3.141592);
 
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SH110X_WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);
 
  display.display();
  delay(2000);
}
 
void testdrawbitmap(void) {
  display.clearDisplay();
 
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}
 
#define NUMFLAKES 10
#define XPOS       0 // Indexes into the 'icons' array in function below
#define YPOS       1
#define DELTAY     2
#define DELTAT     3
 
void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t f;
  int16_t icons[NUMFLAKES][4];
 
  // Initialize 'snowflake' positions
  for(f = 0; f < NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 8);
    icons[f][DELTAT] = 0;
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }
 
  display.clearDisplay(); // Clear the display buffer
 
  for(;;) { // Loop forever...
 
    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][DELTAT] += 1;
      if (icons[f][DELTAT] >= icons[f][DELTAY]) {
        icons[f][YPOS] += 1;
        icons[f][DELTAT] = 0;
        display.drawBitmap(icons[f][XPOS], icons[f][YPOS] - 1, bitmap, w, h, SH110X_BLACK);  // Erase the snowflake
        display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SH110X_WHITE);
      }
    }
 
    display.display(); // Show the display buffer on the screen
    delay(40);        // Pause for 40 ms
 
    // Then update coordinates of each flake...
    for(f = 0; f < NUMFLAKES; f++) {
      //icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= (display.height())) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 8);
        icons[f][DELTAT] = 0;
      }
    }
  }
}
 
// End of code.
// https://simple-circuit.com/
 
/*********************************************************************
  This is an example for our Monochrome OLEDs based on SH1107 drivers
 
  This example is for a 128x128 size display using I2C to communicate
 
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
 
  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution
*********************************************************************/