#ifndef	_IRTC_H_
#define _IRTC_H_

#include "config.h"

#ifdef __IAR_SYSTEMS_ICC__

typedef struct _RTC_TIME
{
    u16 dYear;		///<���
    u8 	bMonth;		///<�·�
    u8 	bDay;		///<����
    u8 	bHour;		///<ʱ
    u8 	bMin;		///<��
    u8 	bSec;		///<��
    u8 	bWeekday;	///<���ڼ�
}RTC_TIME;

typedef struct _ALM_TIME
{
    u8 	bHour;		///<ʱ
    u8 	bMin;		///<��
    u8 	bSw;		///<���ӿ���
    u8  bmWeekdays; ///<��������
}ALM_TIME;

/********************************************/
/*
            Bit Map
    7   |   6   |   5   |   4   |   3   |   2   |   1   |   0
    Sun     Sat     Fri     Thu     Wed     Tue     Mon     Null
*/
/********************************************/
#define SUNDAY      BIT(7)
#define SATURDAY    BIT(6)
#define FRIDAY      BIT(5)
#define THURSDAY    BIT(4)
#define WEDNESDAY   BIT(3)
#define TUESDAY     BIT(2)
#define MONDAY      BIT(1)

#define ALM_WEEKDAYS    (MONDAY|SUNDAY)

#define TRUE 		1
#define FALSE 		0

#define	ONEDAY 		(24*60*60LU)	//86400
#define ONEHOUR 	(60*60)		//3600
#define ONEMIN		60

#define YEAR 		2000U
#define MONTH 		1
#define DAY 		1
#define HOUR 		0
#define MINUTES 	0
#define SECOND 		0

#define DATE 		6

extern RTC_TIME __idata curr_time;
extern ALM_TIME __idata curr_alarm;

/*******************************************/
/*
            Maskrom API
                --IRTC Part
*/
/*******************************************/
/*----------------------------------------------------------------------------*/
/**@brief 	дRTC
   @param 	void
   @return  void
   @note  	void write_RTC(RTC_TIME *curr_time)
*/
/*----------------------------------------------------------------------------*/
_near_func void write_RTC(RTC_TIME _xdata *curr_time);
/*----------------------------------------------------------------------------*/
/**@brief 	��RTC
   @param 	void
   @return  void
   @note  	void read_RTC(RTC_TIME *curr_time)
*/
/*----------------------------------------------------------------------------*/
_near_func void read_RTC(RTC_TIME _xdata *curr_time);
/*----------------------------------------------------------------------------*/
/**@brief 	дRTC ALM
   @param 	void
   @return  void
   @note  	void write_ALM(RTC_TIME *curr_time_alm)
*/
/*----------------------------------------------------------------------------*/
_near_func void write_ALM(RTC_TIME _xdata *curr_time_alm);
/*----------------------------------------------------------------------------*/
/**@brief 	��RTC ALM
   @param 	void
   @return  void
   @note  	void read_ALM(RTC_TIME *curr_time_alm)
*/
/*----------------------------------------------------------------------------*/
_near_func void read_ALM(RTC_TIME _xdata *curr_time_alm);
/*----------------------------------------------------------------------------*/
/**@brief 	д IRTC RAM
   @param 	addr����ַ dat������
   @return  void
   @note  	void write_IRTC_RAM(u8 addr, u8 dat)
*/
/*----------------------------------------------------------------------------*/
_near_func void write_IRTC_RAM(u8 addr, u8 dat);
/*----------------------------------------------------------------------------*/
/**@brief 	�� IRTC RAM
   @param 	addr����ַ
   @return  ����
   @note  	u8 read_IRTC_RAM(u8 addr)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 read_IRTC_RAM(u8 addr);
/*----------------------------------------------------------------------------*/
/**@brief 	дIRTC
   @param 	cmd��дָ�� w_time:д������
   @return  void
   @note  	void write_IRTC(u8 cmd, RTC_TIME *w_time)
*/
/*----------------------------------------------------------------------------*/
_near_func void write_IRTC(u8 cmd, RTC_TIME _xdata *w_time);
/*----------------------------------------------------------------------------*/
/**@brief 	��IRTC
   @param 	cmd����ָ�� r_time������������
   @return  void
   @note  	void read_IRTC(u8 cmd, RTC_TIME *r_time)
*/
/*----------------------------------------------------------------------------*/
_near_func void read_IRTC(u8 cmd, RTC_TIME _xdata *r_time);
/*----------------------------------------------------------------------------*/
/**@brief 	дRTC�Ĵ���
   @param 	cmd���Ĵ���ֵ
   @return  void
   @note  	void write_RTC_reg(u8 cmd, u8 reg)
*/
/*----------------------------------------------------------------------------*/
_near_func void write_RTC_reg(u8 cmd, u8 reg);
/*----------------------------------------------------------------------------*/
/**@brief 	��RTC�Ĵ���
   @param 	void
   @return  void
   @note  	u8 read_RTC_reg(u8 cmd)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 read_RTC_reg(u8 cmd);

/*----------------------------------------------------------------------------*/
/**@brief	�ж�����
   @param 	year:���
   @return  ���
   @note	bool leapyear(u16 year)
*/
/*----------------------------------------------------------------------------*/
_near_func bool leapyear(u16 year);
/*----------------------------------------------------------------------------*/
/**@brief	����������Ϊ���ڵ�����
   @param 	day��������
   @return  ���ڵ�����
   @note	u8 day_to_weekday(u16 day)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 day_to_weekday(u16 day);
/*----------------------------------------------------------------------------*/
/**@brief ���µ�����
   @param 	nmonth�������·ݣ�nyear���������
   @return  ��������
   @note u8 nowmonth(u8 nmonth,u16 nyear)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 nowmonth(u8 nmonth,u16 nyear);
/*----------------------------------------------------------------------------*/
/**@brief	�·ݻ���Ϊ����
   @param 	day��������
   @return  ���ڵ�����
   @note	u8 month_to_day(u8 month)
*/
/*----------------------------------------------------------------------------*/
_near_func u16 month_to_day(u16 year,u8 month);
/*----------------------------------------------------------------------------*/
/**@brief	����������Ϊ���/�·�/����
   @param 	day����������time:��ǰ����
   @return  ���ڵ�����
   @note	void day_to_ymd(u16 day,RTC_TIME *rtc_time)
*/
/*----------------------------------------------------------------------------*/
_near_func void day_to_ymd(u16 day,RTC_TIME *rtc_time);
/*----------------------------------------------------------------------------*/
/**@brief	��ǰ���/�·�/���ڻ����������
   @param 	time:��ǰ����
   @return  ���ڵ�����
   @note	u16 ymd_to_day(RTC_TIME *time,u16 day)
*/
/*----------------------------------------------------------------------------*/
_near_func u16 ymd_to_day(RTC_TIME *time);
#endif /*	__IAR_SYSTEMS_ICC__	*/


#endif /* _IRTC_H_ */
