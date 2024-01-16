/*
 * Name:            Noah Nininger
 * Date Submitted:  05/01/2023
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

const int N = 14;
typedef pair<double,double> Point;
vector<Point> P(N);
vector<int> tour(N), best_tour(N);
vector<bool> used(N);
double best_len = 999999999, mindist = 999999;
map<Point, int> cities;
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
                      "Kansas City"};

double dist(int i, int j)
{
  double dx = P[(i+N)%N].first - P[(j+N)%N].first;
  double dy = P[(i+N)%N].second - P[(j+N)%N].second;
  return sqrt(dx*dx + dy*dy);
}

double tourlen(vector<int> &T)
{
  double total = 0.0;
  for (int i=0; i<N; i++)
    total += dist(T[i], T[(i+1)%N]);
  return total;
}

void solve(int index, double so_far) {
  // base case
  if (index == N) {
    // Bug was here -- had 0 instead of tour[0], etc.
    if (so_far + dist(tour[0],tour[N-1]) < best_len) {
      best_tour = tour;
      best_len = so_far + dist(tour[0],tour[N-1]);
    }
    return;
  }

  // Can I prune my search?
  if (so_far + mindist * (N-index+1) > best_len) return;
  
  // try all possible next cities
  for (int city=0; city<N; city++)
    if (!used[city]) {
      tour[index] = city;
      used[city] = true;
      solve(index+1, so_far + dist(city, tour[index-1]));
      used[city] = false;
    }
}

int main(void)
{
  ifstream fin("cities.txt");
  for (int i=0; i<N; i++)
  {
    fin >> P[i].first >> P[i].second;
    cities[P[i]] = i;
  }
  tour[0] = 0;  // start at city zero
  used[0] = true;
  for (int i=0; i<N; i++)
    for (int j=i+1; j<N; j++)
      mindist = min(mindist, dist(i,j));
  solve(1, 0.0);
  for (int i=0; i<N; i++) cout << cityNames[best_tour[i]] << endl;
  cout << "\nTotal length: " << best_len << "\n";
  return 0;
}
