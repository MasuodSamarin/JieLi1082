/*! \page7 PORTָ��
 *
 * \section intro_sec_port PORT �������
 *
 * - CD002 ֧��7��I/O �жϺ� 1Hz��2Hz �� 1 Minuteʱ����ͬ������8��I/O�жϣ�ͬʱ����Ϊ�����ź�
 * \subsection port0 GPIO�ֲ�����
 *   \image html port.bmp
 * \subsection  �Ĵ�������
 * - IO_MC0��IO mapping���ƼĴ���0\n
 *   bit7~6: UARTģ��IO re-mapping���� \n
 *   00��TX:P06��RX:P07\n
 *   01��TX:P24��RX:P25\n
 *   10��TX:P32��RX:P33\n
 *   11��TX:P36��RX:P37\n
 *   \image html uart.bmp
 *   bit5~4: IICģ��IO re-mapping���� \n
 *   00��SCK:P00��SDL:P01\n
 *   01��SCK:P26��SDL:P27\n
 *   10��SCK:P32��SDL:P33\n
 *   11��SCK:P36��SDL:P37\n
 *   \image html iic.bmp
 *   bit3:	SDģ��ռ��IOʹ�ܣ�0��������SDģ��ռ��IO����ʹSDģ���Ѵ򿪣�1:����SDģ���ڴ�ʱռ����ӦIO\n
 *   bit2:	SDģ��IO re-mapping���ã�0��SDCMDΪP21��SDDATΪP22��1��SDCMDΪP00��SDDATΪP01\n
 *   \image html sd.bmp
 *   bit1~0: SDģ��CLK re-mapping����\n
 *   00��SDCLK�������\n
 *   01��ʹ��P20��ΪSDCLK\n
 *   10��ʹ��P30��ΪSDCLK\n
 *   11��ʹ��P35��ΪSDCLK\n
 *   \image html sd_clk.bmp
 *
 * - IO_MC1��IO mapping���ƼĴ���1\n
 *   bit7��PWM4������� 0�����PWM4,1�����RTC����ʱ�� \n
 *   bit6: isd 2wire ģ��IO re-mapping���� ��0��ISDCKΪP24��ISDDATΪP25,1��ISDCKΪP00��ISDDATΪP01\n
 *   \image html isd_2wire.bmp
 *   bit5: SPIģ��ռ��IOʹ�ܣ�0��������SPIģ��ռ��IO����ʹSPIģ���Ѵ򿪣�1:����SPIģ���ڴ�ʱռ����ӦIO\n
 *   bit4: SPIģ��IO re-mapping����\n
 *   0��\n
 *   2�ߣ�SPICKΪP16��SPIDOΪP17��SPIDIΪP17\n
 *   3�ߣ�SPICKΪP16��SPIDOΪP17��SPIDIΪP17\n
 *   1��\n
 *   2�ߣ�SPICKΪP00��SPIDOΪP01��SPIDIΪP01\n
 *   3�ߣ�SPICKΪP00��SPIDOΪP01��SPIDIΪP44\n
 *   \image html spi.bmp
 *   bit3~2: IRFLT���ѡ��������μ�IRFLT����\n
 *   00��IRFLT�������timer0�Ĳ����\n
 *   01��IRFLT�������timer1�Ĳ����\n
 *   10��IRFLT�������timer2�Ĳ����\n
 *   11��IRFLT�������timer3�Ĳ����\n
 *   bit1~0: IRFLT����ѡ��������μ�IRFLT����\n
 *   00��ʹ��CAP0��ΪIRFLT�������ź�\n
 *   01��ʹ��CAP1��ΪIRFLT�������ź�\n
 *   10��ʹ��CAP2��ΪIRFLT�������ź�\n
 *   11��ʹ��CAP3��ΪIRFLT�������ź�\n
 *
 * - WKUPPND��\n
 *   bit7:	ֻд��д��'1'���¼�3��0 \n
 *   bit6:	ֻд��д��'1'���¼�2��0 \n
 *   bit5:	ֻд��д��'1'���¼�1��0 \n
 *   bit4:	ֻд��д��'1'���¼�0��0 \n
 *   bit3:	ֻ�����¼�3����ʱ����λ����Ӳ����1��������wakeup�жϻ���ϵͳ���������0\n
 *   bit2:	ֻ�����¼�2����ʱ����λ����Ӳ����1��������wakeup�жϻ���ϵͳ���������0\n
 *   bit1:	ֻ�����¼�1����ʱ����λ����Ӳ����1��������wakeup�жϻ���ϵͳ���������0\n
 *   bit0:	ֻ�����¼�0����ʱ����λ����Ӳ����1��������wakeup�жϻ���ϵͳ���������0
 *
 * - WKUPCON��\n
 *   bit7:  �¼�3���ѱ���ѡ��0: ������    1: �½���\n
 *   bit6:  �¼�2���ѱ���ѡ��0: ������    1: �½���\n
 *   bit5:  �¼�1���ѱ���ѡ��0: ������    1: �½���\n
 *   bit4:  �¼�0���ѱ���ѡ��0: ������    1: �½���\n
 *   bit3:  �¼�3���ʹ�ܣ�0: ������¼�3�ķ���	1: ����¼�3�ķ����������λ��1�������ж���1����ô�¼�3�ķ���������wakeup�ж�\n
 *   bit2:  �¼�2���ʹ�ܣ�0: ������¼�2�ķ���	1: ����¼�2�ķ����������λ��1�������ж���1����ô�¼�3�ķ���������wakeup�ж�\n
 *   bit1:  �¼�1���ʹ�ܣ�0: ������¼�1�ķ���	1: ����¼�1�ķ����������λ��1�������ж���1����ô�¼�3�ķ���������wakeup�ж�\n
 *   bit0:	�¼�0���ʹ�ܣ�0: ������¼�0�ķ���	1: ����¼�0�ķ����������λ��1�������ж���1����ô�¼�3�ķ���������wakeup�ж�\n

 */





