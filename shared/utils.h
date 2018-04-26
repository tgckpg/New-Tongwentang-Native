#pragma once
#include <fstream>
#include <vector>
#include <sstream>
#include <tuple>
#include <algorithm>

std::vector<unsigned char> ReadAllBytes(char const* filename);
std::tuple<int, int> ReadKVPairs(char const* filename, std::vector<std::string> &search, std::vector<std::string> &replace );
