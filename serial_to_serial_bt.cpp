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
    M5.Lcd.print(s1_str);
  }
  delay(20);
}





