#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen
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
	static void ShowAddNewClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::eAddNewClient))
		{
			return;
		}

		_DrawScreenHeader("\t  Add New Client Screen");

		string AccountNumber = "";
		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Already Used, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);


		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResult SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case  clsBankClient::enSaveResult::svSucceeded:
		{
			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClient(NewClient);
			break;
		}
		case clsBankClient::enSaveResult::svFailedEmptyOb:
		{
			cout << "\nError account was not saved because it's Empty";
			break;

		}
		case clsBankClient::enSaveResult::svFailedAccountNumExists:
		{
			cout << "\nError account was not saved because account number is used!\n";
			break;

		}
		}

	}
};

