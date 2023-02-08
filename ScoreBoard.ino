#include "LedControl.h"
#include <Adafruit_NeoPixel.h>
#define HARDWARE_TYPE MD_MAX7219::ICSTATION_HW
#define PIN1 7
#define PIN2 8
#define NUMPIXELS 24
#define button 10


LedControl lc = LedControl(5, 3, 4, 4); // Pins: DIN,CLK,CS, # of Display connected

Adafruit_NeoPixel p1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel p2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel pixels[2] = {

  p1,
  p2

};


long rnd;


byte sayilar[10][8] = {
  {
    0b00111000,
    0b01000100,
    0b01000100,
    0b01000100,
    0b01000100,
    0b01000100,
    0b01000100,
    0b00111000
  }, {
    0b00010000,
    0b00110000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00111000
  }, {
    0b00111000,
    0b01000100,
    0b00000100,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01111100
  }, {
    0b00111000,
    0b01000100,
    0b00000100,
    0b00011000,
    0b00000100,
    0b00000100,
    0b01000100,
    0b00111000
  }, {
    0b00000100,
    0b00001100,
    0b00010100,
    0b00100100,
    0b01000100,
    0b01111100,
    0b00000100,
    0b00000100
  }, {
    0b01111100,
    0b01000000,
    0b01000000,
    0b01111000,
    0b00000100,
    0b00000100,
    0b01000100,
    0b00111000
  }, {
    0b00111000,
    0b01000100,
    0b01000000,
    0b01111000,
    0b01000100,
    0b01000100,
    0b01000100,
    0b00111000
  }, {
    0b01111100,
    0b00000100,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b00100000,
    0b00100000
  }, {
    0b00111000,
    0b01000100,
    0b01000100,
    0b00111000,
    0b01000100,
    0b01000100,
    0b01000100,
    0b00111000
  }, {
    0b00111000,
    0b01000100,
    0b01000100,
    0b01000100,
    0b00111100,
    0b00000100,
    0b01000100,
    0b00111000
  }
};


void setup()
{
  pinMode(button, INPUT);

  p1.begin();
  p2.begin();

  Serial.begin(9600);
  lc.shutdown(0, false); // Wake up displays
  lc.shutdown(1, false);
  lc.shutdown(2, false);
  lc.shutdown(3, false);
  lc.setIntensity(0, 5); // Set intensity levels
  lc.setIntensity(1, 5);
  lc.setIntensity(2, 5);
  lc.setIntensity(3, 5);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
  halkaSondur(0);
  halkaSondur(1);
}



void sayiYaz(int digit, int sayi) {
  for (int i = 0; i < 8; i++) {
    lc.setRow(digit, i, sayilar[sayi][i]);
  }
}


void skorYaz(int skor) {
  int hane1 = skor / 1000;
  int hane2 = (skor % 1000) / 100;
  int hane3 = (skor % 100) / 10;
  int hane4 = skor % 10;

  sayiYaz(3, hane1);
  sayiYaz(2, hane2);
  sayiYaz(1, hane3);
  sayiYaz(0, hane4);

}

void halkaYak(int sira) {
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels[sira].setPixelColor(i, pixels[sira].Color(random(255), random(255), random(255)));
    pixels[sira].show();
    delay (10);
    Serial.println("Yandı");

  }

}
void halkaSondur(int sira) {
  for (int i = 0; i < NUMPIXELS; i++) {


    pixels[sira].setPixelColor(i, pixels[sira].Color(0, 0, 0));
    pixels[sira].show();
    delay (10);


  }


}


void loop()
{

  if (digitalRead(button) == LOW) {

    halkaSondur(0);
    Serial.println("butona basildi");
  } else {
    halkaYak(0);
    Serial.println("halka yakıldi");
  }


  skorYaz(2023);
}
