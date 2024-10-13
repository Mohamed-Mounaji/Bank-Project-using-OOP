#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUser.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
    enum enManageUsersMenuOptions 
    { 
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
    };

    static short _ReadManageUsersMenuOption()
    {
        cout << clsUtil::Tabs(4) << "     Choose What Do You Want To Do [1 to 6] : ";
        short Choice = clsInputValidate::ReadNumberBetween(1,6,"\n\t\t\t\t     Invalid Number, Enter Another Number Between 1 and 6 :");
        return Choice;    
    }

    static void _BackToManageUsersScreen()
    {
        cout << "\n\nPress Any Key To Back To Manage Users Screen . . .";
        system("pause > 0");
        ShowManageUsersScreen();
    }

    static void _ShowListUsersScreen()
    {
       // cout << "\nHere will be the list of users . . . \n";
        clsUsersListScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        //cout << "\nHere Will be the add new user screen\n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        //cout << "\nHere Will be the delete user screen\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        //cout << "\nHere Will Be the update user screen\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        //cout << "\nHere will be the find user screen\n";
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void PerformManageUsersOption(enManageUsersMenuOptions Option)
    {
        switch (Option)
        {
        case enManageUsersMenuOptions::eListUsers:
        {
           system("cls");
           _ShowListUsersScreen();
           _BackToManageUsersScreen();
           break;
        
        }
        case enManageUsersMenuOptions::eAddNewUser:
        {
            system("cls");
            _ShowAddNewUserScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersMenuOptions::eDeleteUser:
        {
            system("cls");
            _ShowDeleteUserScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersMenuOptions::eUpdateUser:
        {
            system("cls");
            _ShowUpdateUserScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersMenuOptions::eFindUser:
        {
            system("cls");
            _ShowFindUserScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersMenuOptions::eMainMenu:
        {
           //No need to write anything here :-)
        }

        }
    }


public:

	static void ShowManageUsersScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::eManageUsers))
        {
            return;
        }
		system("cls");
		_DrawScreenHeader("\tManage Users Screen");

        cout << setw(37) << "" << "===========================================\n";
        cout << setw(37) << "" << "\t\t     Manage Users\n";
        cout << setw(37) << "" << "===========================================\n";
        cout << setw(37) << "" << "\t[1] List Users.\n";
        cout << setw(37) << "" << "\t[2] Add New User.\n";
        cout << setw(37) << "" << "\t[3] Delete User.\n";
        cout << setw(37) << "" << "\t[4] Update User.\n";
        cout << setw(37) << "" << "\t[5] Find User.\n";
        cout << setw(37) << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << "" << "===========================================\n";

        PerformManageUsersOption((enManageUsersMenuOptions)_ReadManageUsersMenuOption());
	}

};

