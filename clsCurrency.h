#pragma once
#include <iostream>
#include <vector> 
#include <fstream>
#include <string>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:
	enum enMode { eEmptyMode = 0, eUpdateMode = 1 };
	enMode _Mode;

	string _Country = "";
	string _CurrencyCode = "";
	string _CurrencyName = "";
	float _Rate = 0;

	static clsCurrency _ConvertLineToCurrencyObject(string Line)
	{
		vector <string> vCurrencyData = clsString::Split(Line, "#//#");		
		return clsCurrency(enMode::eUpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector <clsCurrency> vCurrencies;
		fstream File;
		File.open("Currencies.txt", ios::in);

		if (File.is_open())
		{
			string Line = "";
			while (getline(File, Line))
			{
				vCurrencies.push_back(_ConvertLineToCurrencyObject(Line));
			}
			File.close();
		}
		return vCurrencies;
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#")
	{
		string Line = "";
		Line += Currency.Country() + Separator;
		Line += Currency.CurrencyCode() + Separator;
		Line += Currency.CurrencyName() + Separator;
		Line += to_string(Currency.Rate());
		return Line;
	}

	static void _SaveCurrenciesDataToFile(vector <clsCurrency> vCurrencies)
	{
		fstream File;
		File.open("Currencies.txt", ios::out);
		if (File.is_open())
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				File << _ConvertCurrencyObjectToLine(Currency) << endl;
			}
			File.close();
		}


	}

	void _Update()
	{
		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C : vCurrencies)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}

		_SaveCurrenciesDataToFile(vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::eEmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool isEmpty()
	{
		return _Mode == enMode::eEmptyMode;
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();
		for (clsCurrency& C : vCurrencies)
		{
			if (C.CurrencyCode() == CurrencyCode)
			{
				return C;
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);
		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();
		for (clsCurrency& C : vCurrencies)
		{
			if (clsString::UpperAllString(C.Country()) == Country)
			{
				return C;
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static bool isCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);
		return !Currency.isEmpty();
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return Amount / _Rate;
	}

	float ConvertToAnotherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);
		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}
		return AmountInUSD * Currency2.Rate();
	}
};

