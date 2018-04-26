#include "utils.h"

static inline void trim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

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
        while ( infile.good() )
        {
            char _s[256];
            char _r[256];
            if( infile.getline( _s, 256, ',' ) && infile.getline( _r, 256 ) )
            {
                std::string s( _s );
                std::string r( _r );
                trim( s ); trim( r );

                search.push_back( s );
                replace.push_back( r );
            }
        }
    }

    infile.close();
}
