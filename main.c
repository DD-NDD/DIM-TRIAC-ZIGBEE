#include "mcc_generated_files/mcc.h"
#include "triac.h"
#include "define.h"
#include<stdbool.h>
#include<stdint.h>
#include"LED.h"
#include "uart.h"
#include "string.h"
#include "stdlib.h"
/*
                         Main application
 */
char KEY5[7] = {0xFE,0x02,0x27,0x07,0x10,0x01,0x33};
char KEY3[7] = {0xFE,0x02,0x27,0x07,0x04,0x01,0x27};
void CHECK_DIR(void);
void DATA_PROCESS(char x);
void check_message(uint8_t x);
bool  check_data(uint8_t x);
void update_state(void);
void check_on_off(void);
void check_up_down(void);
void myButtonPressedCallback(enum mtouch_button_names button);
void myButtonReleasedCallback(enum mtouch_button_names button);
char* rxData;
char Storage [responseBufferSize] = {0};
char Storage2 [9] = {0};
char Num_Char[3];
void main(void)
{
    SYSTEM_Initialize();   
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    triac_level.full = 0x00;
    last_touch_status.full_status = 0x00;
    LED_OFF();
    config_status = 0;
    INIT_SMART_LIGHT ();
    ReadyReceiveBuffer();
    //triac_level.level = 50;
    while (1)
    {
        if(ResponseIndex != 0)
        {
            blockingWait(2);
            rxData = GetResponse();
            strcpy(Storage, rxData);
            static char *s;
            static char *s1;
            
            s = strstr(Storage,"LEVEL");
            s1 = strstr(Storage,"LIGHT OFF");
            if(s1 != NULL )
            {
                triac_level.level = 0;
            }
            if(s != NULL)
            {
                strcpy(Storage2, s);
                Num_Char[0] = Storage2[6];
                Num_Char[1] = Storage2[7];
                Num_Char[2] = Storage2[8];
                static int num = 0;
                num = atoi(Num_Char);
                if(num >= 99) num = 99;
                triac_level.level = num;
            }
            memset(Storage2,NULL,9);
            memset(Num_Char,NULL,3);
            ReadyReceiveBuffer(); 
        }    
    }
}