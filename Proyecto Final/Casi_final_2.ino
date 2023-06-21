#include <Adafruit_AHTX0.h>
#include <HCSR04.h>

 HCSR04 ultrasonico(3,2);
 float distancia = 0.0;
 float tanque = 15.0;
 float nivel = 0.0;
 Adafruit_AHTX0 aht;
 int ventilador = 13;
 int foco = 12;
 int bomba = 11;
 bool serialRecived = false;
 int lecturaPorcentaje = 0;

void setup() {
  Serial.begin(115200);
  //Serial.println("Adafruit AHT10/AHT20 demo!");
   pinMode(ventilador, OUTPUT);
   pinMode(foco, OUTPUT);
   pinMode(bomba,OUTPUT);

  if (! aht.begin()) {
    //Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  //Serial.println("AHT10 or AHT20 found");
}

void loop() {
  if(serialRecived){
    if (Serial.available()){
      sensors_event_t humidity, temp;
       aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
       lecturaPorcentaje = Serial.read();
        temp.temperature=Serial.read();
        if (temp.temperature == 'a')
            {digitalWrite(ventilador,HIGH);} 
        else if (temp.temperature=='b')
            {digitalWrite(ventilador, LOW);}
        if (temp.temperature == 'f')
            {digitalWrite(foco,HIGH);}
        else if (temp.temperature == 'c')
            {digitalWrite(foco, LOW);}
        if (lecturaPorcentaje == 's')
            {digitalWrite(bomba,HIGH);}
        else if (lecturaPorcentaje == 'h')
            {digitalWrite(bomba, LOW);} 
      }
      serialRecived=false;
  }
  Enviar();
  delay(1000);
}

void Enviar(){
  sensors_event_t humidity, temp;
   int lectura = analogRead(A0);
   int lecturaPorcentaje = map(lectura, 1023, 0, 0, 100);
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print(temp.temperature);
  Serial.print(";");
  Serial.print(humidity.relative_humidity);
  Serial.print(";");
  Serial.print(lecturaPorcentaje);
  Serial.print(";");
  
  distancia = ultrasonico.dist();
  if (distancia >= tanque){
    distancia = tanque;
  }else {
    distancia = distancia;
  }
  nivel = tanque - distancia;
  Serial.println(nivel);
  serialRecived = true;
}