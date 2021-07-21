#ifndef SERVO_HPP
#define SERVO_HPP

#include "hwlib.hpp"

/// @file

/// \brief
/// Set servo
/// \details
/// This is a class that will move a servo.\n
/// The servo pin is stored in the class.\n
/// There is a function provided that moves the servo.

class set_servo{
private:
    hwlib::pin_out & pin_servo;
    
public:
    /// \brief
    /// Constructor for the pin_servo
    /// \details
    /// This constructor initializes a hwlib::pin_out from the pin_servo.\n
    /// There is no default value of pin_servo.
    set_servo(hwlib::pin_out & pin_servo);
    
    /// \brief
    /// Sets a servo to given angle
    /// \details
    /// This funtion sets the servo to a given angle.\n
    /// If the given angle is below 0, the angle is set to 0.\n
    /// If the given angle is above 180, the angle is set to 180.
    void set(int angle);
};

/// \brief
/// Sorting system with 5 servo's
/// \details
/// This is a sorting system that uses 5 servo's.\n
/// This class uses the set_servo class to save servo_pins and rotate the servo's.\n
/// The sole purpose of this class is letting the right servo’s move for each color.
class sort_system{
private:
    set_servo servo1, servo2, servo3, servo4, servo5;
    
public:
    /// \brief
    /// Constructor for the 5 servo's
    /// \details
    /// This constructor initializes 5 servo's that use set_servo.\n
    /// This class is specifically made for a sorting system with 5 servo's.
    sort_system(set_servo & servo1, set_servo & servo2, set_servo & servo3, set_servo & servo4, set_servo & servo5);
    
    /// \brief
    /// Set sorting sytem to red output
    /// \details
    /// This function sets the needed servo's to the output of red.\n
    /// Uses only servo 1 and 3.\n
    /// Used in the color sorting system.
    void set_red();
    
    /// \brief
    /// Set sorting sytem to orange output
    /// \details
    /// This function sets the needed servo's to the output of orange.\n
    /// Uses only servo 1 and 3.\n
    /// Used in the color sorting system.
    void set_orange();
    
    /// \brief
    /// Set sorting sytem to yellow output
    /// \details
    /// This function sets the needed servo's to the output of yellow.\n
    /// Uses only servo 1, 2 and 4.\n
    /// Used in the color sorting system.
    void set_yellow();
    
    /// \brief
    /// Set sorting sytem to green output
    /// \details
    /// This function sets the needed servo's to the output of green.\n
    /// Uses only servo 1, 2 and 4.\n
    /// Used in the color sorting system.
    void set_green();
    
    /// \brief
    /// Set sorting sytem to blue output
    /// \details
    /// This function sets the needed servo's to the output of blue.\n
    /// Uses only servo 1, 2 and 5.\n
    /// Used in the color sorting system.
    void set_blue();
    
    /// \brief
    /// Set sorting sytem to brown output
    /// \details
    /// This function sets the needed servo's to the output of brown.\n
    /// Uses only servo 1, 2 and 5.\n
    /// Used in the color sorting system.
    void set_brown();
};

#endif // SERVO_HPP