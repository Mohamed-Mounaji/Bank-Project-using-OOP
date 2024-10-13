#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{


	static void _PrintClientRecordLine(clsBankClient Client)
	{
		cout << "\t\t\t\t";
		cout << "|" << setw(20) << left << Client.AccountNumber();
		cout << "|" << setw(20) << left << Client.FullName();
		cout << "|" << setw(12) << left << Client.AccountBalance;
	}

public:
	static void ShowTotalBalancesScreen()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\t   Total Balances Screen.";
		string SubTitle = "\t\t" + to_string(vClients.size()) + " Client (s).";

		_DrawScreenHeader(Title, SubTitle);


		cout << "\n\t\t\t___________________________________________________";
		cout << "_________________________\n" << endl;

		cout << "\t\t\t\t|" << setw(20) << left << "Account Number";
		cout << "|" << setw(20) << left << "Full Name";
		cout << "|" << setw(12) << left << "Account Balance";

		cout << "\n\t\t\t___________________________________________________";
		cout << "_________________________\n" << endl;

		if (vClients.size() == 0)
		{
			cout << "\n\t\t\t\tNo Clients Available In The System!\n";
		}
		else
		{
			for (clsBankClient Client : vClients)
			{
				_PrintClientRecordLine(Client);
				cout << endl;
			}
		}

		cout << setw(7) << "" << "\n\t\t\t___________________________________________________";
		cout << "_________________________\n" << endl;

		float TotalBalances = clsBankClient::TotalBalances();
		cout << "\n" << clsUtil::Tabs(6) << "Total Balances = " << TotalBalances ;
		cout << "\n\n" << clsUtil::Tabs(5) << clsUtil::NumberToText(TotalBalances) << endl;


	}
};

