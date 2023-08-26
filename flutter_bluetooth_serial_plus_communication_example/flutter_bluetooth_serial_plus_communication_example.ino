#include <SoftwareSerial.h>

#define RX_PIN_BLUETOOTH 10
#define TX_PIN_BLUETOOTH 11

SoftwareSerial hc06(RX_PIN_BLUETOOTH, TX_PIN_BLUETOOTH);

bool ledIsOn = false;

void setup() 
{
Serial.begin(9600);
hc06.begin(9600); 

pinMode(LED_BUILTIN, OUTPUT);

delay(1000);
}

String readReceivedText() {
  String text = "";
  char character;

  if (hc06.available()) {
   while(hc06.available()){
      character = hc06.read();
      
      if(character != '\n'){
         text += (character);  
      }

      delay(10); 
   }
  }

  return text;
}

void hc06Println (String text) {
    delay(10);
    hc06.println(text);
}

void loop()
{
  String received = readReceivedText();

  if (received.length() > 0) {
    Serial.println(received);

    String receivedLower = received;
    receivedLower.toLowerCase();
    receivedLower.trim();
    
    if(receivedLower == "led on") {
        if(ledIsOn) {
           hc06Println("Led has already on");
        } else {
          ledIsOn = true;
          digitalWrite(LED_BUILTIN, HIGH);
          hc06Println("Got it, turned on the led");
        }
    } else if(receivedLower == "led off") {
        if(!ledIsOn) {
           hc06Println("Led has already off");
        } else {
           ledIsOn = false;
           digitalWrite(LED_BUILTIN, LOW);
           hc06Println("Got it, turned off the led");
        }
    } else if(receivedLower == "led is on?") {
        if(ledIsOn) {
           hc06Println("Yes");
        } else {
          hc06Println("No");
        }
    } else {
       hc06Println("I, microcontroller, received your " + received + ", but i don't know how to deal with it");
    }
  }
}