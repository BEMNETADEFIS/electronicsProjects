#include <FastLED.h>

// Ultrasonic detector
#define trigPin 8
#define echoPin 7

// LEDs
#define LED_DATA_PIN 4
#define NUM_LEDS    30
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

// Built-in LED
#define ledPin 13

void setup() {
  Serial.begin(9600);
  
  // Ultrasonic detector
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LEDs
  FastLED.addLeds<LED_TYPE, LED_DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  // Built-in LED
  //pinMode(ledPin, OUTPUT);
}

void loop() {
  //digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)

  // Ultrasonic detector
  int duration;
  int distance;
  
  // we calculate the distance
  // 1) emit the ultrasound
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);

  // waits for the pin to go HIGH, starts timing and waits for the pin to go LOW then stops timing. Returns the length of the pulse in microseconds (or 0 if no complete pulse was received within the timeout)  
  // default timeout: 1 second
  duration = pulseIn(echoPin, HIGH);

  // 2) calculate the distance
  // formula: speed = distance / time
  // distance = speed * time
  // the result must be divided by 2 to get the correct value because the signal does towards the nearest obstacle then comes back
  // we then divide the result by 29.1 to get the distance in centimeters
  distance = (duration/2) / 29.1;
  
  // print out the distance
  Serial.print(distance);
  Serial.println(" cm");

  if(distance < 200){
    // all red
    for(int currentLed = 0; currentLed < NUM_LEDS; currentLed++){
      leds[currentLed] = CRGB::Red;
    }
    FastLED.show();
    delay(500);
  }

  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();
  
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow

/*
 

  // Built-in LED
  //digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  
  delay(500);               // wait for a second
  */
}



#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(13,0,NUM_LEDS);
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
