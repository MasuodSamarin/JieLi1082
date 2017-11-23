/*--------------------------------------------------------------------------*/
/**@file    iic.c
   @brief   IIC �ӿں���
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "iic.h"
#include "RTC_API.h"
#include "sdmmc_api.h"
#include "play_file.h"
#include "device.h"
#include "IRTC.h"

//#define IIC_DAT_USE_P02

bool iic_busy;

__code const u16 iic_io_tab[8] AT(TABLE_CODE)=
{
    (u16)iic_data_out,
    (u16)iic_data_in,
    (u16)iic_data_r,
    (u16)iic_data,
    (u16)iic_clk_out,
    (u16)iic_clk,
};


/*----------------------------------------------------------------------------*/
/** @brief: IIC dat I/O �����������
    @param: void
    @return:void
    @author:Juntham
    @note:  void iic_data_out(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_data_out(void) AT(COMMON_CODE)
{
#ifdef IIC_DAT_USE_P02
    P0DIR &= ~(1<<2);
#else
    P0DIR &= ~(1<<1);
#endif
}


/*----------------------------------------------------------------------------*/
/** @brief: IIC dat I/O �������뺯��
    @param: void
    @return:void
    @author:Juntham
    @note:  void iic_data_in(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_data_in(void) AT(COMMON_CODE)
{
#ifdef IIC_DAT_USE_P02
    P0DIR |= (1<<2);
    P0PU |= (1<<2);
#else
    P0DIR |= (1<<1);
    P0PU |= (1<<1);
#endif
}


/*----------------------------------------------------------------------------*/
/** @brief: IIC dat I/O ��ȡ����
    @param: void
    @return:��ȡ��ֵ
    @author:Juntham
    @note:  bool iic_data_r(void)
*/
/*----------------------------------------------------------------------------*/
_near_func bool iic_data_r(void) AT(COMMON_CODE)
{
#ifdef IIC_DAT_USE_P02
    return P02;
#else
    return P01;
#endif
}

/*----------------------------------------------------------------------------*/
/** @brief: IIC dat I/O ���ֵ���ú���
    @param: flag�������ƽ
    @return:void
    @author:Juntham
    @note:  void iic_data(bool flag)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_data(bool flag) AT(COMMON_CODE)
{
#ifdef IIC_DAT_USE_P02
    P02 = flag;
#else
    P01 = flag;
#endif
}

/*----------------------------------------------------------------------------*/
/** @brief: IIC dat I/O ���ֵ���ú���
    @param: flag�������ƽ
    @return:void
    @author:Juntham
    @note:  void iic_clk_out(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_clk_out(void) AT(COMMON_CODE)
{
    P0DIR &= ~(1<<0);
}

/*----------------------------------------------------------------------------*/
/** @brief: IIC dat I/O ���ֵ���ú���
    @param: flag�������ƽ
    @return:void
    @author:Juntham
    @note:  void iic_clk(bool flag)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_clk(bool flag) AT(COMMON_CODE)
{
    P00 = flag;
}



/*----------------------------------------------------------------------------*/
/** @brief: IIC ģ���ʼ������
    @param: void
    @return:void
    @author:Juntham
    @note:  void iic_init(void)
*/
/*----------------------------------------------------------------------------*/
void iic_init(void) AT(IIC_CODE)
{
    set_iic_io((u16 __code *)iic_io_tab);       ///<���ýӿں���IO
}

void eeprom_verify(void) AT(IIC_CODE)
{
    unsigned char i;

#ifdef CHECK_EEPROM_ON_POWER_ON
	if ((get_memory(0) != 0x55)
        ||(get_memory(1) != 0xAA))
	{
        //deg_puts("reset EEPROM\n");
        set_memory(0, 0x55);
        set_memory(1, 0xAA);
        for(i=2;i<MEM_CHANNL;i++)
          set_memory(i, 0);
    }

    if ((get_memory(0) != 0x55)
        ||(get_memory(1) != 0xAA))
	{
        //���eeprom��Ч
        //deg_puts("EEPROM error\n");
    }
    else
    {
        //deg_puts("EEPROM OK\n");
        //�����eeprom
        //my_puts("find eeprom\n");
    }
#endif

}

/*----------------------------------------------------------------------------*/
/** @brief: ������Ϣ���洢����EEPROM��
    @param: void
    @return:void
    @author:Juntham
    @note:  void set_memory(u8 addr, u8 dat)
*/
/*----------------------------------------------------------------------------*/
_near_func void set_memory(u8 addr, u8 dat) AT(COMMON_CODE)
{
    //EA = 0;
#ifdef USE_EEPROM_MEMORY
    write_eerom(addr, dat);
#endif
#ifdef USE_IRTC_MEMORY
    write_IRTC_RAM(addr, dat);
#endif
    //EA = 1;
}
/*----------------------------------------------------------------------------*/
/** @brief: ��ȡ������Ϣ��EEPROM��
    @param: void
    @return:void
    @author:Juntham
    @note:  u8 get_memory(u8 addr)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 get_memory(u8 addr) AT(COMMON_CODE)
{
    u8 ret;

    //EA = 0;
#ifdef USE_EEPROM_MEMORY
//    return read_eerom(addr);
    ret = read_eerom(addr);
#endif
#ifdef USE_IRTC_MEMORY
//    return read_IRTC_RAM(addr);
    ret = read_IRTC_RAM(addr);
#endif
    //EA = 1;
    return ret;
}

