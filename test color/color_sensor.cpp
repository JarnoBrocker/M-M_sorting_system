#include "hwlib.hpp"
#include "color_sensor.hpp"

void color_sensor::ATIME(){ // ATIME
    i2c_bus.write(0xA1); 
    i2c_bus.write(0x29).write(0xA1);
    i2c_bus.write(0x00);
    i2c_bus.write(0x29).write(0x00);
}

void color_sensor::GAIN(){ // GAIN
    i2c_bus.write(0xAF); 
    i2c_bus.write(0x29).write(0xAF);
    i2c_bus.write(0x01);
    i2c_bus.write(0x29).write(0x01);
}

void color_sensor::enable(){ // enable
    i2c_bus.write(0xA0); 
    i2c_bus.write(0x29).write(0xA0);
    i2c_bus.write(0x01); 
    i2c_bus.write(0x29).write(0x01);
    hwlib::wait_ms(3);
    i2c_bus.write(0x03); 
    i2c_bus.write(0x29).write(0x03);
    hwlib::wait_ms(3);
}

uint8_t color_sensor::ID(){ // Gets ID of color sensor
    i2c_bus.write(0xB2); 
    i2c_bus.write(0x29).write(0xB2);
    uint8_t ID;
    i2c_bus.read(0x29).read(ID);
    return ID;
}

color_sensor::color_sensor(hwlib::i2c_bus & i2c_bus):
    SetUp_Done(false),
    i2c_bus(i2c_bus)
{}
    
uint16_t color_sensor::get_data_clear(){
    uint8_t low;
    uint8_t high;
    i2c_bus.write(0xB4); 
    i2c_bus.write(0x29).write(0xB4);
    i2c_bus.read(0x29).read(low);
    i2c_bus.write(0xB5); 
    i2c_bus.write(0x29).write(0xB5);
    i2c_bus.read(0x29).read(high);
    uint16_t tmp = low;
    for(int i = 0; i < 8; i++){
        tmp ^= (((high >> i) & 1) << (i + 8));
    }
    hwlib::wait_ms(3);
    return tmp;
}

uint16_t color_sensor::get_data_red(){
    uint8_t low;
    uint8_t high;
    i2c_bus.write(0xB6); 
    i2c_bus.write(0x29).write(0xB6);
    i2c_bus.read(0x29).read(low);
    i2c_bus.write(0xB7); 
    i2c_bus.write(0x29).write(0xB7);
    i2c_bus.read(0x29).read(high);
    uint16_t data = (high << 8) | low;
    hwlib::wait_ms(3);
    return data;
}

uint16_t color_sensor::get_data_green(){
    uint8_t low;
    uint8_t high;
    i2c_bus.write(0xB8); 
    i2c_bus.write(0x29).write(0xB8);
    i2c_bus.read(0x29).read(low);
    i2c_bus.write(0xB9); 
    i2c_bus.write(0x29).write(0xB9);
    i2c_bus.read(0x29).read(high);
    uint16_t data = (high << 8) | low;
    hwlib::wait_ms(3);
    return data;
}

uint16_t color_sensor::get_data_blue(){
    uint8_t low;
    uint8_t high;
    i2c_bus.write(0xBA); 
    i2c_bus.write(0x29).write(0xBA);
    i2c_bus.read(0x29).read(low);
    i2c_bus.write(0xBB); 
    i2c_bus.write(0x29).write(0xBB);
    i2c_bus.read(0x29).read(high);
    uint16_t data = (high << 8) | low;
    hwlib::wait_ms(3);
    return data;
}

bool color_sensor::SetUp(){
    if(SetUp_Done){
        return true;
    }
    auto id = ID();
    if(id != 0x44 and id != 0x4D){
        return false;
    }
    ATIME();
    GAIN();
    enable();
    SetUp_Done = true;
    return true;
}