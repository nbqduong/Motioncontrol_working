#include <MCX_Functions.h>

void reset_f()
{
   CSN_H;
   WRN_H;
   RDN_H;
   
   REG0=0x00ff; //reset MCX514
   REG1=0;
   REG6=0;
   REG7=0;
   REG3=0;
   REG2=0;
   REG4=0;
   REG5=0;
   
   wRP=0;
}

void initial_f()
{
   INT32 int_sp, drv_sp, pulse;
    int_sp=100;
    drv_sp=20000;
    
    wSV=int_sp; //SET START SPEED
    wDV=drv_sp; // Drive speed 2Kpps
    wAC=536870911; // Acceleration (maximum in specification)
    wJK= (4*(drv_sp-int_sp)/pow(5,2)); // Jerk 49750pps/sec2 
}

void SET_CMD_AXIS(INT CMD_AXIS, INT CMD_SET)
{
   CMD_SET = ((CMD_AXIS << 8)|CMD_SET);
   REG0 = (unsigned int16)CMD_SET;  
}

void SET_CMD( INT CMD_SET)
{
   CMD_SET = ((THIS_AXIS << 8)|CMD_SET);
   REG0 = (unsigned int16)CMD_SET;  
}

void set_direction( int8 dir )
{
   switch (dir)
   {
      case 1:  
         SET_CMD(0X52); // +pulse driving
         BREAK;
      
      
      case -1: 
         SET_CMD(0X53); // -pulse driving
         BREAK;
   }
}

void stop_f()
{
   SET_CMD(0X57); //STOP
}

void change_direction()
{
   reset_f();
   initial_f();
    
    
   // Relative position driving
   REG3= 0b0010100000001000;
   
   SET_DIRECTION(1); //, +pulse driving
   delay_ms(2000); 
   STOP_F(); //stop
   delay_us(100);
   SET_DIRECTION(-1); //axis Z, -pulse driving
   delay_ms(2000);
//!   
   STOP_F(); //stop
//!   delay_us(10000);
//!   REG0=0b1001010010; //axis Z, +pulse driving
//!   delay_ms(2000);
//!   
//!   REG0=0b1001010111; //stop
//!   delay_us(10000);
//!   REG0=0b1001010011; //axis Z, -pulse driving
//!   delay_ms(2000);
//!   
//!   REG0=0b1001010111; //stop
//!   delay_us(10000);
//!   REG0=0b1001010010; //axis Z, +pulse driving
   
}

void change_speed()
{
    
    INT32 int_sp, drv_sp, pulse;
    int_sp=100;
    drv_sp=5000;
    
    wSV=int_sp; //SET START SPEED
    wDV=drv_sp; // Drive speed 2Kpps
    wAC=536870911; // Acceleration (maximum in specification)
    wJK= (4*(drv_sp-int_sp)/pow(5,2)); // Jerk 49750pps/sec2 
    
    // Relative position driving
   REG3= 0b0010100000001000;
   
   
   
   SET_DIRECTION(1); //, +pulse driving
   
   delay_ms(2000);
   wDV=30000;
   
   delay_ms(2000);
   wDV=50000;

   delay_ms(2000);
   wDV=70000;
   
   delay_ms(2000);
   wDV=50000;

   delay_ms(2000);
   wDV=30000;
}


void home_search()
{

   RESET_F();
   INT32 int_sp, drv_sp;
    int_sp=100;
//!    drv_sp=10000;
    
    wSV=int_sp; //SET START SPEED
    wDV=drv_sp; // Drive speed 2Kpps
    wAC=536870911; // Acceleration (maximum in specification)
    wJK= (4*(drv_sp-int_sp)/pow(5,2)); // Jerk 49750pps/sec2 
    
    
   // Relative position driving
   REG3= 0b0010100000001000;
   
//!   REG0=0b1001010010; //axis Y, +pulse driving
   
         // WR2 Register setting
      SET_CMD(0X1F);  // Select y axis
      REG2= 0x0800;  // Home signal logical setting: XSTOP1: Low active
      // Enables hardware limit
      // Input signal filter mode setting
      REG6 = 0x0A04;  // D11~D8 1010 Filter delay: 512µsec
      // D2 1 XSTOP1 signal: Enables the filter
      SET_CMD(0X25);  // Writes a command
      // Automatic home search mode setting 1
      REG6 = 0x8037;  
         // D15 1 Step 4 execution/non-execution: Execution
         // D14 0 Step 3 LP clear Disable
         // D13 0 Step 3 RP clear Disable
         // D12 0 Step 3 DCC output: Disable
         // D11 0 Step 3 search direction: -
         // D10 0 Step 3 execution/non-execution: Non-execution
         // D9 0 Step 2 LP clear Disable
         // D8 0 Step 2 RP clear Disable
         // D7 0 Step 2 DCC output: Disable
         // D6 0 Step 2 detection signal: STOP1
         // D5 1 Step 2 search direction: -direction
         // D4 1 Step 2 execution/non-execution : Execution
         // D3,2 0,1 Step 1 detection signal: STOP1
         // D1 1 Step 1 search direction: -direction
         // D0 1 Step 1 execution/non-execution: Execution
      SET_CMD(0X23);; // Writes a command
      // Automatic home search mode setting 2
      REG6= 0X0000;  // D15 0
      // D14 0
      // D13 0
      // D12 0
      // D11 0
      // D10~8 0 Timer value
      // D7 0 Timer between steps Disable
      // D6~4 0 DCC pulse width
      // D3 0 DCC pulse logic
      // D2 0 At the termination of home search, LP clear Disable
      // D1 0 At the termination of home search, RP clear Disable
      // D0 0 Step 2&3 Disable
      SET_CMD(0X24);  // Writes a command
      // High-speed home search and low-speed home search setting
      REG6  =0X7318;  // Acceleration/deceleration:95,000 PPS/SEC
      REG7  =0X0001 ;
      SET_CMD(0X2);
      REG6  =20000 ; // Initial speed:1000 PPS
      REG7  =0X0000 ;
      SET_CMD(0X4);
      REG6  =0X4E20 ; // Speed of step 1 and 4:20000 PPS
      REG7  =0X0000 ;
      SET_CMD(0X5);
      REG6  =500 ; // Speed of step 2:500 PPS
      REG7  =0X0000 ;
      SET_CMD(0X14);
      // Offset pulse setting
      REG6  =100;  // Offset driving pulse count:3500
      REG7  =0X0000 ;
      SET_CMD(0X6);
      // Starts execution of automatic home search
      SET_CMD(0X5A);


   // remember to edit axis REG0
}

void change_speed2()
{
   INT32 int_sp, drv_sp, pulse;
    int_sp=100;
    drv_sp=10000;
    
    wSV=int_sp; //SET START SPEED
    wDV=drv_sp; // Drive speed 2Kpps
    wAC=536870911; // Acceleration (maximum in specification)
    wJK= (4*(drv_sp-int_sp)/pow(5,2)); // Jerk 49750pps/sec2 
    
    wIV=50000; //set increase speed
   
   REG3= 0b0010100000001000; // Relative position driving
   SET_CMD(0X52); //axis Y, +pulse driving
   
   delay_ms(5000);
   SET_CMD(0X70); //increase velocity
   
   delay_ms(5000);
   SET_CMD(0X70);//increase velocity

   delay_ms(5000);
   SET_CMD(0X71); //decrease velocity

   delay_ms(5000);
   SET_CMD(0X70); //increase velocity
   
   delay_ms(5000);
   SET_CMD(0X71); //decrease velocity
   
   delay_ms(5000);
   SET_CMD(0X70); //increase velocity
}

void test_functions(){
    
//!    REG3= 0b0010100000011100;  // Specifies S-curve acceleration/deceleration driving
    INT32 int_sp, drv_sp, pulse;
    int_sp=100;
    drv_sp=10000;
    
    //pulse=(1);
    
     //assign axis
    
    wSV=int_sp; //SET START SPEED
    wDV=drv_sp; // Drive speed 2Kpps
    wAC=536870911; // Acceleration (maximum in specification)
    wJK= (4*(drv_sp-int_sp)/pow(5,2)); // Jerk 49750pps/sec2 
    //wTP=pulse; //pulse number
//!    wLP=0; //logical position
//!    wRP=0;
    
   // Relative position driving
   REG3= 0b0010100000001000; 
   //REG0=0b001001010100;
}


void test_functions2(){
//!    REG3= 0b0010100000011100;  // Specifies S-curve acceleration/deceleration driving
    INT32 int_sp, drv_sp, pulse;
    int_sp=100;
    drv_sp=10000;
    
    pulse=50000;
    
     //assign axis
    
    wSV=int_sp; //SET START SPEED
    wDV=drv_sp; // Drive speed 2Kpps
    wAC=536870911; // Acceleration (maximum in specification)
    wJK= (4*(drv_sp-int_sp)/pow(5,2)); // Jerk 49750pps/sec2 
    wTP=pulse; //pulse number
    wLP=0; //logical position
    wRP=0;
    
   // Relative position driving
   REG3= 0b0010100000001000; 
   SET_CMD(0X54);
}

void read_encoder(){
   int32 RP;
   RP=rRP;
   wP1M=0b0101010101010101;
   
   unsigned int16 out;
   out = 0b10000000 << 8;
   
   
   if(RP>(1000)) 
   {
      out |= 0b1000 <<8;   //den dau tien
   }
   if(RP < 81000)
   {
      out |= 0b100 <<8; //den thu 2    
   }
//!   
   
   
   if(RP < (80300)) 
   {
      out |= 0b10 <<8; // den thu 3
   }
   REG4=out;
}

VOID FIX_PULSE(INT32 PULSE_DR)
{

//!    REG3= 0b0010100000011100;  // Specifies S-curve acceleration/deceleration driving
    INT32 int_sp, drv_sp, pulse;
    int_sp=100;
    drv_sp=10000;
    
    pulse=PULSE_DR;
    
     //assign axis
    
    wSV=int_sp; //SET START SPEED
    wDV=drv_sp; // Drive speed 2Kpps
    wAC=536870911; // Acceleration (maximum in specification)
    wJK= (4*(drv_sp-int_sp)/pow(5,2)); // Jerk 49750pps/sec2 
    wTP=pulse; //pulse number
    wLP=0; //logical position
    wRP=0;
    
   // Relative position driving
   REG3= 0b0010100000001000; 
   SET_CMD(0X54);
}

void home_search0()
{
   INT32 int_sp, drv_sp, pulse;
    int_sp=100;
//!    drv_sp=10000;
    
    wSV=int_sp; //SET START SPEED
    wDV=drv_sp; // Drive speed 2Kpps
    wAC=536870911; // Acceleration (maximum in specification)
    wJK= (4*(drv_sp-int_sp)/pow(5,2)); // Jerk 49750pps/sec2 
    
    
   // Relative position driving
   REG3= 0b0010100000001000;
   
//!   REG0=0b1001010010; //axis Y, +pulse driving
   
         // WR2 Register setting
      REG0= 0x041F;  // Select y axis
      REG2= 0x0800;  // Home signal logical setting: XSTOP1: Low active
      // Enables hardware limit
      // Input signal filter mode setting
      REG6 = 0x0A04;  // D11~D8 1010 Filter delay: 512µsec
      // D2 1 XSTOP1 signal: Enables the filter
      REG0=  0x0425;  // Writes a command
      // Automatic home search mode setting 1
      REG6 = 0x8037;  
         // D15 1 Step 4 execution/non-execution: Execution
         // D14 0 Step 3 LP clear Disable
         // D13 0 Step 3 RP clear Disable
         // D12 0 Step 3 DCC output: Disable
         // D11 0 Step 3 search direction: -
         // D10 0 Step 3 execution/non-execution: Non-execution
         // D9 0 Step 2 LP clear Disable
         // D8 0 Step 2 RP clear Disable
         // D7 0 Step 2 DCC output: Disable
         // D6 0 Step 2 detection signal: STOP1
         // D5 1 Step 2 search direction: -direction
         // D4 1 Step 2 execution/non-execution : Execution
         // D3,2 0,1 Step 1 detection signal: STOP1
         // D1 1 Step 1 search direction: -direction
         // D0 1 Step 1 execution/non-execution: Execution
      REG0 = 0X0423; // Writes a command
      // Automatic home search mode setting 2
      REG6= 0X0000;  // D15 0
      // D14 0
      // D13 0
      // D12 0
      // D11 0
      // D10~8 0 Timer value
      // D7 0 Timer between steps Disable
      // D6~4 0 DCC pulse width
      // D3 0 DCC pulse logic
      // D2 0 At the termination of home search, LP clear Disable
      // D1 0 At the termination of home search, RP clear Disable
      // D0 0 Step 2&3 Disable
      REG0  =0X0424;  // Writes a command
      // High-speed home search and low-speed home search setting
      REG6  =0X7318;  // Acceleration/deceleration:95,000 PPS/SEC
      REG7  =0X0001 ;
      REG0  =0X0402 ;
      REG6  =1000 ; // Initial speed:1000 PPS
      REG7  =0X0000 ;
      REG0  =0X0404 ;
      REG6  =0X4E20 ; // Speed of step 1 and 4:20000 PPS
      REG7  =0X0000 ;
      REG0  =0X0405 ;
      REG6  =500 ; // Speed of step 2:500 PPS
      REG7  =0X0000 ;
      REG0  =0X0414 ;
      // Offset pulse setting
      REG6  =100;  // Offset driving pulse count:3500
      REG7  =0X0000 ;
      REG0  =0X0406 ;
      // Starts execution of automatic home search
      REG0  =0X045A ;


   // remember to edit axis REG0
}
