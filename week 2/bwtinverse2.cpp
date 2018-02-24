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
#include <unordered_map>

using SymbolsMap = std::unordered_map<char, int>;

inline int getIndexInRrightColumn(SymbolsMap &sm, char s, int cnt)
{
  switch (s)
  {
  case 'A':
    return cnt;
  case 'C':
    return sm['A'] + cnt;
  case 'G':
    return sm['A'] + sm['C'] + cnt;
  case 'T':
    return sm['A'] + sm['C'] + sm['G'] + cnt;
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

  SymbolsMap symbolsMap;
  std::vector<int> indexes;
  indexes.reserve(bwt.size());

  for (int i = 0; i < bwt.size(); ++i)
  {
    indexes.emplace_back(++symbolsMap[bwt[i]]);
  }

  std::string r = "$";
  r.reserve(bwt.size());

  char s = bwt[0];
  int j = indexes[0];

  r += s;

  for (int i = 2; i < bwt.size(); ++i)
  {
    int indexInRrightColumn = getIndexInRrightColumn(symbolsMap, s, j);
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
