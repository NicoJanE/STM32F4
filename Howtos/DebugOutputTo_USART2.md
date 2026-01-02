---
layout: default_c
RefPages:
 - howto_create_A_dev_container
---

# Debug Output in Terminal via USART

## 1 Output

To display (debug) output to a terminal, on your host, there are 3 functions defined in the file: `\startup-code\syscalls.c`

1. `USART_Init(...)`
1. `_write_impl_USART_SendChar(...)`
1. `_write(...)`

When `USART2_Init(...)` is called during the initialization phase of your program, you can use standard output functions such as:

```C
printf("Debug this variable: %s\r\n",var1);     // Note the \r\n instead of just \n
puts("Enter function: HelloWorld()\r\n ");
```

The output will appear in a terminal emulator like **PuTTY**, provided the hardware and serial connection are correctly configured.

📍 More documentation can be found in the above meantioned `syscalls.c` file.

## 2 Input

Just like output above the `syscalls.c` also implements the system function: `int _read(...)` which makes sure you can ask for input in your **PuTTy** terminal with scanf function or by calling the function direct.

``` bash
char name[50];   
unsigned  len = 50;    
_read(0, name, len);        // CR Return will end the input
```

## 3 Configure PuTTY

Assuming the files are already part of your project, and you're using the STM32F4-Discovery board (or a compatible one):

1. **Hardware Requirements**:
    - Make sure you have a ***USB-to-TTL Serial Cable*** (USB connector on one side and four lose connectors on the otherside, ***see remark*** below)

1. **Wiring**: Connect the USB-to-TTL cable between your host and the STM32 board:

    - USB-to-TTL TX → STM32 PA3 (USART2 RX) (White)
    - USB-to-TTL RX → STM32 PA2 (USART2 TX) (Green)
    - GND → GND (black)
    - Power → NOT needed (red)

1. **Make the connection**

    -  On the Host (Windows)
        - Locate the used COM port number using **Windows Device manager**
        - In the Host start **Putty** and configure it:
        - set the connection type to: **serial**
        - enter the **COM Port number**
        - specify the speed: **9600**

Once everything is connected and the program runs, output from the device will appear in the terminal.

<br>

>Remark
>
>I used a cable like:
[Exactly this](https://www.kiwi-electronics.com/nl/usb-naar-ttl-seriele-kabel-cp2102-381) 
( [alternative 1](https://www.amazon.nl/CP2102-ap-207-Seri%C3%ABle-Wirelss-Toegangspunt/dp/B0CJX6VH5K)
[alternative 2](https://www.amazon.nl/AZDelivery-Converter-HW-598-compatibel-Inclusief/dp/B089QJZ51Z) )
>
>In Device Manager it shows up like: **Silicon Labs CP210x usa to UART Bridge (COM3)**
<br>

<span style="color: #6d757dff; font-size: 13px; font-style: italic;"> 
<i><b>License</b><br>This file is part of: **STM32 Template Stack**  Copyright (c) 2025-2026 Nico Jan Eelhart.This repository is [MIT licensed](MIT-license.md) and free to use. For optional commercial support, customization, training, or long-term maintenance, see [COMMERCIAL.md](COMMERCIAL.md).</i>
</span>

<br>
<p align="center">─── ✦ ───</p>
