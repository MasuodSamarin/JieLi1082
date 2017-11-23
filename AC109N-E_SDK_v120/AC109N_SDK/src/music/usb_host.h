/*************************************************************/
/** @file:usb_host.h
    @brief:
    @details:
    @author:Juntham
    @date: 2012-07-25,8:59
    @note:
*/
/*************************************************************/

#ifndef _USB_HOST_H_
#define _USB_HOST_H_

#include "config.h"


#ifdef __IAR_SYSTEMS_ICC__

typedef struct _USB_DETECT
{
    u8 online;     		//<USB ���߱�־	[0]:USB Host [1]:USB Slave
    u8 online_counter;  //<USB ���߼�����
    u8 last_data;       //<USB �������Ѽ���ֵ
    u8 current_data;    //<USB ��������ǰ����ֵ
    volatile u8 time_out;		//<USB ������ʱ������
}USB_DETECT;


_near_func void USB_online_otp(void);
bool write_udisk(void);
u8 usb_host_mount_app(u8 retry, u8 timeout, u8 reset_delay, u8 test_delay);
void force_usb_suspend(void);
__monitor void USB_Host_init(void);
u8 USB_Online_app(void);

/////
#ifdef UDISK_IDLE_EN
#define udisk_force_idle() usb_suspend()
#else
#define udisk_force_idle()
#endif
//////



/*******************************************/
/*
            Maskrom API
                --USB Host Part
*/
/*******************************************/
/*----------------------------------------------------------------------------*/
/**@brief   USB ���߼��
   @param   void
   @return  0x1:Host offline 0x2:Device offline 0x3:Host online 0x4:Device online
   @author  Change.tsai
   @note	u8 USB_Online(void)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 USB_Online(void);
/*----------------------------------------------------------------------------*/
/**@brief   ����USB Host����״̬
   @param   void
   @return  void
   @author  Change.tsai
   @note	void usb_host_status(u8 status)
*/
/*----------------------------------------------------------------------------*/
_near_func void usb_host_status(u8 status);
/*----------------------------------------------------------------------------*/
/**@brief   USB �������������ģʽ
   @param   void
   @return  void
   @author  Change.tsai
   @note	void usb_suspend(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void usb_suspend(void);
/*----------------------------------------------------------------------------*/
/**@brief   USB Host ����
   @param   void
   @return  0������ʧ�ܣ�1�����سɹ�
   @author  Change.tsai
   @note	u8 usb_host_mount(u8 retry, u8 timeout, u8 init_delay, u8 reset_delay, u8 test_delay)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 usb_host_mount(u8 retry, u8 timeout, u8 reset_delay, u8 test_delay);
/*----------------------------------------------------------------------------*/
/**@brief   USB �������ָ���ͨI/Oģʽ
   @param   void
   @return  ж�سɹ�
   @author  Change.tsai
   @note	u8 usb_host_unmount(void)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 usb_host_unmount(void);
/*----------------------------------------------------------------------------*/
/**@brief   USB Host ���ӿ�
   @param   buf�����ݻ�������lba�������ַ
   @return  0���ɹ���other��ʧ��
   @author  Change.tsai
   @note	u8 usb_host_read(u8 _xdata *buf, u32 lba)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 usb_host_read(u8 _xdata *buf, u32 lba);
/*----------------------------------------------------------------------------*/
/**@brief   USB Host д�ӿ�
   @param   buf�����ݻ�������lba�������ַ
   @return  0���ɹ���other��ʧ��
   @author  Change.tsai
   @note	u8 usb_host_write(u8 _xdata *buf, u32 lba)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 usb_host_write(u8 _xdata *buf, u32 lba);
/*----------------------------------------------------------------------------*/
/**@brief   USB ��ʱ������
   @param   void
   @return  0����ʱ��other���豸����״̬
   @author  Change.tsai
   @note	bool USB_Host_timeout(void)
*/
/*----------------------------------------------------------------------------*/
_near_func _bool USB_Host_timeout();
/*----------------------------------------------------------------------------*/
/**@brief   USB ��ȡʣ�����ݽӿں���
   @param   void
   @return  ����ɹ���־
   @author  Change.tsai
   @note	_bool USB_read_remain(void)
*/
/*----------------------------------------------------------------------------*/
_near_func _bool USB_read_remain(void);


/*----------------------------------------------------------------------------*/
/**@brief   ��ȡUSB �豸sector��С
   @param   void
   @return  0����ʱ��other���豸����״̬
   @note	u8 get_usb_pkt_size(void)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 get_usb_pkt_size(void);
/*----------------------------------------------------------------------------*/
/**@brief   ��ȡUSB ����״̬
   @param   void
   @return  void
   @author  Change.tsai
   @note	u8 get_usb_online_status(void)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 get_usb_online_status(void);
/*----------------------------------------------------------------------------*/
/**@brief   ��ȡUSB �Ĵ���
   @param   addr���Ĵ�����ַ
   @return  �Ĵ�����ֵ
   @author  Change.tsai
   @note	u8 read_USB_reg(u8 addr)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 read_USB_reg(u8 addr);
/*----------------------------------------------------------------------------*/
/**@brief   д��USB �Ĵ���
   @param   addr��д���ַ
   @return  value��д������
   @author  Change.tsai
   @note	void write_USB_reg(u8 addr , u8 value)
*/
/*----------------------------------------------------------------------------*/
_near_func void write_USB_reg(u8 addr , u8 value);
/*----------------------------------------------------------------------------*/
/**@brief   USB ���ƴ�����������
   @param   void
   @return  ����ɹ���־
   @author  Change.tsai
   @note	_bool USB_ctlXfer(u8 _xdata *buf)
*/
/*----------------------------------------------------------------------------*/
_near_func _bool USB_ctlXfer(u8 _xdata *buf);
/*----------------------------------------------------------------------------*/
/**@brief   USB ���ƴ��䴦����
   @param   void
   @return  ����ɹ���־
   @author  Change.tsai
   @note	_bool USB_Control_transfers(void)
*/
/*----------------------------------------------------------------------------*/
_near_func _bool USB_Control_transfers(void);
/*----------------------------------------------------------------------------*/
/**@brief   USB Host Deviceö��
   @param   void
   @return  �豸ö�ٳɹ���־
   @author  Change.tsai
   @note	_bool USB_Host_dev_enum(u8 _xdata *buf, u16 delay_max)
*/
/*----------------------------------------------------------------------------*/
_near_func _bool USB_Host_dev_enum(u8 _xdata *buf, u8 delay_max);
/*----------------------------------------------------------------------------*/
/**@brief   USB Host Mass Storageö��
   @param   void
   @return  Mass Storageö�ٳɹ���־
   @author  Change.tsai
   @note	_bool USB_Host_Mass_Storage_enum(u8 _xdata *buf, u8 delay)
*/
/*----------------------------------------------------------------------------*/
_near_func _bool USB_Host_Mass_Storage_enum(u8 _xdata *buf, u8 delay);
/*----------------------------------------------------------------------------*/
/**@brief   USB Finite State Machine
   @param   buf���������ݻ�������64Bytes��
   @return  0��MSD ö�ٳɹ���1��״̬��������2���������ö��ʧ�� 3���˵�0ö��û�з���MSD �˵� 4��MSD �豸����
   @author  Change.tsai
   @note	u8 USB_FSM(u8 __xdata *buf)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 USB_FSM(u8 _xdata *buf);
/*----------------------------------------------------------------------------*/
/**@brief   UFI Command Block-Inquiry
   @param   void
   @return  ����ɹ���־
   @author  Change.tsai
   @note	_bool USB_UFI_Inquiry(void)
*/
/*----------------------------------------------------------------------------*/
_near_func _bool USB_UFI_Inquiry(void);
/*----------------------------------------------------------------------------*/
/**@brief   UFI Command Block-Test_unit_ready
   @param   void
   @return  ����ɹ���־
   @author  Change.tsai
   @note	_bool USB_UFI_Test_unit_ready(void)
*/
/*----------------------------------------------------------------------------*/
_near_func _bool USB_UFI_Test_unit_ready(void);
/*----------------------------------------------------------------------------*/
/**@brief   UFI Command Block-Request_sense
   @param   void
   @return  ����ɹ���־
   @author  Change.tsai
   @note	_bool USB_UFI_Request_sense(void)
*/
/*----------------------------------------------------------------------------*/
_near_func _bool USB_UFI_Request_sense(void);
/*----------------------------------------------------------------------------*/
/**@brief   UFI Command Block-Request_sense
   @param   void
   @return  ����ɹ���־
   @author  Change.tsai
   @note	_bool USB_UFI_Request_sense(void)
*/
/*----------------------------------------------------------------------------*/
_near_func _bool USB_UFI_Ready_capacity(void);
/*----------------------------------------------------------------------------*/
/**@brief   ��ȡUSB Host ����
   @param   void
   @return  ������ַ
   @author  Change.tsai
   @note	u16 get_usb_host_var(void)
*/
/*----------------------------------------------------------------------------*/
_near_func u16 get_usb_host_var(void);
/*----------------------------------------------------------------------------*/
/**@brief   ��ȡUSB Host ����
   @param   void
   @return  ������ַ
   @author  Change.tsai
   @note	u16 get_usb_host_var(void)
*/
/*----------------------------------------------------------------------------*/
_near_func u16 get_usb_host_detect(void);
/*----------------------------------------------------------------------------*/
/**@brief   ��ȡUSB ���ƴ����������
   @param   void
   @return  ������ַ
   @author  Change.tsai
   @note	u16 get_usb_control_var(void)
*/
/*----------------------------------------------------------------------------*/
_near_func u16 get_usb_host_control_var(void);
/*----------------------------------------------------------------------------*/
/**@brief   ��ȡUSB ���ƴ�����̱���
   @param   void
   @return  ������ַ
   @author  Change.tsai
   @note	u16 get_usb_ctlXfer_var(void)
*/
/*----------------------------------------------------------------------------*/
_near_func u16 get_usb_host_ctlXfer_var(void);
/*----------------------------------------------------------------------------*/
/**@brief   ��ȡUSB Bulk-Only������̱���
   @param   void
   @return  ������ַ
   @author  Change.tsai
   @note	u16 get_usb_bulkXfer_var(void)
*/
/*----------------------------------------------------------------------------*/
_near_func u16 get_usb_host_bulkXfer_var(void);
/*----------------------------------------------------------------------------*/
/**@brief   ��ȡUSB Bulk-Only�����������
   @param   void
   @return  ������ַ
   @author  Change.tsai
   @note	u16 get_usb_bulk_var(void)
*/
/*----------------------------------------------------------------------------*/
_near_func u16 get_usb_host_bulk_var(void);

void get_usb_host_maskrom_ptr(void);
_bool USB_UFI_specify_command(u8 cmd);

_bool judge_usb_host_virkey(void);

#endif


#endif
