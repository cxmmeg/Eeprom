/*************************************************************
             EEPROM��PIC17F18xxx �ڲ�EEPROM�е�ʵ��
 * ����õĿ��ļ������ļ�ͬʱ������XC8�������Ĵ󲿷�PIC MCU
*************************************************************/

#include <pic.h>
#include "PicBit.h"

#include "Eeprom.h"

//PIC��ջ��Ȳ���,ʵ�ʶ�ջ = IDE��ʾ��ջ - 5
//#define SUPPORT_STACK_TEST

#ifdef SUPPORT_STACK_TEST
#include <string.h>

//---------------------------��ȡEeprom����---------------------------------
void _Wr_Test3(EepromAdr_t Adr,
               void *pVoid,
               EepromLen_t Len)
{
   Eeprom_Rd(Adr,pVoid,Len);//��4��
}

//---------------------------��ȡEeprom����---------------------------------
void _Wr_Test2(EepromAdr_t Adr,
               void *pVoid,
               EepromLen_t Len)
{
   _Wr_Test3(Adr,pVoid,Len);//��3��
}

//---------------------------��ȡEeprom����---------------------------------
void _Wr_Test(EepromAdr_t Adr,
               void *pVoid,
               EepromLen_t Len)
{
   _Wr_Test2(Adr,pVoid,Len);//��2��
}
#endif

//---------------------------��ȡEeprom����---------------------------------
void Eeprom_Rd(EepromAdr_t Adr,
               void *pVoid,
               EepromLen_t Len)
{
    #ifdef SUPPORT_STACK_TEST
     memset(pVoid, 0, Len); //PIC��ջ��Ȳ���,��5��
    #endif

    unsigned char *pData;
    pData = (unsigned char*)pVoid;
    for(;Len > 0;Len--,Adr++,pData++)
    {
      *pData = eeprom_read(Adr);
    }    
}

//---------------------------дEeprom����---------------------------------
void Eeprom_Wr(EepromAdr_t Adr,
               const void *pVoid,
               EepromLen_t Len)
{
    #ifdef SUPPORT_STACK_TEST
      _Wr_Test(Adr,pVoid,Len); //PIC��ջ��Ȳ���:��1��
    #endif
    unsigned char *pData;
    pData = (unsigned char*)(pVoid);
    for(;Len > 0;Len--,Adr++,pData++)
    {
      eeprom_write(Adr, *pData);
    }
}




