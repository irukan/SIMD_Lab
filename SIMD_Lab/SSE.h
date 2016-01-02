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
    size_t const end = (n / 16) * 16;
    size_t index = 0;

    for(; index < end; index += 16)
    {
        __m128i data1_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data1[index]));
        __m128i data2_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data2[index]));
        
        __m128i mask = _mm_cmpeq_epi32(data1_m, data2_m);
        
        if ((mask[0] + mask[1]) != -2)
            return false;
    }
    //余りは、Normal演算
    for(; index < n; ++index)
    {
        if (data1[index] != data2[index])
            return false;
    }
    
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
#endif /* SSE_h */
