//
//  Normal.h
//  SIMD_Lab
//
//  Created by kayama on 2015/12/30.
//  Copyright © 2015年 kayama. All rights reserved.
//

#ifndef Normal_h
#define Normal_h

#include <vector>
#include <math.h>

template<typename T>
void copy_Normal(T* data, T* dist, size_t n)
{
    for (size_t i = 0; i < n; i++)
        dist[i] = data[i];
}

template<typename T>
void add_Normal(T* data, T add, size_t n)
{
    for (size_t i = 0; i < n; i++)
        data[i] += add;
}

template<typename T>
void sub_Normal(T* data, T sub, size_t n)
{
    for (size_t i = 0; i < n; i++)
        data[i] -= sub;
}

template<typename T>
void mul_Normal(T* data, T mul, size_t n)
{
    for (size_t i = 0; i < n; i++)
        data[i] *= mul;
}

template<typename T>
void div_Normal(T* data, T div, size_t n)
{
    for (size_t i = 0; i < n; i++)
        data[i] /= div;
}

template<typename T>
void add_mul_Normal(T* data, T add, T mul, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        data[i] += add;
        data[i] *= mul;        
    }
}

template<typename T>
double max_Normal(T* data, size_t n)
{
    T max = data[0];
    
    for (int i = 0; i < n; i++)
        max = std::max(max, data[i]);
    
    return max;
}

template<typename T>
int findIdx_Normal(T* data, T search, size_t n)
{
    int index;
    for (index = 0; index < n; index++)
    {
        if (data[index] == search)
            return index;
    }
    
    return -1;
}

int factorial(int n) {
    if (n > 0) {
        return n * factorial(n - 1);
    } else {
        return 1;
    }
}

double power(double data, int n)
{
    double ret = 1;
    for (int i = 0; i< n; i++)
        ret *= data;
    return ret;
}

inline double
sin_Normal(double sita)
{
    double ret = 0.0;

    int ruijo = 1;
    
    for (int i = 0; i< 6; i++)
    {
        ret += power(sita, ruijo) * 1.0/ (double)factorial(ruijo) * ( i %2 == 0 ? 1: -1);
        ruijo += 2;
    }
    
//    ret += sita;
//    ret -= 0.16666666666 * sita * sita * sita;
//    ret += 0.00833333333 * sita * sita * sita * sita * sita;
//    ret -= 0.00018518518 * sita * sita * sita * sita * sita * sita * sita;
    return ret;
}

int
strcmp_Normal(const char *s1, const char *s2)
{
    for ( ; *s1 == *s2; s1++, s2++)
    if (*s1 == '\0')
    return 0;
    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}

static inline constexpr bool lt(char __c1, char __c2) _NOEXCEPT
{return __c1 < __c2;}

static inline int
Mymemcmp(const char * s1,const char * s2, size_t n)
{
    unsigned char u1, u2;
    
    for ( ; n-- ; s1++, s2++) {
        u1 = * (unsigned char *) s1;
        u2 = * (unsigned char *) s2;
        if ( u1 != u2) {
            return (u1-u2);
        }
    }
    return 0;
}

#include "SSE.h"
int
compare(const char* __s1, const char* __s2, size_t __n)
{
//    for (; __n; --__n, ++__s1, ++__s2)
//    {
//        if (lt(*__s1, *__s2))
//        return -1;
//        if (lt(*__s2, *__s1))
//        return 1;
//    }
//    return 0;
    
    return __n == 0 ? 0 : memcmp(__s1, __s2, __n);
    //return __n == 0 ? 0 : strcmp(__s1, __s2);
}

inline bool
strcmp_Normal2(const std::string& s1, const std::string& s2)
{
    size_t n = s1.size();

    return n == s2.size() && compare(s1.data(),s2.data(), n) == 0;
}

inline bool
strcmp_Normal3(const std::string& __lhs, const std::string& __rhs)
{
    size_t __lhs_sz = __lhs.size();
    if (__lhs_sz != __rhs.size())
    return false;
    const char* __lp = __lhs.data();
    const char* __rp = __rhs.data();
    if (__lhs.__is_long())
    //return compare(__lp, __rp, __lhs_sz) == 0;
    return compare(__lp, __rp, __lhs_sz) == 0;
    for (; __lhs_sz != 0; --__lhs_sz, ++__lp, ++__rp)
    if (*__lp != *__rp)
    return false;
    return true;
}


template<typename T>
void searchUpIndex_Normal(const std::vector<T>& data, T target, std::vector<int>& dest)
{
    size_t n = data.size();
    size_t const end = (n / 4) * 4;
    dest.resize(n);

    //int* temp = new int[n];
    int findNum=0;
    for (int i = 0; i< end; i++)
    {
        if (data[i] > target)
        {
            dest[findNum++] = i;
            //dest.push_back(i);
            //temp[findNum] = i;
            //findNum++;
        }
    }
    
    //dest = std::vector<int>(temp, &temp[findNum]);
    //delete [] temp;
}

#endif /* Normal_h */
