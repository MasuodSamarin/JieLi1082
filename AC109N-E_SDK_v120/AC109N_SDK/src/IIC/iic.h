

#ifndef _IIC_H_
#define _IIC_H_

#include "config.h"


#ifdef __IAR_SYSTEMS_ICC__


_near_func void iic_data_out(void);
_near_func void iic_data_in(void);
_near_func bool iic_data_r(void);
_near_func void iic_data(bool);
_near_func void iic_clk_out(void);
_near_func void iic_clk(bool);


void iic_init(void);
void sd_write_eeprom(u8 addr, u8 dat);
u8 sd_read_eeprom(u8 addr);
void sd_iic_write(u8 chip_id, u8 iic_addr, u8 *iic_dat, u8 n);
void sd_iic_readn(u8 chip_id, u8 iic_addr, u8 *iic_dat, u8 n);
void eeprom_verify(void);

#define app_IIC_write(a, b, c, d) \
  iic_write(a, b, c, d)
#define app_IIC_readn(a, b, c, d)  \
  iic_readn(a, b, c, d)
#define app_E2PROM_write(a, b)  \
  write_eerom(a, b)
#define app_E2PROM_read(a)   \
  read_eerom(a)



void iic_verify(void);
_near_func void set_memory(u8 addr, u8 dat);
_near_func u8 get_memory(u8 addr);

extern bool iic_busy;

#define MEM_FM_LEN 28



/*******************************************/
/*
            Maskrom API
                --IIC Part
*/
/*******************************************/
/*----------------------------------------------------------------------------*/
/** @brief: ��ȡIIC ��æ��־
    @param: IIC ��ʱ
    @return:��æ��־
    @author:Juntham
    @note:  bool get_iic_busy_status(u8 delay_cnt)
*/
/*----------------------------------------------------------------------------*/
_near_func bool get_iic_busy_status(u8 delay_cnt);
/*----------------------------------------------------------------------------*/
/** @brief: ����IIC ʹ��I/O
    @param: I/O �б�
    @return:void
    @author:Juntham
    @note:  void set_iic_io( u16 __code *p)
*/
/*----------------------------------------------------------------------------*/
_near_func void set_iic_io( u16 __code *p);
/*----------------------------------------------------------------------------*/
/** @brief: IIC Start �ź�
    @param: void
    @return:void
    @author:Juntham
    @note:  void iic_start(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_start(void);
/*----------------------------------------------------------------------------*/
/** @brief: ��IIC ����
    @param: void
    @return:IIC ��ȡ����
    @author:Juntham
    @note:  u8 iic_revbyte( u8 para )
*/
/*----------------------------------------------------------------------------*/
_near_func u8 iic_revbyte(u8 para);
/*----------------------------------------------------------------------------*/
/** @brief: IIC ���ͺ���
    @param: IIC ��������
    @return:void
    @author:Juntham
    @note:  void iic_sendbyte(u8 byte)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_sendbyte(u8 byte);
/*----------------------------------------------------------------------------*/
/** @brief: IIC Stop �ź�
    @param: void
    @return:void
    @author:Juntham
    @note:  void iic_stop(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_stop(void);

/*----------------------------------------------------------------------------*/
/** @brief: IIC д����
    @param: оƬ�ź�
    @param: д��ַ
    @param: д����
    @param: ���ݳ���
    @return:void
    @author:Juntham
    @note:  void iic_write(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_write(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n);
/*----------------------------------------------------------------------------*/
/** @brief: IIC ������
    @param: оƬ�ź�
    @param: ����ַ
    @param: ������
    @param: ���ݳ���
    @return:void
    @author:Juntham
    @note:  void iic_readn(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_readn(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n);
/*----------------------------------------------------------------------------*/
/** @brief: ��ȡ��Ϣ�洢����EEPROM��
    @param: void
    @return:void
    @author:Juntham
    @note:  void set_memory(u8 addr, u8 dat)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 read_eerom(u8 iic_addr);
/*----------------------------------------------------------------------------*/
/** @brief: ������Ϣ���洢����EEPROM��
    @param: void
    @return:void
    @author:Juntham
    @note:  void set_memory(u8 addr, u8 dat)
*/
/*----------------------------------------------------------------------------*/
_near_func void write_eerom(u8 addr,u8 dat);
/*----------------------------------------------------------------------------*/
/** @brief: ������Ϣ���洢����EEPROM��
    @param: void
    @return:void
    @author:Juntham
    @note:  void set_memory(u8 addr, u8 dat)
*/
/*----------------------------------------------------------------------------*/
_near_func void  eeprom_page_write_start(void);
/*----------------------------------------------------------------------------*/
/** @brief: ������Ϣ���洢����EEPROM��
    @param: void
    @return:void
    @author:Juntham
    @note:  void set_memory(u8 addr, u8 dat)
*/
/*----------------------------------------------------------------------------*/
_near_func void  eeprom_page_write_stop(void);
/*----------------------------------------------------------------------------*/
/** @brief: ������Ϣ���洢����EEPROM��
    @param: void
    @return:void
    @author:Juntham
    @note:  void set_memory(u8 addr, u8 dat)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 i2c_master_rbyte(u8 st,u8 ack);
/*----------------------------------------------------------------------------*/
/** @brief: ������Ϣ���洢����EEPROM��
    @param: void
    @return:void
    @author:Juntham
    @note:  void set_memory(u8 addr, u8 dat)
*/
/*----------------------------------------------------------------------------*/
_near_func bool i2c_master_wbyte(u8 st,u8 dat);
/*----------------------------------------------------------------------------*/
/** @brief: ������Ϣ���洢����EEPROM��
    @param: void
    @return:void
    @author:Juntham
    @note:  void set_memory(u8 addr, u8 dat)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 read_eerom_cpu(u8 chip_id, u8 iic_addr);
/*----------------------------------------------------------------------------*/
/** @brief: ������Ϣ���洢����EEPROM��
    @param: void
    @return:void
    @author:Juntham
    @note:  void set_memory(u8 addr, u8 dat)
*/
/*----------------------------------------------------------------------------*/
_near_func void write_eerom_cpu(u8 chip_id, u8 addr,u8 dat);

#endif

enum
{
    EEPROM_SIGN_0 = 0,		 ///<����EEPROMʶ��λ,2��bytes������ʹ��0x55AA
    EEPROM_SIGN_1,
    DEVICE_MEM,
    MEM_SYSMODE,
    MEM_MEDIAMODE,
    MEM_ALARM_0_HOUR,
    MEM_ALARM_0_MIN,
    MEM_ALARM_0_WEEKDAY,
    MEM_VOL_L,
    MEM_VOL_R,
    MEM_VOL_PCL,
    MEM_VOL_PCR,
    
    MEM_EQ_MODE,
    MEM_PLAY_MODE,
    MEM_ACTIVE_DEV,

#ifdef USB_DISK_EN    
    //MEM_USB_PLAYPOINT_ID0,
    MEM_USB_PLAYPOINT_ID1_0,      //2byte
    MEM_USB_PLAYPOINT_ID1_1,
    MEM_USB_PLAYPOINT_ID2_0,      //2byte
    MEM_USB_PLAYPOINT_ID2_1,
    MEM_USB_PLAYPOINT_ID3_0,      //4byte
    MEM_USB_PLAYPOINT_ID3_1,
    MEM_USB_PLAYPOINT_ID3_2,
    MEM_USB_PLAYPOINT_ID3_3,
    MEM_USB_PLAYPOINT_ID4_0,      //4byte
    MEM_USB_PLAYPOINT_ID4_1,
    MEM_USB_PLAYPOINT_ID4_2,
    MEM_USB_PLAYPOINT_ID4_3,
#endif
        
#ifdef SDMMCA_EN    
    //MEM_SDA_PLAYPOINT_ID0,
    MEM_SDA_PLAYPOINT_ID1_0,      //2byte
    MEM_SDA_PLAYPOINT_ID1_1,
    MEM_SDA_PLAYPOINT_ID2_0,      //2byte
    MEM_SDA_PLAYPOINT_ID2_1,
    MEM_SDA_PLAYPOINT_ID3_0,      //4byte
    MEM_SDA_PLAYPOINT_ID3_1,
    MEM_SDA_PLAYPOINT_ID3_2,
    MEM_SDA_PLAYPOINT_ID3_3,
    MEM_SDA_PLAYPOINT_ID4_0,      //4byte
    MEM_SDA_PLAYPOINT_ID4_1,
    MEM_SDA_PLAYPOINT_ID4_2,
    MEM_SDA_PLAYPOINT_ID4_3,
#endif

#ifdef SDMMCB_EN    
    //MEM_SDB_PLAYPOINT_ID0,
    MEM_SDB_PLAYPOINT_ID1_0,      //2byte
    MEM_SDB_PLAYPOINT_ID1_1,
    MEM_SDB_PLAYPOINT_ID2_0,      //2byte
    MEM_SDB_PLAYPOINT_ID2_1,
    MEM_SDB_PLAYPOINT_ID3_0,      //4byte
    MEM_SDB_PLAYPOINT_ID3_1,
    MEM_SDB_PLAYPOINT_ID3_2,
    MEM_SDB_PLAYPOINT_ID3_3,
    MEM_SDB_PLAYPOINT_ID4_0,      //4byte
    MEM_SDB_PLAYPOINT_ID4_1,
    MEM_SDB_PLAYPOINT_ID4_2,
    MEM_SDB_PLAYPOINT_ID4_3,
#endif
    
    MEM_FRE,
    MEM_CHAN,
    MEM_CHANNL,
};

#endif
