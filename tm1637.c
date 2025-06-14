#include "tm1637.h"
#include "tim.h"  // Use TIM17 for microsecond delays

void Delay_us(uint32_t us)
{
    __HAL_TIM_SET_COUNTER(&htim17, 0);
    while (__HAL_TIM_GET_COUNTER(&htim17) < (us * 40)); 
}

void TM1637_Start(void)
{
    CLK_HIGH;
    DIO_HIGH;
    Delay_us(2);
    DIO_LOW;
}

void TM1637_Ask(void)
{
    CLK_LOW;
    Delay_us(5);
    while (DIO_READ);
    CLK_HIGH;
    Delay_us(2);
    CLK_LOW;
}

void TM1637_Stop(void)
{
    CLK_LOW;
    Delay_us(2);
    DIO_LOW;
    Delay_us(2);
    CLK_HIGH;
    Delay_us(2);
    DIO_HIGH;
}

void TM1637_WriteByte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        CLK_LOW;
        (data & 0x01) ? DIO_HIGH : DIO_LOW;
        Delay_us(3);
        data >>= 1;
        CLK_HIGH;
        Delay_us(3);
    }
}

void TM1637_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = TM1637_CLK_PIN | TM1637_DIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(TM1637_CLK_PORT, &GPIO_InitStruct);
}

uint8_t TM1637_ReadKey(void)
{
    uint8_t key = 0;

    TM1637_Start();
    TM1637_WriteByte(0x42);
    TM1637_Ask();
    DIO_HIGH;

    for (int i = 0; i < 8; i++)
    {
        CLK_LOW;
        key >>= 1;
        Delay_us(30);
        CLK_HIGH;
        if (DIO_READ)
            key |= 0x80;
        Delay_us(30);
    }

    TM1637_Ask();
    TM1637_Stop();

    return key;
}
