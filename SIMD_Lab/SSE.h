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
            __m128d data_m = _mm_load_pd(&data[i]);
            _mm_stream_pd(&dist[i], data_m);
        }
    }
    else
    {
        size_t newSize = n - 2;
        for (size_t i = 0; i < newSize; i += 2)
        {
            // SSE
            __m128d data_m = _mm_load_pd(&data[i]);
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
            __m128i data_m = _mm_load_si128(reinterpret_cast<__m128i*>(&data[i]));
            _mm_stream_si128(reinterpret_cast<__m128i*>(&dist[i]), data_m);
        }
    }
    else
    {
        size_t newSize = n - 4;
        for (size_t i = 0; i < newSize; i += 4)
        {
            //SSE
            __m128i data_m = _mm_load_si128(reinterpret_cast<__m128i*>(&data[i]));
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
    
    __m128d add_m = {add, add};
    
    for (size_t i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_load_pd(&data[i]);
        _mm_stream_pd(&data[i], _mm_add_pd(data_m, add_m));
    }
}

void add_SSE(int* data, int add, size_t n)
{
    __v4si add_m = {add, add, add, add};
    //__m128i add_m = {add, add};
    
    for (size_t i = 0; i < n; i += 4)
    {
        __m128i data_m = _mm_load_si128( reinterpret_cast<__m128i*>(&data[i]));
        _mm_stream_si128( reinterpret_cast<__m128i*>(&data[i]), _mm_add_epi32( data_m, add_m ) );
    }
}

void addCopy_SSE(double* data, double* dist, double add, size_t n)
{
    __m128d add_m = {add, add};
    for (size_t i = 0; i < n; i += 2)
    {
        _mm_stream_pd(&dist[i], _mm_add_pd(_mm_load_pd(&data[i]), add_m));
    }
}

void sub_SSE(double* data, double sub, size_t n)
{
    __m128d sub_m = {sub, sub};
    for (size_t i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_load_pd(&data[i]);
        _mm_stream_pd(&data[i], _mm_sub_pd(data_m, sub_m));
    }
}

void mul_SSE(double* data, double mul, size_t n)
{
    __m128d mul_m = {mul, mul};
    for (size_t i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_load_pd(&data[i]);
        _mm_stream_pd(&data[i], _mm_mul_pd(data_m, mul_m));
    }
}

void div_SSE(double* data, double div, size_t n)
{
    __m128d div_m = {div, div};
    for (size_t i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_load_pd(&data[i]);
        _mm_stream_pd(&data[i], _mm_div_pd(data_m, div_m));
    }
}

double
inline max_SSE(double* data, size_t n)
{
    __m128d max = _mm_load_pd(&data[0]);
    
    for (int i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_load_pd(&data[i]);
        max = _mm_max_pd(max, data_m);
    }
    
    double ret[2];
    _mm_stream_pd(ret, max);
    
    return std::max(ret[0], ret[1]);
}



#endif /* SSE_h */
