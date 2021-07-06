#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library
#include <EEPROM.h> // biblioteca usada para guardar valores do ranking

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

#define RED 0xF800
#define BLACK 0x0000
#define GREEN 0x07E0
#define GREEN2 0x2727
#define WHITE 0xFFFF
#define BLUE 0x5F5F
#define LIGHTBLUE 0x5E5E
#define YELLOW 0xFFE0
#define PINK 0xF81F
#define GREY 0x0003
#define ORANGE 0xFD20  

#define MOVE_BUTTON 7
#define SELECT_BUTTON 6

const PROGMEM uint16_t ze[] {
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0x000000, 0x000000, 
    0x000000, 0xdeb683, 0xdeb683, 0x3d2304, 0x3d2304, 0x3d2304, 0x3d2304, 0xdeb683, 0xdeb683, 0x3d2304, 0x3d2304, 0x3d2304, 0x3d2304, 0xdeb683, 0xdeb683, 0x000000, 
    0x000000, 0xdeb683, 0xc7a376, 0xdeb683, 0xccd9e3, 0x3035c9, 0xdeb683, 0xdeb683, 0xc7a376, 0xdeb683, 0x3035c9, 0xe3f2fd, 0xdeb683, 0xc7a376, 0xdeb683, 0x000000, 
    0x000000, 0xdeb683, 0xc7a376, 0xdeb683, 0xe3f2fd, 0x3035c9, 0xdeb683, 0xc7a376, 0xdeb683, 0xdeb683, 0x3035c9, 0xccd9e3, 0xdeb683, 0xc7a376, 0xdeb683, 0x000000, 
    0x000000, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xc7a376, 0xdeb683, 0xc7a376, 0xdeb683, 0xdeb683, 0xc7a376, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0x000000, 
    0x000000, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0x000000, 
    0x000000, 0x000000, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xaf4b68, 0xaf4b68, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0xdeb683, 0x000000, 0x000000, 0x000003, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x116ade, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x28ab48, 0x28ab48, 0x116ade, 0x28ab48, 0x28ab48, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x116ade, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x116ade, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x116ade, 0x000000, 0x116ade, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xc78dc7, 0xc78dc7, 0x000000, 0xc78dc7, 0xc78dc7, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
};

unsigned long startMillis;
unsigned long startMillis2;
unsigned long currentMillis;
unsigned long zeMillis;
unsigned long scoreMillis;

void menu_principal(int y);
void jogar();
void ranking();
void sobre();
void creditos();
void abertura();
void cenario();
void gameOver();
float dificuldade(float vel);
void dificuldade_menu();
void cadastroPlayer(int score);
void resetRanking();
int moveCursor(int y);

int y = 80; // coordenada y do MOVECURSOR()

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);



void setup() {
  Serial.begin(9600);
  tft.init(240, 240, SPI_MODE2);
  pinMode(MOVE_BUTTON, INPUT);
  pinMode(SELECT_BUTTON, INPUT);
  tft.setRotation(2);
  abertura();
  tft.fillScreen(LIGHTBLUE);
  startMillis = millis();
  startMillis2 = millis();
  randomSeed(analogRead(A0));
}



void loop() {
  if (digitalRead(SELECT_BUTTON) == HIGH && digitalRead(MOVE_BUTTON) == HIGH) {
      resetRanking();
  }
  else if (digitalRead(MOVE_BUTTON) == HIGH) {
    delay(150);
    y = moveCursor(y);
  }
  else if (digitalRead(SELECT_BUTTON) == HIGH) {
    tft.fillScreen(BLACK);
    tft.setTextSize(2);

    switch (y) {
      case 80:
          jogar();
          break;
      case 120:
          ranking();
          break;
      case 160:
          sobre();
          break;         
      case 200:
          creditos();
          break;       
      default:
        break;
    }
    y = 80;
    tft.fillScreen(LIGHTBLUE);
  }
  menu_principal(y);
}



void menu_principal(int y){
  tft.drawRect(4, 4, 230, 230, WHITE);
  
  tft.setTextColor(WHITE, LIGHTBLUE);
  tft.setTextSize(4);
  tft.setCursor(36, 20);
  tft.print("Job Run");

  tft.setTextSize(2);
  tft.fillRect(50, 80, 10, 15, LIGHTBLUE);
  tft.fillRect(50, 120, 10, 15, LIGHTBLUE);
  tft.fillRect(50, 160, 10, 15, LIGHTBLUE);
  tft.fillRect(50, 200, 10, 15, LIGHTBLUE);
  tft.fillRect(172, 80, 10, 15, LIGHTBLUE);
  tft.fillRect(172, 120, 10, 15, LIGHTBLUE);
  tft.fillRect(160, 160, 10, 15, LIGHTBLUE);
  tft.fillRect(180, 200, 10, 15, LIGHTBLUE);

  
  tft.setCursor(50, y);
  tft.print('>');
  if(y == 200){
    tft.setCursor(180, y);
    tft.print('<');
  }else if (y == 160){
    tft.setCursor(160, y);
    tft.print('<');
  }else{
    tft.setCursor(172, y);
    tft.print('<');
  }

  
  
  tft.setTextColor(RED, LIGHTBLUE);
  tft.setTextSize(2);
  tft.setCursor(85, 80);
  tft.print("JOGAR");

  tft.setTextSize(2);
  tft.setCursor(78, 120);
  tft.print("RANKING");

  tft.setTextSize(2);
  tft.setCursor(85, 160);
  tft.print("SOBRE");

  tft.setTextSize(2);
  tft.setCursor(75, 200);
  tft.print("CREDITOS");
}

int moveCursor(int y){
  y += 40; 
  if(y > 200){
    y = 80;
  }
  return y;
}



void dificuldade_menu(){
  tft.fillScreen(LIGHTBLUE);
  tft.setCursor(20,20);
  tft.setTextSize(3);
  tft.print("DIFICULDADE");
  tft.setCursor(70, 100);
  tft.print("BRABA");
  tft.setCursor(70, 140);
  tft.print("IMORAL");
  
}



float dificuldade(float vel){
  int h = 100;
  dificuldade_menu();
  tft.setCursor(50, h);
  tft.print(">");
  while (1) {
    if (digitalRead(MOVE_BUTTON) == HIGH) {
        delay(150);
        if(h == 100){
          h = 140;
          tft.fillRect(40, 100, 25, 31, LIGHTBLUE);
          tft.setCursor(40, h);
          tft.print(">");
        }else{
            h = 100;
            tft.fillRect(40, 140, 20, 30, LIGHTBLUE);
            tft.setCursor(40, h);
            tft.print(">");
        }
    }
    else if(digitalRead(SELECT_BUTTON) == HIGH){
      switch(h){
        case 100 : vel = 2.0;break;
        case 140: 
          vel = 2.5;
          tft.fillScreen(GREY);
          tft.setTextColor(YELLOW, GREY);
          tft.setCursor(60,60);
          tft.setTextSize(3);
          tft.print("PREPARE");
          tft.setCursor(90, 120);
          tft.print("SEU");
          tft.setCursor(80, 180);
          tft.print("DEDO");
         
          delay(1500);
          break;
      }
      tft.fillScreen(GREY);
      return vel;
    }
  }
}



void jogar() {
  float x = 210;
  int tam_x_ze = 16;
  int tam_y_ze = 16;
  float vel = dificuldade(vel);// vai receber a velocidade da func dificuldade
  float coord_y = 140;
  float coord_x = 30;
  float xe = 220;
  float ye = 140;
  float tijolo_y = 140;
  int i;int score = 0; int flag;
  int j; int tempo = 0;
  unsigned const int energeticoMillis = millis();
  
  cenario();
  currentMillis = millis();
  scoreMillis = millis();
  tft.setTextColor(YELLOW, BLUE);
  tft.setCursor(80, 20);
  tft.setTextSize(2);
  tft.print("Score"); 

  while (digitalRead(MOVE_BUTTON) == LOW) {
    tft.fillRect(x, tijolo_y, 15, 10, ORANGE); // FUNCAO DO INIMIGO
    tft.fillRect(xe, ye, 8, 15, GREEN);// FUNCAO DO ENERGETICO
    if(energeticoMillis - startMillis2 >= 100){// millis do energetico
      xe-= 0.4;// faz o energetico vim
      if(xe <= 0){
        tft.fillRect(xe, ye, 12, 15, GREY);// apaga ele
        xe = 220;// volta pro inicio
         if (random(0, 2) == 0) {// faz ele vim em direções randomicas
          ye = 80;
        }
        else {
          ye = 140;
        }
      }
      if (xe >= 0 && xe <= coord_x + 20 && ye == coord_y) {
         if (vel == 2.0) {
          score+= 2;// da score no energetico baseado na dificuldade escolhida
         }
         else {
          score += 4;
         }
          tft.fillRect(xe, ye, 12, 15, GREY);// apaga o energetico
          xe = 220;
      }
      Serial.println(vel);
      tft.fillRect(xe+10, ye, 8, 15, GREY);
    }
      
    if (currentMillis - startMillis >= 500) {
      x-= vel;//diminui de acordo com a vel escolhida
      
      
      if (x <= 0) {
        if(scoreMillis - startMillis >= 1000){// controla o score, cada vez que bate na borda, add 1
            tft.setCursor(150,20); 
            tft.setTextColor(WHITE, BLUE);
            tft.print(score);
            score++;
        }
        tft.fillRect(x, tijolo_y, 18, 10, GREY);
        x = 210;
        if (random(0, 2) == 0) {
          tijolo_y = 80;
        }
        else {
          tijolo_y = 140;
        }
      }
       else if (x >= 0 && x <= coord_x && tijolo_y == coord_y) {
        gameOver();
        cadastroPlayer(score);
        break;
       }
      //tft.fillRect(x, 220, 15, 15, GREEN);
        tft.fillRect(x+15, tijolo_y, 15, 10, GREY);    
    }
    
    if (digitalRead(SELECT_BUTTON) == HIGH) {
     zeMillis = millis();// millis do ze
      if (zeMillis - startMillis >= 200){
        startMillis = zeMillis;
        if (coord_y == 140){ // rua de baixo
          tft.fillRect(coord_x,coord_y, tam_x_ze, tam_y_ze,GREY);// desaparece da cord y atual
          coord_y = 80;
          tft.drawRGBBitmap(coord_x, coord_y, ze, tam_x_ze, tam_y_ze);//aparece na proxima
        }
        else if (coord_y == 80) { // rua de cima
            tft.fillRect(coord_x,coord_y, tam_x_ze, tam_y_ze,GREY); 
            coord_y = 140;
            tft.drawRGBBitmap(coord_x, coord_y, ze, tam_x_ze, tam_y_ze); 
        }
      }
    }
  }
}



void ranking() {
  int address = 0; // guarda o valor no endereco de memoria EEPROM
  byte value; // le o valor do EEPROM 
  char alfabeto[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  int tabelaASCII[26] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};
  int i, j;
  int counter = 0;
  int x = 60; // variavel de controle x do setCursor
  int y = 40; // variavel de controle y do setCursor

  tft.setTextColor(BLUE, BLACK);
  tft.setTextSize(2);
  tft.setCursor(80, 2);
  tft.print("TOP 10");

  // mostra jogadores e suas respectivas pontuacoes

  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(2);
  
  for (i = 0; i < 50; i++) {
    counter += 1;
    value = EEPROM.read(i); // le valor em bytes
    if (counter % 5 == 0) { // score
      tft.setCursor(x+40, y);
      tft.print(value);
      y += 20;
      x = 60;
    }
    else { // nome
      for (j = 0; j < 26; j++) {
        if (value == tabelaASCII[j]) { // compara valor em bytes com a tabela ASCII
          tft.setCursor(x, y); 
          tft.print(alfabeto[j]); // escreve na tela a letra correspondente
          x += 20; // direciona o proximo set cursor para o lado
        }
      } 
    }
  }
  
  while (digitalRead(MOVE_BUTTON) == LOW) { // espera o usuario pressionar o botao
     continue;
  }
}



void sobre() {
  tft.setTextSize(2);

  tft.setTextColor(BLUE, BLACK);
  tft.setCursor(10, 20);
  tft.print("BOTAO ESQUERDO:");

  tft.setTextColor(WHITE, BLACK);
  tft.setCursor(40, 50);
  tft.print("ALTERA ENTRE");
  tft.setCursor(40, 70);
  tft.print("AS DIRECOES");

  tft.setTextColor(BLUE, BLACK);
  tft.setCursor(10, 100);
  tft.print("BOTAO DIREITO:");

  tft.setTextColor(WHITE, BLACK);
  tft.setCursor(40, 130);
  tft.print("FECHA O JOGO");
  tft.setCursor(110, 150);
  tft.print("OU");
  tft.setCursor(40, 170);
  tft.print("SAI DAS OPCOES");

  tft.setTextColor(BLUE, BLACK);
  tft.setCursor(20, 200);
  tft.print("PRESSIONE AMBOS");
  tft.setCursor(20, 220);
  tft.print("PARA RST O RANKING");

  while (digitalRead(MOVE_BUTTON) == LOW) {
    continue;
  }
}



void creditos() {
  int x = 10;
  tft.setCursor(40, 20);
  tft.setTextSize(3);
  tft.setTextColor(BLUE, BLACK);
  tft.print("JLG TEAM");

  tft.setTextSize(2);
  tft.setTextColor(WHITE, BLACK);
  
  tft.setCursor(x, 80);
  tft.print("BEKER - DEV&DSGN");
  tft.setCursor(x, 120);
  tft.print("FIDELIS - DEV&DSGN");
  tft.setCursor(x, 160);
  tft.print("MIGLIORINI - DEV");
  tft.setCursor(x, 200);
  tft.print("VICTORIA - DEV");
  
  while (digitalRead(MOVE_BUTTON) == LOW) {
    continue;
  }
}



void abertura(){
    int n;
    tft.fillScreen(BLACK);
    for(n = 0; n < 240; n++){
      for(int h = 0; h < 240; h++){
        tft.drawFastVLine(n, h, 5, PINK);
      }
    }
    tft.setCursor(60, 80);
    tft.setTextSize(3);
    tft.setTextColor(BLACK, PINK);
    tft.print("JLG");
    tft.setCursor(60, 120);
    tft.setTextSize(2);
    tft.print("apresenta...");
    delay(2000);
    tft.fillScreen(BLACK);
    tft.setCursor(45,80);
    tft.setTextSize(3);
    tft.setTextColor(YELLOW, BLACK);
    tft.print("JOB RUN");
    tft.setCursor(24,120);
    tft.setTextSize(2);
    tft.print("Run of your live");
    delay(1500);
    tft.fillScreen(BLACK);
    tft.setTextColor(RED, BLACK);
    tft.setTextSize(3);
    tft.setCursor(35, 100);
    tft.print("Loading..."); 
    tft.drawRect(5, 180, 230, 220, WHITE);
    for(n = 5; n <= 235; n++){
      for(int k = 180; k <= 240; k++){
        tft.drawFastVLine(n, k, 5, WHITE);
      }
    }
    delay(1500); 
}



void cenario(){
    int tam_x_ze = 16;
    int tam_y_ze = 16;
  
   tft.fillScreen(GREY);
   tft.fillRect(0, 0, 240, 70, BLUE);//ceu
   tft.fillRect(0, 170, 240, 240, GREEN2);//grama
   for(int n = 20; n < 240;n+= 40){//faz as flores
     for(int h = 180; h < 240; h += 20 ){
        tft.fillRect(n, h, 5, 5, RED);
     }
   }
  tft.drawLine(0, 120, 240, 120, YELLOW);//faixa amarela 
  tft.drawRGBBitmap(30, 140, ze, tam_x_ze, tam_y_ze);//ze
}



void gameOver() {
      tft.fillScreen(BLUE);
      tft.setCursor(75, 80);
      tft.setTextColor(BLACK, BLUE);
      tft.setTextSize(4);
      tft.print("GAME");
      tft.setCursor(75, 120);
      tft.print("OVER");
      delay(2000);
      tft.fillScreen(BLUE);
}



void cadastroPlayer(int score) {
  int address = 0; // guarda o valor no endereco de memoria EEPROM
  byte value; // le o valor do EEPROM 
  int i, j, n, pos, t;
  int counter = 0;
  int controle_posicao = 70;
  char alfabeto[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  char nome[4] = {'A', 'A', 'A', 'A'};
  byte troca[50];
  
  tft.setTextSize(2);
  tft.setCursor(30, 40);
  tft.print("INSIRA SEU NICK");

  tft.setTextSize(2);
  tft.setCursor(20, 200);
  tft.print("Score:");
  tft.setCursor(100, 200);
  tft.print(score);
  tft.setCursor(150, 200);
  //tft.print(Tempo);

  
  tft.setTextSize(3);
  i = 0;
  pos = -1;
  while (i < 4) {
      tft.setCursor(controle_posicao, 150);
      tft.print('-');
      tft.setCursor(controle_posicao, 120);
      if (digitalRead(SELECT_BUTTON) == HIGH) {
        pos += 1;
        if (pos > 25) {
          pos = 0;
        }
        
        nome[i] = alfabeto[pos];
        tft.setCursor(controle_posicao, 120);
        tft.print(nome[i]);
      }
      else if (digitalRead(MOVE_BUTTON) == HIGH) {
        i++;
        controle_posicao += 20;
        pos = -1;
      }
      delay(200);
  }
  


  for (i = 0; i < 50; i++) {
    counter += 1;
    if (counter % 5 == 0) {
      value = EEPROM.read(i);
      if (score > value) {
        for (t = i-4; t < 50; t++) { // salva o ranking antes de alterar
          troca[t] = EEPROM.read(t);
        }
        n = 0;
        for (j = i-4; j < i; j++) {
           EEPROM.write(j, nome[n]);
           n += 1; 
        }
        EEPROM.write(i, score);
        for (t = i+1; t < 50; t++) { // t recebe uma posicao apos o score do ranking atualizado (no caso o primeiro caractere apos o score do anterior)
          EEPROM.write(t, troca[t-5]); // t-5 = comeca com o player anterior que foi trocado pelo maior (sao 5 posicoes anterior a de agora 4 = nome + 1 = score)
        }
        return;
      }
    }
  }
  tft.fillScreen(BLACK);
}



void resetRanking() {
  int counter = 0;
  
   for (int i = 0; i < 50; i++) { // roda em todas as posicoes de memorias do EEPROM de 0 - 49
      counter += 1; // conta += 1 pois se comeca em 4, espera contar 5 (4 + 5), vai guardar no endereco 9 e assim sucessivamente
      if (counter % 5 == 0) {
        EEPROM.write(i, 0);
      }
      else {      
         EEPROM.write(i, ' '); // DEIXA O NOME DE TODOS OS JOGADORES VAZIO;
      }
   }
}
