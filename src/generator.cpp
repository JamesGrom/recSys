#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "generator.h"

using namespace std;
void initializer()
{
    //clear all append dependent logFiles
    ofstream fileObj;
    fileObj.open("../intermediates/computeSimViaCoSim.txt");
    fileObj << " ";
    fileObj.close();
    fileObj.open("../intermediates/predictRatingViaCoSim.txt");
    fileObj << " ";
    fileObj.close();
    fileObj.open("../intermediates/computeSimViaPC.txt");
    fileObj << " ";
    fileObj.close();
    fileObj.open("../intermediates/predictRatingViaPC.txt");
    fileObj << " ";
    fileObj.close();
    // fileObj.open("../intermediates/");

    for (size_t i = 0; i < 500; i++)
    {
        UserAverageArray[i] = 0;
        for (size_t j = 0; j < 1000; j++)
        {
            if (j < 500)
            {
                SimilarityArrayViaCoSim[i][j] = 0;
                SimilarityArrayViaPC[i][j] = 0;
            }
            trainArray[i][j] = 0;
            resCosim[i][j] = 0;
            resPC[i][j] = 0;
            MovieAverageArray[j] = 0;
        }
    }
    synthTrainMatrix();
    genUserAverageArray();
    genMovieAverageArray();
    genIUFArray();
    genSimilarityArrayViaCoSim();
    genSimilarityArrayViaPC();
    genSimilarityArrayViaItemBased();
}

//generates the SimilarityArrayViaCoSim
void genSimilarityArrayViaCoSim()
{
    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            SimilarityArrayViaCoSim[i][j] = computeSimViaCoSim(i, j);
        }
    }
}

//generates the SimilarityArrayViaPC
void genSimilarityArrayViaPC()
{
    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            SimilarityArrayViaPC[i][j] = computeSimViaPC(i, j);
        }
    }
}

//generates the SimilarityArrayViaItemBased
void genSimilarityArrayViaItemBased()
{
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            SimilarityArrayViaItemBased[i][j] = computeSimBetweenMovies(i, j);
        }
    }
}

//generates the IUFArray
void genIUFArray()
{
    double numRatings;
    double numUsers = 200.0;
    for (int i = 0; i < 1000; i++)
    {
        numRatings = 0;
        for (int j = 0; j < 200; j++)
        {
            if (trainArray[j][i] != 0)
            {
                numRatings++;
            }
        }
        IUFArray[i] = log((numRatings / numUsers));
    }
}

//should be adjusted based on the average ratings given to the movies that are used in computing the user average
void genUserAverageArray()
{
    double ComputedAverageRatingGiven = 0;
    double numRated = 0;
    double sumRatings = 0;
    double temp;
    for (size_t i = 0; i < 500; i++)
    {
        numRated = 0;
        sumRatings = 0;
        for (size_t j = 0; j < 1000; j++)
        {
            if (trainArray[i][j] != 0)
            {
                numRated++;
                sumRatings += trainArray[i][j];
            }
        }
        if (numRated == 0)
        {
            UserAverageArray[i] = -1;
        }
        else
        {
            UserAverageArray[i] = sumRatings / numRated;
        }
        double count = 0;
        double sum = 0;
        for (size_t i = 0; i < 500; i++)
        {
            if (UserAverageArray[i] != -1)
            {
                count++;
                sum += UserAverageArray[i];
            }
        }
        ComputedAverageRatingGiven = sum / count;
        for (size_t i = 0; i < 500; i++)
        {
            if (UserAverageArray[i] == -1)
            {
                UserAverageArray[i] = ComputedAverageRatingGiven;
            }
        }
    }
}

//pearson corelated movie averages
void genMovieAverageArray()
{
    //traverse all the movies and compute their average rating
    double sumRatings;
    double numRatings;
    double temp;
    for (size_t i = 0; i < 1000; i++)
    {
        //initialize the array to have the movie rated as 0
        MovieAverageArray[i] = 0;
        sumRatings = 0;
        numRatings = 0;
        temp = 0;
        for (size_t j = 0; j < 200; j++)
        {
            //grab user j's rating of movie i
            temp = trainArray[j][i];
            if (temp != 0)
            {
                //the user has rated the movie
                //temp = temp - UserAverageArray[j]; //perform pearson correlation correction
                numRatings++;
                sumRatings += temp;
            }
        }
        temp = sumRatings / numRatings;
        //denote fill the array with the appropriate rounded rating from the movie's average rating
        //return a rounded version of the average rating
        if (isnan(temp))
        {
            // invalid source info , thus just use the average rating given to all movies
            MovieAverageArray[i] = 3;
        }
        else
        {
            MovieAverageArray[i] = temp;
        }
    }
}
