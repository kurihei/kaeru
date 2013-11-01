#include "Arduino.h"
#include <ADK.h>

//#define ID0MAXV 0x46
//#define ID0MINV 0x36

#define ID0MAXV 0xff
#define ID0MINV 0x00

#define ID1MAXV 0x41
#define ID1MINV 0x29

ADK L;

// ADK1 usb accessory strings
#define ACCESSORY_STRING_VENDOR "KuriShika"
#define ACCESSORY_STRING_NAME   "Afro"
#define ACCESSORY_STRING_LONGNAME "DemoKit Arduino Board"
#define ACCESSORY_STRING_VERSION  "1.0"
#define ACCESSORY_STRING_URL    "http://www.android.com"
#define ACCESSORY_STRING_SERIAL "0000000012345678"

int i;
int j;
int pos;


void GoCommand(byte b1, byte b2, byte b3){
//  Serial.println("GoCommand!");
   Serial1.write(b1);
   Serial1.write(b2);
   Serial1.write(b3);
  
}

void setup(){
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println("setup starting");
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
  
  GoCommand(0x80, 0x3a, 0x4c);
  delay(100);
  GoCommand(0x81, 0x3a, 0x4c);
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
  Serial1.write(0x20);
  delay(1);
  }
  Serial.println("setup ending");
}

void loop(){
  char buf[64];
  char code=0x00;
  L.adkEventProcess();
  int recvLen = 0;
  if(L.accessoryConnected()){
    recvLen = L.accessoryReceive(buf, sizeof(buf));
    Serial.print("recvLen=");
    Serial.println(recvLen);
  }
  i=0;
  while(recvLen - i >= 4){
    Serial.println("Receiving");
    Serial.print(buf[0]);
    Serial.print(",");
    Serial.print(buf[1]);
    Serial.print(",");
    Serial.print(buf[2]);
    Serial.print(",");
    Serial.println(buf[3]);
    Serial.print("buf2=");
    Serial.println((unsigned int)buf[2]);
      if(buf[i++] != 0xaa)continue;
      if((unsigned int)buf[i] == 0x80){
//        Serial.println("start moving Servo ID=0");
        if((unsigned int)buf[i+1] < ID0MINV | (unsigned int)buf[i+1] > ID0MAXV){
//          Serial.println("refuse value ID=0");
          continue;
        }
      }else if((unsigned int)buf[i] == 0x81){
//        Serial.println("start moving Servo ID=1");
        if((unsigned int)buf[i+1] < ID1MINV | (unsigned int)buf[i+1] > ID1MAXV){
//          Serial.println("refuse value ID=1");
          continue;
        }
      }
      GoCommand((byte)buf[i++], (byte)buf[i++], (byte)buf[i++]);
  }
  delay(95);
}
