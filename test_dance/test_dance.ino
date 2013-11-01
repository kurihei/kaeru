#define USARTADD 0x

char i;
int j;

void setup(){
  Serial.begin(115200);
  Serial1.begin(115200);
  i=0;
/*  USART_Configure(USART1, US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_8_BIT | US_MR_PAR_NO |
                   US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL , 115200,  78000000);
  USART_SetTransmitterEnabled(USART1, 1);  */  

/*  for(j=0;j<100;j++){
     delay(100);
  } */ 
  Serial1.write(0x81);
  delay(1);
  Serial1.write(0x3a);
  delay(1);
  Serial1.write(0x4c);
  delay(1);
  
  for(j=0;j<100;j++){
  Serial1.write(0x80);
  Serial1.write(0x3a);
  Serial1.write(0x4c);
  delay(1);
  }
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

  Serial1.write(0x80);
  delay(1);
  Serial1.write(0x46);
  delay(1);
  Serial1.write(0x4C);
  delay(100);

/*head*/
  Serial1.write(0x81);
  delay(1);
  Serial1.write(0x40);
  delay(1);
  Serial1.write(0x4c);
  delay(300);
  Serial1.write(0x81);
  delay(1);
  Serial1.write(0x30);
  delay(1);
  Serial1.write(0x4c);
  delay(300);
  Serial1.write(0x81);
  delay(1);
  Serial1.write(0x40);
  delay(1);
  Serial1.write(0x4c);
  delay(300);
  Serial1.write(0x81);
  delay(1);
  Serial1.write(0x30);
  delay(1);
  Serial1.write(0x4c);
  delay(1);  
  delay(1000);
  
   Serial1.write(0x80);
  delay(1);
  Serial1.write(0x36);
  delay(1);
  Serial1.write(0x4C); 
  delay(100);
  
  /*Head*/
  Serial1.write(0x81);
  delay(1);
  Serial1.write(0x40);
  delay(1);
  Serial1.write(0x4c);
  delay(300);  
  Serial1.write(0x81);
  delay(1);
  Serial1.write(0x30);
  delay(1);
  Serial1.write(0x4c);
  delay(300);
  Serial1.write(0x81);
  delay(1);
  Serial1.write(0x40);
  delay(1);
  Serial1.write(0x4c);
  delay(300);  
  Serial1.write(0x81);
  delay(1);
  Serial1.write(0x30);
  delay(1);
  Serial1.write(0x4c);
  delay(300);
  
  delay(1000);
  
  i++;
  if(i==0xff)i=0;
}
  
