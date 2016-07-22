//Author: Sören Pirk
//Date: 22.01.2013

#ifndef VECTOR2
#define VECTOR2

#include <math.h>
#include <stdio.h>

class Vector2;

double cross(const Vector2 &a, const Vector2 &b);
Vector2 operator *(double s, const Vector2 &v);
Vector2 normalize(Vector2 &v);
double   dot(const Vector2 &a, const Vector2 &b);
double   length(const Vector2 &v);

class Vector2
{

public:
    Vector2();
    Vector2(double x, double y);
    Vector2(const Vector2 &v);
    Vector2(const double *v);
    ~Vector2();

    double length()const;
    double dot(const Vector2 &vec);
    double angle(Vector2 &vec);
    double cross(const Vector2 &vec);
    Vector2 normalized();
    void normalize();
    void set(double x, double y);
    void set(double *vec);

    Vector2 mulMatrix(double *matrix);
    Vector2 &get();

    void print();

    //Assignment
    Vector2 &operator =  (const Vector2 &a);
    Vector2 &operator += (const Vector2 &a);
    Vector2 &operator += (double s);
    Vector2 &operator -= (const Vector2 &a);
    Vector2 &operator -= (double s);
    Vector2 &operator *= (const Vector2 &a);
    Vector2 &operator *= (double s);
    Vector2 &operator /= (const Vector2 &a);
    Vector2 &operator /= (double s);

    //Arithmetic
    friend Vector2 operator + (const Vector2 &a, const Vector2 &b);
    friend Vector2 operator + (const Vector2 &a, double s);
    friend Vector2 operator + (double s, const Vector2 &a);
    friend Vector2 operator - (const Vector2 &a, const Vector2 &b);
    friend Vector2 operator - (const Vector2 &a, double s);
    friend Vector2 operator - (const Vector2 &a);
    friend Vector2 operator * (const Vector2 &a, const Vector2 &b);
    friend Vector2 operator * (const Vector2 &a, double s);
    friend Vector2 operator * (double s, const Vector2 &a);
    friend Vector2 operator / (const Vector2 &a, const Vector2 &b);
    friend Vector2 operator / (const Vector2 &a, double s);

    //Comparison
    friend bool operator == (const Vector2 &a, const Vector2 &b);
    friend bool operator != (const Vector2 &a, const Vector2 &b);
    friend bool operator <= (const Vector2 &a, const Vector2 &b);
    friend bool operator <  (const Vector2 &a, const Vector2 &b);
    friend bool operator >= (const Vector2 &a, const Vector2 &b);
    friend bool operator >  (const Vector2 &a, const Vector2 &b);

    double x;
    double y;
};


#endif
