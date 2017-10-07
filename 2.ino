

#include <SimpleDHT.h>
#include<ArduinoJson.h>
#include <ESP8266WiFi.h>


const char* ssid     = "Ashwini";
const char* password = "12345678";
const char* host = "api.thingspeak.com";
const char* writeAPIKey = "B6CJO5EKVJUFUNU9";

int pinDHT11 = 2;
SimpleDHT11 dht11;
void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
//    return; 
  
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  }

  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "api.thingspeak.com/channels/329318/feeds.json?api_key=B6CJO5EKVJUFUNU9&results=2";
//  url+=writeAPIKey;
//  url+="&field1=";
//  url+=String(temperature);
//  url+="&field2=";
//  url+=String(humidity);
//  url+="\r\n";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
                   delay(1000);


               String section="header";
while(client.available())
{
 String line = client.readStringUntil('\r');
 // we'll parse the HTML body here

 if(section=="header")
 { //headers..
//Serial.print(".");
  if (line=="\n")
  { //skips the empty space at the beginning 
section="json";
  }
 }
else if (section=="json")
 { // print the good stuff
section="ignore";
 String result = line.substring(1);
Serial.print(result);
 // Parse JSON
int size = result.length() + 1;
char json[size];
result.toCharArray(json, size);
StaticJsonBuffer<1000> jsonBuffer;
JsonArray& root = jsonBuffer.parseArray(json);
if (!root.success())
{
Serial.println("parseObject() failed");
return;
}

const char* motor1 = root['JSON'][0];
//const char* Motor2 = root['JSON'][1];
//const char* Motor3 = root['JSON'][2];
//const char* Motor4 = root['JSON'][3];
//const char* Valve1 = root['JSON'][4];
//const char* Valve2 = root['JSON'][5];
//const char* Valve3 = root['JSON'][6];
//const char* Valve4 = root['JSON'][7];
//
//Serial.println(Motor1);
//Serial.println(Motor2);
//Serial.println(Motor3);
//Serial.println(Motor4);
//Serial.println(Valve1);
//Serial.println(Valve2);
//Serial.println(Valve3);
Serial.println(motor1);
}
}
 Serial.println();
 Serial.println("closing connection");
 }
//  unsigned long timeout = millis();
//  while(client.available() == 0) {
//    if (millis() - timeout > 5000) {
//      Serial.println(">>> Client Timeout !");
//      client.stop();
//      return;
//    }
// 
//  }
//  // Read all the lines of the reply from server and print them to Serial
//  while(client.available())
//    {
//      String line;
//  while(client.available())
//  {
//    line += client.readStringUntil('\r');
//  }
// 
//  Serial.println("#####################################################################################");
//     Serial.print(line);
//       
//    int i1 = line.indexOf("{");
//    int i2 = line.lastIndexOf("}");
//      Serial.print("INDEX OF '{' :");
//      Serial.println(i1);
//      Serial.print("INDEX OF '}' :");
//      Serial.println(i2);
//      String res = line.substring(i1, i2+1);
//     
//      Serial.println("#####################################################################################");
//      Serial.print("JSON OUTPUT :");
//      Serial.println(res);
//
//      StaticJsonBuffer<200> JsonBuffer;
//      JsonObject& root = JsonBuffer.parseObject(res);
//      if (root.success())
//        {
//          Serial.println("parseObject() success");
//          delay(1000);
//          
//        }
//        Serial.print("##########################################################################################\n");
//        const char* Name    = root[" "];
//        Serial.print("OUTPUT IS :");
//        Serial.println(Name);
////          const char* Name1    = root["feeds"][0]["field2"];
////        Serial.print("OUTPUT IS :");
////        Serial.println(Name1);
//        Serial.print("##########################################################################################\n");
//
//  Serial.println("closing connection");
//        Serial.print("##########################################################################################");

//   }}

