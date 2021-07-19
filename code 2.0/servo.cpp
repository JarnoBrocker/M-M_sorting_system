#include "hwlib.hpp"
#include "servo.hpp"

set_servo::set_servo(hwlib::pin_out & pin_servo):
    pin_servo(pin_servo)
{}

void set_servo::set(int angle){
    if(angle < 0){
        angle = 0;
    }else if(angle > 180){
        angle = 180;
    }
    float tmp = angle;
    int us = 500 + ((tmp/180) * 2000);
    pin_servo.write(1);
    pin_servo.flush();
    hwlib::wait_us(us);
    pin_servo.write(0);
    pin_servo.flush();
    hwlib::wait_ms(20);
}

sort_system::sort_system(set_servo & servo1, set_servo & servo2, set_servo & servo3, set_servo & servo4, set_servo & servo5):
    servo1(servo1),
    servo2(servo2),
    servo3(servo3),
    servo4(servo4),
    servo5(servo5)
{}

void sort_system::set_red(){
    servo1.set(45);
    hwlib::wait_ms(50);
    servo3.set(45);
}

void sort_system::set_orange(){
    servo1.set(45);
    hwlib::wait_ms(50);
    servo3.set(135);
}

void sort_system::set_yellow(){
    servo1.set(135);
    hwlib::wait_ms(50);
    servo2.set(45);
    hwlib::wait_ms(50);
    servo4.set(45);
}

void sort_system::set_green(){
    servo1.set(135);
    hwlib::wait_ms(50);
    servo2.set(45);
    hwlib::wait_ms(50);
    servo4.set(135);
}

void sort_system::set_blue(){
    servo1.set(135);
    hwlib::wait_ms(50);
    servo2.set(135);
    hwlib::wait_ms(50);
    servo5.set(45);
}

void sort_system::set_brown(){
    servo1.set(135);
    hwlib::wait_ms(50);
    servo2.set(135);
    hwlib::wait_ms(50);
    servo5.set(135);
}

