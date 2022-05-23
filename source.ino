#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DHT.h>
#include "website.h"

#define DHTPin D4
#define DHTTYPE DHT11
DHT dht(DHTPin,DHTTYPE);

#define LIGHT D5
#define SPEED_1 D6
#define SPEED_2 D7
#define SPEED_3 D8

float temp;
float humi;
String temp_value;
String humi_value;

String start_time;
String stop_time;
String timer = "OFF";
String LightState = "OFF";
String FanState = "OFF";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "2.asia.pool.ntp.org", 7*3600);
ESP8266WebServer webServer(1235);

char* ssid = "Phan Anh Tu";
char* pass = "999999991";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LIGHT, OUTPUT);
  pinMode(SPEED_1, OUTPUT);
  pinMode(SPEED_2, OUTPUT);
  pinMode(SPEED_3, OUTPUT);
  pinMode(DHTPin, INPUT);
  
  digitalWrite(SPEED_1, LOW);
  digitalWrite(SPEED_2, LOW);
  digitalWrite(SPEED_3, LOW);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pass);
  while(WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.print("...");
  }
  Serial.print(WiFi.localIP());
  
  webServer.begin();
  webServer.on("/", mainPage);
  webServer.on("/light", inter_light);
  webServer.on("/setTimer", setTimer);
  webServer.on("/speed_1", speed1);
  webServer.on("/speed_2", speed2);
  webServer.on("/speed_3", speed3);
  webServer.on("/offSpeed", offspeed);
  webServer.on("/updateData", updateData);

  dht.begin();
  timeClient.begin();
}

void loop() {
  // Nghe yêu cầu từ client
  webServer.handleClient();
  // Cập nhật thời gian
  timeClient.update();
  // Đọc giá trị nhiệt độ từ cảm biến
  temp_value = readTemp();
  // Đọc giá trị độ ẩm từ cảm biến
  humi_value = readHumi();
  
  if(timer == "ON") //Bật chế độ hẹn giờ 
  {
    String current_time = timeClient.getFormattedTime();
    if( start_time == current_time ) //Hẹn giờ bật đèn
    {
      digitalWrite(LIGHT, HIGH);
      LightState = "ON";
    }
    else if( stop_time == current_time ) //Hẹn giờ tắt đèn 
    {
      digitalWrite(LIGHT, LOW);
      LightState = "OFF";
    }
  }
}

void mainPage() {
  String s = MainPage;
  webServer.send(200, "text/html", s);
}

// Hàm tương tác với đèn 
void inter_light() {
  if(LightState == "OFF") //Đèn tắt => mở 
  {
      digitalWrite(LIGHT, HIGH);
      LightState = "ON";
      webServer.send(200, "text/html", "Light:ON");
  }
  else //Đèn bật => tắt 
  {
      digitalWrite(LIGHT, LOW);
      LightState = "OFF";
      webServer.send(200, "text/html", "Light:OFF");
  }
}

// Hàm bật tính năng hẹn giờ
void setTimer() {
    if(timer == "OFF") {
       start_time = webServer.arg("start_time");
       stop_time = webServer.arg("stop_time");
       webServer.send(200, "text/html", "Timer:ON");
       timer = "ON";
    }
    else {
      timer = "OFF";
      webServer.send(200, "text/html", "Timer:OFF");
    }
}

void speed1() 
{
  digitalWrite(SPEED_2, LOW);
  digitalWrite(SPEED_3, LOW);
  digitalWrite(SPEED_1, HIGH);
  FanState = "1";
  webServer.send(200, "text/html", "OK");
}

void speed2() 
{
  digitalWrite(SPEED_1, LOW);
  digitalWrite(SPEED_3, LOW);
  digitalWrite(SPEED_2, HIGH);
  FanState = "2";
  webServer.send(200, "text/html", "OK");
}

void speed3() 
{
  digitalWrite(SPEED_1, LOW);
  digitalWrite(SPEED_2, LOW);
  digitalWrite(SPEED_3, HIGH);
  FanState = "3";
  webServer.send(200, "text/html", "OK");
}

void offspeed()
{
  digitalWrite(SPEED_1, LOW);
  digitalWrite(SPEED_2, LOW);
  digitalWrite(SPEED_3, LOW);
  FanState = "OFF";
  webServer.send(200, "text/html", "OFF");
}

String readTemp()
{
  temp = dht.readTemperature();
  String stemp = String(temp);
  if(isnan(temp))
  {
    return "ERR";
  }
  else
  {
    return stemp;
  }
}

String readHumi()
{
  humi = dht.readHumidity();
  String shumi = String(humi);
  if(isnan(humi))
  {
    return "ERR";
  }
  else
  {
    return shumi;
  }
}

void updateData() {
  String data = "{\"Light\": \"" + LightState + "\",\"Timer\": \"" + timer + "\",\"Speed\": \"" + FanState + "\",\"Temp\": \"" + temp_value + "\",\"Humi\": \"" + humi_value + "\"}";
  webServer.send(200, "application/json", data);
}
