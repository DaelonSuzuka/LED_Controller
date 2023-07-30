#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 103

#define DATA_PIN 8
#define CLOCK_PIN 10

CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200);
    Serial.println("resetting");
    FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(84);
}

void fadeall() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].nscale8(250);
    }
}

void loop() {
    static uint8_t hue = 0;
    Serial.print("x");
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue++, 255, 255);
        FastLED.show();
        fadeall();
        delay(10);
    }
    Serial.print("x");

    for (int i = (NUM_LEDS)-1; i >= 0; i--) {
        leds[i] = CHSV(hue++, 255, 255);
        FastLED.show();
        fadeall();
        delay(10);
    }
}
