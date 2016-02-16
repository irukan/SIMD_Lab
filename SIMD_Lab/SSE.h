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
strcmp_SSE(const char* data1, const char* data2, int n)
{
    int const end = (n / 32) * 32;

    for(int index = 0; index < end; index += 32)
    {
        __m128i data1A_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data1[index]));
        __m128i data2A_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data2[index]));
        
        __m128i data1B_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data1[index+16]));
        __m128i data2B_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data2[index+16]));
        
        __m128i maskA = _mm_cmpeq_epi32(data1A_m, data2A_m);
        __m128i maskB = _mm_cmpeq_epi32(data1B_m, data2B_m);
        
        if ((_mm_movemask_epi8(maskA) + _mm_movemask_epi8(maskB)) != 131070)
            return false;
    }
    
    //余り
    int remain1 = n - 32;
    int remain2 = n - 16;
    __m128i remain1A_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data1[remain1]));
    __m128i remain2A_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data2[remain1]));
    __m128i maskRemainA = _mm_cmpeq_epi32(remain1A_m, remain2A_m);
    
    __m128i remain1B_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data1[remain2]));
    __m128i remain2B_m = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&data2[remain2]));
    __m128i maskRemainB = _mm_cmpeq_epi32(remain1B_m, remain2B_m);
    
    // 余りで違いがなければtrueを返す。あればfalse
    return (_mm_movemask_epi8(maskRemainA) + _mm_movemask_epi8(maskRemainB)) == 131070;
}

void add_SSE(double* data, double add, size_t n)
{
    __m128d add_m = _mm_set1_pd(add);
    for (size_t i = 0; i < n; i += 2)
    {
        __m128d data_m = _mm_loadu_pd(&data[i]);
        __m128d rslt_m = _mm_add_pd(data_m, add_m);
        _mm_storeu_pd(&data[i],rslt_m);
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

int
findIdx_SSE(int* data, int search, int n)
{
    int const end = (n / 8) * 8;
    __m128i search_m = _mm_set1_epi32(search);
    
    int index = 0;
    for (; index < end; index += 8)
    {
        __m128i dataA_m = _mm_loadu_si128( reinterpret_cast<__m128i*>(&data[index]));
        __m128i dataB_m = _mm_loadu_si128( reinterpret_cast<__m128i*>(&data[index+4]));
        
        // ##### if (data_m == search_m) -> true: 0xFFFFFFFF(-1), false: 0x00000000(0) #####
        __m128i maskA = _mm_cmpeq_epi32(dataA_m, search_m);
        __m128i maskB = _mm_cmpeq_epi32(dataB_m, search_m);

        int movemaskA = _mm_movemask_epi8(maskA);
        int movemaskB = _mm_movemask_epi8(maskB);
        
        if (movemaskA + movemaskB)
            return index + (__builtin_ctz(movemaskB << 16 | movemaskA) >> 2);
    }
    
    return -1;
}


static __inline__ __m128i __attribute__((__always_inline__, __nodebug__))
gather_left_ps(__m128 mask, int* count )
{
    switch (_mm_movemask_ps(mask))
    {
        case 1://1000
            *count = 1;
            return _mm_setzero_si128();
        case 2://0100
            *count = 1;
            return _mm_set1_epi32(1);
        case 3://1100
            *count = 2;
            return _mm_set_epi32(0,0,1,0);
        case 4://0010
            *count = 1;
            return _mm_set1_epi32(2);
        case 5://1010
            *count = 2;
            return _mm_set_epi32(0,0,2,0);
        case 6://0110
            *count = 2;
            return _mm_set_epi32(0,0,2,1);
        case 7://1110
            *count = 3;
            return _mm_set_epi32(0,2,1,0);
        case 8://0001
            *count = 1;
            return _mm_set1_epi32(3);
        case 9://1001
            *count = 2;
            return _mm_set_epi32(0,0,3,0);
        case 10://0101
            *count = 2;
            return _mm_set_epi32(0,0,3,1);
        case 11://1101
            *count = 3;
            return _mm_set_epi32(0,3,1,0);
        case 12://0011
            *count = 2;
            return _mm_set_epi32(0,0,3,2);
        case 13://1011
            *count = 3;
            return _mm_set_epi32(0,3,2,0);
        case 14://0111
            *count = 3;
            return _mm_set_epi32(0,3,2,1);
        case 15://1111
            *count = 4;
            return _mm_set_epi32(3,2,1,0);
            
        default:
        //case 0://0000
            *count = 0;
            return _mm_setzero_si128();
    }
}

inline  void
searchUpIndex_SSE(const std::vector<float>& data, float target, std::vector<int>& dest)
{
    size_t n = data.size();
    size_t const end = (n / 4) * 4;
    dest.resize(n);
    int index = 0;

    int findTempNum = 0;

    __m128 target_m = _mm_set1_ps(target);

    for(; index < end; index += 4)
    {
        __m128 dataA_m = _mm_loadu_ps(&data[index]);
        //__m128 maskA = _mm_cmpgt_ps(dataA_m, target_m);

        int movemaskA = _mm_movemask_ps(_mm_cmpgt_ps(dataA_m, target_m));
        
        if (!movemaskA)
            continue;
        
        switch (movemaskA)
        {
            case 1://1000
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_set1_epi32(index));
                findTempNum += 1;
                break;
            case 2://0100
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_set1_epi32(index+1));
                findTempNum += 1;
                break;
            case 3://1100
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_add_epi32(_mm_set_epi32(0,0,1,0), _mm_set1_epi32(index)));
                findTempNum += 2;
                break;
            case 4://0010
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_set1_epi32(index+2));
                findTempNum += 1;
                break;
            case 5://1010
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_add_epi32(_mm_set_epi32(0,0,2,0), _mm_set1_epi32(index)));
                findTempNum += 2;
                break;
            case 6://0110
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_add_epi32(_mm_set_epi32(0,0,2,1), _mm_set1_epi32(index)));
                findTempNum += 2;
                break;
            case 7://1110
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_add_epi32(_mm_set_epi32(0,2,1,0), _mm_set1_epi32(index)));
                findTempNum += 3;
                break;
            case 8://0001
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_set1_epi32(index+3));
                findTempNum += 1;
                break;
            case 9://1001
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_add_epi32(_mm_set_epi32(0,0,3,0), _mm_set1_epi32(index)));
                findTempNum += 2;
                break;
            case 10://0101
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_add_epi32(_mm_set_epi32(0,0,3,1), _mm_set1_epi32(index)));
                findTempNum += 2;
                break;
            case 11://1101
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_add_epi32(_mm_set_epi32(0,3,1,0), _mm_set1_epi32(index)));
                findTempNum += 3;
                break;
            case 12://0011
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_add_epi32(_mm_set_epi32(0,0,3,2), _mm_set1_epi32(index)));
                findTempNum += 2;
                break;
            case 13://1011
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_add_epi32(_mm_set_epi32(0,3,2,0), _mm_set1_epi32(index)));
                findTempNum += 3;
                break;
            case 14://0111
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_add_epi32(_mm_set_epi32(0,3,2,1), _mm_set1_epi32(index)));
                findTempNum += 3;
                break;
            case 15://1111
                _mm_storeu_si128( reinterpret_cast<__m128i*>(&dest[findTempNum]), _mm_add_epi32(_mm_set_epi32(3,2,1,0), _mm_set1_epi32(index)));
                findTempNum += 4;
                break;
                
           // default:
             //   break;
        }
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
