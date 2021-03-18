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

    source.open("../intermediates/CoSimArray.txt");
    for (size_t i = 0; i < 500; i++)
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
        for (size_t j = 0; j < 1000; j++)
        {
            if (j % 10 == 0)
            {
                source << "\n index [" << i << "]"
                       << "["
                       << j
                       << "]"
                       << "\n";
            }
            source << resCosim[i][j] << "\t";
        }
    }
}

void printResults()
{
    ifstream srcFile;
    ofstream destFile;
    //handle case 5
    srcFile.open("../data/test5.txt");
    destFile.open("../res/res5cosim.txt");

    string stringVal;
    int counter = 0;
    int userIndex;
    int movieIndex;
    int ratingValue;
    while (!srcFile.eof())
    {
        srcFile >> stringVal;
        counter++;
        if (counter == 1)
        {
            userIndex = stoi(stringVal);
            destFile << userIndex << "\t";
        }
        else if (counter == 2)
        {
            movieIndex = stoi(stringVal);
            destFile << movieIndex << "\t";
        }
        else if (counter == 3)
        {
            counter = 0;
            ratingValue = stoi(stringVal);
            if (ratingValue == 0)
            {
                //write the predicted value to the result file
                destFile << resCosim[userIndex - 1][movieIndex - 1] << "\n";
            }
            else
            {
                //simply copy the rating value to the destfile
                destFile << ratingValue << "\n";
            }
        }
    }
    srcFile.close();
    destFile.close();
    srcFile.open("../data/test10.txt");
    destFile.open("../res/res10cosim.txt");
    counter = 0;

    while (!srcFile.eof())
    {
        srcFile >> stringVal;
        counter++;
        if (counter == 1)
        {
            userIndex = stoi(stringVal);
            destFile << userIndex << "\t";
        }
        else if (counter == 2)
        {
            movieIndex = stoi(stringVal);
            destFile << movieIndex << "\t";
        }
        else if (counter == 3)
        {
            counter = 0;
            ratingValue = stoi(stringVal);
            if (ratingValue == 0)
            {
                //write the predicted value to the result file
                destFile << resCosim[userIndex - 1][movieIndex - 1] << "\n";
            }
            else
            {
                //simply copy the rating value to the destfile
                destFile << ratingValue << "\n";
            }
        }
    }
    srcFile.close();
    destFile.close();
    srcFile.open("../data/test20.txt");
    destFile.open("../res/res20cosim.txt");

    counter = 0;

    while (!srcFile.eof())
    {
        srcFile >> stringVal;
        counter++;
        if (counter == 1)
        {
            userIndex = stoi(stringVal);
            destFile << userIndex << "\t";
        }
        else if (counter == 2)
        {
            movieIndex = stoi(stringVal);
            destFile << movieIndex << "\t";
        }
        else if (counter == 3)
        {
            counter = 0;
            ratingValue = stoi(stringVal);
            if (ratingValue == 0)
            {
                //write the predicted value to the result file
                destFile << resCosim[userIndex - 1][movieIndex - 1] << "\n";
            }
            else
            {
                //simply copy the rating value to the destfile
                destFile << ratingValue << "\n";
            }
        }
    }
}