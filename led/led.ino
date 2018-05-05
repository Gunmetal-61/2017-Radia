#include "FastLED.h"
#include "TimeLib.h"

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

CRGB leds[1];
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  6;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() 
 {
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, ledPin>(leds, 1);

  setSyncProvider(requestSync);
  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  Serial.print("Time: "); 
  Serial.print(hour()); 
  Serial.print(":"); 
  Serial.print(minute()); 
  Serial.print(":"); 
  Serial.println(second());
  //Serial.println(buttonState);
  if (digitalRead(buttonPin) == LOW) 
  {
    if (buttonState == 0)
    {
      buttonState = 1;
    }
    else
    {
      buttonState = 0;
    }
  }

  if (buttonState == 0)
  {
    leds[0] = CRGB::Black; FastLED.show();
  }
  
  if (buttonState == 1)
  {
    switch (second() % 2) 
    {
      case 0:
        leds[0] = CRGB::Red; FastLED.show(); 
        break;
      case 1:
        leds[0] = CRGB::Black; FastLED.show();
        break;
    }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}
