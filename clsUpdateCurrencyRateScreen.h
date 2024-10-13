#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
	static float _ReadNewRate()
	{
		cout << "\nEnter New Rate : ";
		float NewRate;
		cin >> NewRate;
		return NewRate;
	}
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

public:
	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("\tUpdate Rate Screen");

		string CurrencyCode;

		cout << "\nPlease, Enter Currency Code : ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::isCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, Enter another Currency Code : ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrencyInfo(Currency);

		char Answer = 'n';

		cout << "\nAre You Sure You Want To Update the rate of This Currency y/n : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			cout << "\nUpdate Currency Rate :\n";
			cout << "______________________\n";

			Currency.UpdateRate(_ReadNewRate());

			cout << "\nCurrency Rate Updated Successfully :)\n";
			_PrintCurrencyInfo(Currency);
		}
	}
};

