#include <LiquidCrystal_I2C.h> 
#include <SoftwareSerial.h>
// Set up a new SoftwareSerial object
SoftwareSerial gsmSerial(9, 10);
 /*include LCD I2C Library*/
#define buzzer 8
LiquidCrystal_I2C lcd(0x27,16,2);
void sing();
void setAlert();
int redLed = 11;
int greenLed = 12;
int gas = A0;
int sms_count=0;
int sensorThres = 370;


void setup() {
  
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(gas, INPUT);
  gsmSerial.begin(9600); 
  Serial.begin(9600);
  delay(1000);
  lcd.begin(16, 2);
  lcd.init();  /*LCD display initialized*/   /*Clear LCD Display*/
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Gas leakage");
  lcd.setCursor(4, 1);
  lcd.print("Detection");
  delay(1000);
  lcd.clear();
  
  
}

void loop() {
 int analogSensor = analogRead(gas);
 
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  lcd.print("GAS Level:");
  lcd.print(analogSensor);
  

  if (analogSensor > sensorThres)
  {  call();
    SendMessage();
     digitalWrite(redLed, HIGH);
     digitalWrite(greenLed, LOW);
    lcd.setCursor(2, 1);
    lcd.print("Alert OPEN WINDOW....!!!");
    digitalWrite(13, HIGH);
    sing();
    delay(1000);
    
  }
        else
  {
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    
    lcd.setCursor(2, 1);
    lcd.print(".....Normal.....");
    noTone(buzzer);
  }
  
  lcd.clear();
    }


 

  void SendMessage()
{
   Serial.println("Setting the GSM in text mode");
   gsmSerial.println("AT+CMGF=1\r");
   delay(2000);
   Serial.println("Sending SMS to the desired phone number!");
   gsmSerial.println("AT+CMGS=\"+918428431271\"\r");
   // Replace x with mobile number
   delay(2000);

   gsmSerial.println("!!GAS LEAKING!!");    // SMS Text
   delay(200);
   gsmSerial.println((char)26);               // ASCII code of CTRL+Z
   delay(2000);
}
void call()
{
 gsmSerial.println("ATD+918428431271;");
 Serial.println("calling");
   delay(1000);
  }


void sing()
{
  tone(8,660,100);
delay(10);
tone(8,650,100);
delay(10);

  }