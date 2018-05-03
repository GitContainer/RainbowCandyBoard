#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>//wiringPi·��

#define LED1 0//�궨��LED1ΪGPIO17��wiringPi��ΪwPi0 (GPIO_GEN0)
#define LED2 2
#define LED3 3
#define LED4 21

#define KEY1 22//�궨��LED1ΪGPIO17��wiringPi��ΪwPi0 (GPIO_GEN0)
#define KEY2 23
#define KEY3 24
#define KEY4 25
int main()
{
		int leds_pin[4]={0,2,3,21};//���led��Ӧgpio���źŵ�����
		int keys_pin[4]={22,23,24,25};//���led��Ӧgpio���źŵ�����
		int i,count=0;//��������
		printf("Welcome to IODevelopBoard!\n");
		printf("KEYs test,wiringPi version\n");
		wiringPiSetup();//wiringPi���ʼ��
		/*��ѭ��һ��������������а�������ΪOUTPUTģʽ��
		����ԭ��digitalWrite (int pin, int value)*/
		for(i=0;i<4;i++)
		{
			//LED��ʼ��
			pinMode(leds_pin[i],OUTPUT);
			digitalWrite(leds_pin[i],HIGH);//��ʼ��Ϊ�ߵ�ƽ
			//������ʼ��
			pinMode(keys_pin[i],INPUT);
			pullUpDnControl(keys_pin[i],PUD_UP);
		}
		
		while(1)//��ˮ��
		{
			//ɨ�谴����
			for(int i=0;i<4;i++)
			{
				if(!digitalRead(keys_pin[i]))
				{
						delay(20);
						if(!digitalRead(keys_pin[i]))
						{
							while(!digitalRead(keys_pin[i]));//�ȴ�����
						}
						printf("key%d has pressed!\n",i+1);
						count++;
						if(count%2==0)
							digitalWrite(leds_pin[i],LOW);//ͨ��һ���������ߵ��Ƶ�״̬
						else
							digitalWrite(leds_pin[i],HIGH);//��ʼ��Ϊ�ߵ�ƽ
						if(count==2)
							count=0;
				}
			}
		}
	}