#include "main.h"
int trainArray[500][1000];
double UserAverageArray[500];
double MovieAverageArray[1000];
double IUFArray[1000];
int resCosim[500][1000];
int resPC[500][1000];
double SimilarityArrayViaCoSim[500][500];
double SimilarityArrayViaPC[500][500];

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

//cosineSimilarity implementationh
double computeSimViaCoSim(int u1, int u2)
{
    int dimensionality = 0;
    double dotProd = 0;
    double intermediate = 0;
    int indexOfSharedMovie = -1;
    double discrim1 = 0;
    double discrim2 = 0;
    ofstream logFile;
    //open the file in append mode
    logFile.open("../intermediates/computeSimViaCoSim.txt", ios::app);
    logFile << "Sim(" << u1 << "," << u2 << ") = ";

    for (int i = 0; i < 1000; i++)
    {
        // logFile << "itteration = " << i << endl;
        intermediate = trainArray[u1][i] * trainArray[u2][i];

        if (intermediate != 0)
        {
            // logFile << "itteration = " << i << "intermediate = " << intermediate << std::endl;
            indexOfSharedMovie = i;
            dimensionality++;
            // logFile << "dimensionality = " << dimensionality << std::endl;
            discrim1 += trainArray[u1][i] * trainArray[u1][i];
            // logFile << "discrim1 = " << discrim1 << std::endl;
            discrim2 += trainArray[u2][i] * trainArray[u2][i];
            // logFile << "discrim2 = " << dimensionality << std::endl;
            dotProd += intermediate;
            // logFile << "dotProd = " << dotProd << std::endl;
        }
    }
    if (dimensionality == 0)
    {
        logFile << " 0" << endl;
        logFile.close();
        return 0;
    }
    if (dimensionality == 1)
    {
        intermediate = (5 - (abs(trainArray[u1][indexOfSharedMovie] - trainArray[u2][indexOfSharedMovie]))) / 5;
        logFile << intermediate << endl;
        logFile.close();
        return intermediate;
    }
    double denominator = sqrt(discrim1) * sqrt(discrim2);
    logFile << dotProd << " / " << denominator;
    denominator = dotProd / denominator;
    logFile << " = " << denominator << endl;
    logFile.close();
    return denominator;
}
double computeSimViaPC(int u1, int u2)
{
    int dimensionality = 0;
    double dotProd = 0;
    double intermediate1 = 0;
    double intermediate2 = 0;
    double intermediate = 0;
    double Denominator;
    double similarity;
    double discrim1 = 0;
    double discrim2 = 0;
    ofstream logFile;
    logFile.open("../intermediates/computeSimViaPC.txt", ios::app);
    logFile << "Sim(" << u1 << "," << u2 << ") = ";
    for (int i = 0; i < 1000; i++)
    {
        if (trainArray[u1][i] != 0 && trainArray[u2][i] != 0)
        {
            logFile << "(iuf factor = " << IUFArray[i] << ") ";
            intermediate1 = IUFArray[i] * (trainArray[u1][i] - UserAverageArray[u1]);
            intermediate2 = IUFArray[i] * (trainArray[u2][i] - UserAverageArray[u2]);
            discrim1 += intermediate1 * intermediate1;
            discrim2 += intermediate2 * intermediate2;
            dotProd += intermediate1 * intermediate2;
            dimensionality++;
        }
    }
    Denominator = sqrt(discrim1) * sqrt(discrim2);
    if (dimensionality == 0)
    {
        logFile << " 0 (no commonly rated movies \n";
        logFile.close();
        return 0;
    }
    similarity = dotProd / Denominator;
    if (isnan(similarity))
    {
        logFile << "0 --- nan ---- dotProd = " << dotProd << " Denominator = " << Denominator << " with dimensionality = " << dimensionality << endl;
        logFile.close();
        return 0;
    }

    logFile << similarity << " with dimensionality = " << dimensionality << endl;
    logFile.close();
    return similarity;
}
//SimilarityArrayViaCoSim must be computed before calling here
int predictRatingViaCoSim(int userIndex, int movieIndex)
{
    double tempSim = 0;
    double Numerator = 0;
    double Denominator = 0;
    std::ofstream logFile;
    logFile.open("../intermediates/predictRatingViaCoSim.txt", ios::app);
    logFile << "rating(" << userIndex << "," << movieIndex << ") = ";
    for (int i = 0; i < 200; i++)
    {
        if (trainArray[i][movieIndex] != 0)
        {
            tempSim = SimilarityArrayViaCoSim[userIndex][i];
            // computeSimViaCoSim(userIndex, i);
            Denominator += tempSim;
            Numerator += tempSim * trainArray[i][movieIndex];
        }
    }
    double predVal = Numerator / Denominator;
    // std::cout << "predicted value = " << predVal << "\n";
    if (isnan(predVal))
    {
        logFile << Numerator << " / " << Denominator << " = ";
        predVal = MovieAverageArray[movieIndex];
        logFile << predVal << " = given movie's average -> " << endl;
    }
    else
    {
        logFile << predVal << "->";
    }
    if (predVal < 1.5)
    {
        logFile << 1 << endl;
        logFile.close();
        return 1;
    }
    if (predVal >= 1.5 && predVal < 2.5)
    {
        logFile << 2 << endl;
        logFile.close();
        return 2;
    }
    if (predVal >= 2.5 && predVal < 3.5)
    {
        logFile << 3 << endl;
        logFile.close();
        return 3;
    }
    if (predVal >= 3.5 && predVal < 4.5)
    {
        logFile << 4 << endl;
        logFile.close();
        return 4;
    }
    logFile << 5 << endl;
    logFile.close();
    return 5;
}

//SimilarityArrayViaPC must be computed before calling here
int predictRatingViaPC(int userIndex, int movieIndex)
{
    double tempSim = 0;
    double Numerator = 0;
    double Denominator = 0;
    double NumUsersCompairedTo = 0;
    double predVal;
    ofstream logFile;
    logFile.open("../intermediates/predictRatingViaPC.txt", ios::app);
    logFile << "rating(" << userIndex << "," << movieIndex << ") = ";
    for (int i = 0; i < 200; i++)
    {
        if (trainArray[i][movieIndex] != 0)
        {
            NumUsersCompairedTo++;
            tempSim = SimilarityArrayViaPC[userIndex][i];
            if (tempSim != SimilarityArrayViaPC[i][userIndex])
            {
                logFile << "ERROR WITH ASSOCIATIVITY OF SimilarityArrayViaPC \n";
            }

            if (tempSim < 0)
            {
                Denominator -= tempSim;
            }
            else
            {
                Denominator += tempSim;
            }
            Numerator += tempSim * (trainArray[i][movieIndex] - UserAverageArray[i]);
        }
    }
    if (NumUsersCompairedTo == 0 || Denominator == 0)
    {
        logFile << " --no valid users to compair to / or Denominator = 0 -- ";
        predVal = MovieAverageArray[movieIndex];
    }
    else
    {
        predVal = (Numerator / Denominator) + UserAverageArray[userIndex];
    }
    if (predVal < 1.5)
    {
        predVal = 1;
    }
    else if (predVal < 2.5)
    {
        predVal = 2;
    }
    else if (predVal < 3.5)
    {
        predVal = 3;
    }
    else if (predVal < 4.5)
    {
        predVal = 4;
    }
    else
    {
        predVal = 5;
    }
    logFile << predVal << endl;
    logFile.close();
    return predVal;
}

void runCoSim()
{
    int temp;
    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            temp = predictRatingViaCoSim(i, j);
            // std::cout << "temp = " << temp << std::endl;
            resCosim[i][j] = temp;
        }
    }
}
void runPC()
{
    int temp;
    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            temp = predictRatingViaPC(i, j);
            // std::cout << "temp = " << temp << std::endl;
            resPC[i][j] = temp;
        }
    }
}
int main()
{
    initializer();
    //run the prediction algorithms
    runCoSim();
    runPC();
    printGlobalState();
    printResults();
}
