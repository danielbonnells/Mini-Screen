#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
// #include "localWifi.h"
#include "getFeed.h"
#include <WiFiManager.h>
#include <ArduinoJson.h>

char const *WIFI_AP_NAME = "MTA";

#define SCREEN_WIDTH 128                // OLED display width, in pixels
#define SCREEN_HEIGHT 64                // OLED display height, in pixels
int16_t scrollPosition = SCREEN_HEIGHT; // Initial scroll position
int16_t linesToScroll = 8;              // Lines to scroll upwards
int16_t pixelsToScroll = 8;             // Lines to scroll upwards
int textSizeOled = 2;

// const char *response = nullptr;
const char *responseAlerts = nullptr;
int mainDisplayIndex = 0;

JsonDocument doc;
JsonArray mainDisplayTextArray;


#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// LED MATRIX MAX7219
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 32              // Chip select pin
#define LED_MATRIX_INTENSITY 5 // set the brightness of the LED matrix display (from 0 to 15)

MD_Parola ledMatrix = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void calculateLinesToScrollVertically(String text)
{

  // Calculate the height of each character (assuming font size 1)
  int characterWidth = 6 * textSizeOled;
  int characterHeight = 8 * textSizeOled;
  int maxCharsPerLine = SCREEN_WIDTH / characterWidth;

  // Calculate the total height needed to display the text
  linesToScroll = (text.length() / maxCharsPerLine) + 1;
  pixelsToScroll = (linesToScroll * characterHeight) + SCREEN_HEIGHT;
}

void updateOled(const char *text)
{ // Serial.println("Entering updateOled function");
  if (text != nullptr)
  {
    // Serial.print("OLED Text: ");
    Serial.println(text);
    calculateLinesToScrollVertically(text);
    display.clearDisplay(); // Clear the display buffer
    display.setCursor(0, scrollPosition);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(textSizeOled);
    display.print(text);
    display.display(); // Show text
    scrollPosition = (scrollPosition <= -pixelsToScroll) ? SCREEN_HEIGHT : scrollPosition - 1;
  }
  else
  {
    Serial.println("OLED Text is null");
  }
}

void updateLED(const char *text)
{

  if (text != nullptr)
  {
    ledMatrix.displayClear(); // clear led matrix display
    ledMatrix.displayScroll(text, PA_CENTER, PA_SCROLL_LEFT, 100);
  }
  else
  {
    Serial.println("LED Text is null");
  }
}

const char *getContent(const char *endpoint, String routeId, String stopId)
{
  const char *response = httpGETRequest(endpoint, routeId, stopId);
  return response;
}

const long interval = 60000;     // Interval in milliseconds (60 seconds)
long previousMillis = -interval; // Variable to store the previous time the HTTP call was made. Opposite the interval to have the first api call made right away.

bool start(JsonDocument &doc)
{
  unsigned long currentMillis = millis(); // Get the current time

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis; // Update the previous time
    const char *response = getContent("ESP32", "Grand%20Central-42%20St", "BOTH");

    DeserializationError error = deserializeJson(doc, response);

    // Test if parsing succeeds.
    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    }

    // // reset the index and populate array
    // mainDisplayIndex = 0;
    // mainDisplayTextArray = doc["mainDisplayText"].as<JsonArray>();
    // document.clear();
    // document.add(mainDisplayTextArray);
    // Serial.println(mainDisplayTextArray[0].as<const char*>());

    // if (!mainDisplayTextArray.isNull())
    // {
    //   Serial.println("Inside - Main Display Text array found");
    // }
    // else
    // {
    //   Serial.println("Inside - Main Display Text array is null");
    // }

    // responseAlerts = doc["secondaryDisplayText"][0][0].as<const char *>(); // Get the first item from the nested array
    return true; // Indicate success
  }

  return false;

  // updateOled(responseAlerts);
}

void setup()
{
  Serial.begin(115200);

  // SSD1306 OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // WIFI
  // connectWifi();
  /// api/ESP32?stopName=Grand Central-42 St&direction=BOTH

  // MAX7219 setup
  ledMatrix.begin(); // initialize the object
  ledMatrix.setIntensity(LED_MATRIX_INTENSITY);
  ledMatrix.displayClear(); // clear led matrix display
  ledMatrix.displayScroll("Starting up...", PA_CENTER, PA_SCROLL_LEFT, 25);

  display.clearDisplay(); // Clear the display buffer
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.print("Connect to wifi named 'MTA' and configure.");
  display.display(); // Show text

  WiFiManager wm;

  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
  // wm.resetSettings();

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
  // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
  // then goes into a blocking loop awaiting configuration and will return success result

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect(WIFI_AP_NAME); // password is optional second param

  if (!res)
  {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else
  {
    // if you get here you have connected to the WiFi
    display.clearDisplay(); // Clear the display buffer
    display.setCursor(0, 0);
    display.print("Connected!");
    display.display(); // Show text
  }
}

void loop()
{

  if (start(doc)) //&& ledMatrix.displayAnimate()
  {
    mainDisplayTextArray = doc["mainDisplayText"].as<JsonArray>();
  }

  if (ledMatrix.displayAnimate())
  {

    Serial.println(mainDisplayIndex);
    Serial.println(mainDisplayTextArray.size());
    if (true)//mainDisplayTextArray.size() != 0 && mainDisplayIndex < mainDisplayTextArray.size()
    {
      const char *text = mainDisplayTextArray[mainDisplayIndex].as<const char *>();
      Serial.println(text);
      if (text != nullptr)
      {
        ledMatrix.displayScroll(text, PA_CENTER, PA_SCROLL_LEFT, 25);
        mainDisplayIndex++; //

      }
    }
    else
    {
      mainDisplayIndex = 0;
    }
  }
}
