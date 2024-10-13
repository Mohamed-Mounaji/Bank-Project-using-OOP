#pragma once
#include <iostream>
#include <fstream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;
class clsLoginScreen :protected clsScreen
{
	static bool _Login()
	{
		bool LoginFailed = false;
		short Attempts = 3;
		string UserName = "", Password = "";
		do {
			if (LoginFailed)
			{
				cout << "\nLogin Failed, Invalid UserName/Password!!\n";
				Attempts--;
				cout << "You Have " << Attempts << " trials to Login.\n";
				if (!Attempts)
				{
					cout << "\nYou Are Locked After 3 Failed Trials.\n";
					return false;
				}
			}

			cout << "\nEnter The UserName  :  ";
			UserName = clsInputValidate::ReadString();

			cout << "Enter The Password  :  ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserName, Password);
			
			LoginFailed = CurrentUser.isEmpty();

		} while (LoginFailed);

		CurrentUser.RegisterLogin();

		clsMainScreen::ShowMainMenu();
		return true;
	}


public:
	static bool  ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();
	}


};

