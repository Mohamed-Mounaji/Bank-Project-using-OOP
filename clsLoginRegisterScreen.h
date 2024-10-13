#pragma once
#include "clsScreen.h"
#include "clsUtil.h"
#include <fstream>
#include <string>
#include "clsString.h"
using namespace std;
class clsLoginRegisterScreen : protected clsScreen
{
	static void _PrintRegisterRecord(clsUser::stLoginRegisterRecord Record)
	{

		cout << clsUtil::Tabs(1) << setw(40) << left << "|" + Record.DateTime;
		cout << setw(20) << "|" + Record.UserName;
		cout << setw(20) << "|" + Record.Password;
		cout << setw(20) << "|" + to_string(Record.Permissions);
		cout << endl;

	}

public:

	static void ShowLoginRegisterScreen()
	{
		if(!CheckAccessRights( clsUser::enPermissions::eLoginRegister ))
		{
			return;
		}
		_DrawScreenHeader("\tLogin Register Screen");

		vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecords = clsUser::GetLoginRegisterList();

		cout << "\n\t_________________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout <<clsUtil::Tabs(1)<< setw(40) << left << "|Login Date & Time";
		cout << setw(20) << "|UserName";
		cout << setw(20) << "|Password";
		cout << setw(20) << "|Permissions";
		cout << "\n\t_________________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vLoginRegisterRecords.empty())
			cout << clsUtil::Tabs(4) << "There is no Date available in the system\n";
		else
			for (clsUser::stLoginRegisterRecord Record : vLoginRegisterRecords) _PrintRegisterRecord(Record) ;
		cout << "\n\t_________________________________________________________";
		cout << "_________________________________________\n" << endl;


	}
};

