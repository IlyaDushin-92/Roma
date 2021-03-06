#include <TimerOne.h>
#include "pitches.h" //добавляем эквивалентные частоты для музыкальных нот
//#include "themes.h"  //добавляем значения нот и их длительности 

const int SPEAKER=13;


#define a 26
#define b 30 // 22
#define c 24 // 30
#define d 28 // 32
#define e 34
#define f 22 //24
#define g 32 // 28

#define d1 29
#define d2 23
#define d3 25
#define d4 27

int DIN_PLUS = 9;
int DIN_MUNUS = 7;

long n = 5 ;  // время для таймера
int x = 100;
int count = 10;
///////// мелодия//////////////
int notes[] = {
  392, 392, 392, 311, 466, 392, 311, 466, 392,
  587, 587, 587, 622, 466, 369, 311, 466, 392,
  784, 392, 392, 784, 739, 698, 659, 622, 659,
  415, 554, 523, 493, 466, 440, 466,
  311, 369, 311, 466, 392
};
int times[] = {
  350, 350, 350, 250, 100, 350, 250, 100, 700,
  350, 350, 350, 250, 100, 350, 250, 100, 700,
  350, 250, 100, 350, 250, 100, 100, 100, 450,
  150, 350, 250, 100, 100, 100, 450,
  150, 350, 250, 100, 750
};
void music ()
{
  for (int i = 0; i < 39; i++)
    {
      tone(SPEAKER, notes[i], times[i]*2);
      delay(times[i]*2);
      noTone(SPEAKER); 
     }
}

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  
  pinMode(A0, INPUT);

  Timer1.initialize(100000);
  Timer1.attachInterrupt( add );
  Serial.begin (9600);

  pinMode (DIN_PLUS, OUTPUT);
  pinMode (DIN_MUNUS, OUTPUT);
  digitalWrite (DIN_MUNUS, LOW);
}

void loop() {
  while (true) {
    clearLEDs();
    pickDigit(3); // включаем первую цифру (тысячи)
    pickNumber((n / 1000));
    delay(5);

    clearLEDs();
    pickDigit(2); // включаем вторую цифру (сотни)
    pickNumber((n % 1000) / 100);
    delay(5);

    clearLEDs();
    pickDigit(1); // включаем третью цифру (десятки)
    pickNumber(n % 100 / 10);
    delay(5);

    clearLEDs();
    pickDigit(0); // включаем четвертую цифру (единицы)
    pickNumber(n % 10);
    delay(5);

    if (n == 0) 
      {
         digitalWrite (g, HIGH);
         digitalWrite (d1, HIGH);
         digitalWrite (d2, HIGH);
         digitalWrite (d3, HIGH);
         digitalWrite (d4, HIGH);
        
         music ();
      }
  }
  
}

// определение разряда
void pickDigit(int x) {
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  switch (x) {
    case 0: digitalWrite(d1, HIGH);  break;
    case 1: digitalWrite(d2, HIGH);  break;
    case 2: digitalWrite(d3, HIGH);  break;
    default: digitalWrite(d4, HIGH); break;
  }
}

// определение символа (цифры)
void pickNumber(int x) {
  switch (x) {
    default: zero();   break;
    case 1: one();     break;
    case 2: two();     break;
    case 3: three();  break;
    case 4: four();    break;
    case 5: five();     break;
    case 6: six();       break;
    case 7: seven(); break;
    case 8: eight();  break;
    case 9: nine();   break;
  }
}

// очистка индикатора
void clearLEDs() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void zero() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void one() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void two() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void three() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void four() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void five() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void six() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void seven() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void eight() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void nine() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

////////////////////////



void add() {
  count --;
  
  // здесь надо вписать функцию чтения перемычек и выключение таймера
  if (count == 0) {
    count = 9;  n--;
    digitalWrite (DIN_PLUS, HIGH);
    delay (10000);
    digitalWrite (DIN_PLUS, LOW);
    delay (0);
     if (n == 0) 
      {
        Timer1.stop();
      } 
  }
}
