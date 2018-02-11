
#define CUSTOM_SETTINGS
#define INCLUDE_EMAIL_SHIELD
#define INCLUDE_PUSH_BUTTON_SHIELD
#define INCLUDE_GPS_SHIELD 
#define INCLUDE_TEXT_TO_SPEECH_SHIELD
#define trigPin 13
#define echoPin 12
float lat;
float lon;
char latitude[15];
char longitude[10];
String Message;
String Message1;
String Message2;


#include <OneSheeld.h> //onesheeld package declared
long duration, distance;
boolean isInRange = false;
void setup() 
{
 
  OneSheeld.begin();
 
  PushButton.setOnButtonStatusChange(&onButtonStatusChanged);
   pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
 digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
   if(distance>=70)
   {
    Serial.print(distance);
    Serial.println(" cm");
    TextToSpeech.say("safe to move");
    delay(1000);
    }
    else
    {
      Serial.print(distance);
    Serial.println(" cm");
      TextToSpeech.say("stop");
      delay(1000);
      }
   delay(1000);     
}


void onButtonStatusChanged(bool isPressed)
{
  
  if(isPressed)
  {   lat = GPS.getLatitude();
      lon = GPS.getLongitude();
      Message1 = String(lat,8);
      Message2 = String(lon,8);
      
      
     
      Message = "I need Help! I'm at latitude: " + Message1 + " and longitude: " + Message2;
      Message = "Google Maps - https://www.google.co.in/maps/place/" + Message1 + "," + Message2;
      
      
      
      delay(3000);
      Email.send("mahes0424@gmail.com","im in trouble!","my latitude:"+Message+" longitude:"+Message+"");
  }
}
