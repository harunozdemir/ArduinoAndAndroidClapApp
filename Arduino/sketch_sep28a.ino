#include <SoftwareSerial.h>

#define rxPin 10 // to -> TX
#define txPin 11 // to -> RX

SoftwareSerial BT(rxPin, txPin); // rxPin = TXD, txPin = RXD

int ses_sensoru = 6;
int role = 8;
int alkis = 0;
long algilama_araligi_baslangic = 0;
long algilama_araligi = 0;
boolean isik_durumu = false;
char a; // stores incoming character from other device
boolean ledStateChanged = false;

void setup() {
  pinMode(ses_sensoru, INPUT);
  pinMode(role, OUTPUT);

  Serial.begin(9600);

  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
  // Send test message to other device
  //BT.println("Hello from Arduino");




}

void loop() {


  int sensor_durumu = digitalRead(ses_sensoru);

  if (sensor_durumu == 0)
  {
    if (alkis == 0)
    {
      algilama_araligi_baslangic = algilama_araligi = millis();
      alkis++;
    }
    else if (alkis > 0 && millis() - algilama_araligi >= 50)
    {
      algilama_araligi = millis();
      alkis++;
    }
  }

  if (millis() - algilama_araligi_baslangic >= 400)
  {
    if (alkis == 2)
    {
      if (!isik_durumu)
      {
        isik_durumu = true;
        digitalWrite(role, HIGH);
        ledStateChanged = true;

      }
      else if (isik_durumu)
      {
        isik_durumu = false;
        digitalWrite(role, LOW);
        ledStateChanged = true;
      }

    }
    alkis = 0;
  }

  // Bluetooth
  // if text arrived in from BT serial...
  if (BT.available())
  {
    a = (BT.read());
    if (a == '0')
    {
      isik_durumu = true;
      digitalWrite(role, HIGH);
      //BT.println("LED on");
    }
    if (a == '1')
    {
      isik_durumu = false;
      digitalWrite(role, LOW);
      //BT.println("LED off");
    }

    if (a == 'x') // send led state
    {
      if (isik_durumu) {
        BT.print("0");

      } else {
        BT.print("1");
      }
    }


    delay(100);

  }

  if (ledStateChanged) {
    if (isik_durumu) {
      BT.print("0");
      //Serial.print("true led state");

    } else {
      BT.print("1");
      //Serial.print("false led state");

    }

    ledStateChanged = false;
  } 

}
