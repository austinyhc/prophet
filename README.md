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
