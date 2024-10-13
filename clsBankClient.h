#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 3};
	
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedToDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Delim = "#//#")
	{
		vector <string> ClientData = clsString::Split(Line, Delim);

		return clsBankClient(enMode::UpdateMode, ClientData[0], ClientData[1], ClientData[2],
			ClientData[3], ClientData[4], ClientData[5], stof(ClientData[6]));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
	{
		string Line = "";
		Line += Client.FirstName + Separator;
		Line += Client.LastName + Separator;
		Line += Client.Email + Separator;
		Line += Client.Phone + Separator;
		Line += Client.AccountNumber() + Separator;
		Line += Client.PinCode + Separator;
		Line += to_string(Client.AccountBalance);
		return Line;
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;
		fstream File;
		File.open("Clients.txt", ios::in);//Read Mode
		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				vClients.push_back(_ConvertLineToClientObject(Line));
			}
			File.close();
		}
		return vClients;
	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{
		fstream File;
		File.open("Clients.txt", ios::out);
		if (File.is_open())
		{
			for (clsBankClient& Client : vClients)
			{
				if(!Client._MarkedToDelete)
					File << _ConvertClientObjectToLine(Client) << endl;
			}
			File.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for(clsBankClient &C : vClients)
		{
			if (C.AccountNumber() == this->AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream File;
		File.open("Clients.txt", ios::out | ios::app);
		if (File.is_open())
		{
			File << DataLine << endl;
			File.close();
		}
	}
	
	string _GetTransferInfoRecord( clsBankClient TargetClient, float TransferAmount, string UserName)
	{
		string Record = "";
		Record += clsDate::GetSystemDateTimeText() + "#//#";
		Record += AccountNumber() + "#//#";
		Record += TargetClient.AccountNumber() + "#//#";
		Record += to_string(TransferAmount) + "#//#";
		Record += to_string(AccountBalance) += "#//#";
		Record += to_string(TargetClient.AccountBalance) += "#//#";
		Record += UserName;
		return Record;
	}

	void _RegisterTransferOperation(clsBankClient TargetClient, float TransferAmount, string UserName)
	{
		string Record = _GetTransferInfoRecord( TargetClient, TransferAmount, UserName);

		fstream File;
		File.open("TransferLog.txt", ios::out | ios::app);
		if (File.is_open())
		{
			File << Record << endl;
			File.close();
		}	
	}
	struct stTransferLog;
	static stTransferLog _ConvertLineToTransferLogRecord(string Line, string Separator = "#//#")
	{
		vector <string> vElements = clsString::Split(Line, Separator);
		stTransferLog Record;
		Record.Time = vElements[0];
		Record.SourceAccNum = vElements[1];
		Record.TargetAccNum = vElements[2];
		Record.TransferAmount = stof(vElements[3]);
		Record.SourceBalance = stof(vElements[4]);
		Record.TargetBalance = stof(vElements[5]);
		Record.UserName = vElements[6];

		return Record;

	}


public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, float AccountBalance ): clsPerson(FirstName,LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	struct stTransferLog
	{
		string Time;
		string SourceAccNum;
		string TargetAccNum;
		float TransferAmount;
		float SourceBalance;
		float TargetBalance;
		string UserName;
	};


	bool isEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool isClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return !Client.isEmpty();
	}

	enum enSaveResult { svFailedEmptyOb = 0, svSucceeded = 1, svFailedAccountNumExists = 3};

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResult::svFailedEmptyOb;

		case enMode::UpdateMode:
			_Update();
			return enSaveResult::svSucceeded;
		case enMode::AddNewMode:
			if (clsBankClient::isClientExist(_AccountNumber))
			{
				return enSaveResult::svFailedAccountNumExists;
			}
			else
			{
				_AddNew();

				//Now after the object is added it is no longer addNew mode because it exsits in the data base, so we should set it as UpdateMode
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}
			}
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		for (clsBankClient& Client : vClients)
		{
			if (Client.AccountNumber() == _AccountNumber)
			{
				Client._MarkedToDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();
		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static float GetTotalBalances()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		float TotalBalances = 0;
		for (clsBankClient Client : vClients) TotalBalances += Client.AccountBalance;
		return TotalBalances;
	}

	void Deposit(float Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(float Amount)
	{
		if (Amount > _AccountBalance)
			return false;
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	static double TotalBalances()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		double Total = 0;
		for (clsBankClient Client : vClients) Total += Client.AccountBalance;
		return Total;
	}

	bool Transfer(clsBankClient &TargetClient, float TransferAmount, string UserName)
	{
		if (AccountBalance < TransferAmount)
			return false;

		Withdraw(TransferAmount);
		TargetClient.Deposit(TransferAmount);
		_RegisterTransferOperation(TargetClient, TransferAmount, UserName);
		return true;

	}

	static vector <stTransferLog> GetTransferLogList()
	{
		vector <stTransferLog> vList;
		fstream File;
		File.open("TransferLog.txt", ios::in);

		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				vList.push_back(_ConvertLineToTransferLogRecord(Line));
			}
			File.close();
		}

		return vList;
	}


};

