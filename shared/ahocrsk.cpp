#include "pch.h"
#include "ahocrsk.h"

static inline void trim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

AhoCorasick::AhoCorasick()
{
	trie = nullptr;
}

AhoCorasick::AhoCorasick(std::vector<std::string> &p)
{
	trie = new Node;

	for (int i = 0; i < p.size(); i++)
	{
		insert(trie, p[i], i);
		int slen = p[i].size();
		pat_lens.push_back(slen);
	}

	std::queue<Node*> q;
	for (int i = 0; i < 256; i++)
	{
		if (trie->next[i])
		{
			trie->next[i]->suff = trie;
			q.push(trie->next[i]);
		}
		else
		{
			trie->next[i] = trie;
		}
	}

	while (q.empty() == 0)
	{
		Node *x = q.front();
		q.pop();
		for (int i = 0; i < x->out.size(); i++)
		{
			unsigned char c = (unsigned char)x->out[i];
			Node *y = x->next[c];
			y->suff = suffix(x->suff, c);
			y->pats.insert(y->pats.end(), y->suff->pats.begin(), y->suff->pats.end());
			q.push(y);
		}
	}
}

void AhoCorasick::ParseTable(std::istream &table, std::vector<std::string> &search, std::vector<std::string> &replace)
{
	while (!table.eof())
	{
		char _s[256];
		char _r[256];
		if (table.getline(_s, 256, ',') && table.getline(_r, 256))
		{
			std::string s(_s);
			std::string r(_r);
			trim(s); trim(r);

			search.push_back(s);
			replace.push_back(r);
		}
	}
}

void AhoCorasick::insert(Node *x, std::string s, int id)
{
	for (int i = 0; i < s.size(); i++)
	{
		unsigned char c = (unsigned char)s[i];
		if (x->next[c] == 0)
		{
			x->next[c] = new Node;
			x->out.push_back(c);
		}
		x = x->next[c];
	}
	x->pats.push_back(id);
}

std::stringstream AhoCorasick::replace(std::vector<unsigned char> &s, std::vector<std::string> &replace)
{
	Node *x = trie;

	std::stringstream ss;

	for (long i = 0; i < s.size(); i++)
	{
		ss << s[i];
		x = suffix(x, s[i]);
		for (int k = 0; k < x->pats.size(); k++)
		{
			int index = x->pats[k];

			ss.seekp(-pat_lens[ index ], ss.cur);
			ss << replace[ index ];
			break;
		}
	}

	return ss;
}
