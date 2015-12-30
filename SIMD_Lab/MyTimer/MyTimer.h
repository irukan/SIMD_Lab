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
#include <vector>

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
    
    std::vector<std::string> m_label;
    std::vector<double> m_data;
    std::vector<TimeReso> m_reso;
 
    MyTimer();
    ~MyTimer();
public:

    
    static MyTimer& getInstance();
    
    void start(const std::string& label, TimeReso reso);
    void stop();
    
    double getTime(TimeReso reso);
    
    void output(const std::string& file = "");
    
};

#define TIMER MyTimer::getInstance()

#endif /* MyTimer_hpp */
