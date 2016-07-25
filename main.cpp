#include <iostream>
#include <vector>
#include <deque>
#include <stdlib.h>
#include <time.h>
#include "streamline.h"
#include "Field2D.h"
#include "Integrator.h"
#include "SimiliarTest.h"

StreamLineParam g_param;

bool dataLoad( const char* path, VectorField2D &field ) {
    if( !field.readFile( path ) )
        return false;
    return true;
}

void initializeStreamlineParams( const VectorField2D &field, int &dim_x, int &dim_y ) {
    dim_x = field.getNCols();
	dim_y = field.getNRows();

    g_param.alpha = 2.0f;
	g_param.dSep = 0.01 * std::min(dim_x, dim_y);
	g_param.w = 3.0f * g_param.dSep;
	g_param.dSelfsep = g_param.dSep/10.0f;
	g_param.dMin = 10.0f* g_param.dSelfsep;
	g_param.minLen = 2.0 * g_param.w;
	g_param.maxLen = 20 * g_param.minLen;
	g_param.maxSize = 5000;
	g_param.nHalfSample = 10;
	g_param.print();
}

std::vector <vec3> setSeeds( const int &numOfSeeds, const int &dim_x, const int &dim_y ) {
    std::vector<vec3> result;
    srand (time(NULL));
	for(int i=0; i<numOfSeeds; i++)
	{
		vec3 s = vec3(rand()%dim_x, rand()%dim_y, 0);
		result.push_back(s);
	}
	return result;
}

std::vector<Line> integration( VectorField2D &field, const std::vector<vec3> &seeds ) {
    RKIntegrator integrator(&field);		// RK45
	std::vector<Line> streamlines;			// Resulting streamlines

	int num_seed = seeds.size();
	for(int i=0; i<num_seed; i++)
	{
		printf("%d th seed\n", i);
		// current streamline
		Line current_line;
		std::deque<vec3>& curPath = current_line.path;
		curPath.push_back(seeds[i]);

		// grow current_line
		double stepSize[2]   = {0.5,0.5};
		bool   isContinue[2] = {true, true};
		while((isContinue[0] || isContinue[1]) && curPath.size() < g_param.maxSize)
		{
			if (isContinue[0])
			{
				// integrate FORWARD over the flow field
				Vector2 nextPnt;
				isContinue[0] &= integrator.integrate(curPath.back().toVector2(), nextPnt, stepSize[0], stepSize, true);
				if (isContinue[0])
				{
					curPath.push_back(Vector3(nextPnt));

					bool stop_forward  = false;
					bool stop_forward_self  = false;
					int idx = curPath.size()-1;
					stop_forward = SimTester::isSimilarWithLines(streamlines, curPath, idx);
					stop_forward_self = SimTester::isSimilarWithSelf(curPath, idx);

					if (stop_forward || stop_forward_self)
					{
						curPath.pop_back();
						isContinue[0] = false;
					}
				}
			}

			if (isContinue[1])
			{
				// integrate BACKWARD over the flow field
				Vector2 prePnt;
				isContinue[1] &= integrator.integrate(curPath.front().toVector2(), prePnt, stepSize[1], stepSize+1, false);

				if (isContinue[1])
				{
					curPath.push_front(Vector3(prePnt));

					bool stop_backward  = false;
					bool stop_backward_self  = false;
					int idx = 0;
					stop_backward = SimTester::isSimilarWithLines(streamlines, curPath, idx);
					stop_backward_self = SimTester::isSimilarWithSelf(curPath, idx);

					if (stop_backward || stop_backward_self)
					{
						curPath.pop_front();
						isContinue[1] = false;
					}
				}

			}
		}

		// add current line to stream line set
		if(current_line.getLength() > g_param.minLen)
		{
			current_line.pathDir.resize(current_line.path.size());
			for (int i = 0; i < curPath.size(); ++i)
			{
				Vector2 dir(0,0);
				field.getValue(curPath[i].toVector2(), dir);
				current_line.pathDir[i] = dir;
			}
			streamlines.push_back(current_line);
			std::cout<<"The added new streamline, length: "<<(int)curPath.size()<<std::endl;
		}
		else
			std::cout<<"Failed"<<std::endl;
	}

	return streamlines;
}

int main()
{
    const char* fieldPath = "E:/wind.txt";

    VectorField2D field;
    if( !dataLoad( fieldPath, field ) ) {
        std::cerr<<"Reading file failed";
        return 1;
    }

    int dim_x, dim_y;
    int numOfSeeds = 3000;
    initializeStreamlineParams( field, dim_x, dim_y );
    std::vector<vec3> seeds = setSeeds( numOfSeeds, dim_x, dim_y );

    std::vector<Line> streamLines = integration( field, seeds );

    //set the related functions to draw the streamlines

    return 0;
}
