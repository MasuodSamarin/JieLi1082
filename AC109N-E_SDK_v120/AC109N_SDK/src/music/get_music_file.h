/*--------------------------------------------------------------------------*/
/**@file   get_music_file.h
   @brief  ��ȡ�ļ�ͷ�ļ�
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef  _GET_MUSIC_FILE_
#define  _GET_MUSIC_FILE_


#include "config.h"
#include "device.h"
#include "tff.h"

#ifdef __SMART_CPU__

typedef enum							//�����ļ��ķ�ʽ����
{
    PLAY_NEXT_FILE = 0,
    PLAY_AUTO_NEXT,
    PLAY_FIRST_FILE,  		    //�ӵ�һ���ļ�����
    PLAY_BREAK_POINT,           //�Ӽ����ļ���λ�ÿ�ʼ����
    PLAY_LAST_FILE,				//�����һ���ļ�����
    PLAY_PREV_FILE,
    PLAY_SPEC_FILE,             //IR ����ָ���ļ�
}ENUM_FILE_SELECT_MODE;

typedef enum
{
    REPEAT_ALL = 0,

#ifdef FOLDER_PLAY_EN
    REPEAT_FOLDER,
#endif

    REPEAT_ONE,

#ifdef RANDOM_PLAY_EN
    REPEAT_RANDOM,
#endif

    MAX_PLAY_MODE,
}ENUM_PLAY_MODE;


enum
{
    GET_FILE_OK = 0,			        //�ҵ��ļ����
    GET_DEVICE_END,						//�Ѿ����ŵ��豸����
    GET_DEVICE_HEAD,					//�Ѿ����ŵ��豸��ͷ
    //GET_SPEC_FILE_ERR
};

typedef struct _SELECT_PLAY_FILE
{
    ENUM_PLAY_MODE play_mode;
    ENUM_FILE_SELECT_MODE given_file_method;
    ENUM_DEVICE_SELECT_MODE given_device;
    u16 given_file_number;
    u16 break_point_filenum;
}SELECT_PLAY_FILE;

u8 fs_get_filenum(ENUM_PLAY_MODE playmode, ENUM_FILE_SELECT_MODE searchMode);
void get_dir_file_total(void);
u16 file_search(u16 fileNumber);
bool get_file_search_effectDir(void);

extern _no_init bool _bit play_break_point;
extern _no_init FF_APIS _xdata ff_api;
extern SELECT_PLAY_FILE _data playfile;
extern _no_init bool _bit find_break_point_dir_flag;
#endif


#endif
