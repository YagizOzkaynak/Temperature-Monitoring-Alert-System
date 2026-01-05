# Temperature-Monitoring-Alert-System
NTC temperature monitoring and alarm system with LCD and LED display, developed using PlatformIO and AVR C.

Project Overview

    Description: This project is an AVR-based embedded system that monitors real-time temperature using an NTC thermistor and provides multi-level visual, audible, and serial feedback.

    Platform: Developed using PlatformIO on VS Code.

    Microcontroller: ATmega328P (Arduino Uno).

Key Features

    Sensory Input: High-accuracy temperature calculation using the Steinhart-Hart equation via ADC.

    Visual Interface: Real-time temperature display on a 16x2 HD44780 LCD.

    Status Indicators: 3-stage LED alert system (Green, Blue, Red).

    Audio Warning: Active buzzer integration for critical temperature levels (>50°C).

    Serial Communication: Detailed status reports sent via UART to the Serial Monitor at 9600 baud.

Temperature Logic

    Normal (0-25°C): Green LED – System stable.

    Warning (25-50°C): Green + Blue LED – Temperature rising.

    Danger (>50°C): All LEDs + Buzzer – Critical alert.

Hardware Connections

    Port B Pins:

        PB2: Green LED

        PB3: Blue LED

        PB4: Red LED

        PB5: Buzzer

    ADC: NTC Thermistor connected to the analog input.

    LCD: Connected via standard 4-bit or 8-bit parallel interface.
