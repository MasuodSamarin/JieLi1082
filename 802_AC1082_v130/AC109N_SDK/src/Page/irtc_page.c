/*! \page9 IRTCָ��
 *
 * \section intro_sec_irtc IRTC �������
 *
 * - CD002 ֧��Ƭ��IRTC��������Ϊ��ͨʱ��ʹ���⣬�������������Ѻ�Capture �����¼�ʹ��
 *
 * \subsection itrc1 IRTC �Ĵ�������
 * - RTC_CON0��\n
 *   Bit7: Read Only��IRTC WKUP��־λ����RTC��ʱ��������Ĵ������ʱ��1\n
 *   Bit6: WKUP�ж���������Ч\n
 *   Bit5: 512Hzʱ����־�����Ը�CPU����Լ2ms�ж�\n
 *   Bit4: 512Hzʱ���ж�����\n
 *   Bit3: 2Hzʱ����־�����Ը�CPU����500ms�ж�\n
 *   Bit2: 2Hzʱ���ж�����\n
 *   Bit1: Read Only����λ�Ĵ���������ɱ�־������Ч\n
 *   Bit0: ��λ�Ĵ���Ƭѡ�źţ�����Ч

 * - RTC_CON1��\n
 *   Bit7: д"1"���WKUPPending����һֱΪ0\n
 *   Bit5: д"1"���512Hzʱ��Pending����һֱΪ0\n
 *   Bit3: д"1"���2Hzʱ��Pending����һֱΪ0

 * - RTC_BUF��\n
 *   д����Ĵ���������һ�η����ݣ�һ���ֽڣ���ͨ����ɺ���Զ�����Ĵ����õ����յ����ݡ�\n

 * - �������շ���������̡�\n
 *   #define IRTC_CSEN    IRTCON |= BIT(0)\n
 *   #define IRTC_CSDIS   IRTCON &= ~BIT(0)\n
 *   unsigned char irtc_sr_byte(unsigned char x)\n
 *   {\n
 *      IRTBUF = x;\n
 *   	while(!(IRTCON & BIT(1)));\n
 *      return IRTBUF;\n
 *   }\n
 *
 * \subsection itrc2 IRTC֧�ֵ����
 *   \image html rtc1.bmp
 *   \image html rtc2.bmp
 * - ����д������ʱ����ַ���Զ���1������ַ������255�󣬿ɻ�����0����д��������
 * - ע��оƬ�ڲ�����256Byte SRAM
 *
 * - IRTC �ڲ����ƼĴ���0��\n
 *   Bit7: PDFLAG����RTCVDD power upʱд1��������ǵ�һ���ϵ磬�������д0 indicate\n
 *   Bit6: X1MOE��IRTC 512Hz���ȡ�� 1/60Hz���\n
 *   Bit5: Alarm enable\n
 *   Bit4: WKPD��WakeUp pin pulldown enable������Ч\n
 *   Bit3: WakeUp pin DIR��0Ϊ�����1Ϊ����\n
 *   Bit2: WakeUp pin IO SEL��0Ϊ WakeUp��1 Ϊ��ͨ IO\n
 *   Bit1: ����ͨIOʹ��ʱ��λΪWakeUp pin Output register\n
 *   Bit0: WakeUp pin Input��Read Only
 *
 * - IRTC �ڲ����ƼĴ���1��\n
 *   Bit3: Alarm output������Ч��Read Only\n
 *   Bit2: High current OSC enable������Ч\n
 *   Bit1: 12MSEL��1��12MHz OSC,0:32KHz����λֵΪ0\n
 *   Bit0: OSCEN��0��OSC Disable 1��OSC Enable����λֵΪ1
 */
