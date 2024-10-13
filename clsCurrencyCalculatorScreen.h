#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
class clsCurrencyCalculatorScreen : protected clsScreen
{

	static clsCurrency _ReadCurrency(string ErrorMessage = "\nCurrency is not found, Enter another One : ")
	{
		string CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::isCurrencyExist(CurrencyCode))
		{
			cout << ErrorMessage;
			CurrencyCode = clsInputValidate::ReadString();
		}
		return clsCurrency::FindByCode(CurrencyCode);
	}

	static void _PrintCurrencyInfo(clsCurrency Currency)
	{
		cout << "\n___________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate / 1$  : " << Currency.Rate();
		cout << "\n___________________________\n";
	}

	static void _PrintCalculationResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
	{
		cout << "\nConvert From:\n";
		_PrintCurrencyInfo(Currency1);

		float AmountInUSD = Currency1.ConvertToUSD(Amount);
		cout <<endl << Amount << " " << Currency1.CurrencyCode();
		cout << " = ";
		cout << AmountInUSD << " USD";

		if (Currency2.CurrencyCode() == "USD")
		{
			return;
		}

		cout << "Convert To : ";
		_PrintCurrencyInfo(Currency2);
		float AmountInCurrency2 = Currency1.ConvertToAnotherCurrency(Amount, Currency2);
		cout << endl << Amount << " " << Currency1.CurrencyCode();
		cout << " = ";
		cout << AmountInCurrency2 << " " << Currency2.CurrencyCode();

	}


public:
	static void ShowCurrencyCalculatorScreen()
	{
		char Continue = 'y';
		while (tolower(Continue) == 'y')
		{
			system("cls");
			_DrawScreenHeader("\tCurrency Calculator Screen.");

			cout << "\nPlease Enter Currency1 Code : ";
			clsCurrency Currency1 = _ReadCurrency();

			cout << "\nPlease Enter Currency2 Code : ";
			clsCurrency Currency2 = _ReadCurrency();

			cout << "\nEnter Amount To Exchange : ";
			float Amount = clsInputValidate::ReadNumber<float>();

			_PrintCalculationResults(Amount, Currency1, Currency2);
			
			cout << "\n\nDo you want to perform another calculation y/n : ";
			cin >> Continue;
		}
		
	}
};

