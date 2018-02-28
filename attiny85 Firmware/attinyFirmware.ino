#include <SoftwareSerial.h>

SoftwareSerial atSerial(3,4); //Comunicacion serie con ESP8266 
long pulseCount = 0; //Numero de pulsos en 1 minuto
unsigned long lastTime, sendTime; // Diferencia de tiempo entre el ultimo envio y la comprobacion

void setup(){
  atSerial.begin(9600); // Comunicacion serie a 115200 baudios
  pinMode(0, OUTPUT); // Led de confirmacion de interrupcion
  pinMode(1, OUTPUT); // Pin de interrupcion al ESP8266

  attachInterrupt(0, onPulse, RISING); // Interrupcion en pin 2 (int 0) 
}

void loop(){
}


void onPulse(){ // Rutina de interrupcion
  pulseCount ++;
  digitalWrite(0, HIGH);
  delay(50);
  digitalWrite(0, LOW);

  //enviamos la lectura una vez recibimos el pulso
  lastTime = micros();
  
  if(lastTime - sendTime >= 60000000){ //Enviamos la cantidad de pulsos cada 60000000 microsegundos (60segundos)
    noInterrupts();
    sendTime = micros();
    digitalWrite(1, HIGH);
    delay(40);
    atSerial.print(pulseCount);
    delay(1);
    atSerial.print('\n');
    pulseCount = 0;
    digitalWrite(1, LOW);
    interrupts();
  }
}

