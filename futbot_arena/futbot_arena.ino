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

#define DIST_CMP 6

MD_Parola placar = MD_Parola(HARDWARE_TYPE, M_DIN, M_CLK, M_CS, NUM_MATRIZ);
MD_MAX72XX* matriz = nullptr;

TM1637Display display(D_CLK, D_DIO);

Ultrasonic gol1(ultrasonic1[1], ultrasonic1[0]);
Ultrasonic gol2(ultrasonic2[1], ultrasonic2[0]);

byte pontos_esq = 0;
byte pontos_dir = 0;

float dist_gol1, dist_gol2;

bool pausado = true;
unsigned int segundos = 300;
unsigned long ultimoTempo = 0;
const unsigned int TEMPO_INICIAL = 300;

const uint8_t numeros[10][5] = {
  {0x7E, 0x91, 0x89, 0x85, 0x7E}, 
  {0x01, 0x01, 0xFF, 0x41, 0x21}, 
  {0x61, 0x91, 0x89, 0x85, 0x63}, 
  {0x6E, 0x91, 0x91, 0x91, 0x81},
  {0x08, 0xFF, 0x48, 0x28, 0x18}, 
  {0x8E, 0x91, 0x91, 0x91, 0xF1}, 
  {0x8E, 0x91, 0x91, 0x51, 0x3E}, 
  {0xE0, 0x90, 0x88, 0x87, 0x80}, 
  {0x6E, 0x91, 0x91, 0x91, 0x6E},
  {0x7E, 0x91, 0x91, 0x91, 0x60}  
};

void setup() {
  placar.begin();
  placar.setIntensity(8);
  placar.displayClear();
  placar.displaySuspend(false);

  matriz = placar.getGraphicObject();
  matriz->control(MD_MAX72XX::INTENSITY, 8);

  display.setBrightness(15);
  display.clear();

  pinMode(BOTAO_RESET, INPUT_PULLUP);
  pinMode(BOTAO_PAUSE, INPUT_PULLUP);

  Serial.begin(9600);

  desenhaX();
  attPlacar();


}

void loop() {
  dist_gol1 = gol1.distanceRead();
  dist_gol2 = gol2.distanceRead();

  if(dist_gol1 <= DIST_CMP || dist_gol2 <= DIST_CMP){
    if(dist_gol1 <= DIST_CMP){
      pontos_esq++;
    } else if(dist_gol2 <= DIST_CMP){
      pontos_dir++;
    }
    attPlacar();

    while (gol1.distanceRead() <= DIST_CMP || gol2.distanceRead() <= DIST_CMP){
      pausado = !pausado;
    }
  }

  if(digitalRead(BOTAO_PAUSE) == LOW){
    pausado = !pausado;
    while(digitalRead(BOTAO_PAUSE) == LOW);
  }

  if(digitalRead(BOTAO_RESET) == LOW){
    resetaTempo();
    resetaPlacar();
  }

  if(!pausado && segundos > 0 && millis() - ultimoTempo >= 1000){
  ultimoTempo = millis();
  segundos--;
  attDisplay();

    //if(segundos == 0) -> nao sei oq fazer aqui...
  }

}

void desenhaX() {
  
  for(int i = 0; i < 6; i++) {
    matriz->setPoint(1 + i, 13 + i, true);
    matriz->setPoint(1 + i, 18 - i, true);
  }

}

void attPlacar(){
  placar.displaySuspend(true);

  desenhaNumero(0, pontos_dir);
  desenhaNumero(3, pontos_esq);

  placar.displaySuspend(false);

}

void desenhaNumero(uint8_t modulo, uint8_t numero){
  uint8_t col_inicial = modulo * 8;

  for (uint8_t col = col_inicial; col < col_inicial + 8; col++) {
    for (uint8_t row = 0; row < 8; row++) {
      matriz->setPoint(row, col, false);
    }
  }

  numero = numero % 10;


  for (uint8_t col = 0; col < 5; col++) {
    for (uint8_t row = 0; row < 8; row++) {
      if (numeros[numero][col] & (1 << (7 - row))) {
        if (modulo == 3) { 
          matriz->setPoint(row, col_inicial + col + 2, true);
        } else { 
          matriz->setPoint(row, col_inicial + col + 1, true);
        }      
      }
    }
  }
}

void attDisplay(){
  uint8_t minutos = segundos / 60;
  uint8_t segs = segundos % 60;
  display.showNumberDecEx(minutos * 100 + segs, 0b01000000, true);
}

void resetaTempo(){
  segundos = TEMPO_INICIAL;
  ultimoTempo = millis();
  pausado = true;
  attDisplay();

}

void resetaPlacar(){
  pontos_esq = 0;
  pontos_dir = 0;
  attPlacar();
}