#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int ip[64] = { 58, 50, 42, 34, 26, 18, 10,  2,
			   60, 52, 44, 36, 28, 20, 12,  4,
			   62, 54, 46, 38, 30, 22, 14,  6,
			   64, 56, 48, 40, 32, 24, 16,  8,
			   57, 49, 41, 33, 25, 17,  9,  1,
			   59, 51, 43, 35, 27, 19, 11,  3,
			   61, 33, 45, 37, 29, 21, 13,  5,
			   63, 55, 47, 39, 31, 23, 15,  7 };
int ip_reverse[64] = { 40,  8, 48, 16, 56, 24, 64, 32,
					   39,  7, 47, 15, 55, 23, 63, 31,
					   38,  6, 46, 14, 54, 22, 62, 30,
					   37,  5, 45, 13, 53, 21, 61, 29,
					   36,  4, 44, 12, 52, 20, 60, 28,
					   35,  3, 43, 11, 51, 19, 59, 27,
					   34,  2, 42, 10, 50, 18, 58, 26,
					   33,  1, 41,  9, 49, 17, 57, 25 };

int expansion[48] = { 32,  1,  2,  3,  4,  5,  4,  5,
					   6,  7,  8,  9,  8,  9, 10, 11,
					  12, 13, 12, 13, 14, 15, 16, 17,
					  16, 17, 18, 19, 20, 21, 20, 21,
					  22, 23, 24, 25, 24, 25, 26, 27,
					  28, 29, 28, 29, 30, 31, 32,  1 };

int p[32] = { 16,  7, 20, 21, 29, 12, 28, 17,
			   1, 15, 23, 26,  5, 18, 31, 10,
			   2,  8, 24, 14, 32, 27,  3,  9,
			  19, 13, 30,  6, 22, 11,  4, 25 };

// S-box Table
int s[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
					  0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
					  4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
					  15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
					{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
					  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
					  0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
					  13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },
					{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
					  13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
					  13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
					  1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
					{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
					  13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
					  10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
					  3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
					{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
					  14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
					  4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
					  11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
					{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
					  10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
					  9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
					  4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
					{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
					  13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
					  1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
					  6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
					{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
					  1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
					  7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
					  2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };

int pc_1[56] = { 57, 49, 41, 33, 25, 17,  9,
				  1, 58, 50, 42, 34, 26, 18,
				 10,  2, 59, 51, 43, 35, 27,
				 19, 11,  3, 60, 52, 44, 36,
				 63, 55, 47, 39, 31, 23, 15,
				  7, 62, 54, 46, 38, 30, 22,
				 14,  6, 61, 53, 45, 37, 29,
				 21, 13,  5, 28, 20, 12,  4 };

int pc_2[48] = { 14, 17, 11, 24,  1,  5,
				  3, 28, 15,  6, 21, 10,
				 23, 19, 12,  4, 26,  8,
				 16,  7, 27, 20, 13,  2,
				 41, 52, 31, 37, 47, 55,
				 30, 40, 51, 45, 33, 48,
				 44, 49, 39, 56, 34, 53,
				 46, 42, 50, 36, 29, 32 };

string hex2bin(string s)
{
	string ans(64 - s.length() * 4, '0');
	for (int i = 0; i < s.length(); i++)
	{
		switch (s[i])
		{
			case '0':
				ans += "0000";
				break;
			case '1':
				ans += "0001";
				break;
			case '2':
				ans += "0010";
				break;
			case '3':
				ans += "0011";
				break;
			case '4':
				ans += "0100";
				break;
			case '5':
				ans += "0101";
				break;
			case '6':
				ans += "0110";
				break;
			case '7':
				ans += "0111";
				break;
			case '8':
				ans += "1000";
				break;
			case '9':
				ans += "1001";
				break;
			case 'A':
				ans += "1010";
				break;
			case 'B':
				ans += "1011";
				break;
			case 'C':
				ans += "1100";
				break;
			case 'D':
				ans += "1101";
				break;
			case 'E':
				ans += "1110";
				break;
			case 'F':
				ans += "1111";
				break;
			default:
				ans += "1111";
				break;
		}
	}
	return ans;
}

string permute(string input, int table[], int length)
{
	string ans;
	for (int i = 0; i < length; i++)
		ans += input[table[i] - 1];
	return ans;
}

string shiftRight(string key, int shift)
{
	string ans;
	for (int i = 28 - shift; i < 28; i++)
		ans += key[i];
	for (int i = 0; i < 28 - shift; i++)
		ans += key[i];
	return ans;
}

template<typename T>
void SWAP(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}

string XOR(string input, string key)
{
	string ans;
	for (int index = 0; index < input.length(); index++)
	{
		if (input[index] != key[index])
			ans += "1";
		else
			ans += "0";
	}
	return ans;
}

string bin2hex(string s)
{
	string ans = "0x";
	bool meet_zero = false;
	for (int index = 0; index < s.length(); index += 4)
	{
		string sub = s.substr(index, 4);
		if (sub == "0000")
		{
			if (meet_zero)
				ans += "0";
			else
				meet_zero = true;
		}
		else if (sub == "0001")
			ans += "1";
		else if (sub == "0010")
			ans += "2";
		else if (sub == "0011")
			ans += "3";
		else if (sub == "0100")
			ans += "4";
		else if (sub == "0101")
			ans += "5";
		else if (sub == "0110")
			ans += "6";
		else if (sub == "0111")
			ans += "7";
		else if (sub == "1000")
			ans += "8";
		else if (sub == "1001")
			ans += "9";
		else if (sub == "1010")
			ans += "A";
		else if (sub == "1011")
			ans += "B";
		else if (sub == "1100")
			ans += "C";
		else if (sub == "1101")
			ans += "D";
		else if (sub == "1110")
			ans += "E";
		else if (sub == "1111")
			ans += "F";
	}
	return ans;
}

string deDES(string input, string key)
{
	key = hex2bin(key);
	key = permute(key, pc_1, 56);
	string left = key.substr(0, 28);
	string right = key.substr(28, 28);
	string round_key[16];
	round_key[0] = permute(left + right, pc_2, 48);
	for (int round = 1; round < 16; round++)
	{
		if (round + 1 == 2 || round + 1 == 9 || round + 1 == 16)
		{
			left = shiftRight(left, 1);
			right = shiftRight(right, 1);
		}
		else
		{
			left = shiftRight(left, 2);
			right = shiftRight(right, 2);
		}
		round_key[round] = permute(left + right, pc_2, 48);
	}

	input = hex2bin(input);
	input = permute(input, ip, 64);
	left = input.substr(0, 32);
	right = input.substr(32, 32);
	for (int round = 0; round < 16; round++)
	{
		string right_e = permute(right, expansion, 48);
		string right_xor_k = XOR(right_e, round_key[round]);
		string right_s;
		for (int s_index = 0; s_index < 8; s_index++)
		{
			int row = 2 * int(right_xor_k[s_index * 6] - '0') + int(right_xor_k[s_index * 6 + 5] - '0');
			int col = 8 * int(right_xor_k[s_index * 6 + 1] - '0') + 4 * int(right_xor_k[s_index * 6 + 2] - '0') + 2 * int(right_xor_k[s_index * 6 + 3] - '0') + int(right_xor_k[s_index * 6 + 4] - '0');
			int val = s[s_index][row][col];
			right_s += char(val / 8 + '0');
			val = val % 8;
			right_s += char(val / 4 + '0');
			val = val % 4;
			right_s += char(val / 2 + '0');
			val = val % 2;
			right_s += char(val + '0');
		}
		string f = permute(right_s, p, 32);
		left = XOR(left, f);
		SWAP(left, right);
	}
	SWAP(left, right);
	return bin2hex(permute(left + right, ip_reverse, 64));
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
		input.erase(0, 2);
		a = argv[4];
		for (int i = 0; i < a.length(); i++)
		{
			if ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= '0' && a[i] <= '9'))
				key += a[i];
		}
		key.erase(0, 2);
		cout << deDES(input, key) << "\n";
	}
	else
	{
		cout << deDES("456", "123") << "\n";
		cout << deDES("CCA1434BF1A523AF", "123") << "\n";
		cout << deDES("C0B7A8D05F3A829C", "AABB09182736CCDD") << "\n";
	}
	return 0;
}