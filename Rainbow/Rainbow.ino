#include <FastLED.h>

#define DATA_PIN 0 // change to Pin 0 for ATTiny
#define NUM_LEDS 8

CRGB strip[NUM_LEDS];

void setup() {
//FastLED.addLeds<NEOPIXEL, DATA_PIN, RGB>(strip, NUM_LEDS); // setup the strip
FastLED.addLeds<WS2812, DATA_PIN, RGB>(strip, NUM_LEDS); // setup the strip
//fill_solid( &(strip[0]), NUM_LEDS /number of leds/, CRGB::Black ); // set them all to off
//FastLED.show(); // then display the strip
}

void loop() {
// Some example procedures showing how to display to the pixels:
colorWipe(CRGB::Red, 50); // Red
colorWipe(CRGB::Green, 50); // Green
colorWipe(CRGB::Blue, 50); // Blue
// Send a theater pixel chase in…
theaterChase(CRGB::White, 50); // White
theaterChase(CRGB::Red, 50); // Red
theaterChase(CRGB::Blue, 50); // Blue

rainbow(20);
rainbowCycle(20);
theaterChaseRainbow(50);
}

void colorWipe(uint32_t c, uint8_t wait) {
for(uint16_t i=0; i<NUM_LEDS; i++) {
strip[i] = c;
FastLED.show();
delay(wait);
}
}

void rainbow(uint8_t wait) {
uint16_t i, j;

for(j=0; j<256; j++) {
for(i=0; i<NUM_LEDS; i++) {
strip[i].setHue((i+j) & 255);
}
FastLED.show();
delay(wait);
}
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
uint16_t i, j;

for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
for(i=0; i< NUM_LEDS; i++) {
strip[i].setHue(((i * 256 / NUM_LEDS) + j) & 255);
}
FastLED.show();
delay(wait);
}
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
uint16_t i,j,q;
for (j=0; j<10; j++) { //do 10 cycles of chasing
for (q=0; q < 3; q++) {
for (i=0; i+q < NUM_LEDS; i=i+3) {
strip[i+q] = c; //turn every third pixel on
}
FastLED.show();

  delay(wait);
 
  for (i=0; i+q < NUM_LEDS; i=i+3) {
    strip[i+q] = 0;        //turn every third pixel off
  }
}
}
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  uint16_t i,j,q;
  for (j=0; j < 256; j++) { // cycle all 256 colors in the wheel
    for (q=0; q < 3; q++) {
      for (i=0; i+q < NUM_LEDS; i=i+3) {
      strip[i+q].setHue((i+j) % 255); //turn every third pixel on
      }
      FastLED.show();
    
      delay(wait);
     
      for (i=0; i+q < NUM_LEDS; i=i+3) {
        strip[i+q] = 0;        //turn every third pixel off
      }
    }
  }
}
