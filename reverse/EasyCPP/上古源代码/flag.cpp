#include "flag.h"
#include "base64.h"
#include <cctype>

string flag::calu()
{
	const int weiyi = base64_decode(key)[4] - '0';
	string temp = input;
	temp = base64_encode((const unsigned char*)temp.c_str(), temp.length());
	for (auto& x : temp)
		if (islower(x))
			x = (x - 'a' + weiyi) % 26 + 'a';
		else if(isupper(x))
			x = (x - 'A' + weiyi) % 26 + 'A';
	return temp;
}
