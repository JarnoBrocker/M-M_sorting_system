#ifndef colors_HPP
#define colors_HPP

#include "hwlib.hpp"
#include "servo.hpp"

class set_color{
protected:
    uint16_t c;
    uint16_t r;
    uint16_t g;
    uint16_t b;
    
public:
    set_color(uint16_t c = 0, uint16_t r = 0, uint16_t g = 0, uint16_t b = 0);
    uint16_t clear();
    uint16_t red();
    uint16_t green();
    uint16_t blue();
//    void set_RGB(hwlib::target::pin_in button, set_servo servo1, set_servo servo2);
};

//class set_colors{
//private:
//    set_color red;
//    set_color orange;
//    set_color yellow;
//    set_color green;
//    set_color blue;
//    set_color brown;
//    
//public:
//    set_colors();
//    void set_colors(hwlib::terminal_from display, hwlib::target::pin_in button, set_servo servo1, set_servo servo2);
//};

#endif // colors_HPP