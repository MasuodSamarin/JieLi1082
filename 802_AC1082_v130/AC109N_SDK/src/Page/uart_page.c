/*! \page1  UART ���ָ��
 *
 * \section intro0_sec UART �������
 * - CD002 UART���ĸ�����\n
 *   ����1��TXΪP06��RXΪP07\n
 *   ����2��TXΪP24��RXΪP25\n
 *   ����3��TXΪP32��RXΪP33\n
 *   ����4��TXΪUSBDP��RXΪUSBDM
 * \section uart0  UART �Ĵ�������
 * - UART_CON��UART���ƼĴ���\n
 *   Bit0��UART Enable������Ч��ResetֵΪ0\n
 *   Bit1��9bitģʽ������Ч��ResetֵΪ0\n
 *   Bit2��TX�ж���������Ч��ResetֵΪ0����TX PendingΪ1������TX�ж�����Ϊ1���������ж�\n
 *   Bit3��RX�ж���������Ч��ResetֵΪ0����RX PendingΪ1������RX�ж�����Ϊ1���������ж�\n
 *   Bit5~4�������ʿ��ƼĴ�����2λ��ResetֵΪ00 \n
 *   Bit7~6��Reserved����Ϊ0\n
 *   ע�������жϵ�ַΪ��0x003B;

 * - UART_STA�� UART״̬�Ĵ���\n
 *   Bit0��9Bitģʽʱ��RX���յ��ĵ�9λ��ResetֵΪX\n
 *   Bit1��9Bitģʽʱ��TX���͵ĵ�9λ��ResetֵΪX\n
 *   Bit4: ���RX Pending, д1��գ�д0��Ч\n
 *   Bit5: ���TX Pending��д1��գ�д0��Ч\n
 *   Bit6��RX Pending��ResetֵΪ0����������㣬��������1��\n
 *   Bit7��TX Pending��ResetֵΪ1����������㣬��������1��

 * - UTBAUD�������ʼĴ�����8λ��ResetֵΪX����֮ǰҪ��ʼ��\n
 *   �����ʼ��㹫ʽ�������� = Freq_sys / ((UTBAUD+1) *8)\n
 *   ���Ϲ�ʽUTBAUDΪ10λ�Ĵ���

 * - UTBUF:\n
 *   ��UART���Ϳ���ʱ��дUTBUF������һ�η��͡����͵����ݾ���дUTBUF�����ݡ�\n
 *   ��RX PendingΪ1ʱ����UTBUF�ɶ������յ��ֽڡ�ע�⣬�����Ҫ�����RX Pending����������յ����ֽڲ�����UTBUF���ᶪʧ��
 */



