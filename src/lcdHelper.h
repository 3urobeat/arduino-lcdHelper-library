/*
 * File: lcdHelper.h
 * Project: arduino-lcdHelper-library
 * Created Date: 26.08.2022 12:04:51
 * Author: 3urobeat
 * 
 * Last Modified: 27.08.2022 14:48:17
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/HerrEurobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file. 
 */


#ifndef LCDHELPER_H
#define LCDHELPER_H


class lcdHelper {
public:
    
    /**
     * Constructor
     * @param lcd The LiquidCrystal_I2C (or similar) object of the display to control
     * @param rows The amount of rows your display has
     * @param cols The amount of columns your display has
     */
    lcdHelper(void *lcd, int rows, int cols);

private:

    void *_lcd;
    int _lcdRows;
    int _lcdCols;

};


#endif