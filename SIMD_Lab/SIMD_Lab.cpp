//
//  main.cpp
//  SIMD_Lab
//
//  Created by kayama on 2015/12/28.
//  Copyright © 2015年 kayama. All rights reserved.
//

#include <xmmintrin.h>
#include "MyTimer/MyTimer.h"


using namespace std;
void
func(double* data, double mul, size_t size)
{
    for (int i = 0; i< size ;i++)
        data[i] *= mul;
}

int main(int argc, const char * argv[]) {

    int dataN = 5000;
    double *ar = new double[dataN];
    
    for (int i = 0; i< dataN ;i++)
        ar[i] = (double)i / 10.5;
    
    for (int lp = 0; lp< 10000; lp++)
    {

        TIMER.start("mul", NANO);
    
        for (int i = 0; i< dataN ;i++)
            ar[i] = ar[i] * 0.5;
        
        TIMER.stop();
        
        TIMER.start("diff", NANO);
    
        for (int i = 0; i< dataN ;i++)
            ar[i] = ar[i] / 2.0 * 0.33;
        
        TIMER.stop();
    }
    
    
    TIMER.output("output.csv");

    system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 0 2000");

    
    return 0;
}
