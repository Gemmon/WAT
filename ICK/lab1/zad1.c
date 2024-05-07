#include <REGX52.H>	  

 void klawisz() 
 {
 	switch(P2) 
	{
		case 0xEE:
			P1 = 0x30;  //'0'
			break;
		case 0xDE:
			P1 = 0x31;	//'1'
			break;
		case 0xBE:
			P1 = 0x32;	//'2'
			break;
		case 0x7E:
			P1 = 0x33;	//'3'
			break;
		case 0xED:
			P1 = 0x34;	//'4'
			break;
		case 0xDD:
			P1 = 0x35;	//'5'
			break;
		case 0xBD:
			P1 = 0x36;	//'6'
			break;
		case 0x7D:
			P1 = 0x37;	//'7'
			break;
		case 0xEB:
			P1 = 0x38;	//'8'
			break;
		case 0xDB:
			P1 = 0x39;	//'9'
			break;
		case 0xBB:
			P1 = 0x40;	//'10'
			break;
		case 0x7B:
			P1 = 0x41;	//'11'
			break;
		case 0xE7:
			P1 = 0x42;	//'12'
			break;
		case 0xD7:
			P1 = 0x43;	//'13'
			break;
		case 0xB7:
			P1 = 0x44;	//'14'
			break;
		case 0x77:
			P1 = 0x45;	//'15'
			break;

		default: 
			P1 = 0xFF;
			break;
	}
 }																		  

 
void main()
{
	P1 = 0xFF; //poczatkowe ustawienie
	P2 = 0xEF; //
	while(1)
	{
			 switch(P2)
			 {
			 	case 0xEF:
					P2 = 0xDF;				
					break;
				case 0xDF:
					P2 = 0xBF;
					break;
				case 0xBF:
					P2 = 0x7F;
					break;
				case 0x7F:
					P2 = 0xEF;
					break; 
			 }
			 if (P3_2 == 1) 
		   {
			 	P1 = 0xFF;
			 }
	   }
}