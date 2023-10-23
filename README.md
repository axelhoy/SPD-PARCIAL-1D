# Contador binario Parcial SPD 1D

![ARDUINO-BASICO-_-ESPACIO-MAKER-1024x576](https://github.com/axelhoy/spdparcialgrupo/assets/121445908/3e5ca593-c383-400d-85de-061c515ea6cb)

## Integrantes 
1D
- Cannavina Axel

## Proyecto: Contador binario

![arduino2](https://github.com/axelhoy/SPD-PARCIAL-1D/assets/121445908/712d3076-a4e3-488f-8f4d-ee691b9332b1)

## Descripción
Contador binario creado con arduino, implementando el uso de displays 7 segmentos, con un medidor de temperatura y un display LCD

## 💻 Función principal
El contador suma del 0 al 99, o en numeros primos, dependiendo del deslizante.
Este es prendido por un fotodiodo al recibir luz, y cuando su temperatura supera los 90°C, prende un motor (al cual se le podria agregar un sistema de refrigeracion o similar),
y este avisa por un LCD que supera el limite de temperatura.Si supera el limite de temperatura el dispositivo se apaga inmediatamente
Funciones principales a continuacion:

### printDigit

Esta funcion se encarga de encender los correspondientes leds de un display 7 segmentos, para formar el digito enviado por parametro (digit)
Depende la siguiente funcion, ledsSegmento

~~~ C 
void printDigit(int digit)
{
  switch (digit){
    case 1:{
		ledsSegmento(0,1,1,0,0,0,0);
      	break;
    }
  ...
    case 0:{
 		ledsSegmento(1,1,1,1,1,1,0);
      	break;
    }
    
  }
}
~~~
### ledsSegmento

Recibe por parametro los valores a apgar o prender en el display 7 segmentos, 1 para ser prendido y 0 para ser apagado
~~~ C
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
~~~
### prendeDigito

Recibe si debe prender el display decimo, o el display de la unidad, sino, apagar ambos
~~~ C 
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
~~~

### printCount

Recibe el numero a prender, se divide primero por 10 y a partir de ese numero imprime el decimo
luego se le resta 10 y se multiplica por el numero dividido 10 (parse int)
Ej:

14
14/10 
= 1,4 (Prende 1)

Prender decimo

(14-10) * (14/10)
4 * 1,4 
4 * 1 (se parsea a int, borrando los decimales)
= 4 (Prende 4)

Prender unidad

~~~ C
void printCount(int count){
  	prendeDigito(OFF);
    printDigit(count/10);
   	prendeDigito(DECIMO);
    prendeDigito(OFF);
    printDigit(count - 10 * ((int)count/10));
    prendeDigito(UNIDAD);
  }
~~~
### keypressed
Devuelve lo que recibe por parametro, si se presiona el boton para subir la flag pasa a valer 1, y pregunta
Si se presiono (sumar = 0), entonces es diferente a la flag
Si es diferente a la flag, la flag pasa a valer 0
Cuando se suelta, sumar vuelve a valer 1, y la flag vuelve a 1 tambien ya que lo convierte en lo mismo
~~~ C
int sumar;
int flagsumar;
int restar;
int flagrestar;
int reset;
int flagreset;

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
~~~
### Numeros primos
#### esPrimo
recibe por parametro un numero, si la resta de la division del numero divido por 2 es 0, entonces devuelve false
tambien se incluye el for, el cual verifica al numero 2, ya que si es 2 este se salta la iteracion y returna directamente true

#### primoSuma
Recibe start(En este caso es countPrimo, el cual esta incializado en 0), luego le suma 1, si ese numero es primo, lo retorna, si no es, lo va sumando hasta encontrar un numero primo
0+1 = 1, no es primo, 1+1 = 2, es primo, lo retorna

#### primoResta
Misma funcionalidad que el anterior, pero va restando hasta encontrar el siguiente numero primo a retornar
~~~ C
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
~~~

## 🔑 Link 

 - [Proyecto](https://www.tinkercad.com/things/6LKiNuLmDkS-epic-amur/editel?sharecode=7QRuqWXmrb86XEjQE6VlKPgbxGZsvKg7zxhfgHjfEoI)
