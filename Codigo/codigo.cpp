// C++ code
// 1D
//Axel Cannavina
//Franco Velazco
//Dante Tucci
//Alexis Portillo

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
#define DECIMO A1
#define UNIDAD A2
#define OFF 0
#define TIEMPO 10
#define FUERZA 12
#define MOTOR 13
#define SENSOR A4
int lectura;
int sensorPin = A0;
int countDigit=0;
int sumar =1;
int flagsumar =1;
int restar =1;
int flagrestar = 1;
int reset = 1;
int flagreset = 1;

void setup()
{
  pinMode(A4, INPUT);
  pinMode(A0, INPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(DECIMO, OUTPUT);
  pinMode(UNIDAD, OUTPUT);
  digitalWrite(UNIDAD, 0);
  digitalWrite(DECIMO,0);
  pinMode(MOTOR, OUTPUT);
  printDigit(0);
  Serial.begin(9600);
}

void loop()
{
  lectura = analogRead(SENSOR);
  Serial.println(lectura);
  int pressed = keypressed();
  if(lectura== 634)
  {
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
   if (5 % countDigit == 0) {
    digitalWrite(MOTOR, HIGH);
  } else {
    digitalWrite(MOTOR, LOW);
  }
  }
}
void printDigit(int digit)
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  switch (digit){
    case 1:{
    	digitalWrite(B, HIGH);
      	digitalWrite(C, HIGH);
      	break;
    }
    case 2:{
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(A, HIGH);
      break;
    }
    case 3:{
      digitalWrite(D, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(A, HIGH);
      break;
    }
    case 4:{
      digitalWrite(F, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(B, HIGH);
      break;
    }
    case 5:{
      digitalWrite(A, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      break;
    }
    case 6:{
      digitalWrite(A, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      break;
    }
    case 7:{
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;
    }
    case 8:{
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    }
    case 9:{
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    }
    case 0:{
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      break;
    }
    
  }
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
 	
  if(sumar != flagsumar && sumar==0)
  {
    flagsumar = sumar;
      return SUBIRLO;
  }
  if(restar != flagrestar && restar==0)
  {
    flagrestar = restar;
      return BAJARLO;
  }
    if(reset != flagreset && reset==0)
  {
    flagreset = reset;
      return RESET;
    }
  return 0;
}
