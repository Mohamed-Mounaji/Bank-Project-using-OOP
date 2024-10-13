#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;
class clsCurrencyExchangeMainScreen : protected clsScreen
{
    enum enCurrencyManuOptions {
        ListCurrencies = 1, FindCurrency = 2, UpdateRate = 3, CurrencyCalculator = 4, MainMenu = 5
    };

    static short _ReadCurrencyMenuOption()
    {
        short Option;
        cout << setw(37) << "" << "Choose what do you want to do [1 to 5] : ";
        Option = clsInputValidate::ReadNumberBetween(1, 5, " \n\t\t\t\t     Invalid Number, Enter Another Number Between 1 and 5 : ");
        return Option;
    }

    static void _BackToCurrencyMenu()
    {
        cout << setw(37) << "" << "\n\tPress Any Key to Back to Main Menu ...";
        system("pause>0");
        ShowCurrencyExchangeMainMenuScreen();
    }

    static void _ShowListCurrenciesScreen()
    {
       // cout << "\nList Currencies Will be here\n";
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        //cout << "\nFind Currency Screen Will Be Here \n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        //cout << "\nUpdate Rate Screen Will Be Here\n";
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
       // cout << "\nCurrency Calculator Screen Will Be Here\n";
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();

    }


    static void _PerformMenuOptions(enCurrencyManuOptions Option)
    {
        switch (Option)
        {
        case enCurrencyManuOptions::ListCurrencies:
            system("cls");
            _ShowListCurrenciesScreen();
            _BackToCurrencyMenu();
            break;
        case enCurrencyManuOptions::FindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _BackToCurrencyMenu();
            break;
        case enCurrencyManuOptions::UpdateRate:
            system("cls");
            _ShowUpdateRateScreen();
            _BackToCurrencyMenu();
            break;

        case enCurrencyManuOptions::CurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _BackToCurrencyMenu();
            break;
        case enCurrencyManuOptions::MainMenu:
        {

            //I will back auto :)
        }

        }
    }

public:
	static void ShowCurrencyExchangeMainMenuScreen()
	{
        system("cls");
		_DrawScreenHeader("\tCurrency Exchange Main Menu");

        cout << setw(37) << "" << "===========================================\n";
        cout << setw(37) << "" << "\t\tCurrency Exchange Menu\n";
        cout << setw(37) << "" << "===========================================\n";
        cout << setw(37) << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << "" << "===========================================\n";

        _PerformMenuOptions((enCurrencyManuOptions)_ReadCurrencyMenuOption());
	}
};

