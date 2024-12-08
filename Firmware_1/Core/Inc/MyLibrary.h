/*
 * MyLibrary.h
 *
 *  Created on: Oct 21, 2023
 *      Author: khoad
 */

#ifndef MYLIBRARY_H_
#define MYLIBRARY_H_

#define GPIOA_t (unsigned  int*)0x40020000
#define GPIOB_t (unsigned  int*)0x40020400
#define GPIOC_t (unsigned  int*)0x40020800
#define GPIOD_t (unsigned  int*)0x40020C00
#define GPIOE_t (unsigned  int*)0x40021000
#define GPIOH_t (unsigned  int*)0x40021C00

//Pin of GPIOA
#define PA0 (unsigned  int*)0x40020000
#define PA1 (unsigned  int*)0x40020040
#define PA2 (unsigned  int*)0x40020080
#define PA3 (unsigned  int*)0x400200C0
#define PA4 (unsigned  int*)0x40020100
#define PA5 (unsigned  int*)0x40020140
#define PA6 (unsigned  int*)0x40020180
#define PA7 (unsigned  int*)0x400201C0
#define PA8 (unsigned  int*)0x40020200
#define PA9 (unsigned  int*)0x40020240
#define PA10 (unsigned  int*)0x40020280
#define PA11 (unsigned  int*)0x400202C0
#define PA12 (unsigned  int*)0x40020300
#define PA13 (unsigned  int*)0x40020340
#define PA14 (unsigned  int*)0x40020380
#define PA15 (unsigned  int*)0x400203C0

//Pin of GPIOB
#define PB0 (unsigned  int*)0x40020400
#define PB1 (unsigned  int*)0x40020440
#define PB2 (unsigned  int*)0x40020480
#define PB3 (unsigned  int*)0x400204C0
#define PB4 (unsigned  int*)0x40020500
#define PB5 (unsigned  int*)0x40020540
#define PB6 (unsigned  int*)0x40020580
#define PB7 (unsigned  int*)0x400205C0
#define PB8 (unsigned  int*)0x40020600
#define PB9 (unsigned  int*)0x40020640
#define PB10 (unsigned  int*)0x40020680
#define PB11 (unsigned  int*)0x400206C0
#define PB12 (unsigned  int*)0x40020700
#define PB13 (unsigned  int*)0x40020740
#define PB14 (unsigned  int*)0x40020780
#define PB15 (unsigned  int*)0x400207C0

//Pin of GPIOC
#define PC0 (unsigned  int*)0x40020800
#define PC1 (unsigned  int*)0x40020840
#define PC2 (unsigned  int*)0x40020880
#define PC3 (unsigned  int*)0x400208C0
#define PC4 (unsigned  int*)0x40020900
#define PC5 (unsigned  int*)0x40020940
#define PC6 (unsigned  int*)0x40020980
#define PC7 (unsigned  int*)0x400209C0
#define PC8 (unsigned  int*)0x40020A00
#define PC9 (unsigned  int*)0x40020A40
#define PC10 (unsigned  int*)0x40020A80
#define PC11 (unsigned  int*)0x40020AC0
#define PC12 (unsigned  int*)0x40020B00
#define PC13 (unsigned  int*)0x40020B40
#define PC14 (unsigned  int*)0x40020B80
#define PC15 (unsigned  int*)0x40020BC0

//Pin of GPIOD
#define PD0 (unsigned  int*)0x40020C00
#define PD1 (unsigned  int*)0x40020C40
#define PD2 (unsigned  int*)0x40020C80
#define PD3 (unsigned  int*)0x40020CC0
#define PD4 (unsigned  int*)0x40020D00
#define PD5 (unsigned  int*)0x40020D40
#define PD6 (unsigned  int*)0x40020D80
#define PD7 (unsigned  int*)0x40020DC0
#define PD8 (unsigned  int*)0x40020E00
#define PD9 (unsigned  int*)0x40020E40
#define PD10 (unsigned  int*)0x40020E80
#define PD11 (unsigned  int*)0x40020EC0
#define PD12 (unsigned  int*)0x40020F00
#define PD13 (unsigned  int*)0x40020F40
#define PD14 (unsigned  int*)0x40020F80
#define PD15 (unsigned  int*)0x40020FC0

//Pin of GPIOE
#define PE0 (unsigned  int*)0x40021000
#define PE1 (unsigned  int*)0x40021040
#define PE2 (unsigned  int*)0x40021080
#define PE3 (unsigned  int*)0x400210C0
#define PE4 (unsigned  int*)0x40021100
#define PE5 (unsigned  int*)0x40021140
#define PE6 (unsigned  int*)0x40021180
#define PE7 (unsigned  int*)0x400211C0
#define PE8 (unsigned  int*)0x40021200
#define PE9 (unsigned  int*)0x40021240
#define PE10 (unsigned  int*)0x40021280
#define PE11 (unsigned  int*)0x400212C0
#define PE12 (unsigned  int*)0x40021300
#define PE13 (unsigned  int*)0x40021340
#define PE14 (unsigned  int*)0x40021380
#define PE15 (unsigned  int*)0x400213C0

//Pin of GPIOH
#define PH0 (unsigned  int*)0x40021C00
#define PH1 (unsigned  int*)0x40021C40

//Choose Input mode
#define FLOATING (unsigned char*)0b00
#define PULL_UP (unsigned char*)0b01
#define PULL_DOWN (unsigned char*)0b10

//Choose GPIO state
#define INPUT (unsigned char*)0b00
#define OUTPUT (unsigned char*)0b01
#define ALTERNATE (unsigned char*)0b10
#define ANALOG (unsigned char*)0b11

//Choose AF_X
#define AF0 (unsigned int*)0b0000
#define AF1 (unsigned int*)0b0001
#define AF2 (unsigned int*)0b0010
#define AF3 (unsigned int*)0b0011
#define AF4 (unsigned int*)0b0100
#define AF5 (unsigned int*)0b0101
#define AF6 (unsigned int*)0b0110
#define AF7 (unsigned int*)0b0111
#define AF8 (unsigned int*)0b1000
#define AF9 (unsigned int*)0b1001
#define AF10 (unsigned int*)0b1010
#define AF11 (unsigned int*)0b1011
#define AF12 (unsigned int*)0b1100
#define AF13 (unsigned int*)0b1101
#define AF14 (unsigned int*)0b1110
#define AF15 (unsigned int*)0b1111

//EXTI Mode
#define RISING_EDGE (unsigned int*)((int)0x40013C00 + 0x08)
#define FALLING_EDGE (unsigned int*)((int)0x40013C00 + 0x0C)

//Vector table at position
#define EXTI0 6
#define EXTI1 7
#define EXTI2 8
#define EXTI3 9
#define EXTI4 10
#define EXTI5_9 23
#define EXTI10_15 40
#define UART_pos 38

//Vector table at address
#define EXTI0_AD (unsigned int*)0x00000058
#define EXTI1_AD (unsigned int*)0x0000005C
#define EXTI2_AD (unsigned int*)0x00000060
#define EXTI3_AD (unsigned int*)0x00000064
#define EXTI4_AD (unsigned int*)0x00000068
#define EXTI5_9_AD (unsigned int*)0x0000009C
#define EXTI10_15_AD (unsigned int*)0x000000E0
#define UART_ad (unsigned int*)0x000000D8

//NVIC_ISER
#define NVIC_ISER0 (unsigned int*)0xE000E100
#define NVIC_ISER1 (unsigned int*)0xE000E104
#define NVIC_ISER2 (unsigned int*)0xE000E108
#define NVIC_ISER3 (unsigned int*)0xE000E10C
#define NVIC_ISER4 (unsigned int*)0xE000E110
#define NVIC_ISER5 (unsigned int*)0xE000E114
#define NVIC_ISER6 (unsigned int*)0xE000E118
#define NVIC_ISER7 (unsigned int*)0xE000E11C

//Address System tick
#define SYSTICK (unsigned int*)0x0000003C

//Define pin for UART
#define UART (unsigned int*)0x40004400
#define UART_TX PA2
#define UART_RX PA3
#define HAVE_DATA 1
#define NOT_HAVE_DATA 0
#define UART_DR (unsigned int*)0x40004404

//DMA
#define DMA1_Custom (unsigned int*)0x40026000
#define DMA2_Custom (unsigned int*)0x40026400
#define UART_Stream 5
#define UART_Channel 4
#define DMA_SPAR(DMA, Protocal_Stream) (unsigned int*)((int)DMA + 0x18 + (0x18 * Protocal_Stream))
#define DMA_SM0AR(DMA, Protocal_Stream) (unsigned int*)((int)DMA + 0x1C + (0x18 * Protocal_Stream))
#define DMA_SNDTR(DMA, Protocal_Stream) (unsigned int*)((int)DMA + 0x14 + (0x18 * Protocal_Stream))
#define DMA_SCR(DMA, Protocal_Stream) (unsigned int*)((int)DMA + 0x10 + (0x18 * Protocal_Stream))

//Address and position of DMA1
#define DMA1_STREAM0_AD (unsigned int*)0x0000006C
#define DMA1_STREAM1_AD (unsigned int*)0x00000070
#define DMA1_STREAM2_AD (unsigned int*)0x00000074
#define DMA1_STREAM3_AD (unsigned int*)0x00000078
#define DMA1_STREAM4_AD (unsigned int*)0x0000007C
#define DMA1_STREAM5_AD (unsigned int*)0x00000080
#define DMA1_STREAM6_AD (unsigned int*)0x00000084
#define DMA1_STREAM7_AD (unsigned int*)0x000000FC

#define DMA1_STREAM0_Pos (unsigned int)11
#define DMA1_STREAM1_Pos (unsigned int)12
#define DMA1_STREAM2_Pos (unsigned int)13
#define DMA1_STREAM3_Pos (unsigned int)14
#define DMA1_STREAM4_Pos (unsigned int)15
#define DMA1_STREAM5_Pos (unsigned int)16
#define DMA1_STREAM6_Pos (unsigned int)17
#define DMA1_STREAM7_Pos (unsigned int)47

//Address and position of DMA1
#define DMA2_STREAM0_AD (unsigned int*)0x00000120
#define DMA2_STREAM1_AD (unsigned int*)0x00000124
#define DMA2_STREAM2_AD (unsigned int*)0x00000128
#define DMA2_STREAM3_AD (unsigned int*)0x0000012C
#define DMA2_STREAM4_AD (unsigned int*)0x00000130
#define DMA2_STREAM5_AD (unsigned int*)0x00000150
#define DMA2_STREAM6_AD (unsigned int*)0x00000154
#define DMA2_STREAM7_AD (unsigned int*)0x00000158

#define DMA2_STREAM0_Pos (unsigned int)56
#define DMA2_STREAM1_Pos (unsigned int)57
#define DMA2_STREAM2_Pos (unsigned int)58
#define DMA2_STREAM3_Pos (unsigned int)59
#define DMA2_STREAM4_Pos (unsigned int)60
#define DMA2_STREAM5_Pos (unsigned int)68
#define DMA2_STREAM6_Pos (unsigned int)69
#define DMA2_STREAM7_Pos (unsigned int)70
//Choose output status
typedef enum
{
	LOW, HIGH
}Output_mode_t;

typedef enum
{
	SEND_DATA, RECEIVE_DATA
}Uart_mode_t;

//Create Delay function by System tick
void Delay_ms(unsigned int time_ms);
void Init_Systick();

//Configuration for GPIO
void Init_GPIO_Config_Mode(unsigned int* PIN, unsigned char* Mode);
void GPIO_Output_Mode(unsigned int* PIN, Output_mode_t state);
void GPIO_Alternate_Mode(unsigned int* PIN, unsigned int* AF_x);
void GPIO_Input_Mode(unsigned int* PIN, unsigned char* state);
char GPIO_Input_get_signal(unsigned int* PIN);

//Configuration for External Interrupt
void Init_EXTI_Mode(unsigned int* PIN, unsigned int* Mode, void (*fptr)());
void EXTI_escape_Interrupt(unsigned int* PIN);

//Configuration for UART
void Init_UART(unsigned int* UART_X, unsigned int Baund_Rate, Uart_mode_t Mode);
void UART_Send_data(unsigned int* UART_X, char* data);
char* UART_data();
int UART_data_available();

//Configuration DMA
void Init_DMA(unsigned int* DMA, int Protocal_Stream, int Protocal_Channel);

#endif /* MYLIBRARY_H_ */
