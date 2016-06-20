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

.PHONY: clean build run error

clean: error
build: error
run: error

MSG  = You are trying to build in a library directory.
MSG += Make one of the project source files your current editor file.

error:
	$(error $(MSG) )