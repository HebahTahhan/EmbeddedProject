#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

void myDelay(void);
void PLLinit(void);
void ATD0init(void);
unsigned char readATD0(unsigned char channel);
void servo0_init(void);
void servo0_angle(unsigned int);
void servo1_init(void);
void servo1_angle(unsigned int);
void servo2_init(void);
void servo2_angle(unsigned int);
//void servo3_init(void);
//void servo3_angle(unsigned int);

void main(void) {
  /* put your own code here */
  unsigned char reading1,reading2,reading3;
  DDRH=0xFF;
  DDRP=0xFF;
    
  PLLinit();
  ATD0init();
  
  

	EnableInterrupts;

  servo0_init();
  servo1_init();
  servo2_init();
  //servo3_init();

  
  for(;;) {
  
      reading1= readATD0(0); // read the POT connected to ch 0  
      reading2= readATD0(2); // read the POT connected to ch 2  
      reading3= readATD0(3); // read the POT connected to ch 2 
      //reading4= readATD0(4); // read the POT connected to ch 2 
       
      if(reading1<30){
               servo0_angle(5000); 
               
      } 
      
      else{
                     servo0_angle(1000); 

        
      }   
      
      
      if(reading2<15){
              servo1_angle(15000);
                                     
 
               
      } 
      
      
      else{
                     servo1_angle(27000);

                     
      }  
      
      
      
      
      
      
        
      if(reading3<100){
               servo2_angle(20000);
                                     
 
               
      } else{
                   servo2_angle(40000);

                     PTP=0x10;
      }  
      


     // if(reading4<140){
       //        servo3_angle(4000);
                                     
 
               
     // } else{
       //            servo3_angle(5000);

         //            PTP=0x40;
      //}  
      



    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}

void PLLinit(void){
  SYNR = 5;
  REFDV = 1; // 48Mhz with an 8MHz OSc
  PLLCTL = 0x60;//ON Auto 
  while(!(CRGFLG & 0x08));
  CLKSEL = CLKSEL | 0x80;//select PLL
  

}



void myDelay(void){
  unsigned char i;
  unsigned int j;
  for(i=0;i<150;i++){
    for(j=0;j<20000;j++){
      i=i;
      j=j;
    
    }
  
  }
 
 }
 
void ATD0init(void){
  ATD0CTL2 = 0xc0; //Power up, Fast Flag clear
  myDelay();
  ATD0CTL3 = 0x08;// 1 conversion, non FIFO
  ATD0CTL4 = 0x85;//8-bit, 2MHz ATD clk, 2 clks for the 2nd phase

}
unsigned char readATD0(unsigned char channel){
 ATD0CTL5 = 0x80 | channel; //right justify, single conversion across one channel
 while(!(ATD0STAT0 & 0x80));
 return(ATD0DR0L);

}


////servo0 fingure1
void servo0_init(void){
  PWMCLK|=0x00; // select A Clock
  PWMPRCLK |=0x04; // prescale A by 16, 1.5MHz --> 0.66uS per increment
  PWMCTL |=0x1C; //concatinate PWM0:PWM1, and stop PWM in wait and freeze modes
  PWMPOL |=0x02; // set 1 polarity (start high then go low)
  // period 20 ms = 30000 * 0.666uS
  PWMPER0=24000>>8; //highest 8 bit of the Period
  PWMPER1=24000 & 0x00FF; // lowest 8 bit of the period
  
    
  // start with the servo pointing 0 degrees
  PWMDTY0=1000>>8; // highest 8 bit of the duty
  PWMDTY1= 1000 & 0x00FF; //lowest 8 bit of the duty
  
  PWME |=0x02; // enable PWM1


}

void servo0_angle(unsigned int myAngle){

  PWMDTY0 =myAngle>>8; // highest 8 bit of the duty
  PWMDTY1 = myAngle & 0x00FF; //lowest 8 bit of the


}

  //////servo2 fingure2
 void servo1_init(void) {
  PWMCLK |= 0x40; // Select B Clock for PWM3
  PWMPRCLK |= 0x08; // Prescale B by 16, 1.5MHz --> 0.66uS per increment
  PWMCTL |= 0x2C; // Concatenate PWM2:PWM3, and stop PWM in wait and freeze modes
  PWMPOL |= 0x08; // Set polarity of PWM3 (start high then go low)
  PWMPER2 = 30000 >> 8; // Highest 8 bits of the Period for PWM2
  PWMPER3 = 30000 & 0x00FF; // Lowest 8 bits of the period for PWM3
  PWMDTY2 = 2000 >> 8; // Highest 8 bits of the duty for PWM2
  PWMDTY3 = 2000 & 0x00FF; // Lowest 8 bits of the duty for PWM3
  PWME |= 0x08; // Enable PWM3
}

void servo1_angle(unsigned int myAngle) {
  PWMDTY2 = (myAngle >> 8); // Highest 8 bits of the duty for PWM2
  PWMDTY3 = (myAngle & 0x00FF); // Lowest 8 bits of the duty for PWM3
}




 //////servo2 fingure3
 void servo2_init(void) {
  PWMCLK |= 0x00; // Select A Clock for PWM5
  PWMPRCLK |= 0x04; // Prescale A by 16, 1.5MHz --> 0.66uS per increment
  PWMCTL |= 0x4C; // Concatenate PWM4:PWM5, and stop PWM in wait and freeze modes
  PWMPOL |= 0x20; // Set polarity of PWM5 (start high then go low)
  PWMPER4 = 30000 >> 8; // Highest 8 bits of the Period for PWM2
  PWMPER5 = 30000 & 0x00FF; // Lowest 8 bits of the period for PWM3
  PWMDTY4 = 2000 >> 8; // Highest 8 bits of the duty for PWM2
  PWMDTY5 = 2000 & 0x00FF; // Lowest 8 bits of the duty for PWM3
  PWME |= 0x20; // Enable PWM5
}

void servo2_angle(unsigned int myAngle) {
  PWMDTY4 = (myAngle >> 8); // Highest 8 bits of the duty for PWM2
  PWMDTY5 = (myAngle & 0x00FF); // Lowest 8 bits of the duty for PWM3
}


 //////servo3 fingure4
// void servo3_init(void) {
  //PWMCLK |= 0x00; // Select B Clock for PWM7
  //PWMPRCLK |= 0x40; // Prescale A by 16, 1.5MHz --> 0.66uS per increment
  //PWMCTL |= 0x8C; // Concatenate PWM6:PWM7, and stop PWM in wait and freeze modes
  //PWMPOL |= 0x80; // Set polarity of PWM7 (start high then go low)
  //PWMPER4 = 30000 >> 8; // Highest 8 bits of the Period for PWM6
  //PWMPER5 = 30000 & 0x00FF; // Lowest 8 bits of the period for PWM7
  //PWMDTY5 = 2000 >> 8; // Highest 8 bits of the duty for PWM6
  //PWMDTY6 = 2000 & 0x00FF; // Lowest 8 bits of the duty for PWM7
  //PWME |= 0x80; // Enable PWM7
//}

//void servo3_angle(unsigned int myAngle) {
  //PWMDTY5 = (myAngle >> 8); // Highest 8 bits of the duty for PWM2
  //PWMDTY6 = (myAngle & 0x00FF); // Lowest 8 bits of the duty for PWM3
//}