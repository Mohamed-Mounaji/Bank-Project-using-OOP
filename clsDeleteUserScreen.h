#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iostream>

using namespace std;

class clsDeleteUserScreen : protected clsScreen
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

public:
	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\t  Delete User Screen");

		string UserName = "";
		cout << "\nEnter The UserName : ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::isUserExist(UserName))
		{
			cout << "The UserName is not found, enter another one : ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		cout << "\nAre You Sure You Want To Delete This User y/n : ";
		char Answer = 'n';
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted Successfully :-)\n";
				_PrintUser(User);
			}
			else
			{
				cout << "\nError, User Was not Deleted!!\n";
			}
		}

	}
};

