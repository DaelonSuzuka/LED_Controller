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

#define UPDATE_PERIOD 10

void update() {
    static uint8_t hue = 0;
    static int16_t i = 0;
    static int16_t direction = 1;
    static uint32_t lastUpdate = 0;

    uint32_t currentTime = millis();
    if (currentTime < (lastUpdate + UPDATE_PERIOD)) {
        return;
    }
    lastUpdate = currentTime;

    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();

    i += direction;

    if (i == NUM_LEDS) {
        direction = -1;
    }
    if (i == 0) {
        direction = 1;
    }
}

uint8_t updating = 0;

void loop() {
    if (Serial.available()) {
        char c = Serial.read();

        if (c == 'x') {
            updating = !updating;
        }
    }

    if (updating) {
        update(); //
    }
}
