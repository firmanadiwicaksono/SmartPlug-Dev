#include "LedRGB.h"
#include <Arduino.h>

//Private
void LedRGB::HSVtoRGB(float inH, float inS, float inV, float& outR, float& outG, float& outB) {
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk konversi ruang warna HSV ke ruang warna RGB.
  */

  float C = inV * inS;
  float hPrime = fmod(inH / 60.0, 6);
  float X = C * (1 - fabs(fmod(hPrime, 2) - 1));
  float M = inV - C;
  
  if(0 <= hPrime && hPrime < 1) {
    outR = C;
    outG = X;
    outB = 0;
  }else
  if(1 <= hPrime && hPrime < 2) {
    outR = X;
    outG = C;
    outB = 0;
  }else
  if(2 <= hPrime && hPrime < 3) {
    outR = 0;
    outG = C;
    outB = X;
  }else
  if(3 <= hPrime && hPrime < 4) {
    outR = 0;
    outG = X;
    outB = C;
  }else
  if(4 <= hPrime && hPrime < 5) {
    outR = X;
    outG = 0;
    outB = C;
  }else
  if(5 <= hPrime && hPrime < 6) {
    outR = C;
    outG = 0;
    outB = X;
  }else{
    outR = 0;
    outG = 0;
    outB = 0;
  }
  
  outR += M;
  outG += M;
  outB += M;
}
//------------------------------------------------------------------------------

//Public
LedRGB::LedRGB(int pinR, int pinG, int pinB, int channelR, int channelG, int channelB){
  /*
  Spesifikasi :
  - Constructor ini digunakan untuk inisialisasi objek kelas LedPWM R, G, dan B.
  */

  R.begin(pinR, channelR, freq, resolution);
  G.begin(pinG, channelG, freq, resolution);
  B.begin(pinB, channelB, freq, resolution);

  R.setDutyCycle(0);
  G.setDutyCycle(0);
  B.setDutyCycle(0);
}

void LedRGB::setRGB(int valR, int valG, int valB){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk mengatur nilai PWM R, G, dan B.
  */

  R.setDutyCycle(valR);
  G.setDutyCycle(valG);
  B.setDutyCycle(valB);
}

void LedRGB::setBlack(){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk mematikan Led RGB.
  */

  setRGB(0, 0, 0);
}

void LedRGB::setRed(){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk membuat Led RGB menyala dengan warna merah.
  */

  setRGB(255, 0 , 0);
}

void LedRGB::setGreen(){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk membuat Led RGB menyala dengan warna hijau.
  */

  setRGB(0, 255, 0);
}

void LedRGB::rainbow(int delayStep){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk membuat Led RGB menyala dengan perubahan warna
    dengan warna berdasarkan perubahan komponen ruang warna H dari 0-360.
  - Setiap perubahan warna memiliki inverval berdasarkan delayStep.
  */

  float R, G, B;
  for(int i = 0; i <= 360; i++){
    HSVtoRGB(i, 100, 100, R, G, B);
    setRGB((int)(R * 255), (int)(G * 255), (int)(B * 255));
    delay(delayStep);
  }
}
//------------------------------------------------------------------------------
