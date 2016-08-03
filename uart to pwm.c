#include<15.h>
//#include <intrins.h>
// Simple ESC @ 50HZ IO
//STC15 working on 30.000 Mhz
unsigned char oa=0,ob=0,oc=0,od=0;
unsigned int t_20ms=0;
//unsigned int t=0;
unsigned char tcount=0;
char rx=0;
bit rxc = 0;
//Pin definitions
//
//P33,P34,P35,P36  output
//

void Timer0Init(void)  //interrupt 1 on 10us		
{
	AUXR |= 0x80;		
	TMOD &= 0xF0;			
	TL0 = 0xD4;		
	TH0 = 0xFE;		
	TF0 = 0;		
	TR0 = 1;
	ET0 = 1;
	EA =1;
}

void UartInit(void)		//2400bps@30.000MHz
{
	SCON = 0x50;		
	AUXR |= 0x40;		
	AUXR &= 0xFE;	
	TMOD &= 0x0F;	
	TL1 = 0xCB;		
	TH1 = 0xF3;		
	ET1 = 0;	
	TR1 = 1;	
	ES = 1;   
}




void timer0(void) interrupt 1 
{

	t_20ms++;
	if (t_20ms>=2000)
	{
		t_20ms=0;//Add func:more than 3.xs no signal==>(150,150,100,100)
		tcount++;
  	}
  	if(tcount>=200)
  	{
		tcount=0;
		oa=150;ob=150;oc=100;od=100;
  	}
	
	if(t_20ms<oa)P33=1;
  	else P33=0;
	
	if(t_20ms<ob)P34=1;
	else P34=0;
		
	if(t_20ms<oc)P35=1;
	else P35=0;

	if(t_20ms<od)P36=1;
	else P36=0;
}



void main()
{
	Timer0Init();
	UartInit();
	oa=150,ob=150,oc=100,od=100;
	while(1)
  {
		if(rxc == 1)
	  {
			rxc = 0;
			tcount=0;
			switch(rx)
			{ 
				// oa: ch1  ob:ch2  oc:sw7  od:sw8
				//on apm/pixhawk channel ELE needs reverse.
				case 1:oa=150;ob=150;oc=100;od=100;break;
				case 2:oa=140;ob=150;oc=100;od=100;break;
				case 3:oa=160;ob=150;oc=100;od=100;break;
				
				case 4:oa=150;ob=140;oc=100;od=100;break;
				case 5:oa=140;ob=140;oc=100;od=100;break;
				case 6:oa=160;ob=140;oc=100;od=100;break;
				
				case 7:oa=150;ob=160;oc=100;od=100;break;
				case 8:oa=140;ob=160;oc=100;od=100;break;
				case 9:oa=160;ob=160;oc=100;od=100;break;
				
				case 'a':oa=150;ob=150;oc=220;od=100;break;
				
				case 'b':oa=150;ob=150;oc=100;od=220;break;
			
			
			  default:oa=150;ob=150;oc=100;od=100;   break;
			}
			ES = 1;
		}
	}
}




void isr_uart(void) interrupt 4
{
    if(RI)
    {
        RI = 0;     
        rx = SBUF;
	ES = 0;
	rxc = 1;
    }
}




