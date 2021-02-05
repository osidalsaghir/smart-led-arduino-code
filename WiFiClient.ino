#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>


#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

//1. Change the following info
#define WIFI_SSID "ronki"
#define WIFI_PASSWORD "Ronak123+"
#define FIREBASE_HOST "arduinoled-bde68.firebaseio.com"
#define FIREBASE_AUTH "8n1RzbXTWyYd7ccds9ThxAm4Lt5ieHbY6iLdg3DR"

//2. Define FirebaseESP8266 data object for data sending and receiving
FirebaseData fbdo;
FirebaseJsonData jsonData;
FirebaseJson json;
int Led_Red = 16;
int Led_Green = 5;
int Led_Blue = 4;

void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //3. Set your Firebase info

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);

  //5. Try to set int data to Firebase
  //The set function returns bool for the status of operation
  //fbdo requires for sending the data


  //6. Try to get int data from Firebase
  //The get function returns bool for the status of operation
  //fbdo requires for receiving the data


  /*
    In case where you want to set other data types i.e. bool, float, double and String, you can use setBool, setFloat, setDouble and setString.
    If you want to get data which you known its type at specific node, use getInt, getBool, getFloat, getDouble, getString.
    If you don't know the data type at specific node, use get and check its type.
    The following shows how to get the variant data
  */
  pinMode(Led_Red, OUTPUT);
  pinMode(Led_Green, OUTPUT);
  pinMode(Led_Blue, OUTPUT);




}

void loop()
{


  if (Firebase.getInt(fbdo, "/ONOFF/isITOn"))
  {

    if (fbdo.intData() == 1) {
      if (Firebase.getBool(fbdo, "/moodORstatic/isItMood"))
      {
        Serial.println(fbdo.boolData());
        if (fbdo.boolData()) {

          mood();
          Serial.println("here mood");
        }
        else {
          staticColor();
          Serial.println("here static");
        }

      }


    }
    else {
      analogWrite (Led_Blue, 0);
      analogWrite (Led_Green, 0);
      analogWrite (Led_Red, 0);
    }
  }
  else {
    Serial.println("here");
  }


}

void mood()
{
  if (Firebase.getJSON(fbdo, "/moodOn"))  {
    //Success
    int blue1 , blue2 , blue3 , red1 , red2, red3, green1, green2, green3;

    json = fbdo.jsonObject();
    json.get(jsonData, "blue1");
    blue1 = jsonData.intValue;
    json.get(jsonData, "blue2");
    blue2 = jsonData.intValue;
    json.get(jsonData, "blue3");
    blue3 = jsonData.intValue;
    json.get(jsonData, "red1");
    red1 = jsonData.intValue;
    json.get(jsonData, "red2");
    red2 = jsonData.intValue;
    json.get(jsonData, "red3");
    red3 = jsonData.intValue;
    json.get(jsonData, "green1");
    green1 = jsonData.intValue;
    json.get(jsonData, "green2");
    green2 = jsonData.intValue;
    json.get(jsonData, "green3");
    green3 = jsonData.intValue;


    if (!isItOn) {
      return;
    }
    rgb_color(red1, green1, blue1);
    if (!isItOn) {
      return;
    }
    delay(900);
    rgb_color(red2, green2, blue2);
    if (!isItOn) {
      return;
    }
    delay(900);
    rgb_color(red3, green3, blue3);
    if (!isItOn) {
      return;
    }
    delay(900);

  } else {

  }


}

bool isItOn() {


  if (Firebase.getInt(fbdo, "/ONOFF/isITOn"))
  {

    if (fbdo.intData() == 1) {
      return true ;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }


}

void staticColor() {
  int red = 0 ;
  int green = 0 ;
  int blue = 0 ;

  if (isItOn() && Firebase.getInt(fbdo, "/rgb/Blue"))
  {



    blue = fbdo.intData();


  } else {

    return ;

  }

  if (isItOn() && Firebase.getInt(fbdo, "/rgb/Green") )
  {

    green = fbdo.intData();

  } else {

    return ;

  }

  if (isItOn() && Firebase.getInt(fbdo, "/rgb/Red"))
  {


    red = fbdo.intData();

  } else {

    return ;

  }

  rgb_color(red, green, blue);


}


void rgb_color(int red , int green , int blue) {

  analogWrite (Led_Red, red);
  analogWrite (Led_Green, green);
  analogWrite (Led_Blue, blue);


}
