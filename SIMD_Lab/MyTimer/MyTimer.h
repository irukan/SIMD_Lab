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

inline MyTimer&
MyTimer::getInstance()
{
    static MyTimer inst;
    
    return inst;
}

inline void
MyTimer::start(const std::string& label, TimeReso reso)
{
    m_label.push_back(label);
    m_reso.push_back(reso);
    
    m_start = std::chrono::high_resolution_clock::now();
}

inline void
MyTimer::stop()
{
    m_stop = std::chrono::high_resolution_clock::now();
    
    m_data.push_back(getTime(m_reso[m_reso.size() - 1]));
}

#define TIMER MyTimer::getInstance()

#endif /* MyTimer_hpp */
