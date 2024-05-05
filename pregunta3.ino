#include <Keypad.h>

const int ROW_NUM = 4;
const int COLUMN_NUM = 4;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {13, 12, 11, 10};
byte pin_column[COLUMN_NUM] = {9, 8, 7, 6};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const int LIGHTS[] = {0,1,2,3,4};

// States
bool isDay = true;

// Day State
int day_iter= 0 ;
int day_sem[3] = {2,3,4};
int day_ped[3] = {52, 52, 53};
int delays[3] = {2000,1000,2000};

// Day State
bool night_blink = false;
int night_delay = 200;
int night_ped = 52;
int night_sem = 4;

// Time tracking
unsigned long startTime;
unsigned long nextTime = 2000;

// Keypad
//char inputString[10];
String inputString = ""; 
char inputStringIter = 0;

void setup()
{
  Serial.begin(9600);  
  startTime = millis();
  for(int i = 2 ; i<=4; i++){
  	pinMode(i, OUTPUT);  
    digitalWrite(i, HIGH); 
  }
  for(int i = 52 ; i<=53; i++){
  	pinMode(i, OUTPUT);  
    digitalWrite(i, HIGH); 
  }
}

void setAllHigh() {
  for(int i = 2 ; i<=4; i++){
    digitalWrite(i, HIGH); 
  }
    for(int i = 52 ; i<=53; i++){
    digitalWrite(i, HIGH); 
  }
}

void runDay() {
  setAllHigh();
  digitalWrite(day_sem[day_iter], LOW); 
  digitalWrite(day_ped[day_iter], LOW);    
	nextTime = millis() + delays[day_iter];
  day_iter = (day_iter+ 1) % 3;
  //Serial.println("Day step");
  //Serial.println(day_iter);
}

void runNight() {
  setAllHigh();
  if (night_blink) {
    digitalWrite(night_ped, LOW); 
	  digitalWrite(night_sem, LOW);    
    //Serial.println("Blink on night");
  }
  else {
    //Serial.println("Blink off night");
  }
  night_blink = !night_blink;
  nextTime = millis() + night_delay; 
}

void updateLights() {
  if (millis() >= nextTime) {
      if (isDay) {
    runDay();
    }
    else {
      runNight();
    }
  }
}


void readKeypadInput() {
  // GetKey
  char key = keypad.getKey();
  if (key){
    Serial.println(key);
  } 
  else {
    return;
  }
  // NumberInput
  char currentInputChar = key;
  if(key - '0'  >= 0 && key - '0' <= 9) {
    inputString += (char)key;
        Serial.println(inputString); 
    //inputStringIter++;    
  }
  // RegisterInput
  else if (key == '#') {
    Serial.println(inputString); 
    int number = inputString.toInt(); 
    int len = inputString.length();
    inputString = ""; 

    if (len == 0 || len > 2) return;

    
    Serial.println(inputString); 

    if(number < 24 && number >=0) {
      Serial.println(number); 

      // Set Day or Night Conditioanlly
      isDay = number >= 5 && number <= 23;
      Serial.println(number);
      if (isDay) {
        Serial.println("DAY");
      }
      else {
        Serial.println("NIGHT");
      }
    } 
  } 
  // ResetInput
  else {
    inputString = ""; 
  }  
}

void loop()
{
  readKeypadInput();
  updateLights();
}
     
