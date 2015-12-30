//
//  main.cpp
//  SIMD_Lab
//
//  Created by kayama on 2015/12/28.
//  Copyright © 2015年 kayama. All rights reserved.
//


#include "MyTimer/MyTimer.h"

#include "SSE.h"
#include "Normal.h"


using namespace std;


int  main(int argc, const char * argv[]) {

    int dataN = 7001;
    double *ar1 = new double[dataN];
    double *ar2 = new double[dataN];
    
    double *target1 = new double[dataN];
    double *target2 = new double[dataN];
    
    
    for (int i = 0; i< dataN ;i++)
    {
        ar1[i] = (double)i / 10.5;
        ar2[i] = (double)i / 10.5;
    }
    
    for (int lp = 0; lp< 100000; lp++)
    {
        
        TIMER.start("add_Normal", NANO);
        add_Normal(ar1, 0.1, dataN);
        TIMER.stop();
        
        
        TIMER.start("add_SSE", NANO);
        add_SSE(ar2, 0.1, dataN);
        TIMER.stop();
        
        TIMER.start("add_SSE2", NANO);
        add_SSE2(ar1, 0.1, dataN);
        TIMER.stop();
        //        TIMER.start("copy_Normal", NANO);
        //        copy_Normal(ar1, target1, dataN);
        //        TIMER.stop();
        //
        //        TIMER.start("copy_SSE", NANO);
        //        copy_SSE(ar2, target2, dataN);
        //        TIMER.stop();
        //
        //
        //        TIMER.start("copy_SSE + add", NANO);
        //add_SSE(ar1, 0.1, dataN);
        //        copy_SSE(ar1, target1, dataN);
        //        TIMER.stop();
        //
        //
        //        TIMER.start("addCopy_SSE", NANO);
        //        addCopy_SSE(ar1, target1, 0.1,dataN);
        //        TIMER.stop();
        
        //        double m1 = 0;
        //        double m2 = 0;
        //
        //        TIMER.start("Normal", NANO);
        //        m1 = max_Normal(ar1, dataN);
        //        TIMER.stop();
        //
        //        TIMER.start("SSE", NANO);
        //        m2 = max_SSE(ar2, dataN);
        //        TIMER.stop();
        
    }
    
    TIMER.output("output.csv");

    //system("python Analysis/DispPlot.py output.csv");
    system("python Analysis/DispHist.py output.csv 0 17000");

    
    return 0;
}
