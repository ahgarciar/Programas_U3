int Sensor1 = A0;
int Sensor2 = A1;
int Sensor3 = A2;

int Actuador1 = 11;
int Actuador2 = 12;
int Actuador3 = 13;

void setup() {
  pinMode(Actuador1, OUTPUT);
  pinMode(Actuador2, OUTPUT);
  pinMode(Actuador3, OUTPUT);

  // put your setup code here, to run once:
  Serial.begin(9600); //UART
  Serial.setTimeout(5);

  Serial2.begin(9600);
  
}

String temporal;
int v1, v2, v3;
void loop() {
  // put your main code here, to run repeatedly:

  v1 = analogRead(Sensor1); // X   XX  XXX   XXXX
  v2 = analogRead(Sensor2);
  v3 = analogRead(Sensor3);

  Serial.print("H" + String(v1) + "R" + String(v2) + "R" + String(v3) + "T"); //R <-

  //leer datos recibidos del EV para el control de los actuadores
  if (Serial.available() > 0) { //si hay informacion que leer, entonces se lee
    temporal = Serial.readString();
    temporal.replace("\n", "");
    temporal.replace("\r", "");
    Serial2.println(temporal); //echo

    //String aux[] = temporal.Split("S");
    String aux = "";
    int actuador = 11;
    for (int i = 1; i < temporal.length() - 1; i++) {
      if (temporal.charAt(i) == 'R') {
        analogWrite(actuador++, aux.toInt());
        //Serial.println(aux); //feedback
        aux = "";
      }
      else {
        aux += temporal.charAt(i);
      }
    }
    analogWrite(actuador, aux.toInt());
    //Serial.println(aux); //feedback

  }
  /////////////////////////////////////////////////////////////
  
  delay(25);

}
