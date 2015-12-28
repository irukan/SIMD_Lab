//
//  main.cpp
//  SIMD_Lab
//
//  Created by kayama on 2015/12/28.
//  Copyright © 2015年 kayama. All rights reserved.
//

#include <iostream>
#include <xmmintrin.h>
#include "MyTimer/MyTimer.h"


int main(int argc, const char * argv[]) {

    {
        AutoTimer("test", NANO);
        // 重い処理
        long long j = 0;
        for(int i = 1; i <= 100; ++i)
        {
            j += i;
        }
    }
    
    
    return 0;
}
