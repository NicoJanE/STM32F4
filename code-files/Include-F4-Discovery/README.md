<small>
<br><br>
_This file is part of: **STM32F4 Template Stack**_
_Copyright (c) 2025 Nico Jan Eelhart_
_This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree._
<br><br>
_Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_
</small>
<br><br>

# What

These are the specific header for the **STM32F4-Disccovery** board. <br>
Copied from the CMSIS (***.\CMSIS\Device\ST\STM32F4xx\Include\\***) for your reference when creating bare-metal applications you may consult these files.

- **stm32f4xx.h**  is the umbrella header
- **stm32f407xx.h** is device-specific details (included conditionally)

```C
#define STM32F407xx     // Define your target MCU, will automatically include the umbrella header(generic) 
#include "stm32f4xx.h"
```


<br><br>
Note: **STM32 CMSIS / HAL Header Files**

These header files above  are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to: https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html
