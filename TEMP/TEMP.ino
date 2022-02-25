#include <LiquidCrystal.h>
LiquidCrystal lcd(4,5,6,7,8,9);

#define temp_sen A0
#define heart    2
#define buzzer   3

String heart_sen_status,temp_sen_status;
int count=0, chk, heart_read=0,heart_send,heart_min;
unsigned long previousMillis1 = 0;
unsigned int interval1 = 1000, sec = 0,sec1 = 0;
unsigned int temp_sen_read=0;
String msg="NORMAL";
String URL;
const char* ssid = "Test";
const char* password ="12345678";
void data_out();
void setup(void)
{
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(temp_sen,INPUT);
  pinMode(heart,INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW);
  
  lcd.setCursor(0,0); lcd.print(" Patient Health ");
  lcd.setCursor(0,1); lcd.print("   monitoring   ");
  Serial.println(" Patient Health monitoring ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Temp :         ");
  lcd.setCursor(0,1); lcd.print("Pulse:         ");
}
  void loop(void)
{
   
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis1) >= interval1)   // check for rollover delay 1
  {
    sec++;sec1++;
    previousMillis1 = currentMillis;
  }
  if     (digitalRead(heart)==LOW &&chk==0){chk=1;}
  else if(digitalRead(heart)==HIGH&&chk==1){chk=0;heart_read++;}
    if     (heart_min<100){lcd.setCursor(11, 1); lcd.print(" ");}
    else if(heart_min<10) {lcd.setCursor(10, 1); lcd.print("  ");}
         lcd.setCursor(10, 1); lcd.print(heart_read);
      temp_sen_read=analogRead(temp_sen);
     // temp_sen_read=temp_sen_read/3;
     // temp_sen_read=temp_sen_read-100;
     if     (temp_sen_read<10)   {lcd.setCursor(8, 0); lcd.print("   "); }
     else if(temp_sen_read<100)  {lcd.setCursor(9, 0); lcd.print("  ");  }
     else if(temp_sen_read<1000) {lcd.setCursor(10, 0); lcd.print(" ");   }
      lcd.setCursor(7, 0); lcd.print(temp_sen_read);Serial.println(temp_sen_read);
      if(temp_sen_read>40)
      {  digitalWrite(buzzer,HIGH);data_out();
         lcd.setCursor(14, 0); lcd.print("Ab");}
     else {  digitalWrite(buzzer,LOW);
             lcd.setCursor(14, 0); lcd.print("Nm");}
  if(sec>9)
  {
    heart_min=heart_read*6;
    if     (heart_min<100){lcd.setCursor(8, 1); lcd.print(" ");}
    else if(heart_min<10) {lcd.setCursor(7, 1); lcd.print("  ");}
    lcd.setCursor(7, 1); lcd.print(heart_min);

    if     (heart_min>=60&&heart_min<=100)
    {digitalWrite( buzzer,LOW);lcd.setCursor(14, 1); lcd.print("Nm"); }
    else
    {digitalWrite( buzzer,HIGH);delay(1000);digitalWrite( buzzer,LOW);
    lcd.setCursor(14, 1); lcd.print("Ab"); }
    data_out();
    heart_read=0;
    sec=0;
  }
}

void data_out()
{
  
    URL ="http://iot-patienthealth.krabd.com/data.php?uid=ADDWEWS5421EW5BTDM7ETHGKXT&data1=";

    URL =URL+heart_read;  
    URL =URL+"&data2=";  //location
    URL =URL+temp_sen_read;
    Serial.print("WEB Send URL: ");  Serial.println(URL);Serial.println();Serial.println(); 
    delay(1000);
   //     HTTPClient http;
   // http.begin(URL);
   // int httpCode = http.GET();
   // String payload = http.getString();
    //Serial.println(payload);
   // http.end();
    delay(500);
 }
