/*
 * File: lcdHelper.tpp
 * Project: arduino-lcdHelper-library
 * Created Date: 28.08.2022 22:55:04
 * Author: 3urobeat
 * 
 * Last Modified: 30.08.2022 17:16:00
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/HerrEurobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file. 
 */

// Template implementation file
// https://stackoverflow.com/a/495056


// --- Overwritten Functions ---
template <typename lcd>
size_t lcdHelper<lcd>::print(const char *str) {
    strncpy(this->_lcdContent[this->_lcdCursorPos[1]], str, this->_lcdCols); // update local storage of lcd content

    return lcd::print(str);
}

template <typename lcd>
void lcdHelper<lcd>::setCursor(uint8_t col, uint8_t row) {
    this->_lcdCursorPos[0] = col;
    this->_lcdCursorPos[1] = row;

    lcd::setCursor(col, row);
}


// --- Custom Functions ---
template <typename lcd>
void lcdHelper<lcd>::clearLine(uint8_t row) {

    //print _lcdCols amount of spaces to effectively clear the line
    char str[this->_lcdCols]; //_lcdCols counts from 1, so we don't need to do +1 to make space for the null byte

    for (int i = 0; i < this->_lcdCols; i++) {
        str[i] = ' ';
    }

    str[this->_lcdCols] = '\0';

    lcd::setCursor(0, row);
    lcd::print(str);
    
}

template <typename lcd>
void lcdHelper<lcd>::centerPrint(const char *str, uint8_t row, bool callClearLine) {

    // clear the line first to avoid old characters corrupting the text when content is not the same
    if (callClearLine) this->clearLine(row);

    // Calculate column
    int offset = this->_lcdCols - this->utf8_strlen(str);
    if (offset < 0) offset = 0; //set offset to 0 if it would be negative

    lcd::setCursor(offset / 2, row); //center string
    lcd::print(str);

};