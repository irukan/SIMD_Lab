//
//  Normal.h
//  SIMD_Lab
//
//  Created by kayama on 2015/12/30.
//  Copyright © 2015年 kayama. All rights reserved.
//

#ifndef Normal_h
#define Normal_h

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

double
sin_Normal(double sita, int rank)
{
    double ret = 0.0;

//    int ruijo = 1;
//    
//    for (int i = 0; i< rank; i++)
//    {
//        ret += power(sita, ruijo) * 1.0/ (double)factorial(ruijo) * ( i %2 == 0 ? 1: -1);
//        ruijo += 2;
//    }
    
    ret += sita;
    ret -= 0.16666666666 * sita * sita * sita;
    ret += 0.00833333333 * sita * sita * sita * sita * sita;
    ret -= 0.00018518518 * sita * sita * sita * sita * sita * sita * sita;
    return ret;
}
#endif /* Normal_h */
