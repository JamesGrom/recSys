#include "parser.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

//defines the values in the given trainArray
using namespace std;
//make sure that initializer has been called beforethis function
void synthTrainMatrix()
{

    //open the train.txt source file
    ifstream source;
    source.open("../data/train.txt");

    //construct the indexes 0-199 from the train.txt file
    string stringVal;
    int rowIndex = 0;
    int columnIndex = 0;
    while (!source.eof() && rowIndex < 200 && columnIndex < 1000)
    {
        source >> stringVal;
        //enter a number into the matrix and update the indexes accordingly
        trainArray[rowIndex][columnIndex] = stoi(stringVal);
        //cout << trainArray[rowIndex][columnIndex];

        if (columnIndex == 999)
        {
            columnIndex = 0;
            rowIndex++;
        }
        else
        {
            columnIndex++;
        }
    }

    //construct indexes 200-299 from the test5.txt
    source.close();
    source.open("../data/test5.txt");
    int counter = 0;
    int userIndex;
    int movieIndex;
    int ratingValue;
    while (!source.eof())
    {
        source >> stringVal;
        counter++;
        // cout << stringVal << " ";
        if (counter == 1)
        {
            userIndex = stoi(stringVal);
        }
        else if (counter == 2)
        {
            movieIndex = stoi(stringVal);
        }
        else if (counter == 3)
        {
            counter = 0;
            ratingValue = stoi(stringVal);
            trainArray[userIndex - 1][movieIndex - 1] = ratingValue;
        }
    }

    //construct indexes 300-399 from test10.txt
    source.close();
    source.open("../data/test10.txt");
    counter = 0;
    while (!source.eof())
    {
        source >> stringVal;
        counter++;
        if (counter == 1)
        {
            userIndex = stoi(stringVal);
        }
        else if (counter == 2)
        {
            movieIndex = stoi(stringVal);
        }
        else if (counter == 3)
        {
            counter = 0;
            ratingValue = stoi(stringVal);
            trainArray[userIndex - 1][movieIndex - 1] = ratingValue;
            // cout << userIndex << "\t" << movieIndex << "\t" << trainArray[userIndex - 301][movieIndex - 1] << endl;
        }
    }

    //construct indexes 400-499 from test20.txt
    source.close();
    source.open("../data/test20.txt");
    counter = 0;
    while (!source.eof())
    {

        source >> stringVal;
        counter++;
        if (counter == 1)
        {
            userIndex = stoi(stringVal);
        }
        else if (counter == 2)
        {
            movieIndex = stoi(stringVal);
        }
        else if (counter == 3)
        {
            counter = 0;
            ratingValue = stoi(stringVal);
            trainArray[userIndex - 1][movieIndex - 1] = ratingValue;
        }
    }
    source.close();
}