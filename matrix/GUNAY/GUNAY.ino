#include "LedControl.h"

#define DIN_PIN 12  // Data (DIN)
#define CLK_PIN 11  // Clock (CLK)
#define CS_PIN  10  // Chip Select (CS)

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

// IT BRAINS ACADEMY hərfləri
const uint8_t IT_BRAINS[][8] = {
{ // I
  0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000
},
{ // T
  0b01111110, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000
},
{ // Boşluq
  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000
},
{ // B
  0b01111100, 0b01100110, 0b01100110, 0b01111100, 0b01100110, 0b01100110, 0b01111100, 0b00000000
},
{ // R
  0b01111100, 0b01100110, 0b01100110, 0b01111100, 0b01101100, 0b01100110, 0b01100110, 0b00000000
},
{ // A
  0b00111100, 0b01100110, 0b01100110, 0b01111110, 0b01100110, 0b01100110, 0b01100110, 0b00000000
},
{ // I
  0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000
},
{ // N
  0b01100110, 0b01110110, 0b01111110, 0b01101110, 0b01100110, 0b01100110, 0b01100110, 0b00000000
},
{ // S
  0b00111100, 0b01100000, 0b01100000, 0b00111100, 0b00000110, 0b00000110, 0b00111100, 0b00000000
},
{ // Boşluq
  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000
},
{ // A
  0b00111100, 0b01100110, 0b01100110, 0b01111110, 0b01100110, 0b01100110, 0b01100110, 0b00000000
},
{ // C
  0b00111100, 0b01100110, 0b01100000, 0b01100000, 0b01100000, 0b01100110, 0b00111100, 0b00000000
},
{ // A
  0b00111100, 0b01100110, 0b01100110, 0b01111110, 0b01100110, 0b01100110, 0b01100110, 0b00000000
},
{ // D
  0b01111000, 0b01100100, 0b01100110, 0b01100110, 0b01100110, 0b01100100, 0b01111000, 0b00000000
},
{ // E
  0b01111110, 0b01100000, 0b01100000, 0b1111110, 0b01100000, 0b01100000, 0b01111110, 0b00000000
},
{ // M
  0b01100110, 0b01111110, 0b01111110, 0b01101110, 0b01100110, 0b01100110, 0b01100110, 0b00000000
},
{ // Y
  0b01100110, 0b01100110, 0b01100110, 0b00111100, 0b00011000, 0b00011000, 0b00011000, 0b00000000
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

const int HERF_SAYI = sizeof(IT_BRAINS) / 8;
uint8_t buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0}; 

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 5);
  lc.clearDisplay(0);
}

void loop() {
  // 1. Mətnin sürüşməsi
  lc.setIntensity(0, 5);
  for (int h = 0; h < HERF_SAYI; h++) {
    for (int col = 0; col < 8; col++) {
      for (int row = 0; row < 8; row++) {
        buffer[row] = buffer[row] << 1;
        if (IT_BRAINS[h][row] & (0x80 >> col)) {
          buffer[row] |= 0x01;
        }
        lc.setRow(0, row, buffer[row]);
      }
      delay(90); 
    }
  }
  delay(500);

  // 2. Ürək effekti (yanıb sönmə)
  lc.clearDisplay(0);
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, UREK[row]);
  }

  for (int i = 0; i < 3; i++) {
    for (int brightness = 0; brightness <= 15; brightness++) {
      lc.setIntensity(0, brightness);
      delay(30);
    }
    for (int brightness = 15; brightness >= 0; brightness--) {
      lc.setIntensity(0, brightness);
      delay(30);
    }
    delay(200);
  }

  // Təmizləmə və yenidən başlama
  for(int i=0; i<8; i++) buffer[i] = 0;
  lc.clearDisplay(0);
  delay(500);
}