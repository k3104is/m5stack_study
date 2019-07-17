//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial
#include "public.h"
#include "serial_to_serial_bt.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
void scrollLcd(UCHAR data);
int scroll_line();
void scrollAddress(uint16_t vsp);
// The scrolling area must be a integral multiple of TEXT_HEIGHT
#define TEXT_HEIGHT 16 // Height of text to be printed and scrolled
#define TOP_FIXED_AREA 14 // Number of lines in top fixed area (lines counted from top of screen)
#define BOT_FIXED_AREA 0 // Number of lines in bottom fixed area (lines counted from bottom of screen)
#define YMAX 240 // Bottom of screen area

// The initial y coordinate of the top of the scrolling area
uint16_t yStart = 0;
// yArea must be a integral multiple of TEXT_HEIGHT
uint16_t yArea = YMAX-TOP_FIXED_AREA-BOT_FIXED_AREA;
// The initial y coordinate of the top of the bottom text line
// uint16_t yDraw = YMAX - BOT_FIXED_AREA - TEXT_HEIGHT;
uint16_t yDraw = 0;

// Keep track of the drawing x coordinate
uint16_t xPos = 0;


BluetoothSerial SerialBT;
// static const s_c_comment_separate = "\n//////////////////////////\n";
// static const UCHAR *s_c_u1_comment_bt_to_se = "\n//////////////////////////\nserial to BT serial\n//////////////////////////\n";
// static const UCHAR *s_c_u1_comment_se_to_be = "\n//////////////////////////\nbt to serial serial\n//////////////////////////\n";

void BT_setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

}
static UCHAR s_u1_com_dir = 0;

void BT_loop() {
  char s1_str = 0;

  /* シリアル → BTシリアル */
  if (Serial.available()) {
    s1_str = Serial.read();
    if(E_COM_DIR_TO_BT != s_u1_com_dir){
      s_u1_com_dir = E_COM_DIR_TO_BT;
      Serial.write("\n//////////////////////////\nbt to serial serial\n//////////////////////////\n");
      SerialBT.print("\n//////////////////////////\nbt to serial serial\n//////////////////////////\n");
      M5.Lcd.print("\n//////////////////////////\nbt to serial serial\n//////////////////////////\n");
    }
    Serial.write(s1_str);
    SerialBT.write(s1_str);
    M5.Lcd.print(s1_str);
    scrollLcd(s1_str);
  }

  /* BTシリアル → シリアル */
  if (SerialBT.available()) {
    s1_str = SerialBT.read();
    if(E_COM_DIR_TO_SE != s_u1_com_dir){
      s_u1_com_dir = E_COM_DIR_TO_SE;
      Serial.write("\n//////////////////////////\nserial to BT serial\n//////////////////////////\n");
      SerialBT.print("\n//////////////////////////\nserial to BT serial\n//////////////////////////\n");
      M5.Lcd.print("\n//////////////////////////\nserial to BT serial\n//////////////////////////\n");
    }
    Serial.write(s1_str);
    SerialBT.write(s1_str);
    if (s1_str != '\r')
      M5.Lcd.print(s1_str);
    scrollLcd(s1_str);
  }
  delay(20);
}


void scrollLcd(UCHAR data){
  if (data == '\r' || xPos>311) {
    xPos = 0;
    yDraw = scroll_line(); // It can take 13ms to scroll and blank 16 pixel lines
  }
  // if (data > 31 && data < 128) {
  //   xPos += M5.Lcd.drawChar(data,xPos,yDraw,2);
  //   // blank[(18+(yStart-TOP_FIXED_AREA)/TEXT_HEIGHT)%19]=xPos; // Keep a record of line lengths
  // }
  //change_colour = 1; // Line to indicate buffer is being emptied
  return;
}



int scroll_line() {
  int yTemp = yStart; // Store the old yStart, this is where we draw the next line
  // Use the record of line lengths to optimise the rectangle size we need to erase the top line
  // M5.Lcd.fillRect(0,yStart,blank[(yStart-TOP_FIXED_AREA)/TEXT_HEIGHT],TEXT_HEIGHT, TFT_BLACK);
  M5.Lcd.fillRect(0,yStart,320,TEXT_HEIGHT, TFT_BLACK);

  // Change the top of the scroll area
  yStart+=TEXT_HEIGHT;
  // The value must wrap around as the screen memory is a circular buffer
  // if (yStart >= YMAX - BOT_FIXED_AREA) yStart = TOP_FIXED_AREA + (yStart - YMAX + BOT_FIXED_AREA);
  if (yStart >= YMAX) yStart = 0;
  // Now we can scroll the display
  scrollAddress(yStart);
  return  yTemp;
}

void scrollAddress(uint16_t vsp) {
  M5.Lcd.writecommand(ILI9341_VSCRSADD); // Vertical scrolling pointer
  M5.Lcd.writedata(vsp>>8);
  M5.Lcd.writedata(vsp);
}