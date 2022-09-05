/*
 * File: lcdHelper.tpp
 * Project: arduino-lcdHelper-library
 * Created Date: 28.08.2022 22:55:04
 * Author: 3urobeat
 * 
 * Last Modified: 05.09.2022 14:43:34
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
    strncpy(this->_lcdContent[this->_lcdCursorPos[1]] + this->_lcdCursorPos[0], str, this->_lcdCols - this->_lcdCursorPos[0]); // update local storage of lcd content

    //check if str is longer than place available and use cut down version from _lcdContent
    if ((uint8_t) strlen(str) > this->_lcdCols - this->_lcdCursorPos[0]) {
        this->setCursor(0, this->_lcdCursorPos[1]);

        return lcd::print(this->_lcdContent[this->_lcdCursorPos[1]]);
    } else {
        return lcd::print(str);
    }
}

template <typename lcd>
size_t lcdHelper<lcd>::print(char chr) {
    this->_lcdContent[this->_lcdCursorPos[1]][this->_lcdCursorPos[0]] = chr; // update local storage of lcd content

    return lcd::print(chr);
}

template <typename lcd>
void lcdHelper<lcd>::setCursor(uint8_t col, uint8_t row) {
    if (col >= this->_lcdCols - 1 || row >= this->_lcdRows - 1) return; //check for invalid cursor placement

    this->_lcdCursorPos[0] = col;
    this->_lcdCursorPos[1] = row;

    lcd::setCursor(col, row);
}

template <typename lcd>
void lcdHelper<lcd>::home() {
    this->_lcdCursorPos[0] = 0;
    this->_lcdCursorPos[1] = 0;

    lcd::home();
}

template <typename lcd>
void lcdHelper<lcd>::clear() {
    for (int row = 0; row < this->_lcdRows; row++)
        memset(this->_lcdContent[row], ' ', strlen(this->_lcdContent[row]) - 1); // fill row with spaces but keep null byte at the end

    lcd::clear();
}


// --- Custom Functions ---
template <typename lcd>
char* lcdHelper<lcd>::getLcdContent(uint8_t row) {
    return this->_lcdContent[row];
}

template <typename lcd>
uint8_t* lcdHelper<lcd>::getCursorPos() {
    return this->_lcdCursorPos;
}

template <typename lcd>
void lcdHelper<lcd>::clearLine(uint8_t row) {

    // print _lcdCols amount of spaces to effectively clear the line
    char str[this->_lcdCols + 1]; // make space for null byte

    for (int i = 0; i < this->_lcdCols; i++) {
        str[i] = ' ';
    }

    str[this->_lcdCols] = '\0';

    this->setCursor(0, row);
    this->print(str);
    
}

template <typename lcd>
void lcdHelper<lcd>::centerPrint(const char *str, uint8_t row, bool callClearLine) {

    // clear the line first to avoid old characters corrupting the text when content is not the same
    if (callClearLine) this->clearLine(row);

    // Calculate column
    int offset = this->_lcdCols - this->utf8_strlen(str);
    if (offset < 0) offset = 0; //set offset to 0 if it would be negative

    this->setCursor(offset / 2, row); //center string
    this->print(str);

}

template <typename lcd>
void lcdHelper<lcd>::movingPrint(const char *str, uint8_t row) {

    // check if we actually have to move something
    if (strlen(str) > this->_lcdCols) {
        if (this->_moveOffset + this->_lcdCols > strlen(str)) this->_moveOffset = 0; // reset if string was fully displayed

        char temp[this->_lcdCols + 1] = ""; // leave space for next char and null byte

        strncpy(temp, str + this->_moveOffset, this->_lcdCols); // substring to current offset
        
        // Fix for Umlaute: Add more chars if at least one two byte long char is included to avoid message being too short on the display
        strncat(temp, str + this->_lcdCols + this->_moveOffset, this->_lcdCols - this->utf8_strlen(temp));
        // Using Umlaute is still a bit janky but this is definitely an improvement. I'm not sure right now what else I could do.

        // Print current string
        this->setCursor(0, row);
        this->print(temp);

        // Increase offset
        this->_moveOffset++;

    } else {
        
        this->setCursor(0, row);
        this->print(str);
    }

}