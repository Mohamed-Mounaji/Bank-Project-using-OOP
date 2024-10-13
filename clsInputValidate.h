#pragma once
#include "clsDate.h"
#include "clsPeriod.h"
#include <iostream>;
#include <limits>

using namespace std;

class clsInputValidate
{
public:

	template <typename T> static bool isNumberBetween(T Num, T From, T To)
	{
		return Num <= To && Num >= From;
	}

	static bool isDateBetween(clsDate Date, clsDate StartDate, clsDate EndDate)
	{
		return !((clsDate::isDate1BeforeDate2(Date, StartDate) && clsDate::isDate1BeforeDate2(Date, EndDate))
			|| (clsDate::isDate1AfterDate2(Date, StartDate) && clsDate::isDate1AfterDate2(Date, EndDate)));
	}

	static bool isDateBetweenPeriod(clsDate Date, clsPeriod Period)
	{
		return isDateBetween(Date, Period.StartDate, Period.EndDate);
	}

	template <typename T> static T ReadNumber(string ErrorMessage = "Invalid Number, Enter Another Number : ")
	{
		T Num;
		while (!(cin >> Num))
		{
			cin.clear();
			cin.ignore(numeric_limits <streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Num;

	}

	template <typename T> static T ReadNumberBetween(T From, T To, string ErrorMessage = "Invalid Number, Enter Another Number : ")
	{
		T Number = ReadNumber<T>(ErrorMessage);

		while (Number > To || Number < From)
		{
			cout << ErrorMessage;
			Number = ReadNumber<T>(ErrorMessage);
		}
		return Number;
	}

	static bool isValidDate(clsDate Date)
	{
		return clsDate::isValidDate(Date);
	}

	static bool isValidDate(short Day, short Month, short Year)
	{
		return clsDate::isValidDate(clsDate(Day, Month, Year));
	}

	static string ReadString()
	{
		string Text = "";
		getline(cin >> ws, Text);
		return Text;
	}

};

