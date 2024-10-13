#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;
class clsCurrenciesListScreen : protected clsScreen
{
	static void _PrintCurrencyRecord(clsCurrency Currency)
	{
		cout << "\t|" << setw(30) << left << Currency.Country();
		cout << "|" << setw(10) << left << Currency.CurrencyCode();
		cout << "|" << setw(45) << left << Currency.CurrencyName();
		cout << "|" << setw(10) << left << Currency.Rate();
	}

public:
	static void ShowCurrenciesListScreen()
	{
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

		string Title = "\tCurrencies List Screen.";
		string SubTitle = "\t    " + to_string(vCurrencies.size()) + " Currencies.";
		_DrawScreenHeader(Title, SubTitle);


		cout << "\n\t_________________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "\t|" << setw(30) << left << "Country";
		cout << "|" << setw(8) << left << "Code";
		cout << "|" << setw(45) << left << "Name";
		cout << "|" << setw(10) << left << "Rate / 1$";
		cout << "\n\t_________________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vCurrencies.size() == 0)
		{
			cout << "\n\t\t\t\t\tNo Data Available in The System!!\n";
		}
		else
		{
			for (clsCurrency& C : vCurrencies)
			{
				_PrintCurrencyRecord(C);
				cout << endl;
			}
		}

		cout << "\n\t_________________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};

