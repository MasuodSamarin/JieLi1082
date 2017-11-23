/*--------------------------------------------------------------------------*/
/**@file    FM_API.c
   @brief   FM ģʽ���ܽӿں���
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "FM_API.h"
#include "fm_radio.h"
#include "dac.h"

#ifdef FM_ENABLE

#ifdef	BK1080
#include "BK1080.c"
#endif

#ifdef RDA5807
#include "RDA5807.c"
#endif

#ifdef KT0830EG
#include "KT0830EG.c"
#endif

#ifdef QN8035
#include "QN8035.c"
#endif

#ifdef AR1019
#include "AR1019.c"
#endif
#include "hot_msg.h"
#include "msg.h"
#include "key.h"
#include "main.h"
#include "iic.h"
#include "UI_API.h"
#include "clock.h"

void (* const fm_init[])(void) AT(FM_TABLE_CODE) =
{

#ifdef	RDA5807
    init_RDA5807,
#endif

#ifdef	BK1080
    init_BK1080,
#endif

#ifdef	KT0830EG
    init_KT0830,
#endif

#ifdef	QN8035
    init_QN8035,
#endif

#ifdef	AR1019
    init_AR1019,
#endif

};

bool (* const fm_set_fre[])(u16) AT(FM_TABLE_CODE)=
{
#ifdef	RDA5807
    set_fre_RDA5807,
#endif

#ifdef	 BK1080
    set_fre_BK1080,
#endif

#ifdef	 KT0830EG
    set_fre_KT0830,
#endif

#ifdef	QN8035
    set_fre_QN8035,
#endif

#ifdef	AR1019
    set_freq_AR1019,
#endif
};


void (* const fm_power_off[])(void) AT(FM_TABLE_CODE)=
{
#ifdef	RDA5807
    RDA5807_PowerDown,
#endif

#ifdef	 BK1080
    BK1080_PowerDown,
#endif

#ifdef	 KT0830EG
    KT0830_PowerDown,
#endif

#ifdef	 QN8035
    QN8035_powerdown,
#endif

#ifdef	AR1019
    AR1019_powerdown,
#endif
};


bool (* const fm_read_id[])(void) AT(FM_TABLE_CODE)=
{
#ifdef	RDA5807
    RDA5807_Read_ID,
#endif

#ifdef	 BK1080
    BK1080_Read_ID,
#endif

#ifdef	 KT0830EG
    KT0830_Read_ID,
#endif

#ifdef	 QN8035
    QN8035_Read_ID,
#endif

#ifdef	AR1019
    AR1019_Read_ID,
#endif
};


void (* const fm_mute[])(u8) AT(FM_TABLE_CODE)=
{
#ifdef	RDA5807
    RDA5807_mute,
#endif

#ifdef	BK1080
    BK1080_mute,
#endif

#ifdef	KT0830EG
    KT0830_mute,
#endif

#ifdef	 QN8035
    QN8035_mute,
#endif

#ifdef	AR1019
    AR1019_mute,
#endif
};

/*----------------------------------------------------------------------------*/
/**@brief   FMģ���ʼ���ӿں���
   @param
   @return
   @note    void init_fm_rev(void)
*/
/*----------------------------------------------------------------------------*/
bool init_fm_rev(void) AT(FM_CODE)
{
    for (fm_mode_var.bAddr = 0; fm_mode_var.bAddr < (sizeof(fm_read_id)/2); fm_mode_var.bAddr++)
    {
        if ((*fm_read_id[fm_mode_var.bAddr])())
        {
            (* fm_init[fm_mode_var.bAddr])();
            return TRUE;
        }
    }

    return FALSE;
}


/*----------------------------------------------------------------------------*/
/**@brief   �ر�FMģ���Դ
   @param
   @return
   @note    void fm_rev_powerdown(void
*/
/*----------------------------------------------------------------------------*/
void fm_rev_powerdown(void) AT(FM_CODE)
{
    (* fm_power_off[fm_mode_var.bAddr])();
}


/*----------------------------------------------------------------------------*/
/**@brief   ����һ��FMƵ��Ľӿں���
   @param   mode = 0: ʹ��frequency�е�ֵ��= 1:Ƶ���1�� = 2:Ƶ���1
   @return  1����̨��0����̨
   @note    bool set_fre(u16 fre, u8 mode)
*/
/*----------------------------------------------------------------------------*/
bool set_fre(u8 mode) AT(FM_CODE)
{
    fm_module_mute(1);

    if (mode == FM_FRE_INC)
    {
        fm_mode_var.wFreq++;
    }
    else if (mode == FM_FRE_DEC)
    {
        fm_mode_var.wFreq--;
    }
    if (fm_mode_var.wFreq > MAX_FRE)
        fm_mode_var.wFreq = MIN_FRE;
    if (fm_mode_var.wFreq < MIN_FRE)
        fm_mode_var.wFreq = MAX_FRE;

    return (* fm_set_fre[fm_mode_var.bAddr])(fm_mode_var.wFreq);
}


/*----------------------------------------------------------------------------*/
/**@brief   FMģ��Mute����
   @param   flag��Muteʹ��λ
   @return  ��
   @note    void fm_module_mute(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void fm_module_mute(u8 flag) AT(FM_CODE)
{
    (* fm_mute[fm_mode_var.bAddr])(flag);
}

/*----------------------------------------------------------------------------*/
/**@brief ��ȡȫ����¼��Ƶ��
   @param 	��
   @return  Ƶ������
   @note  u8 get_total_mem_channel(void)
*/
/*----------------------------------------------------------------------------*/
u8 get_total_mem_channel(void) AT(FM_CODE)
{
    u8 i,j;
    u8 total;

    total = 0;
    for (i = 0; i < MEM_FM_LEN; i++)
    {
        j = get_memory(MEM_CHANNL + i);
        total += get_one_count(j);
    }

    if (total > MAX_CHANNL)
        total = MAX_CHANNL;

    return total;
}
/*----------------------------------------------------------------------------*/
/**@brief ͨ��Ƶ����ȡƵ��
   @param 	channel��Ƶ��
   @return  ��Ч��Ƶ��ƫ����
   @note  u8 get_fre_via_channle(u8 channel)
*/
/*----------------------------------------------------------------------------*/
u8 get_fre_via_channle(u8 channel) AT(FM_CODE)
{
    u8 i,j, k;
    u8 total;

    total = 0;
    for (i = 0; i < MEM_FM_LEN; i++)
    {
        j = get_memory(MEM_CHANNL + i);

        for (k = 0; k < 8; k++)
        {
            if (j & (BIT(k)))
            {
                total++;
                if (total == channel)
                {
                    return i * 8 + k;		 //fre = MIN_FRE + return val
                }
            }
        }

    }
    return 0xff;							//find none
}
/*----------------------------------------------------------------------------*/
/**@brief ����Ƶ��ƫ������ȡƵ��
   @param 	channel��Ƶ��
   @return  Ƶ��
   @note  u8 get_channel_via_fre(u8 fre)
*/
/*----------------------------------------------------------------------------*/
u8 get_channel_via_fre(u8 fre) AT(FM_CODE)
{
    u8 i,j, k;
    u8 total;

    total = 0;
    for (i = 0; i < MEM_FM_LEN; i++)
    {
        j = get_memory(MEM_CHANNL + i);
        for (k = 0; k < 8; k++)
        {
            if (j & (BIT(k)))
            {
                total++;
                if (fre == (i * 8 + k))
                {
                    return total;		 //return fre index
                }
            }
        }
    }
    return fm_mode_var.bFreChannel;						    //find none
}
/*----------------------------------------------------------------------------*/
/**@brief ����Ƶ��ƫ�������浽��Ӧ��Ƶ��λ������EEPROM
   @param 	fre��Ƶ��ƫ����
   @return  ��
   @note  void save_fm_point(u8 fre)
*/
/*----------------------------------------------------------------------------*/
void save_fm_point(u8 fre) AT(FM_CODE)
{
    u8 i,j, k;

    i = fre / 8;
    k = fre % 8;

    j = get_memory(MEM_CHANNL + i) | BIT(k);
    set_memory(MEM_CHANNL + i, j);
}
/*----------------------------------------------------------------------------*/
/**@brief ��EEPROM�������Ƶ����Ϣ
   @param 	��
   @return  ��
   @note  void clear_all_fm_point(void)
*/
/*----------------------------------------------------------------------------*/
void clear_all_fm_point(void) AT(FM_CODE)
{
    u8 i;

    for (i = MEM_CHANNL; i <= (MEM_CHANNL + MEM_FM_LEN); i++)
    {
        set_memory(i ,0);
    }
}
/*----------------------------------------------------------------------------*/
/**@brief ����Ƶ��
   @param 	��
   @return  ��
   @note  u8 ch_save(void)
*/
/*----------------------------------------------------------------------------*/
void ch_save(void) AT(FM_CODE)
{
    save_fm_point(fm_mode_var.wFreq - MIN_FRE);
    fm_mode_var.bFreChannel = get_channel_via_fre(fm_mode_var.wFreq - MIN_FRE);
    fm_mode_var.bTotalChannel = get_total_mem_channel();
}

/*----------------------------------------------------------------------------*/
/**@brief  fm_scan ״̬��־
   @param  flag=1 ��־�˽�����̨״̬   flag=0��������̨״̬
   @return ��
   @note   void enter_fm_rev(void)
*/
/*----------------------------------------------------------------------------*/
void fm_scan_flag(bool flag) AT(FM_CODE)
{
    if (flag)
    {
        set_memory(MEM_CHAN,fm_mode_var.bFreChannel|0x80);
    }
    else
    {
        set_memory(MEM_CHAN,fm_mode_var.bFreChannel&0x7f);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  FM ģʽ��Ϣ��ʼ��
   @param  ��
   @return ��
   @note   void fm_info_init(void)
*/
/*----------------------------------------------------------------------------*/
void fm_info_init(void) AT(FM_CODE)
{
    /*------------System configuration-----------*/
    Sys_IRInput = 1;
    Sys_Volume = 1;
    key_table_sel(1);

    fm_mode_var.wFreq = get_memory(MEM_FRE);

    if (fm_mode_var.wFreq > (MAX_FRE - MIN_FRE))
    {
        fm_mode_var.wFreq = MIN_FRE;
    }
    else
    {
        fm_mode_var.wFreq += MIN_FRE;
    }

    fm_mode_var.bTotalChannel = get_total_mem_channel();

    if (!fm_mode_var.bTotalChannel)
    {
        fm_mode_var.bTotalChannel = 1;
    }

    fm_mode_var.bFreChannel = get_memory(MEM_CHAN);

    if (fm_mode_var.bFreChannel > MAX_CHANNL)					//̨��Ϊ1;��̨��Ϊ1
    {
        fm_mode_var.bFreChannel = 1;
        fm_mode_var.bTotalChannel = 1;
    }
    else if (!fm_mode_var.bFreChannel)
    {
        fm_mode_var.bFreChannel = 1;
    }

    fm_mode_var.bFreChannel = get_channel_via_fre(fm_mode_var.wFreq - MIN_FRE);

    if (0xff == fm_mode_var.bFreChannel)
    {
        fm_mode_var.bFreChannel = 1;
    }

    set_fre(FM_CUR_FRE);
    fm_module_mute(0);
    scan_mode = FM_SCAN_STOP;
    /*---------FM MAIN UI--------------*/
    SET_UI_MAIN(MENU_FM_MAIN);
    UI_menu(MENU_FM_MAIN);
    UI_menu(MENU_MUTE);
}


/*----------------------------------------------------------------------------*/
/**@brief    ȫƵ������
   @param    mode: 0ȫƵ��, 1:��һ����ЧƵ�㣬 2:��һ����ЧƵ��
   @return   0:δ�ҵ�Ƶ�� 1:������� 2:�˳�FMģʽ 3�����������˳�
   @note     u8 fm_scan(u8 mode)
*/
/*----------------------------------------------------------------------------*/
bool fm_scan(u8 mode) AT(FM_CODE)
{
    bool res;

#ifdef  QN8035
	if (qn8035_online)
        QN8035_setch(4);
#endif

	if (mode == FM_SCAN_PREV)
	    res = set_fre(FM_FRE_DEC);
	else
	    res = set_fre(FM_FRE_INC);

    UI_menu(MENU_FM_DISP_FRE);

    if (res)						//�ҵ�һ��̨
    {
        fm_module_mute(0);
        set_memory(MEM_FRE, fm_mode_var.wFreq - MIN_FRE);
        if ( mode == FM_SCAN_ALL ){
            save_fm_point(fm_mode_var.wFreq - MIN_FRE);
            fm_mode_var.bFreChannel = get_channel_via_fre(fm_mode_var.wFreq - MIN_FRE);
            fm_mode_var.bTotalChannel = get_total_mem_channel();
            UI_menu(MENU_FM_FIND_STATION);
        }
		return true;            		
    }
	
    fm_module_mute(0);
    return false;
}
#endif
