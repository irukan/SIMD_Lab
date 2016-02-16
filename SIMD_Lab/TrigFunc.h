//
//  TrigFunc.h
//  SIMD_Lab
//
//  Created by kayama on 2016/02/11.
//  Copyright © 2016年 kayama. All rights reserved.
//

#ifndef TrigFunc_h
#define TrigFunc_h


inline __m128d
sin_SSE(__m128d th_m)
{
    //__m128d th_m = {th1, th2};
    __m128d sum = th_m;//{th1, th2};
    
    // 2次
    th_m = _mm_mul_pd(th_m, th_m);
    th_m = _mm_mul_pd(th_m, th_m);
    __m128d two = _mm_set1_pd(0.16666666666);
    sum =  _mm_add_pd(sum, _mm_mul_pd(th_m, two));
    
    // 3次
    th_m = _mm_mul_pd(th_m, th_m);
    th_m = _mm_mul_pd(th_m, th_m);
    __m128d three = _mm_set1_pd(0.00833333333);
    sum = _mm_add_pd(sum, _mm_mul_pd(th_m, three));
    //
    //    // 4次
    //    th_m = _mm_mul_pd(th_m, th_m);
    //    th_m = _mm_mul_pd(th_m, th_m);
    //    __m128d four = _mm_set1_pd(0.00018518518);
    //    sum = _mm_sub_pd(sum, _mm_mul_pd(th_m, four));
    
    
    return sum;
}

#endif /* TrigFunc_h */
