/*
 * Machine.cpp
 *
 *  Created on: Feb 13, 2014
 *      Author: VQTEAM
 */


#include "Machine.h"

namespace Machine {

MachineInstance::MachineInstance(long numberOfQBits, long numberOfNodes, long isRandom) {

        // number of qbits in the vqm
        qBits = numberOfQBits;

        // our algorithm assumes that the number of active > number investigating > number inactive
    numberInactive = qBits * .20;
    numberInvestigating = qBits * .30;
    numberActive = qBits * .50;

        cycles =  new Cycle[qBits];
    srand(0);  // set the seed for the random number generator


        if (isRandom)
        {
            for (int i = 0; i < numberOfNodes ; i++)
            {
            Point s;
            s.x = (rand() % 10) + 1 ;
            s.y = (rand() % 10) + 1;
            graph.push_back(s);
            }
                totalNumberOfTicksAllowed = qBits*numberOfNodes;
        }
        else
        {
                // Best path measure:    19.6903 1000 qBits terminated successfully
                // Best path measure:    18.5606 10000 qBits terminated successfully
                // Best path measure:    18.5606 7000 qBits terminated successfully

            Point s;

                s.x = 4;
                s.y = 6;
            graph.push_back(s);
                s.x = 8;
                s.y = 6;
            graph.push_back(s);
                s.x = 7;
                s.y = 3;
            graph.push_back(s);
                s.x = 10;
                s.y = 2;
            graph.push_back(s);
                s.x = 1;
                s.y = 10;
            graph.push_back(s);
                s.x = 1;
                s.y = 7;
            graph.push_back(s);
                s.x = 4;
                s.y = 7;
            graph.push_back(s);
                s.x = 4;
                s.y = 7;
            graph.push_back(s);
                s.x = 3;
                s.y = 8;
            graph.push_back(s);
                s.x = 3;
                s.y = 7;
            graph.push_back(s);

            numberOfNodes = 10;
                totalNumberOfTicksAllowed = qBits*numberOfNodes;
        }
}

MachineInstance::~MachineInstance() {
}

long MachineInstance::Start() {

    long returnedstatus = 0;

    cout << "\nStarting machine\n";
    cout << "Loading point data for Traveling Salesman Problem analysis\n";

    cout << graph.GetStatus() + "\n";

    cout << "Number points = " + Utils::ToString(graph.Length()) + "\n";
    cout << "Number of possible paths = " + Utils::ToString(graph.NumberOfPossiblePaths()) + "\n";
    cout << "Best possible solution (shortest path) length = " + Utils::ToString(graph.ShortestPathLength()) + "\n";

    bestGraph = GenerateRandomGraph(); // alternative initializations are possible
    indexesOfInactiveCycles = new int[numberInactive]; // indexes of cycles which are currently inactive

    for (int i = 0; i < qBits; ++i) // initialize each cycle, and best solution
    {
      int currStatus;

      // depends on i. need status before we can initialize cycle
          // our algorithm assumes that the number of active > number investigating > number inactive

      if (i < numberInactive)
      {
        currStatus = 0; // inactive
        indexesOfInactiveCycles[i] = i; // current cycle is inactive
      }
      else if (i < numberInactive + numberInvestigating)
      {
        currStatus = 2; // investigating
      }
      else
      {
        currStatus = 1; // active
      }

      Graph randomGraph = GenerateRandomGraph();
      double mq = randomGraph.Measure();
      int numberOfVisits = 0;

      cycles[i].status = currStatus;
      cycles[i].graph = randomGraph;
      cycles[i].measure = mq;
      cycles[i].numberOfVisits = numberOfVisits;

      // does this cycle have best solution?
          // current cycle is better (< because smaller is better)
      if (cycles[i].measure < bestGraph.Measure())
      {
          bestGraph.Copy(cycles[i].graph);
      }
    }

    int tickNumber = 0;
    while (tickNumber < totalNumberOfTicksAllowed)
    {
        returnedstatus = Tick(++tickNumber);
    }

        return returnedstatus;
}

long MachineInstance::Stop() {
    cout << "\nStoping machine\n";
        return 0L;
}

long MachineInstance::Tick(int tickNumber) {

    for (int i = 0; i < qBits; ++i)   // initialize each cycle, and best solution
    {
      if (cycles[i].status == 1)      // active cycle
        ProcessActiveCycle(i);
      else if (cycles[i].status == 2) // investigating cycle
          ProcessInvestigatingCycle(i);
      else if (cycles[i].status == 0) // inactive cycle
        ProcessInactiveCycle(i);
    }

    cout << "\nStatus At Tick number " + Utils::ToString(tickNumber) + ": \n";
    cout << GetStatus();

        return 0L;
}


std::string MachineInstance::GetStatus()
{
  std::string s = "";
  s += "\nBest path found: ";
  for (unsigned int i = 0; i < bestGraph.size() - 1; ++i)
    s += bestGraph[i].ToString() + "->";
  s += bestGraph[bestGraph.size()-1].ToString() + "\n";

  s += "Best path measure:    ";
    s += Utils::ToString(bestGraph.Measure()) + "\n";

  s += "\n";
  return s;
}

Graph MachineInstance::GenerateRandomGraph()
{
  Graph result;
  result.Copy(graph);
  for (unsigned int i = 0; i < result.size(); i++) // Fisher-Yates (Knuth) shuffle
  {
        unsigned int r = rand() % result.size(); // [0, Length-1] inclusive
    Point temp = result[r]; result[r] = result[i]; result[i] = temp;
  }
  return result;
} // GenerateRandomGraph()


Graph MachineInstance::GenerateNeighboringGraph(Graph graph)
{
  Graph result;
  result.Copy(graph);

  unsigned int ranIndex = rand() % result.size(); // [0, Length-1] inclusive
  int adjIndex;
  if (ranIndex == result.size() - 1)
    adjIndex = 0;
  else
    adjIndex = ranIndex + 1;

  Point tmp = result[ranIndex];
  result[ranIndex] = result[adjIndex];
  result[adjIndex] = tmp;

  return result;
} // GenerateNeighboringGraph()



void MachineInstance::ProcessActiveCycle(int i)
{
  Graph neighbor = GenerateNeighboringGraph(cycles[i].graph); // find a neighboring solution
  double neighborMeasure = neighbor.Measure(); // get its quality

  if (neighborMeasure < cycles[i].measure) // active cycle found better neighbor (< because smaller values are better)
  {
      ++cycles[i].numberOfVisits; // no change to memory but update number of visits
      cycles[i].graph.Copy(neighbor);
      cycles[i].measure = neighborMeasure; // update the quality
      // first, determine if the new memory is a global best. note that if cycle has accepted a worse food source this can't be true
      if (cycles[i].measure < bestGraph.Measure()) // the modified cycle's memory is a new global best (< because smaller is better)
      {
        bestGraph.Copy(cycles[i].graph);
      }
      InfluenceInactiveCycles(i); // cycle returns to machine availability and does communicates state to other cycles
  }
  else // active cycle did not find a better neighbor
  {
      ++cycles[i].numberOfVisits;
      cycles[i].graph.Copy(neighbor);
      cycles[i].measure = neighborMeasure; // update the quality
  }
} // ProcessActiveCycle()

void MachineInstance::ProcessInvestigatingCycle(int i)
{
  Graph randomGraph = GenerateRandomGraph(); // investigating cycle finds a random point path
  double randomGraphMeasure = randomGraph.Measure(); // and examines its quality
  // investigating cycle has found a better solution than its current one (< because smaller measure is better)
  if (randomGraphMeasure < cycles[i].measure)
  {
    cycles[i].graph.Copy(randomGraph);
    cycles[i].measure = randomGraphMeasure;
    // no change to cycles numberOfVisits or status

    // did this cycle find a graph?
    if (cycles[i].measure < bestGraph.Measure()) // yes, better overall graph
    {
      bestGraph.Copy(cycles[i].graph);
    } // better overall graph

    // investigating cycle returns to machine availability and attempts to influence other cycles
    InfluenceInactiveCycles(i);

  } // if cycle found better solution
} // ProcessInvestigatingCycle()

void MachineInstance::ProcessInactiveCycle(int i)
{
}

void MachineInstance::InfluenceInactiveCycles(int i)
{
  for (int j = 0; j < numberInactive; ++j) // each inactive cycle
  {
    int b = indexesOfInactiveCycles[j]; // index of an inactive cycle
    if (cycles[b].status != 0 || cycles[b].numberOfVisits != 0) continue;
    // investigating cycle has better solution than inactive cycle
    if (cycles[i].measure < cycles[b].measure)
    {
      cycles[b].graph.Copy(cycles[i].graph);
      cycles[b].measure = cycles[i].measure;
    } // investigating cycle has better solution than inactive cycle
  } // each inactive cycle
} // InfluenceInactiveCycles


} /* namespace Machine */
