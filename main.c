#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define NUM_PIXELS 16

//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_RGBW + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(1);
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

enum Mode {
  SUCCESS = 0,
  FAILURE = 1,
  IN_PROGRESS = 2,
  ENDED = 3,
};

Mode mode = IN_PROGRESS;
void loop() {
  if (Serial.available() > 0) {
    unsigned char new_mode = Serial.read();
    Serial.print("Received: ");
    Serial.println(new_mode, DEC);

    // Expect to get ASCII digit representing Mode.
    unsigned int ascii_zero = 48;
    if (new_mode >= ascii_zero && new_mode <= ascii_zero + ENDED) {
      mode = new_mode - ascii_zero;
    }
  }

  switch (mode) {
    case SUCCESS:
      colorSpin(strip.Color(255, 0, 0), 50, false); // Green
      break;
    case FAILURE:
      colorSpin(strip.Color(0, 255, 0), 50, false); // Red
      break;
    case IN_PROGRESS:
      colorSpin(strip.Color(255, 255, 0), 50, true); // Yellow
      break;
    case ENDED:
      colorSpin(strip.Color(0, 0, 0), 50, false); // Nothing
      break;
  }
}

// Which pixel is "first", i.e. beside power cord?
#define FIRST 9
void colorSpin(uint32_t c, uint8_t wait, bool wipe) {
  for(uint16_t i=0; i < NUM_PIXELS; i++) {
    // Starting with the first pixel, spin in a CW direction.
    int pixel_idx = (FIRST + (NUM_PIXELS - 1) - i) % NUM_PIXELS;

    // Show the chosen color.
    strip.setPixelColor(pixel_idx, c);
    strip.show();
    delay(wait);

    // Optionally clear the pixel.
    if (wipe) {
      strip.setPixelColor(pixel_idx, 0);
    }
  }
}
