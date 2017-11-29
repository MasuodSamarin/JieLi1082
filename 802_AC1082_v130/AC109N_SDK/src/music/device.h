/*--------------------------------------------------------------------------*/
/**@file    DEVICE.h
   @brief   �豸���ƽӿ�
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef __DEVICE_H__
#define __DEVICE_H__


#include "config.h"


#ifdef __SMART_CPU__

typedef enum
{
    DEVICE_UDISK,               //����ռס0λ�ã������Ƿ��ж�U�̵Ĺ���

#ifdef SDMMCA_EN
    DEVICE_SDMMCA,
#endif

#ifdef SDMMCB_EN
    DEVICE_SDMMCB,
#endif

#ifdef SDMMCB_EN
    MAX_DEVICE = DEVICE_SDMMCB,
#elif  defined (SDMMCA_EN)
    MAX_DEVICE = DEVICE_SDMMCA,
#else
    MAX_DEVICE = DEVICE_UDISK,
#endif

    DEVICE_AUTO_NEXT = 0x81,
    DEVICE_AUTO_PREV = 0x82,
    NO_DEVICE = 0xff,
}ENUM_DEVICE_SELECT_MODE;

//#ifdef SDMMC_UDISK_MEMORY
extern _no_init u32 sdmmcA_reserve_lba; ///<SDMMC �������ĵ�ַ
extern _no_init u32 sdmmcB_reserve_lba; ///<SDMMC �������ĵ�ַ
extern _no_init u32 udisk_reserve_lba; ///<UDISK �������ĵ�ַ
extern _no_init u8 _xdata mem_buf[130];
extern _no_init u8 info_change;
bool read_device(u8 dev, bool disable_decode);
bool write_device(u8 dev, bool disable_decode);
void power_up_device_info(void);
void updata_fat_memory (void);
void clear_reserve_lba(void);
//#endif


enum
{
    FIND_DEV_OK      = 0,				//�ɹ��ҵ��豸
    NO_DEFINE_DEV,    					//ָ���豸δ�ҵ�
    DEV_INIT_ERR,     					//�ҵ��豸������ʼ��ʧ��
    NO_EFFECTIVE_DEV,					//����Ч����ʹ�õ��豸
    NO_DEV_ONLINE,    					//�������豸
};

typedef struct _DEVICE_INFO
{
    u16 wBreak_point_filenum;
    u16 wfileTotal;
}DEVICE_INFO;

u8 find_device(ENUM_DEVICE_SELECT_MODE);
u8 device_init(u8 dev);
u8 device_check(void);

extern u8 _data device_active;
extern u8 _data device_online;
extern _no_init bool _bit find_break_point_file_flag;
extern _no_init DEVICE_INFO _idata music_device_info[MAX_DEVICE + 1];

extern u8 get_info_form_device(u8 _xdata * mem,u8 dev)  AT(COMMON_CODE);
extern void power_up_device_info(void) AT(COMMON_CODE);
extern bool write_device(u8 dev, bool disable_decode) AT(GET_DEVICE);
extern void updata_fat_memory (void);
extern void clear_reserve_lba(void);
#endif


#endif
