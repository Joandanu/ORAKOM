//Dibawah ini adalah Libary BLYNK
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLTnrvEID-"
#define BLYNK_DEVICE_NAME "PROJECT ORAKOM"
#define BLYNK_AUTH_TOKEN "AyxQqejj7UcuduQTTZzFnkYEs2Tir6XA" //BLYNK AUTH TOKEN

//Dibawah ini untuk menyambung ke WIFI
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Joan Ganteng"; //Nama Wifi
char pass[] = "joandanu"; //Password Wifi

//Libary 
#include  <Wire.h> //Libary untuk sensor
#include  <LiquidCrystal_I2C.h> //Libary untuk LCD
#include <SoftwareSerial.h>

//
#define TRIG D0
#define ECHO D6
#define BUZZER D4
#define LED D5

//Variabel untuk menghitung jarak
long durasi, jarak;
long waktuu = 8;
long old_time = 0;
long waktu = 500;
long old_timee = 0;
int togle = 1;


void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80); //Konfigurasi BLYNK
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  
  //OUTPUT LCD
  lcd.init();   
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("ARDUINO"); 
  lcd.setCursor(0,1);
  lcd.print("SENSOR JARAK");
  delay(2000);
  lcd.clear();

}

void loop() {
    
  digitalWrite(TRIG, LOW);
  delayMicroseconds(8);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(8);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(8);
  durasi = pulseIn(ECHO, HIGH); 
  jarak = (durasi / 2) / 29.1; 
   
  if ( millis() - old_time > waktu){ 
   
     if((jarak <= 15) && (jarak >= 10)) {
       digitalWrite(BUZZER, HIGH);
       digitalWrite(LED, HIGH);
      delay(200);
       digitalWrite(BUZZER, LOW);
       digitalWrite(LED, LOW);
     }else if((jarak < 10) && (jarak >=8)){
        digitalWrite(BUZZER, HIGH);
        digitalWrite(LED, HIGH);
       delay(100);
        digitalWrite(BUZZER, LOW);
        digitalWrite(LED, LOW);
     }else if((jarak < 8 ) && (jarak >= 5)){
            digitalWrite(BUZZER, HIGH);
            digitalWrite(LED, HIGH);
       delay(50);
            digitalWrite(BUZZER, LOW);
         digitalWrite(LED, LOW);
     }else if((jarak < 5 ) && (jarak >= 3)){
           digitalWrite(BUZZER, HIGH);
           digitalWrite(LED, HIGH);
       delay(30);
         digitalWrite(BUZZER, LOW);
         digitalWrite(LED, LOW);
     }else if(jarak < 3 ){
          digitalWrite(BUZZER, HIGH);
          digitalWrite(LED, HIGH);
       delay(10);
          digitalWrite(BUZZER, LOW);
          digitalWrite(LED, LOW);
     }else{
           digitalWrite(BUZZER, LOW);
           digitalWrite(LED, LOW);
     }

    Blynk.virtualWrite(V0, jarak); //OUTPUT BLYNK     
    
    //OUTPUT LCD
    lcd.setCursor(0,0); 
    lcd.print("JARAK = ");   
    lcd.print(jarak);
    lcd.print("  CM");
    
    //OUTPUT SERIAL MONITOR
    Serial.print("JARAK = ");
    Serial.println(jarak);    
   
    old_time= millis();
   
    Blynk.run();
   
   
 }

}