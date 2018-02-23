#include <Adafruit_NeoPixel.h>
#define PIN 0
#define NUM_LEDS 72

#include <LiquidCrystal.h> //Load Liquid Crystal Library

LiquidCrystal LCD(11,10,9,2,3,4,5); //Create Liquid Crystal Object called LCD

#define trigPin 13 //Sensor Echo pin connected to Arduino pin 13
#define echoPin 12 //Sensor Trip pin connected to Arduino pin 12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  LCD.begin(16,2); //Tell Arduino to start your 16 column 2 row LCD
  LCD.setCursor(0,0); //Set LCD cursor to upper left corner, column 0, row 0
  LCD.print("Target Distance:"); //Print Message on First Row
}

void loop() {
  strip.setBrightness(10);
  
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  LCD.setCursor(0,1); //Set cursor to first column of second row
  LCD.print(" "); //Print blanks to clear the row
  LCD.setCursor(0,1); //Set Cursor again to first column of second row
  LCD.print(distance); //Print measured distance
  LCD.print(" cm"); //Print your units.
  delay(250); //pause to let things settle
  if (distance > 10) {
    Sparkle(random(255), random(255), random(255), 0);
  }
}


void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel,0,0,0);
}

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}
