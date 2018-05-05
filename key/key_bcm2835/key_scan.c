/********************************************************************************* 
  *Copyright(C),MrzhangF1ghter studio
  *FileName:key_scan.c
  *Author:MrzhangF1ghter 
  *Version:1.0 
  *Date:2018/5/5 
  *Description:��ݮ�ɲʺ�IO��չ�尴������ ɨ�跽��ʵ�֡�
  *Others:Learn more from��https://github.com/MrzhangF1ghter/RainbowCandyBoard
  												 http://www.airspayce.com/mikem/bcm2835/group__gpio.html
  *Function List:
  *History:
  *compile:gcc -o key_scan key_scan.c -lbcm2835
  �ʺ���ϰ���������������
   ���� |GPIO| wPi |�����|
   KEY1 BCM6 	pin22	34    
   KEY2 BCM13 pin23	36
   KEY3 BCM19 pin24	38
   KEY4 BCM26 pin25 40
**********************************************************************************/  
#include <bcm2835.h>
#include <stdio.h>

int keys_pin[4]={6,13,19,26};//����һ�����led��Ӧgpio���źŵ���������
int i;
int main()
{
	printf("Key Test Program,bcm2835 version\n");	
	if (!bcm2835_init())return 1;
	for(i=0;i<4;i++)//ѭ������keys_pin�����������
	{
		bcm2835_gpio_fsel(keys_pin[i], BCM2835_GPIO_FSEL_INPT);//����Ϊ����ģʽ
		bcm2835_gpio_set_pud(keys_pin[i], BCM2835_GPIO_PUD_UP);//����Ϊ����ģʽ
	}
	i=0;
	while (1)
	{
		i++;
		if(bcm2835_gpio_lev(keys_pin[i]) == 0)//��⵽������Ϊ�͵�ƽʱ
		{  
			printf ("KEY%d PRESS\n",i+1) ;
    		while(bcm2835_gpio_lev(keys_pin[i]) == 0)//�ȴ������ɿ� ����
				bcm2835_delay(100);
		}
		bcm2835_delay(10);//��ʱ10ms
		if(i==3)//ѭ��������0�����¼���
			i=-1;
	}
	bcm2835_close();
	return 0;
}
