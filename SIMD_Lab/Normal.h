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

#endif /* Normal_h */
