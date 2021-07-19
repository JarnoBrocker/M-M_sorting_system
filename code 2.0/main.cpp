#include "hwlib.hpp"
#include "color_sensor.hpp"
#include "servo.hpp"
#include "colors.hpp"

int main( void ){
    WDT->WDT_MR = WDT_MR_WDDIS; // Kill watchdog
    
    namespace target = hwlib::target;
    auto scl     = target::pin_oc(target::pins::scl); // Color sensor pins
    auto sda     = target::pin_oc(target::pins::sda);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    auto INT     = target::pin_out(target::pins::d19);
    auto color   = color_sensor(i2c_bus);
    
    auto scl_oled     = target::pin_oc(target::pins::d18); // Oled pins
    auto sda_oled     = target::pin_oc(target::pins::d17);
    auto i2c_bus_oled = hwlib::i2c_bus_bit_banged_scl_sda(scl_oled, sda_oled);
    auto oled    = hwlib::glcd_oled(i2c_bus_oled, 0x3c); 
    auto font    = hwlib::font_default_8x8();
    auto display = hwlib::terminal_from(oled, font);

    display << "\f\n\nLoading..."; // Display 'Loading...' while seting everything up.
    display << hwlib::flush;
    
    auto servo_pin1 = target::pin_out(target::pins::d14); // Servo pins and class constructing.
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
    
    auto button = target::pin_in(target::pins::d8);
    
//    while(1){
    
//        servo1.set(160);
//        display << "\f\n\nin";
//        display << hwlib::flush;
//        hwlib::wait_ms(2000);
//        servo1.set(180);
//        display << "\f\n\nout";
//        display << hwlib::flush;
//        hwlib::wait_ms(2000);


//        sort.set_red();
//        display << "\f\n\nRed";
//        display << hwlib::flush;
//        hwlib::wait_ms(1000);
//        sort.set_orange();
//        display << "\f\n\nOrange";
//        display << hwlib::flush;
//        hwlib::wait_ms(1000);
//        sort.set_yellow();
//        display << "\f\n\nYellow";
//        display << hwlib::flush;
//        hwlib::wait_ms(1000);
//        sort.set_green();
//        display << "\f\n\nGreen";
//        display << hwlib::flush;
//        hwlib::wait_ms(1000);
//        sort.set_blue();
//        display << "\f\n\nBlue";
//        display << hwlib::flush;
//        hwlib::wait_ms(1000);
//        sort.set_brown();
//        display << "\f\n\nBrown";
//        display << hwlib::flush;
//        hwlib::wait_ms(1000);

//
//        servo5.set(135);
//        servo4.set(135);
//        servo6.set(135);
//        servo3.set(135);
//        servo7.set(135);
//        hwlib::wait_ms(1000);
//        servo5.set(45);
//        hwlib::wait_ms(100);
//        servo4.set(45);
//        servo6.set(45);
//        servo3.set(45);
//        servo7.set(45);
//        hwlib::wait_ms(1000);


        
//    }
    
    servo1.set(160); // 
    servo2.set(45); // Open and close the servo after the color sensor so there are no m&m's in the color recognition.
    hwlib::wait_ms(1000);
    servo2.set(180);
    hwlib::wait_ms(100);

    while(not color.SetUp()){ // SetUp of the color sensor
        display << "\f\n\nERROR SetUp!";
        display << hwlib::flush;
    }
    
    uint16_t clear_re; uint16_t red_re; uint16_t green_re; uint16_t blue_re;
    uint16_t clear_or; uint16_t red_or; uint16_t green_or; uint16_t blue_or;
    uint16_t clear_ye; uint16_t red_ye; uint16_t green_ye; uint16_t blue_ye;
    uint16_t clear_gr; uint16_t red_gr; uint16_t green_gr; uint16_t blue_gr;
    uint16_t clear_bl; uint16_t red_bl; uint16_t green_bl; uint16_t blue_bl;
    uint16_t clear_br; uint16_t red_br; uint16_t green_br; uint16_t blue_br;
    uint16_t clear_n;  uint16_t red_n;  uint16_t green_n;  uint16_t blue_n;
    
    int loop = 0;
    int i = 0;
    while(i < 7){
        auto tmp_clear = color.get_data_clear(); // Get the RGB value
        auto tmp_red   = color.get_data_red();
        auto tmp_green = color.get_data_green();
        auto tmp_blue  = color.get_data_blue(); 

        while(tmp_clear == 0 and tmp_red == 0 and tmp_green == 0 and tmp_blue == 0){ // If all the values are 0, there is probably a cable loose.
            display << "\f\n\nERROR 2!";
            display << hwlib::flush;
            hwlib::wait_ms(100);
            tmp_clear = color.get_data_clear();
            tmp_red   = color.get_data_red();
            tmp_green = color.get_data_green();
            tmp_blue  = color.get_data_blue();
        }   
        
        display << "\f\n\n"; // display the RGB values (mainly for testing)
        display << hwlib::dec << tmp_clear << "\n";
        display << hwlib::dec << tmp_red << "\n";
        display << hwlib::dec << tmp_green << "\n";
        display << hwlib::dec << tmp_blue << "\n\n";
        if(i == 0){ // If statement for adding the color (or 'No color yet') to the display.
            display << "Red";
        }else if(i == 1){
            display << "Orange";
        }else if(i == 2){
            display << "Yellow";
        }else if(i == 3){
            display << "Green";
        }else if(i == 4){
            display << "Blue";
        }else if(i == 5){
            display << "Brown";
        }else if(i == 6){
            display << "Nothing";
        }
        display << hwlib::flush;
        
        button.refresh();
        if(button.read()){
            if(i == 0){ // If statement for adding the color (or 'No color yet') to the display.
                clear_re = tmp_clear;
                red_re = tmp_red;
                green_re = tmp_green;
                blue_re = tmp_blue;
                sort.set_red();
            }else if(i == 1){
                clear_or = tmp_clear;
                red_or = tmp_red;
                green_or = tmp_green;
                blue_or = tmp_blue;
                sort.set_orange();
            }else if(i == 2){
                clear_ye = tmp_clear;
                red_ye = tmp_red;
                green_ye = tmp_green;
                blue_ye = tmp_blue;
                sort.set_yellow();
            }else if(i == 3){
                clear_gr = tmp_clear;
                red_gr = tmp_red;
                green_gr = tmp_green;
                blue_gr = tmp_blue;
                sort.set_green();
            }else if(i == 4){
                clear_bl = tmp_clear;
                red_bl = tmp_red;
                green_bl = tmp_green;
                blue_bl = tmp_blue;
                sort.set_blue();
            }else if(i == 5){
                clear_br = tmp_clear;
                red_br = tmp_red;
                green_br = tmp_green;
                blue_br = tmp_blue;
                sort.set_brown();
            }else if(i == 6){
                clear_n = tmp_clear;
                red_n = tmp_red;
                green_n = tmp_green;
                blue_n = tmp_blue;
            }
            i++;
            servo2.set(45);
            hwlib::wait_ms(1000);
            servo2.set(180);
        }
        
        if(loop >= 20){ // Open and close the upper servo so the next m&m goes.
            servo1.set(180);
            hwlib::wait_ms(1000);
            servo1.set(160);
            loop = 0;
        }
        loop++;
    }
    set_color red(clear_re, red_re, green_re, blue_re);
    set_color orange(clear_or, red_or, green_or, blue_or);
    set_color yellow(clear_ye, red_ye, green_ye, blue_ye);
    set_color green(clear_gr, red_gr, green_gr, blue_gr);
    set_color blue(clear_bl, red_bl, green_bl, blue_bl);
    set_color brown(clear_br, red_br, green_br, blue_br);
    set_color nothing(clear_n, red_n, green_n, blue_n);
    
    display << "\f\n\nDone";
    display << hwlib::flush;
    hwlib::wait_ms(2000);
    
    loop = 0; // A loop variable for opening and closing for the servo above the color recognition.
    bool wait; // Variable for waiting after a color is recognized.
    i = 6; // 6 stands for 'No color yet'.
    while(1){ // A never ending loop
        loop++;
        wait = true;
       
        auto tmp_clear = color.get_data_clear(); // Get the RGB value
        auto tmp_red   = color.get_data_red();
        auto tmp_green = color.get_data_green();
        auto tmp_blue  = color.get_data_blue(); 

        while(tmp_clear == 0 and tmp_red == 0 and tmp_green == 0 and tmp_blue == 0){ // If all the values are 0, there is probably a cable loose.
            display << "\f\n\nERROR 2!";
            display << hwlib::flush;
            hwlib::wait_ms(100);
            tmp_clear = color.get_data_clear();
            tmp_red   = color.get_data_red();
            tmp_green = color.get_data_green();
            tmp_blue  = color.get_data_blue();
        }   
        
        display << "\f\n\n"; // display the RGB values (mainly for testing)
        display << hwlib::dec << tmp_clear << "\n";
        display << hwlib::dec << tmp_red << "\n";
        display << hwlib::dec << tmp_green << "\n";
        display << hwlib::dec << tmp_blue << "\n\n";

        if(tmp_clear > (((nothing.clear() + brown.clear()) / 2) + 100)){                                                 // The values of the RGB are compared with the values of the used colors
            if((tmp_red > (blue.red() - 50) and tmp_red < (blue.red() + 50)) and (tmp_green > (blue.green() - 50) and tmp_green < (blue.green() + 50)) and (tmp_blue > (blue.blue() - 50) and tmp_blue < (blue.blue() + 50)) and (tmp_clear < (blue.clear() + 100) and tmp_clear > (blue.clear() - 100))){ // Blue
                i = 0; // For displaying blue
                sort.set_blue(); // Sorting system to blue
                servo2.set(45);
                hwlib::wait_ms(500);
                servo2.set(180);
            }else if((tmp_red > (green.red() - 50) and tmp_red < (green.red() + 50)) and (tmp_green > (green.green() - 50) and tmp_green < (green.green() + 50)) and (tmp_blue > (green.blue() - 50) and tmp_blue < (green.blue() + 50)) and (tmp_clear < (green.clear() + 100) and tmp_clear > (green.clear() - 100))){ // Green
                i = 1;
                sort.set_green();
                servo2.set(45);
                hwlib::wait_ms(500);
                servo2.set(180);
            }else if((tmp_red > (orange.red() - 50) and tmp_red < (orange.red() + 50)) and (tmp_green > (orange.green() - 50) and tmp_green < (orange.green() + 50)) and (tmp_blue > (orange.blue() - 50) and tmp_blue < (orange.blue() + 50)) and (tmp_clear < (orange.clear() + 100) and tmp_clear > (orange.clear() - 100))){ // Orange
                i = 2;
                sort.set_orange();
                servo2.set(45);
                hwlib::wait_ms(500);
                servo2.set(180); 
            }else if((tmp_red > (red.red() - 50) and tmp_red < (red.red() + 50)) and (tmp_green > (red.green() - 50) and tmp_green < (red.green() + 50)) and (tmp_blue > (red.blue() - 50) and tmp_blue < (red.blue() + 50)) and (tmp_clear < (red.clear() + 100) and tmp_clear > (red.clear() - 100))){ // Red
                i = 3;
                sort.set_red();
                servo2.set(45);
                hwlib::wait_ms(500);
                servo2.set(180);
            }else if((tmp_red > (yellow.red() - 100) and tmp_red < (yellow.red() + 200)) and (tmp_green > (yellow.green() - 100) and tmp_green < (yellow.green() + 200)) and (tmp_clear < (yellow.clear() + 100) and tmp_clear > (yellow.clear() - 100))){ // Yellow
                i = 4;
                sort.set_yellow();
                servo2.set(45);
                hwlib::wait_ms(500);
                servo2.set(180);
            }else if((tmp_red < (brown.red() + 100)) and (tmp_green < (brown.green() + 100)) and (tmp_blue < (brown.blue() + 100)) and (tmp_clear < (brown.clear() + 100) and tmp_clear > (brown.clear() - 100))){ // Brown
                i = 5;
                sort.set_brown();
                servo2.set(45);
                hwlib::wait_ms(500);
                servo2.set(180);
            }else{
                wait = false; // If no color is recognized, there is no need to wait
            }
        }else{
                wait = false; // If no color is recognized, there is no need to wait
        }
        
        if(i == 0){ // If statement for adding the color (or 'No color yet') to the display.
            display << "Blue";
        }else if(i == 1){
            display << "Green";
        }else if(i == 2){
            display << "Orange";
        }else if(i == 3){
            display << "Red";
        }else if(i == 4){
            display << "Yellow";
        }else if(i == 5){
            display << "Brown";
        }else if(i == 6){
            display << "No color yet";
        }
        display << hwlib::flush; 
        
        if(wait){ // Wait if color is recognized.
            loop = 20;
            hwlib::wait_ms(1000);
        }
        
        if(loop >= 20){ // Open and close the upper servo so the next m&m goes.
            servo1.set(180);
            hwlib::wait_ms(1000);
            servo1.set(160);
            loop = 0;
        }
        
        button.refresh();
        if(button.read()){
            servo2.set(45);
            hwlib::wait_ms(500);
            servo2.set(180);
        }
    }
}