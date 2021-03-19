#ifndef GENERATOR_H
#define GENERATOR_H
#include "main.h"

//initializes all global variables derived from given data
void initializer();

//generates the UserAverageArray and calls printUserAverageArray
//trainArray has been initialized
void genUserAverageArray();

//generates the MovieAverageArray and calls printMovieAvarageArray
//trainArray has been initialized
void genMovieAverageArray();

void genSimilarityArrayViaCoSim();
void genSimilarityArrayViaPC();
void genSimilarityArrayViaItemBased();
void genIUFArray();

#endif