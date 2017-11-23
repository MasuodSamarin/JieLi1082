#ifndef _FF_API
#define _FF_API

#include "tff.h"

#ifdef __SMART_CPU__
enum
{
    SEARCH_FILE_BY_NUMBER,  //���ļ���������ļ�
    SEARCH_FILE_BY_PATH,    //���ļ�·��ȫ�豸�����ļ������ҳ��ļ����
    SEARCH_SPEC_FILE,       //����ָ�����ļ�
    SEARCH_CUR_DIR_BY_PATH, //�ڵ�ǰĿ¼�£����ļ�·��������һ���ļ���ƥ����ļ������ҳ��ļ����
    SEARCH_DISK,            //��������Ч�ļ���
    SEARCH_FOLDER           //������ǰĿ¼���µ���Ч�ļ�����
};

/* function list */
bool fs_scan_disk(u32 sclust, u32 fsize);
u16 fs_getfile_totalindir(DIR _xdata * dj);
bool fs_getfile_bynumber(FIL *file_ptr, u16 fileNumber);
void fs_ext_setting(u8 const _code * str);
void fs_api_init(void);

#endif

#endif
