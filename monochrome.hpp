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
//       Filename:   monochrome.hpp
//       Part of :   Library for interfacing a max7219 chip for LED matrices
//
//       Copyright Nick Goris 2016.
//       Distributed under the Boost Software License, Version 1.0.
//       (See accompanying file LICENSE_1_0.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt)
//
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #


#ifndef MONOCHROME_HPP
#define MONOCHOME_HPP

#include <stdint.h>
#include "max7219LEDconstants.hpp"

///@file
//
///monochromeDisplay class
//
///This class is abstract. It can be used for inheritance purposes with monochrome displays, such as LED matrices and (old) OLED screens.
class monochromeDisplay{
protected:
    const int size_x;
    const int size_y;
public:
    monochromeDisplay(const int & size_x, const int & size_y):
    size_x(size_x),
    size_y(size_y)
    {}
    virtual void drawPixel( int x, int y, int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE*LEDMATRIX_AMOUNT)+1], int data = 1) = 0;
    virtual void clear(int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE*LEDMATRIX_AMOUNT)+1]) = 0;
};

#endif