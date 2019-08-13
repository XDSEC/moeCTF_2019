#pragma once
#include <string>
#include <iostream>

using namespace std;

class flag
{
private:
	string key = "Y3BwMTNlYXN5";
	string enflag = "eZ9oB3Uph0QTXI9FBYQIQmUiT2IoX0EbAcIWA3PzA2YkBZIkf3o9";
	string input;
	string calu();
public:
	explicit flag(string& _input) :input(_input) { ; }
	bool check() {
		return enflag == calu();
	}
};