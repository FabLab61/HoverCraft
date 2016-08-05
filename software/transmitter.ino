#define pinPowerTransmitter 12
#define pinData 11
#define pinPowerJoy 2
#define pinX A0
#define pinY A1
#define pinPot 1500 // for future pot

#include <VirtualWire.h>
#include <EasyTransferVirtualWire.h>

EasyTransferVirtualWire ET;

struct SEND_DATA_STRUCTURE {
  int Hrz;
  int Vert;
  int Serv;
};

SEND_DATA_STRUCTURE mydata;

void setup() {
  ET.begin(details(mydata));
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_set_tx_pin(pinData);

  pinMode(pinPowerTransmitter, OUTPUT);
  digitalWrite(pinPowerTransmitter, HIGH);
  pinMode(pinPowerJoy, OUTPUT);
  digitalWrite(pinPowerJoy, HIGH);

  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
}

void loop() {
  mydata.Serv = analogRead(pinX);
  mydata.Vert = analogRead(pinY);
  if (mydata.Vert <= 511) {
    //mydata.Vert = 960 + abs(mydata.Vert - 511) * 2.3;  // ** full power
    mydata.Vert = 960 + abs(mydata.Vert - 511); // ** medium
  }
  else
  {
    mydata.Vert = 960 + (mydata.Vert/3); // ** low
  };
  
    mydata.Serv = 960 + mydata.Serv;
    mydata.Hrz=pinPot; // for future pot;
  ET.sendData();
}
