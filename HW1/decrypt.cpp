#include <iostream>
using namespace std;

void caesar(string input, int key)
{
	
}

int main(int argc, char* argv[])
{
	if (argc == 6)
	{
		if (argv[3] == "caesar")
			caesar(argv[5], atoi(argv[7]));
	}
	else
	{
		caesar("implaintext", 4);
	}
	return 0;
}