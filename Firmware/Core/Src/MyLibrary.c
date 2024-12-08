/*
 * MyLibrary.c
 *
 *  Created on: Oct 21, 2023
 *      Author: khoad
 */
#include "MyLibrary.h"
#include "main.h"
#include "string.h"
#include "Library_Support.h"

//Initialize System Tick

void Delay_ms(unsigned int time_ms)
{
	tick = 0;
	while(tick < time_ms);
}

void Init_Systick()
{
	Address_VTTB = VTTB_Remove();
	unsigned int* RVR = (unsigned int*)0xE000E014;
	unsigned int* CSR = (unsigned int*)0xE000E010;
	*RVR = (16000/1 - 1);
	*CSR |= (1 << 0)|(1 << 1);
	unsigned int* Address_Sys = (unsigned int*)(Address_VTTB + (int)SYSTICK);
	*Address_Sys = (unsigned int)Systick_Handler | 1;
}


//Setup configure mode for GPIO_X
void Init_GPIO_Config_Mode(unsigned int* PIN,unsigned char* Mode)
{
	Clock(PIN);
	unsigned int* GPIO_X = Identify_GPIO(PIN);
	int pos = Position_PIN(PIN, GPIO_X)*2;
	unsigned int* MODER = (unsigned int*)((int)GPIO_X + 0x00);
	*MODER &= ~(0b11 << pos);
	*MODER |= ((int)Mode << pos);
}
//Setup for output mode
void GPIO_Output_Mode(unsigned int* PIN,Output_mode_t state)
{
	unsigned int* GPIO_X = Identify_GPIO(PIN);
	int pos = Position_PIN(PIN, GPIO_X);
	unsigned int* OTYPER = (unsigned int*)((int)GPIO_X + 0x04);
	*OTYPER &= ~(1 << pos);
	unsigned int* ODR = (unsigned int*)((int)GPIO_X + 0x14);
	*ODR &= ~(1 << pos);
	if (state == LOW)
		*ODR &= ~(1 << pos);
	else
		*ODR |= (1 << pos);
}


//Setup for input mode
void GPIO_Input_Mode(unsigned int* PIN,unsigned char* state)
{
	unsigned int* GPIO_X = Identify_GPIO(PIN);
	int pos = Position_PIN(PIN, GPIO_X)*2;
	unsigned int* PUPDR = (unsigned int*)((int)GPIO_X + 0x0C);
	*PUPDR &= ~(0b11 <<  pos);
	*PUPDR |= ((int)state << pos);
}

//get button signal
char GPIO_Input_get_signal(unsigned int* PIN)
{
	unsigned int* GPIO_X = Identify_GPIO(PIN);
	int pos = Position_PIN(PIN, GPIO_X);
	unsigned int* IDR = (unsigned int*)((int)GPIO_X + 0x10);
	return (*IDR << pos) & 1;
}

//Setup Alternate function
void GPIO_Alternate_Mode(unsigned int* PIN, unsigned int* AF_x)
{
	unsigned int* GPIO_X = Identify_GPIO(PIN);
	int pos = Position_PIN(PIN, GPIO_X);
	if(pos >= 0 && pos <= 7)
	{
		unsigned int* AFRL = (unsigned int*)((int)GPIO_X + 0x20);
		*AFRL |= ((int)AF_x << pos*4);
	}
	else
	{
		unsigned int* AFRH = (unsigned int*)((int)GPIO_X + 0x24);
		*AFRH |= ((int)AF_x << pos*4);
	}
}



//Setup external interrupt
void Init_EXTI_Mode(unsigned int* PIN, unsigned int* Mode, void (*fptr)())
{
	unsigned int* GPIO_X = Identify_GPIO(PIN);
	char temp = (int)PIN - (int)GPIO_X;
	int EXTI_X = 0;
	unsigned int* address = 0;
	EXTICR_X(PIN);

	//Setup EXTI
	if(temp == 0)
	{
		EXTI_X = EXTI0;
		address = EXTI0_AD;
	}
	else if(temp == 1)
	{
		EXTI_X = EXTI1;
		address = EXTI1_AD;
	}
	else if(temp == 2)
	{
		EXTI_X = EXTI2;
		address = EXTI2_AD;
	}
	else if(temp == 3)
	{
		EXTI_X = EXTI3;
		address = EXTI3_AD;
	}
	else if(temp == 4)
	{
		EXTI_X = EXTI4;
		address = EXTI4_AD;
	}
	else if(temp >= 5 && temp <= 9)
	{
		EXTI_X = EXTI5_9;
		address = EXTI5_9_AD;
	}
	else
	{
		EXTI_X = EXTI10_15;
		address = EXTI10_15_AD;
	}
	//Setup interrupt mode
	if(Mode == RISING_EDGE)
	{
		unsigned int* RTSR = (unsigned int*)RISING_EDGE;
		*RTSR |= (1 << temp);
	}
	else
	{
		unsigned int* FTSR = (unsigned int*)FALLING_EDGE;
		*FTSR |= (1 << temp);
	}

	unsigned int* IMR = (unsigned int*)((int)0x40013C00 + 0x00);
	*IMR |= (1 << temp);

	Interrupt_NVIC(address, EXTI_X, fptr);
}

//Function remove Interrupt
void EXTI_escape_Interrupt(unsigned int* PIN)
{
	unsigned int* GPIO_X = Identify_GPIO(PIN);
	char temp = (int)PIN - (int)GPIO_X;
	unsigned int* PR = (unsigned int*)((int)0x40013C00 + 0x14);
	*PR |= (1 << temp);
}


void UART_Send_data(unsigned int* UART_X, char* data)
{
	for(int i = 0; data[i] != '\0'; i++)
	{
		UART_Send_one_byte(UART_X, data[i]);
	}
}

char* UART_data()
{
	UART_Data[sizeof(UART_Data) - 1] = '\0';
	if(UART_index == sizeof(UART_Data) - 1)
		UART_index = 0;
	for(int j = DMA_index; j < sizeof(Data); j++)
	{
		Data[j] = '\0';
	}
	int i = 0;
	for(i = UART_index; UART_Data[i] != '\0'; i++)
	{
		Data[DMA_index] = UART_Data[i];
		DMA_index++;
	}
	for(int i = 0; i < sizeof(UART_Data); i++)
	{
		UART_Data[i] = '\0';
	}
	UART_index = i;
	char* res = Data;
	DMA_index = 0;
	return res;
}

int UART_data_available()
{
	Delay_ms(2000);
	if(UART_Data[UART_index] == '\0')
		return NOT_HAVE_DATA;
	else
		return HAVE_DATA;
}
//Initialize UART
void Init_UART(unsigned int* UART_X, unsigned int Baund_Rate, Uart_mode_t Mode)
{
	unsigned int* v_UART_TX = UART_TX;
	unsigned int* v_UART_RX = UART_RX;
	Init_GPIO_Config_Mode(v_UART_TX, ALTERNATE);
	Init_GPIO_Config_Mode(v_UART_RX, ALTERNATE);
	GPIO_Alternate_Mode(v_UART_TX, AF7);
	GPIO_Alternate_Mode(v_UART_RX, AF7);

	__HAL_RCC_USART2_CLK_ENABLE();
	unsigned int* BRR = (unsigned int*)((int)UART_X + 0x08);
	if(Baund_Rate == 1200)
	{
		*BRR |= (833 << 4)|(5 << 0);
	}
	else if(Baund_Rate == 2400)
	{
		*BRR |= (416 << 4)|(11 << 0);
	}
	else if(Baund_Rate == 9600)
	{
		*BRR |= (104 << 4)|(3 << 0);
	}
	else if(Baund_Rate == 19200)
	{
		*BRR |= (52 << 4)|(1 << 0);
	}
	else if(Baund_Rate == 38400)
	{
		*BRR |= (26 << 4)|(1 << 0);
	}
	else if(Baund_Rate == 57600)
	{
		*BRR |= (17 << 4)|(6 << 0);
	}
	else if(Baund_Rate == 115200)
	{
		*BRR |= (8 << 4)|(11 << 0);
	}
	else if(Baund_Rate == 230400)
	{
		*BRR |= (4 << 4)|(5 << 0);
	}
	else if(Baund_Rate == 460800)
	{
		*BRR |= (2 << 4)|(3 << 0);
	}
	else
	{
		*BRR |= (1 << 4)|(1 << 0);
	}
	unsigned int* CR1 = (unsigned int*)((int)UART_X + 0x0C);
	unsigned int* CR3 = (unsigned int*)((int)UART_X + 0x14);
	if(Mode == SEND_DATA)
	{
		*CR1 |= (1 << 13)|(1 << 3);
	}
	else
	{
		*CR1 |= (1 << 13)|(1 << 2);
		*CR3 |= (1 << 6);
	}
}

void Init_DMA(unsigned int* DMA, int Protocal_Stream, int Protocal_Channel)
{
	unsigned int* DMA_ADDRESS = 0;
	unsigned int DMA_POSITION = 0;
	if(DMA == DMA1_Custom)
	{
		__HAL_RCC_DMA1_CLK_ENABLE();
		if(Protocal_Stream == 0)
		{
			DMA_ADDRESS = DMA1_STREAM0_AD;
			DMA_POSITION = DMA1_STREAM0_Pos;
		}
		else if(Protocal_Stream == 1)
		{
			DMA_ADDRESS = DMA1_STREAM1_AD;
			DMA_POSITION = DMA1_STREAM1_Pos;
		}
		else if(Protocal_Stream == 2)
		{
			DMA_ADDRESS = DMA1_STREAM2_AD;
			DMA_POSITION = DMA1_STREAM2_Pos;
		}
		else if(Protocal_Stream == 3)
		{
			DMA_ADDRESS = DMA1_STREAM3_AD;
			DMA_POSITION = DMA1_STREAM3_Pos;
		}
		else if(Protocal_Stream == 4)
		{
			DMA_ADDRESS = DMA1_STREAM4_AD;
			DMA_POSITION = DMA1_STREAM4_Pos;
		}
		else if(Protocal_Stream == 5)
		{
			DMA_ADDRESS = DMA1_STREAM5_AD;
			DMA_POSITION = DMA1_STREAM5_Pos;
		}
		else if(Protocal_Stream == 6)
		{
			DMA_ADDRESS = DMA1_STREAM6_AD;
			DMA_POSITION = DMA1_STREAM6_Pos;
		}
		else
		{
			DMA_ADDRESS = DMA1_STREAM7_AD;
			DMA_POSITION = DMA1_STREAM7_Pos;
		}
	}
	else
	{
		__HAL_RCC_DMA2_CLK_ENABLE();
		if(Protocal_Stream == 0)
		{
			DMA_ADDRESS = DMA2_STREAM0_AD;
			DMA_POSITION = DMA2_STREAM0_Pos;
		}
		else if(Protocal_Stream == 1)
		{
			DMA_ADDRESS = DMA2_STREAM1_AD;
			DMA_POSITION = DMA2_STREAM1_Pos;
		}
		else if(Protocal_Stream == 2)
		{
			DMA_ADDRESS = DMA2_STREAM2_AD;
			DMA_POSITION = DMA2_STREAM2_Pos;
		}
		else if(Protocal_Stream == 3)
		{
			DMA_ADDRESS = DMA2_STREAM3_AD;
			DMA_POSITION = DMA2_STREAM3_Pos;
		}
		else if(Protocal_Stream == 4)
		{
			DMA_ADDRESS = DMA2_STREAM4_AD;
			DMA_POSITION = DMA2_STREAM4_Pos;
		}
		else if(Protocal_Stream == 5)
		{
			DMA_ADDRESS = DMA2_STREAM5_AD;
			DMA_POSITION = DMA2_STREAM5_Pos;
		}
		else if(Protocal_Stream == 6)
		{
			DMA_ADDRESS = DMA2_STREAM6_AD;
			DMA_POSITION = DMA2_STREAM6_Pos;
		}
		else
		{
			DMA_ADDRESS = DMA2_STREAM7_AD;
			DMA_POSITION = DMA2_STREAM7_Pos;
		}
	}
	unsigned int* DMA_SPAR = DMA_SPAR(DMA, Protocal_Stream);
	if(Protocal_Stream == UART_Stream)
	{
		*DMA_SPAR = (unsigned int)UART_DR;
	}
	unsigned int* DMA_SM0AR = DMA_SM0AR(DMA,Protocal_Stream);
	*DMA_SM0AR = (unsigned int)UART_Data;
	unsigned int* DMA_SNDTR = DMA_SNDTR(DMA, Protocal_Stream);
	*DMA_SNDTR = sizeof(UART_Data);
	unsigned int* DMA_SCR = DMA_SCR(DMA, Protocal_Stream);
	*DMA_SCR |= (Protocal_Channel << 25)|(1 << 10)|(1 << 8)|(1 << 4)|(1 << 0);
	if(Protocal_Stream == UART_Stream)
		Interrupt_NVIC(DMA_ADDRESS, DMA_POSITION, UART_Handler);
}



