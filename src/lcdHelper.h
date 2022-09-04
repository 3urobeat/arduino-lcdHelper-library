/*
 * File: lcdHelper.h
 * Project: arduino-lcdHelper-library
 * Created Date: 26.08.2022 12:04:51
 * Author: 3urobeat
 * 
 * Last Modified: 04.09.2022 22:07:44
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
        
        // initialize lcdContent 2D array with acquired sizes
        _lcdContent = new char*[rows];
        for (int i = 0; i < rows; i++)
            _lcdContent[i] = new char[cols + 1];
    };

    /**
     * Destructor
     */
    ~lcdHelper() {
        // delete lcdContent 2D array to avoid mem leaks if user destroys object (if I understand correctly)
        for (int i = 0; i < this->_lcdRows; i++)
            delete _lcdContent[i];
        delete _lcdContent;
    };

    /**
     * Print a string on your display
     * @param str The string to print
     */
    size_t print(const char *str);

    /**
     * Print a string on your display
     * @param col The column to set the cursor to
     * @param row The row to set the cursor to
     */
    void setCursor(uint8_t col, uint8_t row);

    /**
     * Moves cursor to 0, 0.
     */
    void home();

    /**
     * Clears the whole display. Use clearLine() to clear only a specific row.
     */
    void clear();

    /**
     * Get the display content of a row
     * @param row The row to get the content of
     * @return Char array containing the content of the provided row
     */
    char* getLcdContent(uint8_t row);

    /**
     * Get the cursors current column and row position
     * @return Array: col, row
     */
    uint8_t* getCursorPos();

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

private:

    uint8_t _lcdCols;
    uint8_t _lcdRows;

    uint8_t _lcdCursorPos[2] = { 0, 0 }; // (col, row) - save current cursor position
    char  **_lcdContent;                 // save content of lcd to be able to "read"

    uint8_t _moveOffset = 0;
    
    size_t utf8_strlen(const char *str);

};


// Include template implementation files
#include "lcdHelper.tpp"
#include "helpers/stringUtils.tpp"

#endif