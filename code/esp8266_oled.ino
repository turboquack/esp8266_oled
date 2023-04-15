#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <WiFiUdp.h>
#include <U8g2lib.h>
#include <Wire.h>

//WIFI
char* ssid = "SSID NAME HERE";
char* password = "PWD HERE";
//WIFI

//COINS
const char *coins[4] = { "Bitcoin", "Ethereum", "Litecoin", "Cardano"}; //COINS TO LIST
int number_of_coins = sizeof(coins)/sizeof(coins[0]);
unsigned long interval=1800000; //30 min update
//COINS

//COINMARKETCAP HOST & API
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
const char* host = "https://pro-api.coinmarketcap.com/v1/cryptocurrency/listings/latest?start=1&limit=20&convert=USD";
const char* api_key = "YOU API KEY HERE";
const char* fingerprint = "FINGERPRINT HERE";
//COINMARKETCAP HOST & API

//OLED
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE); //Version of I2C controller on OLED
//OLED

#include "draw_coin.h"
#include "grab_and_parse_data.h"

void setup(void) 
{
  Serial.begin(115200); 
  
  WiFi.begin(ssid, password);
 
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2_prepare();

  u8g2.drawStr( 10, line_1_y, "Connecting to");
  u8g2.drawStr(10 , line_2_y , ssid);
  u8g2.sendBuffer();
  Serial.println("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  u8g2.clearBuffer();
  u8g2.sendBuffer();

}


void loop(void) {
  unsigned long start, finished, elapsed_time=0;
  Serial.println("Start...");
  start=millis();
  
  DynamicJsonDocument doc(4096);
  doc=grab_parse_data();//Grab data from Coinmarketcap

  while(elapsed_time<interval)//WORK FOR 30MIN
  {
    for (JsonObject data_item : doc["data"].as<JsonArray>()) 
    {
      const char* data_item_name = data_item["name"]; // "Bitcoin", "Ethereum", "Binance Coin", ...
      const char* data_item_symbol = data_item["symbol"]; // "BTC", "ETH", "BNB", "USDT", "ADA", ...
      JsonObject data_item_quote_USD = data_item["quote"]["USD"];
      double data_item_quote_USD_price = data_item_quote_USD["price"]; // 44969.36841633352, ...
      double data_item_quote_USD_percent_change_1h = data_item_quote_USD["percent_change_1h"]; // -0.27608487, ...
      double data_item_quote_USD_percent_change_24h = data_item_quote_USD["percent_change_24h"];// -0.2754545, ....
      double data_item_quote_USD_percent_change_7d = data_item_quote_USD["percent_change_7d"]; // -1.67418409, ...
      double data_item_quote_USD_percent_change_30d = data_item_quote_USD["percent_change_30d"]; // -1.67418409, ...
      double data_item_quote_USD_percent_change_60d = data_item_quote_USD["percent_change_60d"]; // -1.67418409, ...
      for (int i=0; i<sizeof(coins)/sizeof(coins[0]); i++)
      {
        if (strcmp(data_item_name,coins[i])==0)
          {
            Serial.println(data_item_name);
            Serial.print("Price USD ");
            Serial.println(data_item_quote_USD_price);
            Serial.print(" % change 1h ");
            Serial.println(data_item_quote_USD_percent_change_1h);
            Serial.print(" % change 24h ");
            Serial.println(data_item_quote_USD_percent_change_24h);
            Serial.print(" % change 7d ");
            Serial.println(data_item_quote_USD_percent_change_7d);
            Serial.print(" % change 30d ");
            Serial.println(data_item_quote_USD_percent_change_30d);
            Serial.print(" % change 60d ");
            Serial.println(data_item_quote_USD_percent_change_60d);
            show_coin(coins[i],data_item_quote_USD_price,"Change 1h ",data_item_quote_USD_percent_change_1h,"Change 24h ",data_item_quote_USD_percent_change_24h); //change if want to display something else
            Serial.println("==============");
        }
      }
    }
    finished=millis();
    elapsed_time=finished-start;
  }
}
