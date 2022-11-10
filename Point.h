/*
 * Point.h
 *
 *  Created on: Feb 13, 2014
 *      Author: VQMTEAM
 */

#ifndef POINT_H_
#define POINT_H_
#include <algorithm>
#include <math.h>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>


namespace Machine {


class Utils
{
public:
        static std::string ToString (int);
        static std::string ToString (unsigned long);
        static std::string ToString (double);
};

class Point   {
private:

public:
        Point();
        virtual ~Point();
        std::string ToString();
        double RelativeMeasure(Point);
        int  x;
        int  y;
};

} /* namespace Machine */
#endif /* POINT_H_ */

