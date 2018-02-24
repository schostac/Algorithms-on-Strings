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

using Symbols = std::vector<int>;

inline int getIndexInSymbols(char s)
{
  switch (s)
  {
  case 'A':
    return 0;
  case 'C':
    return 1;
  case 'G':
    return 2;
  case 'T':
    return 3;
  default:
    return 4;
  }
}

inline int getIndexInRrightColumn(Symbols &sm, char s, int cnt)
{
  switch (s)
  {
  case 'A':
    return cnt;
  case 'C':
    return sm[0] + cnt;
  case 'G':
    return sm[1] + sm[0] + cnt;
  case 'T':
    return sm[2] + sm[1] + sm[0] + cnt;
  default:
    return 0;
  }
}

std::string inverseBWT(const std::string &bwt)
{
  if (bwt.size() == 1)
  {
    return bwt;
  }

  Symbols symbols(5, 0);
  std::vector<int> indexes;
  indexes.reserve(bwt.size());

  for (int i = 0; i < bwt.size(); ++i)
  {
    indexes.emplace_back(++symbols[getIndexInSymbols(bwt[i])]);
  }

  std::string r = "$";
  r.reserve(bwt.size());

  char s = bwt[0];
  int j = indexes[0];

  r += s;

  for (int i = 2; i < bwt.size(); ++i)
  {
    int indexInRrightColumn = getIndexInRrightColumn(symbols, s, j);
    r += bwt[indexInRrightColumn];
    j = indexes[indexInRrightColumn];
    s = r.back();
  }

  std::reverse(r.begin(), r.end());
  return r;
}

int main()
{
  std::string bwt;
  std::cin >> bwt;
  std::cout << inverseBWT(bwt) << std::endl;
  return 0;
}
