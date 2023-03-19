/**
  ******************************************************************************
  * @file    main.c
  * @author  SRA
  * @brief   source code of command line example of High Speed Datalog
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
#include "main.h"

#include <cstdlib>
#include <unordered_map>
#include <iomanip>
#include <sstream>
#include <optional>
#include "json.hpp"
#include "cxxopts.hpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;

void action_load_and_store_device_config() {

    if(hs_datalog_open() != ST_HS_DATALOG_OK) {
        cout << "Error occurred while initializing datalog\n";
        cout << "Press any key to exit \n";
        cin.get();
        exit(EXIT_FAILURE);
    }

    int n_devices = 0;
    if(hs_datalog_get_device_number(&n_devices) != ST_HS_DATALOG_OK) {
        cout << "Error occurred while retrieving device number\n";
        cout << "Press any key to exit \n";
        cin.get();
        exit(EXIT_FAILURE);
    }

    if(n_devices == 0) {
        cout << "No devices, exiting\n";
        cout << "Press any key to exit \n";
        cin.get();
        exit(EXIT_FAILURE);
    }

    char *data;
    if(hs_datalog_get_device(0, &data) != ST_HS_DATALOG_OK) {
        cout << "Error occurred while retrieving device configuration\n";
        cout << "Press any key to exit \n";
        cin.get();
        exit(EXIT_FAILURE);
    }
    auto json = nlohmann::json::parse(data);

    std::ofstream writer;
    writer.open("DeviceConfig.json", std::ios::out | std::ios::binary);
    writer << json.dump(1);
    writer.close();

    cout << "Current Device Configuration has been saved.\n";
    hs_datalog_free(data);
    exit(EXIT_SUCCESS);
}

void action_print_usage(const string& content) {
    cout << content << endl;
    exit(EXIT_SUCCESS);
}

void action_print_version() {
    // TODO: What if the HSD Interface cannot be loaded.
    char * version;
    hs_datalog_get_version(&version);
    cout << "Data Logger CLI 0.0.1" << '\n';
    cout << version << '\n';
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    cxxopts::Options options("data_logger", "Data Logger CLI");

    options.add_options()
        ("v,version", "Print version information and then exit.")
        ("h,help", "Print usage and then exit.")
        ("f,config", "Device configuration file (JSON).",
            cxxopts::value<string>())
        ("t,duration", "Duration of the acquisition (seconds).",
            cxxopts::value<uint32_t>()->default_value("60"))
        ("y", "Directly start the acquistion without waiting for user confirmation.")
        ("g", "Get current device configuration and save it.")
    ;

    auto result = options.parse(argc, argv);

    if (result.count("v")) action_print_version();
    if (result.count("h")) action_print_usage(options.help());
    if (result.count("g")) action_load_and_store_device_config();


    // NOTE: `-f` for the reader of the device_config and `-t` for the duration
    std::ifstream reader;
    if (result.count("f")) {

        string filename = result["f"].as<string>();

        reader.open(filename, std::ios::in | std::ios::binary);
        if (!reader.is_open()) {
            cout << "File not found: " << filename << endl;
            exit(1);
        }
    }
    uint32_t timeout_seconds = result["t"].as<uint32_t>();

    return 0;
}


#ifdef __linux__
/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
#endif
