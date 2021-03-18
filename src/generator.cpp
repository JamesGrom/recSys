#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "generator.h"

void initializer()
{
    for (size_t i = 0; i < 500; i++)
    {
        UserAverageArray[i] = 0;
        for (size_t j = 0; j < 1000; j++)
        {
            // std::cout << trainArray[i][j];

            trainArray[i][j] = 0;
            resCosim[i][j] = 0;
            resPC[i][j] = 0;
            MovieAverageArray[j] = 0;
        }
    }
    synthTrainMatrix();
    genUserAverageArray();
    genMovieAverageArray();
    printGlobalState();
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
                temp = temp - UserAverageArray[j]; //perform pearson correlation correction
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
            MovieAverageArray[i] = 0;
        }
        else
        {
            MovieAverageArray[i] = temp;
        }
    }
}
