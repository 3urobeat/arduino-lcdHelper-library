/*
 * File: lcdHelper.h
 * Project: arduino-lcdHelper-library
 * Created Date: 26.08.2022 12:04:51
 * Author: 3urobeat
 * 
 * Last Modified: 28.08.2022 20:04:45
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


template <typename lcd>
class lcdHelper : public lcd { //use template as base to inherit from
public:
    
    /**
     * Constructor
     * @param addr The address of your display
     * @param rows The amount of rows your display haI2Cs
     * @param cols The amount of columns your display has
     */
    lcdHelper(uint8_t addr, uint8_t rows, uint8_t cols) : lcd(addr, rows, cols) {
        _lcdRows = rows;
        _lcdCols = cols;
    };

private:

    uint8_t _lcdRows;
    uint8_t _lcdCols;

};


#endif