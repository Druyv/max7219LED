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
//       Filename:   max7219LED.hpp
//       Part of :   Library for interfacing a max7219 chip for LED matrices
//
//       Copyright Nick Goris 2016.
//       Distributed under the Boost Software License, Version 1.0.
//       (See accompanying file LICENSE_1_0.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt)
//
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

#ifndef MAX7219LED_HPP
#define MAX7219LED_HPP

#include "monochrome.hpp"
#include "hwlib.hpp"
#include "max7219LEDconstants.hpp"

///@file
//
///max7219LED class
//
///This class interfaces the max7219 shift register for use on one or multiple 8x8 single colour LED matrices.
///It uses generic commands, such as drawPixel and clear, to utilize the matrices as a display, but also features somewhat more complex functions.
class max7219LED : public monochromeDisplay {
private:
    hwlib::target::pin_out clk;     
    hwlib::target::pin_out din;     
    hwlib::target::pin_out cs;      
    const int Lsize_x;              
    const int Lsize_y;              
public:
    max7219LED(hwlib::target::pin_out clk, hwlib::target::pin_out din, hwlib::target::pin_out cs, const int & size_x = LEDMATRIX_SIZE, const int & size_y = LEDMATRIX_SIZE);
    
    void shift_repeated_data(const uint16_t data, const uint8_t repeat);
    void send_repeated_data(const uint16_t data, const uint8_t repeat);
    void initialise(int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE*LEDMATRIX_AMOUNT)+1]);
    
    void setPixel( int x, int y, int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE*LEDMATRIX_AMOUNT)+1], int data = 1);
    void drawScreen(int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE*LEDMATRIX_AMOUNT)+1]);
    void drawPixel(int x, int y, int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE*LEDMATRIX_AMOUNT)+1], int data = 1) override;
    void clear(int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE*LEDMATRIX_AMOUNT)+1]) override;

    int get_x();
    int get_y();
};

void pulse_clk(hwlib::pin_out&clk);

#endif