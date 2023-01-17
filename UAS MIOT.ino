#include "DHTesp.h"
4.  #include <WiFi.h>
5.  #include "ThingSpeak.h"
6.  #include <Adafruit_Sensor.h>
7.  
8.  const int DHT_PIN = 12;
9.  const char* ssid = "Wokwi-GUEST";
10. const char* pass = "";
11. #define relay 18
12. 
13. WiFiClient client;
14. 
15. unsigned long myChannelNumber = 0;
16. const char* myWriteAPIKey = "WZ7AZQUVGIHUATLY";
17. const char* server = "api.thingspeak.com";
18. 
19. unsigned long lastTime = 0;
20. unsigned long timerDelay = 20000;
21. 
22. float temp;
23. float humi;
24. float dingin,sedang,panas;
25. 
26. DHTesp DHTSensor;
27. 
28. void setup() {
29.   Serial.begin(115200);
30.   pinMode(relay, OUTPUT);
31.   DHTSensor.setup(DHT_PIN, DHTesp::DHT22);
32.   DHTSensor.getPin();
33.   delay(10);
34.   WiFi.begin(ssid, pass);
35.   while(WiFi.status() != WL_CONNECTED){
36.     delay(100);
37.     Serial.println(".");
38.   }
39.   Serial.println("WiFi Connected!");
40.   Serial.println(WiFi.localIP());
41. 
42.   WiFi.mode(WIFI_STA);
43. 
44.   ThingSpeak.begin(client);
45. }
46. 
47. void loop() {
48.   temp = DHTSensor.getTemperature();
49.   Serial.print("Suhu (°C): ");
50.   Serial.println(temp);
51.   humi = DHTSensor.getHumidity();
52.   Serial.print("Kelembaban (%): ");
53.   Serial.println(humi);
54. 
55.   ThingSpeak.setField(1, temp);
56.   ThingSpeak.setField(2, humi);
57.   if(temp <= 20 ){
58.     Serial.println("Suhu Dingin");
59.     digitalWrite(relay, LOW);
60.     Serial.println("Relay OFF");
61.   }
62.   else if (temp <= 40){
63.     Serial.println("Suhu Sedang");
64.     digitalWrite(relay, HIGH);
65.     Serial.println("Relay On");
66.   }
67.   else if (temp <= 80){
68.     Serial.println("Suhu Panas");
69.     digitalWrite(relay, HIGH);
70.     Serial.println("Relay On");
71.   }
72.   // else{digitalWrite(relay, LOW);
73.   // Serial.println("Relay OFF");
74.   // }
75. 
76.   int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
77.   if (x == 200) {
78.     Serial.println("channel update Sukses.");
79.   }
80.   else {
81.     Serial.println("Masalah Updating cannel. HTTP error code" + String(x));
82.   }
83.   
84. }
