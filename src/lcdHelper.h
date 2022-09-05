/*
 * File: lcdHelper.h
 * Project: arduino-lcdHelper-library
 * Created Date: 26.08.2022 12:04:51
 * Author: 3urobeat
 * 
 * Last Modified: 05.09.2022 15:19:58
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
     * @param cols The amount of columns your display has
     * @param rows The amount of rows your display has
     */
    lcdHelper(uint8_t addr, uint8_t cols, uint8_t rows) : lcd(addr, cols, rows) {
        _lcdCols = cols;
        _lcdRows = rows;
    };

    /**
     * Clears a specific line on your display
     * @param row The row to clear (counted from 0)
     */
    void clearLine(uint8_t row);

    /**
     * Print a string centered on your display
     * @param str The string to print
     * @param row The row to print the string in
     * @param callClearLine Set to true if line should be cleared before printing
     */
    void centerPrint(const char *str, uint8_t row, bool callClearLine);


    /**
     * Prints a String that will be moved on the screen each time the method is called
     * @param str The string to print
     * @param row The row to print the string in
     */
    void movingPrint(const char *str, uint8_t row);

    
    /**
     * Better strlen function to correctly count chars that are two bytes long (like ä ö or ü)
     */
    size_t utf8_strlen(const char *str);

private:

    uint8_t _lcdCols;
    uint8_t _lcdRows;
    
    uint8_t _moveOffset = 0;

};


// Include template implementation files
#include "lcdHelper.tpp"
#include "helpers/stringUtils.tpp"

#endif