# TM1637 STM32 Key Scanner Library

A lightweight TM1637 key-scanning library developed for STM32 microcontrollers using STM32 HAL drivers.  
This library allows reading key inputs from a TM1637-based module with precise microsecond timing using hardware timers.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Microcontroller Support](#microcontroller-support)
- [Pin Configuration](#pin-configuration)
- [Functions Available](#functions-available)
- [Dependencies](#dependencies)
- [Integration Guide](#integration-guide)
- [Acknowledgments](#acknowledgments)
- [License](#license)

---

## Overview

This repository contains a custom driver to interface with the TM1637 module for key scanning (not display control) on STM32 devices.  
It was developed to enable reliable user input scanning in low-power embedded projects without relying on ADC-based key scans.

This library was originally designed and tested as part of a larger **STM32-based toy audio playback device**.

---

## Features

- Full key-scanning interface via TM1637
- Microsecond-precision timing using TIM17 hardware timer
- Start/Stop, WriteByte, ReadKey routines implemented
- Non-blocking operation for real-time key reading
- Fully STM32 HAL compliant

---

## Hardware Requirements

- STM32G030F6P6TR or compatible STM32 MCU
- TM1637-based key scanning module
- TIM17 enabled for precise delays

---

## Microcontroller Support

- STM32G0 series (tested)
- Easily portable to other STM32 families using STM32CubeMX

---

## Pin Configuration

| Signal | STM32 Pin | GPIO Port |
|--------|-----------|-----------|
| CLK    | PA11      | GPIOA     |
| DIO    | PA12      | GPIOA     |

*Note: Can be easily reconfigured inside `tm1637.h`*

---

## Functions Available

- `TM1637_Init()`: Initialize TM1637 GPIO pins.
- `TM1637_Start()`: Send start condition.
- `TM1637_Stop()`: Send stop condition.
- `TM1637_WriteByte(uint8_t data)`: Write one byte to TM1637.
- `TM1637_ReadKey()`: Read key press and return raw key value.
- `Delay_us(uint32_t us)`: Microsecond delay using TIM17.

---

## Dependencies

- STM32 HAL Drivers
- TIM17 Timer (used for microsecond delays)

---

## Integration Guide

1. **Hardware Configuration:**
   - Connect TM1637 module to STM32 pins as defined.
   - Enable TIM17 in STM32CubeMX (used for microsecond delays).

2. **Code Integration:**
   - Copy `tm1637.h` and `tm1637.c` into your STM32CubeIDE project.
   - Ensure `tim.h` is properly initialized before calling `TM1637` functions.
   - Call `TM1637_Init()` at startup.

3. **Key Reading Example:**

```c
TM1637_Init();
while (1)
{
    uint8_t key_val = TM1637_ReadKey();
    // Process key_val accordingly
    HAL_Delay(100);
}
