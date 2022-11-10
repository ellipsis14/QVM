/*
 * Machine.h
 *
 *  Created on: Feb 13, 2014
 *      Author: VQTEAM
 */

#ifndef MACHINE_H_
#define MACHINE_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "Cycle.h"

namespace Machine {

class MachineInstance {
public:
        long qBits;
        Cycle *cycles;
        MachineInstance(long,long,long);
        long Start();
        long Stop();
        long Tick(int);
        std::string GetStatus();
        Graph GenerateRandomGraph();
        Graph GenerateNeighboringGraph(Graph points);
        void ProcessActiveCycle(int i);
        void ProcessInvestigatingCycle(int i);
        void ProcessInactiveCycle(int i);
        void InfluenceInactiveCycles(int i);

        virtual ~MachineInstance();
        Graph graph; // this is the graph we want to find the shortest path for, this is not ordered
        int totalNumberOfTicksAllowed;   // determined by the size of our machine and how many nodes we are processing
        int numberInactive;      // number of inactive cycles
        int numberActive;        // number of active cycles
        int numberInvestigating; // number of investigating cycles
        Graph bestGraph;         // this is our best solution of a shortest path, ordered by best path
        int     *indexesOfInactiveCycles; // contains indexes into the cycles array
};

} /* namespace Machine */
#endif /* MACHINE_H_ */

