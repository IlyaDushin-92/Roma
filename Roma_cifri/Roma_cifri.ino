#include <TimerOne.h>
#include <Keypad.h>

#define a 26
#define b 22
#define c 30
#define d 34
#define e 36
#define f 24
#define g 28

#define d1 29
#define d2 23
#define d3 25
#define d4 27

const byte ROWS = 4; // число строк клавиатуры
const byte COLS = 3; // число столбцов клавиатуры

char hexaKeys[ROWS][COLS] = {
      {'1', '2', '3'},
      {'4', '5', '6'},
      {'7', '8', '9'},
      {'*', '0', '#'}
};

byte rowPins[ROWS] = {8, 7, 6, 5}; // к каким выводам подключаем управление строками
byte colPins[COLS] = {4, 3, 2}; // к каким выводам подключаем управление столбцами

char pass[4] = {'#', '6', '8', '3'}; // верный пароль
char buttons[5]; // массив нажатых кнопок
int k = 0; // счетчик нажатий

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
long n = 3600;  // время для таймера
int x = 100;
int count = 10;



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
}

void loop() {
  while (digitalRead(A0) == LOW) {
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
    
  }
  if (digitalRead(A0) == HIGH) { n = 0; count = 0; }
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
  char customKey = customKeypad.getKey();
      if (customKey) {
            buttons[k] = customKey; // сохраняем значение кнопки в массиве
            k++; // увеличиваем счётчик нажатий на 1
            
            if (k == 4) { 
                  if (buttons[0] == pass[0] && buttons[1] == pass[1] && buttons[2] == pass[2] && buttons[3] == pass[3])
                  { 
                     Serial.println ("Все гуд");
                     k = 0;
                     count == 0;
                     n = 0000;
                  }
            else {
                   Serial.println ("неправильный пароль");
                   k = 0;
                   
                 }
            }
      }
  if (count == 0) {
    count = 9;  n--;
    if (n == 0) {delay(100000); n = 0000; }
  }
}
