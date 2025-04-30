
# What

A minimal yet flexible bare-metal C/C++ project for **STM32F4-Discovery** and related STM32F4 devices.

## ✨ Features

  - Built using `make` (IDE-independent, with Visual Studio Code task support).
  - C Project (***./projects/project-1_c***)   
  - Polymorphic design in C to support multiple independent applications (`app1`, `app2`)
    - Each app can be configured separately to perform its task
    - Demonstrates:
      - USART communication (tested with PuTTY)
      - Blinking LEDs
      - Integration of the standard C runtime (e.g., `malloc`, `printf`, `scanf`) through custom system call implementations
  - C++ Project (***./projects/project-1_cpp***)
    - Same basic functionality as the C project. Startup code in C; the rest in C++
    - Improved Makefile
    - Utility to display include dependencies

### Flashing & Debugging

-   Uses `st-flash` (from [stlink](https://github.com/stlink-org/stlink)) to program the STM32F4-Discovery
-   Can be debugged with `gdb-multiarch` via OpenOCD
-   Easily integrated with Visual Studio Code or CLI workflows for breakpoint debugging and memory inspection
  - `launch.json` to flash and debug the program
  - `tasks.json` to build and run commands inside the container

This project serves as a clean, extensible foundation for low-level STM32 development, showcasing both embedded and software design principles.

## ⚡Getting Started

You can use this **Docker** container(Debian) to start developing your device application.

- Instructions for setting up the Docker container and using it with Visual Studio Code can be found here:
  - [local](./Howtos/howto_create_a_dev_container)
  - [remote](https://nicojane.github.io/PHP-Development-Template-Stack/Howtos/project-setup)

<br>

---
###### *Alternative DTS containers can be found here: [remote](https://nicojane.github.io/Docker-Template-Stacks-Home/)*
