/*
 * File: lcdHelper.tpp
 * Project: arduino-lcdHelper-library
 * Created Date: 28.08.2022 22:55:04
 * Author: 3urobeat
 * 
 * Last Modified: 28.08.2022 23:27:43
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