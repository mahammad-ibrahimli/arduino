#include "LedControl.h"

#define DIN_PIN 12  // Data (DIN)
#define CLK_PIN 11  // Clock (CLK)
#define CS_PIN  10  // Chip Select (CS)

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

const uint8_t NERMIN[][8] = {
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
{ // E
  0b00000000,
  0b01111110,
  0b01100000,
  0b01111100,
  0b01100000,
  0b01100000,
  0b01111110,
  0b00000000
},
{ // R
  0b00000000,
  0b01111100,
  0b01100110,
  0b01111100,
  0b01111000,
  0b01101100,
  0b01100110,
  0b00000000
},
{ // M
  0b00000000,
  0b01100011,
  0b01110111,
  0b01111111,
  0b01101011,
  0b01100011,
  0b01100011,
  0b00000000
},
{ // I
  0b00000000,
  0b00111100,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00111100,
  0b00000000
},
{ // N
  0b00000000,
  0b01100110,
  0b01110110,
  0b01111110,
  0b01101110,
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

const int HERF_SAYI = sizeof(NERMIN) / 8;
uint8_t buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0}; 

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 5); // Başlanğıc parlaqlıq
  lc.clearDisplay(0);
}

void loop() {
  // 1. YAZININ SÜRÜŞMƏSİ (SCROLL)
  lc.setIntensity(0, 5); // Yazı sabit parlaqlıqda keçsin
  for (int h = 0; h < HERF_SAYI; h++) {
    for (int col = 0; col < 8; col++) {
      for (int row = 0; row < 8; row++) {
        buffer[row] = buffer[row] << 1;
        if (NERMIN[h][row] & (0x80 >> col)) {
          buffer[row] |= 0x01;
        }
        lc.setRow(0, row, buffer[row]);
      }
      delay(80); 
    }
  }

  // 2. DÖYÜNƏN ÜRƏK EFFEKTİ
  lc.clearDisplay(0);
  
  // Ürəyi ekrana çək (amma parlaqlıq hələ 0 olacaq)
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, UREK[row]);
  }

  // 3 dəfə döyünsün
  for (int i = 0; i < 3; i++) {
    // Yavaş-yavaş yansın (Fade In)
    for (int brightness = 0; brightness <= 15; brightness++) {
      lc.setIntensity(0, brightness);
      delay(30); // Parlama sürəti
    }
    
    // Yavaş-yavaş sönsün (Fade Out)
    for (int brightness = 15; brightness >= 0; brightness--) {
      lc.setIntensity(0, brightness);
      delay(30); // Sönmə sürəti
    }
    delay(200); // İki döyüntü arası qısa fasilə
  }

  // Bufferi sıfırla ki yazı yenidən təmiz başlasın
  for(int i=0; i<8; i++) buffer[i] = 0;
  lc.clearDisplay(0);
  delay(500);
}