//Author: Sören Pirk
//Date: 22.01.2013

#ifndef VECTOR3
#define VECTOR3

#include <math.h>
#include <stdio.h>

class Vector3;

Vector3 cross(const Vector3 &a, const Vector3 &b);
Vector3 operator *(double s, const Vector3 &v);
Vector3 normalize(Vector3 &v);
double   dot(const Vector3 &a, const Vector3 &b);
double   length(const Vector3 &v);

class Vector2;
class Vector3
{

public:
    Vector3();
    Vector3(double x, double y, double z);
    Vector3(const Vector3 &v);
    Vector3(const double *v);
	Vector3(const Vector2 v);
    ~Vector3();

    double length();
    double dot(const Vector3 &vec);
    double angle(Vector3 &vec);
    Vector3 cross(const Vector3 &vec);
    Vector3 normalized();
    void normalize();
    void set(double x, double y, double z);
    void set(double *vec);
	Vector2 toVector2()const;

    Vector3 mulMatrix(double *matrix);

    Vector3 &get();

    void print();

    //Assignment
    Vector3 &operator =  (const Vector3 &a);
    Vector3 &operator += (const Vector3 &a);
    Vector3 &operator += (double s);
    Vector3 &operator -= (const Vector3 &a);
    Vector3 &operator -= (double s);
    Vector3 &operator *= (const Vector3 &a);
    Vector3 &operator *= (double s);
    Vector3 &operator /= (const Vector3 &a);
    Vector3 &operator /= (double s);

    //Arithmetic
    friend Vector3 operator + (const Vector3 &a, const Vector3 &b);
    friend Vector3 operator + (const Vector3 &a, double s);
    friend Vector3 operator + (double s, const Vector3 &a);
    friend Vector3 operator - (const Vector3 &a, const Vector3 &b);
    friend Vector3 operator - (const Vector3 &a, double s);
    friend Vector3 operator - (const Vector3 &a);
	friend Vector3 operator * (const Vector3 &a, const Vector3 &b);
    friend Vector3 operator * (const Vector3 &a, double s);
    friend Vector3 operator * (double s, const Vector3 &a);
    friend Vector3 operator / (const Vector3 &a, const Vector3 &b);
    friend Vector3 operator / (const Vector3 &a, double s);

    //Comparison
    friend bool operator == (const Vector3 &a, const Vector3 &b);
    friend bool operator != (const Vector3 &a, const Vector3 &b);
    friend bool operator <= (const Vector3 &a, const Vector3 &b);
    friend bool operator <  (const Vector3 &a, const Vector3 &b);
    friend bool operator >= (const Vector3 &a, const Vector3 &b);
    friend bool operator >  (const Vector3 &a, const Vector3 &b);

    double x;
    double y;
    double z;
};


#endif
