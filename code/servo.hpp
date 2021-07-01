#ifndef SERVO_HPP
#define SERVO_HPP

#include "hwlib.hpp"

/// @file

/// \brief
/// Set servo
/// \details
/// This is a class that will move a servo.
/// The servo pin is stored in the class.
/// There are a few functions provided that move the servo.

class set_servo{
private:
    hwlib::pin_out & pin_servo;
    
public:
    /// \brief
    /// Constructor for the pin_servo
    /// \details
    /// This constructor initializes a hwlib::pin_out form the pin_servo.
    /// There is no default value of pin_servo.
    set_servo(hwlib::pin_out & pin_servo);
    
    /// \brief
    /// Closes servo if true
    /// \details
    /// If the value given is true, servo will be closed (it will go down).
    /// If false, servo will open (it will go up).
    /// Used in the color recognition.
    void servo_close(bool close);
    
    /// \brief
    /// Servo is left if true
    /// \details
    /// If the value given is true, servo will go to the left side.
    /// If false, servo will go to the right side.
    /// Used in the color sorting system.
    void servo_left(bool left);
    
    /// \brief
    /// Open and close servo for amount of time
    /// \details
    /// Uses servo_close to open and close the servo for the given amount of time.
    /// The time is in ms.
    /// Used in the color recognition. 
    void servo_open_and_close(float time);
};


/// \brief
/// Sorting system with 5 servo's
/// \details
/// This is an sorting system that uses 5 servo's.
/// This class uses the set_servo class to save servo_pins and rotate the servo's.
/// The only thing this class does is that the right servo's move for each color.
class sort_system{
private:
    set_servo servo1, servo2, servo3, servo4, servo5;
    
public:
    /// \brief
    /// Constructor for the 5 servo's
    /// \details
    /// This constructor initializes 5 servo's that use set_servo.
    /// This class is special made for a sorting system with 5 servo's.
    sort_system(set_servo & servo1, set_servo & servo2, set_servo & servo3, set_servo & servo4, set_servo & servo5);
    
    /// \brief
    /// Set sorting sytem to red output
    /// \details
    /// This function set the needed servo's to the output of red.
    /// Uses only servo 1 and 3.
    /// Used in the color sorting system.
    void set_red();
    
    /// \brief
    /// Set sorting sytem to orange output
    /// \details
    /// This function set the needed servo's to the output of orange.
    /// Uses only servo 1 and 3.
    /// Used in the color sorting system.
    void set_orange();
    
    /// \brief
    /// Set sorting sytem to yellow output
    /// \details
    /// This function set the needed servo's to the output of yellow.
    /// Uses only servo 1, 2 and 4.
    /// Used in the color sorting system.
    void set_yellow();
    
    /// \brief
    /// Set sorting sytem to green output
    /// \details
    /// This function set the needed servo's to the output of green.
    /// Uses only servo 1, 2 and 4.
    /// Used in the color sorting system.
    void set_green();
    
    /// \brief
    /// Set sorting sytem to blue output
    /// \details
    /// This function set the needed servo's to the output of blue.
    /// Uses only servo 1, 2 and 5.
    /// Used in the color sorting system.
    void set_blue();
    
    /// \brief
    /// Set sorting sytem to brown output
    /// \details
    /// This function set the needed servo's to the output of brown.
    /// Uses only servo 1, 2 and 5.
    /// Used in the color sorting system.
    void set_brown();
};

#endif // SERVO_HPP