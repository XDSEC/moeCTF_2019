#include <stdio.h>
#include <Windows.h>

void Input(const char* flag)
{
	puts("Input your flag:");
	char buffer[100];
	gets(buffer);
	if(strcmp(buffer,flag)==0)
		puts("You are right!");
	else
		puts("Oops, you are wrong...\nPress 'R' can transform a intager into a string\n\nWhat? This file looks so strange?\nWho knows?");
	Sleep(500);
}

int main()
{
	if(IsDebuggerPresent())
		return 0;
	puts("Welcome to the MoeCTF!");
	char f[] = "moectf{upx_1s_a_K1nd_0F_sh21L}";
	Input(f);
}