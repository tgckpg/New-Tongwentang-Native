#include "utils.h"
#include "ahocrsk.h"

std::vector<unsigned char> ReadAllBytes(char const* filename)
{
    std::ifstream ifs(filename, std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<unsigned char> result(pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read( (char*) &result[0], pos);

    return result;
}

std::tuple<int, int> ReadKVPairs(char const* filename, std::vector<std::string> &search, std::vector<std::string> &replace )
{
    std::ifstream infile(filename);

    if ( infile.is_open() )
    {
        AhoCorasick::ParseTable( infile, search, replace );
    }

    infile.close();
}
