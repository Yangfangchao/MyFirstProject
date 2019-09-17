//******************************************************************************
//                                www.ghostyu.com
//
//                 Copyright (c) 2017-2018, WUXI Ghostyu Co.,Ltd.
//                                All rights reserved.
//
//  FileName : los_nbiot_entry.c
//  Date     : 2018-11-13 22:43
//  Version  : V0001
// 历史记录  : 第一次创建
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
  NB_INIT,          // 初始化操作
  NB_MODULE,        // 获取NB模块厂商及固件，频段等信息
  NB_SIGN,
  NB_UDP_CR,        // 创建UDP
  NB_UDP_CL,        // 关闭UDP
  NB_UDP_REG,       // 此状态用于注册谷雨云平台信息（如果不与谷雨云平台通信，可忽略）
  NB_UDP_ST,        // 利用已经创建的UDP发送数据
  NB_UDP_RE,        // UDP接收信息
  NB_CoAP_SEVER,    // CoAP远程地址设置与获取
  NB_CoAP_ST,       // 利用CoAP发送消息
  NB_CoAP_RE,       // CoAP返回信息
  NB_RESET,         // 复位NB
  NB_END
}NB_STATE_e;


//记录NB模块初始化流程顺序
#define  NB_SEQ_INIT         0x01
#define  NB_SEQ_UDP_CR       0X02
#define  NB_SEQ_UDP_REG      0x04
#define  NB_SEQ_COAP_SERVER  0x08

//LCD 启始与结束显示行下标
#define LCD_FIRST_LINE       2
#define LCD_LAST_LINE        7

//NB网络状态LED闪烁事件
#define NB_LED_NONET_ID      0x0001    //默认状态
#define NB_LED_ONNET_ID      0x0002    //附着网络

#define NB_LED_MASK_ID       0x0003    //事件掩码

//------------------------------------------------------------------------------
// Global Variable declare
//
static UINT32        g_uwNBiotTaskID;      //NB任务句柄
static UINT32        g_uwLedTaskID;        //Led显示任务句柄
static EVENT_CB_S    net_state_event;      //NB网络状态事件结构

volatile NB_STATE_e  APP_STATE= NB_NONE;   //NB任务状态变量
uint8_t              seq_record = 0;       //标志登记变量
uint8_t*             NB_Module_IMEI = NULL;//记录模块的IMEI号

//------------------------------------------------------------------------------
// Function prototypes declare
//


/* LED 任务函数入口 */
static LITE_OS_SEC_TEXT VOID LOS_LED_Tskfunc(VOID);
//******************************************************************************
// fn : LOS_NbIot_Tskfunc
//
// brief : NBIOT 任务函数
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
// brief : LED 任务函数
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
// brief : 创建nbiot系统任务
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
