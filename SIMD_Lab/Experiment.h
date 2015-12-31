//
//  Experiment.h
//  SIMD_Lab
//
//  Created by kayama on 2015/12/31.
//  Copyright © 2015年 kayama. All rights reserved.
//

#ifndef Experiment_h
#define Experiment_h

#include "MyTimer/MyTimer.h"

#include "SSE.h"
#include "Normal.h"

#include <iostream>
#include <math.h>
#include <random>

using namespace std;

int dataN;
int loopN;

template<typename T>
bool isEqual(T d1, T d2)
{
    return std::abs(d1 - d2) < std::numeric_limits<T>::epsilon();
}

template<typename T>
T* fixArr(T fix)
{
    T *ar = new T[dataN];
    for (int i = 0; i < dataN; i++)
        ar[i] = fix;
    return ar;
}

template<typename T>
T* rampArr(double slope)
{
    T *ar = new T[dataN];
    for (int i = 0; i < dataN; i++)
        ar[i] = i * slope;
    return ar;
}

double* sinArr(double amp = 1.0)
{
    double dx = 2 * M_PI / (double)dataN;
    double *ar = new double[dataN];
    for (int i = 0; i < dataN; i++)
        ar[i] = sin(dx * i) * amp;
    
    return ar;
}

template<typename T>
T* randArr(T min, T max)
{
    T *ar = new T[dataN];
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<T> randVal(min, max);
    
    for (int i = 0; i < dataN; i++)
        ar[i] = randVal(mt);
    
    return ar;
}

int
randVal(int min, int max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> rand(min, max);
    
    return rand(mt);
}

//######################################################################################
void exp_add_double()
{
    dataN = 10000;
    loopN = 5000;
    
    for (int i = 0; i < loopN; i++)
    {
        double *ar1 = rampArr<double>(2.5);
        double *ar2 = rampArr<double>(2.5);
        
        TIMER.start("add_Normal", NANO);
        add_Normal(ar1, 0.1, dataN);
        TIMER.stop();
        
        TIMER.start("add_SSE", NANO);
        add_SSE(ar2, 0.1, dataN);
        TIMER.stop();
        
        for (int i = 0; i< dataN; i++)
        {
            if (isEqual(ar1[i], ar2[i]))
            {
                cout << "Not match" << endl;
                exit(1);
            }
        }
    }
    
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 5000 25000");
}

void exp_add_int()
{
    dataN = 10000;
    loopN = 5000;
    
    for (int i = 0; i < loopN; i++)
    {
        int *ar1 = rampArr<int>(2);
        int *ar2 = rampArr<int>(2);
        
        TIMER.start("add_Normal", NANO);
        add_Normal(ar1, 1, dataN);
        TIMER.stop();
        
        TIMER.start("add_SSE", NANO);
        add_SSE(ar2, 1, dataN);
        TIMER.stop();
        
        for (int i = 0; i< dataN; i++)
        {
            if (ar1[i] != ar2[i])
            {
                cout << "Not match" << endl;
                exit(1);
            }
        }
    }
    
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 5000 25000");
}
void exp_copy_int()
{
    dataN = 10000;
    loopN = 5000;
    
    for (int i = 0; i < loopN; i++)
    {
        int *arI1 = rampArr<int>(10);
        int *arI2 = rampArr<int>(10);
        
        int *target1 = fixArr(0);
        int *target2 = fixArr(0);
        
        TIMER.start("copy_Normal", NANO);
        copy_Normal(arI1, target1, dataN);
        TIMER.stop();
        
        TIMER.start("copy_SSE", NANO);
        copy_SSE(arI2, target2, dataN);
        TIMER.stop();
        
        for (int i = 0; i < dataN; i++)
        {
            if (target1[i] != target2[i])
            {
                cout << "Not match" << endl;
                exit(1);
            }
        }
    }
    
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 5000 25000");
}

void exp_max_double()
{
    dataN = 10000;
    loopN = 5000;
    
    for (int i = 0; i < loopN; i++)
    {
        double *data = randArr<double>(0, 10);
        
        volatile double max1;
        volatile double max2;

        TIMER.start("max_Normal", NANO);
        max1 = max_Normal(data, dataN);
        TIMER.stop();
        
        TIMER.start("max_SSE", NANO);
        max2 = max_SSE(data, dataN);
        TIMER.stop();
        
        if (!isEqual<double>(max1, max2))
        {
            cout << "Not match" << endl;
            exit(1);
        }
    }
    
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 20000 50000");
}

void exp_findIdx_int()
{
    dataN = 10000;
    loopN = 10000;
    
    for (int i = 0; i < loopN; i++)
    {
        int* data = rampArr<int>(1);
        //int target = randVal(0, dataN);
        int target = dataN / 2;
     
        volatile int idx1;
        volatile int idx2;
        
        TIMER.start("findIdx_Normal", NANO);
        idx1 = findIdx_Normal(data, target , dataN);
        TIMER.stop();
        
        TIMER.start("findIdx_SSE", NANO);
        idx2 = findIdx_SSE(data, target , dataN);
        TIMER.stop();
        
        if (idx1 != idx2)
        {
            cout << "Not match" << endl;
            exit(1);
        }
    }
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 0 27000");
    
}

#endif /* Experiment_h */
