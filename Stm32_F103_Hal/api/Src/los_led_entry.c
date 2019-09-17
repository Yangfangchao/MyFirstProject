//******************************************************************************
//                                www.ghostyu.com
//
//                 Copyright (c) 2017-2018, WUXI Ghostyu Co.,Ltd.
//                                All rights reserved.
//
//  FileName : los_led_entry.c
//  Date :     2018-11-13 11:45
//  Version :  V0001
//  History :  初始创建版本
//******************************************************************************
#include <string.h>

#include "los_led_entry.h"
#include "los_task.h"
#include "los_bsp_uart.h"


//------------------------------------------------------------------------------
#define LCD_FIRST_LINE       2
#define LCD_LAST_LINE        7

//------------------------------------------------------------------------------
//Global Variables Declare
static UINT32 g_uwLedTaskID;

//------------------------------------------------------------------------------
// function prototypes

/*  LED 任务函数入口 */
static LITE_OS_SEC_TEXT VOID LOS_BoardLedTskfunc(VOID);

//******************************************************************************
// fn : LOS_BoardLedEntry
//
// brief : 创建LED任务
//
// param : none
//
// return : none
void LOS_BoardLedEntry(void)
{
  UINT32 uwRet;
  TSK_INIT_PARAM_S stTaskInitParam;

  (VOID)memset((void *)(&stTaskInitParam), 0, sizeof(TSK_INIT_PARAM_S));
  stTaskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)LOS_BoardLedTskfunc;
  stTaskInitParam.uwStackSize = LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE;
  stTaskInitParam.pcName = "LED-Demo";
  stTaskInitParam.usTaskPrio = 10;
  uwRet = LOS_TaskCreate(&g_uwLedTaskID, &stTaskInitParam);

  if (uwRet != LOS_OK)
  {
      return;
  }
  return;  
}
//******************************************************************************
// fn : LOS_BoardLedTskfunc
//
// brief : LED 任务函数入口
//
// param : none
//
// return : none
static LITE_OS_SEC_TEXT VOID LOS_BoardLedTskfunc(VOID)
{
  while (1)
  {
    LOS_EvbLedControl(LOS_LED1, LED_ON);
    LOS_EvbUartWriteStr("LED=ON\n");

    (void)LOS_TaskDelay(500);
    LOS_EvbLedControl(LOS_LED1, LED_OFF);
    LOS_EvbUartWriteStr("LED=OFF\n");

    (void)LOS_TaskDelay(500);
  }
}
