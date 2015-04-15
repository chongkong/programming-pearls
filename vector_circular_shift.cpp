#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

ostream& operator<<(ostream& os, vector<char> vec) {
  for (char elem : vec) {
    cout << elem;
  }
  return os;
}

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

vector<char> genvec(int size) {
  vector<char> vec(size);
  for (int i = 0; i < size; i++) {
    vec[i] = 'a' + (i % 26);
  }
  return vec;
}

void juggle_shift(vector<char> &vec, int offset) {
  int g = gcd(vec.size(), offset);
  for (int i = 0; i < g; i++) {
    int tmp = vec[i];
    int curr = i, next = (i + offset) % vec.size();
    while (next != i) {
      vec[curr] = vec[next];
      curr = next;
      next = (next + offset) % vec.size();
    }
    vec[curr] = tmp;
  }
}

void swap_same_size(vector<char> &vec, int left, int right, int size) {
  for (int i = 0; i < size; i++) {
    int tmp = vec[left + i];
    vec[left + i] = vec[right + i];
    vec[right + i] = tmp;
  }
}

void recur_swap(vector<char> &vec, int lmin, int lmax, int rmin, int rmax) {
  int lsize = lmax - lmin + 1, rsize = rmax - rmin + 1;
  int min_size = (lsize > rsize) ? rsize : lsize;

  swap_same_size(vec, lmin, rmax - min_size + 1, min_size);
  if (lsize < rsize)
    recur_swap(vec, lmin, lmax, rmin, rmax - lsize);
  else if (lsize > rsize)
    recur_swap(vec, lmin + rsize, lmax, rmin, rmax);
}

void recur_shift(vector<char> &vec, int offset) {
  recur_swap(vec, 0, offset - 1, offset, vec.size() - 1);
}

void reverse(vector<char> &vec, int min, int max) {
  for (; min != --max; ++min) {
    swap(vec[min], vec[max]);
  }
}

void reverse_shift(vector<char> &vec, int offset) {
  reverse(vec, 0, offset - 1);
  reverse(vec, offset, vec.size() - 1);
  reverse(vec, 0, vec.size() - 1);
}

int main() {
  int size, offset;
  cin >> size >> offset;

  auto vec = genvec(size);
  auto beg = system_clock::now();
  juggle_shift(vec, offset);
  auto end = system_clock::now();
  cout << duration_cast<milliseconds>(end - beg).count() << endl;
  if (size < 30)
    cout << vec << endl;
  
  vec = genvec(size);
  beg = system_clock::now();
  recur_shift(vec, offset);
  end = system_clock::now();
  cout << duration_cast<milliseconds>(end - beg).count() << endl;
  if (size < 30)
    cout << vec << endl;

  vec = genvec(size);
  beg = system_clock::now();
  reverse_shift(vec, offset);
  end = system_clock::now();
  cout << duration_cast<milliseconds>(end - beg).count() << endl;
  if (size < 30)
    cout << vec << endl;
}