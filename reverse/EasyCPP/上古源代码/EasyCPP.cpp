#include "base64.h"
#include "flag.h"
#include <iostream>
#include <string>

using namespace std;
int main()
{
	cout << "Welcome to moectf!\nInput your flag:" << endl;
	string _input;
	getline(cin, _input);
	flag f(_input);
	if (f.check())
		cout << "You are right!\nCongratulations!" << endl;
	else
		cout << "Sorry, you are wrong.\nDon't lose heart, you can do it." << endl;
}