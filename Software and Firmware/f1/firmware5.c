#include <firmware5.h>
//!#include "MCU_USB.c"
#include "MCX_functions.c"
/* TODO: Use usb_put_packet() to transmit data to USB HID,
using USB_HID_ENDPONT for the endpoint and the payload size
needs to match USB_CONFIG_HID_TX_SIZE. Use usb_get_packet()
to read incomming data, using USB_HID_ENDPOINT for the
endpoint. usb_enumerated() can be used to see if connected to
a host and ready to communicate. */


void main()
{
//!   delay_ms(2000);
   
   reset_f();
   SET_AXIS(AXIS_Y);
//!   delay_ms(3000);
//!   change_direction();
   
   change_speed();
//!    home_search();
//!   home_search0();
//!   change_speed2();
//!   test_functions2();
//!   FIX_PULSE(27500); //2 VÒNG
//!  REG0=0x52;
//!  int32 RP;
//!   test_functions();
   
//!   while(TRUE)
//!   {
//!       
//!      //TODO: User Code
//!      RP=rRP;
//!      if(RP > 80000) 
//!   {
//!      REG0=0b1001010111;//axis Y, cmd 57
//!   } else 
//!   REG0=0b1001010010; //axis Y, +pulse driving
//!   delay_ms(5000);

//!
//!   delay_ms(5000);
//!   test_functions();
//!      
//!      read_encoder();
//!
//!   }

}
//!      REG0=0b1001010011; //axis Y, -pulse driving
//!   REG0=0b1001010010; //axis Y, +pulse driving


