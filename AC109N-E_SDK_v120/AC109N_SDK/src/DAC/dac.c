/*--------------------------------------------------------------------------*/
/**@file     DAC.c
   @brief    DAC ģ����غ���
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "DAC.h"
#include "main.h"
#include "iic.h"
#include "music_play.h"
#include "USB_Device_Mode.h"
#include "RTC_API.h"
#include "play_file.h"

_no_init volatile bool _bit fade_l_in;
_no_init volatile bool _bit fade_r_in;
_no_init volatile bool _bit fade_out;
_no_init bool _bit amux;
_no_init bool _bit mute;

_no_init u8 _data key_voice_counter;
_no_init u8 _data main_vol_L, main_vol_R;

#pragma data_alignment=2
_no_init u16 _xdata key_tone_tab[16];

/*----------------------------------------------------------------------------*/
/** @brief:��������
    @param:
    @return:
    @author:Juntham
    @note:
*/
/*----------------------------------------------------------------------------*/
const s16 key_tone[] AT(DAC_TABLE_CODE)=
{
    25414 ,
    -18085,
    -13505,
    29789 ,
    -9293 ,
    -24043,
    29627 ,
    -1    ,
    -29627,
    24042 ,
    9293  ,
    -29788,
    13506 ,
    18085 ,
    -25414,
    0
};

/*----------------------------------------------------------------------------*/
/** @brief:����������0~16384
    @param:
    @return:
    @author:Juntham
    @note:
*/
/*----------------------------------------------------------------------------*/
const u16 digital_vol_tab[] AT(DAC_TABLE_CODE)=
{
    0	  ,
    93	  ,
    111	  ,
    132	  ,
    158	  ,
    189	  ,
    226	  ,
    270	  ,
    323	  ,
    386	  ,
    462	  ,
    552	  ,
    660	  ,
    789	  ,
    943	  ,
    1127  ,
    1347  ,
    1610  ,
    1925  ,
    2301  ,
    2751  ,
    3288  ,
    3930  ,
    4698  ,
    5616  ,
    6713  ,
    8025  ,
    9592  ,
    11466 ,
    15200 ,
    16000 ,
    16384
};


/*----------------------------------------------------------------------------*/
/** @brief: ������������
    @param: L_vol������������ֵ
    @param: R_vol������������ֵ
    @return:void
    @author:Juntham
    @note:  void set_digital_vol(u8 L_vol, u8 R_vol)
*/
/*----------------------------------------------------------------------------*/
void set_digital_vol(u8 L_vol, u8 R_vol) AT(DAC_CODE)
{
    DAC_VLML = (u8)((digital_vol_tab[L_vol])>>8);
    DAC_VLML = (u8)(digital_vol_tab[L_vol]);

    DAC_VLMR = (u8)((digital_vol_tab[R_vol])>>8);
    DAC_VLMR = (u8)(digital_vol_tab[R_vol]);
}

/*----------------------------------------------------------------------------*/
/** @brief: ����ģ������
    @param: L_vol������������ֵ
    @param: R_vol������������ֵ
    @return:void
    @author:Juntham
    @note:  void set_analog_vol(u8 L_vol, u8 R_vol)
*/
/*----------------------------------------------------------------------------*/
void set_analog_vol(u8 L_vol, u8 R_vol) AT(DAC_CODE)
{
    DAA_CON1 = (DAA_CON1 & 0xe0) | (MAX_MAIN_VOL_L-L_vol);
    DAA_CON2 = (DAA_CON2 & 0xe0) | (MAX_MAIN_VOL_R-R_vol);
}

/*----------------------------------------------------------------------------*/
/** @brief: ����ϵͳ������
    @param: L_vol������������ֵ
    @param: R_vol������������ֵ
    @return:void
    @author:Juntham
    @note:  void set_main_vol(u8 L_vol, u8 R_vol)
*/
/*----------------------------------------------------------------------------*/
void set_main_vol(u8 L_vol, u8 R_vol) AT(DAC_CODE)
{
    main_vol_L = L_vol;
    main_vol_R = R_vol;

    if (L_vol | R_vol)
    {
        mute = 0;
        set_digital_vol(L_vol, R_vol);
        dac_fade_in();
    }
    else
    {
        dac_fade_out();
    }
}

/*----------------------------------------------------------------------------*/
/** @brief: ���ð�����DAC �Ĵ���
    @param: L_vol������������ֵ
    @param: R_vol������������ֵ
    @return:void
    @author:Juntham
    @note:  void set_key_tone(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void set_key_tone(void) AT(COMMON_CODE)
{
    if (amux)     //amux
    {
        DAA_CON0 |= BIT(0);
        KV_VLM = 31;                    //������������
        key_voice_counter = 40;         //����������ʱ�䣺80ms,��ʱ������ݰ��������ݱ���ظ������������������ʾ���
    }
    else
    {
        KV_VLM = ((digital_vol_tab[main_vol_L]>>8) + (digital_vol_tab[main_vol_R]>>8))/4;     //������������
    }
    KV_CNT = 0;
    KV_CNT = 20;                      //�������ظ�����
}

/*----------------------------------------------------------------------------*/
/** @brief: DAC �������뺯��
    @param: void
    @return:void
    @author:Juntham
    @note:  void dac_fade_in(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void dac_fade_in(void) AT(COMMON_CODE)
{
    if (mute)
        return;

    fade_l_in = 1;
    fade_r_in = 1;
    while(fade_l_in);
    while(fade_r_in);
}

/*----------------------------------------------------------------------------*/
/** @brief: DAC ������������
    @param: void
    @return:void
    @author:Juntham
    @note:  void dac_fade_out(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void dac_fade_out(void) AT(COMMON_CODE)
{
    fade_out = 1;
    while(fade_out);
}

extern _near_func bool AUDIO_ENERGY_DETECT(u16);

_near_func bool music_detect_app(u8 energy) AT(COMMON_CODE)
{
    _no_init static u8 _data counter;

    if (AUDIO_ENERGY_DETECT(energy))
    {
        if (counter < 250) //�� 250*2ms �������Ƶ������ֵ�Ƚ�С�Ļ��Զ�����
        {
            counter++;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        counter = 0;
    }

    return 0;
}

/*----------------------------------------------------------------------------*/
/** @brief: DAC �Ĵ�����������
    @param: void
    @return:void
    @author:Juntham
    @note:  void dac_check(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void dac_check(void) AT(COMMON_CODE)
{
#ifdef KEY_VOICE_EN
    if (key_voice_counter != 0)         //���ڲ��Ű����������ܹر�����ģ��
    {
        key_voice_counter--;
    }
    else if (amux)
    {
        DAA_CON0 &= ~BIT(0);
    }
#endif

#ifdef MUSIC_ENERGY_DETECT          //������⣬������С��ָ����С����ʱ���Զ�DAC mute��ֻ�Խ���ģʽ��Ч
    {
        if (!amux)
        {
            if (music_detect_app(MAX_WAVEFORM))
            {
                fade_out = 1;
                fade_l_in = 0;
                fade_r_in = 0;
            }
            else if ((!mute) && (!fade_out))    //��û��mute������²ſ�DAC
            {
                fade_l_in = 1;
                fade_r_in = 1;
            }
        }
    }
#endif

    if (fade_l_in || fade_r_in)
    {
        u8 temp_l,temp_r;

        if((main_vol_L | main_vol_R) == 0)      //��ǰ����ֵΪ0
        {
           fade_l_in = 0;
           fade_r_in = 0;
           return;
        }

        if (amux)     //amux
        {
            temp_l = (MAX_MAIN_VOL_L - main_vol_L);
            temp_r = (MAX_MAIN_VOL_R - main_vol_R);
        }
        else
        {
            temp_l = (31 - DECODE_VOL_LIMIT_L);
            temp_r = (31 - DECODE_VOL_LIMIT_R);
        }

        DAA_CON0 &= ~BIT(7);

        if ((DAA_CON1 & 0x1f) > temp_l)
        {
            DAA_CON1--;
        }
        else if ((DAA_CON1 & 0x1f) < temp_l)
        {
            DAA_CON1++;
        }
        else
        {
            fade_l_in = 0;
        }

        if ((DAA_CON2 & 0x1f) > temp_r)
        {
            DAA_CON2--;
        }
        else if ((DAA_CON2 & 0x1f) < temp_r)
        {
            DAA_CON2++;
        }
        else
        {
            fade_r_in = 0;
        }
    }
    else if (fade_out)
    {
        if ((DAA_CON1 & 0x1f) == 0x1f)
        {
            fade_out = 0;
            DAA_CON0 |= BIT(7);
        }
        else
        {
            DAA_CON1++;
            DAA_CON2++;
        }
    }
}

/*----------------------------------------------------------------------------*/
/** @brief: ��������ʼ������
    @param: void
    @return:void
    @author:Juntham
    @note:  void key_tone_init(void)
*/
/*----------------------------------------------------------------------------*/
void key_tone_init(void) AT(DAC_CODE)
{
    my_memcpy((u8 *)key_tone_tab, (u8 *)key_tone, 32);
    /*Key tone SR from Timer0 overflow*/
    DAC_CON1 &= ~(BIT(4)|BIT(5));

    /*Key tone Vocie Data*/
    KV_START = (u8)((u16)&key_tone_tab[0]>>8);
    KV_START = (u8)((u16)&key_tone_tab[0]);

    KV_END = (u8)((u16)&key_tone_tab[15]>>8);
    KV_END = (u8)((u16)&key_tone_tab[15]);
}

/*----------------------------------------------------------------------------*/
/** @brief: �� DAC ģ��
    @param: vcom_outen��VCOM_OUT ʹ�ܿ���λ
    @param: dac_vdden��DAC_VDD ʹ�ܿ���λ
    @return:void
    @author:Juntham
    @note:  void dac_on(bool vcom_outen, bool dac_vdden)
*/
/*----------------------------------------------------------------------------*/
void dac_on(bool vcom_outen, bool dac_vdden) AT(DAC_CODE)
{
    DAA_CON1 |= 0x1f;           //����Ϊ��С
    DAA_CON2 |= 0x1f;

    if (dac_vdden)              //ʹ��DAC_VDD,���1UF���ݣ�SNR���3dB,��ģʽ�£�������ӵ���
    {
       DAA_CON0 = 0x47;
    }
    else                        //����ҪDAC_VDD����
    {
        DAA_CON0 = 0x4B;

        if (vcom_outen)             //DAC_VDD���VCOM��ֻ�в�ʹ��DAC_VDDʱ���ſ�ʹ��VCOM OUT
            DAA_CON4 |= BIT(6);
    }

    delay8(100);
    DAA_CON4 |= BIT(5);
    DAC_CON0 |= BIT(4);
}

/*----------------------------------------------------------------------------*/
/** @brief: �� DAC ģ�飨�������е��ã�
    @param: void
    @return:void
    @author:Juntham
    @note:  void dac_on_asm(void)
*/
/*----------------------------------------------------------------------------*/
void dac_on_asm(void) AT(DAC_CODE)
{
#ifdef DAC_VDD_EN
    dac_on(0,1);
#else
    #ifdef VCOMO_EN
    dac_on(1,0);
    #else
    dac_on(0,0);
#endif  /*  VCOMO_EN    */
#endif  /*  DAC_VDD_EN  */
}

/*----------------------------------------------------------------------------*/
/** @brief: DAC ģ���ʼ����������ࣩ
    @param: void
    @return:void
    @author:Juntham
    @note:  void DAC_init(void)
*/
/*----------------------------------------------------------------------------*/
void DAC_init(void) AT(DAC_CODE)
{
    DAC_setting();
    main_vol_L = get_memory(MEM_VOL_L);
    main_vol_L = ((main_vol_L > MAX_MAIN_VOL_L) || (main_vol_L == 0)) ? 15 : main_vol_L;
    main_vol_R = get_memory(MEM_VOL_R);
    main_vol_R = ((main_vol_R > MAX_MAIN_VOL_R) || (main_vol_R == 0)) ? 15 : main_vol_R;
    obuf_setting(OBUF_REST);            //reset obuf
#if defined KEY_VOICE_EN || defined RTC_ALARM_EN
    key_tone_init();
#endif
}

/*----------------------------------------------------------------------------*/
/** @brief: �ر�DAC
    @param: foating: 1,����  0,���ֵ���
    @return:
    @author:Juntham
    @note:
*/
/*----------------------------------------------------------------------------*/
void dac_off(bool foating) AT(DAC_CODE)
{
    dac_fade_out();
    DAA_CON4 &= ~BIT(5);            //VCM diable
    delay_n10ms(200);               //wait 2.5s
    DAA_CON4 = 0x10;
    if (foating)
        DAA_CON0 = 0x40;
    else
        DAA_CON0 = 0x0;
    DAA_CON1 = 0x0;
    DAA_CON2 = 0x0;
    DAA_CON3 = 0x0;
    DAC_CON0 = 0x0;
    DAC_CON1 = 0x0;
}
/*----------------------------------------------------------------------------*/
/** @brief: DAC ͨ�����ú���
    @param: channel������ͨ��/ģ��ͨ��
    @return:void
    @author:Juntham
    @note:  void dac_channel_sel(u8 channel)
*/
/*----------------------------------------------------------------------------*/
_near_func void dac_channel_sel(u8 channel) AT(COMMON_CODE)
{
    dac_fade_out();

    asm("PUSH 0xA8");
    asm("CLR 0xA8.7");

    DAA_CON4 &= 0xf0;
    DAA_CON0 &= ~(BIT(4) | BIT(0));
    amux = 0;

    if (channel == DAC_DECODER)
    {
        DAA_CON0 |= BIT(0);
        set_digital_vol(main_vol_L, main_vol_R);
    }
    else if (channel == DAC_AMUX0)      //P24P25
    {
        u8 temp;

        /*AUX 0 I/O Input*/
        P2DIE &= ~0x30;                 //��ǰͨ����Ϊģ��IO����Ҫ����ʵ��ʹ�õ�IO��������޸�
        P2DIR |= 0x30;
        temp = DAA_CON4 & 0xf0;
        temp |= 0x03;
        DAA_CON4 = temp;
        DAA_CON0 |= BIT(4);
        amux = 1;
    }
    else if(channel == DAC_AMUX1)       //P26P27
    {
        u8 temp;

        /*AUX 0 I/O Input*/
        P2DIE &= ~0xC0;                 //��ǰͨ����Ϊģ��IO����Ҫ����ʵ��ʹ�õ�IO��������޸�
        P2DIR |= 0xC0;
        temp = DAA_CON4 & 0xf0;
        temp |= 0x0c;
        DAA_CON4 = temp;
        DAA_CON0 |= BIT(4);
        amux = 1;
    }

    asm("POP 0xA8");

    dac_fade_in();
}

/*----------------------------------------------------------------------------*/
/** @brief: DAC ����������
    @param: flag����������λ
    @return:void
    @author:Juntham
    @note:  void dac_mute(bool flag)
*/
/*----------------------------------------------------------------------------*/
void dac_mute(bool flag) AT(DAC_CODE)
{
    if (flag)
    {
        mute = 1;
        dac_fade_out();
		set_digital_vol(0, 0);
        P2PU  |= BIT(4);
        P2DIE |= BIT(4);
        P2DIR &=~BIT(4);
        P24    = 1;
    }
    else
    {
        P2PU  |= BIT(4);
        P2DIE |= BIT(4);
        P2DIR &=~BIT(4);
        P24    = 0;
        mute = 0;
        set_digital_vol(main_vol_L, main_vol_R);
        dac_fade_in();
    }
}

/*----------------------------------------------------------------------------*/
/** @brief: DAC �����л�����
    @param: void
    @return:void
    @author:Juntham
    @note:  void dac_mute_toggle(void)
*/
/*----------------------------------------------------------------------------*/
void dac_mute_toggle(void) AT(DAC_CODE)
{
    dac_mute(!mute);
}
