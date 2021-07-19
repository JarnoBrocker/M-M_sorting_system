#include "hwlib.hpp"
#include "color_sensor.hpp"
#include "servo.hpp"

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
    
    
    uint16_t clear_re;
    uint16_t red_re;
    uint16_t green_re;
    uint16_t blue_re;
    
    uint16_t clear_or;
    uint16_t red_or;
    uint16_t green_or;
    uint16_t blue_or;
    
    uint16_t clear_ye;
    uint16_t red_ye;
    uint16_t green_ye;
    uint16_t blue_ye;
    
    uint16_t clear_gr;
    uint16_t red_gr;
    uint16_t green_gr;
    uint16_t blue_gr;
    
    uint16_t clear_bl;
    uint16_t red_bl;
    uint16_t green_bl;
    uint16_t blue_bl;
    
    uint16_t clear_br;
    uint16_t red_br;
    uint16_t green_br;
    uint16_t blue_br;
    
    uint16_t clear_n;
    uint16_t red_n;
    uint16_t green_n;
    uint16_t blue_n;
    
    
    servo1.set(160); // 
    servo2.set(45); // Open and close the servo after the color sensor so there are no m&m's in the color recognition.
    hwlib::wait_ms(1000);
    servo2.set(180);
    hwlib::wait_ms(100);

    while(not color.SetUp()){ // SetUp of the color sensor
        display << "\f\n\nERROR SetUp!";
        display << hwlib::flush;
    }
    
    int i = 0;
    while(i < 7){
        auto clear = color.get_data_clear(); // Get the RGB value
        auto red   = color.get_data_red();
        auto green = color.get_data_green();
        auto blue  = color.get_data_blue(); 

        while(clear == 0 and red == 0 and green == 0 and blue == 0){ // If all the values are 0, there is probably a cable loose.
            display << "\f\n\nERROR 2!";
            display << hwlib::flush;
            hwlib::wait_ms(100);
            clear = color.get_data_clear();
            red   = color.get_data_red();
            green = color.get_data_green();
            blue  = color.get_data_blue();
        }   
        
        display << "\f\n\n"; // display the RGB values (mainly for testing)
        display << hwlib::dec << clear << "\n";
        display << hwlib::dec << red << "\n";
        display << hwlib::dec << green << "\n";
        display << hwlib::dec << blue << "\n\n";
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
            display << "Nothing";
        }
        display << hwlib::flush;
        
        button.refresh();
        if(button.read()){
            if(i == 0){ // If statement for adding the color (or 'No color yet') to the display.
                clear_bl = clear;
                red_bl = red;
                green_bl = green;
                blue_bl = blue;
            }else if(i == 1){
                clear_gr = clear;
                red_gr = red;
                green_gr = green;
                blue_gr = blue;
            }else if(i == 2){
                clear_or = clear;
                red_or = red;
                green_or = green;
                blue_or = blue;
            }else if(i == 3){
                clear_re = clear;
                red_re = red;
                green_re = green;
                blue_re = blue;
            }else if(i == 4){
                clear_ye = clear;
                red_ye = red;
                green_ye = green;
                blue_ye = blue;
            }else if(i == 5){
                clear_br = clear;
                red_br = red;
                green_br = green;
                blue_br = blue;
            }else if(i == 6){
                clear_n = clear;
                red_n = red;
                green_n = green;
                blue_n = blue;
            }
            i++;
            servo2.set(45);
            hwlib::wait_ms(1000);
            servo2.set(180);
        }
    }
    display << "\f\n\nDone";
    display << hwlib::flush;
    
    hwlib::cout << "\n"; 
    hwlib::cout << "Red:" << "\n\t";
    hwlib::cout << "clear:  " << hwlib::dec << clear_re << "\n\t";
    hwlib::cout << "red:  " << hwlib::dec << red_re << "\n\t";
    hwlib::cout << "green:  " << hwlib::dec << green_re << "\n\t";
    hwlib::cout << "blue:  " << hwlib::dec << blue_re << "\n\n";
    
    hwlib::cout << "Orange:" << "\n\t";
    hwlib::cout << "clear:  " << hwlib::dec << clear_or << "\n\t";
    hwlib::cout << "red:  " << hwlib::dec << red_or << "\n\t";
    hwlib::cout << "green:  " << hwlib::dec << green_or << "\n\t";
    hwlib::cout << "blue:  " << hwlib::dec << blue_or << "\n\n";
    
    hwlib::cout << "Yellow:" << "\n\t";
    hwlib::cout << "clear:  " << hwlib::dec << clear_ye << "\n\t";
    hwlib::cout << "red:  " << hwlib::dec << red_ye << "\n\t";
    hwlib::cout << "green:  " << hwlib::dec << green_ye << "\n\t";
    hwlib::cout << "blue:  " << hwlib::dec << blue_ye << "\n\n";
    
    hwlib::cout << "Green:" << "\n\t";
    hwlib::cout << "clear:  " << hwlib::dec << clear_gr << "\n\t";
    hwlib::cout << "red:  " << hwlib::dec << red_gr << "\n\t";
    hwlib::cout << "green:  " << hwlib::dec << green_gr << "\n\t";
    hwlib::cout << "blue:  " << hwlib::dec << blue_gr << "\n\n";
    
    hwlib::cout << "Blue:" << "\n\t";
    hwlib::cout << "clear:  " << hwlib::dec << clear_bl << "\n\t";
    hwlib::cout << "red:  " << hwlib::dec << red_bl << "\n\t";
    hwlib::cout << "green:  " << hwlib::dec << green_bl << "\n\t";
    hwlib::cout << "blue:  " << hwlib::dec << blue_bl << "\n\n";
    
    hwlib::cout << "Brown:" << "\n\t";
    hwlib::cout << "clear:  " << hwlib::dec << clear_br << "\n\t";
    hwlib::cout << "red:  " << hwlib::dec << red_br << "\n\t";
    hwlib::cout << "green:  " << hwlib::dec << green_br << "\n\t";
    hwlib::cout << "blue:  " << hwlib::dec << blue_br << "\n\n";
    
    hwlib::cout << "nothing:" << "\n\t";
    hwlib::cout << "clear:  " << hwlib::dec << clear_n << "\n\t";
    hwlib::cout << "red:  " << hwlib::dec << red_n << "\n\t";
    hwlib::cout << "green:  " << hwlib::dec << green_n << "\n\t";
    hwlib::cout << "blue:  " << hwlib::dec << blue_n << "\n\n";
}