/***************************************************************************

                Eeprom��дģ��-ʹ�õ�ҳ�ڲ���Flash�ռ���ģ��
��ģ�������Ӳ��,ʹ�ñ�׼Flash�ӿ�ʵ�֣��������ڲ�ͬMCU��FLASH
ʹ��˵��:
1. ��ȫ�ֺ궨����ʼ��ַΪEEPROM_BASE,��EEPROM��С(С��FLASHһҳ�Ĵ�С)
2. ���ֳ�ʼ����־Ϊ�״�ʹ��FLASH�����ʱ����ͨ��Eeprom_Format()��EEPROM����
****************************************************************************/

#include "Eeprom.h"
#include "Flash.h"              //Flash��׼�����ӿ�
#include <string.h>

//----------------------��Ĭ��ֵ�����---------------------------------
#ifndef EEPROM_BASE
  #define EEPROM_BASE  0x0800FC00  //EEPROM��ҳ��ʼ��ַ��ҳ63��
#endif

#ifdef FLASH_PAGE_SIZE 	//������FLASHҳʱ,У��
  #ifndef EEPROM_SIZE
    #define EEPROM_SIZE  FLASH_PAGE_SIZE      //EEPROM����С
  #elif EEPROM_SIZE > FLASH_PAGE_SIZE    //EEPROM����С��������FLASHһҳ��С,�������С
    #undef EEPROM_SIZE
    #define EEPROM_SIZE  FLASH_PER_PAGE
  #endif
#else //��У��
  #ifndef EEPROM_SIZE
    #define EEPROM_SIZE  512 //EEPROM����С
  #endif
#endif //#ifdef FLASH_PAGE_SIZE

struct _Eeprom{ //ҳ����
  unsigned long a; //ΪBuf unsigned short����վλ
  unsigned char Buf[EEPROM_SIZE];
};

struct _Eeprom  __Eeprom;
 
//----------------------��ʽ��Eeprom����---------------------------------
void Eeprom_Format(void)
{
  Flash_Unlock();//����
  Flash_ErasePage(EEPROM_BASE);//����ҳ
  Flash_Lock();//����
}

//---------------------------дEeprom����---------------------------------
void Eeprom_Wr(EepromAdr_t Adr,
               const void *pVoid,
               EepromLen_t Len)
{
  //��Flash�е����ݿ�����������
  memcpy(__Eeprom.Buf,(unsigned char*)EEPROM_BASE, EEPROM_SIZE);
  //�ڻ�������,����Ҫд�������
  memcpy(&(__Eeprom.Buf[Adr]),pVoid,Len);
  //д�뻺�������ȫ������
  Flash_Unlock();//����
  Flash_ErasePage(EEPROM_BASE);//д����ǰ������ҳ
  Flash_Write(EEPROM_BASE, __Eeprom.Buf, EEPROM_SIZE);
  Flash_Lock();//����
}
 
//---------------------------��ȡEeprom����---------------------------------
void Eeprom_Rd(EepromAdr_t Adr,
               void *pVoid,
               EepromLen_t Len)
{
  #ifdef Flash_Read
    Flash_Read(EEPROM_BASE + Adr, pVoid, Len);
  #else //��ͨ���ڴ�ķ���
    memcpy(pVoid, (unsigned char*)(EEPROM_BASE + Adr), Len);
  #endif
}

 
  


