#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

string deDES(string input, string key)
{
	string ans;
	int cols = 1;
	for (int index = 0; index < key.length(); index++)
	{
		if (key[index] - '0' > cols)
			cols = key[index] - '0';
	}
	int rows = input.length() / cols;
	if (input.length() % cols > 0)
		rows++;
	string* anss = new string[rows];
	for (int r = 0; r < rows; r++)
		anss[r] = "";
	for (int key_index = 0; key_index < key.length(); key_index++)
	{
		int row = (key[key_index] - '0' - 1) * rows;
		int input_index = row;
		for (int row_index = 0; row_index < rows && input_index < input.length(); row_index++, input_index++)
		{
			anss[row_index] += input[input_index] - 'A' + 'a';
		}
	}
	for (int r = 0; r < rows; r++)
	{
		ans += anss[r];
		anss[r] += '\0';
	}
	ans += '\0';
	delete[] anss;
	return ans;
}

int main(int argc, char* argv[])
{
	if (argc >= 5)
	{
		string a = argv[2];
		string input, key;
		for (int i = 0; i < a.length(); i++)
		{
			if ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= '0' && a[i] <= '9'))
				input += a[i];
		}
		a = argv[4];
		for (int i = 0; i < a.length(); i++)
		{
			if ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= '0' && a[i] <= '9'))
				key += a[i];
		}
		cout << deDES(input, key) << "\n";
	}
	else
	{
		cout << deDES("0x456", "0x123");
	}
	return 0;
}