#include<lpc214x.h>
void delay(unsigned int z);       
void pll();
int main(void)
{
    IO0DIR=0xffffffff;
    IO1DIR = 0x0;                         
    pll();                  //Fosc=12Mhz,CCLK=60Mhz,PCLK=60MHz
    while(1) {
      if((IO1PIN & (1<<16)) ==0)
        {           
        IO0SET=0x000000ff;
        delay(1000);            //1sec delay
        IO0CLR=0x000000ff;
        delay(1000);
        }
        if((IO1PIN & (1<<17)) ==0)
        {
        IO0SET=0x0000ff00;
        delay(500); //500msec delay
        IO0CLR=0x0000ff00;
        delay(500);
        }           
    }
}
void pll()                  //Fosc=12Mhz,CCLK=60Mhz,PCLK=60MHz
{
    PLL0CON=0x01;
    PLL0CFG=0x24;
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    while(!(PLL0STAT&(1<<10)));
    PLL0CON=0x03;
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    VPBDIV=0x01;
}
void delay(unsigned int z)
{
    T0CTCR=0x0;                                 //Select Timer Mode
    T0TCR=0x00;                 //Timer off
    T0PR=59999;                 //Prescaler value for 1ms
    T0TCR=0x02;                 //Timer reset
    T0TCR=0x01;                 //Timer ON
    while(T0TC<z);          
    T0TCR=0x00;                 //Timer OFF
    T0TC=0;                     //Clear the TC value. This is Optional.
}