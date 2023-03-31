#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <stdlib.h>

using namespace std;
char character[] = "0123456789ABCDEF";

string Dec2Num(long long _dec, short _db, string num)
{
	if (_dec == 0)
		return num;

	num = character[_dec % _db] + num;
	return Dec2Num(_dec / _db, _db, num);
}

long long Num2Dec(string _num, short _bn)
{
	long long dec = 0;
	int index_value, position = _num.length() - 1;

	for (int i = 0; i < _num.length(); i++)
	{
		if (_num[i] >= 'A')
			index_value = _num[i] - 55;
		else
			index_value = _num[i] - 48;

		dec += (index_value * (pow(_bn, position - i)));
	}

	return dec;
}

string Text2Boh(string _text, short _bh)
{
	stringstream boh;
	int index_ascii;
	for (int i = 0; i < _text.length(); i++)
	{
		index_ascii = _text[i];
		boh << setfill('0');
		if (_bh == 2)
			boh << setw(8);
		else
			boh << setw(2);
		boh << Dec2Num(index_ascii, _bh, "") << " ";
	}
	return boh.str();
}

string Boh2Text(string _boh, short _bh)
{
	string text = "";
	stringstream boh(_boh);
	string char_boh;
	while (boh >> char_boh)
	{
		text += (char)Num2Dec(char_boh, _bh);
	}
	return text;
}

void convertFrom(string options[], short &fs)
{
	//Asking the user to enter a number representing the system they want to convert from
	cout << "What is the system that you want to convert from:\n";
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << ". " << options[i] << endl;
	}

	cout << "Enter a number to choose: ";
	cin >> fs;

	while (fs < 1 || fs > 5)
	{
		cout << "Please enter a valid number: ";
		cin >> fs;
	}
}

void convertTo(string options[], short fs, short &ts)
{
	//Asking the user to enter a number representing the system they want to convert to
	cout << "What is the system that you wish to convert to:\n";
	for (int i = 0; i < 5; i++)
	{
		if ((fs - 1) == i)
			continue;
		cout << i + 1 << ". " << options[i] << endl;
	}

	cout << "Enter a number to choose: ";
	cin >> ts;

	while (ts < 1 || ts > 5 || ts == fs)
	{
		cout << "Please enter a valid number: ";
		cin >> ts;
	}
}

void assignBase(short fs, short ts, short &bn, short &db)
{
	short base[5] = {2, 8, 10, 16, 0};

	bn = base[fs - 1];
	db = base[ts - 1];
}

void processValue(short bn, short db, long long d, string n, string t)
{
	if (bn == 10)
	{
		cin >> d;
		n = Dec2Num(d, db, "");
		cout << "Converted Value: " << n << endl;
	}
	else if (db == 10)
	{
		cin >> n;
		d = Num2Dec(n, bn);
		cout << "Converted Value: " << d << endl;
	}
	else if (bn == 0)
	{
		cin.ignore();
		getline(cin, t);
		n = Text2Boh(t, db);
		cout << "Converted Value: " << n << endl;
	}
	else if (db == 0)
	{
		cin.ignore();
		getline(cin, n);
		t = Boh2Text(n, bn);
		cout << "Converted Value: " << t << endl;
	}
	else
	{
		cin >> n;
		d = Num2Dec(n, bn);
		n = Dec2Num(d, db, "");
		cout << "Converted Value: " << n << endl;
	}
}

void converter()
{
	short from_system = 0, to_system = 0, base_number, devide_by;
	long long dec;
	string num, text;

	string options[5] = {
		"Binary",
		"Octal ",
		"Decimal",
		"Hexadecimal",
		"Text"};

	convertFrom(options, from_system);
	system("cls");
	
	convertTo(options, from_system, to_system);
	system("cls");
	
	assignBase(from_system, to_system, base_number, devide_by);

	cout << "You are converting from " << options[from_system - 1] << " to " << options[to_system - 1] << endl;
	cout << "Enter A " << options[from_system - 1] << " Value: ";
	//.........................................................

	processValue(base_number, devide_by, dec, num, text);
}

int main()
{
	int exit = 1;
	cout << "... SystemConverter ...\nUsing this program you can convert a vlaue from any system to any system!\n\n";
	while (!(exit - 1))
	{
		converter();
		cout << "\nWhat else?" << endl;
		cout << "1. Convert another value." << endl
			 << "2. Exit program." << endl
			 << "Enter a number to choose: ";
		cin >> exit;
		system("cls");
	}
	return 0;
}
