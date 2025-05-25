/*
SDA   Digital 10
SCK   Digital 13
MOSI  Digital 11
MISO  Digital 12
IRQ   unconnected
GND   GND
RST   Digital 9
3.3V  3.3V 
 */
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
String a;
const int KEY1=A0;
const int KEY2=A1;
int total=0;
int i=0;
int item=0;
int itm1=0;
int itm2=0;
int itm3=0;
char x=0; 
void setup() {
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("    WELCOME     ");
  lcd.setCursor(0,1);
  lcd.print(" HAPPY SHOPPING ");
  pinMode(KEY1, INPUT);  
  pinMode(KEY2, INPUT);
  digitalWrite(KEY1,HIGH);  
  digitalWrite(KEY2,HIGH); 
  Serial.println("WELCOME,HAPPY SHOPPING");  
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print(" SCAN UR ITEM   ");
  lcd.setCursor(0,1);
  lcd.print("ITMS:   BILL:   ");   
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
//  Serial.println("Approximate your card to the reader...");
  delay(100);   
}

void loop() {
home:
 if(digitalRead(KEY1)==LOW)
  {
RMV:    
  if(item>0)
  {
  lcd.setCursor(0,0);
  lcd.print(" SCAN THE ITEM  ");
  lcd.setCursor(0,1);
  lcd.print("   TO REMOVE    "); 
wait: 
//  Serial.println("waiting for remove");  
 if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    goto wait;
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    goto wait;
    return;
  }
  //Show UID on serial monitor
//  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
 //    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
 //    Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
 // Serial.println();

  content.toUpperCase();

    if (content.substring(1) == "06 C6 66 5F")  
    {
   
    if(itm1>=1)
    {
    item=item-1;
    total=total-10;
    itm1=itm1-1;
out:lcd.setCursor(0,0);
    lcd.print(" ITEM REMOVED   ");
    lcd.setCursor(0,1);
    lcd.print("ITMS:   BILL:   ");     
    lcd.setCursor(5,1);
    lcd.print(item);
    lcd.setCursor(13,1);
    lcd.print(total);
    Serial.println("ITEM REMOVED,DO YOU WANT TO REMOVE ANOTHER ITEM,REPLY Y OR N");  
rep_wait:    
  if(Serial.available()>0)  // Send data only when you receive data:
  {
    x = Serial.read();      //Read the incoming data and store it into variable data
    if(x == 'Y')            
    {
    Serial.print("YOU CAN REMOVE ANOTHER ITEM\n"); 
    delay(1000);
    goto RMV;
    } 
    if(x == 'N')            
    {
    Serial.print("NOW YOU CAN ADD ITEMS \n");       
    delay(1000); 
    lcd.setCursor(0,0);
    lcd.print(" SCAN UR ITEM   "); 
    goto home;
    } 
  }  
  goto rep_wait;      
    }
  lcd.setCursor(0,0);
  lcd.print(" SCAN UR ITEM   ");
  lcd.setCursor(0,1);
  lcd.print("ITMS:   BILL:   ");     
    goto home;    
    }
    if (content.substring(1) == "A6 30 0C 4E") 
    {
    if(itm2>=1)
    {      
    item=item-1;
    total=total-20;
    itm2=itm2-1;    
    goto out;
    }
  lcd.setCursor(0,0);
  lcd.print(" SCAN UR ITEM   ");
  lcd.setCursor(0,1);
  lcd.print("ITMS:   BILL:   ");     
    goto home;
    }
    if (content.substring(1) == "AA 8D 0B 03") 
    {
    if(itm3>=1)
    {      
    item=item-1;
    total=total-30;
    itm3=itm3-1;    
    goto out; 
    }
  lcd.setCursor(0,0);
  lcd.print(" SCAN UR ITEM   ");
  lcd.setCursor(0,1);
  lcd.print("ITMS:   BILL:   ");     
    goto home;
    } 
    goto wait;    
  } 
  }
  if(digitalRead(KEY2)==LOW)
  {
  lcd.setCursor(0,0);
  lcd.print("ITEMS:     ,BILL");
  lcd.setCursor(0,1);
  lcd.print("IN RUPEES:      "); 
  lcd.setCursor(10,1); 
  lcd.print(total);   
  lcd.setCursor(6,0);
  lcd.print(item);
    Serial.print("THANKS FOR SHOPPING,PLEASE PAY BILL RS:");   
    Serial.println(total); 
    Serial.println("PURCHASE DETAILS:");
    if(item>0)
    {
    Serial.print("TOTAL ITEMS:"); 
    Serial.println(item);   
    }     
    if(itm1>0)
    {
    Serial.print("SOAP QTY:"); 
    Serial.print(itm1);
    Serial.print(",AMNT=");
    itm1=itm1*10;
    Serial.println(itm1);            
    }   
    if(itm2>0)
    {
    Serial.print("SALT QTY:"); 
    Serial.print(itm2);  
    Serial.print(",AMNT=");
    itm2=itm2*20;
    Serial.println(itm2);          
    } 
    if(itm3>0)
    {
    Serial.print("SUGAR 500G QTY:"); 
    Serial.print(itm3); 
    Serial.print(",AMNT=");
    itm3=itm3*30;
    Serial.println(itm3);           
    } 
bill:             
    if(Serial.available()>0)
    {
    a= Serial.readString();// read the incoming data as string
    Serial.println(a);
    if(a[0]=='@')            
    {
    if(a[1]=='P')            
    {  
    if(a[2]=='A')            
    {
    if(a[3]=='I')            
    {  
    if(a[4]=='D')            
    { 
    lcd.setCursor(0,0);
    lcd.print("   THANK YOU,   ");
    lcd.setCursor(0,1);
    lcd.print("PAYMENT RECEIVED"); 
    while(1);    
    }}}}}
    }
    goto bill;
 
  }
   
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
//  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
//  Serial.println();
  content.toUpperCase();
  
    if (content.substring(1) == "06 C6 66 5F")  
    {
    Serial.println("SOAP,10Rs");      
    lcd.setCursor(0,0);
    lcd.print("    SOAP 10Rs  ");     
    item=item+1;
    total=total+10;
    lcd.setCursor(5,1);
    lcd.print(item);
    lcd.setCursor(13,1);
    lcd.print(total); 
    itm1=itm1+1; 
    delay(2000); 
    lcd.setCursor(0,0);
    lcd.print(" SCAN UR ITEM   ");    
    }
    if (content.substring(1) == "A6 30 0C 4E") 
    {
    Serial.println("SALT,20Rs");       
    lcd.setCursor(0,0);
    lcd.print("    SALT  20Rs  ");      
    item=item+1;
    total=total+20;
    lcd.setCursor(5,1);
    lcd.print(item);
    lcd.setCursor(13,1);
    lcd.print(total); 
    itm2=itm2+1;      
    delay(2000); 
    lcd.setCursor(0,0);
    lcd.print(" SCAN UR ITEM   ");    
    }
    if (content.substring(1) == "AA 8D 0B 03") 
    {
    Serial.println("SUGAR 500G,30Rs");       
    lcd.setCursor(0,0);
    lcd.print("SUGAR 500G 30Rs ");      
    item=item+1;
    total=total+30;
    lcd.setCursor(5,1);
    lcd.print(item);
    lcd.setCursor(13,1);
    lcd.print(total);   
    itm3=itm3+1;    
    delay(2000); 
    lcd.setCursor(0,0);
    lcd.print(" SCAN UR ITEM   ");    
    }       
    goto home;         
}
