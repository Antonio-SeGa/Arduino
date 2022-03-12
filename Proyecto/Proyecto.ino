#include <ArduinoJson.h>
#include <IRremote.h>

#define Boton_1 0xBA45FF00    // reemplaza cada instancia de Boton_1 por su valor HEX
#define Boton_2 0xB946FF00    // reemplaza cada instancia de Boton_2 por su valor HEX
#define Boton_3 0xB847FF00    // reemplaza cada instancia de Boton_3 por su valor HEX

int Boton_1_pin = 2;
int Boton_2_pin = 4;
int Boton_1_valor = 0;
int Boton_2_valor = 0;

int pot_1_pin = A0;
int pot_2_pin = A1;
int pot_3_pin = A2;
int pot_1_valor = 0;
int pot_2_valor = 0;
int pot_3_valor = 0;

//Salidas digitales
int LED_1_pin = 3;
int LED_2_pin = 5;
int LED_3_pin = 6;
int LED_4_pin = 9;

//boolean Estado_Led_1 = false;
//boolean Estado_Led_2 = false;
//boolean Estado_Led_3 = false;
//boolean Estado_Led_4 = false;

int SENSOR = 13;      // sensor KY-022 a pin digital 13

int LEDROJO = 12;      // componente rojo de LED RGB a pin 12
int LEDVERDE = 11;     // componente verde de LED RGB a pin 11
int LEDAZUL = 10;      // componente azul de LED RGB a pin 10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Boton_1_pin, INPUT_PULLUP);
  pinMode(Boton_2_pin, INPUT_PULLUP);
  
  pinMode (LED_1_pin,OUTPUT);
  pinMode (LED_2_pin,OUTPUT);
  pinMode (LED_3_pin,OUTPUT);
  pinMode (LED_4_pin,OUTPUT);

  IrReceiver.begin(SENSOR, DISABLE_LED_FEEDBACK); // inicializa recepcion de datos
  pinMode(LEDROJO, OUTPUT);   // pin 2 como salida
  pinMode(LEDVERDE, OUTPUT);    // pin 3 como salida
  pinMode(LEDAZUL, OUTPUT);   // pin 4 como salida
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  Boton_1_valor = digitalRead(Boton_1_pin);
  Boton_2_valor = digitalRead(Boton_2_pin);

  pot_1_valor = analogRead(pot_1_pin);
  pot_2_valor = analogRead(pot_2_pin);
  pot_3_valor = analogRead(pot_3_pin);

//  Enviar por el serial
  StaticJsonDocument<96> docEnvio;

  docEnvio["ID"] = "Antonio Arduino";
  docEnvio["Boton_1"] = Boton_1_valor;
  docEnvio["Boton_2"] = Boton_2_valor;
  docEnvio["Pot_1"] = pot_1_valor;
  docEnvio["Pot_2"] = pot_2_valor;
  docEnvio["Pot_3"] = pot_3_valor;
  
  serializeJson(docEnvio, Serial);
  Serial.println("");
  
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
    int LED_5 = docRecibe["LED_5"];
    int LED_6 = docRecibe["LED_6"];
    int LED_7 = docRecibe["LED_7"];

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

    if(LED_5 == 0 || LED_5 == 1){
      digitalWrite(LEDROJO, LED_5);
      //Serial.println("LED_1");
    }

    if(LED_6 == 0 || LED_6 == 1){
      digitalWrite(LEDVERDE, LED_6);
      //Serial.println("LED_2");
    }

    if(LED_7 == 0 || LED_7 == 1){
      digitalWrite(LEDAZUL, LED_7);
      //Serial.println("LED_3");
    }
  }
  if (IrReceiver.decode()) {          // si existen datos ya decodificados
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);  // imprime valor en hexadecimal en monitor
    IrReceiver.resume();              // resume la adquisicion de datos
  }
  delay(100);

}

/*
 * {
 *  LED_5: 0xBA45FF00 
 *  LED_6: 0
 *  LED_7: 0
 * }
*/
///
///
