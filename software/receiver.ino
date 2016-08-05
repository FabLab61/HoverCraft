#include <ServoTimer2.h>
#define pinHrz 5
#define pinVert 6
#define pinServ 11

#include <VirtualWire.h>
#include <EasyTransferVirtualWire.h>
#define pinPowerReciever 2
#define pinDo 3

unsigned long tlp; //time of last packet;
unsigned long now;

EasyTransferVirtualWire ET;
ServoTimer2 Hrz;
ServoTimer2 Vert;
ServoTimer2 Serv;

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
  vw_set_rx_pin(pinDo);
  vw_rx_start();

  pinMode(pinPowerReciever, OUTPUT);
  digitalWrite(pinPowerReciever, HIGH); // 5v for Reciever

  Hrz.attach(pinHrz);
  Vert.attach(pinVert);
  Serv.attach(pinServ);
  Hrz.write(0);
  Vert.write(0);
  Serv.write(0);

  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, LOW);
  if (ET.receiveData()) {
    tlp = millis();
    digitalWrite(13, HIGH);
    Hrz.write(mydata.Hrz);
    Vert.write(mydata.Vert);
    Serv.write(mydata.Serv);
  }
  now = millis();
  if (now > tlp + 300) {
    Hrz.write(0);
    Vert.write(0);
    Serv.write(0);
  }

}
