/* 

This file is part of: **STM32F4 Template Stack**_
Copyright (c) 2025 Nico Jan Eelhart_
This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
 
Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_	    */


/*
    When you use standard C functions like printf() or malloc(), the linker looks for low-level 
    system call implementations (e.g., _write(), _sbrk(), _fstat()).

    If these are missing, the linker uses weak stub implementations from `nosys.specs`, 
    which typically do nothing or return errors.

    By providing your own `syscalls.c`, you override these stubs with working versions 
    tailored for your platform (e.g., using USART for _write, defining a heap for _sbrk, etc.).

    To ensure proper linking, make sure the Makefile includes the C standard library:

        LDFLAGS += -nostartfiles -lc -lm -lgcc

    This allows linking against Newlib (-lc), but still uses your custom startup code 
    and syscall implementations.            */



// System include files required

//#include "syscalls.h"     // This also works for the makefile(the build), but VSC intelisense requires a defintion in ./vscode/c_cpp_properties.json
//                             See also comments at point 2 in the ./makefile
#include "system/c-implementation/syscalls.h"
 #include "system/startup-code/registers.h"

// Use standard C files with C linkage guards for compatibility
#ifdef __cplusplus
extern "C" 
{
#endif        
    #include <sys/stat.h>
    #include <errno.h>
    #include <unistd.h>
#ifdef __cplusplus
}
#endif

/*  
    Support for new and delete C++ operators, see documentation in header.

    Create new objects in C++ for objects that need to persist through the whole program's 
    runtime. These are objects that will live for the duration of the program and be 
    cleared only by a reset. 

    Do not create new objects for short-lived objects. For such temporary objects, 
    consider using:
      - Stack objects (automatic variables).
      - A dynamic memory pool for managed memory allocations.                               */

/*  Te handle                                                                               */
void *__dso_handle = (void*)&__dso_handle;
/*  Dummy implementation: register destructors (we ignore them).                            */
int __cxa_atexit(void (*func)(void*), void *arg, void *dso) 
{
  (void)func; (void)arg; (void)dso;
   return 0;
}
/* Dummy implementation: finalize destructors (we ignore them).                             */
void __cxa_finalize(void *dso) 
{
  (void)dso;
}


/* Private implementation functions                                         */
static int  _write_impl_USART2_SendChar(char c);  


void *_sbrk(int incr) {
    char *prev_heap_end =heap_end;
    char *new_heap_end = heap_end + incr;

    // Ensure heap does not grow into the stack
    if (new_heap_end >= (char*)&__StackTop) {
        errno = ENOMEM;
        return (void *)-1;  // Not enough memory
    }

    heap_end = new_heap_end;
    return (void *)prev_heap_end;
}


void SystemClock_Config(void) {
    /* Enable HSI (High-Speed Internal clock)                   */
    RCC->CR |= (1 << 0);            /* Set HSION bit            */
    while (!(RCC->CR & (1 << 1)));  /* Wait until HSIRDY is set */

    /* Select HSI as the system clock                           */
    RCC->CFGR &=    ~(0x3U <<0);    /* Clear SW bits, SAME: RCC->CFGR &=    ~0b00000011;  // Same but more readable, Not supported in C11 then use this as documentation? */
    RCC->CFGR |= (0x0 << 0);        /* Set SW bits to 00 (HSI)  */

    /* Wait until HSI is used as the system clock               */
    while (((RCC->CFGR >> 2) & 0x3) != 0);
    
}

void delay2(uint32_t delayTime) {
    volatile uint32_t count;
    for (count = 0; count < delayTime; count++) {
        /* Empty loop for delay */
    }
}


void USART2_Init(void) {
    
    #define F_CLK 16000000U
    #define BAUD  9600U    
    SystemClock_Config();    
    
    /* 1. Enable clocks for GPIOA and USART2                    */
    RCC->AHB1ENR |= (1 << 0);       /* Bit 0: GPIOAEN           */
    RCC->APB1ENR |= (1 << 17);      /* Bit 17: USART2EN or use: #define USART2EN (1 << 17)  */
        
    /* 2. Set PA2 and PA3 to Alternate Function mode (10)       */
    GPIOA->MODER &= ~((3U << (2 * 2)) | (3U << (3 * 2)));       /* Clear bits               */
    GPIOA->MODER |=  (2U << (2 * 2)) | (2U << (3 * 2));         /* Set to AF mode           */

    /* 3. Set Alternate Function 7                              */
    /* Set AF7 (USART2) for PA2, PA3 BEFORE enabling USART      */
    uint32_t afr_mask = (0xF << (4U * 2U)) | (0xF << (4U * 3U));
    GPIOA->AFRL &= ~(afr_mask);
    GPIOA->AFRL |=  (7U << (4U * 2U)) | (7U << (4U * 3U));      /* AF7 for USART2           */
    delay2(1000);                                               /* Optional: give GPIO state time to stabilize before enabling USART */

    /* Configure USART2.                                        */
    USART->CR1 = 0;             /* Disable USART2 before configuration                      */
    //USART2_BRR = 0x8A;        /* Set baud rate (16 MHz / 115200 = approx 138.88 = 0x8A)   */
    USART->BRR = (F_CLK / BAUD);/* 9600 baud SAVE Baudrate, with less change for 'GARBAGE' issus  9600 baud at 16 MHz   */
    USART->CR1 |= (1 << 3);     /* TE (Transmitter Enable)                                  */
    USART->CR1 |= (1 << 2);     /* RE (Receiver Enable)                                     */
    USART->CR1 |= (1 << 13);    /* UE (USART Enable)                                        */

    /* Disable buffering for stdout, WARNING! without this printf() will not work if it does not contain("\r\n")    */
    setvbuf(stdout, NULL, _IONBF, 0);   
    
}

      
/* Used by _write       */
static int _write_impl_USART2_SendChar(char c) {
    int timeout = 100000;              /* Arbitrary large timeout value    */
    while (!(USART->SR & (1 << 7))) {   /* Wait for TXE                     */
        if (--timeout == 0) {
            /* Handle timeout (e.g., return an error or reset USART)        */
            return -99;
        }
    }
    USART->DR = c;
    return 0;
}

/*
 Send a character to USART2, for displaying,  using:

 1) STM32 Virtual COM Port Driver (Specific to STM32  ST-LINK/V2-1, warning: Not available on ST-LINK/V2 )
      - See\install:  https://www.st.com/en/development-tools/stsw-stm32102.html
      - Restart
      - Power-shell -> mode -> check if COM port is available
      - Open COM port with a terminal program (e.g., PuTTY, Tera Term). Baud Rate = 115200 and connect to COM port

 2) OR
 2.1 Or use a 'External USB-to-Serial Adapter' and connect:
         FTDI TX → STM32 PA3 (USART2 RX)
         FTDI RX → STM32 PA2 (USART2 TX)
 2.2 Or use a 'USB-to-TTL Serial Cable' and connect: (more generic)
         CONNECT
         - USB-to-TTL TX → STM32 PA3 (USART2 RX) (White)
         - USB-to-TTL RX → STM32 PA2 (USART2 TX) (Green) 
         - GND → GND (black)
         - Power → NOT needed (red)
         HOST terminal
         - locate COM port number (Windows device manager)
         - start putty -> , COM port number, Speed:115200, Connection type: Serials
*/
int _write(int file, char *ptr, int len) 
{
    int res = -1;
    if (file == STDOUT_FILENO || file == STDERR_FILENO) {
        for (int i = 0; i < len; i++) {
            res = _write_impl_USART2_SendChar(ptr[i]);
        }
        return len;
    }
    
     return res;
}

/*
 Not preffered, slow, complexity(interaction with debugger and host)

 Alternative _write function for UART thta uses semihosting only for prinff
 this those make sure that semihosting is not used for malloac and other system functions
 This requires:
        "openOCDLaunchCommands": [
    "monitor arm semihosting enable"
  ]
 in the launch.json file
,
int _write(int file, char *ptr, int len) {
    if (file == STDOUT_FILENO || file == STDERR_FILENO) {
        asm volatile (
            "mov r0, #1\n"  // SYS_WRITE0 (stdout)
            "mov r1, %0\n"  // Pointer to string
            "bkpt #0xAB\n"
            :
            : "r" (ptr)
            : "r0", "r1"
        );
        return len;
    }
    errno = EIO;
    return -1;
}
*/

/* Make sure the terminal (USART) screen is cleared     */
void Clear(void) 
{
    printf("\033[2J\033[H");
}


/* Make sure we can receive input from the USART, each input char, will be send back to the terminal (USART)    */
#define USART_SR_RXNE   (1 << 5)        /* RXNE is at bit 5 in USART_SR                             */
#define USART_SR_TXE    (1 << 7)        /* TXE is at bit 7 in USART_SR (Transmitter Empty flag)     */
int _read(int file, char *ptr, int len) 
{
    for (int i = 0; i < len; i++) 
    {        
        while (!(USART->SR & USART_SR_RXNE)) ;  /* Wait for RXNE (Receive Data Register Not Empty)              */
        ptr[i] =(char) USART->DR;

        while (!(USART->SR & USART_SR_TXE)) ;   /* Wait for TXE (transmitter ready)                             */
        USART->DR = ptr[i];                     /* Echo, send the character back via USART                      */

        if (ptr[i] == '\r'  || ptr[i] == '\n')  /* Check for carriage return or newline                         */
        {  
            /*  Question is here OPTION 1 set the ptr[i] character to '\0' and adjust the length(return the length by reference)
                Or OPTION 2 set the charter staring from  ptr[i] till ptr[len-1] to '\0' and Dont change the length.
                Here we use Option 2. for efficiency you coiuld pursaw option 1 */
            for(int j = i; j < len; j++) 
                ptr[j] = '\0';                  /* Set the rest of the buffer to null                           */
        
            _write_impl_USART2_SendChar('\n');  /* Send newline character                                       */
            break;
        }
        else if(i == len-1)   /* Add Null-terminate chars when buffer is full and no newline character is found */
        {
            ptr[len-1] = '\0';  
            _write_impl_USART2_SendChar('\n'); 
        }
    }
    return len;
}


/* No implementation , yet added when required */
int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}


/* No implementation , yet added when required */
int _isatty(int file) {
    return 1;
}


// NewLib (standard C library) how the heap is initialized
// https://llvm-gcc-renesas.com/wiki/index.php?title=How_does_Newlib_initialize_the_heap%3F
