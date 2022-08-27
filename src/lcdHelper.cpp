/*
 * File: lcdHelper.cpp
 * Project: arduino-lcdHelper-library
 * Created Date: 26.08.2022 12:04:54
 * Author: 3urobeat
 * 
 * Last Modified: 27.08.2022 14:48:23
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/HerrEurobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file. 
 */


#include "lcdHelper.h"


//Constructor
lcdHelper::lcdHelper(void *lcd, int rows, int cols) {
    _lcd     = lcd;
    _lcdRows = rows;
    _lcdCols = cols;
}