/*
 * Coursera/Algorithms on Strings/Weeks 3-4/Problem 3:
 * Pattern Matching with the Suffix Array
 * Grading: 'Good job! (Max time used: 0.17/1.00, max memory used: 20062208/536870912.)'
 * Respect Coursera Honor Code
 * Copyright © 2018. All rights reserved
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

constexpr int ALPHABET_SIZE = 5;

inline int getIndex(char c) noexcept
{
  switch (c)
  {
  case 'A':
    return 1;
  case 'C':
    return 2;
  case 'G':
    return 3;
  case 'T':
    return 4;
  default:
    return 0;
  }
}

std::vector<int> sortDoubled(const std::string &s, int L, const std::vector<int> &order, const std::vector<int> &cclass)
{
  std::vector<int> count(s.size());
  std::vector<int> newOrder(s.size());

  const int S = s.size();

  for (int i = 0; i < S; ++i)
  {
    ++count[cclass[i]];
  }

  for (int j = 1; j < S; ++j)
  {
    count[j] += count[j - 1];
  }

  for (int i = s.size() - 1; i >= 0; --i)
  {
    int start = (order[i] - L + s.size()) % s.size();
    newOrder[--count[cclass[start]]] = start;
  }

  return newOrder;
}

std::vector<int> computeCharacterClasses(const std::string &s, const std::vector<int> &order)
{
  std::vector<int> cclass(s.size());

  const int S = s.size();
  for (int i = 1; i < S; ++i)
  {
    if (s[order[i]] != s[order[i - 1]])
    {
      cclass[order[i]] = cclass[order[i - 1]] + 1;
    }
    else
    {
      cclass[order[i]] = cclass[order[i - 1]];
    }
  }

  return cclass;
}

std::vector<int> countingCharactersSort(const std::string &s) noexcept
{
  std::vector<int> order(s.size());
  std::vector<int> count(ALPHABET_SIZE);

  for (auto &c : s)
  {
    ++count[getIndex(c)];
  }

  for (int j = 1; j < ALPHABET_SIZE; ++j)
  {
    count[j] += count[j - 1];
  }

  for (int i = s.size() - 1; i >= 0; --i)
  {
    char c = s[i];
    count[getIndex(c)] -= 1;
    order[count[getIndex(c)]] = i;
  }
  return order;
}

std::vector<int> updateClasses(std::vector<int> &newOrder, std::vector<int> &cclass, int L)
{
  const int n = newOrder.size();
  std::vector<int> newCclass(n);

  for (int i = 1; i < n; ++i)
  {
    int cur = newOrder[i], prev = newOrder[i - 1];
    int mid = cur + L, midPrev = (prev + L) % n;

    if (cclass[cur] != cclass[prev] || cclass[mid] != cclass[midPrev])
    {
      newCclass[cur] = newCclass[prev] + 1;
    }
    else
    {
      newCclass[cur] = newCclass[prev];
    }
  }
  return newCclass;
}

std::vector<int> buildSuffixArray(const std::string &s)
{
  std::vector<int> order = countingCharactersSort(s);
  std::vector<int> cclass = computeCharacterClasses(s, order);
  int L = 1;

  const int S = s.size();
  while (L < S)
  {
    order = sortDoubled(s, L, order, cclass);
    cclass = updateClasses(order, cclass, L);
    L *= 2;
  }
  return order;
}

void suffixArrayPatternMatching(
  const std::string &text,
  const std::string &pattern,
  const std::vector<int> &suffixArray,
  vector<pair<int, int>> &results)
{
  int minIndex = 0;
  int maxIndex = text.size();

  while (minIndex < maxIndex)
  {
    int midIndex = (minIndex + maxIndex) / 2;
    if (strncmp(pattern.c_str(), text.c_str() + suffixArray[midIndex], pattern.size()) > 0)
    {
      minIndex = midIndex + 1;
    }
    else
    {
      maxIndex = midIndex;
    }
  }

  int start = minIndex;
  maxIndex = text.size();

  while (minIndex < maxIndex)
  {
    int midIndex = (minIndex + maxIndex) / 2;
    if (strncmp(pattern.c_str(), text.c_str() + suffixArray[midIndex], pattern.size()) < 0)
    {
      maxIndex = midIndex;
    }
    else
    {
      minIndex = midIndex + 1;
    }
  }

  int end = maxIndex;

  if (start > end)
  {
    return;
  }

  for (auto &p : results)
  {
    if (p.first <= start && end <= p.second)
    {
      return;
    }
    else if (p.first <= start && end > p.second)
    {
      if (p.second >= start)
      {
        p.second = end;
        return;
      }
    }
    else if (end >= p.first)
    {
      p.first = start;
      return;
    }
  }

  results.push_back(std::pair<int, int>(start, end));
}

int main()
{
  std::string text;
  cin >> text;
  text += '$';

  auto suffixArray = buildSuffixArray(text);

  unsigned n;
  cin >> n;

  std::string pattern;
  vector<pair<int, int>> results;

  while (n--)
  {
    cin >> pattern;
    suffixArrayPatternMatching(text, pattern, suffixArray, results);
  }

  for (auto &resp : results)
  {
    auto start = resp.first;
    auto end = resp.second;
    while (start < end)
    {
      cout << suffixArray[start++] << ' ';
    }
  }

  return 0;
}
