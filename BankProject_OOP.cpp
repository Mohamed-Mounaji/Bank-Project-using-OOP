#include <iostream>
#include <vector>
#include "clsLoginScreen.h"
#include <string>

using namespace std;


int main()
{
    bool LoginSucceeded = true;
    
    while (LoginSucceeded)
    {
        LoginSucceeded = clsLoginScreen::ShowLoginScreen();
    }


    system("pause>0");
    return 0;  
}
