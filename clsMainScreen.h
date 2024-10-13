#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsFindClientScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
    enum enMainMenuOptions {
        eShowClientsList = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClientInfo = 4, eFindClient = 5, eTransactions = 6,
        eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eLogout = 10
    };

    static short _ReadMainMenuOption()
    {
        short Option;
        cout << setw(37)  << "" << "Choose what do you want to do [1 to 10] : ";
        Option = clsInputValidate::ReadNumberBetween(1, 10," \n\t\t\t\t     Invalid Number, Enter Another Number Between 1 and 10 : ");
        return Option;
    }

    static void _BackToMainMenu()
    {
        cout << setw(37) << "" << "\n\tPress Any Key to Back to Main Menu ...";
        system("pause>0");
        ShowMainMenu();
    }

    static void _ShowClientsListScreen()
    {
       // cout << "\nClients List Screen Will be here\n";
        clsClientsListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientScreen()
    {
        //cout << "\nAdd New Client Screen Will be here\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        //cout << "\nDelete Client Screen Will be here\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientInfoScreen()
    {
        //cout << "\nUpdate Clients Info Screen Will Be Here\n";
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
       // cout << "\nFind Client Screen Will be here\n";
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsScreen()
    {
        //cout << "\nTransactions Screen Will Be Here\n";
        clsTransactionsScreen::ShowTransactionsScreen();
    }

    static void _ShowManagerUsersScreen()
    {
        //cout << "\nManage Users Screen Will Be Here\n";
        clsManageUsersScreen::ShowManageUsersScreen();
    }

    static void _ShowLoginRegisterScreen()
    {
        //cout << "Login Register will be here\n";
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeScreen()
    {
       // cout << "\nCurrency Exchange Screen Will be Here.\n";
        clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMainMenuScreen();
    }

    static void _Logout()
    {
        //cout << "\nLogout Screen :(";
        CurrentUser = clsUser::Find("");

    }

    static void _PerformMainMenuOption(enMainMenuOptions Option)
    {
        switch (Option)
        {
        case enMainMenuOptions::eShowClientsList:
        {
            system("cls");
            _ShowClientsListScreen();
            _BackToMainMenu();
            break;
        }
        case enMainMenuOptions::eAddNewClient:
        {
            system("cls");
            _ShowAddNewClientScreen();
            _BackToMainMenu();
            break;
        }
        case enMainMenuOptions::eDeleteClient:
        {
            system("cls");
            _ShowDeleteClientScreen();
            _BackToMainMenu();
            break;
        }
        case enMainMenuOptions::eUpdateClientInfo:
        {
            system("cls");
            _ShowUpdateClientInfoScreen();
            _BackToMainMenu();
            break;
        }
        case enMainMenuOptions::eFindClient:
        {
            system("cls");
            _ShowFindClientScreen();
            _BackToMainMenu();
            break;
        }
        case enMainMenuOptions::eTransactions:
        {
            system("cls");
            _ShowTransactionsScreen();
            _BackToMainMenu();
            break;
        }
        case enMainMenuOptions::eManageUsers:
        {
            system("cls");
            _ShowManagerUsersScreen();
            _BackToMainMenu();
            break;
        }
        case enMainMenuOptions::eLoginRegister:
            system("cls");
            _ShowLoginRegisterScreen();
            _BackToMainMenu();
        case enMainMenuOptions::eCurrencyExchange:
                system("cls");
                _ShowCurrencyExchangeScreen();
                _BackToMainMenu();
        case enMainMenuOptions::eLogout:
        {
            system("cls");
            _Logout();
            break;
        }

        }
    }

public:

	static void ShowMainMenu()
	{
        system("cls");
		_DrawScreenHeader("\t\tMain Screen" );

        cout << setw(37) << "" << "===========================================\n";
        cout << setw(37) << "" << "\t\t      Main Menu\n";
        cout << setw(37) << "" << "===========================================\n";
        cout << setw(37) << "" << "\t[1] Clients List.\n";
        cout << setw(37) << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << "" << "\t[5] Find Client.\n";
        cout << setw(37) << "" << "\t[6] Transactions.\n";
        cout << setw(37) << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << "" << "\t[8] Login Register.\n";
        cout << setw(37) << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << "" << "\t[10] Logout.\n";
        cout << setw(37) << "" << "===========================================\n";

        _PerformMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
	}

};

