#ifndef COLOR_SENSOR_HPP
#define COLOR_SENSOR_HPP

#include "hwlib.hpp"

/// @file

/// \brief
/// Color sensor
/// \details
/// This is a class that will read and write data to the TCS3472 color sensor
/// The i2c_bus of hwlib is stored in the class.
/// There are a few functions provided like Setup and get_data_red.
///
/// Before you start read the colors, use the SetUp function.
/// If SetUp returns true, you are ready to go.

class color_sensor{
protected:
    bool SetUp_Done;
    hwlib::i2c_bus & i2c_bus;
    
    void ATIME();
    void GAIN();
    void enable();
    uint8_t ID();

public:
    /// \brief
    /// Constructor for the i2c_bus
    /// \details
    /// This constructor initializes a hwlib::i2c_bus form the i2c_bus.
    /// SetUp_Done is also constucted here, but SetUp_Done always starts with false.
    color_sensor(hwlib::i2c_bus & i2c_bus);  

    /// \brief
    /// Get the clear for the color sensor
    /// \details
    /// This function reads the clear data of the color sensor.
    /// It will return a uint16_t value.
    /// Used in the color recognition.
    uint16_t get_data_clear();
    
    /// \brief
    /// Get the red for the color sensor
    /// \details
    /// This function reads the red data of the color sensor.
    /// It will return a uint16_t value.
    /// Used in the color recognition.
    uint16_t get_data_red();
    
    /// \brief
    /// Get the green for the color sensor
    /// \details
    /// This function reads the green data of the color sensor.
    /// It will return a uint16_t value.
    /// Used in the color recognition.
    uint16_t get_data_green();
    
    /// \brief
    /// Get the blue for the color sensor
    /// \details
    /// This function reads the blue data of the color sensor.
    /// It will return a uint16_t value.
    /// Used in the color recognition.
    uint16_t get_data_blue();
    
    /// \brief
    /// Writes the right settings to the color sensor
    /// \details
    /// First checks if the ID of the color sensor is 0x44 or 0x4D.
    /// An other value means that the color sensor isn't conected right.
    ///
    /// After that check, Setup will set the ATIME (how precisely the sensor is) and the GAIN.
    /// Last stap is to enable the color sensor, so it can 'see' colors.
    bool SetUp();
};

#endif // COLOR_SENSOR_HPP

//if((tmp_red > (blue.red() - 30) and tmp_red < (blue.red() + 30)) and (tmp_green > (blue.green() - 75) and tmp_green < (blue.green() + 75)) and (tmp_blue > (blue.blue() - 50) and tmp_blue < (blue.blue() + 50))){ // Blue
//                i = 0; // For displaying blue
//                sort.set_blue(); // Sorting system to blue
//                servo2.set(45);
//                hwlib::wait_ms(500);
//                servo2.set(180);
//            }else if((tmp_red > (green.red() - 100) and tmp_red < (green.red() + 100)) and (tmp_green > (green.green() - 150) and tmp_green < (green.green() + 150)) and (tmp_blue > (green.blue() - 100) and tmp_blue < (green.blue() + 100))){ // Green
//                i = 1;
//                sort.set_green();
//                servo2.set(45);
//                hwlib::wait_ms(500);
//                servo2.set(180);
//            }else if((tmp_red > (orange.red() - 40) and tmp_red < (orange.red() + 100)) and (tmp_green > (orange.green() - 50) and tmp_green < (orange.green() + 75)) and (tmp_blue > (orange.blue() - 50) and tmp_blue < (orange.blue() + 50))){ // Orange
//                i = 2;
//                sort.set_orange();
//                servo2.set(45);
//                hwlib::wait_ms(500);
//                servo2.set(180); 
//            }else if((tmp_red > (red.red() - 100) and tmp_red < (red.red() + 40)) and (tmp_green > (red.green() - 75) and tmp_green < (red.green() + 50)) and (tmp_blue > (red.blue() - 50) and tmp_blue < (red.blue() + 50))){ // Red
//                i = 3;
//                sort.set_red();
//                servo2.set(45);
//                hwlib::wait_ms(500);
//                servo2.set(180);
//            }else if((tmp_red > (yellow.red() - 200) and tmp_red < (yellow.red() + 2000)) and (tmp_green > (yellow.green() - 200) and tmp_green < (yellow.green() + 2000))){ // Yellow
//                i = 4;
//                sort.set_yellow();
//                servo2.set(45);
//                hwlib::wait_ms(500);
//                servo2.set(180);
//            }else if((tmp_red < (brown.red() + 500)) and (tmp_green < (brown.green() + 500)) and (tmp_blue < (brown.blue() + 500))){ // Brown
//                i = 5;
//                sort.set_brown();
//                servo2.set(45);
//                hwlib::wait_ms(500);
//                servo2.set(180);