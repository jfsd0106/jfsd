#include<reg51.h>	  //����ͷ�ļ�

#define LEDData P0	  //�궨��P0��ΪLEDData

unsigned char code LEDCode[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	  //����ܶ����

unsigned char minit,second,count,count1;        	//�֣��룬��ʱ����ʱ����

sbit add1=P1^0;						//�׶Լӷ֣�ÿ��һ�μ�1��   /��δ��ʼ����ʱΪ��ʱ���
sbit dec1=P1^1;						//�׶Լ��֣�ÿ��һ�μ�1��	/��δ��ʼ����ʱΪ��ʱ���
sbit exchange=P1^2;					//��������
sbit add2=P1^3;						//�ҶԼӷ֣�ÿ��һ�μ�1��	/��δ��ʼ����ʱΪ��ʱ����
sbit dec2=P1^4;						//�ҶԼ��֣�ÿ��һ�μ�1��	/��δ��ʼ����ʱΪ��ʱ����
sbit secondpoint=P0^7;				//��������
//----���ε�������ܵ�λ------
sbit led1=P2^7;	//����ܵ�λѡ����
sbit led2=P2^6;
sbit led3=P2^5;
sbit led4=P2^4;
sbit led5=P2^3;
sbit led6=P2^2;
sbit led7=P2^1;
sbit led8=P2^0;
sbit led9=P3^7;
sbit led10=P3^6;
sbit led11=P3^5;

sbit alam=P1^7;						//��������������
sbit onoff=P3^2;					//��ʼ��ͣ��������
bit  playon=0;						//�������б�־λ��Ϊ1ʱ��ʾ������ʼ����ʱ����
bit  timeover=0;					//����������־λ��Ϊ1ʱ��ʾʱ���Ѿ���
bit  AorB=0;						//���ҶԽ���λ�ñ�־λ
bit  halfsecond=0;					//�����־λ

unsigned int scoreA;				//�׶ӵ÷�
unsigned int scoreB;				//�Ҷӵ÷�
		

void Delay5ms(void)					//5ms��ʱ����������ȷ��ֻ��Ϊ����ʱһ��ʱ��
{
	unsigned int i;					//��������
	for(i=100;i>0;i--);				//forѭ��100��
}
void display(void)					//��ʾ����
{
//-----------��ʾʱ���--------------
	LEDData=LEDCode[minit/10];		//�������ݳ���10�õ����̾���ʮλ���ݣ���������õ���Ӧ���ֵĶ��븳ֵ����Ƭ����P0����ʾ����ͬ
	led1=0;							//������ܵ�λѡ
	Delay5ms();						//��ʱ
	led1=1;							//�ر�����ܵ�λѡ
	LEDData=LEDCode[minit%10];		//���������ݳ���10��������ȡ�ࣩ�õ��ľ��Ǹ�λ���ݣ���������õ���Ӧ���ֵĶ��븳ֵ����Ƭ����P0����ʾ����ͬ
	led2=0;							//������ܵ�λѡ
	Delay5ms();						//��ʱ
	led2=1;							//�ر�����ܵ�λѡ
//-------------�������------------
	if(halfsecond==1)				//�����־λΪ1
		LEDData=0x80;				//��ʾ���
	else							//�����־λ��Ϊ1
		LEDData=0x00;				//�ر������ʾ
	led2=0;							//������ܵ�λѡ
	Delay5ms();						//��ʱ
	led2=1;							//�ر�����ܵ�λѡ
	secondpoint=0;					//���ر�
//-----------��ʾʱ����------------
	LEDData=LEDCode[second/10];
	led3=0;
	Delay5ms();
	led3=1;
	LEDData=LEDCode[second%10];
	led4=0;
	Delay5ms();
	led4=1;
//-----------��ʾ1��ķ�����λ-------
	if(AorB==0)							  //A������
		LEDData=LEDCode[scoreA/100];	  //�����ʾA�ӱȷ֣���������100���̾��Ƿ����İ�λ������ʾ
	else								  //B������
		LEDData=LEDCode[scoreB/100];	  //�����ʾB�ӱȷ֣���������100���̾��Ƿ����İ�λ������ʾ
	led5=0;								  //�������λѡ
	Delay5ms();							  //��ʱ
	led5=1;								  //�ر������λѡ
//---------------��ʾ1�������ʮλ-----------
	if(AorB==0)
		LEDData=LEDCode[(scoreA%100)/10];
	else
		LEDData=LEDCode[(scoreB%100)/10];
	led6=0;
	Delay5ms();
	led6=1;

//---------------��ʾ1������ĸ�λ-----------
	if(AorB==0)
		LEDData=LEDCode[scoreA%10];
	else
		LEDData=LEDCode[scoreB%10];
	led7=0;
	Delay5ms();
	led7=1;

//-----------��ʾ2������İ�λ-------
	if(AorB==1)
		LEDData=LEDCode[scoreA/100];
	else
		LEDData=LEDCode[scoreB/100];
	led8=0;
	Delay5ms();
	led8=1;
//-----------��ʾ2�������ʮλ-----------
	if(AorB==1)
		LEDData=LEDCode[(scoreA%100)/10];
	else
		LEDData=LEDCode[(scoreB%100)/10];
	led9=0;
	Delay5ms();
	led9=1;

//-----------��ʾ2������ĸ�λ-----------
	if(AorB==1)
		LEDData=LEDCode[scoreA%10];
	else
		LEDData=LEDCode[scoreB%10];
	led10=0;
	Delay5ms();
	led10=1;
}


//=========================����������================================================
void keyscan(void)
{
	if(onoff==0)			   //��ʼ��ͣ�������£������͵�ƽ��Ч
	{
		display();			   //����ʾ�������水��ȥ������ʱ
		if(onoff==0)		   //�ٴ��жϰ�������
		{
			alam=0;					   //��������
			Delay5ms();Delay5ms();	   //��ʱ
			alam=1;					   //������ֹͣ��������������
			TR1=0;					   //�رն�ʱ��1
			timeover=0;				   //����������־λ����
			playon=!playon;				//��ʼ��־λȡ��
			TR0=playon;					//�����ʼ���Ϳ�����ʱ����ͣ��ֹͣ��ʱ
			do
				display();				//ɨ����ʾ
			while(onoff==0);			//�����ͷţ��������ɿ��ͻ�һֱִ����ʾ����
		}
	}
	if(playon==0)						//�������ͣ����ֹͣ����ʱ
	{
		if(add1==0)						//�Ӱ������£���ʱ�Ǽ�ʱ��ģʽ
		{
			display();
			if(add1==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				if(minit<99)			//��������С��99ʱ
					minit++;			//�������ݼ�
				else					//�������ݲ�С��99
					minit=99;			//�������ݸ�ֵ99��Ҳ���������ܼӵ�99����
			}
			do
				display();				//ɨ����ʾ����
			while(add1==0);				//�����ͷţ�����һֱ���£���һֱɨ����ʾ����
		}

		if(dec1==0)						//������������������
		{
			display();
			if(dec1==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				if(minit>0)				 //�������ݴ���0
					minit--;			 //�������ݼ�
				else					 //�������ݲ�����0	
					minit=0;			 //�������ݸ�ֵ0��Ҳ������С���ܼ���0
			}
			do
				display();
			while(dec1==0);
		}

		if(add2==0)
		{
			display();
			if(add2==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				if(second<59)		   //������ܼӵ�59
					second++;
				else
					second=59;
			}
			do
				display();
			while(add2==0);
		}

		if(dec2==0)
		{
			display();
			if(dec2==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				if(second>0)			 //����С�ܼ���0
					second--;
				else
					second=0;
			}
			do
				display();
			while(dec2==0);
		}

		if(exchange==0)					//�������ذ���
		{
			display();
			if(exchange==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				TR1=0;					//�ر�T1������
				alam=1;					//�ر���
   				AorB=~AorB;				//��������	
				minit=15;				//����ʱ��Ԥ��Ϊ15��00
				second=0;
			}
			do
				display();
			while(exchange==0);
		}	
	}
	else						   //��������ʱ
	{
		if(add1==0)						 //��ʱ�Ӱ����Ǽӷ�������
		{
			display();
			if(add1==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				if(AorB==0)				   //A������
				{
					if(scoreA<999)		   //�������ӵ�999
						scoreA++;
					else
						scoreA=999;
				}
				else					   //B������
				{
					if(scoreB<999)
						scoreB++;
					else
						scoreB=999;
				}
			}
			do
				display();
			while(add1==0);
		}

		if(dec1==0)						//������
		{
			display();
			if(dec1==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				if(AorB==0)
				{
					if(scoreA>0)		 //������С����0
						scoreA--;
					else
						scoreA=0;
				}
				else
				{
					if(scoreB>0)
						scoreB--;
					else
						scoreB=0;
				}
			}
			do
				display();
			while(dec1==0);
		}

		if(add2==0)
		{
			display();
			if(add2==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				if(AorB==1)
				{
					if(scoreA<999)
						scoreA++;
					else
						scoreA=999;
				}
				else
				{
					if(scoreB<999)
						scoreB++;
					else
						scoreB=999;
				}
			}
			do
				display();
			while(add2==0);
		}

		if(dec2==0)
		{
			display();
			if(dec2==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				if(AorB==1)
				{
					if(scoreA>0)
						scoreA--;
					else
						scoreA=0;
				}
				else
				{
					if(scoreB>0)
						scoreB--;
					else
						scoreB=0;
				}
			}
			do
				display();
			while(dec2==0);
		}
	}
}
	


//******************************������*************************************************
void main(void)
{
	TMOD=0x11;				//��ʱ��0��1���ǹ�����ʽ1
 	TL0=0xb0;
 	TH0=0x3c;				//��ʱ��0��ֵ50ms
 	TL1=0xb0;
 	TH1=0x3c;				//��ʱ��1��ֵ50ms
	minit=15;				//���ӳ�ʼֵ15
	second=0;				//���ӳ�ʼֵ0
 	EA=1;					//���ж�ϵͳ�ܿ���
	ET0=1;					//�򿪶�ʱ��T0�ж�����
	ET1=1;					//�򿪶�ʱ��T1�ж�����
 	TR0=0;					//�رն�ʱ��T0��ʱ����
	TR1=0;					//�رն�ʱ��T1��ʱ����
	P1=0xFF;				//����IO��Ĭ�ϸߵ�ƽ
	P3=0xFF;
 	while(1)				//����whileѭ��
 	{
		keyscan();			//ɨ�谴������
		display();			//ɨ����ʾ����
    }
}

//*********************************�жϷ�����**************************************
void  time0_int(void) interrupt 1 	  //��ʱ��0������	���ȼ�1
{
 	TL0=0xb0;
 	TH0=0x3c;			 //�����жϺ����¸���ֵ50ms
 	TR0=1;				 //�򿪶�ʱ��
  	count++;			 //ÿ����һ�ζ�ʱ��count��һ
	if(count==10)		 //�ӵ�10��Ҳ����0.5s
	{
		halfsecond=0;	 //�����־λ����
	}

   	if(count==20)		 //��20�ξ���1s
   	{
		count=0;		 //����
		halfsecond=1;	 //�����־��1
	
    	if(second==0)	 //�����0ʱ
	 	{
			if(minit>0)	   //���Ӵ���0ʱ
			{
				second=59; //�����59
				minit--;   //���Ӽ�
			}
			else		   //���ӵ���0ʱ
			{
				timeover=1;//����ֹͣ
				playon=0;  //����ֹͣ
				TR0=0;	   //ֹͣ��ʱ��T0
				TR1=1;	   //������ʱ��T1
			}
		}
		else			   //�벻����0ʱ
			second--;	   //���
   	}
}


//*********************************�жϷ�����**************************************
void  time1_int(void) interrupt 3	 //��ʱ��1������ ���ȼ�3
{
	TL1=0xb0;
 	TH1=0x3c;		 //���¸���ֵ50ms
 	TR1=1;			 //�򿪶�ʱ��T1
  	count1++;		 //������1
	if(count1==10)	 //�ӵ�10����0.5��
	{
		alam=0;		 //��������
	}

   	if(count1==20)	 //�ӵ�20����1��
   	{
		count1=0;	 //����
		alam=1;		 //������ֹͣ�������÷�����һ����һ��
	}
} 
