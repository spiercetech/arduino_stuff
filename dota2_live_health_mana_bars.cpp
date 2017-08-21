#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>
#define NUM_LEDS 50
CRGB leds[NUM_LEDS];

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid     = "Cats in Space";
const char* password = "meowmixer";

ESP8266WebServer server(80);

String webPage = "";
void health_loop(int li, int a, int b, int c){
    clear_health();
    for(int k = 0; k < li; k++) { 
      leds[k].setRGB(a, b, c);FastLED.show();
      FastLED.delay(20);
    }
}
void mana_loop(int li, int a, int b, int c){
    clear_mana();
    for(int k = 19; k > li; k--) { 
      leds[k].setRGB(a, b, c);FastLED.show();
      FastLED.delay(20);
    }
}
void setup(void){
  FastLED.addLeds<NEOPIXEL, 15>(leds, NUM_LEDS);
  webPage += "<h1>ESP8266 Web Server</h1><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });

  server.on("/health/0", [](){
    server.send(200, "text/html", webPage);
    clear_health();
  });

  server.on("/health/10", [](){
    server.send(200, "text/html", webPage);
    health_loop(1, 0, 224, 0);
  });

  server.on("/health/20", [](){
    server.send(200, "text/html", webPage);
    health_loop(2, 0, 224, 0);
  });

  server.on("/health/30", [](){
    server.send(200, "text/html", webPage);
    health_loop(3, 30, 224, 30);
  });
  server.on("/health/40", [](){
    server.send(200, "text/html", webPage);
    health_loop(4, 30, 224, 30);
  });  
  server.on("/health/50", [](){
    server.send(200, "text/html", webPage);
    health_loop(5, 60,224,60);
  });  
  server.on("/health/60", [](){
    server.send(200, "text/html", webPage);
    health_loop(6, 60,224,60);
  });  
  server.on("/health/70", [](){
    server.send(200, "text/html", webPage);
    health_loop(7, 60,224,60);
  });  
  server.on("/health/80", [](){
    server.send(200, "text/html", webPage);
    health_loop(8, 130,224,130);
  });
  server.on("/health/90", [](){
    server.send(200, "text/html", webPage);
    health_loop(9, 130,224,130);
  });
  server.on("/health/100", [](){
    server.send(200, "text/html", webPage);
    health_loop(10, 130,224,130);
  });

  server.on("/mana/0", [](){
    server.send(200, "text/html", webPage);
    clear_mana();
  });

  server.on("/mana/10", [](){
    server.send(200, "text/html", webPage);
    mana_loop(18,0,0,224);
  });

  server.on("/mana/20", [](){
    server.send(200, "text/html", webPage);
    mana_loop(17,0,0,224);
  });

  server.on("/mana/30", [](){
    server.send(200, "text/html", webPage);
    mana_loop(16,30,30,224);
  });
  server.on("/mana/40", [](){
    server.send(200, "text/html", webPage);
    mana_loop(15,30,30,224);
  });  
  server.on("/mana/50", [](){
    server.send(200, "text/html", webPage);
    mana_loop(14,70,70,224);
  });  
  server.on("/mana/60", [](){
    server.send(200, "text/html", webPage);
    mana_loop(13,70,70,224);
  });  
  server.on("/mana/70", [](){
    server.send(200, "text/html", webPage);
    mana_loop(12,70,70,224);
  });  
  server.on("/mana/80", [](){
    server.send(200, "text/html", webPage);
    mana_loop(11, 130,130,224);
  });
  server.on("/mana/90", [](){
    server.send(200, "text/html", webPage);
    mana_loop(10, 130,130,224);
  });
  server.on("/mana/100", [](){
    server.send(200, "text/html", webPage);
    mana_loop(9, 130,130,224);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void clear_health(){
  leds[0] = CRGB::Black;FastLED.show();
  leds[1] = CRGB::Black;FastLED.show();
  leds[2] = CRGB::Black;FastLED.show();
  leds[3] = CRGB::Black;FastLED.show();
  leds[4] = CRGB::Black;FastLED.show();
  leds[5] = CRGB::Black;FastLED.show();
  leds[6] = CRGB::Black;FastLED.show();
  leds[7] = CRGB::Black;FastLED.show();
  leds[8] = CRGB::Black;FastLED.show();
  leds[9] = CRGB::Black;FastLED.show();
}

void clear_mana(){
  leds[10] = CRGB::Black;FastLED.show();
  leds[11] = CRGB::Black;FastLED.show();
  leds[12] = CRGB::Black;FastLED.show();
  leds[13] = CRGB::Black;FastLED.show();
  leds[14] = CRGB::Black;FastLED.show();
  leds[15] = CRGB::Black;FastLED.show();
  leds[16] = CRGB::Black;FastLED.show();
  leds[17] = CRGB::Black;FastLED.show();
  leds[18] = CRGB::Black;FastLED.show();
  leds[19] = CRGB::Black;FastLED.show();
}
 
void loop(void){
  server.handleClient();
} 