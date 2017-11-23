/*! \page11 LCD ���ָ��
 *
 * \section intro_sec_lcd LCD ����
 * - CD002 LCDģ�����������Ҫ���������LCD��Ļ����������6COM & 16SEG����Ļ��ģ��ʹ��IRTC 1KHz��ģ�����ʹ��RTC����ʱ��32KHz���ڲ�RC(Լ250KHz/8)��Ϊģ��ʱ��
 * \section lcd1 LCD �Ĵ��� �б�
 *   \image html lcd.bmp
 * \section lcd2 LCD �Ĵ�����
 * - LCD_CON0��\n
 *   Bit0: ʹ�����ģ��\n
 *   Bit1: COM0, SEG0���һ��1Hz���źţ�����Ϊ"����"��\n
 *   Bit3~2��ƫѹѡ��\n
 *    00��ģ��ģ�鹤����ֹ\n	
 *    01:  1/2 bias\n
 *    10:  1/3 bias \n
 *    11:  1/4 bias\n
 *   Bit6~Bit4��VLCD����\n
 *    000��2.6V\n
 *    001��2.7V\n
 *    ......  \n
 *    110��3.2V\n
 *    111��3.3V\n
 *   Bit7��֡Ƶ�ʿ���\n
 *    0��FLCD = 32KHz/128\n
 *    1��FLCD = 32KHz/64\n
 *   FLCDΪģ��״̬�л�ʱ��Ƶ��

 * - LCD_CON1��\n
 *   Bit3~0��������ģʽ��ǿ���ռ��Cycle������32KHzʱ�ӣ�\n
 *   Bit5~4�����ģʽ����\n
 *    00��һֱ�������ģʽ\n
 *    01��һֱ��ǿ���ģʽ\n
 *    10��������ģʽA\n
 *    11��������ģʽB\n
 *   Bit7~6��ѡ��COM����Ŀ(Duty)\n
 *    00��3COM\n
 *    01��4COM\n
 *    10��5COM\n
 *    11��6COM\n
 *    1/Duty = 1/(COMCNT + 3)\n
 *   (ע��������ģʽA��״̬�л�ʱ��ʼתǿ����������CHGDUTY+1��32KHzʱ�Ӻ���ǿ����\n
 *   ������ģʽB��״̬�л�ǰ������ڣ�32KHzʱ�ӣ���ʼתǿ����������CHGDUTY+1.5��32KHzʱ�Ӻ���ǿ����)

 * - LCD_CON2��\n
 *   Bit4��ѡ��LCD��ʱ�ӣ�0��IRTC����ʱ����ΪLCDģ�鹤��ʱ�� ��1: RCʱ����ΪLCDģ�鹤��ʱ��

 * - ʹ��˵����\n
 *   1.����ѡ��LCDģ�鹤��ʱ�ӣ����ϵͳ��32K������ѡ32KHz����ʱ�ӣ�����ѡ�ڲ�RCʱ�ӡ�\n
 *   2.����趨LCD��ѹ��VLCDS����ƫ�ã�BIAS�������ģʽ��CHGMOD��CHGDUTY����\n
 *   3.�ٴ�ѡ��COM��SEG��λ�ã�����ѡ����Ҫ4��COM��ѡ��COM0(P30), COM1(P31), COM2(P32), COM3(P33), Ȼ��ѡ��SEG8~SEG15(P1)�����4COMX8SEG����ô������ѡ�����£�\n
 *     COMCNT =  01;	//ѡ��COM  \n
 *     SEGEN1 = 0xff;	//ѡ��SEG   \n
 *   4.Ȼ���LCDģ��\n
 *     LCDCCON0 |= 0x01;	     //��LCD \n
 *   5.��д����; ����6��COM��ÿ��SEG��Ҫ16bit����д���ݷֱ���\n
 *     SEG0:{P1DIE, P0DIE}\n
 *     SEG1:{P1HD, P0HD}\n
 *     SEG2:{P1PD, P0PD}\n
 *     SEG3:{P1PU, P0PU} \n
 *     SEG4:{P1, P0}\n
 *     SEG5:{P1DIR, P0DIR}\n

 */
