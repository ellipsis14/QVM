/*
 *  Graph.cpp
 *
 *  Created on: Feb 26, 2014
 *      Author: VQMTEAM.
 */

#include "Graph.h"

namespace Machine {


void Graph::Copy(Graph in) {
        swap(in);
}

std::string Graph::GetStatus() {
    string s = "";
    s += "Points: ";
    for (unsigned int i = 0; i < size(); ++i)
      s += at(i).ToString() + " ";
    return s;
}

bool Graph::multiplication_is_safe(unsigned long a, unsigned long b) {
    size_t a_bits=highestOneBitPosition(a), b_bits=highestOneBitPosition(b);
    return (a_bits+b_bits<=sizeof(unsigned long));
}

size_t Graph::highestOneBitPosition(unsigned long a) {
    size_t bits=0;
    while (a!=0) {
        ++bits;
        a>>=1;
    };
    return bits;
}

unsigned long Graph::NumberOfPossiblePaths()
{
    unsigned long answer = 1;
    for (unsigned long i = 1; i <= size(); ++i)
       {
          if (multiplication_is_safe(answer,i))
                  answer *= i;
          else
                  break;
       }
    return answer;
}

unsigned long Graph::ShortestPathLength()
{
    return 1.0 * (size() - 1);
}

unsigned long Graph::Length()
{
    return size();
}

double Graph::Measure()
{
  double answer = 0.0;
  for (unsigned int i = 0; i < size() - 1; ++i)
  {
    double d = at(i).RelativeMeasure(at(i+1));
    answer += d;
  }
  return answer;
} // MeasureOfQuality()


} /* namespace Machine */
