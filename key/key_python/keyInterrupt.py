#!/usr/bin/python
# -*- coding:utf-8 -*-
#�˰汾Ϊ�жϰ汾����������ʱ������жϣ����������жϴ�����ʵ�����ǵĹ���
import RPi.GPIO as GPIO
import time

#����һ����Ű������źŵ��б�
keys_pin = [6,13,19,26];

def key_Interrupt(key):
			print("KEY %d PRESS" %(keys_pin.index(key)+1));
	
print("Key Test Program,Interrupt version.");			
GPIO.setmode(GPIO.BCM);#����ΪBCM����ģʽ
for i in keys_pin:
	GPIO.setup(i,GPIO.IN,GPIO.PUD_UP);#����Ϊ���� ����ģʽ
	pass		
#����¼����� �½��ش�������keyx_Interrupt()��������ʱ200
for i in range(len(keys_pin)):
	GPIO.add_event_detect(keys_pin[i],GPIO.FALLING,key_Interrupt,200)
	pass
while True:
	time.sleep(1)
