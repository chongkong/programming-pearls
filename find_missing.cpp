#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

vector<int> randgen(int size, int max) {
  srand(time(NULL));
  vector<int> rand_vec(size);
  for (int i = 0; i < size; i++)
    rand_vec[i] = rand() % max;
  return rand_vec;
}

int count_num_in_range(vector<int> &vec, int low, int high) {
  int cnt = 0;
  for (int elem : vec) {
    if (low <= elem && elem <= high) cnt++;
  }
  return cnt;
}

int find_missing_in_range(vector<int> &vec, int low, int high) {
  if (low >= high)
    return low;

  int mid = (low + high) / 2;
  if (count_num_in_range(vec, low, mid) < mid - low + 1)
    return find_missing_in_range(vec, low, mid);
  else
    return find_missing_in_range(vec, mid + 1, high);
}

int find_missing(vector<int> &vec) {
  return find_missing_in_range(vec, 0, vec.size() - 1);
}

bool contains_num(vector<int> &vec, int num) {
  for (int elem : vec)
    if (elem == num) return true;
  return false;
}

int main() {
  int size, max;
  cin >> size >> max;
  if (size > max) 
    return 0;
  
  for (int i = 0; i < 100; i++) {
    cout << "test #" << i + 1 << ": ";
    auto rand_vec = randgen(size, max);
    auto missing_num = find_missing(rand_vec);
    if (contains_num(rand_vec, missing_num))
      cout << "failed" << endl;
    else
      cout << "succeeded" << endl;
  }
}