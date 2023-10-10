#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

//Functions convert dec to bin:
string Dec_To_Bin(unsigned long long dec, const int byte);     //convert dec to binary.
void Change_size_of_bit_sequence(string &bitseq, const int size); //resize the sequence.
//Two complement:
string ToTwoComplement(string result); //convert sequence to 2's complement.
string Dec_To_Signed(double dec, const int byte);

//Floating point:
string Dec_To_Float32(double dec); //convert decimal to binary as single precision floating point.
string Dec_To_Float64(double dec); //convert decimal to binary as double precision floating point.

//Excess K:
string Dec_To_Bin_K(double dec, const int K, const int byte);

//Functions convert bin to dec:
void BinToDecExcessK(string bin, double &result, const int K); //convert unsigned bits sequence to dec
void BinToDecTwoComplement(string bin, double &result);        //convert signed bits sequence to dec
void Float32_To_Dec(string input, float &result);              //convert single precision floating point to decimal
void Float64_To_Dec(string input, double &result);             //convert double precision floating point to decimal

std::string ASCII_To_Bin(std::string str);
std::string UTF16_To_Bin(std::wstring wstr);

std::string Bin_To_Str_ASCII(std::string bin);
std::string Bin_To_Str_UTF16(std::string bin);

std::string BE_To_LE(std::string bin, int byte_num);
std::string LE_To_BE(std::string bin, int byte_num);

//Other functions:
void printBitSequence(string result);                                //print the bit sequence.
void Write_To_BinFile(const string input);                           //save to bin file
void Read_From_BinFile(string &output, const long offset, int byte); //read from bin file

#endif
