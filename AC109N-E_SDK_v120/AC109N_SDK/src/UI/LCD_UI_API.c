/*--------------------------------------------------------------------------*/
/**@file    LCD_UI_API.c
   @brief   LCD ��������ʾ����ӿں���
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "UI_API.h"
#include "device.h"

#if defined LCD_96X32_SERIAL || defined LCD_128X32_SERIAL \
  || defined LCD_128X64_SERIAL || defined LCD_128X64_PARALLEL

#include "LCD.h"
#include "msg.h"
#include "get_music_file.h"
#include "hot_msg.h"
#include "RTC_API.h"

UI_VAR _data UI_var;   /*UI ��ʾ����*/   

/*----------------------------------------------------------------------------*/
/**@brief   UI ��ʾ���洦����
   @param   menu����Ҫ��ʾ�Ľ���
   @return  ��
   @note    void UI_menu_api(u8 menu)
*/
/*----------------------------------------------------------------------------*/
_near_func void UI_menu_api(u8 menu) AT (COMMON_CODE)
{    
    LCD_clear();
    
    /*��������-���������Զ�����*/
    if (menu == MENU_MAIN)                  
    {
        /*�ȴ������淵��*/
        if (UI_var.bMenuReturnCnt)
        {
            UI_var.bMenuReturnCnt++;
            if (UI_var.bMenuReturnCnt > UI_RETURN)
            {
                if (UI_var.bCurMenu == MENU_INPUT_NUMBER)
                    put_msg_fifo(MSG_INPUT_TIMEOUT);
                UI_var.bMenuReturnCnt = 0;
                UI_var.bCurMenu = UI_var.bMainMenu;
            }
        }
        else
        {
            if (UI_var.bCurMenu == UI_var.bMainMenu)
                return;
            UI_var.bCurMenu = UI_var.bMainMenu;   
        }    
    }
    else
    {
        if (menu > 0x80)    //���ڵ�ǰ����Ϊ������ʱˢ�½���
        {
            if (UI_var.bCurMenu != UI_var.bMainMenu)
              return;
        }
        else
        {
            UI_var.bCurMenu = menu;
            if (menu != UI_var.bMainMenu)
            {
                UI_var.bMenuReturnCnt = 0x1;   //�������濪ʼ���ؼ��� 
            }
            if (menu != MENU_INPUT_NUMBER)
              input_number = 0;
        }
    }
    
    switch(UI_var.bCurMenu)
    {
    /*-----System Power On UI*/
    case MENU_POWER_UP:
      LCD_show_hello();
      break;
    
    /*-----Common Info UI*/
    case MENU_MAIN_VOL:
      LCD_show_volume();
      break;
    case MENU_INPUT_NUMBER:
      LCD_show_IR_number();
      break;
    
      
    /*-----Music Related UI*/
    case MENU_EQ: 
    case MENU_MUSIC_MAIN:
      LCD_show_music_main();
      break;
    case MENU_FILENUM:
      LCD_show_filenumber(playfile.given_file_number);
      break; 

    case MENU_PAUSE:
      LCD_show_pause();
      break;
      
    case MENU_PLAYMODE:
      LCD_show_playmode();
      break;
    
    case MENU_WAIT:
      LCD_show_waiting();
      break;
      
    /*-----PC Related UI*/
    case MENU_PC_MAIN:
      LCD_show_pc_main();
      break;
    case MENU_PC_VOL_UP:
      LCD_show_pc_vol_up();
      break;
    case MENU_PC_VOL_DOWN:
      LCD_show_pc_vol_down();
      break;  
#ifdef FM_ENABLE       
    /*-----FM Related UI*/
    case MENU_FM_MAIN:
    case MENU_FM_DISP_FRE:
    case MENU_FM_FIND_STATION:
    case MENU_FM_CHANNEL:  
      LCD_show_fm_main();
      break;
#endif      
    /*-----AUX Related UI*/
    case MENU_AUX_MAIN:
      LCD_show_aux_main();
      break;

#ifdef RTC_EN      
    /*-----RTC Related UI*/
    case MENU_RTC_MAIN:
      RTC_setting_var.bMode = 0;    //ģʽ�����ͬ������ 
    case MENU_RTC_SET:
      LCD_show_RTC_main();
      break;
      
    case MENU_ALM_SET:
      LCD_show_week_alarm();
      break;
      
    case MENU_ALM_UP:
      LCD_show_alarm_up();
      break;  
#endif
      
    default:
      break;
    }
    LCD_Update(0, LCD_var.bMaxPage);
}
#endif
