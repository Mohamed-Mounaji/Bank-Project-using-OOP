#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

using namespace std;

class clsClientsListScreen : protected clsScreen
{
private:
	static void _PrintClientRecordLine(clsBankClient Client)
	{
		cout << "\t";
		cout << "|" << setw(15) << left << Client.AccountNumber();
		cout << "|" << setw(20) << left << Client.FullName();
		cout << "|" << setw(12) << left << Client.Phone;
		cout << "|" << setw(20) << left << Client.Email;
		cout << "|" << setw(10) << left << Client.PinCode;
		cout << "|" << setw(12) << left << Client.AccountBalance;
	}

public:
	static void ShowClientsList()
	{
		if (!CheckAccessRights(clsUser::enPermissions::eClientsList))
		{
			return;
		}
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\t  Client List Screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\t_________________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "\t|" << setw(15) << left << "Account Number";
		cout << "|" << setw(20) << left << "Full Name";
		cout << "|" << setw(12) << left << "Phone";
		cout << "|" << setw(20) << left << "Email";
		cout << "|" << setw(10) << left << "Pin Code";
		cout << "|" << setw(12) << left << "Account Balance";

		cout << "\n\t_________________________________________________________";
		cout << "_________________________________________\n" << endl;

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
		cout << setw(7) << "" << "\n\t_________________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};

