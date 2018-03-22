#include <Servo.h>
#include <IRremote.h>
#include <IRremoteInt.h>

#define IRPIN     7
#define SERVOPIN  3
#define LEDPIN    5
#define MICPIN    A5

#define OFF   16753245
#define MODE  16736925
#define EQ    16769055
#define FF    16761405
#define RW    16712445
#define PLUS  16748655
#define MINUS 16754775

#define BRG_DEFAULT 127
#define BRG_DELTA   20

#define SPD_DEFAULT 90
#define SPD_DELTA   10

#define MIC_THRESHOLD 450
#define MIC_DELTA     1000

//#define DEBUG 0

IRrecv irrecv(IRPIN);
decode_results results;

Servo motor;

bool motor_on;
bool led_on;
byte brightness;
byte mSpeed; 
unsigned long mic_time;

void setup() {
  Serial.begin(9600);

  motor_on = false;
  led_on = false;
  brightness = BRG_DEFAULT;
  mic_time = 0;
  mSpeed = SPD_DEFAULT;

  pinMode(LEDPIN, OUTPUT);
  pinMode(MICPIN, INPUT);
  
  irrecv.enableIRIn();

  motor.attach(SERVOPIN);
  motor.write(0);
  delay(100);
}

void loop() {
  readIR();

  readMic();

  controlMotor();
  controlLED();
}

void readIR(){
  if(irrecv.decode(&results)){
      if(results.value == OFF){
        motor_on = !motor_on;
      }
      if(results.value == EQ){
        led_on = !led_on;
      }
      if(results.value == PLUS && led_on){
        brightness = (brightness+BRG_DELTA < 255)? brightness+BRG_DELTA:255;  
      }
      if(results.value == MINUS && led_on){
        brightness = (brightness-BRG_DELTA > 0)? brightness-BRG_DELTA:0;  
      }
      if(results.value == FF && motor_on){
        mSpeed = (mSpeed+SPD_DELTA < 180)? mSpeed+SPD_DELTA:180;  
      }
      if(results.value == RW && motor_on){
        mSpeed = (mSpeed-SPD_DELTA > 0)? mSpeed-SPD_DELTA:0;  
      }
      irrecv.resume();
  }
}

void readMic(){
  int mic = analogRead(MICPIN);
  #ifdef DEBUG
  Serial.println(mic_time);
  Serial.println(millis());
  #endif

  Serial.println(mic);

  if((mic >= MIC_THRESHOLD) && (millis() > mic_time)){
    led_on = !led_on;
    mic_time = millis() + MIC_DELTA;
  }
}

void controlMotor(){
  if(motor_on){
    #ifdef DEBUG
    Serial.println("motor on");
    #endif
    motor.write(mSpeed);  
  }
  else{
    #ifdef DEBUG
    Serial.println("motor off");
    #endif
    motor.write(0);  
    mSpeed = SPD_DEFAULT;
  }
}

void controlLED(){
  if(led_on){
    #ifdef DEBUG
    Serial.println("led on");
    #endif
    analogWrite(LEDPIN, brightness);  
  }
  else{
    #ifdef DEBUG
    Serial.println("led off");
    #endif
    analogWrite(LEDPIN, 0);
    brightness = BRG_DEFAULT;  
  }
}

