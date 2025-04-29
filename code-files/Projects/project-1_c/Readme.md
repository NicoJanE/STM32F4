# What
    
A minimal yet flexible bare-metal C program for STM32F4-Discovery and related STM32F4 devices.

-   Built using `make` (no IDE dependency)
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

---

This project serves as a clean, extensible foundation for low-level STM32 development, showcasing both embedded and software design principles.
