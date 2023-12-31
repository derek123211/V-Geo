//
// Created by 11914 on 2022/10/17.
//

#ifndef MYPROJECT_VECTOR2_H
#define MYPROJECT_VECTOR2_H

//定义点类
#include "numeric.h"

#include <iostream>
#include <cmath>

template <typename T>
class Vector2
{
public:

    // Constructors  构造函数
    Vector2():x(0), y(0){}
    Vector2(T _x, T _y): x(_x), y(_y){}
    Vector2(const Vector2 &v): x(v.x), y(v.y){}

    // Operations
    // 计算距离
    T dist2(const Vector2 &v) const
    {
        T dx = x - v.x;
        T dy = y - v.y;
        return dx * dx + dy * dy;
    }

    T dist(const Vector2 &v) const
    {
        return sqrt(dist2(v));
    }

    //计算平方和，此函数在 delaunay.h 中判断一点是否在三角形内部
    T norm2() const
    {
        return x * x + y * y;
    }

    T x;
    T y;
};


template <>
float Vector2<float>::dist(const Vector2<float> &v) const { return hypotf(x - v.x, y - v.y);}

template <>
double Vector2<double>::dist(const Vector2<double> &v) const { return hypotf(x - v.x, y - v.y);}

template<typename T>
std::ostream &operator << (std::ostream &str, Vector2<T> const &point)
{
    return str << "Point x: " << point.x << " y: " << point.y;
}

template<typename T>
bool operator == (const Vector2<T>& v1, const Vector2<T>& v2)
{
    return (v1.x == v2.x) && (v1.y == v2.y);
}

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(const Vector2<T>& v1, const Vector2<T>& v2, int ulp=2)
{
    return almost_equal(v1.x, v2.x, ulp) && almost_equal(v1.y, v2.y, ulp);
}

#endif //MYPROJECT_VECTOR2_H
