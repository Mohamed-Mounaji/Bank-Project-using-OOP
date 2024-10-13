#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsUser.h"
#include "clsTransferLogListScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:
    enum enTransactionsMenuOptions
    {
        eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4 ,eTransferLog=5, eMainMenu = 6
    };

    static short _ReadTransactionsMenuOption()
    {
        cout << setw(37) << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadNumberBetween(1, 6, "Invalid Number, Enter Number Between 1 and 6 : ");
        return Choice;
    }

    static void _BackToTransactionsMenu()
    {
        cout << "\n\t\tPress Any Key To Back To Transactions Menu . . .\n";
        system("pause>0");
        ShowTransactionsScreen();
    }

    static void _ShowDepositScreen()
    {
        //cout << "\nDeposit Screen Will Be Here in the Future";
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        //cout << "\nWithdraw Screen Will Be Here in the future";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        //cout << "\nTotal Balances Screen Will Be Here in The Future";
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }

    static void _ShowTransferScreen()
    {
        //cout << "Transfer Screen Will be here.\n";
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogListScreen()
    {
        //cout << "TransferLogScreen WILL BE HERE!";
        clsTransferLogListScreen::ShowTransferLogListScreen();
    }

    static void _PerformTransactionsMenuOption(enTransactionsMenuOptions Option)
    {
        switch (Option)
        {
        case enTransactionsMenuOptions::eDeposit:
        {
            system("cls");
            _ShowDepositScreen();
            _BackToTransactionsMenu();
            break;
        }
        case enTransactionsMenuOptions::eWithdraw:
        {
            system("cls");
            _ShowWithdrawScreen();
            _BackToTransactionsMenu();
            break;
        }
        case enTransactionsMenuOptions::eTotalBalances:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _BackToTransactionsMenu();
            break;
        }
        case enTransactionsMenuOptions::eTransfer:
        {
            system("cls");
            _ShowTransferScreen();
            _BackToTransactionsMenu();
            break;
        }
        case enTransactionsMenuOptions::eTransferLog:
        {
            system("cls");
            _ShowTransferLogListScreen();
            _BackToTransactionsMenu();
            break;
        }
        case enTransactionsMenuOptions::eMainMenu:
        {
            //We need not to add any code here it will automatically back  to main menu "You can trace the code to see :)"
        }
        }
    }

public:
	static void ShowTransactionsScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::eTransactions))
        {
            return;
        }
		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << "" << "===========================================\n";
        cout << setw(37) << "" << "\t\t\tMain Menu\n";
        cout << setw(37) << "" << "===========================================\n";
        cout << setw(37) << "" << "\t[1] Deposit.\n";
        cout << setw(37) << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << "" << "\t[4] Transfer.\n";
        cout << setw(37) << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << "" << "\t[6] Main Manu.\n";
        cout << setw(37) << "" << "===========================================\n";

        _PerformTransactionsMenuOption((enTransactionsMenuOptions)_ReadTransactionsMenuOption());

	}
};

