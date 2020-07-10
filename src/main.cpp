#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

// Status LED
#define LED_PIN  1

// Neopixel(s)
#define DATA_PIN 4
#define NUM_LEDS 1
#define NEO_IO   (NEO_GRB+NEO_KHZ800)

// Rainbowspeed
#define DELAY_MS 100

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_IO);

// Color wheel through the rainbow
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
      return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
      WheelPos -= 85;
      return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
      WheelPos -= 170;
      return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

// Increment color of neopixels
void rainbow( uint32_t delay_ms ) {
  static uint8_t step = 0;
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + step) & 255));
  }
  strip.show();
  step++;
  delay(delay_ms);
}

// Set all pixels to one color
void color( uint32_t c, uint32_t delay_ms ) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(delay_ms);
}

void setup() {
  // Status LED on to show we are alive
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  // Set strip to medium white to see if all colors of all pixels work
  strip.begin();
  color(strip.Color(128,128,128), DELAY_MS);

  // Status LED off: init done
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Cycle neopixels through rainbow colors
  rainbow(DELAY_MS);
}