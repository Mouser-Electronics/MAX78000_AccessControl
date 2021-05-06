/**************************************************************************/
/*!
    @file     readMifare.pde
    @author   Adafruit Industries
	@license  BSD (see license.txt)

    This example will wait for any ISO14443A card or tag, and
    depending on the size of the UID will attempt to read from it.

    If the card has a 4-byte UID it is probably a Mifare
    Classic card, and the following steps are taken:

    - Authenticate block 4 (the first block of Sector 1) using
      the default KEYA of 0XFF 0XFF 0XFF 0XFF 0XFF 0XFF
    - If authentication succeeds, we can then read any of the
      4 blocks in that sector (though only block 4 is read here)

    If the card has a 7-byte UID it is probably a Mifare
    Ultralight card, and the 4 byte pages can be read directly.
    Page 4 is read by default since this is the first 'general-
    purpose' page on the tags.


  This is an example sketch for the Adafruit PN532 NFC/RFID breakout boards
  This library works with the Adafruit NFC breakout
  ----> https://www.adafruit.com/products/364

  Check out the links above for our tutorials and wiring diagrams
  These chips use SPI or I2C to communicate.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

*/
/**************************************************************************/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include "TMC5130_registers.h"
#include <Estee_TMC5130.h>

// If using the breakout with SPI, define the pins for SPI communication.
#define SPI_SCK       (13)
#define SPI_MISO      (12)
#define SPI_MOSI      (11)
#define PN532_SS      (10)
#define TMC5130_SS    (9)
#define TMC5130_CLK16 (8)
#define TMC5130_ENN   (7)
#define MAX_PB2       (6)
#define MAX_LED       (5)

Adafruit_PN532 nfc(SPI_SCK, SPI_MISO, SPI_MOSI, PN532_SS);
Estee_TMC5130 tmc = Estee_TMC5130(TMC5130_SS);

bool dir = false;
bool correct_tag_read = false;
bool received_open_signal = false;


void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10); // for Leonardo/Micro/Zero

  Serial.println("Hello!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);

  pinMode(MAX_PB2, OUTPUT);
  pinMode(MAX_LED, INPUT);
  digitalWrite(MAX_PB2, LOW);



  pinMode(TMC5130_ENN, OUTPUT);
  digitalWrite(TMC5130_ENN, HIGH); // disabled for start
  pinMode(TMC5130_SS, OUTPUT);
  digitalWrite(TMC5130_SS, HIGH);
  tmc.begin(0x4, 0x4, NORMAL_MOTOR_DIRECTION);
  uint32_t onerev = 200 * 256;
  tmc.writeRegister(VSTART, 0x0);
  tmc.writeRegister(A_1, 1000);
  tmc.writeRegister(V_1, 50000);
  tmc.writeRegister(AMAX, 500);
  tmc.writeRegister(VMAX, 200000);
  tmc.writeRegister(DMAX, 700);
  tmc.writeRegister(D_1, 1400);
  tmc.writeRegister(VSTOP, 10);
  tmc.writeRegister(TZEROWAIT, 0);
  tmc.writeRegister(RAMPMODE, 0);
  digitalWrite(TMC5130_ENN, LOW);
  

  // configure board to read RFID tags
  nfc.SAMConfig();

  Serial.println("Waiting for an ISO14443A Card ...");
}


void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  uint32_t cardid = uid[0];

  if (correct_tag_read == false) {
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
    if (success) {
      // Display some basic information about the card
      Serial.println("Found an ISO14443A card");
      Serial.print("  UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
      Serial.print("  UID Value: ");
      nfc.PrintHex(uid, uidLength);
      Serial.println();

      if (uidLength == 4)
      {
        // We probably have a Mifare Classic card ...

        cardid <<= 8;
        cardid |= uid[1];
        cardid <<= 8;
        cardid |= uid[2];
        cardid <<= 8;
        cardid |= uid[3];
        Serial.print("Seems to be a Mifare Classic card #");
        Serial.println(cardid);

        if (cardid == 2165834) {
          correct_tag_read = true;
          digitalWrite(MAX_PB2, HIGH);
          delay(2000);
          digitalWrite(MAX_PB2, LOW);
          Serial.println("Correct card swiped. Please repeat the passphrase to unlock...\n");
        }
      }
    }
  }

  received_open_signal = digitalRead(MAX_LED);
  if (received_open_signal) {
    unlockDevice();
  }
}


void unlockDevice() {
  tmc.writeRegister(XTARGET, dir ? (200 * 256) : 0);
}
