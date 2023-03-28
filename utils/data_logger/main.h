/**
  ******************************************************************************
  * @file    main.h
  * @author  Austin Chen
  * @brief   header file of `data_logger` command line tool
  *
  * Copyright (c) 2022 Austin Chen
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
 **/

#include <stdint.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <string>
#include <chrono>
#include "hsd.h"
#include "pthread.h"
#include "json.hpp"

#ifdef _WIN32
#include <conio.h>
#include "windows.h"
#elif __linux__
#include <sys/stat.h>
int _kbhit() ;
#endif

#define DLOGGER__VERSION_MAJOR 0
#define DLOGGER__VERSION_MINOR 0
#define DLOGGER__VERSION_PATCH 1

static constexpr struct {
    uint8_t major, minor, patch;
} version = {
    DLOGGER__VERSION_MAJOR,
    DLOGGER__VERSION_MINOR,
    DLOGGER__VERSION_PATCH
};

bool getInput(char *c) {
#ifdef __linux__
    if (_kbhit())
    {
        *c = getc(stdin);
        return true; // Key Was Hit
    }
    return false; // No keys were pressed
#elif _WIN32
    if (_kbhit())
    {
        *c = getch();
        return true; // Key Was Hit
    }
    return false; // No keys were pressed
#endif
}
