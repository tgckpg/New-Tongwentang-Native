#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <stdio.h>

#include "wconv_gtable.h"
#include "wUTF8.h"


using namespace std;



int main(int argc, char* argv[])
{
	const char* file = argv[1];
	ifstream conv_file(file, ifstream::binary);

	if(conv_file)
	{
		const unsigned char* byte_arr;
		char* byte_arr_c;
		const char* out_phrase;
		int step_size = 0;
		int arg_size;

		while(conv_file.good())
		{

			conv_file.seekg(0, conv_file.end);
			// Get file length
			arg_size = conv_file.tellg();
			conv_file.seekg(0, conv_file.beg);

			byte_arr_c = new char[arg_size];

			// read file
			conv_file.read(byte_arr_c, arg_size);

			if (!conv_file)
			{
				conv_file.close();
				return 2;
			}

			conv_file.close();

			stringstream conv_stream;
			byte_arr = (const unsigned char*)byte_arr_c;

			// Phase 1, translate words
			for(int i = 0; i < arg_size; i ++)
			{
				if(is_utf8_byte6(byte_arr, i))
				{
					match_w_byte6(byte_arr, i, out_phrase, step_size);
					if(0 < step_size)
					{
						conv_stream << out_phrase;
					}
					else
					{
						// if word does not match, pad this word
						step_size = 5;
						conv_stream << byte_arr[i] << byte_arr [i + 1] << byte_arr [i + 2] << byte_arr [i + 3] << byte_arr [i + 4] << byte_arr[i + 5] ;
					}
				}
				else if(is_utf8_byte5(byte_arr, i))
				{
					match_w_byte5(byte_arr, i, out_phrase, step_size);
					if(0 < step_size)
					{
						conv_stream << out_phrase;
					}
					else
					{
						// if word does not match, pad this word
						step_size = 4;
						conv_stream << byte_arr[i] << byte_arr [i + 1] << byte_arr [i + 2] << byte_arr [i + 3] << byte_arr [i + 4] ;
					}
				}
				else if(is_utf8_byte4(byte_arr, i))
				{
					match_w_byte4(byte_arr, i, out_phrase, step_size);
					if(0 < step_size)
					{
						conv_stream << out_phrase;
					}
					else
					{
						// if word does not match, pad this word
						step_size = 3;
						conv_stream << byte_arr[i] << byte_arr [i + 1] << byte_arr [i + 2] << byte_arr [i + 3] ;
					}
				}
				else if(is_utf8_byte3(byte_arr, i))
				{
					match_w_byte3(byte_arr, i, out_phrase, step_size);
					if(0 < step_size)
					{
						conv_stream << out_phrase;
					}
					else
					{
						// if word does not match, pad this word
						step_size = 2;
						conv_stream << byte_arr[i] << byte_arr [i + 1] << byte_arr [i + 2] ;
					}
				}
				else if(is_utf8_byte2(byte_arr, i))
				{
					match_w_byte2(byte_arr, i, out_phrase, step_size);
					if(0 < step_size)
					{
						conv_stream << out_phrase;
					}
					else
					{
						// if word does not match, pad this word
						step_size = 1;
						conv_stream << byte_arr[i] << byte_arr [i + 1] ;
					}
				}
				else if(is_ascii(byte_arr, i))
				{
					match_w_ascii(byte_arr, i, out_phrase, step_size);
					if(0 < step_size)
					{
						conv_stream << out_phrase;
					}
					else
					{
						// if word does not match, pad this word
						step_size = 0;
						conv_stream << byte_arr[i];
					}
				}
				else
				{
					// Not a valid character, pad it
					step_size = 0;
					conv_stream << byte_arr[i];
				}
				i += step_size;
			}

			arg_size =  conv_stream.tellp();
			string s = conv_stream.str();
			conv_stream.str("");

			byte_arr = (const unsigned char*) s.c_str();

			// Phase 2	
			for(int i = 0; i < arg_size; i ++)
			{
				if(is_utf8_byte6(byte_arr, i))
				{
					match_p_byte6(byte_arr, i, out_phrase, step_size);
					if(0 < step_size)
					{
						conv_stream << out_phrase;
					}
					else
					{
						// if phrase does not match, pad this word
						step_size = 5;
						conv_stream << byte_arr[i] << byte_arr [i + 1] << byte_arr [i + 2] << byte_arr [i + 3] << byte_arr [i + 4] << byte_arr[i + 5] ;
					}
				}
				else if(is_utf8_byte5(byte_arr, i))
				{
					match_p_byte5(byte_arr, i, out_phrase, step_size);
					if(0 < step_size)
					{
						conv_stream << out_phrase;
					}
					else
					{
						// if phrase does not match, pad this word
						step_size = 4;
						conv_stream << byte_arr[i] << byte_arr [i + 1] << byte_arr [i + 2] << byte_arr [i + 3] << byte_arr [i + 4] ;
					}
				}
				else if(is_utf8_byte4(byte_arr, i))
				{
					match_p_byte4(byte_arr, i, out_phrase, step_size);
					if(0 < step_size)
					{
						conv_stream << out_phrase;
					}
					else
					{
						// if phrase does not match, pad this word
						step_size = 3;
						conv_stream << byte_arr[i] << byte_arr [i + 1] << byte_arr [i + 2] << byte_arr [i + 3] ;
					}
				}
				else if(is_utf8_byte3(byte_arr, i))
				{
					match_p_byte3(byte_arr, i, out_phrase, step_size);
					if(0 < step_size)
					{
						conv_stream << out_phrase;
					}
					else
					{
						// if phrase does not match, pad this word
						step_size = 2;
						conv_stream << byte_arr[i] << byte_arr [i + 1] << byte_arr [i + 2] ;
					}
				}
				else if(is_utf8_byte2(byte_arr, i))
				{
					match_p_byte2(byte_arr, i, out_phrase, step_size);
					if(0 < step_size)
					{
						conv_stream << out_phrase;
					}
					else
					{
						// if phrase does not match, pad this word
						step_size = 1;
						conv_stream << byte_arr[i] << byte_arr [i + 1] ;
					}
				}
				else if(is_ascii(byte_arr, i))
				{
					match_p_ascii(byte_arr, i, out_phrase, step_size);
					if(0 < step_size)
					{
						conv_stream << out_phrase;
					}
					else
					{
						// if phrase does not match, pad this word
						step_size = 0;
						conv_stream << byte_arr[i];
					}
				}
				else
				{
					// Not a valid character, pad it
					step_size = 0;
					conv_stream << byte_arr[i];
				}
				i += step_size;
			}

			cout << conv_stream.str();

			delete byte_arr_c;
			return 0;
		}
	}
	return 1;
}
