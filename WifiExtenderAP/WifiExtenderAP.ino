#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <lwip/napt.h>
#include <lwip/dns.h>

#define NAPT 1000
#define NAPT_PORT 10

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK "thereisnospoon"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  String message = "<h1>You are connected</h1>";
  message += "<form method='POST' action='/submit'>";
  message += "<input type='text' name='ssid' placeholder='Enter SSID'>";
  message += "<input type='password' name='password' placeholder='Enter password'>";
  message += "<button type='submit' value='Connect'>";
  message += "</form>";

  server.send(200, "text/html", message);
}

void handleSubmit() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.printf("\nSTA: %s (dns: %s / %s)\n", WiFi.localIP().toString().c_str(), WiFi.dnsIP(0).toString().c_str(), WiFi.dnsIP(1).toString().c_str());

  auto& server = WiFi.softAPDhcpServer();
  server.setDns(WiFi.dnsIP(0));

  WiFi.softAPConfig(  // enable AP, with android-compatible google domain
    IPAddress(172, 217, 28, 254), IPAddress(172, 217, 28, 254), IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid "extender",  password);
  Serial.printf("AP: %s\n", WiFi.softAPIP().toString().c_str());

  Serial.printf("Heap before: %d\n", ESP.getFreeHeap());
  err_t ret = ip_napt_init(NAPT, NAPT_PORT);
  Serial.printf("ip_napt_init(%d,%d): ret=%d (OK=%d)\n", NAPT, NAPT_PORT, (int)ret, (int)ERR_OK);
  if (ret == ERR_OK) {
    ret = ip_napt_enable_no(SOFTAP_IF, 1);
    Serial.printf("ip_napt_enable_no(SOFTAP_IF): ret=%d (OK=%d)\n", (int)ret, (int)ERR_OK);
    if (ret == ERR_OK) { Serial.printf("WiFi Network '%s' with same password is now NATed behind '%s'\n", ssid "extender", password); }
  }
  Serial.printf("Heap after napt init: %d\n", ESP.getFreeHeap());
  if (ret != ERR_OK) { Serial.printf("NAPT initialization failed\n"); }

  server.send(200, "text/plain", "Connecting to network...");
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }

  server.send(404, "text/plain", message);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  MDNS.update();
}
