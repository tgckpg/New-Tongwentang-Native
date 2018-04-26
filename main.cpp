#include <iostream>

#include "shared/ahocrsk.h"
#include "shared/utils.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<unsigned char> buffer = ReadAllBytes( argv[1] );

    vector<string> search, replace;
    ReadKVPairs( "words.txt", search, replace );

    AhoCorasick ac( search );

    stringstream s01 = ac.replace( buffer, replace );
    s01.seekp( 0, s01.end );
    long len = s01.tellp();
    s01.seekp( 0, s01.beg );

    search.clear(); replace.clear();

    buffer = vector<unsigned char>( len );

    ReadKVPairs( "phrases.txt", search, replace );

    ac = AhoCorasick( search );
    s01.read( ( char* ) &buffer[0], len );

    stringstream s02 = ac.replace( buffer, replace );
    cout << s02.str();
    return 0;
}
