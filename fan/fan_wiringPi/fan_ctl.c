#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <wiringPi.h>
#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define FREQ_PATH "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq"
#define MAX_SIZE 32
#define FAN 1//原生PWM引脚 GPIO18,wiringPi引脚为1

int main(void)

{

	int fd_temp,fd_freq;
	double temp = 0;
	int freq;
	char buf_temp[MAX_SIZE];
	char buf_freq[MAX_SIZE];
	int speed;//速度值
	float speed_precent;
	int min_speed=10;//最小速度值
	int temp_thre=40;//启动风扇的阈值
	int speed_step=100;//步进值
	if(wiringPiSetup()==-1)
	{
		printf("wiringPi gpio setup error\n");
		return -1;
	}
	pinMode(FAN,PWM_OUTPUT);//配置为PWM输出
	while(1)//循环检测
	{
		//open
		fd_temp = open(TEMP_PATH,O_RDONLY);//打开文件
		fd_freq = open(FREQ_PATH,O_RDONLY);//打开文件
		if(fd_temp<0)
		{
			printf("failed to open /sys/class/thermal/thermal_zone0/temp\n");
			return -1;
		}
		if(fd_freq<0)
		{
			printf("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq\n");
			return -1;
		}
		//read
		if(read(fd_temp,buf_temp,MAX_SIZE)<0)
		{
			printf("failed to read temp\n");
			return -1;
		}	
		if(read(fd_freq,buf_freq,MAX_SIZE)<0)
		{
			printf("failed to read freq\n");
			return -1;
		}
		temp = atoi(buf_temp)/1000.0;//将读到的温度值转化为浮点数;
		freq = atol(buf_freq);//将读到的频率值转化为整数;
		if(temp<=temp_thre)//如果CPU温度小于启动阈值
		{
			pwmWrite(FAN,0);//风扇转速为0
		}
		else if(temp>temp_thre) //如果CPU温度大于启动阈值
		{
			pwmWrite(FAN,1023);//全速运转10ms启动防卡转
			usleep(10);
			speed = min_speed+(temp-temp_thre)*speed_step;//速度=最小速度+温度差*速度步进值
			if(speed>1023)//防止pwm溢出
				speed=1023;
			pwmWrite(FAN,speed);//设置pwm值
		}
		//speed_precent = (speed/1023.0)*100;
		printf("cpu temp:%.2f,cpu freq:%.2fGhz,fan speed:%.0f%%\n",temp,freq/1000000.0,(float)((speed/1023.0)*100));
		close(fd_temp);//关闭文件
		close(fd_freq);//关闭文件
		sleep(1);//睡眠5s
	}

}
