//Author: Sören Pirk
//Date: 22.01.2013

#include "Vector3.h"
#include "Vector2.h"

Vector3::Vector3() 
: x(0.0),
  y(0.0),
  z(0.0)
{
}

Vector3::Vector3(double x, double y, double z)
{
   this->x = x;
   this->y = y;
   this->z = z;
}

Vector3::Vector3(const Vector3 &v)
{
   this->x = v.x;
   this->y = v.y;
   this->z = v.z;
}

Vector3::Vector3(const double *v)
{
   this->x = v[0];
   this->y = v[1];
   this->z = v[2];
}

Vector3::Vector3( const Vector2 v ) :x(v.x), y(v.y), z(0)
{

}

Vector3::~Vector3() 
{
}

double Vector3::length()
{
   double length = 0.0f;

   length = sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));

   return length;
}

double Vector3::dot(const Vector3 &vec)
{
   double dot = 0.0f;

   dot = (this->x * vec.x) + (this->y * vec.y) + (this->z * vec.z);

   return dot;
}

double Vector3::angle(Vector3 &vec)
{
    double d = this->dot(vec);

    double a = this->length();    
    double b = vec.length();

    double s = d / (a*b);
    double angle = (double)acos((double)s);

    return angle;
}

Vector3 Vector3::cross(const Vector3 &vec)
{
   Vector3 cross;

   cross.x = (this->y * vec.z) - (this->z * vec.y);
   cross.y = (this->z * vec.x) - (this->x * vec.z);
   cross.z = (this->x * vec.y) - (this->y * vec.x);

   return cross;
}

Vector3 normalize(Vector3 &v)
{
   double len = v.length();
   Vector3 normalized; 

   if(len > 0.0)
   {
       normalized.x = v.x / len;
       normalized.y = v.y / len;
	   normalized.z = v.z / len;
   }

   return normalized;
}

void Vector3::normalize()
{
   double len = this->length();

   if(len > 0.0f)
   {
       this->x = this->x / len;
       this->y = this->y / len;
       this->z = this->z / len;   
   }
}

Vector3 Vector3::normalized()
{
   double len = this->length();
   Vector3 normalized; 

   if(len > 0.0)
   {
       normalized.x = this->x / len;
       normalized.y = this->y / len;
       normalized.z = this->z / len;   
   }

   return normalized;
}

void Vector3::set(double x, double y, double z)
{
   this->x = x;
   this->y = y;
   this->z = z;
}

void Vector3::set(double *vec)
{
   this->x = vec[0];
   this->y = vec[1];
   this->z = vec[2];
}

Vector3 &Vector3::get()
{
    return *this;
}

void Vector3::print()
{
    printf("x: %f, y: %f, z: %f\n", x, y, z);
}

Vector3 &Vector3::operator =(const Vector3 &a)
{
   this->x = a.x;
   this->y = a.y;
   this->z = a.z;

   return *this;
}

Vector3 &Vector3::operator +=(const Vector3 &a)
{
   this->x += a.x;
   this->y += a.y;
   this->z += a.z;

   return *this;
}

Vector3 &Vector3::operator +=(double s)
{
   this->x += s;
   this->y += s;
   this->z += s;

   return *this;
}

Vector3 &Vector3::operator -=(const Vector3 &a)
{
   this->x -= a.x;
   this->y -= a.y;
   this->z -= a.z;

   return *this;
}

Vector3 &Vector3::operator -=(double s)
{
   this->x -= s;
   this->y -= s;
   this->z -= s;

   return *this;
}

Vector3 &Vector3::operator *=(const Vector3 &a)
{
   this->x *= a.x;
   this->y *= a.y;
   this->z *= a.z;

   return *this;
}

Vector3 &Vector3::operator *=(double s)
{
   this->x *= s;
   this->y *= s;
   this->z *= s;

   return *this;
}

Vector3 &Vector3::operator /=(const Vector3 &a)
{
   this->x /= a.x;
   this->y /= a.y;
   this->z /= a.z;
   
   return *this;
}

Vector3 &Vector3::operator /=(double s)
{
   this->x /= s;
   this->y /= s;
   this->z /= s;

   return *this;
}

//-----------------------------------------------------------------------------------------------

Vector3 operator +(const Vector3 &a, const Vector3 &b)
{
   Vector3 r;

   r.x = a.x + b.x;
   r.y = a.y + b.y;
   r.z = a.z + b.z;

   return r;
}

Vector3 operator +(const Vector3 &a, double s)
{
   Vector3 r;

   r.x = a.x + s;
   r.y = a.y + s;
   r.z = a.z + s;

   return r;
}

Vector3 operator +(double s, const Vector3 &a)
{
   Vector3 r;

   r.x = a.x + s;
   r.y = a.y + s;
   r.z = a.z + s;

   return r;
}

Vector3 operator -(const Vector3 &a, const Vector3 &b)
{
   Vector3 r;

   r.x = a.x - b.x;
   r.y = a.y - b.y;
   r.z = a.z - b.z;

   return r;
}

Vector3 operator -(const Vector3 &a, double s)
{
   Vector3 r;

   r.x = a.x - s;
   r.y = a.y - s;
   r.z = a.z - s;

   return r;
}


Vector3 operator -(const Vector3 &a)
{
    Vector3 r;
	
	r.x = -a.x;
	r.y = -a.y;
	r.z = -a.z;
	
	return r;
}

Vector3 operator *(const Vector3 &a, double s)
{
   Vector3 r;

   r.x = a.x * s;
   r.y = a.y * s;
   r.z = a.z * s;

   return r;
}

Vector3 operator *(const Vector3 &a, const Vector3 &b)
{
   Vector3 r;

   r.x = a.x * b.x;
   r.y = a.y * b.y;
   r.z = a.z * b.z;

   return r;
}

Vector3 operator /(const Vector3 &a, double s)
{
   Vector3 r;

   r.x = a.x / s;
   r.y = a.y / s;
   r.z = a.z / s;

   return r;
}

Vector3 operator /(const Vector3 &a, const Vector3 &b)
{
   Vector3 r;

   r.x = a.x / b.x;
   r.y = a.y / b.y;
   r.z = a.z / b.z;

   return r;
}

//-----------------------------------------------------------------------------------------------

bool operator == (const Vector3 &a, const Vector3 &b)
{
    return(a.x == b.x && a.y == b.y && a.z == b.z);
}

bool operator != (const Vector3 &a, const Vector3 &b)
{
    return(a.x != b.x || a.y != b.y || a.z != b.z);
}

bool operator <= (const Vector3 &a, const Vector3 &b)
{
    return(a.x <= b.x && a.y <= b.y && a.z <= b.z);
}

bool operator < (const Vector3 &a, const Vector3 &b)
{
    return(a.x < b.x && a.y < b.y && a.z < b.z);
}

bool operator >= (const Vector3 &a, const Vector3 &b)
{
    return(a.x >= b.x && a.y >= b.y && a.z >= b.z);
}

bool operator > (const Vector3 &a, const Vector3 &b)
{
    return(a.x > b.x && a.y > b.y && a.z > b.z);
}

//-----------------------------------------------------------------------------------------------

Vector3 Vector3::mulMatrix(double *matrix)
{
    Vector3 result;

    result.x = matrix[0] * this->x + matrix[1] * this->y + matrix[2] * this->z;
    result.y = matrix[3] * this->x + matrix[4] * this->y + matrix[5] * this->z;
    result.z = matrix[6] * this->x + matrix[7] * this->y + matrix[8] * this->z;

    return result;
}

Vector2 Vector3::toVector2() const
{
	return Vector2(x,y);
}


Vector3 cross(const Vector3 &a, const Vector3 &b)
{
   Vector3 c;

   c.x = (a.y * b.z) - (a.z * b.y);
   c.y = (a.z * b.x) - (a.x * b.z);
   c.z = (a.x * b.y) - (a.y * b.x);

   return c;
}


double dot(const Vector3 &a, const Vector3 &b)
{
   double dot = 0.0f;

   dot = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);

   return dot;
}

double length(const Vector3 &v)
{
   double length = 0.0f;

   length = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

   return length;
}

Vector3 operator *(double s, const Vector3 &v)
{
    return (v * s);
}