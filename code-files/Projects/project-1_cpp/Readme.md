# What
    
A minimal yet flexible **bare-metal C++** project (`project-1_cpp`) for the STM32F4-Discovery board and related STM32F4 devices.

-   Built using `make` (no IDE dependency; **Visual Studio Code supported**)
-   Demonstrates the use of **C++ classes** after program startup via C-based initialization.
-   Behaves similarly to the C version (project-1_c), refer to that documentation for more background.
-   Includes several improvements over the C project:
    - Enhanced `Makefile` supporting both C and C++ with cleaner, more informative output (give it a try!)
    - `src_doc/` folder with a script to visualize include dependencies
    - Improved Visual Studio Code **tasks** and debug **launch configurations**

### Flashing & Debugging

-   Uses `st-flash` (from [stlink](https://github.com/stlink-org/stlink)) to program the STM32F4-Discovery
-   Can be debugged with `gdb-multiarch` via OpenOCD
-   Easily integrated with Visual Studio Code or CLI workflows for breakpoint debugging and memory inspection

---

This project serves as a clean, extensible foundation for low-level STM32 development, demonstrating both **embedded programming** and **modern C++ design** principles.
