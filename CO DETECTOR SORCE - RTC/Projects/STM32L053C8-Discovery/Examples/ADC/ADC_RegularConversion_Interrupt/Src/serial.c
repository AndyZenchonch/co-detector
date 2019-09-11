#include "serial.h"
#include "string.h"

uint8_t aRxBuffer[RXBUFFERSIZE];
uint8_t aTxBuffer[TXBUFFERSIZE];

void uartInit(void){
  UartHandle.Instance        = USARTx;
  UartHandle.Init.BaudRate   = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  
  HAL_UART_Init(&UartHandle);
	
	//HAL_UART_Receive_DMA(&UartHandle, (uint8_t *)aRxBuffer, RXBUFFERSIZE);
}

void serialConfig(uint8_t mode){
	UartRxReady = RESET;
	UartTxReady = RESET;
  if(HAL_UART_DeInit(&UartHandle) != HAL_OK){
  }
  if(HAL_UART_Init(&UartHandle) != HAL_OK){
  }	

	if(mode == SERIAL_RX){
		HAL_UART_Receive_DMA(&UartHandle, (uint8_t *)aRxBuffer, RXBUFFERSIZE);
		UartRxReady = RESET;
	}	
}

/*·¢ËÍÊý¾Ý*/
void serialPrintStr(uint8_t *str){
	serialConfig(SERIAL_TX);
	UartTxReady = RESET;
  HAL_UART_Transmit_DMA(&UartHandle, str, strlen((char*)str));
	while (UartTxReady != SET){
  }
	serialConfig(SERIAL_RX);
}




