/*! \page8 DAC ���ָ��
 *
 * \section dac0 DAC ����
 * - CD002 ��9 �ֲ�����\n
 * \section dac1 ���ֲ��ֿ��ƼĴ���
 * - DAC_CON0���ɶ�д��\n
 *   Bit3~0��DAC����������\n
 *   0000��44.1KHz\n
 *   0001��48KHz\n
 *   0010��32KHz\n
 *   0100��22.05KHz\n
 *   0101��24KHz\n
 *   0110��16KHz\n
 *   1000��11.025KHz\n
 *   1001��12KHz\n
 *   1010��8KHz\n
 *   others��reserved����������\n
 *   Bit4��DACģ��ʹ��  0���ر�DAC  1����DAC\n
 *   Bit7~5������ģʽ����\n
 *   0xx��Lout = Lin��Rout = Rin\n
 *   100��Lout = Rout = Lin + Rin\n
 *   101��Lout = Rout = Lin - Rin\n
 *   110��Lout = Rout = Lin\n
 *   111��Lout = Rout = Rin

 * - DAC_VLML\n
 *   DAC�������������ƼĴ�����ֻд������Ϊ��ȷ��ֵ��\n
 *   �˼Ĵ���������Ϊ15bit������д����ֵΪ0-16384��0Ϊ������16384Ϊ���������\n
 *   ���ô˼Ĵ���ʱ������˼Ĵ���д�����Σ���д���7λ����д���8λ��\n
 *   �磬������Ϊ0x1234����д��0x12����д��0x34

 * - DAC_VLMR\n
 *   DAC�������������ƼĴ�����ֻд������Ϊ��ȷ��ֵ��\n
 *   �˼Ĵ���������Ϊ15bit������д����ֵΪ0-16384��0Ϊ������16384Ϊ���������\n
 *   ���ô˼Ĵ���ʱ������˼Ĵ���д�����Σ���д���7λ����д���8λ��\n
 *   �磬������Ϊ0x1234����д��0x12����д��0x34\n
 *
 * - KV_START\n
 *   ��������ʼ��ַ�Ĵ�����ֻд������Ϊ��ȷ��ֵ��\n
 *   ������ʼ��ַʱ������˼Ĵ���д�����Σ���д���ַ�ĸ�8λ����д���ַ�ĵ�8λ��\n
 *   �磬��������ʼ��ַΪ0x1234����д��0x12����д��0x34��\n
 *
 * - KV_END\n
 *   ������������ַ�Ĵ�����ֻд������Ϊ��ȷ��ֵ��\n
 *   ���ý�����ַʱ������˼Ĵ���д�����Σ���д���ַ�ĸ�8λ����д���ַ�ĵ�8λ��\n
 *   �磬�����ý�����ַΪ0x1234����д��0x12����д��0x34��\n
 *
 * - KV_CNT:\n
 *   �������ظ������Ĵ�����ֻд������Ϊ��ȷ��ֵ��\n
 *   �˼Ĵ��������Ϲ���10bit������д���ֵΪ1-1023��д��0ֵ���������������д��100��ʾ����KV_START��KV_END�����ݲ���100�Σ��Դ����ơ�
 *   ���ô˼Ĵ���ʱ������˼Ĵ���д�����Σ���д���2λ����д���8λ��\n
 *   �磬�������ظ�����ΪΪ0x123����д��0x1����д��0x23��\n
 *
 * - KV_VLM:\n
 *   ������������ֻд������Ϊ��ȷ��ֵ��\n
 *   ����������Ϊһ��7bit���޷�������0Ϊ������127Ϊ�������
 *
 * \section dac2 ģ�ⲿ�ֿ��ƼĴ���
 * - DAA_CON0\n
 *   Bit0��DAC enable,����Ч\n
 *   Bit1��DACVDD��ѹ����λ\n
 *   Bit2��LDO1enable������Ч\n
 *   Bit3��LDO2 enable������Ч\n
 *   Bit4: AMUX enable������Ч\n
 *   Bit5: AMUX gain boost����λ������Ч\n
 *   Bit6��Power up/down pop pop noise suppress����λ������Ч\n
 *   Bit7��AMUX mute����λ������Ч \n
 *
 * - DAA_CON1\n
 *   Bit4~0��DAC L channel gain control\n
 *   Bit7~0: Reserve
 *
 * - DAA_CON2\n
 *   Bit4~0��DAC R channel gain control\n
 *   Bit5��LIN-in BUF enable��For ADC record������Ч\n
 *   Bit6��AMUX L+R>L����λ������Ч\n
 *   Bit7��AMUX L+R>R����λ������Ч\n
 *
 * - DAA_CON3\n
 *   Bit4~0��MIC gain control\n
 *   Bit5��MIC OPA enable������Ч\n
 *   Bit6��MIC > L����λ������Ч\n
 *   Bit7��MIC > R����λ������Ч\n

 * - DAA_CON4\n
 *   Bit0��LIN-in 0 L channel enable,����Ч\n
 *   Bit1��LIN-in 0 R channel enable,����Ч\n
 *   Bit2��LIN-in 1 L channel enable������Ч\n
 *   Bit3��LIN-in 1 R channel enable������Ч\n
 *   Bit4: VCM detect block enable������Ч\n
 *   Bit5: DAC with AMUX common mode����λ������Ч\n
 *   Bit6��VCM_OUT buffer enable����λ������Ч\n
 *   Bit7��VCM_OUT pull down 1K �������λ������Ч \n
 */
