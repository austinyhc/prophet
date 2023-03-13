# Prophet

This repository holds all the possible applications, tools and templates that we created in the past two years since I started Sensor.ai.
Even the company has been transferred to a successor, still, I want to use some time to finish some unfinished works. Taking this opportunities, this is also a good time for retrospection.

## Todos

- [x] Select a mcu level device to move features to: [STWIN](https://www.st.com/en/evaluation-tools/steval-stwinkt1.html#tools-software)
- [ ] Use cpp instead of c if possible
    - [ ] Confirm the compatibility of the `gcc-arm-none-eabi`
    - [x] Create a `gcc-arm-none-eabi.cmake` specifically
    - [ ] Make sure the version is correctly defined in the Dockerfile
- [ ] Use CMake to build the build system
    - [ ] Startup file could be c file or assembly file
- [ ] Use Makefile to maintain some useful commandline
- [ ] Use Docker image to maintain the build environment and toolchain
- [ ] Use this one repository to main all the applications
    - [ ] Add the application, datalog, to this repo
    - [ ] Add the application, prophet, to this repo

- [ ] Include paths (-I)
```xml
<listOptionValue builtIn="false" value="../../../Inc"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/BSP/Components/stts751"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/BSP/Components/hts221"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/BSP/Components/lps22hh"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/BSP/Components/iis2mdc"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/BSP/Components/ism330dhcx"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/BSP/Components/lps22hb"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/BSP/Components/iis2dh"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/BSP/Components/iis3dwb"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/BSP/Components/Common"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/BSP/STWIN"/>
<listOptionValue builtIn="false" value="../../../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/SensorStreaming_WCID/Inc"/>
<listOptionValue builtIn="false" value="../../../../../../../Middlewares/ST/STM32_USB_Device_Library/CoreWCID/Inc"/>
<listOptionValue builtIn="false" value="../../../../../../../Middlewares/Third_Party/FatFs/src"/>
<listOptionValue builtIn="false" value="../../../../../../../Middlewares/Third_Party/FatFs/src/drivers"/>
<listOptionValue builtIn="false" value="../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F"/>
<listOptionValue builtIn="false" value="../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS"/>
<listOptionValue builtIn="false" value="../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/include"/>
<listOptionValue builtIn="false" value="../../../../../../../Middlewares/ST/Audio/C/lib/inc"/>
<listOptionValue builtIn="false" value="../../../../../../../Middlewares/Third_Party/parson"/>
<listOptionValue builtIn="false" value="../../../../../../../Drivers/CMSIS/Include"/>
```

- [ ] Define symbols (-D)
```xml
<listOptionValue builtIn="false" value="STM32L4R9xx"/>
<listOptionValue builtIn="false" value="USE_HAL_DRIVER"/>
<listOptionValue builtIn="false" value="ARM_MATH_CM4"/>
<listOptionValue builtIn="false" value="USE_HAL_DFSDM_REGISTER_CALLBACKS"/>
<listOptionValue builtIn="false" value="USE_HAL_ADC_REGISTER_CALLBACKS"/>
<listOptionValue builtIn="false" value="USE_HAL_SAI_REGISTER_CALLBACKS"/>
<listOptionValue builtIn="false" value="USE_HAL_SPI_REGISTER_CALLBACKS"/>
<listOptionValue builtIn="false" value="USE_HAL_I2C_REGISTER_CALLBACKS"/>
```




