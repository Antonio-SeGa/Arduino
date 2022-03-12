#include <ArduinoJson.h>

//{
//  "ID": "Antonio Arduino",
//  "Boton_1": 1,
//  "Boton_2": 1,
//  "Pot_1": 1023,
//  "Pot_2": 1023
//}

int Boton_1_pin = 2;
int Boton_2_pin = 4;
int Boton_1_valor_Actual = 1;
int Boton_2_valor_Actual = 1;
int Boton_1_valor_Anterior = 1;
int Boton_2_valor_Anterior = 1;

int pot_1_pin = A0;
int pot_2_pin = A1;
int pot_3_pin = A2;
int pot_1_valor_Actual = 0;
int pot_2_valor_Actual = 0;
int pot_3_valor_Actual = 0;
int pot_1_valor_Anterior = 0;
int pot_2_valor_Anterior = 0;
int pot_3_valor_Anterior = 0;

//Salidas digitales
int LED_1_pin = 3;
int LED_2_pin = 5;
int LED_3_pin = 6;
int LED_4_pin = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Boton_1_pin, INPUT_PULLUP);
  pinMode(Boton_2_pin, INPUT_PULLUP);
  
  pinMode (LED_1_pin,OUTPUT);
  pinMode (LED_2_pin,OUTPUT);
  pinMode (LED_3_pin,OUTPUT);
  pinMode (LED_4_pin,OUTPUT);

}

void loop() {
  
  Boton_1_valor_Actual = digitalRead(Boton_1_pin);
  Boton_2_valor_Actual = digitalRead(Boton_2_pin);

  pot_1_valor_Actual = analogRead(pot_1_pin);
  pot_2_valor_Actual = analogRead(pot_2_pin);
  pot_3_valor_Actual = analogRead(pot_3_pin);

  //si una de las entradas cambio de valir --> Serializar
  if((Boton_1_valor_Actual != Boton_1_valor_Anterior)||
  (Boton_2_valor_Actual != Boton_2_valor_Anterior)||
  (pot_1_valor_Actual != pot_1_valor_Anterior||
  (pot_2_valor_Actual != pot_2_valor_Anterior)||
  (pot_3_valor_Actual != pot_3_valor_Anterior))){

    StaticJsonDocument<96> docEnvio;
    
    docEnvio["ID"] = "Antonio Arduino";
    docEnvio["Boton_1"] = Boton_1_valor_Actual;
    docEnvio["Boton_2"] = Boton_2_valor_Actual;
    docEnvio["Pot_1"] = pot_1_valor_Actual;
    docEnvio["Pot_2"] = pot_2_valor_Actual;
    docEnvio["Pot_3"] = pot_3_valor_Actual;

    serializeJson(docEnvio, Serial);

    Boton_1_valor_Anterior = Boton_1_valor_Actual;
    Boton_1_valor_Anterior = Boton_2_valor_Actual;
    pot_1_valor_Anterior = pot_1_valor_Actual;
    pot_2_valor_Anterior = pot_2_valor_Actual;
    pot_3_valor_Anterior = pot_3_valor_Actual;

    Serial.println("");  
  }
  

 // Si hay datos en el buffer --> Deserializar 
  if(Serial.available()>0){

    StaticJsonDocument<96> docRecibe;
    DeserializationError error = deserializeJson(docRecibe, Serial);

    if(error){
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    int LED_1 = docRecibe["LED_1"];
    int LED_2 = docRecibe["LED_2"];
    int LED_3 = docRecibe["LED_3"];
    int LED_4 = docRecibe["LED_4"];

// Serial.println(LED_1);

//Si el valor de llegada es 2 el valor del LED no se altera
    if(LED_1 == 0 || LED_1 == 1){
      digitalWrite(LED_1_pin, LED_1);
      //Serial.println("LED_1");
    }

    if(LED_2 == 0 || LED_2 == 1){
      digitalWrite(LED_2_pin, LED_2);
      //Serial.println("LED_2");
    }

    if(LED_3 == 0 || LED_3 == 1){
      digitalWrite(LED_3_pin, LED_3);
      //Serial.println("LED_3");
    }

    if(LED_4 == 0 || LED_4 == 1){
      digitalWrite(LED_4_pin, LED_4);
      //Serial.println("LED_4");
    }
  }

}
