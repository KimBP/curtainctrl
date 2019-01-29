
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

/* =========================================================== */
/* Init function call once by Arduino framework */
void setup() 
{

  Initialize_RTC();

}


/* =========================================================== */
/* Function called continously by Arduino framework */
void loop()
{
  DateTime t = rtc.now();
  
  delay(3000);
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
