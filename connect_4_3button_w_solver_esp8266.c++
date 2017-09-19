#define FASTLED_ESP8266_RAW_PIN_ORDER
#include "FastLED.h"
#include <time.h>

#define NUM_LEDS 50
CRGBArray<NUM_LEDS> leds;
CRGBArray<NUM_LEDS> leds_new;

int curLed = 0;
int lastInt = 0;
char* lastStuff;
bool starting = true;
bool downLoop = true;
bool rightLoop = true;
bool leftLoop = true;
bool diagDownLeftLoop = true;
bool diagDownRightLoop = true;
bool diagUpRightLoop = true;
bool diagUpLeftLoop = true;
bool winner = false;
char loopColor[1] = {'1'};
int point[2] = {1, 0};
int endPoint[2] = {point[0], point[1]};
int finalWinnerHue = 0;
bool darBoard = true;
bool compEnemy = false;
bool compTurn = true;
int dropPosition = 3;

void setup() {
  pinMode(13, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
//  pinMode(3, INPUT_PULLUP);
//  pinMode(4, INPUT_PULLUP);
//  pinMode(5, INPUT_PULLUP);
//  pinMode(6, INPUT_PULLUP);
//  pinMode(7, INPUT_PULLUP);
  //  srand(time(NULL));
  // Define pin #13 as output, for the LED
    Serial.println("in setup");
  FastLED.addLeds<NEOPIXEL, 15>(leds, NUM_LEDS);
  FastLED.setBrightness( 255 );
  for (int led = 0; led < 50; led++) {
    if (darBoard == false) {
      leds[led] = CHSV(5, 255, 0); FastLED.show();
    } else {
      leds[led] = CHSV(5, 255, 255); FastLED.show();
    }
  }
  Serial.begin(115200);
}

char color[1] = {'r'};
int curHue = 1;
void setLedArray(char* a, int* l) {
  for (int i = 6; i -- > 0;) {
    if (a[i] == 'r') {
      leds[l[i]] = CHSV(155, 255, 255); FastLED.show();
      a[i] = 'r';
    } else if (a[i] == 'b') {
      leds[l[i]] = CHSV(125, 255, 255); FastLED.show();
      a[i] = 'b';
    } else {
      if (color[0] == 'r') {
        leds[l[i]] = CHSV(155, 255, 255); FastLED.show();
      } else {
        leds[l[i]] = CHSV(125, 255, 255); FastLED.show();
      }
      if (darBoard == false) {
        FastLED.delay(30); leds[l[i]] = CHSV(5, 255, 0); FastLED.show();
      } else {
        FastLED.delay(30); leds[l[i]] = CHSV(5, 255, 255); FastLED.show();
      }
    }
  }
  if (color[0] == 'r') {
    color[0] = 'b';
    curHue = 100;
  } else {
    color[0] = 'r';
    curHue = 1;
  }
  checkWin();
  checkComnpEnemy();
}

void checkComnpEnemy() {
  if (compEnemy == true && compTurn == true) {
    compTurn = false;
    switch (rand() % 7) {
      case 0: rowA(); break;
      case 1: rowB(); break;
      case 2: rowC(); break;
      case 3: rowD(); break;
      case 4: rowE(); break;
      case 5: rowF(); break;
      case 6: rowG(); break;
    }
  }
}

void selectRow(char* a, int* l) {
  bool changed = false;
  for (int i = 0; i < 6; i++) {
    if (changed == false) {
      if (a[i] != 'r') {
        if (a[i] != 'b') {
          changed = true;
          curLed = l[i];
          lastStuff = a;
          lastInt = i;
          starting = false;
          a[i] = color[0];
          point[1] = i;
          endPoint[1] = i;
        }
      }
    }
  }
  setLedArray(a, l);
}

void resetLastMove() {
  if (color[0] == 'r') {
    color[0] = 'b';
  } else {
    color[0] = 'r';
  }
  lastStuff[lastInt] = '1';
  if (darBoard == false) {
    FastLED.delay(150); leds[curLed] = CHSV(5, 255, 0); FastLED.show();
  } else {
    FastLED.delay(150); leds[curLed] = CHSV(5, 255, 255); FastLED.show();
  }
  delay(200);
}

char az[6] = {'1', '2', '3', '4', '5', '6'};
int al[6] = {8, 9, 10, 11, 12, 13};
void rowA() {
  point[0] = 0;
  endPoint[0] = 0;
  selectRow(az, al);
}

char b[6] = {'1', '2', '3', '4', '5', '6'};
int bl[6] = {19, 18, 17, 16, 15, 14};
void rowB() {
  point[0] = 1;
  endPoint[0] = 1;
  selectRow(b, bl);
}

char c[6] = {'1', '2', '3', '4', '5', '6'};
int cl[6] = {20, 21, 22, 23, 24, 25};
void rowC() {
  point[0] = 2;
  endPoint[0] = 2;
  selectRow(c, cl);
}

char d[6] = {'1', '2', '3', '4', '5', '6'};
int dl[6] = {31, 30, 29, 28, 27, 26};
void rowD() {
  point[0] = 3;
  endPoint[0] = 3;
  selectRow(d, dl);
}

char e[6] = {'1', '2', '3', '4', '5', '6'};
int el[6] = {32, 33, 34, 35, 36, 37};
void rowE() {
  point[0] = 4;
  endPoint[0] = 4;
  selectRow(e, el);
}

char f[6] = {'1', '2', '3', '4', '5', '6'};
int fl[6] = {43, 42, 41, 40, 39, 38};
void rowF() {
  point[0] = 5;
  endPoint[0] = 5;
  selectRow(f, fl);
}

char g[6] = {'1', '2', '3', '4', '5', '6'};
int gl[6] = {44, 45, 46, 47, 48, 49};
void rowG() {
  point[0] = 6;
  endPoint[0] = 6;
  selectRow(g, gl);
}

void checkWin() {
  int winLeds[4] = {0, 0, 0, 0};
  int* ledArr[7] = {al, bl, cl, dl, el, fl, gl};
  char* arr[7] = {az, b, c, d, e, f, g};
  loopColor[0] = arr[point[0]][point[1]];
  point[0] = endPoint[0];
  point[1] = endPoint[1];
  for (int z = 0; z < 4; z++) {
    if (winner == false) {
      winLeds[z] = ledArr[point[0]][point[1]];
    }
    if (arr[point[0]][point[1]] != loopColor[0] || point[0] < 0 || point[1] < 0 || point[0] > 6 || point[1] > 5) {
      downLoop = false;
    }
    point[1] = point[1] - 1;
  }//down solving is working, next is right then left
  if (downLoop == true) {
    winner = true;
  } else {
    downLoop = true;
  }

  point[0] = endPoint[0];
  point[1] = endPoint[1];
  for (int z = 0; z < 7; z++) {
    if (point[0] < 0 || point[1] < 0 || point[0] > 6 || point[1] > 5) {
    } else {
      if (arr[point[0] - 1][point[1]] == loopColor[0]) {
        point[0] = point[0] - 1;
      }
    }
  }
  for (int z = 0; z < 4; z++) {
    if (point[0] < 0 || point[1] < 0 || point[0] > 6 || point[1] > 5) {
      rightLoop = false;
    } else {
      if (winner == false) {
        winLeds[z] = ledArr[point[0]][point[1]];
      }
      if (arr[point[0]][point[1]] != loopColor[0]) {
        rightLoop = false;
      }
    }
    point[0] = point[0] + 1;
  }//right solving is working, next is right then left
  if (rightLoop == true) {
    winner = true;
  } else {
    rightLoop = true;
  }

  point[0] = endPoint[0];
  point[1] = endPoint[1];
  for (int z = 0; z < 7; z++) {
    if (point[0] < 0 || point[1] < 0 || point[0] > 6 || point[1] > 5) {
    } else {
      if (arr[point[0] + 1][point[1] + 1] == loopColor[0]) {
        point[0] = point[0] + 1;
        point[1] = point[1] + 1;
      }
    }
  }
  for (int z = 0; z < 4; z++) {
    if (point[0] < 0 || point[1] < 0 || point[0] > 6 || point[1] > 5) {
      diagDownLeftLoop = false;
    } else {
      if (winner == false) {
        winLeds[z] = ledArr[point[0]][point[1]];
      }
      if (arr[point[0]][point[1]] != loopColor[0]) {
        diagDownLeftLoop = false;
      }
    }
    point[0] = point[0] - 1;
    point[1] = point[1] - 1;
  }//left solving is working
  if (diagDownLeftLoop == true) {
    winner = true;
  } else {
    diagDownLeftLoop = true;
  }

  point[0] = endPoint[0];
  point[1] = endPoint[1];
  for (int z = 0; z < 7; z++) {
    if (point[0] < 0 || point[1] < 0 || point[0] > 6 || point[1] > 5) {
    } else {
      if (arr[point[0] - 1][point[1] + 1] == loopColor[0]) {
        point[0] = point[0] - 1;
        point[1] = point[1] + 1;
      }
    }
  }
  for (int z = 0; z < 4; z++) {
    if (point[0] < 0 || point[1] < 0 || point[0] > 6 || point[1] > 5) {
      diagDownRightLoop = false;
    } else {
      if (winner == false) {
        winLeds[z] = ledArr[point[0]][point[1]];
      }
      if (arr[point[0]][point[1]] != loopColor[0]) {
        diagDownRightLoop = false;
      }
    }
    point[0] = point[0] + 1;
    point[1] = point[1] - 1;
  }//left solving is working, next is right then left
  if (diagDownRightLoop == true) {
    winner = true;
  } else {
    diagDownRightLoop = true;
  }


  if (winner == true) {
    if (loopColor[0] == 'b') {
      finalWinnerHue = 125;
    } else {
      finalWinnerHue = 155;
    }
    for (int z = 0; z < 7; z++) {
      leds[winLeds[0]] = CHSV(finalWinnerHue, 255, 0);
      leds[winLeds[1]] = CHSV(finalWinnerHue, 255, 0);
      leds[winLeds[2]] = CHSV(finalWinnerHue, 255, 0);
      leds[winLeds[3]] = CHSV(finalWinnerHue, 255, 0);
      for (int led = 0; led < 8; led++) {
        leds[led] = CHSV(finalWinnerHue, 255, 0);
      }
      FastLED.show(); FastLED.delay(50);
      leds[winLeds[0]] = CHSV(finalWinnerHue, 255, 255);
      leds[winLeds[1]] = CHSV(finalWinnerHue, 255, 255);
      leds[winLeds[2]] = CHSV(finalWinnerHue, 255, 255);
      leds[winLeds[3]] = CHSV(finalWinnerHue, 255, 255);
      for (int led = 0; led < 8; led++) {
        leds[led] = CHSV(finalWinnerHue, 255, 255);
      }
      FastLED.show(); FastLED.delay(50);
    }
    winner = false;
  }
}

void resetBoard(char* az, char* b, char* c, char* d, char* e, char* f, char* g) {
  for (int cou = 0; cou < 6; cou++) {
    az[cou] = 'a';
    b[cou] =  'v';
    c[cou] =  's';
    d[cou] =  'e';
    e[cou] =  'u';
    f[cou] =  'p';
    g[cou] =  'q';
  }
}
void startClear() {
  resetBoard(az, b, c, d, e, f, g);
  FastLED.clear();
  FastLED.setBrightness( 255 );
  for (int led = 0; led < 50; led++) {
    if (darBoard == false) {
      leds[led] = CHSV(5, 255, 0); FastLED.show();
    } else {
      leds[led] = CHSV(5, 255, 255); FastLED.show();
    }
  }
  FastLED.show();
  delay(200);
}
void naps() {
  FastLED.setBrightness( 0 );
  starting = false;
}
void setColorInAction() {
  if (color[0] == 'b') {
    for (int led = 0; led < 8; led++) {
      leds[led] = CHSV(125, 255, 255); FastLED.show();
    }
  } else {
    for (int led = 0; led < 8; led++) {
      leds[led] = CHSV(155, 255, 255); FastLED.show();
    }
  }
}

void setDropPosition(){
  int dropArr[6] = {};
  if (dropPosition == 0){
    dropArr[0] = 8;
    dropArr[1] = 9;
    dropArr[2] = 10;
    dropArr[3] = 11;
    dropArr[4] = 12;
    dropArr[5] = 13;
  };
  if (dropPosition == 1){
    dropArr[0] = 19;
    dropArr[1] = 18;
    dropArr[2] = 17;
    dropArr[3] = 16;
    dropArr[4] = 15;
    dropArr[5] = 14;
  };
  if (dropPosition == 2){
    dropArr[0] = 20;
    dropArr[1] = 21;
    dropArr[2] = 22;
    dropArr[3] = 23;
    dropArr[4] = 24;
    dropArr[5] = 25;
  };
  if (dropPosition == 3){
    dropArr[0] = 31;
    dropArr[1] = 30;
    dropArr[2] = 29;
    dropArr[3] = 28;
    dropArr[4] = 27;
    dropArr[5] = 26;
  };
  if (dropPosition == 4){
    dropArr[0] = 32;
    dropArr[1] = 33;
    dropArr[2] = 34;
    dropArr[3] = 35;
    dropArr[4] = 36;
    dropArr[5] = 37;
  };
  if (dropPosition == 5){
    dropArr[0] = 43;
    dropArr[1] = 42;
    dropArr[2] = 41;
    dropArr[3] = 40;
    dropArr[4] = 39;
    dropArr[5] = 38;
  };
  if (dropPosition == 6){
    dropArr[0] = 44;
    dropArr[1] = 45;
    dropArr[2] = 46;
    dropArr[3] = 47;
    dropArr[4] = 48;
    dropArr[5] = 49;
  };
  for (int i = 0; i < 6; i++) {
    Serial.print(dropArr[i]);
          leds_new[dropArr[i]] = leds[dropArr[i]];
          leds[dropArr[i]]= CRGB::Black;FastLED.show();
  };
  FastLED.delay(50);
  for (int i = 0; i < 6; i++) {
          leds[dropArr[i]] = leds_new[dropArr[i]];FastLED.show();
  };
  FastLED.delay(50);
  for (int i = 0; i < 6; i++) {
          leds_new[dropArr[i]] = leds[dropArr[i]];
          leds[dropArr[i]]= CRGB::Black;FastLED.show();
  };
  FastLED.delay(50);
  for (int i = 0; i < 6; i++) {
          leds[dropArr[i]] = leds_new[dropArr[i]];FastLED.show();
  };    
}

void leftButton(){
  dropPosition -= 1;
  if (dropPosition < 0){
    dropPosition = 6;
  };
  setDropPosition();
}

void rightButton(){
  dropPosition += 1;
  if (dropPosition > 6){
    dropPosition = 0;
  };
  setDropPosition();
}

void selectDropPosition(){
  if (dropPosition == 0){
    rowA();
  };
  if (dropPosition == 1){
    rowB();
  };
  if (dropPosition == 2){
    rowC();
  };
  if (dropPosition == 3){
    rowD();
  };
  if (dropPosition == 4){
    rowE();
  };
  if (dropPosition == 5){
    rowF();
  };
  if (dropPosition == 6){
    rowG();
  };
  dropPosition = 3;
  delay(200);
}

int buttonTimer = 0;
int longPressTime = 250;

boolean buttonActive = false;
boolean longPressActive = false;
void loop() {
  setColorInAction();
  int but1 = digitalRead(13);
  int but2 = digitalRead(12);
  int but3 = digitalRead(14);

  if (but1 == LOW) {
    Serial.println("left");
    leftButton();
    delay(100);
  }

  if (but3 == LOW) {
    Serial.println("right");
    rightButton();
    delay(100);
  }

  if (but2 == LOW) {
    Serial.println("drop");
    selectDropPosition();
    delay(100);
  }

  if (but1 == LOW) {
    if (but2 == LOW) {
      if (but3 == LOW) {
        Serial.println("reset");
        startClear();
        delay(200);
      }
    } 
  }

  if (but1 == LOW) {
    if (but3 == LOW) {
      resetLastMove();
      delay(100);
    }
  }
}