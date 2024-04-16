//Complete project details: https://RandomNerdTutorials.com/esp32-https-requests/

#include "localWifi.h"
#include <WiFi.h>
//#include "drawDisplay.h"

void connectWifi() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  delay(100);

  WiFi.begin(SECRET_SSID, SECRET_PASS);
  
  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
   //  oledDrawText("Attempting to connect to Wifi.");
    // wait 1 second for re-trying
    delay(1000);
  }
  //oldedDisplayClear();

 // oledDrawText("Connected to Wifi.");

}


