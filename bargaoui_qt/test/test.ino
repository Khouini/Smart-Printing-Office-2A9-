//Viral Science
//RFID
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4); //afficheur



#define PIN_LED 7
#define PIN_LED2   8
 
#define SS_PIN 10
#define RST_PIN 9  

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name
// parking space 
int Total = 5;
int Space;
int var1 = 0;


char data; // variable contenant le caractère lu
int x; // variable contenant l'intensité de la deuxième lampe

 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(2); //servo pin
  myServo.write(0); //servo start position


  Serial.println("Put your card to the reader...");
  Serial.println();

  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("AKREM  ****");
  lcd.setCursor(3,1);
  lcd.print( "****  FAHED");

  
   x=0; // Intialiser l'intensité de la deuxième lampe 
   
delay(2000);
   lcd.setCursor (0,0);
lcd.print("  Car  Parking  ");
lcd.setCursor (0,1);
lcd.print("     System     ");
 delay(1500);
 lcd.clear() ;
lcd.setCursor (0,0);
Space = Total;
lcd.print("Total Space: ");
lcd.print(Total);

lcd.setCursor (0,1);
lcd.print("Have  Space: ");
lcd.print(Space);





  
    pinMode(PIN_LED,OUTPUT);
    pinMode(PIN_LED2,OUTPUT);
    digitalWrite(PIN_LED,LOW);
   digitalWrite(PIN_LED2,LOW);
}
void loop() 
{
  if (Serial.available()){




         
  }
    //Si un message a été reçu  faire ceci
     data=Serial.read();  
   
     if((data=='1') &&(Space<5) )//si le caractère lu est égale à 1
    {

      Serial.write('1'); //envoyer le nouvel état de la lampe  

digitalWrite(PIN_LED,HIGH);
   
 delay(2000);
       digitalWrite(PIN_LED,LOW);
  Space = Space+1;
    Serial.println("nb de Space :   ");
    Serial.println(Space);
    Serial.println("Authorized access");
    Serial.println();
      lcd.clear() ;
    lcd.setCursor(1,0);
  lcd.print(" Authorized");
   lcd.setCursor(2,1);
    lcd.print("  access ");
    delay(1000);
 lcd.clear() ;
 lcd.setCursor (0,0);
lcd.print("  out by  ");
  myServo.write(90);
delay(3000);
myServo.write(0);
  
lcd.setCursor (0,0);
lcd.print("Total Space: ");
lcd.print(Total);

lcd.setCursor (0,1);
lcd.print("Have  Space: ");
lcd.print(Space);
      
     } 


      if((data=='2')  &&(Space>0) )//si le caractère lu est égale à 1
    {

      Serial.write('2'); //envoyer le nouvel état de la lampe  

digitalWrite(PIN_LED,HIGH);
   
 delay(2000);
       digitalWrite(PIN_LED,LOW);
  Space = Space-1;
  Serial.println("nb de Space :   ");
    Serial.println(Space);
    Serial.println("Authorized access");
    Serial.println();
      lcd.clear() ;
    lcd.setCursor(1,0);
  lcd.print(" Authorized");
   lcd.setCursor(2,1);
    lcd.print("  access ");
    delay(1000);
 lcd.clear() ;
 lcd.setCursor (0,0);
lcd.print("  in  ");
  myServo.write(90);
delay(3000);
myServo.write(0);
  
lcd.setCursor (0,0);
lcd.print("Total Space: ");
lcd.print(Total);

lcd.setCursor (0,1);
lcd.print("Have  Space: ");
lcd.print(Space);
      
     } 



 

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
   
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  data=Serial.read(); 
  Serial.println("data");     
   Serial.println(data);    
  if ((content.substring(1) == "2A D6 26 48") &&(Space>0) && ( var1 == 0 ) )  //change here the UID of the card/cards that you want to give access
  {
    var1 = 1;
     Serial.write('1');
      // Allume la LED
      digitalWrite(PIN_LED,HIGH);
   
 delay(2000);
       digitalWrite(PIN_LED,LOW);
  Space = Space-1;
    Serial.println("Authorized access");
    Serial.println();
    Serial.println("nb de Space :   ");
    Serial.println(Space);
      lcd.clear() ;
    lcd.setCursor(1,0);
  lcd.print(" Authorized");
   lcd.setCursor(2,1);
    lcd.print("  access ");
    delay(1000);
 lcd.clear() ;
 lcd.setCursor (0,0);
lcd.print("  WELCOME ");
  myServo.write(90);
delay(3000);
myServo.write(0);
  
lcd.setCursor (0,0);
lcd.print("Total Space: ");
lcd.print(Total);

lcd.setCursor (0,1);
lcd.print("Have  Space: ");
lcd.print(Space);

}
 else if ((content.substring(1) == "2A D6 26 48")  &&(Space<5) && (var1 == 1 )) {

{
  var1= 0;
     Serial.write('1');
      // Allume la LED
      digitalWrite(PIN_LED,HIGH);
   
 delay(2000);
       digitalWrite(PIN_LED,LOW);
  Space = Space+1;
    Serial.println(" access ok ");
    Serial.println();
    Serial.println("nb de Space :   ");
    Serial.println(Space);
      lcd.clear() ;
    lcd.setCursor(1,0);
  lcd.print(" Authorized");
   lcd.setCursor(2,1);
    lcd.print("  access ");
    delay(1000);
 lcd.clear() ;
 lcd.setCursor (0,0);
lcd.print("  out ");
  myServo.write(90);
delay(3000);
myServo.write(0);
  
lcd.setCursor (0,0);
lcd.print("Total Space: ");
lcd.print(Total);

lcd.setCursor (0,1);
lcd.print("Have  Space: ");
lcd.print(Space);




   
  }
  }
 
 else  {
    Serial.println(" Access denied");
    lcd.clear() ;
    lcd.setCursor(1,0);
  lcd.print(" Access denied");
    delay(1000);
    
    lcd.setCursor (0,0);
lcd.print(" Sorry not Space ");  
lcd.setCursor (0,1);
lcd.print("    Available    "); 


 // Allume la LED

      digitalWrite(PIN_LED2,HIGH);

delay (1000);

 digitalWrite(PIN_LED2,LOW);
//Space = Space+1;
lcd.clear() ;
lcd.setCursor (0,0);
lcd.print("Total Space: ");
lcd.print(Total);

lcd.setCursor (0,1);
lcd.print("Have  Space: ");
lcd.print(Space);



  
   
    
  }

   
} 
