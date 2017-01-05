#include <Wire.h>

#define disk1 0x50    //Address of 24LC256 eeprom chip

char harf;

void setup(void)
{
  Serial.begin(9600);
  Wire.begin();

  unsigned int address = 0;

  writeEEPROM(disk1, address, 123);
  Serial.print(readEEPROM(disk1, address), DEC);
}

void loop() {

  // 0 ve 1 numarali adressleri ogrenme denemesi

  /* if (Serial.available() > 0)
  {
    harf = Serial.read();
    if (harf == 'a') {
      Serial.println(readEEPROM(disk1, 1));
    }
    else if (harf == 'b') {
      Serial.println(readEEPROM(disk1, 0));
    }
  }*/

  // 1`den 1000`e otomatik adresleme denemesi

  /* for (int i = 0; i < 1000; i++)
  {
    writeEEPROM(disk1, i, i);
    Serial.print("Adress: ");
    Serial.println(readEEPROM(disk1, i));
    delay(200);
  }*/

}

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data )
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();

  delay(5);
}

byte readEEPROM(int deviceaddress, unsigned int eeaddress )
{
  byte rdata = 0xFF;

  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(deviceaddress, 1);

  if (Wire.available()) rdata = Wire.read();

  return rdata;
}
