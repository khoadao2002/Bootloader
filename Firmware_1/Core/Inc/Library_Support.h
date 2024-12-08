/*
 * Library_Support.h
 *
 *  Created on: Oct 22, 2023
 *      Author: khoad
 */
#include "main.h"
#include "MyLibrary.h"
#ifndef INC_LIBRARY_SUPPORT_H_
#define INC_LIBRARY_SUPPORT_H_

unsigned int Address_VTTB = 0;
unsigned int tick = 0;
char UART_Data[128];
char Data[128];
int UART_index = 0;
int DMA_index = 0;

unsigned int VTTB_Remove()
{
	//Remove Vector table from FLASH to SRAM
	unsigned int* Flash = (unsigned int*)0x00;
	memcpy((void*)0x20000000, Flash, (unsigned int)0x198);
	unsigned int* VTOR = (unsigned int*)0xE000ED08;
	*VTOR = (unsigned int)0x20000000;
	return *VTOR;
}

void Systick_Handler()
{
	tick++;
	unsigned int* CSR = (unsigned int*)0xE000E010;
	*CSR &= ~(1 << 16);
}

unsigned int* Identify_GPIO(unsigned int* PIN)
{
	unsigned int* GPIO_X = 0;
	if (PIN >= PA0 && PIN <= PA15)
	{
		GPIO_X = (unsigned int*)GPIOA_t;
	}
	else if (PIN >= PB0 && PIN <= PB15)
	{
		GPIO_X = (unsigned int*)GPIOB_t;
	}
	else if (PIN >= PC0 && PIN <= PC15)
	{
		GPIO_X = (unsigned int*)GPIOC_t;
	}
	else if (PIN >= PD0 && PIN <= PD15)
	{
		GPIO_X = (unsigned int*)GPIOD_t;
	}
	else if (PIN >= PE0 && PIN <= PE15)
	{
		GPIO_X = (unsigned int*)GPIOE_t;
	}
	else if (PIN == PH0 || PIN == PH1)
	{
		GPIO_X = (unsigned int*)GPIOH_t;
	}
	return GPIO_X;
}
//Find position of pin in register
int Position_PIN(unsigned int* PIN, unsigned int* GPIO_X)
{
	int delta = (int)PIN - (int)GPIO_X;
	int pos = delta / 64;
	return pos;
}
//Create Clock for GPIO
void Clock(unsigned int* PIN)
{
	if(PIN >= PA0 && PIN <= PA15)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
	}
	else if(PIN >= PB0 && PIN <= PB15)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
	}
	else if(PIN >= PC0 && PIN <= PC15)
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
	}
	else if(PIN >= PD0 && PIN <= PD15)
	{
		__HAL_RCC_GPIOD_CLK_ENABLE();
	}
	else if(PIN >= PE0 && PIN <= PE15)
	{
		__HAL_RCC_GPIOE_CLK_ENABLE();
	}
	else
	{
		__HAL_RCC_GPIOH_CLK_ENABLE();
	}
}
void Interrupt_NVIC(unsigned int* address, int position, void (*fptr)())
{
	if(position >= 0 && position <= 31)
	{
		unsigned int* NVIC0 = NVIC_ISER0;
		*NVIC0 |= (1 << (position - 0));
	}
	else if(position >= 32 && position <= 63)
	{
		unsigned int* NVIC1 = NVIC_ISER1;
		*NVIC1 |= (1 << (position - 32));
	}
	else if(position >= 64 && position <= 95)
	{
		unsigned int* NVIC2 = NVIC_ISER2;
		*NVIC2 |= (1 << (position - 64));
	}
	unsigned int* Address_EXTI = (unsigned int*)(Address_VTTB + (int)address);
	*Address_EXTI = (unsigned int)(fptr) | 1;
}

//Choose EXTICR corresponding Port need to implement
void EXTICR_X(unsigned int* PIN)
{
	Init_GPIO_Config_Mode(PIN, INPUT);
	unsigned int* GPIO_X = Identify_GPIO(PIN);
	char temp = (int)PIN - (int)GPIO_X;
	if(temp >= 0 && temp <= 3)
	{
		unsigned int* EXTICR1 = (unsigned int*)((int)0x40013800 + 0x08);
		*EXTICR1 &= ~(0b1111 << (temp * 4));
		if(GPIO_X == GPIOA_t)
			*EXTICR1 &= ~(0b1111 << (temp * 4));
		else if(GPIO_X == GPIOB_t)
			*EXTICR1 |= (0b0001 << (temp * 4));
		else if(GPIO_X == GPIOC_t)
			*EXTICR1 |= (0b0010 << (temp * 4));
		else if(GPIO_X == GPIOD_t)
			*EXTICR1 |= (0b0011 << (temp * 4));
		else if(GPIO_X == GPIOE_t)
			*EXTICR1 |= (0b0100 << (temp * 4));
		else
			*EXTICR1 |= (0b0111 << (temp * 4));
	}
	else if(temp >= 4 && temp <= 7)
	{
		unsigned int* EXTICR2 = (unsigned int*)((int)0x40013800 + 0x0C);
		*EXTICR2 &= ~(0b1111 << (temp * 4));
		if(GPIO_X == GPIOA_t)
			*EXTICR2 &= ~(0b1111 << (temp * 4));
		else if(GPIO_X == GPIOB_t)
			*EXTICR2 |= (0b0001 << (temp * 4));
		else if(GPIO_X == GPIOC_t)
			*EXTICR2 |= (0b0010 << (temp * 4));
		else if(GPIO_X == GPIOD_t)
			*EXTICR2 |= (0b0011 << (temp * 4));
		else if(GPIO_X == GPIOE_t)
			*EXTICR2 |= (0b0100 << (temp * 4));
		else
			*EXTICR2 |= (0b0111 << (temp * 4));
	}
	else if(temp >= 8 && temp <= 11)
	{
		unsigned int* EXTICR3 = (unsigned int*)((int)0x40013800 + 0x10);
		*EXTICR3 &= ~(0b1111 << (temp * 4));
		if(GPIO_X == GPIOA_t)
			*EXTICR3 &= ~(0b1111 << (temp * 4));
		else if(GPIO_X == GPIOB_t)
			*EXTICR3 |= (0b0001 << (temp * 4));
		else if(GPIO_X == GPIOC_t)
			*EXTICR3 |= (0b0010 << (temp * 4));
		else if(GPIO_X == GPIOD_t)
			*EXTICR3 |= (0b0011 << (temp * 4));
		else if(GPIO_X == GPIOE_t)
			*EXTICR3 |= (0b0100 << (temp * 4));
		else
			*EXTICR3 |= (0b0111 << (temp * 4));
	}
	else
	{
		unsigned int* EXTICR4 = (unsigned int*)((int)0x40013800 + 0x14);
		*EXTICR4 &= ~(0b1111 << (temp * 4));
		if(GPIO_X == GPIOA_t)
			*EXTICR4 &= ~(0b1111 << (temp * 4));
		else if(GPIO_X == GPIOB_t)
			*EXTICR4 |= (0b0001 << (temp * 4));
		else if(GPIO_X == GPIOC_t)
			*EXTICR4 |= (0b0010 << (temp * 4));
		else if(GPIO_X == GPIOD_t)
			*EXTICR4 |= (0b0011 << (temp * 4));
		else if(GPIO_X == GPIOE_t)
			*EXTICR4 |= (0b0100 << (temp * 4));
		else
			*EXTICR4 |= (0b0111 << (temp * 4));
	}
}

//Send data
void UART_Send_one_byte(unsigned int* UART_X, char data)
{
	unsigned int* DR = (unsigned int*)((int)UART_X + 0x04);
	unsigned int* SR = (unsigned int*)((int)UART_X +0x00);
	while(((*SR >> 7)&1) != 1);
	*DR = data;
	while(((*SR >> 6)&1) != 1);
}


void UART_Handler()
{
	int i = 0;
	for(i = UART_index; i < sizeof(UART_Data); i++)
	{
		Data[DMA_index] = UART_Data[i];
		DMA_index++;
	}
	for(int j = UART_index; j < sizeof(UART_Data) - 1; j++)
	{
		UART_Data[j] = '\0';
	}
	UART_index = i - 1;
	unsigned int* DMA_HIFCR = (unsigned int*)((int)DMA1_Custom + 0x0C);
	*DMA_HIFCR |= (1 << 11);
}


#endif /* INC_LIBRARY_SUPPORT_H_ */
