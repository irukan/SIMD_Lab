//
//  MyTimer.hpp
//  SIMD_Lab
//
//  Created by kayama on 2015/12/28.
//  Copyright © 2015年 kayama. All rights reserved.
//

#ifndef MyTimer_hpp
#define MyTimer_hpp

#include <chrono>
#include <string>

enum TimeReso
{
    NANO,
    MICRO,
    MILLI,
    SEC
};

class MyTimer
{
private:
    std::chrono::high_resolution_clock::time_point m_start;
    std::chrono::high_resolution_clock::time_point m_stop;
    
public:
    MyTimer();
    ~MyTimer();
    
    void start();
    void stop();
    
    double getTime(TimeReso reso);
    
};

class AutoTimer
{
private:
    MyTimer m_timer;
    std::string m_label;
    TimeReso m_reso;
    
public:
    AutoTimer(std::string label, TimeReso reso);
    ~AutoTimer();
};

#endif /* MyTimer_hpp */
