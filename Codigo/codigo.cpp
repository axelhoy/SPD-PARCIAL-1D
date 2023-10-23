// C++ code
// 1D
//Axel Cannavina
#include <Adafruit_LiquidCrystal.h>
#define A 10
#define B 11
#define C 7
#define D 6
#define E 5
#define F 9
#define G 8
#define SUBIRLO 3
#define BAJARLO 2
#define RESET 4
#define RESET2 
#define DECIMO A1
#define UNIDAD A2
#define OFF 0
#define TIEMPO 20
#define MOTOR 12
#define TEMP A3
#define FOTO A0
#include <Adafruit_LiquidCrystal.h>
int lectura;
int sensorPin = A0;
int countDigit=0;
int countPrimo=0;
int sumar;
int flagsumar;
int restar;
int flagrestar;
int reset;
int flagreset;
Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
    lcd_1.begin(16, 2);
  pinMode(A4, INPUT);
  pinMode(FOTO, INPUT);
  pinMode(4, INPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(DECIMO, OUTPUT);
  pinMode(UNIDAD, OUTPUT);
  digitalWrite(UNIDAD, 0);
  digitalWrite(DECIMO,0);
  pinMode(MOTOR, OUTPUT);
  pinMode(A3, INPUT);
  printDigit(0);
  Serial.begin(9600);

}




void loop()
{
    lcd_1.setCursor(0, 1);

  Serial.println(sumar);
  int pressed = keypressed();
  int deslizanteON = digitalRead(4);
  int prender = analogRead(FOTO);
  int temperatura = analogRead(TEMP);
  int avisomotor = map(temperatura,0,570,0,255);
    if(prender > 0){
      analogWrite(MOTOR, avisomotor);
      if(temperatura>287){
         lcd_1.print("Temperatura Alta!");
        apagarSistema();
      }
      else{
        lcd_1.clear();
    if (deslizanteON==0){
    if(pressed==SUBIRLO){
        countDigit++;
        if(countDigit>99)
          countDigit=0;
      }
      else if(pressed==BAJARLO){
        countDigit--;
        if(countDigit<0)
          countDigit=99;
      }
      else if(pressed==RESET){
        countDigit=0;
      }
      printCount(countDigit);
    }
    else{
    if(pressed==SUBIRLO){
        countPrimo = primoSuma(countPrimo);
        if(countPrimo>97)
          countPrimo=0;
      }
      else if(pressed==BAJARLO){
        countPrimo = primoResta(countPrimo);
        if(countPrimo>99)
          countPrimo=97;
      }
      else if(pressed==RESET){
        countPrimo=0;
      }
      printCount(countPrimo);
      

    }
      }
      }
  else{
  	apagarSistema();
  }

}

void apagarSistema(){
  	digitalWrite(DECIMO, HIGH);	
    digitalWrite(UNIDAD, HIGH);
}
bool esPrimo(int n) {
  if (n <= 1) {
    return false;
  }
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int primoSuma (int start) {
  int num = start + 1;
  while (true) {
    if (esPrimo(num)) {
      return num;
    }
    num++;
  }
}
int primoResta(int start) {
  int num = start - 1;
  while (true) {
    if (esPrimo(num)) {
      return num;
    }
    num--;
  }
}

void printDigit(int digit)
{
  switch (digit){
    case 1:{
		ledsSegmento(0,1,1,0,0,0,0);
      	break;
    }
    case 2:{
		ledsSegmento(1,1,0,1,1,0,1);
      	break;
    }
    case 3:{
		ledsSegmento(1,1,1,1,0,0,1);
      	break;
    }
    case 4:{
		ledsSegmento(0,1,1,0,0,1,1);
      	break;
    }
    case 5:{
		ledsSegmento(1,0,1,1,0,1,1);
      	break;
    }
    case 6:{
 		ledsSegmento(1,0,1,1,1,1,1);
      	break;
    }
    case 7:{
		ledsSegmento(1,1,1,0,0,0,0);
      	break;
    }
    case 8:{
		ledsSegmento(1,1,1,1,1,1,1);
      	break;
    }
    case 9:{
		ledsSegmento(1,1,1,1,0,1,1);
      	break;
    }
    case 0:{
 		ledsSegmento(1,1,1,1,1,1,0);
      	break;
    }
    
  }
}

void ledsSegmento(int a, int b, int c, int d, int e, int f, int g)
{
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);
  digitalWrite(D, d);
  digitalWrite(E, e);
  digitalWrite(F, f);
  digitalWrite(G, g);
	
}
    
void prendeDigito(int digito){
    if (digito == UNIDAD){
      digitalWrite(UNIDAD, LOW);
      digitalWrite(DECIMO, HIGH);
      delay(TIEMPO);
    }
    else if (digito == DECIMO){
      digitalWrite(UNIDAD, HIGH);
      digitalWrite(DECIMO, LOW);
      delay(TIEMPO);
    }
    else
    {
      digitalWrite(UNIDAD, HIGH);
      digitalWrite(DECIMO, HIGH);
    }
  }

  
void printCount(int count){
  	prendeDigito(OFF);
    printDigit(count/10);
   	prendeDigito(DECIMO);
    prendeDigito(OFF);
    printDigit(count - 10 * ((int)count/10));
    prendeDigito(UNIDAD);
  }
  
int keypressed(void){
  	sumar = digitalRead(SUBIRLO);
  	restar = digitalRead(BAJARLO);
  	reset = digitalRead(RESET);
  	if (sumar)
      flagsumar = 1;
  	if (restar)
      flagrestar = 1;
  	if(reset)
      flagreset = 1;
 	
  if(sumar != flagsumar)
  {
    flagsumar = sumar;
      return SUBIRLO;
  }
  if(restar != flagrestar)
  {
    flagrestar = restar;
      return BAJARLO;
  }
   if(reset != flagreset)
  {
    flagreset = reset;
      return RESET;
    }
  return 0;
}

