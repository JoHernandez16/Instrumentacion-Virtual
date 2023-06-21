long randNumber;
long randNumber2;
String inputString = "";      // Variable para almacenar valor de entrada por Labview
bool stringComplete = false;  // Variable que sirve como bandera de recepción de un dato nuevo

void setup()
{
  
  Serial.begin(9600);         // Inicialización de UART
  randomSeed(analogRead(0));  // Habilitamos generador de números pseudoaleatorios
  inputString.reserve(200);   // Reservamos memoria para dato de entrada por UART
}

void loop()
{
  /*Seccion donde realiza la lectura de sensores*/
  randNumber = random(300);
  randNumber2 = random(300);
  Serial.print("Lecturas: ");
  Serial.print(randNumber);
  Serial.print(",");
  Serial.println(randNumber2);
  delay(1000); 
  ////////////////////////////////

  /*Si se ha recibido un dato por UART y al finalizar un saldo de linea se imprime*/
  if (stringComplete) {
    Serial.println(inputString);
    // Limpiamos acción, en caso de tener un actuador, aquí debería ir la función de control  
    inputString = "";
    // Limpiamos bandera
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // se obtiene byte:
    char inChar = (char)Serial.read();
    // concatenamos byte con byte anterior:
    inputString += inChar;
    // Si el byte es un salto de linea finalizamos el mensaje y habilitamos bandera
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
