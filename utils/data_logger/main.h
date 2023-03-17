/**
  ******************************************************************************
  * @file    main.c
  * @author  SRA
  * @brief   header file of command line example of High Speed Datalog
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *
  ******************************************************************************
  */

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

using std::vector;
using std::string;

class InputParser {

private:
    vector <std::string> tokens;

public:
    InputParser(int &argc, char **argv) {
        for (int i = 1; i < argc; ++i) {
            this->tokens.push_back(string(argv[i]));
        }
    }

    const string &getCmdOption(const string &option) const {

        vector<string>::const_iterator citer;

        citer = std::find(this->tokens.begin(), this->tokens.end(), option);

        if (citer != this->tokens.end() && ++citer != this->tokens.end()) {
            return *citer;
        }
        static const string empty_string("");
        return empty_string;
    }

    bool cmdOptionExists(const string &option) const {
        return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
    }
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
