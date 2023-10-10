#include "function.h"

string Dec_To_Bin(unsigned long long dec, const int byte)
{
	string temp;
	if (dec == 0)
	{
		temp.push_back('0');
	}
	else
	{
		while (dec > 0)
		{
			temp.push_back((dec % 2) + 48);
			dec = dec / 2;
		}
	}
	Change_size_of_bit_sequence(temp, (int)byte * 8);
	string result;
	int n = (int)temp.size();
	for (int i = n - 1; i >= 0; i--)
	{
		result.push_back(temp[i]);
	}
	return result;
}


void Change_size_of_bit_sequence(string &bitseq, const int size)
{
	int temp = (int)bitseq.size() - size;
	if (temp < 0)
	{
		temp = -temp;
		while (temp > 0)
		{
			bitseq.push_back('0');
			temp--;
		}
	}
	else if (temp > 0)
	{
		while (temp > 0)
		{
			bitseq.pop_back();
		}
	}
}


string ToTwoComplement(string result)
{
	int n = (int)result.size();
	for (int i = 0; i < n; i++)
	{
		if (result[i] == '0')
		{
			result[i] = '1';
		}
		else
		{
			result[i] = '0';
		}
	}
	for (int i = n - 1; i >= 0; i--)
	{
		if (result[i] == '0')
		{
			result[i] = '1';
			break;
		}
		else
		{
			result[i] = '0';
		}
	}
	return result;
}


string Dec_To_Signed(double dec, const int byte)
{
	int negative = 0;
	if (dec < 0)
	{
		dec = -dec;
		negative = 1;
	}
	string result;
	result = Dec_To_Bin((unsigned long long)dec, byte);
	if (negative == 1)
	{
		result = ToTwoComplement(result);
	}
	return result;
}


string Dec_To_Float32(double dec)
{
	int IntPart, expo, ToWorkOn;
	string sign, temp, Expo, Mantissa, result;
	//SIGN BIT
	if (dec < 0)
	{
		sign = "1";
		dec = dec * (-1);
	}
	else
		sign = "0";
	//Expo and mantissa
	IntPart = (int)dec;
	bool flag = false;
	if (IntPart == 1)
		temp = "1";
	else if (IntPart == 0)
		temp = "0";
	else
	{
		while (flag == false)
		{
			if (IntPart % 2 == 1)
				temp = temp + "1";
			else
				temp = temp + "0";
			IntPart = IntPart / 2;
			if (IntPart == 1)
			{
				temp = temp + "1";
				flag = true;
			}
		}
		reverse(temp.begin(), temp.end());
	}

	//EXPO
	expo = 126 + temp.length();
	flag = false;
	while (flag == false)
	{
		if (expo % 2 == 1)
			Expo = Expo + "1";
		else
			Expo = Expo + "0";
		expo = expo / 2;
		if (expo == 1)
		{
			Expo = Expo + "1";
			flag = true;
		}
	}
	reverse(Expo.begin(), Expo.end());

	//MANTISSA
	Mantissa = Mantissa + temp;
	Mantissa.erase(0, 1);
	int left = 23 - Mantissa.length();
	temp.erase();
	ToWorkOn = (dec - int(dec)) * pow(2, 23);
	for (int i = 0; i < left; i++)
	{
		if (ToWorkOn - pow(2, 22 - i) >= 0)
		{
			temp = temp + "1";
			ToWorkOn -= pow(2, 22 - i);
		}
		else if (ToWorkOn - pow(2, 22 - i) == 0)
		{
			temp = temp + "1";
			i++;
			while (i != left)
			{
				temp = temp + "0";
				i++;
			}
		}
		else
			temp = temp + "0";
	}
	Mantissa = Mantissa + temp;
	result = result + sign + Expo + Mantissa;
	return result;
}


string Dec_To_Float64(double dec)
{
	int IntPart, expo;
	float ToWorkOn;
	string sign, temp, Expo, Mantissa, result;
	//SIGN BIT
	if (dec < 0)
	{
		sign = "1";
		dec = dec * (-1);
	}
	else
		sign = "0";
	//Expo and mantissa
	IntPart = dec;
	bool flag = false;
	if (IntPart == 1)
		temp = "1";
	else if (IntPart == 0)
		temp = "0";
	else
	{
		while (flag == false)
		{
			if (IntPart % 2 == 1)
				temp = temp + "1";
			else
				temp = temp + "0";
			IntPart = IntPart / 2;
			if (IntPart == 1)
			{
				temp = temp + "1";
				flag = true;
			}
		}
		reverse(temp.begin(), temp.end());
	}

	//EXPO
	expo = 1022 + temp.length();
	flag = false;
	while (flag == false)
	{
		if (expo % 2 == 1)
			Expo = Expo + "1";
		else
			Expo = Expo + "0";
		expo = expo / 2;
		if (expo == 1)
		{
			Expo = Expo + "1";
			flag = true;
		}
	}
	reverse(Expo.begin(), Expo.end());

	//MANTISSA
	Mantissa = Mantissa + temp;
	Mantissa.erase(0, 1);
	int left = 52 - Mantissa.length();
	temp.erase();
	ToWorkOn = (dec - int(dec)) * pow(2, 53);
	for (int i = 0; i < left; i++)
	{
		if (ToWorkOn - pow(2, 52 - i) > 0)
		{
			temp = temp + "1";
			ToWorkOn -= pow(2, 52 - i);
		}
		else if (ToWorkOn - pow(2, 52 - i) == 0)
		{
			temp = temp + "1";
			i++;
			while (i != left)
			{
				temp = temp + "0";
				i++;
			}
		}
		else
			temp = temp + "0";
	}
	Mantissa = Mantissa + temp;
	result = result + sign + Expo + Mantissa;
	return result;
}


string Dec_To_Bin_K(double dec, const int K, const int byte)
{
	dec += K;
	string result;
	result = Dec_To_Bin((unsigned long long)dec, byte);
	return result;
}


void BinToDecExcessK(string bin, double &result, const int K)
{
	int size = (int)bin.length();
	double temp = 0;
	for (int i = 0; i < size; i++)
	{
		temp = (bin[i] - 48) * pow(2, size - 1 - i);
		result += temp;
	}
	result = result - K;
}


void BinToDecTwoComplement(string bin, double &result)
{
	int size = (int)bin.length();
	double temp = 0;
	for (int i = 0; i < size; i++)
	{
		temp = (bin[i] - 48) * pow(2, size - 1 - i);
		if (bin[i] == '1' && i == 0)
		{
			temp = -temp;
		}
		result += temp;
	}
}


void Float32_To_Dec(string input, float &result)
{
	float mantissa;
	int sign, expo, ToWorkOn;
	//Sign
	ToWorkOn = input[0] - '0';
	input.erase(0, 1);
	if (ToWorkOn == 0)
		sign = 1;
	else
		sign = -1;
	//Expo
	expo = 0;
	for (int i = 7; i >= 0; i--)
	{
		ToWorkOn = input[0] - '0';
		input.erase(0, 1);
		if (ToWorkOn == 1)
			expo += pow(2, i);
	}
	//Mantissa
	mantissa = 0;
	for (int i = 1; i <= 23; i++)
	{
		ToWorkOn = input[0] - '0';
		input.erase(0, 1);
		if (ToWorkOn == 1)
			mantissa += pow(2, -i);
	}
	//Result
	result = sign * (1 + mantissa) * pow(2, expo - 127);
}


void Float64_To_Dec(string input, double &result)
{
	double mantissa;
	int sign, expo, ToWorkOn;
	//Sign
	ToWorkOn = input[0] - '0';
	input.erase(0, 1);
	if (ToWorkOn == 0)
		sign = 1;
	else
		sign = -1;
	//Expo
	expo = 0;
	for (int i = 10; i >= 0; i--)
	{
		ToWorkOn = input[0] - '0';
		input.erase(0, 1);
		if (ToWorkOn == 1)
			expo += pow(2, i);
	}
	//Mantissa
	mantissa = 0;
	for (int i = 1; i <= 53; i++)
	{
		ToWorkOn = input[0] - '0';
		input.erase(0, 1);
		if (ToWorkOn == 1)
			mantissa += pow(2, -i);
	}
	//Result
	result = sign * (1 + mantissa) * pow(2, expo - 1023);
}


string ASCII_To_Bin(std::string str)
{
	std::string result, bit;
	int codepoint;
	int len = str.length();
	for (int i = 0; i < len; ++i)
	{
		codepoint = int(str.at(i));
		bit = Dec_To_Bin(codepoint, 1);
		result.append(bit);
	}
	return result;
}


string UTF16_To_Bin(std::wstring wstr)
{
	std::string result, bit;
	int codepoint;
	int len = wstr.length();
	for (int i = 0; i < len; ++i)
	{
		codepoint = int(wstr.at(i));
		bit = Dec_To_Bin(codepoint, 2);
		result.append(bit);
	}
	return result;
}


string Bin_To_Str_ASCII(std::string bin)
{
	std::string result, bit;
	double codepoint;
	int len = bin.length() / 8;
	for (int i = 0; i < len; ++i)
	{
		codepoint = 0;
		bit = bin.substr(i * 8, 8);
		BinToDecExcessK(bit, codepoint, 0);
		result.push_back(char(int(codepoint)));
	}
	return result;
}


string Bin_To_Str_UTF16(std::string bin)
{
	std::string result, bit;
	double codepoint;
	int len = bin.length() / 16;
	for (int i = 0; i < len; ++i)
	{
		codepoint = 0;
		bit = bin.substr(i * 16, 16);
		BinToDecExcessK(bit, codepoint, 0);
		result.push_back(char(int(codepoint)));
	}
	return result;
}


string BE_To_LE(std::string bin, int byte_num)
{
	std::string LE, bit;
	int len = bin.length() / (byte_num * 8);
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < byte_num; ++j)
		{
			bit = bin.substr((i * byte_num + byte_num - 1 - j) * 8, 8);
			LE.append(bit);
		}
	}
	return LE;
}


string LE_To_BE(std::string bin, int byte_num)
{
	std::string BE, bit;
	int len = bin.length() / (byte_num * 8);
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < byte_num; ++j)
		{
			bit = bin.substr((i * byte_num + byte_num - 1 - j) * 8, 8);
			BE.append(bit);
		}
	}
	return BE;
}


void printBitSequence(string result)
{
	int n = (int)result.size();
	for (int i = 0; i < n; i++)
	{
		cout << result[i];
		if ((i + 1) % 8 == 0 && i != (n - 1))
		{
			cout << " ";
		}
	}
	cout << endl;
}


void Write_To_BinFile(const string input)
{
	ofstream fsave;
	char *temp = new char[input.size() + 1];
	int n = (int)input.size();
	for (int i = 0; i < n; i++)
	{
		temp[i] = input[i];
	}
	fsave.open("test.bin", ios::binary | ios::app);
	if (!fsave.is_open())
	{
		cout << "Cannot create file." << endl;
	}
	else
	{
		fsave.seekp(0, ios::end);
		fsave.write(temp, n);
		while (fsave.is_open())
		{
			fsave.close();
		}
		if (fsave.is_open())
		{
			cout << "Close failed." << endl;
		}
	}
	delete[] temp;
	cout << "Save succeeded" << endl;
	system("pause");
	system("CLS");
}


void Read_From_BinFile(string &output, const long offset, int byte)
{
	ifstream fread;
	fread.open("test.bin", ios::binary);
	if (!fread.is_open())
	{
		cout << "Cannot open file." << endl;
	}
	else
	{
		fread.seekg(0, ios::beg);
		fread.seekg(0, fread.end);
		long size = (long)fread.tellg();
		fread.seekg(0, ios::beg);
		if (offset <= size - 1)
		{
			long byte_can_read_from_file = size - offset;
			if (byte > byte_can_read_from_file)
			{
				byte = byte_can_read_from_file;
			}
			unsigned char *temp;
			temp = new unsigned char[byte];
			fread.seekg(offset, ios::beg);
			fread.read((char *)temp, byte);
			for (int i = 0; i < byte; i++)
			{
				output.push_back((int)temp[i]);
			}
			delete[] temp;
		}
		else
		{
			cout << "Cannot get the data from the offset you want." << endl;
			cout << "The reason is only offset from " << 0 << " to " << (size / 8) - 1 << " is allowed right now." << endl;
			cout << "Cancel reading file." << endl;
		}
		while (fread.is_open())
		{
			fread.close();
		}
		if (fread.is_open())
		{
			cout << "Close failed." << endl;
		}
		cout << "Load succeeded." << endl;
	}
	system("pause");
	system("CLS");
}
