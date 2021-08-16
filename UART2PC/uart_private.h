/********************************************************************/
/* Author	   :	Mohamed Abd El-Naby								*/
/* Date		   :	15 Aug 2021										*/
/* Version	   :	V01												*/
/* Description :	Private UART Frame							*/
/********************************************************************/
#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_





#define PORTA	0
#define PORTB	1
#define PORTC	2
#define PORTD	3
#define PORTE	4
#define PORTF	5








/******************************* UART Base Address ******************************/

#define UART0_BASE_ADDRESS	0x4000C000
#define UART1_BASE_ADDRESS	0x4000D000
#define UART2_BASE_ADDRESS	0x4000E000
#define UART3_BASE_ADDRESS	0x4000F000
#define UART4_BASE_ADDRESS	0x40010000
#define UART5_BASE_ADDRESS	0x40011000
#define UART6_BASE_ADDRESS	0x40012000
#define UART7_BASE_ADDRESS	0x40013000
#define UARTx_CLK_BASE_ADDRESS  0x400FE000
#define	GPIO_CLK_BASE_ADDRESS 	0x400FE000

#define PORTA_BASE_ADDRESS	0x40004000
#define PORTB_BASE_ADDRESS	0x40005000
#define PORTC_BASE_ADDRESS	0x40006000
#define PORTD_BASE_ADDRESS	0x40007000
#define PORTE_BASE_ADDRESS	0x40024000
#define PORTF_BASE_ADDRESS	0x40025000


#define NVIC_BASE_ADDRESS	 0xE000E100

/******************************* UARTx Offesets ******************************/
#define UARTDR_OFFSET	0x000 
#define UARTRSR_OFFSET	0x004	 
#define UARTECR_OFFSET	0x004 
#define UARTFR_OFFSET	0x018
#define UARTILPR_OFFSET	0x020

#define UARTIBRD_OFFSET	0x024
#define UARTFBRD_OFFSET	0x028
#define UARTLCRH_OFFSET	0x02C
#define UARTCTL_OFFSET	0x030
#define UARTIFLS_OFFSET	0x034
#define UARTIM_OFFSET	0x038
#define UARTRIS_OFFSET	0x03C
#define UARTMIS_OFFSET	0x040
#define UARTICR_OFFSET	0x044
#define UARTDMACTL_OFFSET	0x048
#define UART9BITADDR_OFFSET	0x0A4
#define UART9BITAMASK_OFFSET	0x0A8

#define UARTPP_OFFSET	0xFC0
#define UARTCC_OFFSET	0xFC8

#define RCGCUART_OFFSET	0x618

#define RCGCGPIO_OFFSET	0x608
#define GPIODEN_OFFSET	0x51C
#define GPIOAFSEL_OFFSET 0x420
#define GPIOPCTL_OFFSET 0x52C


/******************************* Used UARTx Reg ******************************/
// Enable/Disable UART
#define UARTx_RCGCUART	*((volatile u32 * ) (UARTx_CLK_BASE_ADDRESS+RCGCUART_OFFSET))
#define UARTx_RCGCGPIO	*((volatile u32 * ) (GPIO_CLK_BASE_ADDRESS+RCGCGPIO_OFFSET))
#define GPIOADEN		*((volatile u32 * ) (PORTA_BASE_ADDRESS+GPIODEN_OFFSET))
#define GPIOAFSEL		*((volatile u32 * ) (PORTA_BASE_ADDRESS+GPIOAFSEL_OFFSET))
#define GPIOPCTL		*((volatile u32 * ) (PORTA_BASE_ADDRESS+GPIOPCTL_OFFSET))
#define UART0IBRD		*((volatile u32 * ) (UART0_BASE_ADDRESS+UARTIBRD_OFFSET))
#define UART0FBRD		*((volatile u32 * ) (UART0_BASE_ADDRESS+UARTFBRD_OFFSET))
#define UART0CTL		*((volatile u32 * ) (UART0_BASE_ADDRESS+UARTCTL_OFFSET))
#define UARTL0CRH		*((volatile u32 * ) (UART0_BASE_ADDRESS+UARTLCRH_OFFSET))
#define UART0FR			*((volatile u32 * ) (UART0_BASE_ADDRESS+UARTFR_OFFSET))
#define UART0DR 		*((volatile u32 * ) (UART0_BASE_ADDRESS+UARTDR_OFFSET))
#define UART0IM			*((volatile u32 * ) (UART0_BASE_ADDRESS+UARTIM_OFFSET))
#define UART0ICR		*((volatile u32 * ) (UART0_BASE_ADDRESS+UARTICR_OFFSET))
#define UART0RIS		*((volatile u32 * ) (UART0_BASE_ADDRESS+UARTRIS_OFFSET))
#define UART0LCRH		*((volatile u32 * ) (UART0_BASE_ADDRESS+UARTRIS_OFFSET))




/*	IRQs	*/
 void __vector_5(void) __attribute__(( signal , used ));



#endif