/*******************************************************************************************
File Name:  IRFF00.h

Version:    1.00

Discription: ���ⰴ���� 0xFF00

Author:     Caibingquan

Email:      change.tsai@gmail.com

Date:       2012.06.04

Copyright:(c) 2012 , All Rights Reserved.
*******************************************************************************************/
#ifndef	_AD_KEY_H_
#define _AD_KEY_H_

/*-----------FPGA use-------------------*/
#define AD_VDD      (u16)0xff80
#define AD_VOL1     (u16)0xc8c0
#define AD_VOL2     (u16)0x9680
#define AD_VOL3     (u16)0x6440
#define AD_VOL4     (u16)0x3200
#define AD_GND      (u16)0x0000

//#define AD_NOKEY    ((((u16)AD_VDD - AD_VOL1)>>1) + AD_VOL1)
#define AD_KEY1     ((((u16)AD_VOL1 - AD_VOL2)>>1) + AD_VOL2)
#define AD_KEY2     ((((u16)AD_VOL2 - AD_VOL3)>>1) + AD_VOL3)
#define AD_KEY3     ((((u16)AD_VOL3 - AD_VOL4)>>1) + AD_VOL4)
#define AD_KEY4     ((((u16)AD_VOL4 - AD_GND)>>1) + AD_GND)


/*-------------ADKEY GROUP 1----------------*/
#define AD_NOKEY		(0xff40-0xe840)/2+0xe840
#define ADKEY1_0		(0xe800-0xd1c0)/2+0xd1c0
#define ADKEY1_1		(0xd140-0xb2c0)/2+0xb2c0
#define ADKEY1_2		(0xb2c0-0x99c0)/2+0x99c0
#define ADKEY1_3		(0x9980-0x85c0)/2+0x85c0
#define ADKEY1_4		(0x8540-0x67c0)/2+0x67c0
#define ADKEY1_5		(0x66c0-0x4ac0)/2+0x4ac0
#define ADKEY1_6		(0x49c0-0x3740)/2+0x3740
#define ADKEY1_7		(0x3700-0x1e80)/2+0x1e80
#define ADKEY1_8		(0x1e40-0x0)/2+0x0


const u16 ad_key_table[] AT (TABLE_CODE)=
{
    ADKEY1_0,ADKEY1_1,ADKEY1_2,ADKEY1_3,ADKEY1_4,
    ADKEY1_5,ADKEY1_6,ADKEY1_7,ADKEY1_8
};


#define ADKEY1_MUSIC_SHORT		\
                                /*00*/    NO_MSG,\
							    /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    MSG_MUSIC_PREV_FILE,\
								/*04*/    MSG_MUSIC_NEXT_FILE,\
								/*05*/    MSG_MUSIC_PP,\
								/*06*/    MSG_VOL_UP,\
								/*07*/    MSG_VOL_DOWN,\
								/*08*/    MSG_CHANGE_WORK_MODE,\
								/*09*/    MSG_MUTE,

#define ADKEY1_MUSIC_LONG		\
                                /*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    MSG_MUSIC_FR,\
								/*04*/    MSG_MUSIC_FF,\
								/*05*/    NO_MSG,\
								/*06*/    MSG_VOL_UP,\
								/*07*/    MSG_VOL_DOWN,\
								/*08*/    NO_MSG,\
								/*09*/    MSG_STOP,


#define ADKEY1_MUSIC_HOLD		\
                                /*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    MSG_MUSIC_FR,\
								/*04*/    MSG_MUSIC_FF,\
								/*05*/    NO_MSG,\
								/*06*/    MSG_VOL_UP,\
								/*07*/    MSG_VOL_DOWN,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,

#define ADKEY1_MUSIC_LONG_UP	\
                                /*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,

const u8 adkey_msg_music_table[][10] AT (TABLE_CODE)=				//Musicģʽ�µ�ң��ת����
{
    /*�̰�*/	  {ADKEY1_MUSIC_SHORT},
    /*����*/		{ADKEY1_MUSIC_LONG},
    /*����*/		{ADKEY1_MUSIC_HOLD},
    /*����̧��*/	{ADKEY1_MUSIC_LONG_UP},
};

#define ADKEY1_FM_SHORT			\
                                /*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    MSG_FM_PREV_STATION,\
								/*04*/    MSG_FM_NEXT_STATION,\
								/*05*/    NO_MSG,\
								/*06*/    MSG_VOL_UP,\
								/*07*/    MSG_VOL_DOWN,\
								/*08*/    MSG_CHANGE_WORK_MODE,\
								/*09*/    MSG_MUTE,

#define ADKEY1_FM_LONG			\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    MSG_FM_SCAN_ALL_DOWN,\
								/*04*/    MSG_FM_SCAN_ALL_UP,\
								/*05*/    NO_MSG,\
								/*06*/    MSG_VOL_UP,\
								/*07*/    MSG_VOL_DOWN,\
								/*08*/    MSG_FM_SCAN_ALL_INIT,\
								/*09*/    MSG_STOP,

#define ADKEY1_FM_HOLD			\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    MSG_VOL_UP,\
								/*07*/    MSG_VOL_DOWN,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,


#define ADKEY1_FM_LONG_UP		\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,

const u8 adkey_msg_fm_table[][10] AT (TABLE_CODE)=				//Musicģʽ�µ�ң��ת����
{
    /*�̰�*/	    {ADKEY1_FM_SHORT},
    /*����*/		{ADKEY1_FM_LONG},
    /*����*/		{ADKEY1_FM_HOLD},
    /*����̧��*/	{ADKEY1_FM_LONG_UP},
};


#endif /*   _AD_KEY_H_  */
