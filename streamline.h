#ifndef STREAMLINE_H_INCLUDED
#define STREAMLINE_H_INCLUDED

#include "Vector2.h"
#include "Vector3.h"
#include <vector>
#include <deque>

typedef Vector3 vec3;
typedef Vector2 vec2;

template <typename TA, typename TB, typename TC>
TA clamp( const TA &x, const TB &minval, const TC &maxval ) {
    if( x < (TA)minval )
        return (TA)minval;
    else if( x > (TA)maxval )
        return (TA)maxval;
    else
        return x;
}

struct StreamLineParam
{
    double alpha;
    double dMin;
    double dSep;
    double dSelfsep;
    double w;
    double minLen;
    double maxLen;

    int nHalfSample;
    int maxSize;

    void print()const;
};

struct Line
{
    std::deque<vec3> path;
    std::vector<vec2> pathDir;
    double getLength()const;
};

extern vec2 m_minDims;
extern vec2 m_maxDims;
extern StreamLineParam g_param;

#endif // STREAMLINE_H_INCLUDED
