.PHONY: all build cmake run cleat
############################### Native Makefile ###############################

SHELL := /bin/bash
PROJECT_NAME ?= data_logger
BUILD_DIR ?= build
EXECUTABLE := $(BUILD_DIR)/$(PROJECT_NAME)

PLATFORM = $(if $(OS),$(OS),$(shell uname -s))
ifeq ($(PLATFORM),Windows_NT)
    BUILD_SYSTEM ?= MinGW Makefiles
else
    ifeq ($(PLATFORM),Linux)
        BUILD_SYSTEM ?= Unix Makefiles
    else
        @echo "Unsuported platform"
        exit 1
    endif
endif

all: build

build: cmake
	$(MAKE) -C $(BUILD_DIR) --no-print-directory

cmake: $(BUILD_DIR)/Makefile

$(BUILD_DIR)/Makefile: CMakeLists.txt
	cmake \
		-G "$(BUILD_SYSTEM)" \
		-B$(BUILD_DIR) \
		-DPROJECT_NAME=$(PROJECT_NAME)

run: build dev_config.json
	$(EXECUTABLE) -f ./DeviceConfig.json -t 100

clean:
	rm -rf $(BUILD_DIR)

