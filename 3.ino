/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

const char* ssid     = "OS3-AP3";
const char* password = "Udt@Punj@b";

const char* host = "www.google.co.in";
//const char* streamId   = "....................";
//const char* privateKey = "....................";

void setup() {
  Serial.begin(9600);
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


  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

//  // We now create a URI for the request
//  String url = "/search?q=arduino";
//  url += streamId;
//  url += "?private_key=";
//  url += privateKey;
//  url += "&value=";
//  url += value;
//
//  Serial.print("Requesting URL: ");
//  Serial.println(url);
//
//  // This will send the request to the server
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "Connection: close\r\n\r\n");
               client.print("GET /search?q=arduino HTTP/1.1\r\n");
               client.println("Host: www.google.co.in \r\n");
               client.println("Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from serverand print them to Serial
  String section="header";
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);

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

const char* Motor1 = root['res'][0];
//const char* Motor2 = root['JSON'][1];
//const char* Motor3 = root['JSON'][2];
//const char* Motor4 = root['JSON'][3];
//const char* Valve1 = root['JSON'][4];
//const char* Valve2 = root['JSON'][5];
//const char* Valve3 = root['JSON'][6];
//const char* Valve4 = root['JSON'][7];

Serial.println(Motor1);
//Serial.println(Motor2);
//Serial.println(Motor3);
//Serial.println(Motor4);
//Serial.println(Valve1);
//Serial.println(Valve2);
//Serial.println(Valve3);
//Serial.println(Valve4);
}
}
 Serial.println();
 Serial.println("closing connection");
 }
