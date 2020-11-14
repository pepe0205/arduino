
#include "DHT.h"
#include<ESP8266WiFi.h>
#include <SPI.h>

int pin = 14; //D5 trên wemos
DHT dht(pin,DHT11);
float h;  //humidity
float t;  //temperature

char ssid[]="Thanh Nhan 205"; //Tên wifi
char pass[]="0903183523";     // pass wifi
int status = WL_IDLE_STATUS;  //Trạng thái connect của wifi
char server[]="mtpmtp.000webhostapp.com"; // địa chỉ ip của local server

WiFiClient client;



void setup() {
  Serial.begin(9600);
  dht.begin();
  connectToWifi();
  //setup cho chươnh trình
}
//------------------------------------------------------------------------------


/* Infinite Loop */
void loop(){

  
  h=dht.readHumidity(); //đọc  độ ẩm
  t=dht.readTemperature(); // đọc nhiệt độ

  Sending_To_phpmyadmindatabase(); 
    delay(30000);
   
}

  void connectToWifi()
  {
  Serial.printf("Connecting to %s \n", ssid);
  WiFi.begin(ssid, pass); //bắt đầu kết nối wifi
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    //check kết nối
    
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP()); 
  delay(1000);
  }
  void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) {                      
    Serial.println("connected");
    // Make a HTTP request:
    
    Serial.print("GET /Arduino/arduino_final.php?humidity=");     //url cho file host dạng ip:port/Arduino/arduino.php?humidity=2&temperature=3
    client.print("GET /Arduino/arduino_final.php?humidity=");    
    Serial.print(h);
    client.print(h);
    client.print("&temperature=");
    Serial.print("&temperature=");
    client.print(t);
    Serial.println(t);
    client.print(" ");      
    client.print("HTTP/1.1");
    client.println();
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();

  } else {
    // nếu ko kết nối đc sẽ gọi th này
    Serial.println("connection failed");
  }
  
 }
