#include "Arduino.h"
#include <ADK.h>
#define MAXDANCE 40

ADK L;

// ADK1 usb accessory strings
#define ACCESSORY_STRING_VENDOR "KuriShika"
#define ACCESSORY_STRING_NAME   "Afro"
#define ACCESSORY_STRING_LONGNAME "DemoKit Arduino Board"
#define ACCESSORY_STRING_VERSION  "1.0"
#define ACCESSORY_STRING_URL    "http://www.android.com"
#define ACCESSORY_STRING_SERIAL "0000000012345678"
//
//  dance code
//  0  =  wait 100msec
//  1  = 80,46,4c  move horizontal1
//  2  = 80,36,4c  move Horizontal2
//  3  = 81,40,4c  move HEAD1
//  4  = 81,30,4c  move HEAD2
//  5  = 80,3a,4c  move startpoint horizontal
//  6  = 81,3a,4c  move startpoint HEAD

/*int dance[56] = {1, 0, 3, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               2, 0, 3, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0};*/
int dance[MAXDANCE] = {1, 3, 0, 0, 4, 0, 0, 3, 0, 0, 4, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 
               2, 3, 0, 0, 4, 0, 0, 3, 0, 0, 4, 0, 0, 0, 
               0, 0, 0, 0, 0, 0};

int i;
int j;
int pos;


void ServoMove(int moveid){
  if(moveid==0){
//    delay(100);
  }else if(moveid==1){
    Serial1.write(0x80);
    Serial1.write(0x46);
    Serial1.write(0x4C);
  }else if(moveid==2){
    Serial1.write(0x80);
    Serial1.write(0x36);
    Serial1.write(0x4C);    
  }else if(moveid==3){
    Serial1.write(0x81);
    Serial1.write(0x40);
    Serial1.write(0x4C);
  }else if(moveid==4){
    Serial1.write(0x81);
    Serial1.write(0x30);
    Serial1.write(0x4C);    
  }else if(moveid==5){
    Serial1.write(0x80);
    Serial1.write(0x3a);
    Serial1.write(0x4C);
  }else if(moveid==6){
    Serial1.write(0x81);
    Serial1.write(0x3a);
    Serial1.write(0x4C);    
  }
  return;
}

void setup(){
  Serial.begin(115200);
  Serial1.begin(115200);
  i=0;
  pos=0;
  
  L.adkInit();
  L.usbSetAccessoryStringVendor(ACCESSORY_STRING_VENDOR);
  L.usbSetAccessoryStringName(ACCESSORY_STRING_NAME);
  L.usbSetAccessoryStringLongname(ACCESSORY_STRING_LONGNAME);
  L.usbSetAccessoryStringVersion(ACCESSORY_STRING_VERSION);
  L.usbSetAccessoryStringUrl(ACCESSORY_STRING_URL);
  L.usbSetAccessoryStringSerial(ACCESSORY_STRING_SERIAL);

  L.usbStart();
  
  ServoMove(6);
  delay(100);
  ServoMove(5);
  delay(200);
  
  /*SPEED*/
  for(j=0;j<100;j++){
  Serial1.write(0xc0);
  delay(1);
  Serial1.write(0x02);
  delay(1);
  Serial1.write(0x6);
  delay(1);
  Serial1.write(0xc1);
  delay(1);
  Serial1.write(0x02);
  delay(1);
  Serial1.write(0x30);
  delay(1);
  }
}

void loop(){
  char buf[64];
  char code=0x00;
  L.adkEventProcess();
  int recvLen = 0;
  if(L.accessoryConnected()){
    recvLen = L.accessoryReceive(buf, sizeof(buf));
  }
  if(recvLen > 0){  
      for(i=0;i<recvLen;i++){
        code |= buf[i];
      }
      if(code!=0){
        ServoMove(dance[pos]);
        pos++;
        if(pos==MAXDANCE){
          pos=0;
        }
      }else{
//        pos=0;
//        ServoMove(5);
//        ServoMove(6);
      }
  }
  delay(95);
}
