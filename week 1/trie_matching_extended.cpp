/*
 * Coursera/Algorithms on Strings/Week 1/Problem 3: Extend TrieMatching
 * Grading: 'Good job! (Max time used: 0.25/1.00, max memory used: 55250944/536870912.)'
 * Respect Coursera Honor Code
 * Copyright © 2018. All rights reserved
 *
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Value
{
  int next_vertex;
  bool is_pattern{false};
  operator int() const { return next_vertex; }
  int &operator=(int val) { return (next_vertex = val); }
};

using edges = map<char, Value>;
using trie = vector<edges>;

trie build_trie(vector<string> &patterns)
{

  if (patterns.empty())
  {
    return trie{};
  }

  trie t{edges{}};

  int root{0}, cnt{0};

  for (auto &p : patterns)
  {
    int current = root;
    int prev = root;

    for (auto s : p)
    {
      if (t[current].find(s) != t[current].end())
      {
        prev = current;
        current = t[current][s];
      }
      else
      {
        t.emplace_back(edges{});
        prev = current;
        t[current][s] = ++cnt;
        current = cnt;
      }
    }
    t[prev][p.back()].is_pattern = true;
  }
  return t;
}

vector<int> trie_matching(const string &text, int n, vector<string> &patterns)
{
  vector<int> positions;
  trie patterns_trie = build_trie(patterns);

  for (int i = 0; i < text.size(); ++i)
  {
    int current_vertex = 0, current_symbol_index = i;
    char symbol = text[current_symbol_index];
    while (patterns_trie[current_vertex].find(symbol) != patterns_trie[current_vertex].end())
    {
      if (patterns_trie[current_vertex][symbol].is_pattern)
      {
        positions.push_back(i);
        break;
      }
      current_vertex = patterns_trie[current_vertex][symbol];
      symbol = text[++current_symbol_index];
    }
  }

  return positions;
}

int main(void)
{
  string text;
  cin >> text;

  int n;
  cin >> n;

  vector<string> patterns(n);
  for (int i = 0; i < n; i++)
  {
    cin >> patterns[i];
  }

  vector<int> ans = trie_matching(text, n, patterns);

  for (int i = 0; i < (int)ans.size(); i++)
  {
    cout << ans[i];
    if (i + 1 < (int)ans.size())
    {
      cout << " ";
    }
    else
    {
      cout << endl;
    }
  }

  return 0;
}
