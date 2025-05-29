#include <LedControl.h>
#include <Ultrasonic.h>

int const gol1[] = {4, 5};
int const gol2[] = {8, 9};

#define DIN 11
#define CS 10
#define CLK 13
#define NUM_MATRIZ 4

LedControl placar = LedControl(DIN, CS, CLK, NUM_MATRIZ);

byte pontos_esq = 0;
byte pontos_dir = 0;

void setup() {

  for(int i = 0; i < NUM_MATRIZ; i++){
    placar.shutdown(i, false);
    placar.shutdown(i, 8); // 8 -> brilho
    placar.clearDisplay(i);
  }

  


}

void loop() {
  // put your main code here, to run repeatedly:

}
