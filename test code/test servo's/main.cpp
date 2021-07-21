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
        display << "\f\n\n Push button\n to loop\n between servo's";
        display << hwlib::flush;
        button.refresh();
        if(button.read()){
            display << "\f\n\nLooping...";
            display << hwlib::flush;
            servo1.set(166);
            hwlib::wait_ms(1000);
            servo1.set(150);
            hwlib::wait_ms(1500);
            
            servo2.set(45);
            hwlib::wait_ms(1000);
            servo2.set(180);
            hwlib::wait_ms(1500);
            
            servo3.set(45);
            hwlib::wait_ms(1000);
            servo3.set(135);
            hwlib::wait_ms(1500);
            
            servo4.set(45);
            hwlib::wait_ms(1000);
            servo4.set(135);
            hwlib::wait_ms(1500);
            
            servo5.set(45);
            hwlib::wait_ms(1000);
            servo5.set(135);
            hwlib::wait_ms(1500);
            
            servo6.set(45);
            hwlib::wait_ms(1000);
            servo6.set(135);
            hwlib::wait_ms(1500);
            
            servo7.set(45);
            hwlib::wait_ms(1000);
            servo7.set(135);
            hwlib::wait_ms(1500);
        }
    }
}