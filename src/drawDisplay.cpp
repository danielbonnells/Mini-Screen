// #include "drawDisplay.h"

// #define DEMO_DURATION 3000
// typedef void (*Demo)(void);

// int demoMode = 0;
// int counter = 1;

// // Initialize the OLED display using Arduino Wire:
// SSD1306Wire oledDisplay(0x3c, SDA, SCL);   // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h e.g. https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h

// void oldedDisplayClear(){
//   // clear the display
//   oledDisplay.clear();
// }
// void oledDisplayInit(){
//       // Initialising the UI will init the display too.
//   oledDisplay.init();

//   oledDisplay.flipScreenVertically();
//   oledDisplay.setFont(ArialMT_Plain_10);

// }
// void oledDisplayShow(){
//   oledDisplay.setFont(ArialMT_Plain_10);
//   oledDisplay.setTextAlignment(TEXT_ALIGN_RIGHT);
//   oledDisplay.drawString(128, 54, String(millis()));
//   // write the buffer to the display
//   oledDisplay.display();
// }
// // void drawFontFaceDemo() {
// //   // Font Demo1
// //   // create more fonts at http://oleddisplay.squix.ch/
// //   oledDisplay.setTextAlignment(TEXT_ALIGN_LEFT);
// //   oledDisplay.setFont(ArialMT_Plain_10);
// //   oledDisplay.drawString(0, 0, "Hello world");
// //   oledDisplay.setFont(ArialMT_Plain_16);
// //   oledDisplay.drawString(0, 10, "Hello world");
// //   oledDisplay.setFont(ArialMT_Plain_24);
// //   oledDisplay.drawString(0, 26, "Hello world");
// // }

// // void drawTextFlowDemo() {
// //   oledDisplay.setFont(ArialMT_Plain_10);
// //   oledDisplay.setTextAlignment(TEXT_ALIGN_LEFT);
// //   oledDisplay.drawStringMaxWidth(0, 0, 128,
// //                              "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
// // }

// // void drawTextAlignmentDemo() {
// //   // Text alignment demo
// //   oledDisplay.setFont(ArialMT_Plain_10);

// //   // The coordinates define the left starting point of the text
// //   oledDisplay.setTextAlignment(TEXT_ALIGN_LEFT);
// //   oledDisplay.drawString(0, 10, "Left aligned (0,10)");

// //   // The coordinates define the center of the text
// //   oledDisplay.setTextAlignment(TEXT_ALIGN_CENTER);
// //   oledDisplay.drawString(64, 22, "Center aligned (64,22)");

// //   // The coordinates define the right end of the text
// //   oledDisplay.setTextAlignment(TEXT_ALIGN_RIGHT);
// //   oledDisplay.drawString(128, 33, "Right aligned (128,33)");
// // }

// // void drawRectDemo() {
// //   // Draw a pixel at given position
// //   for (int i = 0; i < 10; i++) {
// //     oledDisplay.setPixel(i, i);
// //     oledDisplay.setPixel(10 - i, i);
// //   }
// //   oledDisplay.drawRect(12, 12, 20, 20);

// //   // Fill the rectangle
// //   oledDisplay.fillRect(14, 14, 17, 17);

// //   // Draw a line horizontally
// //   oledDisplay.drawHorizontalLine(0, 40, 20);

// //   // Draw a line horizontally
// //   oledDisplay.drawVerticalLine(40, 0, 20);
// // }

// // void drawCircleDemo() {
// //   for (int i = 1; i < 8; i++) {
// //     oledDisplay.setColor(WHITE);
// //     oledDisplay.drawCircle(32, 32, i * 3);
// //     if (i % 2 == 0) {
// //       oledDisplay.setColor(BLACK);
// //     }
// //     oledDisplay.fillCircle(96, 32, 32 - i * 3);
// //   }
// // }

// // void drawProgressBarDemo() {
// //   int progress = (counter / 5) % 100;
// //   // draw the progress bar
// //   oledDisplay.drawProgressBar(0, 32, 120, 10, progress);

// //   // draw the percentage as String
// //   oledDisplay.setTextAlignment(TEXT_ALIGN_CENTER);
// //   oledDisplay.drawString(64, 15, String(progress) + "%");
// // }

// // // void drawImageDemo() {
// // //   // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
// // //   // on how to create xbm files
// // //   display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
// // // }


// // Demo demos[] = {drawFontFaceDemo, drawTextFlowDemo, drawTextAlignmentDemo, drawRectDemo, drawCircleDemo, drawProgressBarDemo};
// // int demoLength = (sizeof(demos) / sizeof(Demo));
// // long timeSinceLastModeSwitch = 0;

// // void oledDisplayDemo(){
// //  oldedDisplayClear();
// //       // draw the current demo method
// //   demos[demoMode]();

// //   oledDisplay.setFont(ArialMT_Plain_10);
// //   oledDisplay.setTextAlignment(TEXT_ALIGN_RIGHT);
// //   oledDisplay.drawString(128, 54, String(millis()));
// //   // write the buffer to the display
// //   oledDisplay.display();

// //   if (millis() - timeSinceLastModeSwitch > DEMO_DURATION) {
// //     demoMode = (demoMode + 1)  % demoLength;
// //     timeSinceLastModeSwitch = millis();
// //   }
// //   counter++;
// //   delay(10);
// // }


// void oledDrawText(String text) {
//   oledDisplay.setFont(ArialMT_Plain_10);
//   oledDisplay.setTextAlignment(TEXT_ALIGN_LEFT);
//   oledDisplay.drawStringMaxWidth(0, 0, 128, text);
  
// //  display.setFont(ArialMT_Plain_10);
// //   display.setTextAlignment(TEXT_ALIGN_RIGHT);
// //   display.drawString(128, 54, String(millis()));
//   // write the buffer to the display
//   oledDisplay.display();
// }