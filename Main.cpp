//============================================================================
// Name        : Main.cpp
// Author      : VQMTeam
// Version     : the one and only
// Copyright   : this doesn't belong to you, do not take it
// Description : Virtual Quantum Machine
//============================================================================


#include "Machine.h"

using namespace std;
using namespace Machine;

int main(int argc, char* argv[])
{
        int returned_error = 0;
        MachineInstance* pmachine = 0L;
        try
        {
                long numberofqBits = atol(argv[1]);
                long numberofNodes = atol(argv[2]);
                long isRandom = atol(argv[3]);
                // Create virtual quantum machine on the stack
                pmachine = new MachineInstance(numberofqBits, numberofNodes, isRandom);
                // Start the virtual quantum machine
                returned_error = pmachine->Start();
                // Assuming the machine hasn't thrown an error, process the stop request
                if (!returned_error)
                  returned_error = pmachine->Stop();
        }
        catch (int error)
        {
                returned_error = error;
        }

        if (pmachine)
                delete pmachine;

        if (returned_error == 0)
                cout << "Machine Completed Normally.";
        else
                cout << "Machine Completed Abnormally.  Returned error code is " + Utils::ToString(returned_error);

        return returned_error;
}

