#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
class clsTransferLogListScreen : protected clsScreen
{

	static void _PrintRecord(clsBankClient::stTransferLog Record)
	{
		cout << "\t| " << setw(25) << left << Record.Time;
		cout << "| " << setw(10) << left << Record.SourceAccNum;
		cout << "| " << setw(10) << left << Record.TargetAccNum;
		cout << "| " << setw(10) << left << Record.TransferAmount;
		cout << "| " << setw(10) << left << Record.SourceBalance;
		cout << "| " << setw(10) << left << Record.TargetBalance;
		cout << "| " << setw(10) << left << Record.UserName;
	}
public:

	static void ShowTransferLogListScreen()
	{
		vector <clsBankClient::stTransferLog> vRecords = clsBankClient::GetTransferLogList();
		string Title = "\tTransfer Log List Screen";
		string SubTitle = "\t     (" + to_string(vRecords.size()) + ") Record(s)";
		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\t_________________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "\t| " << setw(25) << left << "Date/Time";
		cout << "| " << setw(10) << left << "S.Acct";
		cout << "| " << setw(10) << left << "T.Acct";
		cout << "| " << setw(10) << left << "Amount";
		cout << "| " << setw(10) << left << "S.Balance";
		cout << "| " << setw(10) << left << "T.Balance";
		cout << "| " << setw(10) << left << "User";

		cout << "\n\t_________________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vRecords.size() == 0)
		{
			cout << clsUtil::Tabs(5) << "No Records Available in the system\n";
		}
		else
		{
			for (clsBankClient::stTransferLog Record : vRecords)
			{
				_PrintRecord(Record);
				cout << endl;
			}
		}


		cout << "\n\t_________________________________________________________";
		cout << "_________________________________________\n" << endl;

	}
};

