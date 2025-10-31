---
layout: default_c
RefPages:
 - howto_create_A_dev_container
---

<span class="nje-br"> </span>

# STM32 <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  Docker bare-metal C/C++ project Container</span>

## ℹ️ Introduction

This project sets up a Linux (Debian) container running on Docker Desktop for Windows, tailored for **STM32 MCU development**. It uses the **STM32 ST-Link** to flash programs to the device. ***Example*** startup programs are included for the **STM32F4-Discovery** board.

### ✨ Features

- Minimal yet flexible bare-metal C/C++ projects for STM32F4-Discovery and related STM32F4 devices, showing:
  - Custom **linker script** usage
  - How **startup** code integrates with the linker script
  - Implementation of C system calls for functions like `printf()` and `scanf()`
  - A working `USART` (serial interface) for serial input\output (e.g., PuTTY)
  - Use of memory-mapped hardware registers
  - Built using make (no IDE dependency, Visual Studio Code supported)
  - C project template (***./projects/project-1_c***)   
    - Demonstrates polymorphic design in C to support multiple independent applications (`app1`, `app2`) Where each app can be configured wit different device initialization code or application initalization code
    - Demonstrates:
      - USART communication (tested with PuTTY)
      - Blinking LEDs
      - Includes standard C runtime integration (e.g., `malloc`, `printf`, `scanf`) through custom system call implementations
  - C++ project template (***./projects/project-1_cpp***)      
    - Same basic functionality as the C project. Startup code in C; the rest in C++
    - Improved Makefile
    - Utility to display include dependencies
  - Preconfigured **Visual Studio Code files** (***see paragraph 4***)
    - `launch.json` to flash and debug the program
    - `tasks.json` to build and run commands inside the container

---

## ⚙️ Build and configure the container

### 🛠️ Build  container

To build the docker container enter the root folder of the **STM32F4 project** and execute the following command:
<pre class="nje-cmd-one-line"> docker-compose up --build</pre>
<span class="nje-expect-indent1">This should create and start the container.</span>


### 🔌 Steps to expose the USB device to WSL

To connect the host USB to the Docker container, we must ensure the USB device is accessible inside the WSL environment. Since Docker Desktop uses WSL, once it's visible there, it will also be available to the Docker container.

> **Note**{: style="color: black;font-size:13px; "}
> <small>You only need to do this if the USB device is **not yet attached to WSL**. There's no need to reattach it after every reboot unless it detaches.  <br></small>

**List USB Devices (in PowerShell)**{: style="color:green; "} <br>
To expose the USB device from Windows to WSL, we use the utility driver **usbipd-win**. Open an **Administrator PowerShell** and run:

<pre class="nje-cmd-one-line">usbipd list</pre>
<span class="nje-expect-indent1"> This should return something like: ***STM#@ DTLINK (i.e: 3-3)    # 3-3 is your BUSID***</span>

> **Note**{: style="color: black;font-size:13px; "}
> <small> When `usbipd` is not installed, download  it from [usbipd-win GitHub Releases]( https://github.com/dorssel/usbipd-win/releases)  <br></small>

**Attach the USB to the WSL**{: style="color:green; "} <br>
First, identify which WSL distro is used by Docker Desktop:

<pre class="nje-cmd-one-line">Docker Desktop → Settings → Resources → WSL Integration</pre>
<span class="nje-expect-indent1"> This should return something like: **Ubuntu-docker-App-X11-Win32Dev***</span>

Then, in an **Administrator PowerShell**, use the commands below. Replace the `BUSID` (e.g., 3-3) and the WSL distro name with the ones you found earlier:

<pre class="nje-cmd-multi-line">
usbipd bind --busid 3-3    # 1e share the BUS ID device
usbipd attach --wsl Ubuntu-docker-App-X11-Win32Dev --busid  3-3
</pre>
<span class="nje-expect-indent1"> Running `usbipd list` again should show: ***STATE: Attached***</span>


<details class="nje-remark-box">
  <summary> Is USB connected, disconnect USB (WSL/VSC)
  </summary>
  
  **Check the USB status**  
- Start the WSL
  - `wsl -d Ubuntu-docker-App-X11-Win32Dev  # Also use: wsl -l`
  - Or start a terminal from within Visual Studio Code (see section 4) and run:
  - `lsusb`
    - If lsusb is not available, install it: `apt-get install usbutils`
  Expected output: ***'Bus 001 Device 002: ID 0483:3748 STMicroelectronics ST-LINK/V2'***
  -for more details run:
    - `dmesg | grep -i usb`

**Detach the USB**  
From Admin **PowerShell**:

- `usbipd detach --busid <BUSID>`

</details>
<br />

---

## ⚡ Build and flash the program

This section describes a few commands to manually test the environment using the Docker CLI.  
The actual development workflow is intended to be used from **Visual Studio Code** (see Section 4), which provides the same functionality and much more.

### ⚙️ Build the sample project111

In the directory: **/workspace/Projects/Project** execute the following command:  
<pre class="nje-cmd-one-line" style="margin-left: 0px;">make</pre>
<span class="nje-expect">`make` should return <b>Successfully finished...</b> and has created a new <b>./bin</b> directory with the binary results </span>

### 🛠️ Manual Debug

From a CLI terminal inside the Docker container, run:
<pre class="nje-cmd-one-line" style="margin-left: 0px;">st-info --probe </pre>
<span class="nje-expect"> This should return: **Found 1 stlink programmer** along with some additional information. </span>

In a **new** Docker CLI terminal, start OpenOCD to listen for debugger (GDB) connections:
<pre class="nje-cmd-one-line"  style="margin-left: 0px;">openocd -f interface/stlink.cfg -f target/stm32f4x.cfg`  *NOT NEED VSC DOES THIS IMPLICITE!* </pre>
<span class="nje-expect">You should see: **Info : Listening on port 3333 for gdb connections** and OpenOCD waits for GDB commands</span>

<details class="nje-warn-box">
  <summary>No Need for it in VS Code
  </summary>
  This command is **not needed** when using Visual Studio Code, it is done automatically. Running this manually while debugging in VS Code will cause an error
</details>

<span class="nje-br"> </span>

In **another terminal** (inside the container), from the **./bin** directory, run:
<pre class="nje-cmd-one-line" style="margin-left: 0px;">gdb-multiarch project.elf  </pre>

Then inside the debugger, you can execute command like these:
<pre class="nje-cmd-multi-line" style="margin-left: 0px;">
(gdb) target remote localhost:3333
(gdb) load
(gdb) monitor reset init
(gdb) monitor reset run # Leaves the program running after quit command, wait
(gdb) continue  
</pre>

To exit the debuger and rest the controller
<pre class="nje-cmd-multi-line" style="margin-left: 0px;">
(gdb) monitor reset halt    # reset device
(gdb) detach                # leave debug session
(gdb) quit  
</pre>

Other sample
<pre class="nje-cmd-multi-line" style="margin-left: 0px;">
(gdb) target remote localhost:3333
(gdb) load
(gdb) monitor reset init
(gdb) break main
(gdb) use 'step'  and other debug commands ....  
(gdb) monitor reset run
(gdb) CTRL-X -> Exit # Program is flashed, manually reset(button) device to run it 
</pre>

> 💡 For more commands and usage tips, consult the official GDB documentation online.

### 🔦 Manual Flash

To manually flash your device you can use make, Run:
<pre class="nje-cmd-one-line">make burn</pre>
<span class="nje-br"> </span>

<details class="nje-remark-box">
  <summary>Burn with Window ST-Link Utility
  </summary>
  When for a reason the above flash fails or your unsure it went well you can docnload ths STM32 utility andflash the program with it. Use the file open command, select the **.bin** file that was created with the ***make*** file  and, select the oprion **Program and Verify** this should load the program, verify it and after that reset the device so it start to run(there are some settings that control this so make sure to check these!)
</details>
<br />

---

## <img src="https://upload.wikimedia.org/wikipedia/commons/9/9a/Visual_Studio_Code_1.35_icon.svg" alt="VS Code" width="16" height="16">  Visual code

Make sure the following **extensions** are installed and activated (inside the container):

- C/C++ Extention Pack (ms-vscode.cpptools)
- Remote- containers 
- Cortex-Debug (OpenOCD) (marus25.cortex-debug)
- Make file tools(ms-vscode.makefile-tools)
- Arm Assembly (dan-c-underwood.arm)
- live server, optional for html content and images (ritwickdey.LiveServer)

### <img src="https://www.docker.com/wp-content/uploads/2022/03/Moby-logo.png" alt="Docker" width="20" height="20"> Open container

- Press `F1` and choose: **Remote-Containers: Attach to Running Container**
- Select: **stm32-dev-vxx**

### 📁 Open the following folder inside the container

Two projects are provided:

- `/workspace/code-files/projects/project-1_c`  
A sample C project
- `/workspace/code-files/projects/project-1_cpp`  
A sample C++ Project

### 🛠️ Build the Project

Use `Terminal -> Run Task...` in Visual Studio Code to access available `make` tasks.  
These tasks are named starting with **STM32-**.

### 🐞 Debug the Project

The launch file in `.vscode/launch.json` is already configured. To debug:

- Ensure **OpenOCD** is **not** running manually — Visual Studio Code will start it automatically.
- Press `F5` to start debugging. You should see something like this in the Debug Console:

<pre class="nje-cmd-multi-line">
make burn
ortex-Debug: VSCode debugger extension version 1.12.1 git(652d042). Usage info: https://github.com/Marus/cortex-debug#usage
"configuration": {
    "name": "Debug STM32",
    "type": "cortex-debug",
    "request": "launch",
    "servertype": "openocd"
    ...
</pre>

---

<details>
<summary class="clickable-summary"> <span class="summary-icon"></span>
    <span style="color: #097df1ff; font-size: 26px;">Appendix I</span> <span style="color: #409EFF; font-size: 16px; font-style: italic;"> -  Use the USART for input and output. </span>
</summary>

This implementation supports input and output via the STM32's serial interface.You can use a terminal application like PuTTY to interact with the device on the host.

➡️ or more details, see the separate document accessible:  

- [here local](DebugOutputTo_USART2)
- [here remote](https://nicojane.github.io/STM32F4/Howtos/DebugOutputTo_USART2)

</details>

<br>
<sub> This file is part of: **STM32 Template Stack**
Copyright (c) 2025 Nico Jan Eelhart. This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree. _Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html
</sub>
<br><br>
<p align="center">─── ✦ ───</p>