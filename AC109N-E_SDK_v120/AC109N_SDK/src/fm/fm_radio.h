/*----------------------------------------------------------------------------*/
/** @brief:
    @param:
    @return:
    @author:Juntham
    @note:
    @date: 2012-06-13,15:51
*/
/*----------------------------------------------------------------------------*/
#ifndef __FM_RADIO_H__
#define __FM_RADIO_H__

#include "config.h"

#ifdef __SMART_CPU__

typedef struct _FM_MODE_VAR
{
    u16 wFreq;          ///<��ǰƵ��
    u8  bFreChannel; 	///<��̨��
    u8  bTotalChannel;  ///<��ǰƵ��
    u8  bAddr;	        ///<���ߵ�FM�����ĵ�ַָ��
}FM_MODE_VAR;

extern FM_MODE_VAR _data fm_mode_var;
extern _no_init u8 _data scan_mode;
void fm_play(void);
void fm_mode(void);

#endif

#endif
