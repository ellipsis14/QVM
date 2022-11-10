/*
 *  PointArray.cpp
 *
 *  Created on: Feb 26, 2014
 *      Author: VQMTEAM.
 */

#include "PointArray.h"

namespace Machine {


void PointArray::Copy(PointArray in) {
        swap(in);
}

std::string PointArray::GetStatus() {
    string s = "";
    s += "Points: ";
    for (unsigned int i = 0; i < size(); ++i)
      s += at(i).ToString() + " ";
    return s;
}

bool PointArray::multiplication_is_safe(unsigned long a, unsigned long b) {
    size_t a_bits=highestOneBitPosition(a), b_bits=highestOneBitPosition(b);
    return (a_bits+b_bits<=32);
}

size_t PointArray::highestOneBitPosition(unsigned long a) {
    size_t bits=0;
    while (a!=0) {
        ++bits;
        a>>=1;
    };
    return bits;
}

unsigned long PointArray::NumberOfPossiblePaths()
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

unsigned long PointArray::ShortestPathLength()
{
    return 1.0 * (size() - 1);
}

unsigned long PointArray::Length()
{
    return size();
}


double PointArray::MeasureOfQuality()
{
  double answer = 0.0;
  for (unsigned int i = 0; i < size() - 1; ++i)
  {
    double d = RelativeQuality(at(i),at(i+1));
    answer += d;
  }
  return answer;
} // MeasureOfQuality()

