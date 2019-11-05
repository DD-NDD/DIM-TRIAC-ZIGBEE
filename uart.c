#include "uart.h"  
#include <string.h>
#include "mcc_generated_files/mcc.h"
const uart_functions_t uart[] = {   
    {EUSART_Read, EUSART_Write, EUSART_is_tx_ready, EUSART_is_rx_ready, EUSART_SetTxInterruptHandler, EUSART_Receive_ISR, EUSART_SetRxInterruptHandler, EUSART_is_tx_done, EUSART_Transmit_ISR, EUSART_Initialize }
};
void SendString(const char* command)
{
    while (ResponseIndex-- != 0)
        uart[SML].Write(*command++);
    //uart[SML].Write('\r');
    //uart[SML].Write('\n');
}
void SML_SendString(const char* command,int len)
{
    while (len-- !=0)
        uart[SML].Write(*command++);
}
//*********************************************************
//          Accessible Example Functions
//*********************************************************
void INIT_SMART_LIGHT (void)                           // Call After System Init; Above while(1) Loop in Main.c
{
    uart[SML].SetRxISR(ReceivedMessage); 
    SendString("SYS FACTORY RESET");               // Send "sys" Command: "factoryRESET"  
    SendString("SMART LIGHT INIT");
}
void ReceivedMessage(void)       // Call in ISR EUSART RX after EUSART_Receive_ISR() 
{
    uart[SML].RxDefaultISR();
    while (!uart[SML].DataReady()) {
        NOP();
    }
    uint8_t readByte = uart[SML].Read();
    if ((ResponseIndex < responseBufferSize) )
        ResponseBuffer[ResponseIndex++] = readByte;
}
//*********************************************************
//          Local Used Example Functions
//*********************************************************
void ReadyReceiveBuffer (void)
{
    ResponseIndex = 0;
    for (uint8_t position = 0; position < responseBufferSize; position++)
        ResponseBuffer[position] = 0;
}
char* GetResponse(void)
{
    return ResponseBuffer;
}
void blockingWait (uint16_t limit)
{
    for (uint16_t counter = 0; counter < limit; counter++)
		__delay_ms(10);
}