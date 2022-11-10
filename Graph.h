#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Point.h"

using namespace std;

namespace Machine {
class Graph : public vector<Point> {
private:
        bool multiplication_is_safe(unsigned long a, unsigned long b);
        size_t highestOneBitPosition(unsigned long a);
public:
        void Copy(Graph);
        std::string GetStatus();
        unsigned long Length();
        unsigned long NumberOfPossiblePaths();
        unsigned long ShortestPathLength();
        double Measure();
        double RelativeMeasure(Point,Point);


};


} /* namespace Machine */

#endif /* GRAPH_H_ */