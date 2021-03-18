#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "printer.h"

using namespace std;

void printGlobalState()
{
    //write the train array into its file
    ofstream source;
    source.open("../intermediates/trainArray.txt");
    for (int i = 0; i < 500; i++)
    {
        source << "\n";
        source << "\n";
        source << "\n";
        source << "\n";
        source << "\n";
        source << "\n";
        source << "\n";
        source << "userIndex= " << i;
        source << "\n";
        for (int j = 0; j < 1000; j++)
        {
            if (j % 10 == 0)
            {
                source << "\n index [" << i << "]"
                       << "["
                       << j
                       << "]"
                       << "\n";
            }
            source << trainArray[i][j] << "\t";
            //cout << trainArray[i][j] << "\t";
        }
    }
    //write state of user average array
    source.close();
    source.open("../intermediates/UserAverageArray.txt");
    for (size_t i = 0; i < 500; i++)
    {
        source << "Average for userIndex = " << i << " === " << UserAverageArray[i];
        source << "\n";
    }
    source.close();
    source.open("../intermediates/MovieAverageArray.txt");
    for (size_t i = 0; i < 1000; i++)
    {
        source << "Average for MovieIndex = " << i << " === " << MovieAverageArray[i];
        source << "\n";
    }
    source.close();
}