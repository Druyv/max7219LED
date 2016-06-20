// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
// 
//                    ............
//                  ."         .":
//                ."         ."  :
//               :..........:    :
//         ......:          :    :...........
//       ."      :          :  ."         .":
//     ."        :          :."         ."  :
//    :..........:..........:..........:    : 
//    :          :          :          :    :
//    :          :          :          :   ."
//    :          :          :          : ."
//    :..........:..........:..........:"
//
//       Author  :   Nick Goris
//       Filename:   max7219LED.cpp
//       Part of :   Library for interfacing a max7219 chip for LED matrices
//
//       Copyright Nick Goris 2016.
//       Distributed under the Boost Software License, Version 1.0.
//       (See accompanying file LICENSE_1_0.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt)
//
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

#include "max7219LED.hpp"
#include "max7219LEDconstants.hpp"
#include <stdint.h>

///@file
///max7219LED constructor
//
///The constructor for objects based on the max7219LED class. This constructor requires 3 pins connected to the Arduino Due for the clock(clk), dataIn(din) and chipSelect(cs),
///and two values that represent the width and the height of your LED matrix construction. 
max7219LED::max7219LED(hwlib::target::pin_out clk, hwlib::target::pin_out din, hwlib::target::pin_out cs, const int & size_x, const int & size_y):
    monochromeDisplay(size_x,size_y),
    clk(clk),
    din(din),
    cs(cs),
    Lsize_x(size_x), 
    Lsize_y(size_y)
    {
        hwlib::wait_ms(1000);
    }

///Pulse clock
//
///This function pulses the clock
void pulse_clk(hwlib::pin_out&clk){
    hwlib::wait_us(1);
    clk.set(0);
    hwlib::wait_us(3);
    clk.set(1);
    hwlib::wait_us(2);
}

///Sets a pixel in the matrix
//
///This method sets the specified point (x,y) in the matrix to 1 (standard, or any other value if otherwise specified in the data variable).
void max7219LED::setPixel(int x, int y, int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE*LEDMATRIX_AMOUNT)+1], int data){
   if( ( x <= LEDMATRIX_SIZE ) && ( x > 0 ) && ( y <= LEDMATRIX_SIZE*LEDMATRIX_AMOUNT ) && ( y > 0 ) ){
        matrix[x][y] = data;
    }
}

///Shift repeated data
//
///This method repeatedly shifts data as often as needed, based on the value stored in 'repeat'. but does not load it yet. 
///Especially useful for initialising.
///Loading can be done manually by setting the chipSelect low before shifting data, and high after. 
///Loading can also be done by using the send_repeated_data method, which uses this shift method.
///It is recommended to set repeat to the amount of max7219 chips daisychained, otherwise non-specified behaviour might occur when the data is loaded.
void max7219LED::shift_repeated_data(const uint16_t data, const uint8_t repeat){
    for( uint8_t repeat_cnt = 0; repeat_cnt < repeat; repeat_cnt++ ) {
        for( int16_t bit_cnt = 15; bit_cnt >= 0; bit_cnt-- ) {
            din.set( ( data & ( 1 << bit_cnt ) ) != 0 );
            pulse_clk(clk);
        }
    }
}

///Send repeated data
//
///This method repeatedly sends data as often as needed, based on the value stored in 'repeat'.
///This method uses the shift_repeated_data method.
///It is recommended to set repeat to the amount of max7219 chips daisychained, otherwise non-specified behaviour might occur when the data is loaded.
void max7219LED::send_repeated_data(const uint16_t data, const uint8_t repeat){
    cs.set(0);          // pull chip-select low to allow clocking in data.
    max7219LED::shift_repeated_data(data, repeat);
    cs.set(1);          // pull chip-select high to load data.
}

///Clears the matrix and screen
//
///This method clears the matrix by setting all values to 0, and then uses the drawScreen method to translate this to the LED matrix screen.
void max7219LED::clear(int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE*LEDMATRIX_AMOUNT)+1]){
    for(int columnr = 1; columnr <= LEDMATRIX_SIZE; columnr++ ){
            for( int pixel = 1; pixel <= ( LEDMATRIX_SIZE*LEDMATRIX_AMOUNT ); pixel++ ){
                max7219LED::setPixel(columnr,pixel,matrix,0);
            }
    }
    max7219LED::drawScreen(matrix);
}

///initialise max7219 chip
//
///This method initialises the LED matrices. All operation values can be altered in max7219LEDconstants.hpp.
///All registers specified in this method must be initialised.
///It uses the send_repeated_data method to send the commands to every max7219 chip connected.
void max7219LED::initialise(int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE*LEDMATRIX_AMOUNT)+1]){
    send_repeated_data( ( MAX7219_REG_DISPLAYTEST << 8) | MAX7219_NO_OP_DATA, LEDMATRIX_AMOUNT );       //Sets display test
    send_repeated_data( ( MAX7219_REG_SHUTDOWN    << 8) | MAX7219_NORMAL_OPERATION, LEDMATRIX_AMOUNT ); //Sets shutdown mode
    send_repeated_data( ( MAX7219_REG_SCAN_LIMIT  << 8) | MAX7219_SCAN_LIMIT, LEDMATRIX_AMOUNT );       //Sets scan limit
    send_repeated_data( ( MAX7219_REG_DECODE      << 8) | MAX7219_NO_OP_DATA, LEDMATRIX_AMOUNT );       //Sets decode mode
    send_repeated_data( ( MAX7219_REG_BRIGHTNESS  << 8) | BRIGHTNESS_LVL, LEDMATRIX_AMOUNT );           //Sets brightness
    max7219LED::clear(matrix);                                                                          //Clears matrix, just in case
}

///Translates (software)matrix to screen
//
///This method reads a matrix, and draws the corresponding pixels on the LED matrix screen.
void max7219LED::drawScreen(int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE*LEDMATRIX_AMOUNT)+1]){
    for( int columnr = 1; columnr <= LEDMATRIX_SIZE; columnr++ ){
        cs.set(0);
        for( int pixel = ( LEDMATRIX_SIZE*LEDMATRIX_AMOUNT ); pixel >= 1; pixel-- ){
            if( pixel%8 == 0 ){
                for ( int columnbit = 7; columnbit >= 0; columnbit-- ){
                    din.set( ( columnr & ( 1 << columnbit ) ) != 0 );
                    pulse_clk(clk);
                }
            }
            din.set( ( matrix[columnr][pixel] ) != 0 );
            pulse_clk(clk);
        }
        cs.set(1);
    }
}

///Sets and draws a single pixel
//
///This method sets a pixel in the matrix to 1 (or any other value if otherwise specified in the data variable), and then draws it to the screen.
///It is a combinatory method of setPixel and drawScreen, making it more efficient to call this method for single pixels, but slower for bigger objects.
void max7219LED::drawPixel(int x, int y, int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE*LEDMATRIX_AMOUNT)+1], int data){
   if( ( x <= LEDMATRIX_SIZE ) && ( x > 0 ) && ( y <= LEDMATRIX_SIZE*LEDMATRIX_AMOUNT ) && ( y > 0 ) ){
        max7219LED::setPixel(x,y,matrix,data);
        max7219LED::drawScreen(matrix);
   }
}

///Get width of object
//
///This method returns the width of the LED matrix screen, as defined in the constructor/max7219LEDconstants file.
int max7219LED::get_x(){
    return size_x;
}

///Get heigth of object
//
///This method returns the height of the LED matrix screen, as defined in the constructor/max7219LEDconstants file.
int max7219LED::get_y(){
    return size_y;
}