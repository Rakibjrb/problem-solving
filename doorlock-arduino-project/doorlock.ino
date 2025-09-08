// author Rakibul Hasan

//include libraries for modules
#include<LiquidCrystal_I2C.h>
#include<Servo.h>
#include<Keypad.h>

//create object for use the modules
LiquidCrystal_I2C display = LiquidCrystal_I2C(0x27, 16, 2);
Servo servoMotor = Servo();

// global variables
char userInput[7];
int pressedCount = 0;

// initialization pins
int buzzerPin = A0; int servoPin = A1;

// initialize keypad control keymap
const byte keyRows = 4; const byte keyCols = 4;
char keyMap[keyRows] [keyCols] = {
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  '*', '0', '#', 'D',
};

//initialize pins for keypad used this keymap
byte keypadRowPins[keyRows] = {0, 1, 2, 3}; byte keypadColPins[keyCols] = {4, 5, 6, 7};
//create keypad object
Keypad keyPad = Keypad(makeKeymap(keyMap), keypadRowPins, keypadColPins, keyRows, keyCols);

//this function is for print single line
void printSL(int col, int row, String message, int time, bool clear){
  display.setCursor(col, row);
  display.print(message);
  delay(time);
  if(clear){ display.clear(); };
};

//this function is for print double line
void printDL(int col, int row, String message, int col1, int row1, String message2, int time){
  display.setCursor(col, row);
  display.print(message);
  display.setCursor(col1, row1);
  display.print(message2);
  delay(time);
  display.clear();
};

// this function is for buzzer sound control
void beep(int time){ digitalWrite(buzzerPin, HIGH); delay(time); digitalWrite(buzzerPin, LOW); delay(time); };

// rotate servo motor
void rotateServo(String rotateFor){
  if(rotateFor == "open"){
    for(int angleAdd = 5; angleAdd <= 110; angleAdd++){ servoMotor.write(angleAdd); delay(20); };
  }else if(rotateFor == "close"){
    for(int angleSub = 110; angleSub >= 5; angleSub--){ servoMotor.write(angleSub); delay(20); };
  }else{
    display.clear();
    printSL(0, 0, "NOT WORKING", 1000, true);
  }
}

//arduino board pin setup default void
void setup(){
  // init display
  display.init(); display.backlight();
  //init servo motor
  servoMotor.attach(servoPin);
  //init buzzer
  pinMode(buzzerPin, OUTPUT);
  servoMotor.write(5);
  beep(300);
  printSL(0, 0, "RUNNING ...", 2000, false);
  beep(100); beep(100);
  printSL(0, 1, "SUCCESS ....", 2000, true);
  beep(100); beep(100); beep(100);
  printDL(0, 0, "ARDUINO PROJECT", 0, 1, "STUDENTS CST-5", 5000);
  beep(50); beep(50); beep(50); beep(50);
}

//this is default and main repeater function
void loop(){
  printSL(3, 0, "ENTER PIN", 0, false);
  // when key pressed detect throw keyPad.getKey() function and add it to userPassword
  char pressedKey = keyPad.getKey();

  if(pressedCount < 7){
    if(pressedKey){
      beep(100);
      userInput[pressedCount] = pressedKey;
      display.setCursor(4 + pressedCount, 1);
      display.print("*");
      pressedCount++;
    };
  }else{
    pressedCount = 0;
    beep(50);
    display.clear();
    printSL(0, 0, "CHECKING ...", 2000, true);
    if(strcmp(userInput, "715523D") == 0){
      beep(50); beep(50); beep(50);
      printSL(0, 0, "VALID PIN ...", 2000, false);
      beep(50); beep(50); beep(50);
      printSL(0, 1, "UNLOCKED DOOR", 2000, true);
      rotateServo("open");
      delay(5000);
      rotateServo("close");
    }else{
      display.clear();
      beep(50); beep(50); beep(50); beep(50);
      printSL(0, 0, "INVALID PIN ...", 2000, false);
      beep(50); beep(50); beep(50); beep(50);
      beep(50); beep(50); beep(50); beep(50);
      printSL(0, 0, "TRY AGAIN ...", 2000, true);
      beep(50); beep(50);
    }
  }
}