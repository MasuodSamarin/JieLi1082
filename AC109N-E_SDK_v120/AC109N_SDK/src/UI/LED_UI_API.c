/*--------------------------------------------------------------------------*/
/**@file    LED_UI_API.c
   @brief   LED ��ʾ����ӿں���
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/

#include "UI_API.h"
#include "device.h"

#if defined LED_5X7 
#include "UI_common.c"
#include "LED5X7.h"
#include "LED5X7.c"
#include "msg.h"
#include "get_music_file.h"
#include "hot_msg.h"
#include "RTC_API.h"

#include "display.h"


_no_init UI_VAR _data UI_var;   /*UI ��ʾ����*/   

/*----------------------------------------------------------------------------*/
/**@brief   UI ��ʾ���洦����
   @param   menu����Ҫ��ʾ�Ľ���
   @return  ��
   @note    void UI_menu_api(u8 menu)
*/
/*----------------------------------------------------------------------------*/
_near_func void UI_menu_api(u8 menu) AT(COMMON_CODE)
{       
    /*��������-���������Զ�����*/
    if (menu == MENU_MAIN)                  
    {
        if (UI_var.bMenuReturnCnt < UI_RETURN)
        {
            UI_var.bMenuReturnCnt++;
            if (UI_var.bMenuReturnCnt == UI_RETURN)
            {
                LED5X7_clear_icon();
                if (UI_var.bCurMenu == MENU_INPUT_NUMBER)
                    put_msg_lifo(MSG_INPUT_TIMEOUT);    //���볬ʱ
                else
                    UI_var.bCurMenu = UI_var.bMainMenu;
            } 
        }
        else
        {
            /*�ȴ����治�ظ�ˢ�½���*/
            if (UI_var.bCurMenu == UI_var.bMainMenu)
                return;
            UI_var.bCurMenu = UI_var.bMainMenu;   
        }
    }
    else
    {
        if (menu > 0x80)    //���ڵ�ǰ����Ϊ������ʱˢ�½���,���磺��������ˢ�²���ʱ��
        {
            if (UI_var.bCurMenu != UI_var.bMainMenu)
              return;
        }
        else
        {
            LED5X7_clear_icon();
            /*����������Ҫ�������ؼ�����*/
            if (menu != UI_var.bMainMenu)   
                UI_var.bMenuReturnCnt = 0;
            UI_var.bCurMenu = menu;
            if (menu != MENU_INPUT_NUMBER)
              input_number = 0;
        }
    }
    LED5X7_setX(0);
   
    switch(UI_var.bCurMenu)
    {
    /*-----System Power On UI*/
    case MENU_POWER_UP:
    case MENU_WAIT:
#ifdef USB_DEVICE_EN        
    case MENU_PC_MAIN:
    case MENU_PC_VOL_UP:
    case MENU_PC_VOL_DOWN:
#endif        
    case MENU_AUX_MAIN:
#ifdef RTC_ALARM_EN      
    case MENU_ALM_UP:   
#endif      
      //LED5X7_show_string_menu(UI_var.bCurMenu);
      break;
    
    /*-----Common Info UI*/
    case MENU_MAIN_VOL:
      //LED5X7_show_volume();
      LCD_show_volume();
      break;
      
    case MENU_INPUT_NUMBER:
      //LED5X7_show_IR_number();
      break;
      
    /*-----Music Related UI*/
    case MENU_MUSIC_MAIN:
    case MENU_PAUSE:  
      //LED5X7_show_music_main();
      LCD_show_music_main();
      break;
    case MENU_FILENUM:
      //LED5X7_show_filenumber();
      LCD_show_filenumber();
      break; 
    case MENU_EQ:
      //LED5X7_show_eq();
      break; 
    case MENU_PLAYMODE:
      //LED5X7_show_playmode();
      break;
    case MENU_MUTE:
      LCD_mute();
      break;
    case MENU_UNMUTE:
      LCD_unmute();
      break;
    case MENU_STOP:
      LCD_stop();
      break;
    /*-----FM Related UI*/
#ifdef FM_ENABLE      
    case MENU_FM_MAIN:
    case MENU_FM_DISP_FRE:
      //LED5X7_show_fm_main();
      LCD_show_fm_main();
      break;
    case MENU_FM_FIND_STATION:
    case MENU_FM_CHANNEL:  
      deg_puts("MENU_FM_CHANNEL\n");     
      //LED5X7_show_fm_station();
      break;
#endif
      
#ifdef RTC_EN
    case MENU_RTC_MAIN:
      RTC_setting_var.bMode = 0;    //ģʽ�����ͬ������  
    case MENU_RTC_SET:  
      //LED5X7_show_RTC_main();
      break;
#ifdef RTC_ALARM_EN    
    case MENU_ALM_SET:
      //LED5X7_show_alarm();
      break; 
#endif
#endif
            
    default:
      break;
    }
}
#endif
