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
//       Filename:   max7219LEDconstants.hpp
//       Part of :   Library for interfacing a max7219 chip for LED matrices
//
//       Copyright Nick Goris 2016.
//       Distributed under the Boost Software License, Version 1.0.
//       (See accompanying file LICENSE_1_0.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt)
//
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

#ifndef MAX7219LED_CONSTANTS_HPP
#define MAX7219LED_CONSTANTS_HPP
///@file

///NO-OP register address - If this is send as an address, the matrix this is sent to changes nothing, disregarding the data sent to the same chip.
constexpr uint8_t MAX7219_REG_NO_OP         = 0x00;

///DECODE register address - Sets the decode mode of the max7219 chip. 
constexpr uint8_t MAX7219_REG_DECODE        = 0x09;
constexpr uint8_t MAX7219_REG_BRIGHTNESS    = 0x0A;
constexpr uint8_t MAX7219_REG_SCAN_LIMIT    = 0x0B;
constexpr uint8_t MAX7219_REG_SHUTDOWN      = 0x0C;
constexpr uint8_t MAX7219_REG_DISPLAYTEST   = 0x0F;

constexpr uint8_t MAX7219_COLUMN1           = 0x01;
constexpr uint8_t MAX7219_COLUMN2           = 0x02;
constexpr uint8_t MAX7219_COLUMN3           = 0x03;
constexpr uint8_t MAX7219_COLUMN4           = 0x04;
constexpr uint8_t MAX7219_COLUMN5           = 0x05;
constexpr uint8_t MAX7219_COLUMN6           = 0x06;
constexpr uint8_t MAX7219_COLUMN7           = 0x07;
constexpr uint8_t MAX7219_COLUMN8           = 0x08;

///Multi-purpose data - Sends no data to a column or used for a NO-OP on certain settings.
constexpr uint8_t MAX7219_NO_OP_DATA        = 0x00; 
///Sets the amount of columns that can be adressed, 1-8 (0x00-0x07).
constexpr uint8_t MAX7219_SCAN_LIMIT        = 0x07; 
///Used to enable Shutdown mode and Display test.
constexpr uint8_t MAX7219_NORMAL_OPERATION  = 0x01;
///Sets brightness of LEDs (0x01-0x1F).
constexpr uint8_t BRIGHTNESS_LVL            = 0x05;
 
///Sets the amount of LED matrices daisy chained.
constexpr uint8_t LEDMATRIX_AMOUNT          = 4;    
///Sets the size of the led matrices.
constexpr uint8_t LEDMATRIX_SIZE            = 8;    

constexpr uint8_t PIXELBUFFER               = 0x00;

#endif

