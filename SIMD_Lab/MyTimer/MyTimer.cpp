//
//  MyTimer.cpp
//  SIMD_Lab
//
//  Created by kayama on 2015/12/28.
//  Copyright © 2015年 kayama. All rights reserved.
//

#include "MyTimer.h"
#include <iostream>

using namespace std;

MyTimer::MyTimer()
{
}

MyTimer::~MyTimer()
{
    
}

void
MyTimer::start()
{
    m_start = std::chrono::high_resolution_clock::now();
}

void
MyTimer::stop()
{
    m_stop = std::chrono::high_resolution_clock::now();
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

// ######################################################################################################

AutoTimer::AutoTimer(std::string label, TimeReso reso)
{
    m_label = label;
    m_reso = reso;
    
    m_timer.start();
}

AutoTimer::~AutoTimer()
{
    m_timer.stop();
    
    switch (m_reso)
    {
        case NANO:
            cout << m_label << "," << m_timer.getTime(NANO) << "," << "nS" << endl;
            break;
        case MICRO:
            cout << m_label << "," << m_timer.getTime(MICRO) << "," << "uS" << endl;
            break;
        case MILLI:
            cout << m_label << "," << m_timer.getTime(MILLI) << "," << "mS" << endl;
            break;
        case SEC:
        default:
            cout << m_label << "," << m_timer.getTime(SEC) << "," << "S" << endl;
            break;
    }
}