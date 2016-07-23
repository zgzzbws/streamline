#include "Integrator.h"

RKIntegrator::RKIntegrator(VectorField2D* field):m_field(field), m_tolerance(1e-5), m_minStep(0.01), m_maxStep(2)
{
}

RKIntegrator::~RKIntegrator()
{
}

bool RKIntegrator::integrate( const Vector2 &pnt, Vector2& nextPnt, double stepSize, double *nextStepSize, bool isForward )
{
    double h = isForward ? stepSize : -stepSize;

    //integration methods
    //the parameters are based on the Runge-Kutta-Fehlberg scheme
    //the details could be consulted from the following website
    //http://www4.ncsu.edu/~mtchu/Teaching/Lectures/MA427/By_subjects/27_rkf45_method.pdf
    Vector2 d1, d2, d3, d4, d5, d6;
    if( !m_field->getValue(pnt, d1) )
        return false;
    d1 *= h;
    if(!m_field->getValue(pnt + d1*(0.25), d2)) {
        return false;
    }
	d2 *= h;
	if(!m_field->getValue(pnt + d1*(3.0/32) + d2*(9.0/32), d3))
	    return false;
	d3 *= h;
	if(!m_field->getValue(pnt + d1*(1932.0/2197) + d2*(-7200.0/2197) + d3*(7296.0/2197), d4))
	    return false;
	d4 *= h;
	if(!m_field->getValue(pnt + d1*(439.0/216) + d2*(-8.0) + d3*(3680.0/513) + d4*(-845.0/4104), d5))
	    return false;
	d5 *= h;
	if(!m_field->getValue(pnt + d1*(-8.0/27) + d2*(2.0) + d3*(-3544.0/2565) + d4*(1859.0/4104) + d5 * (-11.0/40), d6))
	    return false;
	d6 *= h;

	Vector2 nextPnt0 = pnt + d1*(25.0/216) + d3*(1408.0/2565)  + d4*(2197.0/4104)   + d5*(-1.0/5);
	Vector2 nextPnt1 = pnt + d1*(16.0/135) + d3*(6656.0/12825) + d4*(28561.0/56430) + d5*(-9.0/50) + d6*(2.0/55);
	if ((nextPnt1 - pnt).length() < 0.05)
		return false;

	nextPnt = nextPnt1;
	if (nextStepSize)
	{
		Vector2 delta = nextPnt1 - nextPnt0;
		double deltaL = delta.length();
		double s = 1;
		if (deltaL >= 1e-6)
			s = pow(m_tolerance / (2 * delta.length()), 0.25);
		if (s < 0.75 && stepSize > 2 * m_minStep)
			*nextStepSize = stepSize / 2.0;
		if (s > 1.5 && stepSize < m_maxStep / 2)
			*nextStepSize = stepSize * 2.0;
		else
			*nextStepSize = stepSize;
	}
	return true;
}
