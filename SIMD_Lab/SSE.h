//
//  SSE.h
//  SIMD_Lab
//
//  Created by kayama on 2015/12/30.
//  Copyright © 2015年 kayama. All rights reserved.
//&&

#ifndef SSE_h
#define SSE_h
#include <xmmintrin.h>
#include <tmmintrin.h>
//#include <smmintrin.h>
#include <string>

void
copy_SSE(double* data, double* dist, size_t n)
{
    size_t const end = (n / 2) * 2;
    
    size_t index = 0;
    for(; index < end; index += 2)
    {
        __m128d data_m = _mm_loadu_pd(&data[index]);
        _mm_stream_pd(&dist[index], data_m);
    }
    // 余りは、Normal演算
    for(; index < n; ++index)
        dist[index] = data[index];
}

void
copy_SSE(int* data, int* dist, size_t n)
{
    size_t const end = (n / 4) * 4;
    
    size_t index = 0;
    for(; index < end; index += 4)
    {
        __m128i data_m = _mm_loadu_si128(reinterpret_cast<__m128i*>(&data[index]));
        _mm_stream_si128(reinterpret_cast<__m128i*>(&dist[index]), data_m);
    }
    // 余りは、Normal演算
    for(; index < n; ++index)
        dist[index] = data[index];
}

void
strcpy_SSE(const char* data, char* dist, size_t n)
{
    size_t const end = (n / 16) * 16;
    
    size_t index = 0;
    for(; index < end; index += 16)
    {
        __m128i data_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data[index]));
        _mm_stream_si128(reinterpret_cast<__m128i*>(&dist[index]), data_m);
    }
    //余りは、Normal演算
    for(; index < n; ++index)
        dist[index] = data[index];
}

bool
strcmp_SSE(const char* data1, const char* data2, size_t n)
{
    //size_t const end = (n / 32) * 32;
    size_t index = 0;

    for(; index < n; index += 32)
    {
        __m128i data1A_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data1[index]));
        __m128i data2A_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data2[index]));
        __m128i maskA = _mm_cmpeq_epi32(data1A_m, data2A_m);
        
        __m128i data1B_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data1[index+16]));
        __m128i data2B_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data2[index+16]));
        __m128i maskB = _mm_cmpeq_epi32(data1B_m, data2B_m);
        
        
        if ((maskA[0] + maskA[1] + maskB[0] + maskB[1]) != -4)
            return false;
    }
    //余りは、Normal演算
//    for(; index < n; ++index)
//    {
//        if (data1[index] != data2[index])
//            return false;
//    }
//    
    return 0;
}

void add_SSE(double* data, double add, size_t n)
{
    __m128d add_m = _mm_set1_pd(add);
    for (size_t i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_loadu_pd(&data[i]);
        _mm_stream_pd(&data[i], _mm_add_pd(data_m, add_m));
    }
}

void add_mul_SSE(double* data, double add, double mul, size_t n)
{
    __m128d add_m = _mm_set1_pd(add);
    __m128d mul_m = _mm_set1_pd(mul);
    for (size_t i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_loadu_pd(&data[i]);
        __m128d ret = _mm_add_pd(data_m, add_m);
        ret = _mm_mul_pd(ret, mul_m);
        _mm_stream_pd(&data[i], ret);
    }
}

void add_SSE(int* data, int add, size_t n)
{
    __m128i add_m = _mm_set1_epi32(add);
    for (size_t i = 0; i < n; i += 4)
    {
        __m128i data_m = _mm_load_si128( reinterpret_cast<__m128i*>(&data[i]));
        _mm_stream_si128( reinterpret_cast<__m128i*>(&data[i]), _mm_add_epi32( data_m, add_m ) );
    }
}

void addCopy_SSE(double* data, double* dist, double add, size_t n)
{
    __m128d add_m = _mm_set1_pd(add);
    for (size_t i = 0; i < n; i += 2)
    {
        _mm_stream_pd(&dist[i], _mm_add_pd(_mm_loadu_pd(&data[i]), add_m));
    }
}

void sub_SSE(double* data, double sub, size_t n)
{
    __m128d sub_m = _mm_set1_pd(sub);
    for (size_t i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_loadu_pd(&data[i]);
        _mm_stream_pd(&data[i], _mm_sub_pd(data_m, sub_m));
    }
}

void mul_SSE(double* data, double mul, size_t n)
{
    __m128d mul_m = _mm_set1_pd(mul);
    for (size_t i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_loadu_pd(&data[i]);
        _mm_stream_pd(&data[i], _mm_mul_pd(data_m, mul_m));
    }
}

void div_SSE(double* data, double div, size_t n)
{
    __m128d div_m = _mm_set1_pd(div);
    for (size_t i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_loadu_pd(&data[i]);
        _mm_stream_pd(&data[i], _mm_div_pd(data_m, div_m));
    }
}

double
max_SSE(double* data, size_t n)
{
    __m128d max = _mm_loadu_pd(&data[0]);
    
    for (int i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_loadu_pd(&data[i]);
        max = _mm_max_pd(max, data_m);
    }
    
    double ret[2];
    _mm_stream_pd(ret, max);
    
    return std::max(ret[0], ret[1]);
}

double
max_SSE2(double* data, size_t n)
{
    __m128d max = _mm_loadu_pd(&data[0]);
    
    for (int i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_loadu_pd(&data[i]);
        max = _mm_max_pd(max, data_m);
    }
    
    double ret[2];
    _mm_stream_pd(ret, max);
    
    return std::max(ret[0], ret[1]);
}

int
findIdx_SSE(int* data, int search, size_t n)
{
    __m128i search_m = _mm_set1_epi32(search);
    
    int result[4];
    //__attribute__((aligned(16)))int result[4];
    
    int index = 0;
    for (; index < n; index += 4)
    {
        __m128i data_m = _mm_loadu_si128( reinterpret_cast<__m128i*>(&data[index]));
        
        // ##### if (data_m == search_m) -> true: 0xFFFFFFFF(-1), false: 0x00000000(0) #####
        __m128i mask = _mm_cmpeq_epi32(data_m, search_m);
        
        if ((mask[0] + mask[1]) != 0)
        {
            _mm_stream_si128( reinterpret_cast<__m128i*>(&result[0]), mask);
            break;
        }
    }
    
    for (int i = 0; i < 4; i++)
    {
        if (result[i] == -1)
            return index;
        index++;
    }
    
    return -1;
}

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

//

static __inline__ __m128i __attribute__((__always_inline__, __nodebug__))
gather_left_ps(__m128i data, __m128 mask, int* count )
{ 
    switch (_mm_movemask_ps(mask)) {

        case 1:
            *count = 1;
            //return _mm_shuffle_epi32(data, _MM_SHUFFLE(3,2,1,0));
            return data;
        case 2:
            *count = 1;
            return _mm_shuffle_epi32(data, _MM_SHUFFLE(3,2,0,1));
        case 3:
            *count = 2;
            //return _mm_shuffle_epi32(data, _MM_SHUFFLE(3,2,1,0));
            return data;
        case 4:
            *count = 1;
            return _mm_shuffle_epi32(data, _MM_SHUFFLE(3,1,0,2));
        case 5:
            *count = 2;
            return _mm_shuffle_epi32(data, _MM_SHUFFLE(3,1,2,0));
        case 6:
            *count = 2;
            return _mm_shuffle_epi32(data, _MM_SHUFFLE(3,0,2,1));
        case 7:
            *count = 3;
            //return _mm_shuffle_epi32(data, _MM_SHUFFLE(3,2,1,0));
            return data;
        case 8:
            *count = 1;
            return _mm_shuffle_epi32(data, _MM_SHUFFLE(2,1,0,3));
        case 9:
            *count = 2;
            return _mm_shuffle_epi32(data, _MM_SHUFFLE(2,1,3,0));
        case 10:
            *count = 2;
            return _mm_shuffle_epi32(data, _MM_SHUFFLE(2,0,3,1));
        case 11:
            *count = 3;
            return _mm_shuffle_epi32(data, _MM_SHUFFLE(2,3,1,0));
        case 12:
            *count = 2;
            return _mm_shuffle_epi32(data, _MM_SHUFFLE(1,0,3,2));
        case 13:
            *count = 3;
            return _mm_shuffle_epi32(data, _MM_SHUFFLE(1,3,2,0));
        case 14:
            *count = 3;
            return _mm_shuffle_epi32(data, _MM_SHUFFLE(0,3,2,1));
        case 15:
            *count = 4;
            //return _mm_shuffle_epi32(data, _MM_SHUFFLE(3,2,1,0));
            return data;
            
        default:
        //case 0:
            *count = 0;
            //return _mm_shuffle_epi32(data, _MM_SHUFFLE(3,2,1,0));
            return data;
    }
}

inline  void
findUpIndex_SSE(const std::vector<float>& data, float target, std::vector<int>& dest)
{
    size_t n = data.size();
    size_t const end = (n / 4) * 4;
    dest.resize(end);
    int index = 0;

    int findTempNum = 0;

    __m128 target_m = _mm_set1_ps(target);
    __m128i index_m = _mm_set_epi32(3, 2, 1, 0);
    __m128i incVal_m = _mm_set1_epi32(4);
    
    int getCnt = 0;
    for(; index < end; index += 4)
    {
        __m128 data_m = _mm_loadu_ps(&data[index]);
        __m128 mask = _mm_cmpgt_ps(data_m, target_m);

        __m128i conv = gather_left_ps(index_m, mask, &getCnt);
        if (getCnt != 0)
        {
            _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), conv );
            findTempNum += getCnt;
        }
        index_m = _mm_add_epi32(index_m, incVal_m);
    }
    
    dest.resize(findTempNum);
}

void exp()
{
    __m128d one = _mm_set1_pd(1.0);
    
    
    int movemask1 = _mm_movemask_pd(_mm_cmpeq_pd(one, _mm_set_pd(0, 0)));
    int movemask2 = _mm_movemask_pd(_mm_cmpeq_pd(one, _mm_set_pd(0, 1)));
    int movemask3 = _mm_movemask_pd(_mm_cmpeq_pd(one, _mm_set_pd(1, 0)));
    int movemask4 = _mm_movemask_pd(_mm_cmpeq_pd(one, _mm_set_pd(1, 1)));
    
}


#endif /* SSE_h */
