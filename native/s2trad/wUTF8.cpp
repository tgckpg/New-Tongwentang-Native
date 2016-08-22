bool is_utf8_byte6(unsigned char const* str, int start)
{
	// 6 Bytes sequesce 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	return (str[start] >> 1 == 0x7e && str[start + 1] >> 6 == 2 && str[start + 2] >> 6 == 2 && str[start + 3] >> 6 == 2 && str[start + 4] >> 6 == 2 && str[start + 5] >> 6 == 2);
}

bool is_utf8_byte5(unsigned char const* str, int start)
{
	// 5 Bytes sequesce 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	return (str[start] >> 2 == 0x3e && str[start + 1] >> 6 == 2 && str[start + 2] >> 6 == 2 && str[start + 3] >> 6 == 2 && str[start + 4] >> 6 == 2);
}

bool is_utf8_byte4(unsigned char const* str, int start)
{
	// 4 Bytes sequesce 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
	return (str[start] >> 3 == 0x1e && str[start + 1] >> 6 == 2 && str[start + 2] >> 6 == 2 && str[start + 3] >> 6 == 2);
}

bool is_utf8_byte3(unsigned char const* str, int start)
{
	// 3 Bytes sequesce 1110xxxx 10xxxxxx 10xxxxxx
	return (str[start] >> 4 == 0xe && str[start + 1] >> 6 == 2 && str[start + 2] >> 6 == 2);
}

bool is_utf8_byte2(unsigned char const* str, int start)
{
	// 2 Bytes sequence 110xxxxx 10xxxxxx
	return (str[start] >> 5 == 6 && str[start + 1] >> 6 == 2);
}

bool is_ascii(unsigned char const* str, int start)
{
	return (str[start] < 128);
}

