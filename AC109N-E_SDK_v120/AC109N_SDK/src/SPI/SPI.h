#ifndef _SPI_H_
#define _SPI_H_


#include "config.h"

#ifdef __IAR_SYSTEMS_ICC__
/*----------------------------------------------------------------------------*/
/**@brief   SPI Flash �������ú���
   @param   cmd�����
   @param cmd[0] - Write Enable		/
   @param cmd[1] - Write Disbale	/
   @param cmd[2] - Read SR			/
   @param cmd[3] - Write SR
   @param cmd[4] - Read Data		/
   @param cmd[5] - Page Program		/
   @param cmd[6] - Sector Erase
   @param cmd[7] - Block Erase
   @param cmd[8] - Chip Erase
   @param cmd[9] - Power Down
   @param cmd[10] - Release Power Down
   @param cmd[11] - JEDEC ID
   @param cmd[12] - Read Manufacture
   @return  ��
   @note    void SPI_FlashCMD_setting(u8 _xdata *cmd)
*/
/*----------------------------------------------------------------------------*/
typedef struct _SPI_WR_PARA
{
    u8  write;
    u8  read;
    u8  fast_read;
    u8  read_sr;
    u8  write_en;
    u8  write_dis;
    u32 addr;
    u8 _xdata * buf;
    u16 len;
}SPI_WR_PARA;


void SPI_init(void);
void SPI_run(void);



/*******************************************/
/*
            Maskrom API
                --SPI Part
*/
/*******************************************/
/*----------------------------------------------------------------------------*/
/**@brief 	SPI FLASH ��ȡ����
   @param 	buf����ȡ��ID�Ż���
   @return  void
   @note  	void SPI_flash_readID(u8 _xdata *buf)
*/
/*----------------------------------------------------------------------------*/
_near_func void SPI_flash_readID(u8 _xdata *buf);
/*----------------------------------------------------------------------------*/
/**@brief 	SPI FLASH ��������
   @param 	cmd����������
   @param 	address��������ַ
   @return  void
   @note  	void spi_erase(u8 cmd,u32 address)
*/
/*----------------------------------------------------------------------------*/
_near_func void spi_erase(u8 cmd,u32 address);
/*----------------------------------------------------------------------------*/
/**@brief 	SPI FLASH ������
   @param 	addr����ȡ��ʼ��ַ
   @param 	len����ȡ����
   @param 	buf�����ݻ�����
   @return  void
   @note  	void SPI_flash_read(u32 addr, u16 len, u8 _xdata *buf)
*/
/*----------------------------------------------------------------------------*/
_near_func void SPI_flash_read(u32 addr, u16 len, u8 _xdata *buf);
/*----------------------------------------------------------------------------*/
/**@brief 	SPI FLASH д����
   @param 	addr��д����ʼ��ַ
   @param 	len��д�볤��
   @param 	buf�����ݻ�����
   @return  void
   @note  	void SPI_flash_write(u32 addr, u16 len, u8 _xdata *buf)
*/
/*----------------------------------------------------------------------------*/
_near_func void SPI_flash_write(u32 addr, u16 len, u8 _xdata *buf);
_near_func void set_hook_SPI(void (_near_func * fun)(u8));
_near_func u16 get_spi_var(void);

#endif  /*  __IAR_SYSTEMS_ICC__ */

/*************************************************/
/*
		COMMAND LIST - WinBond FLASH WX25X10
*/
/*************************************************/
#define WINBOND_WRITE_ENABLE	0x06
#define WINBOND_WRITE_DISABLE	0x04
#define WINBOND_READ_SR			0x05
#define WINBOND_WRITE_SR		0x01
#define WINBOND_READ_DATA		0x03
#define WINBOND_FAST_READ		0x0B
#define WINBOND_FAST_READ_DUAL	0x3B
#define WINBOND_PAGE_PROGRAM	0x02
#define WINBOND_SECTOR_ERASE	0x20
#define WINBOND_BLOCK_ERASE		0xD8
#define WINBOND_CHIP_ERASE		0xC7
#define WINBOND_POWER_DOWN		0xB9
#define WINBOND_RELEASE			0xAB
#define WINBOND_MANUFACTURE		0x90
#define WINBOND_JEDEC_ID		0x9F

#endif  /*  _SPI_H_   */
