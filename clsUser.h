#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"
#include "clsDate.h"
#include "clsUtil.h"
using namespace std;

class clsUser : public clsPerson
{
private:
	enum enMode { eEmptyMode = 1, eUpdateMode = 2, eAddNewMode = 3};

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedToDelete = false;

	static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#")
	{
		vector <string> vRecord = clsString::Split(Line, Separator);
		return clsUser(enMode::eUpdateMode, vRecord[0], vRecord[1], vRecord[2], vRecord[3],
			vRecord[4], clsUtil::DecryptText(vRecord[5],5), stoi(vRecord[6]));
	}

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLineToLoginRegisterRecord(string Line, string Separator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;
		vector <string> LoginRegisterDataLine = clsString::Split(Line, Separator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2],5);
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);
		return LoginRegisterRecord;
	}

	static string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#")
	{
		string UserRecord = "";
		UserRecord += User.FirstName + Separator;
		UserRecord += User.LastName + Separator;
		UserRecord += User.Email + Separator;
		UserRecord += User.Phone + Separator;
		UserRecord += User.UserName + Separator;
		UserRecord += clsUtil::EncryptText(User.Password, 5) + Separator;
		UserRecord += to_string(User.Permissions);
		return UserRecord;
	}

	static  vector <clsUser> _LoadUsersDataFromFile()
	{
		vector <clsUser> vUsers;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);//overwrite
		string DataLine;
		if (MyFile.is_open())
		{
			for (clsUser U : vUsers)
			{
				if (U.isMarkedToDelete() == false)
				{
					//we only write records that are not marked for delete.  
					DataLine = _ConvertUserObjectToLine(U);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.UserName == UserName)
			{
				U = *this;
				break;
			}
		}
		_SaveUsersDataToFile(_vUsers);

	}

	void _AddNew()
	{

		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::eEmptyMode, "", "", "", "", "", "", 0);
	}

	string _GetLoginRegister(string Separator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeText() + Separator;
		LoginRecord += UserName + Separator;
		LoginRecord += clsUtil::EncryptText(Password,5)+Separator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;

	}

public:

	enum enPermissions {
		eAll = -1, eClientsList = 1, eAddNewClient = 2, eDeleteClient = 4, 
		eUpdateClientInfo = 8, eFindClient = 16, eTransactions = 32, eManageUsers = 64, eLoginRegister = 128
	};

	struct stLoginRegisterRecord 
	{
			string DateTime;
			string UserName;
			string Password;
			int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool isEmpty()
	{
		return _Mode == enMode::eEmptyMode;
	}

	bool isMarkedToDelete()
	{
		return _MarkedToDelete;
	}

	string GetUserName()
	{
		return _UserName;
	}
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();

		}
		return _GetEmptyUserObject();
	}

	enum enSaveResults { svFailedEmptyOb = 0, svSucceeded = 1, svFailedUserExists = 2 };

	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::eEmptyMode:
		{
			if (isEmpty())
			{
				return enSaveResults::svFailedEmptyOb;
			}
		}

		case enMode::eUpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}

		case enMode::eAddNewMode:
		{
			//This will add new record to file or database
			if (clsUser::isUserExist(_UserName))
			{
				return enSaveResults::svFailedUserExists;
			}
			else
			{
				_AddNew();
				//We need to set the mode to update after add new
				_Mode = enMode::eUpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
		}
	}

	static bool isUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);
		return (!User.isEmpty());
	}

	bool Delete()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkedToDelete = true;
				break;
			}
		}
		_SaveUsersDataToFile(_vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static clsUser GetNewUserObject(string UserName)
	{
		return clsUser(enMode::eAddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		return ((Permission & this->Permissions) == Permission) || this->Permissions == enPermissions::eAll;
	}

	void RegisterLogin()
	{
		string LoginRegister = _GetLoginRegister();
		fstream File;
		File.open("LoginRegister.txt", ios::out | ios::app);
		if (File.is_open())
		{
			File << LoginRegister << endl;
			File.close();
		}

	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vRecords;
		fstream File;
		File.open("LoginRegister.txt", ios::in);
		if (File.is_open())
		{
			stLoginRegisterRecord Record;
			string Line;
			while (getline(File, Line))
			{
				Record = _ConvertLineToLoginRegisterRecord(Line);
				vRecords.push_back(Record);
			}
			File.close();
		}
		return vRecords;
	}
};

