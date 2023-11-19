#include<bits/stdc++.h>
#include<unistd.h>
#define endl '\n'
using namespace std;
typedef struct CPUSTAT
{
	char name[20];
	unsigned int user;
	unsigned int nice;
	unsigned int system;
	unsigned int idle;
	unsigned int lowait;
	unsigned int irq;
	unsigned int lowirq;
}CPU_STAT;
double getCpuUse(CPU_STAT *o,CPU_STAT *n)
{
	unsigned long od,nd;
	od=(unsigned long)(o->user+o->nice+o->system+o->idle+o->lowait+o->irq+o->lowirq);
	nd=(unsigned long)(n->user+n->nice+n->system+n->idle+n->lowait+n->irq+n->lowirq);
	double sum=nd-od,idle=n->idle-o->idle;
	return (sum-idle)/sum;
}
CPU_STAT getCpuStat(void)
{
	FILE *fd;
	int n;
	char buff[256];
	CPU_STAT cpust;
	fd=fopen("/proc/stat","r");
	fgets(buff,sizeof(buff),fd);
	if(strstr(buff,"cpu")!=NULL)
		sscanf(buff,"%s %u %u %u %u %u %u %u",cpust.name,&cpust.user,&cpust.nice,&cpust.system,&cpust.idle,&cpust.lowait,&cpust.irq,&cpust.lowirq);
	return cpust;
	
}
double getCPUtemp(void)
{
	FILE *fd;
	int temp;
	char buff[256];
	fd=fopen("/sys/class/thermal/thermal_zone0/temp","r");
	fgets(buff,sizeof(buff),fd);
	sscanf(buff,"%d",&temp);
	return double(temp)/1000.0;
}
int main()
{
	CPU_STAT old,now;
	while(1)
	{
		now=getCpuStat();
		cout<<"CPU Usage:"<<to_string(getCpuUse(&old,&now)*100)+"%"<<endl;
		cout<<"CPU Temp:"<<to_string(getCPUtemp())+"℃"<<endl<<endl;
		old=now;
		sleep(1);
	}
	return 0;
}


