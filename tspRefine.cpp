/*
 * Name:            Noah Nininger
 * Date Submitted:  05/02/2023
 * Lab Section:     001
 * Assignment Name: Lab 11
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

const int N = 14; //Number of cities in cities.txt
typedef pair<double,double> Point; //<latitude,longitude> of a city
vector<Point> P(N), best; //P - current solution, best - best solution
map<Point, int> cities; //Point (latitude,longitude) -> index of city in cities.txt order
string cityNames[] = {"New York City",
                      "Chicago",
                      "Los Angeles",
                      "Toronto",
                      "Houston",
                      "Montreal",
                      "Mexico City",
                      "Vancouver",
                      "Atlanta",
                      "Denver",
                      "San Juan",
                      "New Orleans",
                      "Miami",
                      "Kansas City"}; //Index of a city -> city name

//Calculates "distance"
//Units are lat./long. "degrees" on an x-y plane
//to simplify calculations (not mi/km on globe)
double dist(int i, int j)
{
  double dx = P[(i+N)%N].first - P[(j+N)%N].first;
  double dy = P[(i+N)%N].second - P[(j+N)%N].second;
  return sqrt(dx*dx + dy*dy);
}

bool refine(double &len)
{
  //Implement this function
  
  //Should iterate through each pair of edges in the tour
  //checking if there is a decrease in tour length by
  //replacing these edges with their diagonals (see lab description)
  for (int i = 0; i < N; i++)
  {
    for (int j = (i + 2); j < N; j++)
    {
     //If the decrease is more than a minimum threshold (such as 0.0001)
      if (dist(i, (i + 1)) + dist(j, (j + 1)) > 
          dist(i, j) + dist((i + 1), (j + 1)))
      {
       //swap these edges for their diagonals (see description) and return true
        swap(P[i + 1], P[j]);

       // updates length
        len = 0;
        for (int k = 0; k < N; k++)
          { len += dist(k, (k + 1)); }

        return true;
      }
    }
  }

  //Otherwise return false after iterating through all possible edge pairs
  //if swapping a pair of edges for their diagonals fails to decrease
  //tour length beyond a minimum threshold
  return false;
}

//Returns best length for test case
double tspRefine()
{
  double best_len = 999999999;
  ifstream fin("cities.txt");
  for (int i=0; i<N; i++)
  {
    fin >> P[i].first >> P[i].second;
    cities[P[i]] = i;
  }
  
  //Use a loop that will repeat a certain number of times starting with
  //a randomly generated tour (P)
  //First calculate the length of this randomly generated tour
  double len = 0;
  for (int i = 0; i < N; i++)
    { len += dist(i, i + 1); }

  //Then run refine() to rearrange the ordering of the cities in the
  //tour until refine() returns false
  while (refine(len));

  //Finally, if final tour length < best_len replace best with the
  //current tour (P) and update best_len
  if (len < best_len)
  {
    best_len = len;
    best = P;
  }

  for (auto p : best) cout << cityNames[cities[p]] << endl;
  cout << "\nTotal length: " << best_len << "\n";
  return best_len;
}

/*
int main(void)
{
  double best_len = 999999999;
  best_len=tspRefine();
  return 0;
}*/
