#include <iostream>
#include <string>
#include <vector>
using namespace std;

char* args[] = { (char*)"encrypt.o", (char*)"-m", (char*)"vernam", (char*)"-i", (char*)"abcdefgh", (char*)"-k", (char*)"monarchy" };

string caesar(string input, int key)
{
	string result = input;
	for (int id = 0; id < input.length(); id++)
	{
		result[id] = ((input[id] - 'a' + key + 26) % 26 + 'A');
	}
	return result;
}

string playfair(string input, string key)
{
	for (int id = 0; id < 26 && id != 9; id++)
	{
		if (key.find('a' + id) == -1) key.push_back('a' + id);
	}

	string result = "";

	for (int id = 0; id < input.length(); id += 2)
	{
		int pos1 = key.find(input[id]);
		int pos2 = key.find((id + 1 == input.length()) ? 'x' : input[id + 1]);

		//repeated letter
		if (pos1 == pos2)
		{
			if (pos1 == key.find('x')) return "Error: repeated x!\n";
			pos2 = key.find('x');
			id--;
		}
		//same row
		else if (pos1 / 5 == pos2 / 5)
		{
			pos1++;
			pos2++;
			if (pos1 % 5 == 0) pos1 -= 5;
			if (pos2 % 5 == 0) pos2 -= 5;
		}
		//same column
		else if (pos1 % 5 == pos2 % 5)
		{
			pos1 += 5;
			pos2 += 5;
			if (pos1 >= 25) pos1 -= 25;
			if (pos2 >= 25) pos2 -= 25;
		}
		//none of the above
		else
		{
			int backup1 = pos1;
			int backup2 = pos2;
			pos1 = (((backup1 / 5) * 5) + (backup2 % 5));
			pos2 = (((backup2 / 5) * 5) + (backup1 % 5));
		}

		result.push_back(key[pos1] - 'a' + 'A');
		result.push_back(key[pos2] - 'a' + 'A');
	}
	return result;
}

string vernam(string input, string key)
{
	key += input;
	string result = "";
	for (int id = 0; id < input.length(); id++)
	{
		result.push_back(((input[id] + key[id]) % 26) - 'a' + 'A');
	}
	return result;
}

string railfence(string input)
{
	string odd = "", even = "";
	for (int id = 0; id < input.length(); id++)
	{
		if (id % 2 == 0) even.push_back(input[id] - 'a' + 'A');
		else odd.push_back(input[id] - 'a' + 'A');
	}
	return even + odd;
}

string row(string input, string key)
{
	string result = "";
	vector<string> list = {};
	for (int id = 0; id < key.length(); id++)
	{
		list.push_back("");
	}
	for (int id = 0; id < input.length(); id++)
	{
		list[id % key.length()].push_back(input[id % key.length()] - 'a' + 'A');
	}
	for (int id = 0; id < key.length(); id++)
	{
		result += list[key[id] - '1'];
	}
	return result;
}

int main(int argc, char* argv[])
{
	argc = 7;
	argv = args;

	string cipher_type = argv[2];
	if (cipher_type == "caesar") cout << caesar(argv[4], stoi(argv[6]));
	else if (cipher_type == "playfair") cout << playfair(argv[4], argv[6]);
	else if (cipher_type == "vernam") cout << vernam(argv[4], argv[6]);
	else if (cipher_type == "railfence") cout << railfence(argv[4]);
	else if (cipher_type == "row") cout << row(argv[4], argv[6]);
	return 0;
}