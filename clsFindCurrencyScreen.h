#pragma once
#include "clsScreen.h"
#include <iostream>

using namespace std;
class clsFindCurrencyScreen : protected clsScreen
{

	static void _PrintCurrencyInfo(clsCurrency Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n___________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate / 1$  : " << Currency.Rate();
		cout << "\n___________________________\n";

	}

	static void _PrintResult(clsCurrency Currency)
	{
		if (Currency.isEmpty())
		{
			cout << "\nCurrency Was Not Found :(\n";
		}
		else
		{
			cout << "\nCurrency Was Found Successfully :)\n";
			_PrintCurrencyInfo(Currency);
		}
	}
public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\tFind Currency Screen.");

		short FindBy;
		cout << "\nFind By [1] Code or [2] Country  : ";
		FindBy = clsInputValidate::ReadNumberBetween(1, 2, "\nInvalid Number, Enter 1 or 2 : ");

		if (FindBy == 1)
		{
			cout << "\nPlease Enter Currency Code : ";
			string Code = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(Code);
			_PrintResult(Currency);
			
		}
		else
		{
			cout << "\nPlease Enter Country Name : ";
			string Code = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Code);
			_PrintResult(Currency);
		}

	}
};

