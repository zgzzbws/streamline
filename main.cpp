#include <iostream>
#include "Vector2.h"

using namespace std;

int main()
{
    Vector2 vec( 3.5, 2.6 );
    double length = vec.length();
    cout<<length<<endl;

    return 0;
}
