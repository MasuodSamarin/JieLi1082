/*--------------------------------------------------------------------------*/
/**@file     config.h
   @brief    һЩ��������������
   @author
   @date   2010-12-13
   @note   AC109N
*/
/*----------------------------------------------------------------------------*/
#ifndef _CONFIG_
#define _CONFIG_

//////////////////////////////////////////////////////////////////
#include "cd02.h"

#ifdef __IAR_SYSTEMS_ICC__
#define __SMART_CPU__
#define WDT_CLEAR()     WDT_CON |= BIT(6)

#ifndef NDEBUG
//#ifdef NDEBUG

#define _near_func __near_func
#define _banked_func __banked_func

#define deg         my_printf
#define deg_puts    my_puts

#else
#define deg(...)
#define deg_puts(...)
#define _near_func
#define _banked_func
#endif              //end NDEBUG

#include "typedef.h"
#include "intrinsics.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "INT.h"
#include "uart.h"
#include "common.h"

#endif          // end __IAR_SYSTEMS_ICC__

/*---------System Configuration---------------*/

//---------------------------------------------------------------------------------------------------------------/
/*---------Clock Configuration*/
#define OSC_32768           32768L
#define OSC_12M             12000000L

#define OSC_CLK             OSC_32768

//SYSTEM CLOCK
enum
{
    CLK_512K = 0,            //512000L
    CLK_1M,              //1000000L
    CLK_2M,              //1000000L
    CLK_12M,             //12000000L
    CLK_24M,             //24000000L
    CLK_48M,             //48000000L
};


#define SYSTEM_CLK          CLK_24M
//#define CLK_USE_HTC
//#define CLK_USE_32K_WITH_HTC
#define CLK_USE_32K_NO_HTC
//#define CLK_USE_12M_NO_HTC
//#define CLK_USE_12M_WITH_HTC

#define SHARE_RTC_OSC_TO_FM
//---------------------------------------------------------------------------------------------------------------/
#define WDT_EN              //�Ƿ������Ź���λ
//---------------------------------------------------------------------------------------------------------------/
///������ģʽ�£��������ڵ����������������Ҫ����������������Ҫ�޸����������������뱣�����ֵ��16384
///�����Ҫ��С����ģʽ�µ�DAC������������Զ�������������µ�����
#define DECODE_VOL_LIMIT_L  31          //������ģʽ�£�DAC����������ֵ(0~31)
#define DECODE_VOL_LIMIT_R  31

//����������
#define MAX_MAIN_VOL_L    31
#define MAX_MAIN_VOL_R    31


//DACVDD_VCOMOѡ��DAC_VDD��VCOMO��ͬһPIN��ͬʱֻ��ѡ������һ�ֹ��ܣ�Ҳ�������ֶ���ѡ(DAC_VDD����)
#define DAC_VDD_EN                      //DAC_VDD��ӵ��ݣ�SNR�������1.5dB

//�Ƿ�ѡ��VCMOֱ�ƶ���
#ifndef DAC_VDD_EN
#define VCOMO_EN
#endif

//---------------------------------------------------------------------------------------------------------------/
/*---------UI Configuration*/
//#define LCD_96X32_SERIAL
//#define LCD_128X32_SERIAL
//#define LCD_128X64_SERIAL
//#define LCD_128X64_PARALLEL
//#define LCD_SEG_5X9
//#define LED_5X7
#define LCD_BL55072

#if defined LCD_96X32_SERIAL || defined LCD_128X32_SERIAL \
  || defined LCD_128X64_SERIAL || defined LCD_128X64_PARALLEL \
    || defined LCD_SEG_4X8 || defined LED_5X7 || defined LCD_SEG_5X9 || defined LCD_BL55072
#define UI_ENABLE           //UI ���濪��

#ifdef LED_5X7
#define UI_FADE_EN
#endif

#ifdef LCD_SEG_5X9
//#define STANDBY_EN   //������RTCģʽ����ʱ��������
#endif

#endif

#ifdef UI_FADE_EN
#define LED_FADE_ON()   set_LED_all_on()
#define LED_FADE_OFF()  set_LED_fade_out()
#else
#define LED_FADE_ON()
#define LED_FADE_OFF()
#endif


//---------------------------------------------------------------------------------------------------------------/
/*---------FM Configuration*/
#define RDA5807
//#define BK1080
//#define KT0830EG
//#define QN8035
//#define AR1019

#if defined RDA5807 || defined BK1080 || defined KT0830EG || defined QN8035 || defined AR1019
#define FM_ENABLE           //FM ģʽ����
#endif

//---------------------------------------------------------------------------------------------------------------/
/*---------Work Mode Configuration*/
//#define USB_DEVICE_EN       //Enable USB SLAVE MODE

//#define USB_VIR_KEY_EN      //Enable USB virtual key

//---------------------------------------------------------------------------------------------------------------/

/*---------System Charateristic Configuration v100---------------*/
//#define    IR_REMOTE_EN                 //�Ƿ���Ҫ����ң��
///<���ֲ��Ź���ѡ��
#define    LAST_MEM_FILE_PLAY_EN        //�Ƿ���������ļ���Ų��Ź���
#ifdef     LAST_MEM_FILE_PLAY_EN
#define    BREAK_POINT_PLAY_EN			//�Ƿ�����ϵ㲥�Ź���
#endif

//#define   MUSIC_POWER_EN              //������������ʾ
//#define 	FF_FR_MUSIC_EN               //�ڿ������ʱ���Ƿ���Ҫ��������

//#define     GET_MUSIC_TOTAL_TIME         //�Ƿ��ȡ�����ļ���ʱ��
//#define     RANDOM_PLAY_EN               //�Ƿ�֧��������Ź���
//#define 	FOLDER_PLAY_EN               //�Ƿ�֧���ļ����л��Ͳ��Ź���

#define 	USB_DISK_EN      			 //�Ƿ���Զ�U��
//#define 	SDMMC_IDLE_EN                //����ʹSDMMC������ʡ��ģʽ
#define 	UDISK_IDLE_EN                //��Щ(����)U���ڴ�ģʽ�£�����ö�ٻ�������


#define     USE_EEPROM_MEMORY          //ʹ��EEPROM ��Ϊ�洢������
#ifndef     USE_EEPROM_MEMORY             //ʹ���ڲ�RTC RAM������
#define     USE_IRTC_MEMORY
#endif

#ifdef      USE_EEPROM_MEMORY
#define     CHECK_EEPROM_ON_POWER_ON     //�Ƿ����ϵ�ʱ��У��eeprom
#endif


/*---------System Charateristic Configuration v101---------------*/
//#define RTC_EN                  //<RTC ģʽʹ�ܿ���λ
//#define RTC_ALARM_EN            //<RTC ����ʹ�ܿ���λ
#if (!defined RTC_EN) && (defined RTC_ALARM_EN)
#error("RTC selectd err!")
#endif

#define 	KEY_VOICE_EN                 //������ʹ��, ���ʹ�ð��������򲻿���ʹ�����ݼ���Զ�mute/unmute����
#if !defined KEY_VOICE_EN && !defined RTC_ALARM_EN                  //û�а�����ʱ��������ʹ���������ݼ�⣬���򰴼��ڸ����л�����ͣ������»��ް�����
#define     MUSIC_ENERGY_DETECT          //���ڼ����������ݴ�С,�ɾݴ��ж��Զ�mute/unmute DAC,�е��뵭��Ч��
#define     MAX_WAVEFORM        1        //����������ݵ����Ʒ�Χ,�趨ֵΪһ�������Ⱦ�����
//�ż�ֵ����Ϊ��0ֵ(1~255), 1:��ȫ����, 2: <-90.3dB, 3: < -84.29dB, 4: <-80.7dB, 5: <-78.26dB, 6: <-76.3dB
#endif

///<SD���ӿ�ѡ��
//#define SDMMCA_EN
//#define SDMMCB_EN

#ifdef SDMMCA_EN                 //ֻ��ѡ����A���ſ���ѡ��B��������ǵ�������ͳһʹ��A��
#define SDMMCB_EN0
#endif
///<SD����ⷽʽ���
///<A CARD
#ifdef SDMMCA_EN

#define SDMMCA_DET_CMD
//#define SDMMCA_DET_CLK
//#define SDMMCA_DET_IO
#endif

///<B CARD
#ifdef SDMMCB_EN
//#define SDMMCB_DET_CMD
#define SDMMCB_DET_CLK
//#define SDMMCB_DET_IO
#endif

#define P04_TOGGLE       P0DIR &= ~BIT(4); P04 = ~P04
#define P05_TOGGLE       P0DIR &= ~BIT(5); P05 = ~P05

#endif

