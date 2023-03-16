# Prophet

This repository holds all the possible applications, tools and templates that we created in the past two years since I started Sensor.ai.
Even the company has been transferred to a successor, still, I want to use some time to finish some unfinished works. Taking this opportunities, this is also a good time for retrospection.

## Todos

- [x] Select a target platform to move features to: [STWIN](https://www.st.com/en/evaluation-tools/steval-stwinkt1.html#tools-software)
- [ ] Use cpp instead of c if possible
    - [ ] Confirm the compatibility of the `gcc-arm-none-eabi`
    - [x] Create a `gcc-arm-none-eabi.cmake` specifically
    - [ ] Make sure the version is correctly defined in the Dockerfile
- [ ] Use CMake to build the build system
    - [ ] Startup file could be c file or assembly file
- [ ] Use Makefile to maintain some useful commandline
- [ ] Use Docker image to maintain the build environment and toolchain
- [ ] Use this one repository to main all the applications
    - [x] Add the application, datalog, to this repo
    - [ ] Add the application, prophet, to this repo

## System headers and warnings
While inspecting compiler output when building your project, you might find that some header file paths include -isystem option right before. Also, in my CMake project template, I call target_include_directories twice. One includes CubeMX drivers only and has an extra SYSTEM option, while other includes all user generated code without the extra option. This SYSTEM options generates -isystem argument for the compiler before giving it a include path. What's up with that?

In short, system paths are already pre-determined by the compiler and it's the reason, why you can just #include <stdio.h> and the compiler will find the file. It has a set of system paths where it will look for the library first. But there is more.
Because such libraries might be old and/or cross platform, some harmless errors might be produced. If you were to use them on your project, you might get tons and tons of useless errors coming from the library and not your code. This is why system libraries get special treatment. This is why ALL warnings, other then #warning ARE IGNORED.

The case of vendor provided libraries is much the same. They might not be developed with such strict error checking as your project; which I advise. C++ warnings regarding casting -Wuseless-cast and -Wold-style-cast dominate the warning output (try removing SYSTEM from include directory for CubeMX and see the output). Specifying CubeMX headers as system clears them of useless errors and allows us to use strict error checking on user code without affecting system libraries.
