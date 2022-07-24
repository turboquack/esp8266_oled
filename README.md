# Crypto ticker
Crypto ticker using ESP8266 and 1.3" OLED 1,3.
![alt text](https://github.com/turboquack/esp8266_oled/blob/main/pictures/ticker.PNG)<br>
This ticker displays crypto, their price and price change. Data comes using CoinMarketCap API.
# Hardware
1.3" OLED Display I2C SSH1106 Chip 128 x 64 Pixel<br>
D1 Mini V3 NodeMCU ESP8266EX<br>
![alt text](https://github.com/turboquack/esp8266_oled/blob/main/pictures/wiring.PNG)<br>
# Software
Libraries used<br>
[ESP8266WiFi](https://github.com/esp8266/Arduino)<br>
[ESP8266HTTPClient](https://github.com/esp8266/Arduino)<br>
[WiFiClient](https://github.com/esp8266/Arduino)<br>
[ArduinoJson](https://arduinojson.org/)<br>
[WiFiUdp](https://github.com/esp8266/Arduino)<br>
[U8g2lib](https://www.arduino.cc/reference/en/libraries/u8g2/)<br>
[Wire](https://www.arduino.cc/reference/en/language/functions/communication/wire/)<br>
[CoinMarketCap Api Documentation](https://coinmarketcap.com/api/documentation/v1/)<br>
# Usage
Insert your WiFi name and password, crypto coins, api key and fingerprint for host. You can change if you want to display different price change(```percent_change_7d/percent_change_30d/percent_change_60d```) or different data(market cap/supply/etc). For different data you will have to specify that in ```grab_parse_data()``` function.<br>
For more info check documentation of [Coinmarketcap API](https://coinmarketcap.com/api/documentation/v1/) and [ArduinoJson](https://arduinojson.org/)<br>
