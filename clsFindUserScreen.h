#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;
class clsFindUserScreen : protected clsScreen
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
		cout << "\nUserName    : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}

public:
	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t  Find User Screen");

		string UserName = "";
		cout << "\nEnter the UserName : ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::isUserExist(UserName))
		{
			cout << "\nThe UserName is not found, Enter another one : ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser  User = clsUser::Find(UserName);

		if (User.isEmpty())
		{
			cout << "\nUser Was not Found :-(\n";
		}
		else
		{
			cout << "\nUser Was Found Successfully :-)\n";
		_PrintUser(User);
		}
	}
};

