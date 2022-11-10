
#ifndef SEGVECTORS_H_
#define SEGVECTORS_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Point.h"

using namespace std;

namespace Machine {
class PointArray : public vector<Point> {
private:
        bool multiplication_is_safe(unsigned long a, unsigned long b);
        size_t highestOneBitPosition(unsigned long a);
public:
        void Copy(PointArray);
        std::string GetStatus();
        unsigned long Length();
        unsigned long NumberOfPossiblePaths();
        unsigned long ShortestPathLength();
        double MeasureOfQuality();
        double RelativeQuality(Point,Point);


};


} /* namespace Machine */

#endif /* SEGVECTORS_H_ */

