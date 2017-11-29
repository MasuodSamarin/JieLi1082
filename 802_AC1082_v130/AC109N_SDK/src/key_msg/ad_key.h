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


/*-------------ADKEY GROUP 1----------------*///0XF3C0
#define AD_NOKEY		(0xff40-0xe840)/2+0xe840   //220//

#define ADKEY1_0		(0xe500-0xc640)/2+0xc640   //100
#define ADKEY1_1		(0xc640-0xb2c0)/2+0xb2c0  // 51
#define ADKEY1_2		(0xb2c0-0x99c0)/2+0x99c0   //33
#define ADKEY1_3		(0x9980-0x85c0)/2+0x85c0   //24
#define ADKEY1_4		(0x8540-0x67c0)/2+0x67c0   //15
#define ADKEY1_5		(0x66c0-0x4ac0)/2+0x4ac0  //9.1
#define ADKEY1_6		(0x49c0-0x3740)/2+0x3740  //   6.2
#define ADKEY1_7		(0x3700-0x1e80)/2+0x1e80  //3//
#define ADKEY1_8		(0x1e40-0x0)/2+0x0    //0



/*
#define ADKEY1_0        0xef00
#define ADKEY1_1        0xec00
#define ADKEY1_2        0xeb00
#define ADKEY1_3        0xea40
#define ADKEY1_4        0xe400         //51K
#define ADKEY1_5        0xcd00         //33K
#define ADKEY1_6        0xb800         //20K
#define ADKEY1_7	0x8f00         //10K
#define ADKEY1_8	0x4000         //0R
*/


const u16 ad_key_table[] AT (TABLE_CODE)=
{
    ADKEY1_0,ADKEY1_1,ADKEY1_2,ADKEY1_3,ADKEY1_4,
    ADKEY1_5,ADKEY1_6,ADKEY1_7,ADKEY1_8
};


#define ADKEY1_MUSIC_SHORT		\
                                                                /*00*/    NO_MSG,\
							        /*01*/    NO_MSG,\
								/*02*/    MSG_MUSIC_NEXT_FILE,\
								/*03*/    MSG_MUSIC_NEXT_EQ,\
								/*04*/    MSG_NEXT_PLAYMODE,\
								/*05*/    MSG_MUSIC_PP,\
								/*06*/    MSG_MUSIC_PREV_FILE,\
								/*07*/    MSG_MUSIC_NEXT_FILE,\
								/*08*/    MSG_MUSIC_PREV_FILE,\
								/*09*/    MSG_USB_TO_SD,

#define ADKEY1_MUSIC_LONG		\
                                                                /*00*/    NO_MSG,\
                                                                /*01*/    NO_MSG,\
								/*02*/    MSG_MUSIC_FF,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    MSG_VOL_DOWN,\
								/*07*/    MSG_VOL_UP,\
								/*08*/    MSG_MUSIC_FR,\
								/*09*/    NO_MSG,


#define ADKEY1_MUSIC_HOLD		\
                                                                /*00*/    NO_MSG,\
                                                                /*01*/    NO_MSG,\
								/*02*/    MSG_MUSIC_FF,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    MSG_VOL_DOWN,\
								/*07*/    MSG_VOL_UP,\
								/*08*/    MSG_MUSIC_FR,\
								/*09*/    NO_MSG,

#define ADKEY1_MUSIC_LONG_UP	\
                                                                /*00*/    NO_MSG,\
                                                                /*01*/    NO_MSG,\
								/*02*/    MSG_MUSIC_FFR_DONE,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    MSG_MUSIC_FFR_DONE,\
								/*09*/    NO_MSG,
const u8 adkey_msg_music_table[3][10] AT (TABLE_CODE)=				//Musicģʽ�µ�ң��ת����
{
    /*�̰�*/	    {ADKEY1_MUSIC_SHORT},
    /*����*/		{ADKEY1_MUSIC_LONG},
    /*����*/		{ADKEY1_MUSIC_HOLD},
    ///*����̧��*/	{ADKEY1_MUSIC_LONG_UP},
};

#define ADKEY1_FM_SHORT			\
                                /*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
				/*02*/    MSG_FM_NEXT_STATION,\
				/*03*/    NO_MSG,\
				/*04*/    NO_MSG,\
				/*05*/    MSG_MUSIC_PP,\
				/*06*/    MSG_FM_PREV_STATION,\
				/*07*/    MSG_FM_NEXT_STATION,\
				/*08*/    MSG_FM_PREV_STATION,\
				/*09*/    MSG_NEXT_WORKMODE,

#define ADKEY1_FM_LONG			\
				/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
				/*02*/    NO_MSG,\
				/*03*/    NO_MSG,\
				/*04*/    NO_MSG,\
				/*05*/    MSG_FM_SCAN_ALL_INIT,\
				/*06*/    MSG_VOL_DOWN,\
				/*07*/    MSG_VOL_UP,\
				/*08*/    NO_MSG,\
				/*09*/    NO_MSG,

#define ADKEY1_FM_HOLD			\
				/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
				/*02*/    NO_MSG,\
				/*03*/    NO_MSG,\
				/*04*/    NO_MSG,\
				/*05*/    NO_MSG,\
				/*06*/    MSG_VOL_DOWN,\
				/*07*/    MSG_VOL_UP,\
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

const u8 adkey_msg_fm_table[3][10] AT (TABLE_CODE)=				//Musicģʽ�µ�ң��ת����
{
    /*�̰�*/	    {ADKEY1_FM_SHORT},
    /*����*/		{ADKEY1_FM_LONG},
    /*����*/		{ADKEY1_FM_HOLD},
    ///*����̧��*/	{ADKEY1_FM_LONG_UP},
};


#endif /*   _AD_KEY_H_  */
