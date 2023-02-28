#include<reg51.h>	  //包含头文件

#define LEDData P0	  //宏定义P0口为LEDData

unsigned char code LEDCode[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	  //数码管段码表

unsigned char minit,second,count,count1;        	//分，秒，定时器定时变量

sbit add1=P1^0;						//甲对加分，每按一次加1分   /在未开始比赛时为加时间分
sbit dec1=P1^1;						//甲对减分，每按一次减1分	/在未开始比赛时为减时间分
sbit exchange=P1^2;					//交换场地
sbit add2=P1^3;						//乙对加分，每按一次加1分	/在未开始比赛时为加时间秒
sbit dec2=P1^4;						//乙对减分，每按一次减1分	/在未开始比赛时为减时间秒
sbit secondpoint=P0^7;				//秒闪动点
//----依次点亮数码管的位------
sbit led1=P2^7;	//数码管的位选引脚
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

sbit alam=P1^7;						//报警蜂鸣器引脚
sbit onoff=P3^2;					//开始暂停比赛按键
bit  playon=0;						//比赛进行标志位，为1时表示比赛开始，计时开启
bit  timeover=0;					//比赛结束标志位，为1时表示时间已经完
bit  AorB=0;						//甲乙对交换位置标志位
bit  halfsecond=0;					//半秒标志位

unsigned int scoreA;				//甲队得分
unsigned int scoreB;				//乙队得分
		

void Delay5ms(void)					//5ms延时函数，不精确，只是为了延时一段时间
{
	unsigned int i;					//声明变量
	for(i=100;i>0;i--);				//for循环100次
}
void display(void)					//显示函数
{
//-----------显示时间分--------------
	LEDData=LEDCode[minit/10];		//将分数据除以10得到的商就是十位数据，代入数组得到对应数字的段码赋值给单片机的P0口显示，下同
	led1=0;							//打开数码管的位选
	Delay5ms();						//延时
	led1=1;							//关闭数码管的位选
	LEDData=LEDCode[minit%10];		//将分数数据除以10的余数（取余）得到的就是个位数据，代入数组得到对应数字的段码赋值给单片机的P0口显示，下同
	led2=0;							//打开数码管的位选
	Delay5ms();						//延时
	led2=1;							//关闭数码管的位选
//-------------秒点闪动------------
	if(halfsecond==1)				//半秒标志位为1
		LEDData=0x80;				//显示秒点
	else							//半秒标志位不为1
		LEDData=0x00;				//关闭秒点显示
	led2=0;							//打开数码管的位选
	Delay5ms();						//延时
	led2=1;							//关闭数码管的位选
	secondpoint=0;					//秒点关闭
//-----------显示时间秒------------
	LEDData=LEDCode[second/10];
	led3=0;
	Delay5ms();
	led3=1;
	LEDData=LEDCode[second%10];
	led4=0;
	Delay5ms();
	led4=1;
//-----------显示1组的分数百位-------
	if(AorB==0)							  //A队在左
		LEDData=LEDCode[scoreA/100];	  //左边显示A队比分，分数除以100的商就是分数的百位，送显示
	else								  //B队在左
		LEDData=LEDCode[scoreB/100];	  //左边显示B队比分，分数除以100的商就是分数的百位，送显示
	led5=0;								  //打开数码管位选
	Delay5ms();							  //延时
	led5=1;								  //关闭数码管位选
//---------------显示1组分数的十位-----------
	if(AorB==0)
		LEDData=LEDCode[(scoreA%100)/10];
	else
		LEDData=LEDCode[(scoreB%100)/10];
	led6=0;
	Delay5ms();
	led6=1;

//---------------显示1组分数的个位-----------
	if(AorB==0)
		LEDData=LEDCode[scoreA%10];
	else
		LEDData=LEDCode[scoreB%10];
	led7=0;
	Delay5ms();
	led7=1;

//-----------显示2组分数的百位-------
	if(AorB==1)
		LEDData=LEDCode[scoreA/100];
	else
		LEDData=LEDCode[scoreB/100];
	led8=0;
	Delay5ms();
	led8=1;
//-----------显示2组分数的十位-----------
	if(AorB==1)
		LEDData=LEDCode[(scoreA%100)/10];
	else
		LEDData=LEDCode[(scoreB%100)/10];
	led9=0;
	Delay5ms();
	led9=1;

//-----------显示2组分数的个位-----------
	if(AorB==1)
		LEDData=LEDCode[scoreA%10];
	else
		LEDData=LEDCode[scoreB%10];
	led10=0;
	Delay5ms();
	led10=1;
}


//=========================按键检测程序================================================
void keyscan(void)
{
	if(onoff==0)			   //开始暂停按键按下，按键低电平有效
	{
		display();			   //用显示函数代替按键去抖的延时
		if(onoff==0)		   //再次判断按键按下
		{
			alam=0;					   //蜂鸣器响
			Delay5ms();Delay5ms();	   //延时
			alam=1;					   //蜂鸣器停止，按键音的作用
			TR1=0;					   //关闭定时器1
			timeover=0;				   //比赛结束标志位清零
			playon=!playon;				//开始标志位取反
			TR0=playon;					//如果开始，就开启计时，暂停就停止计时
			do
				display();				//扫描显示
			while(onoff==0);			//按键释放，按键不松开就会一直执行显示函数
		}
	}
	if(playon==0)						//如果是暂停或者停止比赛时
	{
		if(add1==0)						//加按键按下，此时是加时间模式
		{
			display();
			if(add1==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				if(minit<99)			//分钟数据小于99时
					minit++;			//分钟数据加
				else					//分钟数据不小于99
					minit=99;			//分钟数据赋值99，也就是最大就能加到99分钟
			}
			do
				display();				//扫描显示函数
			while(add1==0);				//按键释放，按键一直按下，就一直扫描显示函数
		}

		if(dec1==0)						//减按键，减分钟数据
		{
			display();
			if(dec1==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				if(minit>0)				 //分钟数据大于0
					minit--;			 //分钟数据减
				else					 //分钟数据不大于0	
					minit=0;			 //分钟数据赋值0，也就是最小就能减到0
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
				if(second<59)		   //秒最大能加到59
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
				if(second>0)			 //秒最小能减到0
					second--;
				else
					second=0;
			}
			do
				display();
			while(dec2==0);
		}

		if(exchange==0)					//交换场地按键
		{
			display();
			if(exchange==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				TR1=0;					//关闭T1计数器
				alam=1;					//关报警
   				AorB=~AorB;				//开启交换	
				minit=15;				//并将时间预设为15：00
				second=0;
			}
			do
				display();
			while(exchange==0);
		}	
	}
	else						   //比赛进行时
	{
		if(add1==0)						 //此时加按键是加分数功能
		{
			display();
			if(add1==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				if(AorB==0)				   //A队在左
				{
					if(scoreA<999)		   //分数最多加到999
						scoreA++;
					else
						scoreA=999;
				}
				else					   //B队在左
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

		if(dec1==0)						//减分数
		{
			display();
			if(dec1==0);
			{
				alam=0;
				Delay5ms();Delay5ms();
				alam=1;
				if(AorB==0)
				{
					if(scoreA>0)		 //分数最小减到0
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
	


//******************************主函数*************************************************
void main(void)
{
	TMOD=0x11;				//定时器0和1都是工作方式1
 	TL0=0xb0;
 	TH0=0x3c;				//定时器0初值50ms
 	TL1=0xb0;
 	TH1=0x3c;				//定时器1初值50ms
	minit=15;				//分钟初始值15
	second=0;				//秒钟初始值0
 	EA=1;					//打开中断系统总开关
	ET0=1;					//打开定时器T0中断允许
	ET1=1;					//打开定时器T1中断允许
 	TR0=0;					//关闭定时器T0定时开关
	TR1=0;					//关闭定时器T1定时开关
	P1=0xFF;				//所有IO口默认高电平
	P3=0xFF;
 	while(1)				//进入while循环
 	{
		keyscan();			//扫描按键函数
		display();			//扫描显示函数
    }
}

//*********************************中断服务函数**************************************
void  time0_int(void) interrupt 1 	  //定时器0服务函数	优先级1
{
 	TL0=0xb0;
 	TH0=0x3c;			 //进入中断后重新赋初值50ms
 	TR0=1;				 //打开定时器
  	count++;			 //每进入一次定时器count加一
	if(count==10)		 //加到10，也就是0.5s
	{
		halfsecond=0;	 //半秒标志位清零
	}

   	if(count==20)		 //加20次就是1s
   	{
		count=0;		 //清零
		halfsecond=1;	 //半秒标志置1
	
    	if(second==0)	 //秒等于0时
	 	{
			if(minit>0)	   //分钟大于0时
			{
				second=59; //秒等于59
				minit--;   //分钟减
			}
			else		   //分钟等于0时
			{
				timeover=1;//比赛停止
				playon=0;  //比赛停止
				TR0=0;	   //停止定时器T0
				TR1=1;	   //开启定时器T1
			}
		}
		else			   //秒不等于0时
			second--;	   //秒减
   	}
}


//*********************************中断服务函数**************************************
void  time1_int(void) interrupt 3	 //定时器1服务函数 优先级3
{
	TL1=0xb0;
 	TH1=0x3c;		 //重新赋初值50ms
 	TR1=1;			 //打开定时器T1
  	count1++;		 //变量加1
	if(count1==10)	 //加到10就是0.5秒
	{
		alam=0;		 //蜂鸣器响
	}

   	if(count1==20)	 //加到20就是1秒
   	{
		count1=0;	 //清零
		alam=1;		 //蜂鸣器停止，就是让蜂鸣器一秒响一声
	}
} 
