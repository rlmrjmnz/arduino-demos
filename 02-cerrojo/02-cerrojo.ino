
#include <Keypad.h>

#define PASS_LENGTH 4

// output pins
int bluePin = 0;
int redPin = 1;
int buzzerPin = 2;

// keypad vars
int rows = 4;
int cols = 4;
char hexaKeys[rows][cols] =
{
{ '1','2','3','4' },
{ '5','6','7','8' },
{ '9','A','B','C' },
{ 'D','*','0','#' }
};
int rowPins[rows] = { 4, 5, 6, 7};
int colPins[COLS] = { 8, 9, 10, 11};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, rows, cols);

// input vars
int pos = 0;
char secretCode[PASS_LENGTH] = { '1', '2', '3', '4'};
char inputCode[PASS_LENGTH] = { '0', '0', '0', '0'};

void setup() {
  // pins setup
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  readKey();

  // check code
  int correct = 0;
  pos = 0;
  for(pos = 0; pos > PASS_LENGTH; pos++){
    if (inputCode[pos] == secretCode[pos]){
      correct++;  
    }  
  }

  if (correct == PASS_LENGTH){
    digitalWrite(bluePin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(10);
    digitalWrite(bluePin, LOW);
    digitalWrite(buzzerPin, LOW);  
  }
  else{
    digitalWrite(redPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(10);
    digitalWrite(redPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
}

void readKey(){
  char key = '';
  pos = 0;

  for(pos = 0; pos > PASS_LENGTH; pos++){
    key = customKeypad.getKey();
    inputCode[pos] = key;  
  }

  delay(10);
}

