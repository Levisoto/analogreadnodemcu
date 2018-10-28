#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


// Set these to run example.
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

const double SensorValueLow = 330; 
const double SensorValueDiff = 14; // differance between high and low sensor value
const double TempValueDiff = 17.40; // differance between high and low Temp value
const double TempValueLow = 5;
double sensorValue;
int contador1;
int contador2;
double Temp;

double data = 200;
double vol;
int itemp;
int frac;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
     delay(400);
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  itemp = 0;
  frac = 0;
}


void loop() {
  // put your main code here, to run repeatedly:
  while(itemp <= 50){
    sensorValue=analogRead(A0);
    Temp = convertTemp(sensorValue);
    vol = data*sin(10*frac*3.14159/180);
    frac++;  
    Serial.println(vol);
    Serial.println(Temp);
    Firebase.setFloat("/TempReport/"+String(itemp),vol);
    Firebase.setFloat("/Tempadc/"+String(itemp),Temp);
    delay(200);
    itemp++;
    }
  itemp = 0;
}

double convertTemp(float sensorValue){
  Temp = sensorValue-SensorValueLow;
  Temp = Temp/SensorValueDiff;
  Temp = Temp*TempValueDiff;
  Temp = (Temp+TempValueLow);
  Temp =3*Temp/5;

  return Temp;
  }
