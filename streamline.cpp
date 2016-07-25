#include "streamline.h"

double Line::getLength() const
{
    double l = 0;
    for( size_t i = 0; i < path.size()-1; ++i )
    {
        vec3 delta = path[i+1] - path[i];
        l += delta.length();
    }
    return l;
}

void StreamLineParam::print() const
{
    printf("alpha:%lf\n", alpha);
    printf("dMin :%lf\n", dMin);
	  printf("dSep :%lf\n", dSep);
  	printf("dSelfSep:%lf\n", dSelfsep);
	  printf("w    :%lf\n", w);
	  printf("minLen:%lf\n", minLen);
	  printf("maxLen:%lf\n", maxLen);
	  printf("nHalfSample:%d\n", nHalfSample);
	  printf("maxSize:%d\n", maxSize);
}
