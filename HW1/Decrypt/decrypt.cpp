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
			ans[index] = matrix[(col_a - 1 + 5) % 5][row_a];
			ans[index + 1] = matrix[(col_b - 1 + 5) % 5][row_b];
		}
		else if (col_a == col_b)
		{
			ans[index] = matrix[col_a][(row_a + 1 + 5) % 5];
			ans[index + 1] = matrix[col_b][(row_b + 1 + 5) % 5];
		}
		else
		{
			ans[index] = matrix[col_b][row_a];
			ans[index + 1] = matrix[col_a][row_b];
		}
	}
	return ans;
}

string vernam(string input, string key)
{
	string ans = input;
	for (int index = 0; index < input.length(); index++)
	{
		ans[index] = (short)((input[index] - 'A') ^ (key[index] - 'a')) + 'a';
	}
	return ans;
}

string railfence(string input, int key)
{
	string ans = input;

	return ans;
}

string row(string input, int key)
{
	string ans = input;

	return ans;
}

int main(int argc, char* argv[])
{
	if (argc == 7)
	{
		if (argv[3] == "caesar")
			caesar(argv[5], atoi(argv[7]));
		else if (argv[3] == "playfair")
			playfair(argv[5], argv[7]);
		else if (argv[3] == "vernam")
			vernam(argv[5], argv[7]);
		else if (argv[3] == "railfence")
			railfence(argv[5], atoi(argv[7]));
		else if (argv[3] == "row")
			row(argv[5], atoi(argv[7]));
	}
	else
	{
		//cout << caesar("MQTPEMRXIBX", 4);
		//cout << playfair("implaintext", "monarchy");
		cout << vernam("QIJF", "xmcl");
	}
	return 0;
}