#ifndef _SERIAL_TO_SERIAL_BT_LIB_
#define _SERIAL_TO_SERIAL_BT_LIB_


#include "BluetoothSerial.h"

#define TEXT_HEIGHT 16 // Height of text to be printed and scrolled
#define TOP_FIXED_AREA 14 // Number of lines in top fixed area (lines counted from top of screen)
#define BOT_FIXED_AREA 0 // Number of lines in bottom fixed area (lines counted from bottom of screen)
#define YMAX 240 // Bottom of screen area

enum{
    E_COM_DIR_NONE = 0,
    E_COM_DIR_TO_BT,
    E_COM_DIR_TO_SE,
};

#endif