#include <iostream>
#include <cstring>
using namespace std;

void find_row_col(char matrix[5][5], char input, int& row, int& col)
{
	if (input >= 'A') input = input - 'A' + 'a';
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (matrix[i][j] == input || (input == 'i' && matrix[i][j] == 'j') || (input == 'j' && matrix[i][j] == 'i'))
			{
				row = i;
				col = j;
				return;
			}
		}
	}
}

string caesar(string input, int key)
{
	string ans = input;
	for (int index = 0; index < input.length(); index++)
	{
		ans[index] = ((input[index] - 'A' - key + 26) % 26 + 'a');
	}
	return ans;
}

string playfair(string input, string key)
{
	string ans = input;
	char matrix[5][5];
	int matrix_index = 0;
	bool character[26];
	for (int index = 0; index < 26; index++)
	{
		character[index] = false;
	}
	for (int index = 0; index < key.length(); index++)
	{
		if (!character[key[index] - 'a'])
		{
			character[key[index] - 'a'] = true;
			matrix[matrix_index / 5][matrix_index % 5] = key[index];
			matrix_index++;
		}
	}
	int ch_index = 0;
	for (; matrix_index < 25; matrix_index++)
	{
		while (character[ch_index] || ch_index == 9)
			ch_index++;
		matrix[matrix_index / 5][matrix_index % 5] = 'a' + ch_index;
		character[ch_index] = true;
	}
	for (int index = 0; index < input.length(); index += 2)
	{
		int row_a, col_a, row_b, col_b;
		find_row_col(matrix, input[index], row_a, col_a);
		find_row_col(matrix, input[index + 1], row_b, col_b);

		if (row_a == row_b)
		{
			ans[index] = matrix[row_a][(col_a - 1 + 5) % 5];
			ans[index + 1] = matrix[row_b][(col_b - 1 + 5) % 5];
		}
		else if (col_a == col_b)
		{
			ans[index] = matrix[(row_a - 1 + 5) % 5][col_a];
			ans[index + 1] = matrix[(row_b - 1 + 5) % 5][col_b];
		}
		else
		{
			ans[index] = matrix[row_a][col_b];
			ans[index + 1] = matrix[row_b][col_a];
		}
	}
	return ans;
}

string vernam(string input, string key)
{
	string ans;
	string ans_t;
	for (int index = 0; index < input.length(); index++)
	{
		if (index >= key.length())
		{
			key += ans_t;
			ans += ans_t;
			ans_t = "";
		}
		ans_t += (short)((input[index] - 'A') ^ (key[index] - 'a')) + 'a';
	}
	ans += ans_t;
	return ans;
}

string railfence(string input, int key)
{
	string ans;
	string *anss = new string[key];
	int* indexes = new int[key];
	int row_length = 2 * (key - 1);
	int row_left = input.length() % row_length;
	int col_length = input.length() / row_length;
	int input_index = 0;
	int sub_length = 0;
	for (int index = 0; index < key; index++)
	{
		if (index == 0 || index + 1 == key)
		{
			sub_length = col_length + ((index + 1 <= row_left) ? 1 : 0);
		}
		else
		{
			sub_length = 2 * col_length + ((index + 1 <= row_left && index < key) ? 1 : (index + 1 <= row_left) ? 2 : 0);
		}
		anss[index] = input.substr(input_index, sub_length);
		input_index = input_index + sub_length;
		indexes[index] = 0;
	}
	int row_index = 0;
	bool is_down = true;
	for (int index = 0; index < input.length(); index++)
	{
		ans += anss[row_index][indexes[row_index]++] - 'A' + 'a';
		if (is_down)
			row_index++;
		else
			row_index--;
		if (row_index == 0)
			is_down = true;
		if (row_index == key - 1)
			is_down = false;
	}
	ans += '\0';
	delete[] anss;
	return ans;
}

string row(string input, string key)
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
		if (!strcmp(argv[2], "caesar"))
			cout << caesar(argv[4], atoi(argv[6])) << "\n";
		else if (!strcmp(argv[2], "playfair"))
			cout << playfair(argv[4], argv[6]) << "\n";
		else if (!strcmp(argv[2], "vernam"))
			cout << vernam(argv[4], argv[6]) << "\n";
		else if (!strcmp(argv[2], "railfence"))
			cout << railfence(argv[4], atoi(argv[6])) << "\n";
		else if (!strcmp(argv[2], "row"))
			cout << row(argv[4], argv[6]) << "\n";
	}
	else
	{
		//cout << caesar("MQTPEMRXIBX", 4);
		//cout << playfair("BIHCFGFY", "monarchy");
		//cout << vernam("QIJF", "xmcl");
		//cout << vernam("MBDBHBDB", "m");
		//cout << railfence("MEMATRHTGPRYETEFETEOAAT", 2);
		//cout << railfence("WECRUOERDSOEERNTNEAIVDAC", 3);
		//cout << railfence("WVOEOETNACRACRSENEEIDUDR", 6);
		cout << row("TTNAAPTMTSUOAODWCOIXKNLYPETZ", "4312567");
		//cout << row("ILHIOJSAESREHEPHWOTHITERISRHKCSTOOPTTCFM", "4312567");
	}
	return 0;
}