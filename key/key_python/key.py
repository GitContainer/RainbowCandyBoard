#!/usr/bin/python
# -*- coding:utf-8 -*-
#�˰汾Ϊɨ�跨�жϰ����Ƿ��£��ķ�cpu��Դ������ʹ���жϷ�ʵ��
import RPi.GPIO as GPIO
import time
i=0;
#����һ����Ű������źŵ��б�
keys_pin = [6,13,19,26];

print("Key Test Program");
GPIO.setmode(GPIO.BCM);#����ΪBCM����ģʽ
for x in keys_pin:
	GPIO.setup(x,GPIO.IN,GPIO.PUD_UP);#����Ϊ���� ����ģʽ
	pass
	
while True:
	i=i+1;
	time.sleep(0.05)#����5����ɨ��һ�ΰ����Ƿ���
	if GPIO.input(keys_pin[i]) == 0:
		print("KEY %d PRESS" %(i+1));
		while GPIO.input(keys_pin[i]) == 0:#����
			time.sleep(0.01);
	if(i==3):
		i=-1;
