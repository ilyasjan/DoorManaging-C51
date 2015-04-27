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

	SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X20;			//���ü�����������ʽ2
	PCON=0X80;			//�����ʼӱ�
	TH1=0XF3;		    //��������ʼֵ���ã�ע�Ⲩ������4800��
	TL1=0XF3;
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
	TR1=1;					    //�򿪼�����
}

void Usart() interrupt 4
{
	unsigned char receiveData;

	receiveData=SBUF; //��ȥ���յ�������
	RI = 0;           //��������жϱ�־λ
	//�����յ������ݷ��뵽���ͼĴ���
	//P1=receiveData;
	if(0xff==receiveData)
	{
	  DOOR=LOCK;
	}
	else{
	  DOOR=OPEN;
	}
	SBUF=receiveData;
	while(!TI);		  //�ȴ������������
	TI=0;			  //���������ɱ�־λ
}
