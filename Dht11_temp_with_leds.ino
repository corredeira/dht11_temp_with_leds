#include <dht.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHT11_PIN 7 // define DHT pin

dht  DHT; 


void setup(){
  Serial.begin(115200);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  pinMode(13, OUTPUT); //define led pin
  pinMode(12, OUTPUT); //define led pin
  pinMode(11, OUTPUT); //define led pin

  

  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);

}

void loop(){
  int chk = DHT.read11(DHT11_PIN);  // check the data coming from the DHT pin
  float t = DHT.temperature;
  float h = DHT.humidity;
  Serial.print("Temperature = ");  // print temperature on the serial monitor
  Serial.println(t);
  Serial.print("Humidity = ");// Print humidity on the serial monitor
  Serial.println(h);
  delay(1000); // delay of 1 second

  

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }

  //clear display
  display.clearDisplay();

  // display temp
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(t);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");

  // display Humidity
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(h);
  display.print(" %"); 

  display.display();



  if (t <= 23){
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);    
  }
  if (t >= 24 && t <= 28){
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);    
  }
  if (t >= 29){
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);    
  }
  
   
}



