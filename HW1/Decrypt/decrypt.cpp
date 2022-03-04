#include <iostream>
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
	/*for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}*/
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
	string ans = input;
	if (key.length() < input.length())
		key += input;
	for (int index = 0; index < input.length(); index++)
	{
		ans[index] = (short)((input[index] - 'A') ^ (key[index] - 'a')) + 'a';
	}
	return ans;
}

string railfence(string input)
{
	string ans;
	int m = input.length() / 2;
	int p = 0, q = m + 1;
	for (int index = 0; index < input.length(); index++)
	{
		if (index % 2 == 0)
			ans += input[p++] - 'A' + 'a';
		else
			ans += input[q++] - 'A' + 'a';
	}
	ans += '\0';
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
	char** anss = new char*[rows];
	for (int r = 0; r < rows; r++)
		anss[r] = new char[cols + 1];
	int input_index = 0;
	int c = 1;
	int c_index = 1;
	for (; input_index < input.length();)
	{
		for (int key_index = 0; key_index < key.length(); key_index++)
		{
			if (c == key[key_index] - '0')
			{
				c_index = key_index;
				c++;
				break;
			}
		}
		for (int r = 0; r < rows; r++)
		{
			anss[r][c_index] = input[input_index++] - 'A' + 'a';
		}
	}
	for (int r = 0; r < rows; r++)
	{
		anss[r][cols] = '\0';
		ans += anss[r];
	}
	delete[] anss;
	return ans;
}

int main(int argc, char* argv[])
{
	if (argc >= 5)
	{
		if (argv[3] == "caesar")
			caesar(argv[5], atoi(argv[7]));
		else if (argv[3] == "playfair")
			playfair(argv[5], argv[7]);
		else if (argv[3] == "vernam")
			vernam(argv[5], argv[7]);
		else if (argv[3] == "railfence")
			railfence(argv[5]);
		else if (argv[3] == "row")
			row(argv[5], argv[7]);
	}
	else
	{
		//cout << caesar("MQTPEMRXIBX", 4);
		cout << playfair("BIHCFGFY", "monarchy");
		//cout << vernam("QIJF", "xmcl");
		//cout << railfence("MEMATRHTGPRYETEFETEOAAT");
		//cout << row("TTNAAPTMTSUOAODWCOIXKNLYPETZ", "4312567");
	}
	return 0;
}