#ifndef FIELD2D_H_INCLUDED
#define FIELD2D_H_INCLUDED

#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <float.h>
#include "Vector2.h"

using namespace std;

struct RGB {
    int red;
    int green;
    int blue;
    RGB( int r = 255, int g = 255, int b = 255 )
        : red(r),green(g),blue(b){}
};

class VectorField2D
{
public:
    VectorField2D();
    ~VectorField2D();

    enum { INVALID_VALUE = -9999 };

    void     clear();
    bool     readFile( const char* fileName );
    bool     writeFile( const char* fileName );

    //set the data manually to test the algorithm
    bool     setToConstant( const Vector2& v, int nRows, int nCols );
    bool     setToRadical( int nRows, int nCols );
    bool     setToCircular( int nRows, int nCols );

    bool     getValue( const Vector2& pnt, Vector2& dir ) const;
    bool     getLengthField( vector<double>& field )const;

    const vector<RGB> getImage()const;

    Vector2& getCell( int row, int col ) {
        return m_data[row*m_nCols+col];
    }

    const Vector2& getCell( int row, int col ) const {
        return m_data[row*m_nCols+col];
    }

    bool isInvalid( const Vector2& v ) const {
        return v.x == INVALID_VALUE || v.y == INVALID_VALUE;
    }

    int getNRows()const {
        return m_nRows;
    }

    int getNCols()const {
        return m_nCols;
    }

private:
    //set the coordinates of the area
    Vector2          m_minVal;
    Vector2          m_maxVal;
    //set the rectangle area
    int              m_nRows;
    int              m_nCols;
    vector<Vector2>  m_data;
    //compute the bound
    void computeBound();
};

#endif // FIELD2D_H_INCLUDED
