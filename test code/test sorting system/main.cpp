#include "hwlib.hpp"
#include "servo.hpp"

int main( void ){
    WDT->WDT_MR = WDT_MR_WDDIS;
    
    namespace target = hwlib::target;
    auto scl_oled     = target::pin_oc(target::pins::d18);
    auto sda_oled     = target::pin_oc(target::pins::d17);
    auto i2c_bus_oled = hwlib::i2c_bus_bit_banged_scl_sda(scl_oled, sda_oled);
    auto oled    = hwlib::glcd_oled(i2c_bus_oled, 0x3c); 
    auto font    = hwlib::font_default_8x8();
    auto display = hwlib::terminal_from(oled, font);

    display << "\f\n\nLoading...";
    display << hwlib::flush;
    
    auto servo_pin1 = target::pin_out(target::pins::d14);
    auto servo_pin2 = target::pin_out(target::pins::d15);
    auto servo_pin3 = target::pin_out(target::pins::d3);
    auto servo_pin4 = target::pin_out(target::pins::d4);
    auto servo_pin5 = target::pin_out(target::pins::d5);
    auto servo_pin6 = target::pin_out(target::pins::d6);
    auto servo_pin7 = target::pin_out(target::pins::d7);
    set_servo servo1(servo_pin1); 
    set_servo servo2(servo_pin2);
    set_servo servo3(servo_pin3);
    set_servo servo4(servo_pin4);
    set_servo servo5(servo_pin5);
    set_servo servo6(servo_pin6);
    set_servo servo7(servo_pin7);
    sort_system sort(servo3, servo4, servo5, servo6, servo7);
    
    auto button = target::pin_in(target::pins::d8); // safety button if something is wrong
    
    while(1){
        display << "\f\n\n Push button\n to loop the\n sorting sytem";
        display << hwlib::flush;
        button.refresh();
        if(button.read()){
            display << "\f\n\n\n      Red";
            display << hwlib::flush;
            sort.set_red();
            hwlib::wait_ms(1500);
            
            display << "\f\n\n\n     Orange";
            display << hwlib::flush;
            sort.set_orange();
            hwlib::wait_ms(1500);
            
            display << "\f\n\n\n     Yellow";
            display << hwlib::flush;
            sort.set_yellow();
            hwlib::wait_ms(1500);
            
            display << "\f\n\n\n     Green";
            display << hwlib::flush;
            sort.set_green();
            hwlib::wait_ms(1500);
            
            display << "\f\n\n\n      Blue";
            display << hwlib::flush;
            sort.set_blue();
            hwlib::wait_ms(1500);
            
            display << "\f\n\n\n     Brown";
            display << hwlib::flush;
            sort.set_brown();
            hwlib::wait_ms(1500);
        }
    }
}