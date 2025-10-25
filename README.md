
# STM32 <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  Docker bare-metal C/C++ project Container</span>

## ℹ️ Introduction

A minimal yet flexible bare-metal C/C++ project for **STM32F4-Discovery** and related STM32F4 devices.

### ✨ Features

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

- Uses `st-flash` (from [stlink](https://github.com/stlink-org/stlink)) to program the STM32F4-Discovery
- Can be debugged with `gdb-multiarch` via OpenOCD
- Easily integrated with Visual Studio Code or CLI workflows for breakpoint debugging and memory inspection
  - `launch.json` to flash and debug the program
  - `tasks.json` to build and run commands inside the container

This project serves as a clean, extensible foundation for low-level STM32 development, showcasing both embedded and software design principles.

## ⚡Getting Started

This project serves as a clean, extensible foundation for low-level STM32 development, showcasing both embedded and software design principles.You can use this container to start programming and experimenting in your local Debian environment.

### *Setup instructions [here](https://nicojane.github.io/STM32F4/Howtos/howto_create_A_dev_container)*

Here the information for the Docker container, as well as build and development instructions for use with **Visual Studio Code**, can be found. <sub> [click here for local](./Howtos/howto_create_a_dev_container)  </sub>

<br>

<p align="center">
  <a href="https://nicojane.github.io/Docker-Template-Stacks-Home/">
    <img src="assets/images/DTSfooter.svg" alt="DTS Template Stacks" width="400" />
  </a>
</p>

<sub> This file is part of:  *STM32 Template Stack*
Copyright (c) 2025 Nico Jan Eelhart. This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree. 
</sub>

<p align="center">─── ✦ ───</p>