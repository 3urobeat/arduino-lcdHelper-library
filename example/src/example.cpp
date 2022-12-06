/*
 * File: example.cpp
 * Project: arduino-lcdHelper-library
 * Created Date: 22.11.2022 16:50:28
 * Author: 3urobeat
 * 
 * Last Modified: 06.12.2022 12:16:00
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/HerrEurobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file. 
 */


/* 
    lcdHelper v1.0.0 usage example

    ------

    This example shows you how to use all new functions added by lcdHelper by displaying random stuff on the display.
    Make sure to download the LiquidCrystal_I2C library first!
*/


// Include libraries
#include <ESP8266WiFi.h>         // Ignore this import, I'm using an ESP8266 for testing, this import is needed for setup() and loop() to be defined
#include <LiquidCrystal_I2C.h>
//#include <lcdHelper.h>         // Normal import when lcdHelper is inside your lib folder - use this one in your project
#include "../../src/lcdHelper.h" // "Custom" import just for this example as lcdHelper.h is inside src at the project root and not inside lib of this example folder


// Init lcdHelper, which inits LiquidCrystal, so we can use our display
lcdHelper<LiquidCrystal_I2C> lcd(0x27, 20, 4); // My display is a 4x20 HD44780 with address 0x27

// Define two persistent animationFrame vars for animationPrint()
uint8_t animFrameTracker1 = 0; // uint8_t is an Arduino datatype - an unsigned 8 bit number
uint8_t animFrameTracker2 = 0;

// Define a persistent moveOffset var for movingPrint()
uint8_t moveOffset = 0;
uint8_t dots       = 0; // also save the dots progress of our little animation for later


// Setup display, enable backlight and print stuff which won't change and therefore doesn't need to be updated each 500ms
void setup()
{
    lcd.init();
    lcd.backlight();


    /* 
        centerPrint()

        Print a centered Hello! which will stay for the whole runtime
    */
    lcd.centerPrint("Hello!", 0); // We don't need to clear the row beforehand so we don't provide callClearLine as the default value is false


    /* 
        clearLine()

        Print something in line 2 and clear line after 2.5 seconds
    */
    lcd.centerPrint("lcdHelper Example", 2);
    delay(2500);
    lcd.clearLine(2); // This will remove "lcdHelper Example" but keep "Hello!" as we only clear one row


    // End of "startup welcome screen"


    /*
        utf8_strlen()

        Count length of a char array which contains UTF-8 chars (two byte long), convert size_t to char array and print to line 1
        Print strlen() result infront to see the difference

        You can also see some basic examples on how to work with char arrays here
    */
    const char utf8Message[] = "Here are UTF-8 chars:  ä ö ü ß ° $"; // 39 bytes + 1 for null byte
    char tempLen[21] = "UTF8: ";                                     // Temp char array to construct message showing length

    char tempUTF8[3] = ""; // Temp char arrs to convert ints returned by strlen() to char arrs
    char tempByte[3] = "";     

    itoa(lcd.utf8_strlen(utf8Message), tempUTF8, 10); // Get result from lcdHelper's utf8_strlen() and onvert int to char arr
    itoa(strlen(utf8Message), tempByte, 10);          // Get result from C's string.h strlen() and onvert int to char arr

    strncat(tempLen, tempUTF8, 2); // Construct tempLen message which will be printed by adding the 2 results to the end of tempLen
    strcat(tempLen, "  Normal: "); // No need for strncat when we cat a fixed length char arr
    strncat(tempLen, tempByte, 2);

    lcd.setCursor(0, 1);
    lcd.print(tempLen);  // Print it!


    /*
        limitedPrint()

        Print a cut off message without needing to do modify char array.
        This function was made to work especially well with UTF-8 chars but LiquidCrystal_I2C doesn't really support them so you have to trust me.
        This is why I'm using NoiascaLiquidCrystal: https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm
    */
    lcd.setCursor(0, 2);
    lcd.limitedPrint("Cut off msg - Secret: You won't see this", 10);
}


// Now print stuff that should update every 250ms
void loop()
{
    /* 
        animationPrint()

        Print a loading and progress animation in the first row beside the centered "Hello!"
    */
    lcd.animationPrint(lcd.animations.loading, 8, &animFrameTracker1, 0, 0);
    lcd.animationPrint(lcd.animations.progress, 6, &animFrameTracker2, 15, 0); // progress is 5 chars wide


    /* 
        alignedPrint()
    
        Print some moving dots aligned to the right of row 2
    */
    dots++;                 // Add another dot
    if (dots > 4) dots = 0; // Reset when 4 dots are present

    char tempDots[5] = "";                                    // Temp char arr to construct dots
    for (uint8_t i = 0; i < dots; i++) strcat(tempDots, "."); // Add dots amount of dots to temp

    lcd.setCursor(11, 2);
    lcd.print("Dots:");                     // Show something infront to showcase that temp is aligned to the right
    lcd.alignedPrint("right", tempDots, 4); // Print temp and overwrite any previous dots


    /* 
        movingPrint()

        Let a long message run across 2/3 of the last row
    */
    lcd.setCursor(0, 3);
    lcd.movingPrint("  This is a long message moving every 500ms  ", &moveOffset, 14); // Pass address of moveOffset and limit to a width of 14 chars


    /* 
        toFixedLengthNumber()

        Show seconds of uptime with fixed width at the end of the last row 
    */
    unsigned long uptime = millis() / 1000; // Current uptime in seconds
    char tempSeconds[3] = "";               // Buffer char array with space for two digits and null byte

    lcd.toFixedLengthNumber(tempSeconds, uptime % 60, 2); // Add preceding 0 to seconds if <10
    
    lcd.setCursor(18, 3);
    lcd.print(tempSeconds); // Print using the normal print function inherited from LiquidCrystal



    // Delay next iteration
    delay(500);
}