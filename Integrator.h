#ifndef INTEGRATOR_H_INCLUDED
#define INTEGRATOR_H_INCLUDED

#include "Field2D.h"

class RKIntegrator
{
public:
    RKIntegrator( VectorField2D* field = NULL );
    ~RKIntegrator();

    void setTolerance( double t ){
        m_tolerance = t;
    }

    double getTolerance()const {
        return m_tolerance;
    }

    bool integrate( const Vector2 &pnt, Vector2& nextPnt, double stepSize = 0.1, double *nextStepSize = NULL, bool isForward = true );

private:
    VectorField2D*  m_field;
    double          m_tolerance;
    double          m_minStep;
    double          m_maxStep;
};

#endif // INTEGRATOR_H_INCLUDED
