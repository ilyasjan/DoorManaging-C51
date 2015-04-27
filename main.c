#include<reg51.h>
#define OPEN 0
#define LOCK 1
void UsartConfiguration();
sbit DOOR =P2^0;
void main()
{
	P1=0x00;
	UsartConfiguration();
	while(1)
	{
	}
}

void UsartConfiguration()
{	

	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XF3;		    //计数器初始值设置，注意波特率是4800的
	TL1=0XF3;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					    //打开计数器
}

void Usart() interrupt 4
{
	unsigned char receiveData;

	receiveData=SBUF; //出去接收到的数据
	RI = 0;           //清除接收中断标志位
	//将接收到的数据放入到发送寄存器
	//P1=receiveData;
	if(0xff==receiveData)
	{
	  DOOR=LOCK;
	}
	else{
	  DOOR=OPEN;
	}
	SBUF=receiveData;
	while(!TI);		  //等待发送数据完成
	TI=0;			  //清除发送完成标志位
}
