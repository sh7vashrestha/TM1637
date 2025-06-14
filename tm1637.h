/*
 * TM1637 Key Scanner Library for STM32
 * Author: Shiva Shrestha
 * Electronics Engineer, Yarsa Tech
 */

#ifndef TM1637_H
#define TM1637_H

#include "stm32g0xx_hal.h" 

// User-configurable GPIO Pins
#define TM1637_CLK_PIN    GPIO_PIN_11
#define TM1637_CLK_PORT   GPIOA
#define TM1637_DIO_PIN    GPIO_PIN_12
#define TM1637_DIO_PORT   GPIOA

// Macros for Pin Control
#define CLK_HIGH   HAL_GPIO_WritePin(TM1637_CLK_PORT, TM1637_CLK_PIN, GPIO_PIN_SET)
#define CLK_LOW    HAL_GPIO_WritePin(TM1637_CLK_PORT, TM1637_CLK_PIN, GPIO_PIN_RESET)
#define DIO_HIGH   HAL_GPIO_WritePin(TM1637_DIO_PORT, TM1637_DIO_PIN, GPIO_PIN_SET)
#define DIO_LOW    HAL_GPIO_WritePin(TM1637_DIO_PORT, TM1637_DIO_PIN, GPIO_PIN_RESET)
#define DIO_READ   HAL_GPIO_ReadPin(TM1637_DIO_PORT, TM1637_DIO_PIN)

// Function Prototypes
void TM1637_Init(void);
void TM1637_Start(void);
void TM1637_Stop(void);
void TM1637_WriteByte(uint8_t data);
uint8_t TM1637_ReadKey(void);
void Delay_us(uint32_t us);

#endif 
