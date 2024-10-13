#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDepositScreen : protected clsScreen
{
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}

	static string _ReadAccountNumber()
	{
		cout << "\nPlease Enter Account Number : ";
		string AccountNumber = clsInputValidate::ReadString();
		return AccountNumber;
	}

public:
	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t  Deposit Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\nClient With [" << AccountNumber << "] Does Not Exist.";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);
		
		float Amount = 0;
		cout << "\nPlease Enter the deposit amount : ";
		Amount = clsInputValidate::ReadNumber<float>();

		char Answer = 'n';
		cout << "\nAre You Sure You Want To Perform This Transaction : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			Client.Deposit(Amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is: " << Client.AccountBalance;
		}
		else
		{
			cout << "\nThe Operation Was Cancelled.\n";
		}
	}
};
