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
#include <SoftwareSerial.h>  /* USed for comm. with BT module */

/* =========================================================== */
/* Const defines. Must match HW cabling */

/* HC_05 BT module related wires */
#define BT_RX_PIN    11  /* Goes to TXD on BT module */
#define BT_TX_PIN    10  /* Goes to RXD on BT module */

/* DS3231 RTC related wires */


/* Motor related wires */


/* =========================================================== */
/* Init function call once by Arduino framework */
void setup() 
{
  
  
  
}


/* =========================================================== */
/* Function called continously by Arduino framework */
void loop()
{
  
  
  
}
