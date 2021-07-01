#include "hwlib.hpp"
#include "servo.hpp"

set_servo::set_servo(hwlib::pin_out & pin_servo):
    pin_servo(pin_servo)
{}

void set_servo::servo_close(bool close){
    int us;
    if(close){
        us = 2500; // close
    }else{
        us = 1000; // open
    }
    pin_servo.write(1);
    pin_servo.flush();
    hwlib::wait_us(us);
    pin_servo.write(0);
    pin_servo.flush();
    hwlib::wait_us(20000 - us);
}

void set_servo::servo_left(bool left){
    int us;
    if(left){
        us = 2000; // left
    }else{
        us = 1000; // right
    }
    pin_servo.write(1);
    pin_servo.flush();
    hwlib::wait_us(us);
    pin_servo.write(0);
    pin_servo.flush();
    hwlib::wait_us(20000 - us);
}

void set_servo::servo_open_and_close(float time){
    servo_close(false);
    hwlib::wait_ms(time);
    servo_close(true);
}

sort_system::sort_system(set_servo & servo1, set_servo & servo2, set_servo & servo3, set_servo & servo4, set_servo & servo5):
    servo1(servo1),
    servo2(servo2),
    servo3(servo3),
    servo4(servo4),
    servo5(servo5)
{}

void sort_system::set_red(){
    servo1.servo_left(false);
    servo3.servo_left(false);
}

void sort_system::set_orange(){
    servo1.servo_left(false);
    servo3.servo_left(true);
}

void sort_system::set_yellow(){
    servo1.servo_left(true);
    servo2.servo_left(false);
    servo4.servo_left(false);
}

void sort_system::set_green(){
    servo1.servo_left(true);
    servo2.servo_left(false);
    servo4.servo_left(true);
}

void sort_system::set_blue(){
    servo1.servo_left(true);
    servo2.servo_left(true);
    servo5.servo_left(false);
}

void sort_system::set_brown(){
    servo1.servo_left(true);
    servo2.servo_left(true);
    servo5.servo_left(true);
}

