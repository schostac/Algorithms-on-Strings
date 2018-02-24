/*
 * Coursera/Algorithms on Strings/Week 2/Problem 2:
 * Reconstruct a String from its Burrows–Wheeler Transform
 * Grading: 'Good job! (Max time used: 0.26/2.00, max memory used: 45449216/536870912.)'
 * Respect Coursera Honor Code
 * Copyright © 2018. All rights reserved
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Comp
{
  bool operator()(const char *s1, const char *s2)
  {
    return (*s1 == *s2) ? s1 < s2 : *s1 < *s2;
  }
};

string InverseBWT(const string &bwt)
{

  if (bwt.size() == 1)
    return bwt;

  auto num = bwt.size();

  vector<const char *> sbwt;
  sbwt.reserve(num);

  for (const auto &s : bwt)
    sbwt.push_back(&s);

  sort(sbwt.begin(), sbwt.end(), Comp());

  string r = "$";
  r.reserve(num--);

  const char *c = &bwt[0];
  r += c[0];

  while (--num)
  {
    c = &bwt[lower_bound(sbwt.begin(), sbwt.end(), c, Comp()) - sbwt.begin()];
    r += c[0];
  }

  reverse(r.begin(), r.end());
  return r;
}

int main()
{
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
