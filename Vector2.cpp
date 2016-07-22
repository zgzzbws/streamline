//Author: Sören Pirk
//Date: 22.01.2013

#include "Vector2.h"

Vector2::Vector2() 
: x(0.0),
  y(0.0)
{
}

Vector2::Vector2(double x, double y)
{
   this->x = x;
   this->y = y;
}

Vector2::Vector2(const Vector2 &v)
{
   this->x = v.x;
   this->y = v.y;
}

Vector2::Vector2(const double *v)
{
   this->x = v[0];
   this->y = v[1];
}

Vector2::~Vector2() 
{
}

double Vector2::length()const
{
   double length = 0.0f;

   length = sqrtf((this->x * this->x) + (this->y * this->y));

   return length;
}

double Vector2::dot(const Vector2 &vec)
{
   double dot = 0.0f;

   dot = (this->x * vec.x) + (this->y * vec.y);

   return dot;
}

double Vector2::angle(Vector2 &vec)
{
    double d = this->dot(vec);

    double a = this->length();    
    double b = vec.length();

    double s = d / (a*b);
    double angle = (double)acos((double)s);

    return angle;
}

double Vector2::cross(const Vector2 &vec)
{
   return (this->x * vec.y - this->y * vec.x);
}

void Vector2::normalize()
{
   double len = this->length();

   if(len > 0.0f)
   {
       this->x = this->x / len;
       this->y = this->y / len;  
   }
}

Vector2 Vector2::normalized()
{
   double len = this->length();
   Vector2 normalized; 

   if(len > 0.0)
   {
       normalized.x = this->x / len;
       normalized.y = this->y / len;  
   }

   return normalized;
}

void Vector2::set(double x, double y)
{
   this->x = x;
   this->y = y;
}

void Vector2::set(double *vec)
{
   this->x = vec[0];
   this->y = vec[1];
}

Vector2 &Vector2::get()
{
    return *this;
}

void Vector2::print()
{
    printf("x: %f, y: %f\n", x, y);
}

Vector2 &Vector2::operator =(const Vector2 &a)
{
   this->x = a.x;
   this->y = a.y;

   return *this;
}

Vector2 &Vector2::operator +=(const Vector2 &a)
{
   this->x += a.x;
   this->y += a.y;

   return *this;
}

Vector2 &Vector2::operator +=(double s)
{
   this->x += s;
   this->y += s;

   return *this;
}

Vector2 &Vector2::operator -=(const Vector2 &a)
{
   this->x -= a.x;
   this->y -= a.y;

   return *this;
}

Vector2 &Vector2::operator -=(double s)
{
   this->x -= s;
   this->y -= s;

   return *this;
}

Vector2 &Vector2::operator *=(const Vector2 &a)
{
   this->x *= a.x;
   this->y *= a.y;

   return *this;
}

Vector2 &Vector2::operator *=(double s)
{
   this->x *= s;
   this->y *= s;

   return *this;
}

Vector2 &Vector2::operator /=(const Vector2 &a)
{
   this->x /= a.x;
   this->y /= a.y;
   
   return *this;
}

Vector2 &Vector2::operator /=(double s)
{
   this->x /= s;
   this->y /= s;

   return *this;
}

//-----------------------------------------------------------------------------------------------

Vector2 operator +(const Vector2 &a, const Vector2 &b)
{
   Vector2 r;

   r.x = a.x + b.x;
   r.y = a.y + b.y;

   return r;
}

Vector2 operator +(const Vector2 &a, double s)
{
   Vector2 r;

   r.x = a.x + s;
   r.y = a.y + s;

   return r;
}

Vector2 operator +(double s, const Vector2 &a)
{
   Vector2 r;

   r.x = a.x + s;
   r.y = a.y + s;

   return r;
}

Vector2 operator -(const Vector2 &a, const Vector2 &b)
{
   Vector2 r;

   r.x = a.x - b.x;
   r.y = a.y - b.y;

   return r;
}

Vector2 operator -(const Vector2 &a, double s)
{
   Vector2 r;

   r.x = a.x - s;
   r.y = a.y - s;

   return r;
}


Vector2 operator -(const Vector2 &a)
{
    Vector2 r;
	
	r.x = -a.x;
	r.y = -a.y;
	
	return r;
}

Vector2 operator *(const Vector2 &a, double s)
{
   Vector2 r;

   r.x = a.x * s;
   r.y = a.y * s;

   return r;
}

Vector2 operator *(const Vector2 &a, const Vector2 &b)
{
   Vector2 r;

   r.x = a.x * b.x;
   r.y = a.y * b.y;

   return r;
}

Vector2 operator /(const Vector2 &a, double s)
{
   Vector2 r;

   r.x = a.x / s;
   r.y = a.y / s;

   return r;
}

Vector2 operator /(const Vector2 &a, const Vector2 &b)
{
   Vector2 r;

   r.x = a.x / b.x;
   r.y = a.y / b.y;

   return r;
}

//-----------------------------------------------------------------------------------------------

bool operator == (const Vector2 &a, const Vector2 &b)
{
    return(a.x == b.x && a.y == b.y);
}

bool operator != (const Vector2 &a, const Vector2 &b)
{
    return(a.x != b.x || a.y != b.y);
}

bool operator <= (const Vector2 &a, const Vector2 &b)
{
    return(a.x <= b.x && a.y <= b.y);
}

bool operator < (const Vector2 &a, const Vector2 &b)
{
    return(a.x < b.x && a.y < b.y);
}

bool operator >= (const Vector2 &a, const Vector2 &b)
{
    return(a.x >= b.x && a.y >= b.y);
}

bool operator > (const Vector2 &a, const Vector2 &b)
{
    return(a.x > b.x && a.y > b.y);
}

//-----------------------------------------------------------------------------------------------

Vector2 Vector2::mulMatrix(double *matrix)
{
    Vector2 result;

	//not implemented

    return result;
}


double cross(const Vector2 &a, const Vector2 &b)
{
	return (a.x * b.y - a.y * b.x);
}

Vector2 normalize(Vector2 &v)
{
   double len = v.length();
   Vector2 normalized; 

   if(len > 0.0)
   {
       normalized.x = v.x / len;
       normalized.y = v.y / len;
   }

   return normalized;
}

double dot(const Vector2 &a, const Vector2 &b)
{
   double dot = 0.0f;

   dot = (a.x * b.x) + (a.y * b.y);

   return dot;
}

double length(const Vector2 &v)
{
   double length = 0.0f;

   length = sqrtf((v.x * v.x) + (v.y * v.y));

   return length;
}

Vector2 operator *(double s, const Vector2 &v)
{
    return (v * s);
}