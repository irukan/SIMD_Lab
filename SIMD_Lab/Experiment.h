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
#include "TrigFunc.h"

#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>
#include <string>

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

float
randVal(float min, float max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> rand(min, max);
    
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
            if (!isEqual(ar1[i], ar2[i]))
            {
                cout << "Not match" << endl;
                exit(1);
            }
        }
    }
    
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 0 10000");
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

void exp_add_mul_double()
{
    dataN = 10000;
    loopN = 5000;
    
    for (int i = 0; i < loopN; i++)
    {
        double *ar1 = rampArr<double>(2.5);
        double *ar2 = rampArr<double>(2.5);
        
        TIMER.start("add_mul_Normal", NANO);
        add_mul_Normal(ar1, 0.1, 0.5, dataN);
        TIMER.stop();
        
        TIMER.start("add_mul_SSE", NANO);
        add_mul_SSE(ar2, 0.1, 0.5, dataN);
        TIMER.stop();
        
        for (int i = 0; i< dataN; i++)
        {
            if (!isEqual(ar1[i], ar2[i]))
            {
                cout << "Not match" << endl;
                exit(1);
            }
        }
    }
    
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 5000 30000");
}
void exp_copy_int()
{
    dataN = 10006;
    loopN = 5000;
    
    for (int i = 0; i < loopN; i++)
    {
        int *data = rampArr<int>(10);
        
        int *target1 = fixArr(0);
        int *target2 = fixArr(0);
        
        TIMER.start("copy_Normal", NANO);
        copy_Normal(data, target1, dataN);
        TIMER.stop();
        
        TIMER.start("copy_SSE", NANO);
        copy_SSE(data, target2, dataN);
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
    system("python Analysis/DispHist.py output.csv 8000 30000");
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
    system("python Analysis/DispHist.py output.csv 22000 50000");
}

void exp_findIdx_int()
{
    dataN = 10000;
    loopN = 5000;
    
    for (int i = 0; i < loopN; i++)
    {
        int* data = rampArr<int>(1);
        //int target = randVal(0, dataN);
        int target = dataN -13;
     
        volatile int* idx1;
        volatile int idx2;
        
        
        TIMER.start("findIdx_Normal", NANO);
        //idx1 = findIdx_Normal(data, target , dataN);
        idx1 = std::find(&data[0], &data[dataN], target);
        TIMER.stop();


        TIMER.start("findIdx_SSE", NANO);
        idx2 = findIdx_SSE(data, target , dataN);
        TIMER.stop();
        
        if (*idx1 != idx2)
        {
            cout << "Not match" << endl;
            exit(1);
        }
    }
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 0 5000");
    
}

void exp_Trig()
{
    dataN = 10000;
    loopN = 1000;
    
    for (int l = 0; l< loopN; l++)
    {
        volatile double x1 = 0;
        volatile double x2 = 0;
        TIMER.start("sin_My", MICRO);
        for (int i = 0; i < dataN; i++)
        {
            x1 += sin_Normal(0.5);
        }
        TIMER.stop();

        TIMER.start("sin_Normal", MICRO);
        for (int i = 0; i < dataN; i++)
        {
            x2 += sin(0.5);
        }
        TIMER.stop();
        
        //cout << x1 << " " << x2 << endl;
        
        if (!isEqual(x1, x2))
            cout << "Not Match" << endl;

    }

//    double x = sin(0.5);
//    cout << "Match" << endl;
//    
//    if (isEqual(sin(0.5), sin_Normal(0.5, 20)))
//    {
//        cout << "Match" << endl;
//    }
//    else
//    {
//        cout << "Not Match" << endl;
//    }
    
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 50 0 6000");
    
}

void
exp_strcpy()
{
    dataN = 10001;
    loopN = 10000;
    
    string randStrData = "abcdefghijklmnopqrstuvwxyz";
    
    char* src = new char[dataN];
    char* dist1 = new char[dataN];
    char* dist2 = new char[dataN];
    for (int i = 0; i < dataN -1 ; i++)
        src[i] =  randStrData[randVal(0, (int)randStrData.size()-1)];
    
    for (int l = 0; l< loopN; l++)
    {
        memset(dist1, '\0', dataN);
        memset(dist2, '\0', dataN);
        
        TIMER.start("strcpy_Normal", NANO);
        strcpy(dist1, src);
        TIMER.stop();
        
        TIMER.start("strcpy_SSE", NANO);
        strcpy_SSE(src, dist2, dataN);
        TIMER.stop();
       
    }
    
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 0 3000");
}

void
exp_strcmp()
{
    dataN = 6400;
    loopN = 10000;
    
    string randStrData = "abcdefghijklmnopqrstuvwxyz";
    
    string src="";
    for (int i = 0; i < dataN -1 ; i++)
        src += randStrData[randVal(0, randStrData.size()-1)];
    string target = src;
    //target[dataN - 20] = 'A';
    
    
    for (int l = 0; l< loopN; l++)
    {
        volatile bool find1 = true;
        volatile bool find2 = true;
        
        TIMER.start("strcmp_Normal", NANO);
        find1 = (src == target);
        TIMER.stop();

        TIMER.start("strcmp_SSE", NANO);
        find2 = strcmp_SSE(src.data(), target.data(), dataN);
        TIMER.stop();
        
        //cout << boolalpha << find1 << " " << find2 << endl;
        if (find1 != find2)
        {
            cout << "Not Match" <<endl;
            exit(1);
        }
    }
        
    
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 25 0 260");
}

void
exp_sin()
{
    dataN = 1000;
    loopN = 10000;
    
    int dataNForSSE = dataN/2;
    
    __m128d theta = _mm_set1_pd(0.5);
    for (int l = 0; l< loopN; l++)
    {
        double a;
        __m128d a_m;
        TIMER.start("sin_Normal", NANO);
        for (int i = 0; i<dataN;i++)
            a = sin(0.5);
        TIMER.stop();
        
        TIMER.start("sin_SSE", NANO);
        for (int i = 0; i<dataNForSSE;i++)
            a_m = sin_SSE(theta);
        TIMER.stop();
    }
    
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 0 7000");
}

void
exp_searchUpIndex()
{
//    vector<float> data = {0.2, 1.3, 3.22, 1.3 , 0.44, 4.55, 2.33, 3.33};
//    vector<int> find;
//    findUpIndex_SSE(data, 3, find);
    
  
    dataN = 1024;
    loopN = 1000;

    for (int l = 0; l< loopN; l++)
    {
        vector<float> data(dataN);
        for (size_t i = 0 ; i< dataN; i++)
            data[i] = randVal((float)0, (float)10);

        vector<int> find1, find2;
        float target = 5.0;
      
        TIMER.start("findUpIndex_Normal", NANO);
        searchUpIndex_Normal(data, target, find2);
        TIMER.stop();

        TIMER.start("findUpIndex_SSE", NANO);
        searchUpIndex_SSE(data, target, find1);
        TIMER.stop();
        
//        if (find1.size() != find2.size())
//        {
//            cout << "Size not match" << endl;
//            cout << find1.size() << " " << find2.size() << endl;
//            exit(1);
//        }
//        for (size_t i = 0; i < find1.size(); i++)
//        {
//            if (find1[i] != find2[i])
//            {
//                cout << "Not Match!" << endl;
//                cout << i << ":"<<find1[i] << " " << find2[i] << endl;
//                exit(1);
//            }
//        }
        //cout << find1.size() << " " << find2.size()<< endl;
    }
    TIMER.output("output.csv");
    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 100 0 15000");
    
}

void experiment()
{
    exp();
}
#endif /* Experiment_h */
