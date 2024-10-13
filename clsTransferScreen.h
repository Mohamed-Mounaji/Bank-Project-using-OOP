#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsTransferScreen : protected clsScreen
{
	static clsBankClient _ReadBankClient(string Message)
	{
		cout << Message;
		string AccountNum =	clsInputValidate::ReadString();

		while (!clsBankClient::isClientExist(AccountNum))
		{
			cout << "\nClient With [" << AccountNum << "] is not found, Enter another one : ";
			AccountNum = clsInputValidate::ReadString();
		}
		return clsBankClient::Find(AccountNum);
	}

	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card :";
		cout << "\n____________________________\n";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n____________________________\n";

	}


public:
	static void ShowTransferScreen() 
	{
		_DrawScreenHeader("\t  Transfer Screen");

		clsBankClient SourceClient = _ReadBankClient("\nEnter Account Number To transfer From : ");
		_PrintClientCard(SourceClient);

		clsBankClient TargetClient = _ReadBankClient("\nEnter Account Number To transfer To : ");
		_PrintClientCard(TargetClient);

		cout << "\nEnter Transfer Amount : ";
		float Amount = clsInputValidate::ReadNumber<float>();
		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceed The Available Balance, Enter Another Amount : ";
			Amount = clsInputValidate::ReadNumber<float>();
		}

		char Answer = 'n';
		cout << "\nAre You Sure You Want To Perform This Operation y/n : ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			if (SourceClient.Transfer(TargetClient, Amount, CurrentUser.UserName))
			{
				cout << "\nTransfer done successfully\n";
			}
			else
			{
				cout << "\nTransfer Failed \n";
			}

			_PrintClientCard(SourceClient);
			_PrintClientCard(TargetClient);
		}

	}
};

