#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;
class clsAddNewUserScreen : protected clsScreen
{
private:
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

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\tAdd New User Screen");

		string UserName = "";
		
		cout << "\nPlease, Enter a UserName : ";
		UserName = clsInputValidate::ReadString();
		while (clsUser::isUserExist(UserName))
		{
			cout << "\nThe UserName is already used, choose another one : ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetNewUserObject(UserName);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResult = NewUser.Save();
		
		switch (SaveResult)
		{
		case clsUser::enSaveResults::svFailedEmptyOb:
			cout << "\nError, Save Failed, You Can Not Save An Empty User!!\n";
			break;
		case clsUser::enSaveResults::svFailedUserExists:
			cout << "\nError, Save Failed, This User Already Exists!!\n";
			break;
		case clsUser::enSaveResults::svSucceeded:
			cout << "\nThe User Added Successfully :-)\n";
			_PrintUser(NewUser);
			break;
		}

	}
};

