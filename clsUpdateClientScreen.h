#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : clsScreen
{
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter First Name : ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name : ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email : ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone : ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Pin Code : ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance : ";
		Client.AccountBalance = clsInputValidate::ReadNumber<float>();
	}

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

	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::eUpdateClientInfo))
		{
			return;
		}

		_DrawScreenHeader("\t  Update Client Screen");

		string AccountNum = "";
		cout << "\nPlease Enter Account Number : ";
		AccountNum = clsInputValidate::ReadString();

		while (!clsBankClient::isClientExist(AccountNum))
		{
			cout << "\nAccount Number is Not Found, Enter Another One : ";
			AccountNum = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNum);
		_PrintClient(Client);
		
		char Answer = 'n';
		cout << "\nAre You Sure You Want To Update This Client Info : ";
		cin >> Answer;
		
		if (tolower(Answer) == 'y')
		{
			cout << "\n\nUpdate Client Info:";
			cout << "\n____________________\n";
			_ReadClientInfo(Client);

			clsBankClient::enSaveResult SaveResult;
			SaveResult = Client.Save();
			switch (SaveResult)
			{
			case clsBankClient::enSaveResult::svFailedEmptyOb:
				cout << "\nError, Can't save Empty Account !!";
				break;

			case clsBankClient::enSaveResult::svSucceeded:
				cout << "\nAccount Has been Updated Successfully :)";
				_PrintClient(Client);
				break;
			}

		}

	}

};