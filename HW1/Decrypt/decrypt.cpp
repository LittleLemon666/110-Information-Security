#include <iostream>
using namespace std;

string caesar(string input, int key)
{
	string ans = input;
	for (int index = 0; index < input.length(); index++)
	{
		ans[index] = ((input[index] - 'a' - key + 26) % 26 + 'A');
	}
	return ans;
}

int main(int argc, char* argv[])
{
	if (argc == 7)
	{
		if (argv[3] == "caesar")
			caesar(argv[5], atoi(argv[7]));
	}
	else
	{
		cout << caesar("implaintext", 4);
	}
	return 0;
}