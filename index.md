---
layout: default_c
RefPages:
 - howto_create_A_dev_container
--- 

# What

A minimal yet flexible bare-metal C program for STM32F4-Discovery and related STM32F4 devices.

## ✨ Features

   Built using `make` (no IDE dependency)
-   Demonstrates polymorphic design in C to support multiple independent applications (`app1`, `app2`)
-   Each app can be configured separately to perform its task
-   Demonstrates:
    - USART communication (tested with PuTTY)
    - Blinking LEDs
-   Includes standard C runtime integration (e.g., `malloc`, `printf`, `scanf`) through custom system call implementations

### Flashing & Debugging

-   Uses `st-flash` (from [stlink](https://github.com/stlink-org/stlink)) to program the STM32F4-Discovery
-   Can be debugged with `gdb-multiarch` via OpenOCD
-   Easily integrated with Visual Studio Code or CLI workflows for breakpoint debugging and memory inspection
  - `launch.json` to flash and debug the program
  - `tasks.json` to build and run commands inside the container
---

This project serves as a clean, extensible foundation for low-level STM32 development, showcasing both embedded and software design principles.

## ⚡Getting Started

You can use this container to start programming and experimenting in your local Debian environment.

- Setup instructions for the Docker container, as well as build and development instructions for use with **Visual Studio Code**, can be found here:
  - [local](./Howtos/howto_create_a_dev_container)
  - [remote](https://nicojane.github.io/PHP-Development-Template-Stack/Howtos/project-setup)

##### *Alternative DTS containers can be found here: [remote](https://nicojane.github.io/Docker-Template-Stacks-Home/)*

Version: 0.2
