//******************************************************************************
//                                www.ghostyu.com
//
//                 Copyright (c) 2017-2018, WUXI Ghostyu Co.,Ltd.
//                                All rights reserved.
//
//  FileName : los_nbiot_entry.c
//  Date     : 2018-11-13 22:43
//  Version  : V0001
// ��ʷ��¼  : ��һ�δ���
//******************************************************************************
#include <stdio.h>
#include <string.h>

//#include "los_bsp_nbuart.h"
#include "los_nbiot_entry.h"
#include "los_task.h"
#include "los_event.h"

//#include "NB_Board.h"
//#include "NB_BC95.h"
//#include "NB_Board_Cfg.h"


//------------------------------------------------------------------------------
// Typedef 
//
typedef enum
{
  NB_NONE,
  NB_INIT,          // ��ʼ������
  NB_MODULE,        // ��ȡNBģ�鳧�̼��̼���Ƶ�ε���Ϣ
  NB_SIGN,
  NB_UDP_CR,        // ����UDP
  NB_UDP_CL,        // �ر�UDP
  NB_UDP_REG,       // ��״̬����ע�������ƽ̨��Ϣ��������������ƽ̨ͨ�ţ��ɺ��ԣ�
  NB_UDP_ST,        // �����Ѿ�������UDP��������
  NB_UDP_RE,        // UDP������Ϣ
  NB_CoAP_SEVER,    // CoAPԶ�̵�ַ�������ȡ
  NB_CoAP_ST,       // ����CoAP������Ϣ
  NB_CoAP_RE,       // CoAP������Ϣ
  NB_RESET,         // ��λNB
  NB_END
}NB_STATE_e;


//��¼NBģ���ʼ������˳��
#define  NB_SEQ_INIT         0x01
#define  NB_SEQ_UDP_CR       0X02
#define  NB_SEQ_UDP_REG      0x04
#define  NB_SEQ_COAP_SERVER  0x08

//LCD ��ʼ�������ʾ���±�
#define LCD_FIRST_LINE       2
#define LCD_LAST_LINE        7

//NB����״̬LED��˸�¼�
#define NB_LED_NONET_ID      0x0001    //Ĭ��״̬
#define NB_LED_ONNET_ID      0x0002    //��������

#define NB_LED_MASK_ID       0x0003    //�¼�����

//------------------------------------------------------------------------------
// Global Variable declare
//
static UINT32        g_uwNBiotTaskID;      //NB������
static UINT32        g_uwLedTaskID;        //Led��ʾ������
static EVENT_CB_S    net_state_event;      //NB����״̬�¼��ṹ

volatile NB_STATE_e  APP_STATE= NB_NONE;   //NB����״̬����
uint8_t              seq_record = 0;       //��־�ǼǱ���
uint8_t*             NB_Module_IMEI = NULL;//��¼ģ���IMEI��

//------------------------------------------------------------------------------
// Function prototypes declare
//


/* LED ��������� */
static LITE_OS_SEC_TEXT VOID LOS_LED_Tskfunc(VOID);
//******************************************************************************
// fn : LOS_NbIot_Tskfunc
//
// brief : NBIOT ������
//
// param : none
//
// return : none
LITE_OS_SEC_TEXT VOID LOS_NbIot_Tskfunc(VOID)
{
  seq_record = 0; 
  
 
  while(1)
  {
    printf("Task1 Runing!-----\n");
    LOS_TaskDelay(1000);
  }
}
//******************************************************************************
// fn : LOS_LED_Tskfunc
//
// brief : LED ������
//
// param : none
//
// return : none
static LITE_OS_SEC_TEXT VOID LOS_LED_Tskfunc(VOID)
{

  while(1)
  {
		printf("Task2 Runing!-----\n");
    LOS_TaskDelay(10000);
  }
}
//******************************************************************************
// fn : LOS_NBIOT_Entry
//
// brief : ����nbiotϵͳ����
//
// param : none
//
// return : none
void LOS_NBIOT_Entry(void)
{
    UINT32 uwRet;
    TSK_INIT_PARAM_S stTaskInitParam;

    (VOID)memset((void *)(&stTaskInitParam), 0, sizeof(TSK_INIT_PARAM_S));
    stTaskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)LOS_NbIot_Tskfunc;
    stTaskInitParam.uwStackSize = LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE;
    stTaskInitParam.pcName = "nb-iot";
    stTaskInitParam.usTaskPrio = 5;
    uwRet = LOS_TaskCreate(&g_uwNBiotTaskID, &stTaskInitParam);

    if (uwRet != LOS_OK)
    {
#ifdef UART_DBG
      printf("NB-IOT task create failed\n");
#endif
      return;
    }

    (VOID)memset((void *)(&stTaskInitParam), 0, sizeof(TSK_INIT_PARAM_S));
    stTaskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)LOS_LED_Tskfunc;
    stTaskInitParam.uwStackSize  = 0x200;
    stTaskInitParam.pcName       = "LED";
    stTaskInitParam.usTaskPrio   = LOS_TASK_PRIORITY_LOWEST -1;
    uwRet = LOS_TaskCreate(&g_uwLedTaskID, &stTaskInitParam);
    
    if (uwRet != LOS_OK)
    {
#ifdef UART_DBG
      printf("LED task create failed\n");
#endif
      return;
    }
    
    uwRet = LOS_EventInit(&net_state_event);
    if (uwRet != LOS_OK)
    {
#ifdef UART_DBG
      printf("NET event create failed\n");
#endif
      return;
    }
}
