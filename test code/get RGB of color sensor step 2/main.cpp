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

    display << "\f\n\nLoading..."; // Display 'Loading...' while setting everything up.
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
    
    auto button = target::pin_in(target::pins::d8); // safety button if something is wrong
    
    servo1.set(150); // set servo 1 to the left.
    servo2.set(45); // Open and close the servo after the color sensor so there are no m&m's in the color recognition.
    hwlib::wait_ms(1000);
    servo2.set(180);
    hwlib::wait_ms(100);

    while(not color.SetUp()){ // SetUp of the color sensor.
        display << "\f\n\nERROR SetUp!"; // if SetUp failed, it will give an error.
        display << hwlib::flush;
    }
    
    int i = 6;
    int loop = 0;
    bool wait;
    while(1){
        loop++;
        wait = true;
        float clear = color.get_data_clear(); // Get the RGB value.
        float red   = color.get_data_red();
        float green = color.get_data_green();
        float blue  = color.get_data_blue(); 

        while((clear == 0 or clear == 65536) and (red == 0 or red == 65536) and (green == 0 or green == 65536) and (blue == 0 or blue == 65536)){ 
            // If all the values are 0 or 65536, there is probably a cable loose.
            display << "\f\n\nERROR 2!";
            display << hwlib::flush;
            hwlib::wait_ms(100);
            clear = color.get_data_clear();
            red   = color.get_data_red();
            green = color.get_data_green();
            blue  = color.get_data_blue();
        }   
        
        display << "\f\n\n";
        display << hwlib::dec << int(clear) << "\n"; // display the RGB values (mainly for testing)
        display << hwlib::dec << int(red)   << "\n";
        display << hwlib::dec << int(green) << "\n";
        display << hwlib::dec << int(blue)  << "\n\n";  
                                                                                                       // The values of the RGB are compared with the values of the used colors
        if(((green/red) > 1.7) and ((green/red) < 2.2) and ((blue/red) > 1.8) and ((blue/red) < 2.7)){ // Blue
            i = 0; // For displaying blue
            sort.set_blue(); // Sorting system to blue
            servo2.set(45); // To let the m&m go in the sorting system
            hwlib::wait_ms(500);
            servo2.set(180);
            hwlib::wait_ms(1000);
        }else if(((green/red) > 1.6) and ((green/red) < 2) and ((blue/red) > 0.9) and ((blue/red) < 1.2)){ // Green
            i = 1;
            sort.set_green();
            servo2.set(45);
            hwlib::wait_ms(500);
            servo2.set(180);
            hwlib::wait_ms(1000);
        }else if(((red/blue) > 1.7) and ((red/blue) < 2) and ((green/blue) > 1.4) and ((green/blue) < 1.7)){ // Orange
            i = 2;
            sort.set_orange();
            servo2.set(45);
            hwlib::wait_ms(500);
            servo2.set(180);
            hwlib::wait_ms(1000); 
        }else if(((red/blue) > 1.4) and ((red/blue) < 1.7) and ((green/blue) > 1.2) and ((green/blue) < 1.4)){ // Red
            i = 3;
            sort.set_red();
            servo2.set(45);
            hwlib::wait_ms(500);
            servo2.set(180);
            hwlib::wait_ms(1000);
        }else if(((red/blue) > 1.5) and ((red/blue) < 2.5) and ((green/blue) > 2.1) and ((green/blue) < 2.8)){ // Yellow
            i = 4;
            sort.set_yellow();
            servo2.set(45);
            hwlib::wait_ms(500);
            servo2.set(180);
            hwlib::wait_ms(1000);
        }else if(((red/blue) > 1.1) and ((red/blue) < 1.3) and ((green/blue) > 1.2) and ((green/blue) < 1.4) and ((clear/blue) > 3.5) and ((clear/blue) < 4.1)){ // Brown
            i = 5;
            sort.set_brown();
            servo2.set(45);
            hwlib::wait_ms(500);
            servo2.set(180);
            hwlib::wait_ms(1000);
        }else{
            wait = false; // If no color is recognized, no need to wait 
        }
        
        if(i == 0){ // If-statement for adding the color (or 'No color yet') to the display.
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
        display << hwlib::flush; // Flushing the display
        
        if(wait){ // Wait if color is recognized.
            loop = 20;
            hwlib::wait_ms(5000);
        }
        
        if(loop >= 20){ // Open and close the upper servo so the next m&m goes to the color sensor.
            servo1.set(166);
            hwlib::wait_ms(1000);
            servo1.set(150);
            loop = 0;
        }
        
        button.refresh();
        if(button.read()){ // Safety button for if m&m is stuck under the sensor.
            servo2.set(45);
            hwlib::wait_ms(1000);
            servo2.set(180);
            hwlib::wait_ms(15000);
        }
    }
}