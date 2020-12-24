
#include <ESP8266WiFi.h>
/* 依赖 C 2.4.0 */
#include <PubSubClient.h>
/* 依赖 ArduinoJson 5.13.4 */
#include <ArduinoJson.h>
#include <Arduino.h>
#include "LedController.hpp"
#include <string>

#include "DHT.h"

// #define SENSOR_PIN    LED_BUILTIN
 
// /* 修改1 ------------------------------------------ */
// /* 连接您的WIFI SSID和密码 */
// #define WIFI_SSID         "Xiaomi_C744"
// #define WIFI_PASSWD       "Aa1234567890"
// // #define WIFI_SSID         "ChinaNet-pvXM"
// // #define WIFI_PASSWD       "rruysn4z"

// /* 修改1 end--------------------------------------- */
 
// /* 修改2 ------------------------------------------ */
// //   "ProductKey": "a1Uilh2dXmk",
// //   "DeviceName": "4KSXMBHG24Ldx86n3FGu",
// //   "DeviceSecret": "b8fda2de2765852812a1629190707701"
// /* 设备证书信息*/

// // #define PRODUCT_KEY       "a1Uilh2dXmk"
// // #define DEVICE_NAME       "97PKdrnsJBihtBJXsK6o"
// // #define DEVICE_SECRET     "84de41335e5f6371a9a06671cbf6edf7"
// // #define MQTT_PASSWD       "0BB1C415FC58283E0AB2A1068DAF9DDB8479A4B8"

// #define PRODUCT_KEY       "a1Uilh2dXmk"
// #define DEVICE_NAME       "4KSXMBHG24Ldx86n3FGu"
// #define DEVICE_SECRET     "84de41335e5f6371a9a06671cbf6edf7"
// #define MQTT_PASSWD       "241317E7793F08DD94CF10944F8610EA28B00DB6"

// #define REGION_ID         "cn-shanghai"
// #define MQTT_SERVER       PRODUCT_KEY ".iot-as-mqtt." REGION_ID ".aliyuncs.com"
// #define MQTT_PORT         1883
// #define MQTT_USRNAME      DEVICE_NAME "&" PRODUCT_KEY
// #define CLIENT_ID         "esp8266|securemode=3,signmethod=hmacsha1,timestamp=123456789|"
 
// #define ALINK_BODY_FORMAT         "{\"id\":\"123\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"
// #define ALINK_TOPIC_PROP_POST     "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post"

// #define DHTPIN 5 
// #define DHTTYPE DHT11

// DHT dht(DHTPIN, DHTTYPE);

// unsigned long lastMs = 0;
// WiFiClient espClient;
// PubSubClient  client(espClient);

// int temp=0;
// char Temperature[16]="Temperature:  ";

// void mqttPostLightSta(bool sta){
//     char param[32];
//     char jsonBuf[128];

//     Serial.print("mqttPost ");

//     sprintf(param, "{\"LightSwitch\":%d}", sta);

//     sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
//     Serial.println(jsonBuf);
//     boolean d = client.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
//     Serial.print("publishe ret:");
//     Serial.println(d);
// }

// void callback(char *topic, byte *payload, unsigned int length)//网络反馈数据
// {
//     Serial.print("callback    ");
//     Serial.print("Message arrived [");
//     Serial.print(topic);
//     Serial.print("] ");
//     payload[length] = '\0';
//     Serial.println((char *)payload);
//     std::string message = (char *)payload;
//     std::string::size_type position;

//     position = message.find("LightSwitch");
//     if (position != message.npos){
//         if(payload[position+13] == '1'){
//             Serial.println("Light:close");
//             mqttPostLightSta(true);
//             digitalWrite(SENSOR_PIN,LOW);
//         }else if(payload[position+13] == '0'){
//             Serial.println("Light:on");
//             mqttPostLightSta(false);
//             digitalWrite(SENSOR_PIN,HIGH);
//         }
//     }
// }

// void wifiInit()
// {
//     Serial.print("wifiInit    ");
//     WiFi.mode(WIFI_STA);
//     WiFi.begin(WIFI_SSID, WIFI_PASSWD);
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(1000);
//         Serial.println("WiFi not Connect");
//     }
 
//     Serial.println("Connected to AP");
//     Serial.println("IP address: ");
//     Serial.println(WiFi.localIP());
 
//     Serial.print("espClient [");
//     client.setServer(MQTT_SERVER, MQTT_PORT);   /* 连接WiFi之后，连接MQTT服务器 */
//     client.setCallback(callback);
// }
 
 
// void mqttCheckConnect()
// {
//     Serial.println("mqttCheckConnect    ");
//     while (!client.connected())
//     {
//         Serial.println("Connecting to MQTT Server ...");
//         if (client.connect(CLIENT_ID, MQTT_USRNAME, MQTT_PASSWD)){
//             Serial.println("MQTT Connected!");
//         }else{
//             Serial.print("MQTT Connect err:");
//             Serial.println(client.state());
//             delay(5000);
//         }
//     }
// }

// void mqttIntervalPost2()
// {
//     char param[32];
//     char jsonBuf[128];
//     // Serial.print("mqttIntervalPost2   ");

//     // float h = dht.readHumidity();
//     // float t = dht.readTemperature();
//     // if (isnan(h) || isnan(t)) {
//     //     Serial.println(F("Failed to read from DHT sensor!"));
//     // }else{
//     //     sprintf(param, "{\"Temperature\":%f, \"Humidity\":%d}", t, (int)h);
//     //     sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
//     //     Serial.println(jsonBuf);
//     //     boolean d = client.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
//     //     Serial.print("published:");
//     //     Serial.println(d);
//     // }
//     sprintf(param, "{\"Temperature\":%f, \"Humidity\":%d}", random(0, 40), (int)random(0, 40));
//     sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
//     Serial.println(jsonBuf);
//     boolean d = client.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
//     Serial.print("published:");
//     Serial.println(d);
// } 

// void setup() 
// {
//     pinMode(SENSOR_PIN,  OUTPUT);
//     /* initialize serial for debugging */
//     Serial.begin(115200);
//     Serial.println("Demo Start");
//     randomSeed(analogRead(0));
 
//     wifiInit();
//     dht.begin();
// }

// // the loop function runs over and over again forever
// void loop()
// {
//     if (millis() - lastMs >= 500)
//     {
//         lastMs = millis();
//         mqttCheckConnect(); 
 
//         // mqttIntervalPost2();//温度数据
//     }
 
//     client.loop(); 
// }


/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedController lc;


void displayInt(int n){
    int t=n;
    int c=0;

    while(t/10){
        c++;
        t = t/10;
    }

    if(c > 7){
        t = n;
        for(int i=7; i>=0; i--){
            lc.setDigit(0, i, t%10, false);
            t = t/10;
        }
    }else{
        t = n;
        for(int i=c; i>=0; i--){
            lc.setDigit(0, i, t%10, false);
            t = t/10;
        }
    }
}


/* we always wait a bit between updates of the display */
unsigned long delaytime=250;

void setup() {

  lc=LedController(14, 4, 12, 1);

  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.activateAllSegments();
  /* Set the brightness to a medium values */
  lc.setIntensity(8);
  /* and clear the display */
  lc.clearMatrix();
}

void loop() { 
    for(int i=0; i<1000; i++){
        displayInt(i);
        delay(200);
        lc.clearMatrix();
    }
    
}


