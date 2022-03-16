#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

//char* args[] = { (char*)"encrypt.o", (char*)"-m", (char*)"vernam", (char*)"-i", (char*)"abcdefgh", (char*)"-k", (char*)"m" };

string caesar(string input, int key)
{
	string result = input;
	for (int id = 0; id < input.length(); id++)
	{
		result[id] = ((input[id] - 'a' + key + 26) % 26 + 'A');
	}
	return result + '\0';
}

string playfair(string input, string key)
{
	for (int id = 0; id < 26; id++)
	{
		if (id != 9 && key.find('a' + id) == -1) key += 'a' + id;
	}
	string result = "";
	for (int id = 0; id < input.length(); id += 2)
	{
		int pos1 = key.find(input[id]);
		int pos2 = key.find((id + 1 == (int)input.length()) ? 'x' : input[id + 1]);

		//repeated letter
		if (pos1 == pos2)
		{
			if (pos1 == key.find('x')) return "Error: repeated x!\n";
			pos2 = key.find('x');
			id--;
		}

		//same row
		if (pos1 / 5 == pos2 / 5)
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

		result += key[pos1] - 'a' + 'A';
		result += key[pos2] - 'a' + 'A';
	}
	return result + '\0';
}

string vernam(string input, string key)
{
	key += input;
	string result = "";
	for (int id = 0; id < input.length(); id++)
	{
		int num1 = input[id] - 'a', num2 = key[id] - 'a';
		result += 'A' + (short)(num1 ^ num2);
	}
	return result + '\0';
}

string railfence(string input, int key)
{
	bool down = true;
	int index = 0;
	vector<string> strs = {};
	for (int id = 0; id < key; id++)
	{
		strs.push_back("");
	}
	int counter = 0;
	while (counter < (int)input.size())
	{
		strs[index] += input[counter] - 'a' + 'A';
		if (down) index++;
		else index--;
		if (index == (int)strs.size() - 1) down = false;
		if (index == 0) down = true;
		counter++;
	}
	string result = "";
	for (int id = 0; id < key; id++)
	{
		result += strs[id];
	}
	return result + '\0';
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
		list[id % key.length()] += input[id] - 'a' + 'A';
	}
	for (int id = 0; id < key.length(); id++)
	{
		result += list[key.find('1' + id)];
	}
	return result + '\0';
}

int main(int argc, char* argv[])
{
	//argc = 7;
	//argv = args;
	string answer = "";
	string cipher_type = argv[2];
	if (cipher_type == "caesar") answer = caesar(argv[4], atoi(argv[6]));
	else if (cipher_type == "playfair") answer = playfair(argv[4], argv[6]);
	else if (cipher_type == "vernam") answer = vernam(argv[4], argv[6]);
	else if (cipher_type == "railfence") answer = railfence(argv[4], atoi(argv[6]));
	else if (cipher_type == "row") answer = row(argv[4], argv[6]);
	cout << answer << "\n";
	return 0;
}