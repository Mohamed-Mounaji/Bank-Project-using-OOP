#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:
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
	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::eDeleteClient))
		{
			return;
		}
		_DrawScreenHeader("\t  Delete Client Screen");

		string AccountNumber ="";

		cout << "\nPlease Enter The Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\nThe Account Number is not found, Enter another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		char Answer = 'n';
		cout << "\nAre you sure you want to delete this client : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (Client.Delete())
			{
				cout << "\nClient Has Been Deleted Successfully :-)\n";
				_PrintClient(Client);
			}
			else
			{
				cout << "\nError, Client Was not Deleted\n";
			}
		}
	}
};

