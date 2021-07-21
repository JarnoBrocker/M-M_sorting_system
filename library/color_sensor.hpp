#ifndef COLOR_SENSOR_HPP
#define COLOR_SENSOR_HPP

#include "hwlib.hpp"

/// @file

/// \brief
/// Color sensor
/// \details
/// This is a class that will read and write data to the TCS3472 color sensor.\n
/// The i2c_bus of hwlib is stored in the class.\n
/// There are a few functions provided like Setup and get_data_red.\n\n
/// Before you start to read the colors, use the SetUp function.\n
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
    /// This constructor initializes a hwlib::i2c_bus from the i2c_bus.\n
    /// The SetUp_Done is also constucted here, but the SetUp_Done always starts as false.
    color_sensor(hwlib::i2c_bus & i2c_bus);  

    /// \brief
    /// Get the clear for the color sensor
    /// \details
    /// This function reads the clear data of the color sensor.\n
    /// It will return a uint16_t value.\n
    /// This function is used in the color recognition.
    uint16_t get_data_clear();
    
    /// \brief
    /// Get the red for the color sensor
    /// \details
    /// This function reads the red data of the color sensor.\n
    /// It will return a uint16_t value.\n
    /// This function is used in the color recognition.
    uint16_t get_data_red();
    
    /// \brief
    /// Get the green for the color sensor
    /// \details
    /// This function reads the green data of the color sensor.\n
    /// It will return a uint16_t value.\n
    /// This function is used in the color recognition.
    uint16_t get_data_green();
    
    /// \brief
    /// Get the blue for the color sensor
    /// \details
    /// This function reads the blue data of the color sensor.\n
    /// It will return a uint16_t value.\n
    /// This function is used in the color recognition.
    uint16_t get_data_blue();
    
    /// \brief
    /// Writes the right settings to the color sensor
    /// \details
    /// First checks if the ID of the color sensor is 0x44 or 0x4D.\n
    /// Another value means that the color sensor isn't connected right.\n
    /// After that check, Setup will set the ATIME and the GAIN (both control how precise the sensor is).\n
    /// Last step is to turn on the color sensor, so it can 'see' colors.\n
    bool SetUp();
};

#endif // COLOR_SENSOR_HPP