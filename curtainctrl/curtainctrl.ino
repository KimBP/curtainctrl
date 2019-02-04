
/* 
  CurtainCtrl is a BT enabled controller supposed to control a curtain using a little motor
  The module has an RTC module supposed to execute 'timed' commands at the right time
  
  Copyright Kim Bøndergaard <kim@fam-boendergaard>   2019
  
  HW Required:
    Arduino
    DS3231 Real Time clock
    HC-05 Bluetooth module
    
  SW Modules required
    
 */

/* =========================================================== */
/* Include modules needed */
#include <SoftwareSerial.h>  /* Used for comm. with BT module */
#include <Wire.h>            /* Needed by RTClib.h            */
#include <RTClib.h>          /* Library for RTC module        */


/* =========================================================== */
/* Const defines. Must match HW cabling */

/* HC_05 BT module related wires */
#define BT_RX_PIN    11  /* Goes to TXD on BT module */
#define BT_TX_PIN    10  /* Goes to RXD on BT module */

/* DS3231 RTC related wires */


/* Motor related wires */

/* =========================================================== */
/* Module global variables */
static RTC_DS3231 rtc;
static const char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


static SoftwareSerial bluetooth(BT_TX_PIN, BT_RX_PIN);   // The bluetooth object

/* =========================================================== */
/* Init function call once by Arduino framework */
void setup() 
{

  Serial.begin(9600); // For debugging
  delay(3000);        //Wait for console to open
  Serial.println("CurtainCtrl started");
  
  Initialize_RTC();

  bluetooth.begin(9600);  
}


/* =========================================================== */
/* Function called continously by Arduino framework */
void loop()
{
  DateTime t = rtc.now();
  
  dbgPrintTime(t);
  delay(3000);
  btInteractive();
}


/* =========================================================== */
/* Bluetooth helpers */
void btWaitForReply()
{
    bluetooth.flush();
    while(!bluetooth.available()) {};
}

void btInteractive()
{
    if (bluetooth.available() > 0) {
        bool keepReading = true;
        Serial.println("Bluetooth activity registered");
        
        bluetooth.flush(); // Skip what have brought us in here
        while(keepReading) {
            bluetooth.println("0->Inc hour");
            bluetooth.println("1->Dec hour");
            bluetooth.println("X-Exit");
          
            btWaitForReply();
            char btChar = bluetooth.read();
            Serial.print("Received a command from BT: ");
            Serial.println(btChar);
            
            TimeSpan deltaTime(60*60);
            
            switch (btChar) {
              case '0':
                  rtc.adjust(rtc.now()+deltaTime);
                  break;
                  
              case '1':
                  rtc.adjust(rtc.now()-deltaTime);
                  break;
              
              case 'x': // Accept both lower case 
              case 'X': // and upper case X
                  bluetooth.println("Exiting menu");
                  keepReading = false;
                  break;
              default: 
                  break;
            }
        }
    }
}

/* =========================================================== */
/* RTC helpers */
void Initialize_RTC()
{
  if (! rtc.begin() ) {
    Serial.println("Couldn't find RTC");
    while(1); // Stay here forever
  }
  
  if (rtc.lostPower()) {
    Serial.println("RTC lost power. New time set");
    rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  }
}

/* =========================================================== */
/* Debug helpers */
void dbgPrintTime(DateTime t)
{
    Serial.print(t.year(), DEC);
    Serial.print('/');
    Serial.print(t.month(), DEC);
    Serial.print('/');
    Serial.print(t.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[t.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(t.hour(), DEC);
    Serial.print(':');
    Serial.print(t.minute(), DEC);
    Serial.print(':');
    Serial.print(t.second(), DEC);
    Serial.println();

}
