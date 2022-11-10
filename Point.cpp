/*
 * Points.cpp
 *
 *  Created on: Feb 13, 2014
 *      Author: VQMTEAM
 */

#include "Point.h"
#include <math.h>

namespace Machine {


std::string Utils::ToString(int value)
{
        std::string number;
        std::stringstream strstream;
        strstream << value;
        strstream >> number;
        return number;
}

std::string Utils::ToString(unsigned long value)
{
        std::string number;
        std::stringstream strstream;
        strstream << value;
        strstream >> number;
        return number;
}

std::string Utils::ToString(double value)
{
        std::string number;
        std::stringstream strstream;
        strstream << value;
        strstream >> number;
        return number;
}


Point::Point() {

}

Point::~Point() {

}


std::string Point::ToString() {
        std::string s;
        s.append("(");
        s.append(Utils::ToString(x));
        s.append(",");
        s.append(Utils::ToString(y));
        s.append(")");
        return s;
}

double Point::RelativeMeasure(Point pt)
{
    return  sqrt(float((pt.x - x)*(pt.x - x) + (pt.y - y)*(pt.y - y)));
}


} /* namespace Machine */

