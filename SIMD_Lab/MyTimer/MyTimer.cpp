//
//  MyTimer.cpp
//  SIMD_Lab
//
//  Created by kayama on 2015/12/28.
//  Copyright © 2015年 kayama. All rights reserved.
//

#include "MyTimer.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

std::string
getTimeResoStr(TimeReso reso)
{
    switch (reso)
    {
        case NANO:
            return "nS";
        case MICRO:
            return "uS";
        case MILLI:
            return "mS";

        case SEC:
        default:
            return "S";
            break;
    }
}

MyTimer::MyTimer()
{
}

MyTimer::~MyTimer(){}

MyTimer&
MyTimer::getInstance()
{
    static MyTimer inst;
    
    return inst;
}

void
MyTimer::start(const std::string& label, TimeReso reso)
{
    m_label.push_back(label);
    m_reso.push_back(reso);
    
    m_start = std::chrono::high_resolution_clock::now();
}

void
MyTimer::stop()
{
    m_stop = std::chrono::high_resolution_clock::now();
    
    m_data.push_back(getTime(m_reso[m_reso.size() - 1]));
}

double
MyTimer::getTime(TimeReso reso)
{
    switch (reso)
    {
        case NANO:
            return std::chrono::duration_cast<std::chrono::nanoseconds>(m_stop - m_start).count();
        case MICRO:
            return std::chrono::duration_cast<std::chrono::microseconds>(m_stop - m_start).count();
        case MILLI:
            return std::chrono::duration_cast<std::chrono::milliseconds>(m_stop - m_start).count();
        case SEC:
        default:
            return std::chrono::duration_cast<std::chrono::seconds>(m_stop - m_start).count();
    }
}

void
MyTimer::output(const std::string& file)
{
    size_t size = m_data.size();
    
    ostringstream os;
    for (int i = 0; i < size; i++)
    {
        os << m_label[i] << ","
           << m_data[i] << ","
           << getTimeResoStr(m_reso[i])
           << endl;
    }
    
    cout << os.str();
    
    if (file.size() != 0)
    {
        ofstream ofs(file);
        ofs << os.str();
        ofs.close();
    }
    
    m_data.clear();
    m_label.clear();
    m_reso.clear();
}
