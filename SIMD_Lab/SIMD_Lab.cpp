//
//  main.cpp
//  SIMD_Lab
//
//  Created by kayama on 2015/12/28.
//  Copyright © 2015年 kayama. All rights reserved.
//

#include <xmmintrin.h>
#include "MyTimer/MyTimer.h"
#include <vector>
MyTimer *timer;

using namespace std;
void
func(double* data, double mul, size_t size)
{
    for (int i = 0; i< size ;i++)
        data[i] *= mul;
}

int main(int argc, const char * argv[]) {

    timer = new MyTimer();
    
    int dataN = 5000;
    vector<double> ar;
    
    for (int i = 0; i< dataN ;i++)
        ar.push_back(i/10.5);
    
    for (int lp = 0; lp< 10000; lp++)
    {

        timer->start("to_string", NANO);
    
        for (int i = 0; i< dataN ;i++)
            ar[i] = ar[i] * 2 * 5;
        
        timer->stop();
    }
    
    timer->output("output.csv");
    return 0;
}
