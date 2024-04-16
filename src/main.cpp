#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
// #include "localWifi.h"
#include "getFeed.h"
#include <WiFiManager.h>

char const* WIFI_AP_NAME = "MTA";

#define SCREEN_WIDTH 128                // OLED display width, in pixels
#define SCREEN_HEIGHT 64                // OLED display height, in pixels
int16_t scrollPosition = SCREEN_HEIGHT; // Initial scroll position
int16_t linesToScroll = 8;              // Lines to scroll upwards
int16_t pixelsToScroll = 8;             // Lines to scroll upwards
int textSizeOled = 2;

const char *response = nullptr;
const char *responseAlerts = nullptr;

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
{

  calculateLinesToScrollVertically(text);

  // Scroll text vertically upwards on OLED display
  display.clearDisplay(); // Clear the display buffer
  display.setCursor(0, scrollPosition);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(textSizeOled);
  display.print(text);
  display.display(); // Show text

  // Reset scroll position
  scrollPosition = (scrollPosition <= -pixelsToScroll) ? SCREEN_HEIGHT : scrollPosition - 1;
}

void updateLED(const char *text)
{

  ledMatrix.displayClear(); // clear led matrix display
  ledMatrix.displayScroll(text, PA_CENTER, PA_SCROLL_LEFT, 100);
}

const char *getContent(const char *endpoint, String routeId, String stopId)
{
  const char *response = httpGETRequest(endpoint, routeId, stopId);
  return response;
}

const long interval = 45000;     // Interval in milliseconds (45 seconds)
long previousMillis = -interval; // Variable to store the previous time the HTTP call was made. Opposite the interval to have the first api call made right away.

void start()
{
  unsigned long currentMillis = millis(); // Get the current time

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis; // Update the previous time
    response = getContent("Stop/", "A", "A41S");
    responseAlerts = getContent("Alerts/", "A", "A41S");
    updateLED(response);
  }

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis; // Update the previous time
    responseAlerts = getContent("Alerts/", "A", "A41S");
  }

  updateOled(responseAlerts);
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

  // MAX7219 setup
  ledMatrix.begin(); // initialize the object
  ledMatrix.setIntensity(LED_MATRIX_INTENSITY);
  ledMatrix.displayClear(); // clear led matrix display
  ledMatrix.displayScroll("Starting up...", PA_CENTER, PA_SCROLL_LEFT, 100);

  display.clearDisplay(); // Clear the display buffer
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.print("Connect to wifi named 'MTA' and configure.");
  display.display(); // Show text

  WiFiManager wm;

  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
  //wm.resetSettings();

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

  start();

  // Update LED matrix display animation
  if (ledMatrix.displayAnimate())
  {
    ledMatrix.displayReset();
  }
}
