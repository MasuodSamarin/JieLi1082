/*--------------------------------------------------------------------------*/
/**@file    clock.c
   @brief   ʱ��ģ��ӿں���
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/

#include "clock.h"
#include "main.h"
#include "RTC_API.h"
#include "IRTC.h"
#include "iic.h"
#include "dac.h"

_no_init u16 _data pll_nr,pll_nf;
_no_init u8 _data system_clk;

/*----------------------------------------------------------------------------*/
/** @brief: P05 ������ƺ���
    @param: cfg���������ʱ��
    @return:void
    @author:Juntham
    @note:  void P05_config(u8 cfg)
*/
/*----------------------------------------------------------------------------*/
_near_func void P05_config(u8 cfg) AT(COMMON_CODE)
{
    u8 temp;

    if (cfg == P05_NORMAL_IO)
    {
        CLK_CON2 &= ~BIT(4);
    }
    else
    {
        temp = CLK_CON2 & 0xf3;
        CLK_CON2 = temp | cfg | BIT(4);
        P0HD |= BIT(5);
        P0DIR &= ~BIT(5);
    }
}
/*----------------------------------------------------------------------------*/
/** @brief: HTC ģ����ƺ���
    @param: on_off����/�ؿ���λ
    @return:void
    @author:Juntham
    @note:  void htc_control(bool on_off)
*/
/*----------------------------------------------------------------------------*/
_near_func static void htc_control(bool on_off) AT(COMMON_CODE)
{
    if (on_off)
    {
        HTC_CON |=  BIT(6)|BIT(5);
        HTC_CON &=  ~BIT(7);
        delay8(100);
        HTC_CON |=  BIT(7);
    }
    else
    {
        HTC_CON &=  ~BIT(7);
        HTC_CON &=  ~BIT(6);
    }
}

/*----------------------------------------------------------------------------*/
/** @brief: PLL ϵ������
    @param: nr��PLL ����
    @param: nf��PLL ����
    @return:void
    @author:Juntham
    @note:  void pll_nrnf_cfg(u16 nr, u16 nf)
*/
/*----------------------------------------------------------------------------*/
_near_func void pll_nrnf_cfg(u16 nr, u16 nf) AT(COMMON_CODE)
{
    pll_nr = nr;        //14bit��Ч
    pll_nf = nf;        //10bit��Ч

    PLL_CON2 = pll_nf >> 2;
    PLL_CON1 = ((pll_nf & 0x03) << 6) | (pll_nr >> 8);
    PLL_CON0 = pll_nr & 0xff;
    delay8(200);
}

/*----------------------------------------------------------------------------*/
/** @brief: PLL����ʱ��ѡ��
    @param: 0:32768(RTC), 1:HTC, 2:1M~24M(RTC),3:1M~24M(P00P01)
    @return:void
    @author:Juntham
    @note:  void pll_in_sel(u8 sel)
*/
/*----------------------------------------------------------------------------*/
_near_func static void pll_in_sel(u8 sel) AT(COMMON_CODE)
{
    u8 tmp = CLK_CON0;

    tmp &= ~(BIT(4) | BIT(5));
    tmp |= sel;
    CLK_CON0 = tmp;        //config PLL, enable PLL
}

/*----------------------------------------------------------------------------*/
/** @brief: PLL����
    @param: 0:�ر�PLL��1����PLL
    @return:
    @author:Juntham
    @note:  void pll_control(bool on_off)
*/
/*----------------------------------------------------------------------------*/
_near_func static void pll_control(bool on_off) AT(COMMON_CODE)
{
    if (on_off)
    {
        CLK_CON0 |= BIT(2);
        delay8(100);
    }
    else
        CLK_CON0 &= ~BIT(2);

}

/*----------------------------------------------------------------------------*/
/** @brief: ����ʱ�����OSC(�ṩ��system_clkin()�Ĳ���0)ѡ��,��ѡ��P00P01(������ӵ���,1M~24M)��RTC OSC(32768��1M~24M)
    @param: 0��ʹ��RTCʱ�ӣ�1��ʹ��P00P01ʱ��
    @return:void
    @author:Juntham
    @note:  void osc_out_sel(bool sel)
*/
/*----------------------------------------------------------------------------*/
_near_func void osc_out_sel(bool sel) AT(COMMON_CODE)
{
    if (sel)
        CLK_CON0 |= BIT(3);
    else
        CLK_CON0 &= ~BIT(3);
}

/*----------------------------------------------------------------------------*/
/** @brief: ϵͳʱ��ǰ��ѡ��������
    @param: 0:OSC(osc_out_sel()����)��1��RC(~256K)��2��HTC��3��PLL
    @return:void
    @author:Juntham
    @note:  void system_clk_prein(u8 sel)
*/
/*----------------------------------------------------------------------------*/
_near_func static void system_clk_prein(u8 sel) AT(COMMON_CODE)
{
    u8 tmp = CLK_CON1;

    tmp &= ~(BIT(0) | BIT(1));

    CLK_CON1 = tmp | sel;
}

/*----------------------------------------------------------------------------*/
/** @brief: ϵͳʱ��ǰ��ѡ�������ú��ٱ�Ƶ
    @param: en��ʱ�ӷ�Ƶ����λ
    @return:void
    @author:Juntham
    @note:  void system_clk_preinx2(bool en)
*/
/*----------------------------------------------------------------------------*/
_near_func void system_clk_preinx2(bool en) AT(COMMON_CODE)
{
    if (en)
        CLK_CON1 |= BIT(2);
    else
        CLK_CON1 &= ~BIT(2);
}

/*----------------------------------------------------------------------------*/
/** @brief: ϵͳʱ��ѡ��ΪRC(~256K)����ʱ��(system_clk_prein()����)���޸�system_clkin��system_clk_preinx2ʱ���������ô˺�����ϵͳʱ��ѡ��ΪRC
    @param: 0��ѡ��RC(~256K),1��ѡ������ʱ��
    @return:void
    @author:Juntham
    @note:  void system_clk_sel(bool sel)
*/
/*----------------------------------------------------------------------------*/
_near_func static void system_clk_sel(bool sel) AT(COMMON_CODE)
{
    if(sel)
        CLK_CON1 |= BIT(3);
    else
        CLK_CON1 &= ~BIT(3);
}

/*----------------------------------------------------------------------------*/
/**@brief 	Timer 0 ��ʼ������,���ڰ������Ĳ���, 8K������
   @param 	sys_clk: ϵͳʱ��
   @return  void
   @author: Juntham
   @note  	void Timer0_init(u8 sys_clk)
*/
/*----------------------------------------------------------------------------*/
const u8 timer0_table[][3] AT(TABLE_CODE) =
{
    0x21, 0, 3,
    0x21, 0, 7,
    0x21, 0, 15,
    0x1, 0x40, 5,
    0x1, 0x40, 11,
    0x11, 0x40, 5,
};


_near_func void Timer0_init(u8 div) AT(COMMON_CODE)
{
    TMR0_CON0 = timer0_table[div][0];
    TMR0_CON1 = timer0_table[div][1];
    TMR0_PRD =  timer0_table[div][2];
}

/*----------------------------------------------------------------------------*/
/**@brief 	Timer 1 ��ʼ������
   @param 	void
   @return  void
   @author  Change.tsai
   @note  	void Timer1_init(void)
*/
/*----------------------------------------------------------------------------*/
const u8 timer1_table[][3] AT(TABLE_CODE)=
{
    3,  0x40, 0x41,
    7,  0x40, 0x41,
    15, 0x40, 0x41,
    24, 0x40, 0x51,
    47, 0x40, 0x51,
    95, 0x40, 0x51,
};

_near_func void Timer1_init(u8 div) AT(COMMON_CODE)
{
    TMR1_PRD = timer1_table[div][0];
    TMR1_CON1 = timer1_table[div][1];
    TMR1_CON0 = timer1_table[div][2];

    Timer1_IP(1);
    Timer1_IE(1);
}

/*----------------------------------------------------------------------------*/
/**@brief 	Timer 2 ��ʼ������
   @param 	void
   @return  void
   @author  Change.tsai
   @note  	void Timer2_init(void)
*/
/*----------------------------------------------------------------------------*/

const u8 timer2_table[][2] AT(TABLE_CODE)=
{
    0x41, 0x23,
    0x41, 0x23,
    0x41, 0x23,
    0x81, 0x23,
    0x91, 0x33,
    0xa1, 0x33,
};

_near_func void Timer2_init(u8 div) AT(COMMON_CODE)
{
    IRFLT_CON = timer2_table[div][0];
    TMR2_CON = timer2_table[div][1];

	P4DIR |= BIT(6);
    IO_MC1 |= 0x0B;
    Timer2_IP(2);
    Timer2_IE(1);
}

/*----------------------------------------------------------------------------*/
/** @brief: ϵͳʱ�Ӻ��Ƶ,system_clock /= (CLK_CON3 + 1)
    @param: div����Ƶϵ��
    @return:void
    @author:Juntham
    @note:  void system_clk_div(u8 div)
*/
/*----------------------------------------------------------------------------*/
u8 const sys_clk_table[] AT(TABLE_CODE)=
{
    95, 47, 23, 3, 1, 0
};

_near_func void system_clk_div(u8 div) AT(COMMON_CODE)
{
    asm("setb c");
    asm("jbc 0xA8.7, $+4");
    asm("clr c");
    asm("push PSW");

    system_clk = div;
    CLK_CON3 = sys_clk_table[div];
    ADC_CON0 &= ~(BIT(0) | BIT(1) | BIT(2));

    switch(div)
    {
    case CLK_512K:
        //my_puts("CLK_512K\n");
        otp_clk_div2(0);
        get_iic_busy_status(0);
        //adc setting
        ADC_CON0 |= BIT(2);
        break;

    case CLK_1M:
        //my_puts("CLK_1M\n");
        otp_clk_div2(0);
        get_iic_busy_status(0);
        ADC_CON0 |= BIT(2);
        break;

    case CLK_2M:
        //my_puts("CLK_2M\n");
        otp_clk_div2(0);
        get_iic_busy_status(0);
        ADC_CON0 |= BIT(2);
        break;

    case CLK_12M:
        //my_puts("CLK_12M\n");
        //UART_BAUD = (12000000/(8 * 115200)) - 1;
        otp_clk_div2(0);
        get_iic_busy_status(5);
        break;

    case CLK_24M:
        //my_puts("CLK_24M\n");
        //UART_BAUD = (24000000/(8 * 115200)) - 1;
        otp_clk_div2(0);
        get_iic_busy_status(10);
        ADC_CON0 |= BIT(1);
        break;

    case CLK_48M:
        //my_puts("CLK_48M\n");
        //UART_BAUD = (48000000/(8 * 115200)) - 1;
        otp_clk_div2(1);
        get_iic_busy_status(15);
        ADC_CON0 |= BIT(0) | BIT(1);
        break;
    }

#if defined KEY_VOICE_EN || defined RTC_ALARM_EN
    Timer0_init(div);
#endif
    //timer1 setting
    Timer1_init(div);

#ifdef IR_REMOTE_EN
    //timer2 setting
    Timer2_init(div);
#endif

    asm("pop PSW");
    asm("mov 0xA8.7, c");
}

/*----------------------------------------------------------------------------*/
/** @brief: OTPʱ�ӷ�Ƶ
    @param: 1:��2, 0:��1
    @return:void
    @author:Juntham
    @note:  void otp_clk_div2(bool en)
*/
/*----------------------------------------------------------------------------*/
_near_func void otp_clk_div2(bool en) AT(COMMON_CODE)
{
    if (en)
        CLK_CON1 |= BIT(6);
    else
        CLK_CON1 &= ~BIT(6);
}

/*----------------------------------------------------------------------------*/
/** @brief: ʱ�ӳ�ʼ������
    @param: void
    @return:void
    @author:Juntham
    @note:  void clock_power_on(void)
*/
/*----------------------------------------------------------------------------*/
void clock_power_on(void) AT(CSTART)      //ϵͳ�ϵ��������~24M
{
#if defined (CLK_USE_12M_WITH_HTC) || defined (CLK_USE_12M_NO_HTC)
    write_RTC_reg(WRITE_SR1,0x3);       //��12M����
#endif

#if defined (CLK_USE_32K_WITH_HTC) || defined (CLK_USE_32K_NO_HTC)
#ifdef SHARE_RTC_OSC_TO_FM
    write_RTC_reg(WRITE_SR1,0x5);
#else
    write_RTC_reg(WRITE_SR1,0x1);
#endif
#endif

    htc_control(1);
    pll_in_sel(PLLIN_HTC);

#ifdef CLK_USE_HTC
    check_htc_otp();
#else
    pll_nrnf_cfg(1151,23);
#endif

    pll_control(1);
    system_clk_prein(PRE_SYSCLK_PLL_CLK);
    system_clk_div(CLK_24M);
    system_clk_sel(SYSCLK_MAIN_CLK);
}

/*----------------------------------------------------------------------------*/
/** @brief: PLL ģ���ʼ������
    @param: void
    @return:void
    @author:Juntham
    @note:  void pll_init(void)
*/
/*----------------------------------------------------------------------------*/
_monitor void pll_init(void) AT(CSTART)
{
#ifdef CLK_USE_32K_WITH_HTC
    check_htc_32k();
    system_clk_sel(SYSCLK_MAIN_CLK);
    system_clk_div(SYSTEM_CLK);
#endif

#ifdef CLK_USE_32K_NO_HTC
    system_clk_sel(SYSCLK_RC256K);
    pll_in_sel(PLLIN_32K);
    pll_nrnf_cfg(0x392,0);
    system_clk_sel(SYSCLK_MAIN_CLK);
    system_clk_div(SYSTEM_CLK);
#endif

#ifdef CLK_USE_12M_WITH_HTC
    check_htc_12M();
    system_clk_sel(SYSCLK_MAIN_CLK);
    system_clk_div(SYSTEM_CLK);
#endif

#ifdef CLK_USE_12M_NO_HTC
    system_clk_sel(SYSCLK_RC256K);
    pll_in_sel(PLLIN_RTC_12M);
    pll_nrnf_cfg(1120,55);
    system_clk_sel(SYSCLK_MAIN_CLK);
    system_clk_div(SYSTEM_CLK);
#endif
}
