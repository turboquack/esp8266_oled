#pragma once

DynamicJsonDocument grab_parse_data() {

  //JSON FILTER OUT UNWANTED DATA
  //StaticJsonDocument<192> filter;
  StaticJsonDocument<256> filter;
  filter["status"]["timestamp"] = true;
  JsonObject filter_data_0 = filter["data"].createNestedObject();
  filter_data_0["name"] = true;
  filter_data_0["symbol"] = true;
  JsonObject filter_data_0_quote_USD = filter_data_0["quote"].createNestedObject("USD");
  filter_data_0_quote_USD["price"] = true;
  filter_data_0_quote_USD["percent_change_1h"] = true;
  filter_data_0_quote_USD["percent_change_24h"] = true;
  filter_data_0_quote_USD["percent_change_7d"] = true;
  filter_data_0_quote_USD["percent_change_30d"] = true;
  filter_data_0_quote_USD["percent_change_60d"] = true;
  DynamicJsonDocument doc(4096);
  //JSON FILTER OUT UNWATED DATA

  HTTPClient http;
  WiFiClientSecure client;
  
  client.setFingerprint(fingerprint);
  //client.setInsecure();    // Delete comment and comment setFingerprint if dont want to use HTTPS
  client.setTimeout(15000); // 15 Seconds
  client.connect(host, httpsPort);

  http.begin(client, host);
  http.useHTTP10(true);
  http.addHeader("X-CMC_PRO_API_KEY", api_key);
  // Send HTTP GET request
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) 
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    yield();
    DeserializationError error = deserializeJson(doc, http.getStream(), DeserializationOption::Filter(filter));
    if (error) 
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      exit;
    }
    
    client.stop();
    http.end();
  }
  else 
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    u8g2.drawStr( 10,line_1_y, "ERROR");
    u8g2.drawStr(10,line_2_y,String(httpResponseCode).c_str());
    u8g2.sendBuffer();
    delay(1800000);
  }
  return doc;
}
