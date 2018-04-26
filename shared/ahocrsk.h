#pragma once
#include <queue>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <cstring>

class AhoCorasick
{
	struct Node
	{
		Node *suff;
		Node *next[256];
		std::vector<int> pats;
		std::vector<char> out;

		Node()
		{
			suff = 0;
			memset(next, 0, sizeof(next));
		}
	};

	std::vector<int> pat_lens;
	Node *trie;

	Node *suffix(Node *x, unsigned char c)
	{
		while (x->next[c] == 0)
		{
			x = x->suff;
		}
		return x->next[c];
	}

	void insert(Node *x, std::string s, int id);

public:
	AhoCorasick();
	AhoCorasick(std::vector<std::string> &p);
	std::stringstream replace(std::vector<unsigned char> &s, std::vector<std::string> &replace);
	static void ParseTable(std::istream &table, std::vector<std::string> &search, std::vector<std::string> &replace);
};
