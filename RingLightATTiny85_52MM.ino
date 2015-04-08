#include <Adafruit_NeoPixel.h>

#define PIN 1   // LED Ring Pin
#define POTB 3  // Brightness Pot - MODIFIED to Pin 3 for the 123D Circuit board
#define POTC 2  // Color Selection Pot - MODIFIED to Pin 2 for the 123D Circuit board

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);

int lastreadB, lastreadC = 0;
int B, C = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  B = map(analogRead(POTB),0,1024,0,20);
  C = map(analogRead(POTC),0,1024,0,255);
  if(lastreadB != B || lastreadC != C) { // Eliminate Flicker
    setcolor(C,B);
  }
}

void setcolor(uint8_t color, uint8_t brightness) {
  uint16_t i;
  for(i=0; i<strip.numPixels(); i++) {
    if(brightness > 0) {
      strip.setPixelColor(i, Wheel(color,brightness));
    } else {
      strip.setPixelColor(i,0,0,0);
    }
  }
  strip.show();
}

uint32_t Wheel(byte WheelPos, uint8_t brightness) {
  uint8_t nb = 21 - brightness;
  if(WheelPos < 20) {
   return strip.Color((255/nb), (255/nb), (255/nb));
  } else if(WheelPos < 85) {
   return strip.Color(((WheelPos * 3)/nb), ((255 - WheelPos * 3)/nb), 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(((255 - WheelPos * 3)/nb), 0, ((WheelPos * 3)/nb));
  } else {
   WheelPos -= 170;
   return strip.Color(0, ((WheelPos * 3)/nb), ((255 - WheelPos * 3)/nb));
  }
}
