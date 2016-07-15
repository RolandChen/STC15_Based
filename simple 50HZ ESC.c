#include<15.h>
//#include <intrins.h>
// Simple ESC @ 50HZ IO
//STC15 working on 30.000 Mhz
 int ta=0,ia=0;
 int oa=0;
unsigned int t_20ms=0;
unsigned int t=0;

//Pin definitions
//
//P32  input 
//
//P34  output
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


void timer0(void) interrupt 1 
{
	//input counting part
	//regardless of input freq.  once input is 0 reset the counter
	
	if(P32==1)ta++;
	else if(ta!=0 && P32==0) {ia=ta;ta=0;}     //a: elevator      
    t_20ms++;
    if (t_20ms==2000)
	{
		t_20ms=0;
		if(ia>100) oa=(ia-100)*20;
		else oa=0;
	}

  //output counting part. also regardless of frequency.
	if(t_20ms<oa)P34=1;
	else P34=0;

}

void main()
{
	Timer0Init();
	for(;;)
	{
          //nothing to do in the main loop.
		  //All the code has been put in the interrupt of timer0
	}
}



