#ifndef SIMILIARTEST_H_INCLUDED
#define SIMILIARTEST_H_INCLUDED

#include "Field2D.h"
#include "streamline.h"

class SimTester
{
public:
    static bool isSimilarWithLines( std::vector<Line> &streamLines, std::deque<vec3> &si_tmp, int id );
    static bool isSimilarWithSelf( std::deque<vec3> &si, int siInx );
    static bool self_line_similarty( std::vector<vec3> &si_tmp, int id );

    static bool findIdxRange( const std::deque<vec3>&line, const vec3& centerPnt, double radius, int& lowID, int& highID );

    static bool sampleLine(	const std::deque<vec3>& line, int idx, double lineLength,
                           int nHalfSample, std::vector<vec3>& result, int& idxPos);
};

#endif // SIMILIARTEST_H_INCLUDED
