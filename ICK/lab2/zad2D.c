#include <REGX52.H>



 sbit clkM = P2^0;
 sbit dtaM = P2^1;
 sbit clkS = P2^2;
 sbit dtaS = P2^3;

 bit bM;
 int dt = 10;
 int tt = 100;

 volatile unsigned char liczbaM = 0x00;
 unsigned char liczbaS = 0x00;
 unsigned char bajt = 0x00;

 void czekaj(int i)
 {
	unsigned int k, l, m;
	for (l = 0; l < i; l++)
	{
		k = 500;
		m = 1000;
		k = m * l;
	}
 }

 void liczInt0() interrupt 0
 {
 	EX0 = 0;
	liczbaM ++;
	if (liczbaM == 255) liczbaM = 0;
	EX0 = 1;
	bM = 0;
 }

 void zapiszBajt(unsigned char bajt)
 {
	unsigned char liczbaBitow = 8; 	
	
	  dtaM = 0;
		czekaj(dt);
		czekaj(tt);
		clkM = 0;
		czekaj(tt);
		clkM = 1;
		czekaj(tt);
	 
	 
	do 
	{
		dtaM = bajt & 0x80;
		czekaj(dt);
		czekaj(tt);
		clkM = 0;
		czekaj(tt);
		clkM = 1;
		czekaj(tt);
		bajt = (bajt << 1) + 1;
	} while(--liczbaBitow);
	
	  dtaM = 1;
		czekaj(dt);
		czekaj(tt);
		clkM = 0;
		czekaj(tt);
		clkM = 1;
		czekaj(tt);
	
	clkM = 1;
	dtaM = 1;
 }

 
 unsigned char czytajBajt()
 {
	unsigned char liczbaBitow = 10; 	
	unsigned char wynik = 0; 	
	do 
	{
		while(clkS == 1)
		{	}
		if(liczbaBitow > 1)
		{
		wynik = wynik << 1;
		if (dtaS) wynik ++;
		}
		while(clkS == 0)
		{		}
	} while(--liczbaBitow);
	return wynik;
 }

 
 
 void initInt0()
 {
 	liczbaM = 0;

	IT0 = 1;	//INT0 aktywne zero
	EX0 = 1;	//Wlaczenia INT0
	EA = 1;		//Wlaczenie wszstkich przerwan
 }

 void main()
 {
 	initInt0();
	P1 = 0;
	clkM = 1;
	dtaM = 1;

	while (P0_0 == 1)		//MASTER
	{
		while(bM)	
		{
			czekaj(dt);
		}
		P1 = liczbaM;
		zapiszBajt(liczbaM);
		bM = 1;	 
	}

	while (P0_0 == 0) 	//SLAVE
	{
		while(clkS == 1)
		{
			czekaj(dt);
		}
		liczbaS = czytajBajt();
		P1 = liczbaS;
	}
 }