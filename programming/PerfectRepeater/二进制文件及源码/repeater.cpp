#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <atomic>
#include <unistd.h>

using namespace std;

string table = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/=)(*&^%$#@!~`";
bool signal = false;

void DelayExit()
{
	sleep(10);
	if (!signal)
	{
		cout << "You've run out of time.\nSorry, you are not a good repeater...\n";
		exit(0);
	}
}

string RandStr()
{
	random_device x;
	uniform_int_distribution<int> distribution(0, table.length() - 1);
	uniform_int_distribution<int> distribution2(20, 30);
	string rands;
	int times = distribution2(x);
	for (int i = 0; i < times; ++i)
		rands += table[distribution(x)];
	return rands;
}

int main()
{
	setbuf(stdin, nullptr);
	setbuf(stdout, nullptr);
	string flag = "moectf{W0_Bu_zH1_Da0_Y@o_cHU_sHen_me_f1@G_lE}\n";
	thread exitfunc(DelayExit);
	cout << "Welcome to moectf.\nA good repeater needs to repeat in time!\nAre you a good repeater?\nHave a try!\n";
	exitfunc.detach();
	for (int i = 1; i <= 100; ++i)
	{
		string temp = RandStr();
		cout << temp << '\n';
		string input;
		getline(cin, input);
		if (input != temp)
		{
			cout << "Sorry, you are wrong\nGood repeaters make no mistakes\n";
			exit(0);
		}
	}
	signal = true;
	cout << "Wow, you are a good repeater!\nHere is your flag:\n" << flag;
	exit(0);
}
