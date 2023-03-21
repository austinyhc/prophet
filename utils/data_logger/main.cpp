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
#include <memory>
#include "hsd.h"
#include "json.hpp"
#include "cxxopts.hpp"

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

#define DEVICE_ID 0

static uint8_t FEATURE_TAGGING = 1;


void hs_datalog_initialize() {
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
}

void action_load_and_save_device_config() {

    char* config;
    int ret = hs_datalog_get_device(DEVICE_ID, &config);

    if (ret == ST_HS_DATALOG_ERROR) {
        cout << "Error occurred while retrieving device configuration\n";
        cout << "Press any key to exit \n";
        cin.get();
        exit(EXIT_FAILURE);
    }

    auto json = nlohmann::json::parse(config);

    std::ofstream writer;
    writer.open("./DeviceConfig.json", std::ios::out | std::ios::binary);
    writer << json.dump(1);
    writer.close();

    cout << "Current Device Configuration has been saved.\n";

    hs_datalog_free(config);
}

void action_print_device_descriptor() {

    char* desc;
    int ret = hs_datalog_get_device_descriptor(DEVICE_ID, &desc);

    if (ret == ST_HS_DATALOG_ERROR) {
        cout << "Error occurred while retrieving device descriptor\n";
        cout << "Press any key to exit \n";
        cin.get();
        exit(EXIT_FAILURE);
    }

    auto json = nlohmann::json::parse(desc);
    cout << "Device information: \n";
    cout << json.dump(1) << "\n";

    hs_datalog_free(desc);
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

std::map<std::tuple<int, string>, bool>
action_get_available_tag() {

    char* tag_info;
    hs_datalog_get_available_tags(DEVICE_ID, &tag_info);

    auto json  = nlohmann::json::parse(std::string(tag_info));
    auto tags = json.at("swTags");

    std::map<std::tuple<int, string>, bool> dict;
    for (auto const& tag : tags) {
        auto key = std::make_tuple(tag.at("id"), tag.at("label"));
        dict.insert({key, false});
    }

    hs_datalog_free(tag_info);

    return dict;
}

// TODO: Can I use unique pointer here are move the ownership to the caller
char* read_file(std::ifstream& infile) {

    infile.seekg(0, std::ios::end);
    size_t len = infile.tellg();

    char* stream = new char[len+1];

    infile.seekg (0, std::ios::beg);
    infile.read(stream, static_cast<int>(len));
    infile.close();

    stream[len] = '\0';
    return stream;
}

void action_send_message(std::ifstream& infile) {

    char acq_name[] = "testName";
    char acq_description[] = "descriptionTest";
    hs_datalog_set_acquisition_param(DEVICE_ID, acq_name, acq_description);

    vector<vector<bool>> SubsensorIsActive;

    char* data = read_file(infile);
    auto json = nlohmann::json::parse(data);

    auto sensors = json.at("device").at("sensor");
    for (auto const& sensor : sensors) {

        auto sub_sensor_stat = sensor.at("sensorStatus").at("subSensorStatus");
        auto sub_sensor_desc = sensor.at("sensorDescriptor").at("subSensorDescriptor");

        nlohmann::json cmd;
        cmd["command"] = "SET";
        cmd["sensorId"] = sensor.at("id");

        auto stat_iter = std::begin(sub_sensor_stat);
        auto desc_iter = std::begin(sub_sensor_desc);

        for (; stat_iter != sub_sensor_stat.end() &&
               desc_iter != sub_sensor_desc.end();
                ++stat_iter, ++desc_iter) {

            int sub_sensor_id = desc_iter->at("id");
            nlohmann::json params;
            params["id"] = sub_sensor_id;

            for (auto const& [key,val] : stat_iter->items()) {
                params[key] = val;
            }
            cmd["subSensorStatus"].push_back(params);
        }

        int ret = hs_datalog_send_message(
                DEVICE_ID, const_cast<char *>(cmd.dump().data()),
                static_cast<int>(cmd.dump().length()), nullptr, nullptr);

        if (ret == ST_HS_DATALOG_ERROR) {
            cout << "Error occurred while sending message\n";
            cout << "Press any key to exit \n";
            cin.get();
            exit(EXIT_FAILURE);
        }
    }

    /* Update tag list */
    auto tag_hw = json.at("device").at("tagConfig").at("hwTags");
    auto tag_sw = json.at("device").at("tagConfig").at("swTags");

    for (auto const& el : tag_hw) {
        int id = el.at("id");
        string label = el.at("label");
        hs_datalog_set_hw_label(DEVICE_ID, id, &label[0]);

        bool status = el.at("enabled");
        hs_datalog_enable_hw_tag(DEVICE_ID, id, status);
    }

    for (auto const& el : tag_sw) {
        int id = el.at("id");
        string label = el.at("label");
        hs_datalog_set_sw_label(DEVICE_ID, id, &label[0]);
    }

    delete[] data;
}


std::map<std::tuple<int,string>, bool>
action_read_tags() {
    std::map<std::tuple<int,string>, bool> tags;

    char* data;
    hs_datalog_get_available_tags(0, &data);

    auto json = nlohmann::json::parse(std::string(data));
    auto sw_tags = json.at("swTags");

    for (auto const& sw_tag : sw_tags) {
        auto tup = std::make_tuple(sw_tag.at("id"), sw_tag.at("label"));
        tags.insert(std::pair<std::tuple<int, string>, bool>(tup, false));
    }
    delete[] data;

    return tags;
}

int main(int argc, char *argv[])
{
    hs_datalog_initialize();

    cxxopts::Options options("data_logger", "Data Logger CLI");

    options.add_options()
        ("v,version", "Print version information and then exit.")
        ("h,help", "Print usage and then exit.")
        ("f,config", "Device configuration file (JSON).", cxxopts::value<string>())
        ("t,duration", "Duration of the acquisition (seconds).", cxxopts::value<uint32_t>()->default_value("60"))
        ("g,load-config", "Get current device configuration and save it.")
    ;

    auto result = options.parse(argc, argv);
    if (result.count("v")) action_print_version();
    if (result.count("h")) action_print_usage(options.help());
    if (result.count("g")) action_load_and_save_device_config();


    // NOTE: `-f` for the reader of the device_config and `-t` for the duration
    std::ifstream reader;
    if (result.count("f")) {

        string filename = result["f"].as<string>();

        reader.open(filename, std::ios::in | std::ios::binary);
        if (!reader.is_open()) {
            cout << "File not found: " << filename << endl;
            return EXIT_FAILURE;
        }
    }

    uint32_t timeout_seconds = result["t"].as<uint32_t>();

    action_print_device_descriptor();

    auto dict = action_get_available_tag();

    if (reader.is_open()) action_send_message(reader);

    std::map<std::tuple<int,string>, bool> tags;
    if (FEATURE_TAGGING) tags = action_read_tags();

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
