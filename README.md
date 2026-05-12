# HD44780 LCD Driver (No RW pin)

A lightweight and stable driver library for alphanumeric displays compatible with the HD44780 standard (e.g., 16x2, 20x4). This project is optimized for ARM Cortex-M microcontrollers and other embedded systems requiring precise timing control.

## Key Features

- Supports both 4-bit and 8-bit interface modes.
- Operates without the RW pin (LCD RW pin must be connected to GND).
- Implementation of Setup Time and Execution Time delays strictly according to the HD44780 datasheet.
- Stable performance on high-speed processors by respecting critical nanosecond timings.
- Integrated integer-to-string conversion for easy numerical display.

## Hardware Configuration (4-bit Mode)


| LCD Pin | Function | Connection |
|:---:|:---:|:---:|
| 1 | VSS | GND |
| 2 | VDD | VCC (5V/3.3V) |
| 3 | V0 | Contrast (Potentiometer) |
| 4 | RS | GPIO Output |
| 5 | RW | GND |
| 6 | E | GPIO Output |
| 11-14| D4-D7 | GPIO Output |

## Getting Started

### 1. Header Configuration
In the `hd44780_no_RW.h` file, uncomment your preferred operating mode:

```c
#define LCD_MODE_4_BIT
// #define LCD_MODE_8_BIT
```

### 2. Implementation Example

```c
#include "hd44780_no_RW.h"

int main(void) {
    // Initialize GPIO bus and LCD controller
    LCD_Init();

    // Set cursor position: row 0, column 0
    LCD_Set_Position(0, 0);

    // Send a string
    LCD_Send_Data("System Ready");

    // Send an integer value
    LCD_Set_Position(1, 0);
    LCD_Send_Int(12345);

    while(1) {
        // Main loop
    }
}
```

## API Reference

- **LCD_Init()**: Executes the full power-on stabilization sequence and function set configuration.
- **LCD_Set_Position(uint8_t row, uint8_t column)**: Addresses the DDRAM to move the cursor to a specific coordinate.
- **LCD_Send_Data(const char* buffer)**: Sends a null-terminated string to the display.
- **LCD_Send_Int(int val)**: Converts an integer to ASCII characters and prints them.
- **LCD_Clear()**: Clears the entire display and resets the cursor to the home position (0,0).

## Requirements

The library requires an external delay function `delay_us(uint32_t microseconds)`, which must provide precise timing with microsecond resolution to satisfy the controller's requirements.

---
Author: silnymaciej  
Date: May 11, 2026
