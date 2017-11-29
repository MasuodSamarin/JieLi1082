/*--------------------------------------------------------------------------*/
/**@file     key.h
   @brief
   @details
   @author
   @date   2011-4-26
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _KEY_
#define _KEY_

#include "config.h"
#include "msg.h"

/*��������*/
#define KEY_TYPE_AD     0x0
#define KEY_TYPE_IR     0x1


/*�����ż�ֵ*/

#define KEY_BASE_CNT  4
#define KEY_LONG_CNT  75
#define KEY_HOLD_CNT  15

/*����״̬*/
#define KEY_SHORT_UP    0x0
#define KEY_LONG        0x1
#define KEY_HOLD        0x2
#define KEY_LONG_UP     0x3

/*��������*/
#define KEY_TYPE_AD     0x0
#define KEY_TYPE_IR     0x1

#define NO_KEY          0xff


/*ADͨ������*/
enum
{
    AD_CH_KEY = 0,
    AD_CH_AMUX_L,
    AD_CH_AMUX_R,   
    AD_CH_LDO,       
    AD_CH_VBG,     
    MAX_AD_CHANNEL,
};


#ifdef __SMART_CPU__


typedef struct _IR_CODE
{
    u16 wData;          //<��ֵ
    u8  bState;         //<����״̬
    u16 wUserCode;      //<�û���
    u8  boverflow;      //<�����źų�ʱ
}IR_CODE;


typedef struct _AD_VAR
{
    u8    bmChannel;                //<ѡ�е�AD ͨ��
    u8    bChIndex;                 //<��ǰ�������ͨ��
    u16   wADValue[MAX_AD_CHANNEL]; //<AD ͨ������ֵ����
}AD_VAR;

_near_func u8 app_get_msg(void);
_near_func void key_scan(void);
void AD_init(void);
_near_func __monitor void key_table_sel(u8 sel);
_near_func void ADC_scan(void);

extern IR_CODE __idata IR_code;
extern AD_VAR __data AD_var;      //AD ����
extern u16 _xdata key_tone_tab[];
#endif

#endif
