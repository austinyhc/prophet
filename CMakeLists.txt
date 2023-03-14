# STM32 Minimal CMake project for C/C++ projects
cmake_minimum_required(VERSION 3.12)
###############################################################################

include(./gcc-arm-none-eabi.cmake)

# Set project name and some defaults
if ("${PROJECT_NAME}" STREQUAL "")
    set(PROJECT_NAME prophet)
endif()

project(${PROJECT_NAME})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set debug mode as default
if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()
message("Build type: ${CMAKE_BUILD_TYPE}")

# Set microcontroller information
set(MCU_FAMILY stm32l4xx)
set(MCU_MODEL STM32L4R9xx)
set(BOARD_MODEL STWIN)

set(CPU_PARAMETERS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard)

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/app/${PROJECT_NAME}/startup_stm32l4r9xx.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/app/${PROJECT_NAME}/stm32l4r9zitx_flash.ld)

###############################################################################
set(EXECUTABLE ${CMAKE_PROJECT_NAME})

enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
set(CMAKE_CXX_EXTENSIONS ON)
###############################################################################

set(DRIVER_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/app/${PROJECT_NAME}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/app/${PROJECT_NAME}/HSDCore/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/hal/${MCU_FAMILY}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/hal/${MCU_FAMILY}/inc/Legacy
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/board/${BOARD_MODEL}
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/components/common
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/components/stts751
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/components/hts221
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/components/lps22hh
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/components/iis2mdc
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/components/ism330dhcx
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/components/lps22hb
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/components/iis2dh
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/components/iis3dwb
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/cpu
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/cmsis
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/st/STM32_USB_Device_Library/Class/SensorStreaming_WCID/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/st/STM32_USB_Device_Library/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/st/BlueNRG-2/includes
	${CMAKE_CURRENT_SOURCE_DIR}/middleware/st/BlueNRG-2/utils
	${CMAKE_CURRENT_SOURCE_DIR}/middleware/st/BlueNRG-2/hci/hci_tl_patterns/Basic
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/third_party/FatFs/src
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/third_party/FatFs/src/drivers
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/third_party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/third_party/FreeRTOS/Source/CMSIS_RTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/third_party/FreeRTOS/Source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/third_party/parson)

set(PROJECT_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE DRIVER_SOURCES CONFIGURE_DEPENDS
    # ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/st/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/third_party/FatFs/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/third_party/FreeRTOS/Source/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/third_party/FreeRTOS/CMSIS_RTOS/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/third_party/FreeRTOS/Source/portable/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/third_party/parson/*.c)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app/${PROJECT_NAME})
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    ${PROJECT_DIR}/*.cpp
    ${PROJECT_DIR}/*.c)

add_executable(${EXECUTABLE}
    ${DRIVER_SOURCES}
    ${PROJECT_SOURCES}
    ${STARTUP_SCRIPT})

target_compile_definitions(${EXECUTABLE} PRIVATE
    #$<$<CONFIG:Debug>:DEBUG>
    ${MCU_MODEL}
    USE_HAL_DRIVER
    ARM_MATH_CM4
    USE_HAL_DFSDM_REGISTER_CALLBACKS
    USE_HAL_ADC_REGISTER_CALLBACKS
    USE_HAL_SAI_REGISTER_CALLBACKS
    USE_HAL_SPI_REGISTER_CALLBACKS
    USE_HAL_I2C_REGISTER_CALLBACKS
    USE_HAL_TIM_REGISTER_CALLBACKS
    ONBOARD_DIGITAL_MIC)

target_include_directories(${EXECUTABLE} SYSTEM PRIVATE
    ${DRIVER_INCLUDE_DIRECTORIES})

target_include_directories(${EXECUTABLE} PRIVATE
    ${PROJECT_INCLUDE_DIRECTORIES})
###############################################################################
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wdouble-promotion
    -Wformat=2 -Wformat-truncation
    -Wundef
    -fno-common
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wconversion
        -Wno-volatile
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override>
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0>)

target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    $<$<VERSION_GREATER:$<C_COMPILER_VERSION>,10.3.1>:-Wl,--no-warn-rwx-segments>
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage)
###############################################################################

# The last command can take a couple of seconds on larger project, usefull for debugging
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin)

option(DUMP_ASM "Create full assembly of final executable" OFF)
if (${DUMP_ASM})
    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -D -C $<TARGET_FILE:${EXECUTABLE}> > ${EXECUTABLE}.s)
endif()

