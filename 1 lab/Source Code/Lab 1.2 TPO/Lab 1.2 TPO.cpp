/*
�������� ������ ��-31
������������ ������ 1. ����������� ���� ������������.
�������� ���������� ���������� �� ����� ����� ����������������, ������� 
���������� ��� ������������ �� 3 ��������.

������:
triangle.exe a b c
��� a, b, c - ����� ������ ������������
��������� ������ ���������� ��� ������������: �������, ��������������, 
��������������, �� �����������.

���� ������� ������ �������� �����-�� ������, ��������� ������ ������ 
������������ �������� ��������� �� ������.

��������� ������������:
1. ���� ��������� � ����������� �������
2. bat-���� � ��������� �������
3. �������� ���
*/

#include "stdafx.h"
#include "iostream"
#include <locale.h>  
#include <vector>
#include <string>

using namespace std;

enum Triangle{
	EQUILATERAL,	 
	ISOSCELES,		 
	COMMON,			
	NONE			
};
enum ProgrammStatus{
	SUCCESS,
	ERROR
};

void ReadParamsFromCL(vector<string>& paramsCL, vector<double>& sides);
bool IsComandLineParametresNumbers(vector<string>& paramsCL);
bool IsSideValuesNotNegative(const vector<double>& sides); 
Triangle GetTriangleType(vector<double> & sides);
void PrintResult(vector<double> & sides);
void ReplaceDotWithComma(const char * str, string& res);


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUS");

	vector<double> sideValues(3, 0.0);

	if (argc != 4)
	{
		cout << "������� ����� ������ � �������� ����������." << endl;
		cout << "������ �����: triangle.exe a b c" << endl;
		return ERROR;
	}
	else
	{
		vector<string> paramsCL;
		for (int i = 1; i < argc; i++)
			paramsCL.push_back(string(argv[i]));

		if (!IsComandLineParametresNumbers(paramsCL))
		{
			cout << "���� ��� ��������� ���������� ��������� ������ ";
			cout << endl << "�� �������� �������. ��������� ����.";
			return ERROR;
		}
		
		ReadParamsFromCL(paramsCL, sideValues);

		if (!IsSideValuesNotNegative(sideValues))
		{
			cout << "���� ��� ��������� ���������� ��������� ������ ";
			cout << endl << "������������� �����. ��������� ����.";
			return ERROR;
		}

		PrintResult(sideValues);
	}
	return SUCCESS;
}


void PrintResult(vector<double> & sides)
{
	Triangle type = GetTriangleType(sides);
	if (type == Triangle::EQUILATERAL)
	{
		cout << "����������� �������� ��������������" << endl;
	}
	if (type == Triangle::ISOSCELES)
	{
		cout << "����������� �������� ��������������" << endl;
	}
	if (type == Triangle::COMMON)
	{
		cout << "����������� �������� �������" << endl;
	}
	if (type == Triangle::NONE)
	{
		cout << "������ ������������� �� ��������" << endl;
	}
}
Triangle GetTriangleType(vector<double> & sides)
{

	if (((sides[0] + sides[1]) <= sides[2]) || 
		((sides[1] + sides[2]) <= sides[0]) ||
		((sides[0] + sides[2]) <= sides[1]))
		return Triangle::NONE;

	else if ((sides[1] == sides[2]) &&
			 (sides[2] == sides[0]) &&
			 (sides[0] == sides[1]))
		return Triangle::EQUILATERAL;

	else if (sides[1] == sides[0] || 
			 sides[2] == sides[1] || 
			 sides[0] == sides[2])
		return Triangle::ISOSCELES;

	return Triangle::COMMON;
}
void ReplaceDotWithComma(const char * str, string& res)
{
	res = str;
	size_t found = res.find_first_of(".");
	if (found != string::npos)
	{
		res.replace(found, 1, ",");
	}
}
void ReadParamsFromCL(vector<string>& paramsCL, vector<double>& sides)
{
	double temp = 0.0;
	for (int i = 0; i <= 2; i++)
	{
		string s; 
		ReplaceDotWithComma(paramsCL[i].c_str(), s);
		temp = stod(s);
		sides[i] = temp;
	}
}
bool IsSideValuesNotNegative(const vector<double>& sides)
{
	for (size_t i = 0; i < sides.size(); i++)
	{
		if (sides[i] < 0.0)
			return false;
	}
	return true;
}
bool IsComandLineParametresNumbers(vector<string>& paramsCL)
{
	try
	{
		for (int i = 0; i <= 2; i++)
		{
			stod(paramsCL[i], NULL);
		}		
	}
	catch (...)
	{
		return false;
	}
	return true;
}


