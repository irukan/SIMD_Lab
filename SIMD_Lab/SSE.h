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

void copy_SSE(double* data, double* dist, size_t n)
{
    if (n % 2 == 0)
    {
        for (size_t i = 0; i < n; i += 2)
        {
            __m128d data_m = _mm_loadu_pd(&data[i]);
            _mm_stream_pd(&dist[i], data_m);
        }
    }
    else
    {
        size_t newSize = n - 2;
        for (size_t i = 0; i < newSize; i += 2)
        {
            // SSE
            __m128d data_m = _mm_loadu_pd(&data[i]);
            _mm_stream_pd(&dist[i], data_m);
        }
        // Normal
        dist[n - 1] = data[n -1];
    }
}

void copy_SSE(int* data, int* dist, size_t n)
{
    if (n % 4 == 0)
    {
        for (size_t i = 0; i < n; i += 4)
        {
            __m128i data_m = _mm_loadu_si128(reinterpret_cast<__m128i*>(&data[i]));
            _mm_stream_si128(reinterpret_cast<__m128i*>(&dist[i]), data_m);
        }
    }
    else
    {
        size_t newSize = n - 4;
        for (size_t i = 0; i < newSize; i += 4)
        {
            //SSE
            __m128i data_m = _mm_loadu_si128(reinterpret_cast<__m128i*>(&data[i]));
            _mm_stream_si128(reinterpret_cast<__m128i*>(&dist[i]), data_m);
        }
        // Normal
        dist[n - 3] = data[n - 3];
        dist[n - 2] = data[n - 2];
        dist[n - 1] = data[n - 1];
    }
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
    //int *result = new __attribute__((aligned(32))) int[4];
    
    int index = 0;
    for (; index < n; index += 4)
    {
        __m128i data_m = _mm_loadu_si128( reinterpret_cast<__m128i*>(&data[index]));
        
        // ##### if (data_m == search_m) -> true: 0xFFFFFFFF(-1), false: 0x00000000(0) #####
        __m128i mask = _mm_cmpeq_epi32(data_m, search_m);
        
        _mm_stream_si128( reinterpret_cast<__m128i*>(&result[0]), mask);
        if ((result[0] + result[1] + result[2] + result[3]) < 0)
            break;
    }
    
    for (int i = 0; i < 4; i++)
    {
        if (result[i] == -1)
            return index;
        index++;
    }
    
    return -1;
}


#endif /* SSE_h */
