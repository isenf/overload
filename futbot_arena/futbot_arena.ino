#include <Ultrasonic.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <TM1637Display.h>//nao eh certeza

int const ultrasonic1[] = {4, 5};// echo, trig
int const ultrasonic2[] = {6, 7}; 

#define M_DIN 11
#define M_CS 10
#define M_CLK 13
#define NUM_MATRIZ 4
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

#define BOTAO_PAUSE 8
#define BOTAO_RESET 9

#define D_DIO 2
#define D_CLK 3

MD_Parola placar = MD_Parola(HARDWARE_TYPE, M_DIN, M_CLK, M_CS, NUM_MATRIZ);
//MD_MAX72XX  matriz(HARDWARE_TYPE, M_DIN, M_CLK, M_CS, NUM_MATRIZ); -> causa conflito

TM1637Display display(D_CLK, D_DIO);

Ultrasonic gol1(ultrasonic1[1], ultrasonic1[0]);
Ultrasonic gol2(ultrasonic2[1], ultrasonic2[0]);

byte pontos_esq = 0;
byte pontos_dir = 0;

void setup() {
  placar.begin();
  placar.setIntensity(8);
  placar.displayClear();
  placar.displaySuspend(false);

  display.setBrightness(8);
  display.clear();

  pinMode(BOTAO_RESET, INPUT_PULLUP);
  pinMode(BOTAO_PAUSE, INPUT_PULLUP);

  Serial.begin(9600);
  desenhaX();


}

void loop() {
  
}

//esta função funciona diferente no wokwi, forma um <>
void desenhaX() {
  MD_MAX72XX *mx = placar.getGraphicObject();
  
  for(int i = 0; i < 6; i++) {
    mx->setPoint(1 + i, 13 + i, true);
    mx->setPoint(1 + i, 18 - i, true);
  }
}
