## Configuration before compile 
### uart_config.h File :
you must add CPU Frequency in this form 8MHz = 8000000UL
```c
#define F_CPU			8000000UL
```

## Development :  
| Function Name | Usage |  Parameter | return |
| ------ | ------ |  ------ |  ------ |
| UART_voidInit()  | Initialize UART Parameters .|`UART_CHANNEL channel` - <a href="#UART_CHANNEL">channel</a> <br /> `u16 copy_u16BaudRate` - <a href="#UART_BaudRate">BaudRate</a> <br /> `UART_PARITY Parity` - <a href="#UART_PARITY">Parity</a> <br /> `UART_STOPBIT stopBitType` - <a href="#UART_STOPBIT">stopBitType</a><br /> `UART_FIFO FIFO_mode` - <a href="#UART_FIFOMode">FIFO_mode</a><br /> `u8 copy_u8FrameLength` - <a href="#UART_FrameLength">copy_u8FrameLength</a><br />|`void`|
| UART_voidControl()  | Control UARTx Disablle or Enable. |`UART_CHANNEL channel` - <a href="#UART-CHANNEL">channel</a> <br />`u8 copy_u8State` - <a href="#UART_Control"> copy_u8State</a> <br />| `void`|
| UARTx_charReceiverSynch()  | receive data `Synchronously` in u8 . |`UART_CHANNEL channel` - <a href="#UART-CHANNEL">channel</a> | `u8`|
| UARTx_charReceiverAsynch()  | receive data `Asynchronously` in pointer to function execute when receiving done. |`UART_CHANNEL channel` - <a href="#UART-CHANNEL">channel</a> <br/> `void(*callBack)(u8)` - Pointer to Function receiving data in u8 parameter  | `void`|
| UARTx_voidTransmitterSynch()  | transmit  data `Synchronously` using u8 parameter. |`UART_CHANNEL channel` - <a href="#UART-CHANNEL">channel</a> <br/> `char TransmittedData` - char to be transmit. | `void`|
| UARTx_voidTransmitterAsynch()  | transmit  data `Asynchronously` in pointer to function execute when transmit successfully. |`UART_CHANNEL channel` - <a href="#UART-CHANNEL">channel</a> <br/> `char TransmittedData` - char to be transmit. <br/> `void(*callBack)(void)` - Pointer to Function execute after transmit data successfully.   | `void`|




### UART_CHANNEL
| Parameter Name | Description |  RX Pin |  TX Pin |
| ------ | ------ |  ------ | ------ | 
| UART1 | For UART1 | PA0 | PA1 |
| UART2 | For UART2 | PC4 | PC5 |
| UART3 | For UART3 | PD6 | PD7 |
| UART4 | For UART4 | PC6 | PC7 |
| UART5 | For UART5 | PC4 | PC5 |
| UART6 | For UART6 | PE4 | PE5 |
| UART7 | For UART7 | PD4 | PD5 |

### UART_BaudRate
| BaudRate Example | 
| ------ | 
| 9600 |
| 112500 |

### UART_PARITY
| Parameter Name | Description |
| ------ | ------ |
| EVEN_PARITY | Enables even parity, which generates and checks for even num- ber of l’s in the data and parity bits during transmission and reception. |
| ODD_PARITY |  Enables odd parity, which generates and checks for odd num- ber of l’s in the data and parity bits during transmission and reception. |
| DISABLE_PARITY | Disables parity. |
### UART_STOPBIT

| Parameter Name | Description |
| ------ | ------ |
| ONE_STOP_BIT | one stop bit is transmitted at the end of UART frame. |
| TWO_STOP_BIT | two stop bit is transmitted at the end of UART frame. |

### UART_FIFOMode

| Parameter Name | Description |
| ------ | ------ |
| ENABLE_FIFO | The transmit and receive FIFO buffers are enabled. |
| DISABLE_FIFO | The FIFOs are disabled (Character mode). The FIFOs become 1-byte-deep holding registers. |

### UART_FrameLength
| Parameter Name | Description |
| ------ | ------ |
| 5 | Frame Length Will Be 5-bit. |
| 6 | Frame Length Will Be 6-bit. |
| 7 | Frame Length Will Be 7-bit. |
| 8 | Frame Length Will Be 8-bit. |


### UART_Control
| Parameter Name | Description |
| ------ | ------ |
| ENABLE | For enable UARTx channel. |
| DISABLE | For disable UARTx channel. |

