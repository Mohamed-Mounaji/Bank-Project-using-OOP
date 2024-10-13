#pragma once
#include <iostream>
using namespace std;

class InterfaceCommunication
{
public:

	virtual void SendEmail(string Subject, string Body) = 0;
	virtual void SendFax(string Subject, string Body) = 0;
	virtual void SendSMS(string Subject, string Body) = 0;

};

