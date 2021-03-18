#ifndef GLOBALS_H
#define GLOBALS_H

//array of data given to us by the .txt files
// x index:
// userID = index + 1
// index = userID -1
// 0-199 indexes (users 1 - 200)
// 200-299 indexes (users 201-300)
// 300-399 indexes (users 301-400)
// 400-499 indexes (users 401-500)
// y index;
// MovieID = MovieIndex + 1
// MovieIndex = MovieID - 1
//0-999 indexes (movies 1-1000)
extern int trainArray[500][1000];

//floating point values for a user's average rating
// userID's average= UserAverageArray[userID -1];
// UserIndex's average  = UserAverageArray[UserIndex]
extern double UserAverageArray[500];

//floating point values for a movie's average rating
//movieID's average = MovieAverageArray[movieID -1];
//movieIndex's average = MovieAverageArray[movieIndex];
// holds the pearson correlated movie's average score
extern double MovieAverageArray[1000];

//holds the prediction results for the appropriate algorithm
//same indexing systems as the trainArray
// we compute the predictions for the trainArray values as well, so we can test our predictions

extern int resCosim[500][1000];
extern int resPC[500][1000];

#endif