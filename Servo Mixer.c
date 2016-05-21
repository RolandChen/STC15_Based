#include<15.h>

// Servo Fast mixer
// STC15 working on 30.000 Mhz

int ta=0,tb=0,ia=0,ib=0;
int oa=0,ob=0;
unsigned int t_20ms=0;
unsigned int t=0;

//Pin definitions
//
//P32 elevator input 
//P33 aileron  input
//P34 left  output
//P35 right output
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
	//regardless of input freq.  once input is 0 it resets the counter
	
	if(P32==1)ta++;
	else if (ta!=0 && P32==0) {ia=ta;ta=0;}    //a: elevator          //ia,ib is the counted exact input.

  	if(P33==1)tb++;
  	else if (tb!=0 && P33==0) {ib=tb;tb=0;}    //b: aileron

  	t_20ms++;
  	if (t_20ms==2000)
	{
		t_20ms=0;
		if(ia>=100 && ib>=100 &&ia<=220 && ib<=220)
		{
			oa=((ia-150)/2) + ((ib-150)/2)+150;  
	  		ob=((ia-150)/2) - ((ib-150)/2)+150;
		}
		else{oa=0;ob=0;}
	}

  	//output counting part. also regardless of frequency.
  
	if(t_20ms<oa)P34=1;
	else P34=0;
		
	if(t_20ms<ob)P35=1;
	else P35=0;

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



