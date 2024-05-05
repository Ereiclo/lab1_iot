#define BUTTON_PIN 4

int delayTime;
int currentLED;
bool pressed;
int direccion;
int array[4]  = {13,12,11,10}; // Pins de LED
int n;
int i;

void setup()
{
  Serial.begin(9600);
  delayTime = 200;
  currentLED = array[0];
  n=4;
  i=0;
  
  for (int j = 0; j < n; j++) {
    int ledActual = array[j];
    pinMode(ledActual, OUTPUT);
    digitalWrite(ledActual, HIGH);
  }
}


void loop () {
  int ledActual = array[i];
  digitalWrite(ledActual, LOW);
  delay(delayTime); 
  digitalWrite(ledActual, HIGH);
  delay(delayTime);

  int input = digitalRead(BUTTON_PIN);

  direccion = input ? -1 : 1;
  i += direccion;
  i = (i+n) % n;
}
