/* 
 * File:   uart.h
 * Author: Duy Ngo
 *
 * Created on November 4, 2019, 3:14 PM
 */

#ifndef _UART_H
#define _UART_H

/**
  Section: Included Files
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "mcc_generated_files/eusart.h"

//*********************************************************
//          Local Defines/Variables used for Example
//*********************************************************
#define responseBufferSize  64
uint8_t ResponseIndex = 0;


typedef enum { 
    SML
} uart_configurations_t;

typedef struct { uint8_t (*Read)(void); void (*Write)(uint8_t txdata); bool (*TransmitReady)(void); uint8_t (*DataReady)(void); void (*SetTxISR)(void (* interruptHandler)(void)); void (*RxDefaultISR)(void); void (*SetRxISR)(void (* interruptHandler)(void)); bool (*TransmitDone)(void); void (*TxDefaultISR)(void); void (*Initialize)(void);  } uart_functions_t;

extern const uart_functions_t uart[];

char ResponseBuffer [responseBufferSize] = {0};
char ReadStorage [responseBufferSize] = {0};
void blockingWait(uint16_t);
void ReadyReceiveBuffer(void);
char* GetResponse(void);
void SendString(const char*);
void SML_SendString(const char*,int len);
void INIT_SMART_LIGHT (void);
void ReceivedMessage(void);
#endif	// _UART_H

