#include "hwlib.hpp"
#include "colors.hpp"
#include "servo.hpp"

set_color::set_color(uint16_t c, uint16_t r, uint16_t g, uint16_t b):
    c(c),
    r(r),
    g(g),
    b(b)
{}

uint16_t set_color::clear(){
    return c;
}

uint16_t set_color::red(){
    return r;
}

uint16_t set_color::green(){
    return g;
}

uint16_t set_color::blue(){
    return b;
}

//void set_color::set_RGB(hwlib::target::pin_in button, set_servo servo1, set_servo servo2){
//    auto tmp_c = color.get_data_clear();
//    auto tmp_r = color.get_data_red();
//    auto tmp_g = color.get_data_green();
//    auto tmp_b = color.get_data_blue();
//    button.refresh();
//    int i = 0;
//    while(not button.read()){
//        tmp_c = color.get_data_clear();
//        tmp_r = color.get_data_red();
//        tmp_g = color.get_data_green();
//        tmp_b = color.get_data_blue();
//        
//        if(i <= 20){
//            servo1.set(180);
//            hwlib::wait_ms(1000);
//            servo1.set(160);
//            i = 0;
//        }
//        
//        button.refresh();
//    }
//    
//    c = tmp_c;
//    r = tmp_r;
//    g = tmp_g;
//    b = tmp_b;
//    
//    servo2.set(45);
//    hwlib::wait_ms(500);
//    servo2.set(180);
//}


//set_colors::set_colors():
//    
//{}

//void set_colors::set_colors(hwlib::terminal_from display, hwlib::target::pin_in button, set_servo servo1, set_servo servo2){
//    display << "\n\n\t Red";
//    display << hwlib:flush;
//    red.set_RGB(button, servo1, servo2);
//    
////    orange.set_RGB;
////    yellow.set_RGB;
////    green.set_RGB;
////    blue.set_RGB;
////    brown.set_RGB;
//}