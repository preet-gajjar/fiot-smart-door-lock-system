#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Replace with your WiFi credentials
const char* ssid = "iQOO Neo6";        // Your WiFi SSID
const char* password = "ma6ibxixfes44ye"; // Your WiFi Password

// Telegram Bot Token and Chat ID
const char* botToken = "7591470761:AAFNEMsjsm7vV92AIZa2vTc0k7zIuCWCl8I"; // Replace with your Telegram Bot Token
const char* chatID = "5696211760"; // Replace with your Telegram Chat ID

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // Test Telegram message
  String testMessage = "Hello! This is a test message from NodeMCU.";
  sendTelegramMessage(testMessage);
}

void loop() {
  // Nothing in the loop for this test
}

// Function to send Telegram message
void sendTelegramMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    client.setInsecure(); // Skip SSL certificate validation
    String url = "https://api.telegram.org/bot" + String(botToken) + "/sendMessage?chat_id=" + String(chatID) + "&text=" + message;

    if (client.connect("api.telegram.org", 443)) {
      Serial.println("Connected to Telegram server");
      client.println("GET " + url + " HTTP/1.1");
      client.println("Host: api.telegram.org");
      client.println("Connection: close");
      client.println();

      // Wait for response
      while (client.connected() || client.available()) {
        if (client.available()) {
          String line = client.readStringUntil('\n');
          Serial.println(line); // Print response from Telegram
        }
      }
      client.stop();
      Serial.println("Message sent!");
    } else {
      Serial.println("Connection to Telegram failed.");
    }
  } else {
    Serial.println("WiFi not connected.");
  }
}
