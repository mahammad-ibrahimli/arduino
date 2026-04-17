#include "LedControl.h"

#define DIN_PIN 12
#define CLK_PIN 11
#define CS_PIN  10

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

// N U B A R hərfləri
const uint8_t NUBAR[][8] = {
{ // N
  0b00000000,
  0b01100110,
  0b01110110,
  0b01111110,
  0b01101110,
  0b01100110,
  0b01100110,
  0b00000000
},
{ // U
  0b00000000,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b00111100,
  0b00000000
},
{ // B
  0b00000000,
  0b01111100,
  0b01100110,
  0b01111100,
  0b01100110,
  0b01100110,
  0b01111100,
  0b00000000
},
{ // A
  0b00000000,
  0b00111100,
  0b01100110,
  0b01100110,
  0b01111110,
  0b01100110,
  0b01100110,
  0b00000000
},
{ // R
  0b00000000,
  0b01111100,
  0b01100110,
  0b01111100,
  0b01101100,
  0b01100110,
  0b01100110,
  0b00000000
}
};

// Ürək fiquru
const uint8_t UREK[8] = {
  0b00000000,
  0b01100110,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00000000
};

const int HERF_SAYI = sizeof(NUBAR) / 8;
uint8_t buffer[8] = {0,0,0,0,0,0,0,0};

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 15); 
  lc.clearDisplay(0);
}

void loop() {

  // Sürüşən yazı
  for (int h = 0; h < HERF_SAYI; h++) {
    for (int col = 0; col < 8; col++) {
      for (int row = 0; row < 8; row++) {
        buffer[row] <<= 1;
        if (NUBAR[h][row] & (0x80 >> col)) {
          buffer[row] |= 0x01;
        }
        lc.setRow(0, row, buffer[row]);
      }
      delay(90);
    }
  }

  delay(800);

  // Ürək effekti
  lc.clearDisplay(0);
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, UREK[row]);
  }

  for (int i = 0; i < 3; i++) {
    for (int b = 0; b <= 15; b++) {
      lc.setIntensity(0, b);
      delay(30);
    }
    for (int b = 15; b >= 0; b--) {
      lc.setIntensity(0, b);
      delay(30);
    }
  }

  for (int i = 0; i < 8; i++) buffer[i] = 0;
  lc.clearDisplay(0);
  delay(500);
}