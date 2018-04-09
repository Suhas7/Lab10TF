cmake_minimum_required(VERSION 3.9)
project(Lab10TF)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lab10TF
        audio/dac.h
        audio/Lab6.c
        audio/sBytes.hpp
        audio/Sound.cpp
        audio/Sound.h
        display/Kentec_4C123/FPU.c
        display/Kentec_4C123/FPU.h
        display/Kentec_4C123/images.h
        display/Kentec_4C123/LCDTestMain.c
        display/Kentec_4C123/LCDTests.h
        display/Kentec_4C123/lm4f120h5qr.h
        display/Kentec_4C123/PLL.c
        display/Kentec_4C123/PLL.h
        display/Kentec_4C123/random.h
        display/Kentec_4C123/SSD2119.c
        display/Kentec_4C123/SSD2119.h
        display/Kentec_4C123/systick.c
        display/Kentec_4C123/systick.h
        display/FPU.c
        display/FPU.h
        display/images.h
        display/LCDTestMain.c
        display/LCDTests.h
        display/lm4f120h5qr.h
        display/PLL.c
        display/PLL.h
        display/random.h
        display/SSD2119.c
        display/SSD2119.h
        display/systick.c
        display/systick.h
        hardware/Controller.cpp
        hardware/Controller.hpp
        physics/Actors.hpp
        physics/Physics.cpp
        main.cpp
        main.hpp
        TExaS.h
        tm4c123gh6pm.h
        workpad.cpp)
