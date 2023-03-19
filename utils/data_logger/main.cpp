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

using std::vector;
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

void action_load_device_descriptor() {
    if(hs_datalog_open() != ST_HS_DATALOG_OK)
    {
        cout << "Error occurred while initializing datalog\n";
        cout << "Press any key to exit \n";
        cin.get();
        exit(EXIT_FAILURE);
    }

    int n_devices = 0;
    if(hs_datalog_get_device_number(&n_devices) != ST_HS_DATALOG_OK)
    {
        cout << "Error occurred while retrieving device number\n";
        cout << "Press any key to exit \n";
        exit(EXIT_FAILURE);
        getchar();
    }

    if(n_devices == 0)
    {
        cout << "No devices, exiting\n";
        cout << "Press any key to exit \n";
        cin.get();
        exit(EXIT_FAILURE);
    }

    /* If multiple devices are present, address only device with id = 0 */
    int device_id = 0;
    int n_sensors = 0;

    char * tempDev;

    if(hs_datalog_get_device_descriptor(device_id, &tempDev) != ST_HS_DATALOG_OK)
    {
        cout << "Error occurred while retrieving device descriptor\n";
        cout << "Press any key to exit \n";
        cin.get();
        exit(EXIT_FAILURE);
    }

    auto json = nlohmann::json::parse(tempDev);
    cout << "Device information: \n";
    cout << json.dump(1) << "\n";

    /* Free memory */
    if(hs_datalog_free(tempDev) != ST_HS_DATALOG_OK)
    {
        cout << "Error occurred while freeing memory\n";
        cout << "Press any key to exit \n";
        cin.get();
        exit(EXIT_FAILURE);
    }
}

void action_print_usage(const string& content) {
    cout << content << endl;
    exit(EXIT_SUCCESS);
}

void action_print_version() {
    // TODO : What if the HSD Interface cannot be loaded.
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

    // NOTE: Do we need to read device descriptor before reading number of sensor
    // NOTE: `deviceID` is set to 0 if multiple devices found
    // if(hs_datalog_get_sensor_number(deviceID, &nSensors) != ST_HS_DATALOG_OK)
    // {
    //     cout << "Error occurred while retrieving sensor number\n";
    //     cout << "Press any key to exit \n";
    //     getchar();
    //     return -1;
    // }

    // char acq_name[] = "testName";
    // char acq_description[] = "descriptionTest";
    // hs_datalog_set_acquisition_param(deviceID, acq_name, acq_description);


    vector<vector<bool>> SubsensorIsActive;

    /* Try and open JSON config file on the hard disk*/
    bool configFromFile = false;
    if (configFile.is_open())
    {
        configFromFile = true;
        cout << endl <<"Configuration imported from Json file " << endl << endl;

        configFile.seekg (0, configFile.end);
        long long size = configFile.tellg();
        configFile.seekg (0, configFile.beg);

        /* Read the whole file */
        char * jsonChar = new char [size+1];
        configFile.seekg (0, ios::beg);
        configFile.read (jsonChar, static_cast<int>(size));
        configFile.close();
        jsonChar[size]=0;  // JSON lib needs a '\0' at the end of the string

        /* Parse JSON and extract sensors */
        auto configJson = nlohmann::json::parse(jsonChar);
        auto jSensors = configJson.at("device").at("sensor");

        /* Create messages to set sensor status as described in the file and send them to the device*/
        for (size_t j = 0; j < jSensors.size(); j++ )
        {
            auto jSubSensorsStatus = jSensors.at(j).at("sensorStatus").at("subSensorStatus");
            nlohmann::json cmd;
            cmd["command"] = "SET";
            cmd["sensorId"] = jSensors.at(j).at("id");

            SubsensorIsActive.push_back(std::vector<bool>());
            for(size_t k = 0; k< jSubSensorsStatus.size(); k++ )
            {
                nlohmann::json params;
                auto subId = jSensors.at(j).at("sensorDescriptor").at("subSensorDescriptor").at(k).at("id");
                params["id"]= subId;

                auto it = jSubSensorsStatus.at(k).begin();
                auto end = jSubSensorsStatus.at(k).end();
                for(; it!=end; it++)
                {
                    params[it.key()]=it.value();
                }
                cmd["subSensorStatus"].push_back(params);
                SubsensorIsActive[j].push_back(jSensors.at(j).at("sensorStatus").at("subSensorStatus").at(k).at("isActive"));
            }
            if(hs_datalog_send_message(deviceID, const_cast <char *>(cmd.dump().data()), static_cast<int>(cmd.dump().length()), nullptr, nullptr) != ST_HS_DATALOG_OK)
            {
                cout << "Error occurred while sending message\n";
                cout << "Press any key to exit \n";
                getchar();
                return -1;
            }
        }
        /* Update tag list */
        auto tag_hw = configJson.at("device").at("tagConfig").at("hwTags");
        auto tag_sw = configJson.at("device").at("tagConfig").at("swTags");

        auto it= tag_hw.begin();
        while(it !=tag_hw.end() )
        {
            int id=it->at("id");
            string label=it->at("label");
            hs_datalog_set_hw_label(deviceID, id, &label[0]);

            bool status =it->at("enabled");
            hs_datalog_enable_hw_tag(deviceID, id, status);
            it++;
        }

        it= tag_sw.begin();
        while(it !=tag_sw.end() )
        {
            int id=it->at("id");
            string label=it->at("label");
            hs_datalog_set_sw_label(deviceID, id, &label[0]);
            it++;
        }
        delete[] jsonChar;
    }

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
