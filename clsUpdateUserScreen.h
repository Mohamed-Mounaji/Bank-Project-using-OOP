#pragma once
#include "clsScreen.h"

class clsUpdateUserScreen : protected clsScreen
{
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter First Name : ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name  : ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email : ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone : ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password : ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permissions : \n";
		User.Permissions = _ReadPermissions();


	}

	static int _ReadPermissions()
	{
		int Permissions = 0;
		char Answer = 'n';

		cout << " \nDo you want to give this user full access y/n: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			return -1;
		}

		cout << "\nDo you want to give them access to\n";

		cout << "\nClients List y/n : ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::eClientsList;
		}

		cout << "\nAdd New Client y/n : ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::eAddNewClient;
		}

		cout << "\nDelete Client y/n : ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::eDeleteClient;
		}

		cout << "\nUpdate Client Info y/n : ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::eUpdateClientInfo;
		}

		cout << "\nFind Client y/n : ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::eFindClient;
		}

		cout << "\nTransactions y/n : ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::eTransactions;
		}

		cout << "\nManage Users y/n : ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::eManageUsers;
		}
		cout << "\nLogin Register y/n : ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::eLoginRegister;
		}

		return Permissions;
	}


public:
	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\t  Update User Screen");

		string UserName = "";
		cout << "\nEnter The UserName : ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::isUserExist(UserName))
		{
			cout << "\nThe UserName is not found, Enter another one : ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer = 'n';
		cout << "\nAre Sure You Want To Update This User y/n : ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			cout << "\n\nUpdate User Info:";
			cout << "\n____________________\n";

			_ReadUserInfo(User);

			clsUser::enSaveResults SaveResult = User.Save();

			switch (SaveResult)
			{
			case clsUser::enSaveResults::svSucceeded:
				cout << "\nUser Updated Successfully :-)\n";
				_PrintUser(User);
				break;
			case clsUser::enSaveResults::svFailedEmptyOb:
			{
				cout << "\nError User was not saved because it's Empty";
				break;
			}
			}
		}
	}
};

