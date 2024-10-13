#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
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

public:
	static void ShowFindClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::eFindClient))
		{
			return;
		}
		_DrawScreenHeader("\t  Find Client Screen");

		string AccountNum = "";
		cout << "\nEnter Account Number : ";
		AccountNum = clsInputValidate::ReadString();
		while (!clsBankClient::isClientExist(AccountNum))
		{
			cout << "\nAccount Number is not found, Enter another one : ";
			AccountNum = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNum);
		
		if (!Client.isEmpty())
		{
			cout << "\nClient Was Found :-)\n";
		}
		else
		{
			cout << "\nClient Was NOT Found :-(\n";
		}

		_PrintClient(Client);
	}
};

