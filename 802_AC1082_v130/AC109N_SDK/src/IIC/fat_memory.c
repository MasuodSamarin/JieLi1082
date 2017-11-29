/*--------------------------------------------------------------------------*/
/**@file    fat_memory.c
   @brief   �豸�����ܽӿ�
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "device.h"

///#ifdef SDMMC_UDISK_MEMORY
#include "play_file.h"
#include "get_music_file.h"
#include "music_play.h"
#include "sdmmc_api.h"
#include "break_point.h"
#include "clock.h"
#include "usb_host.h"
#include "iic.h"

__no_init u32 sdmmcA_reserve_lba; ///<SDMMC �������ĵ�ַ
__no_init u32 sdmmcB_reserve_lba; ///<SDMMC �������ĵ�ַ
__no_init u32 udisk_reserve_lba; ///<UDISK �������ĵ�ַ
__no_init u8 _xdata mem_buf[130]; ///<SDMMCA ����Buf
__no_init u8 _xdata mem_buf0[130]; ///<UDISK ����Buf
__no_init u8 _xdata mem_buf1[130]; ///<SDMMCB ����Buf

__no_init u8 info_change;
__no_init u8 device_flag;

void clear_reserve_lba(void) AT(COMMON_CODE)
{
    device_check();
    if ( !( device_online & BIT(DEVICE_SDMMCA) ))
    {
        sdmmcA_reserve_lba = 0;
    }
#ifdef SDMMCB_EN
    if ( !( device_online & BIT(DEVICE_SDMMCB) ))
    {
        sdmmcB_reserve_lba = 0;
    }
#endif
    if( !( device_online & BIT(DEVICE_UDISK) ))
    {
        udisk_reserve_lba = 0;
    }
}
/*----------------------------------------------------------------------------*/
/**@brief   ������SD���л�ȡ�豸�м������Ϣ
   @param   mem ������buf    card_id�� U��Ϊ0��A��Ϊ1��B��Ϊ2
   @return  0 :��ȡ��Ϣ����  2����ȡA����Ϣ�ɹ�  4����ȡB����Ϣ�ɹ�
   @note    u8 get_info_form_sdmmc(u8 _xdata * mem,u8 card_id)
*/
/*----------------------------------------------------------------------------*/
u8 get_info_form_device(u8 _xdata * mem,u8 dev)  AT(COMMON_CODE)
{
    u8 _xdata *p;
    u8 pkt_size;
    device_check();
    if (dev == DEVICE_UDISK)
    {
        if(! (device_online & BIT(DEVICE_UDISK) ) )///<UDISK offline
        {
            return false;
        }
        if (usb_host_mount_app(1, 255, 4, 16))     ///<USB MASS STORAGE ö��
        {
            return false;            ///<ö��ʧ��
        }
        pkt_size = get_usb_pkt_size();
        if(1 != pkt_size)
        {
            return false;
        }
        f_init(usb_host_read, pkt_size);
    }
    else
    {
       if (dev == DEVICE_SDMMCA)
        {
            if(! (device_online & BIT(DEVICE_SDMMCA) ) )///<sdmmc offline
            {
                return false;
            }
            if(identif_sdmmc(DEVICE_SDMMCA))///<ident sdmmc fail
            {
                return false;
            }
            f_init(sdmmcA_read, 1);
        }
    #ifdef SDMMCB_EN
        else if (dev == DEVICE_SDMMCB)
        {
            if(! (device_online & BIT(DEVICE_SDMMCB) ) )///<sdmmc offline
            {
                return false;
            }
            if(identif_sdmmc(DEVICE_SDMMCB))///<ident sdmmc fail
            {
                return false;
            }
            f_init(sdmmcB_read, 1);
        }
    #endif
    }

    if(f_mount(0))///<fat init fail
    {
        return false;
    }
    p = (u8 _xdata *)get_win_buffer_address();

    if (dev == DEVICE_UDISK)
    {
        udisk_reserve_lba = (fat_fs.fatbase - 1) << fat_fs.secotr_512size;
        if(usb_host_read( p , udisk_reserve_lba ))///<sdmmc read fail
        {
            return false;
        }
    }
    else
    {
        if (dev == DEVICE_SDMMCA)
        {
            sdmmcA_reserve_lba = (fat_fs.fatbase - 1) << fat_fs.secotr_512size;
            if(sdmmcA_read(p , sdmmcA_reserve_lba))///<sdmmc read fail
            {
                return false;
            }
        }
#ifdef SDMMCB_EN
        if (dev == DEVICE_SDMMCB)
        {
            sdmmcB_reserve_lba = (fat_fs.fatbase - 1) << fat_fs.secotr_512size;
            if(sdmmcB_read(p , sdmmcB_reserve_lba))///<sdmmc read fail
            {
                return false;
            }
        }
#endif
    }

    if( (p[0] != 0x55 )
       || (p[1] != 0xaa) )///<info err
    {
        return false;
    }
    my_memcpy(mem,p,130);

    if (dev == DEVICE_UDISK)
    {
        return 1;
    }
    else
    {
        if (dev == DEVICE_SDMMCA)
        {
            return 2;
        }
#ifdef SDMMCB_EN
        else if (dev == DEVICE_SDMMCB)
        {
            return 4;
        }
#endif
    }

    return false;
}


/*----------------------------------------------------------------------------*/
/**@brief   �������豸�л�ȡ�豸�м������Ϣ
   @param   ��
   @return  ��
   @note    void power_up_device_info(void))
*/
/*----------------------------------------------------------------------------*/
void power_up_device_info(void) AT(COMMON_CODE)
{
    u8 sd_udisk_flag =0;
    sd_udisk_flag |= get_info_form_device(mem_buf,DEVICE_SDMMCA);
#ifdef SDMMCB_EN
    sd_udisk_flag |= get_info_form_device(mem_buf1,DEVICE_SDMMCB);
#endif
    sd_udisk_flag |= get_info_form_device(mem_buf0,DEVICE_UDISK);

    // my_printf("%04u\n",sd_udisk_flag);
    switch (sd_udisk_flag)
    {
        case 7:
             if(mem_buf1[DEVICE_MEM] > mem_buf0[DEVICE_MEM])
             {
                if(mem_buf1[DEVICE_MEM] > mem_buf[DEVICE_MEM])
                {
                    my_memcpy(mem_buf,mem_buf1,130);
                }
                else
                {

                }
             }
             else
             {
                if(mem_buf0[DEVICE_MEM] > mem_buf[DEVICE_MEM])
                {
                    my_memcpy(mem_buf,mem_buf0,130);
                }
                else
                {

                }
             }
             break;
        case 6:
            if(mem_buf1[DEVICE_MEM] > mem_buf[DEVICE_MEM])
            {
                my_memcpy(mem_buf,mem_buf1,130);
            }
            break;
        case 5:
            if(mem_buf0[DEVICE_MEM] > mem_buf1[DEVICE_MEM])
            {
                my_memcpy(mem_buf,mem_buf0,130);
            }
            else
            {
                my_memcpy(mem_buf,mem_buf1,130);
            }
            break;
        case 4:
            my_memcpy(mem_buf,mem_buf1,130);
            break;
        case 3:
            if(mem_buf0[DEVICE_MEM] > mem_buf[DEVICE_MEM])
            {
                my_memcpy(mem_buf,mem_buf0,130);
            }
            break;

        case 2:
            break;
        case 1:
            my_memcpy(mem_buf,mem_buf0,130);
            break;
        case 0:
            my_memset(mem_buf,0xff,130);
            break;

        default: break;
    }

}

/*----------------------------------------------------------------------------*/
/** @brief:
    @param: dev:�����豸disable_decode:�Ƿ�Ҫ��ʱ�رս��룬�ڽ�������е���ʱ���贫1
    @return:
    @author:Juntham
    @note: �뾡����Ҫ�ڽ��������ʹ�á�
*/
/*----------------------------------------------------------------------------*/

bool write_device(u8 dev, bool disable_decode) AT(GET_DEVICE)
{
    bool res;
    //u8 tmp;
    u8 p_status;

    u32 lba ;//= (fat_fs.fatbase - 1) << fat_fs.secotr_512size;    //������

    //my_printf(":%08lx\n", lba);

    if(disable_decode)
        p_status = pause_decode(1);

    if (dev == DEVICE_UDISK)
    {
        lba = udisk_reserve_lba;
        res = !usb_host_write(mem_buf, lba);
    }
    else
    {

        if (dev != check_sd_controller())             //�������ȣ��Խ���Ӱ���С������ʱ�������ڰ���������
        {
            //tmp = system_clk(48/48);
            if(dev == DEVICE_SDMMCA)
            {
                lba = sdmmcA_reserve_lba;
            }
#ifdef SDMMCB_EN
            else if(dev == DEVICE_SDMMCB)
            {
                lba = sdmmcB_reserve_lba;
            }
#endif
            res = !sdmmc_write(mem_buf, lba, dev);
            unlock_cmd_chk();
            //system_clk(tmp);
        }
        else                            //�˴�дʧ��
            res = false;
    }

    if(disable_decode)
    {
        if (p_status == MAD_PLAY)
            start_decode();
    }

    return res;
}



void updata_fat_memory (void)
{
    ///static u8 device_flag;

    if(1 == info_change)///<��Ϣ�иı�
    {
        device_check();
        if ( !( device_online & BIT(DEVICE_SDMMCA) ))
        {
            sdmmcA_reserve_lba = 0;
            device_flag &= ~BIT(DEVICE_SDMMCA);
        }
#ifdef SDMMCB_EN
        if( !( device_online & BIT(DEVICE_SDMMCB) ))
        {
            sdmmcB_reserve_lba = 0;
            device_flag &= ~BIT(DEVICE_SDMMCB);
        }
#endif
        if( !( device_online & BIT(DEVICE_UDISK) ))
        {
            udisk_reserve_lba = 0;
            device_flag &= ~BIT(DEVICE_UDISK);
        }
        mem_buf[0] = 0x55;
        mem_buf[1] = 0xaa;
        if(device_flag & 0x80)
        {
            mem_buf[DEVICE_MEM]++;
            device_flag &= ~0x80;
        }
        if ( ( device_flag & BIT(DEVICE_SDMMCA) ) && sdmmcA_reserve_lba )
        {
            if(write_device(DEVICE_SDMMCA,1))
            {
                device_flag &= ~BIT(DEVICE_SDMMCA);
            }
        }
#ifdef SDMMCB_EN
        if ( ( device_flag & BIT(DEVICE_SDMMCB) ) && sdmmcB_reserve_lba )
        {
            if(write_device(DEVICE_SDMMCB,1))
            {
                device_flag &= ~BIT(DEVICE_SDMMCB);
            }
        }
#endif
        if  ( ( device_flag & BIT(DEVICE_UDISK) ) && udisk_reserve_lba)
        {
            if( write_device(DEVICE_UDISK,1))
            {
                device_flag &= ~BIT(DEVICE_UDISK);
            }
        }
        if(0 == device_flag)
        {
            info_change = 0;
        }
    }
    else
    {
        if(info_change)
        {
            info_change--;
        }
#ifdef SDMMCB_EN
        device_flag = 0x80 | BIT(DEVICE_SDMMCA) | BIT(DEVICE_SDMMCB)| BIT(DEVICE_UDISK) ;
#else
        device_flag = 0x80 | BIT(DEVICE_SDMMCA) | BIT(DEVICE_UDISK) ;
#endif
    }
}

///#endif

