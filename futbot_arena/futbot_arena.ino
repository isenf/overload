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
#define TYPE_MATRIZ MD_MAX72XX::FC16HW

#define BOTAO_PAUSE 8
#define BOTAO_RESET 9

#define D_DIO 2
#define D_CLK 3

MD_Parola placar = MD_Parola(TYPE_MATRIZ, M_DIN, M_CLK, M_CS, NUM_MATRIZ);
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

}

/*
matriz: din 11; cs 10; clk 13;
display: dio 2; clk 3;

gol 1: echo 4; trig 5;
gol 2: echo 6; trig 7;

botao pause: 8
botao reset: 9

*/

void loop() {

  
}
