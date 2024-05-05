#define LEDR 8
#define LEDB 7
#define LEDG 6
#define LEDY 5

#define BUTTON 9


int sem[3] = {6,7,8};
int ped[3] = {5,5,4};
int delays[3] = {2000,1000,2000};

int iter= 0 ;
int ax = 0 ; 


void setup()
{
  Serial.begin(9600);  
  
  for(int i = 4 ; i<=8; i++){
  	pinMode(i, OUTPUT);  
    digitalWrite(i, HIGH); 
  }
  
}





void loop()
{
  digitalWrite(sem[iter], LOW); 
  digitalWrite(ped[iter], LOW);    
  delay(delays[iter]);
  digitalWrite(sem[iter], HIGH); 
  digitalWrite(ped[iter], HIGH); 
  iter = (iter + 1) % 3; 
}
