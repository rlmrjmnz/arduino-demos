
#include <Keypad.h>

#define PASS_LENGTH 4

// output pins
int bluePin = 12;
int redPin = 13;
int buzzerPin = 2;

// keypad vars
const byte rows = 4;
const byte cols = 4;
char hexaKeys[rows][cols] =
{
{ '1','2','3','A' },
{ '4','5','6','B' },
{ '7','8','9','C' },
{ '*','0','#','D' }
};
byte rowPins[rows] = { 4, 5, 6, 7};
byte colPins[cols] = { 8, 9, 10, 11};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, rows, cols);

// input vars
int pos = 0;
char secretCode[PASS_LENGTH] = { '1', '2', '3', '4'};
char inputCode[PASS_LENGTH] = { '0', '0', '0', '0'};

bool readPass = false;

void setup() {
  Serial.begin(9600);
  
  // pins setup
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  readKey();

  if(readPass){
    // check code
    int correct = 0;
    pos = 0;
    for(pos = 0; pos < PASS_LENGTH; pos++){
      if (inputCode[pos] == secretCode[pos]){
        correct++;  
      }  
    }

    Serial.println(correct);
  
    if (correct == PASS_LENGTH){
      Serial.println("ok");
      digitalWrite(bluePin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(300);
      digitalWrite(bluePin, LOW);
      digitalWrite(buzzerPin, LOW);  
    }
    else{
      Serial.println("bad");
      digitalWrite(redPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(300);
      digitalWrite(redPin, LOW);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(buzzerPin, HIGH);
      delay(300);
      digitalWrite(buzzerPin, LOW);
    }
    readPass = false;
  }
}

void readKey(){
  char key = 'f';
  pos = 0;

  for(pos = 0; pos < PASS_LENGTH; pos++){
    key = customKeypad.waitForKey();
    inputCode[pos] = key;  
  }

  readPass = true;
  //delay(10);
}

