
#include "MySideFunctionsLib.h"

using namespace AllLibs;


#pragma region enums, structs and Global variables

enum enMenuOptions
{
	enShowClientList = 1,
	enAddNewClient = 2,
	enDeleteClient = 3,
	enUpdateClientInfo = 4,
	enFindClient = 5,
	enExit = 6
};

struct stClient
{
	string AccountNumber;
	string FullName;
	string PhoneNumber;
	string PinCode;
	double Balance;
};

vector <stClient> vClients;

string FileNamePath = "ClientsDataBaseFile.txt";

#pragma endregion


#pragma region Program Functions







#pragma region Secondary Functions


void ShowMainMenuScreen();


stClient ConvertRecordToClient(string Record)
{
	stClient Client;
	vector <string> vWords = SplitString(Record, "#//#");

	Client.AccountNumber = vWords[0];
	Client.PinCode = vWords[1];
	Client.FullName = vWords[2];
	Client.PhoneNumber = vWords[3];
	Client.Balance = stod(vWords[4]);

	return Client;
}


string ConvertClientToRecord(stClient NewClient, string Seprator = "#//#")
{
	string Record = "";

	Record += NewClient.AccountNumber;
	Record += Seprator;

	Record += NewClient.PinCode;
	Record += Seprator;

	Record += NewClient.FullName;
	Record += Seprator;

	Record += NewClient.PhoneNumber;
	Record += Seprator;


	Record += to_string(NewClient.Balance);

	return Record;
}


void AddClientsDataFromFileToClientsVector()
{

	vector <string> vRecords;
	stClient Client;

	LoadDataFromFile(FileNamePath, vRecords);

	for (int i = 0; i < vRecords.size(); i++)
	{
		Client = ConvertRecordToClient(vRecords[i]);
		::vClients.push_back(Client);
	}

}


void PressAnyKeyToGetBackToMainMenu()
{
	cout << ("\n\nPress any key to go back to the Main Menu...\t");
	system("pause > 0");

	ShowMainMenuScreen();
}


void ScreenHeader(string Header)
{
	system("cls");

	cout << "\n=====================================\n";
	cout << "\t  " << Header;
	cout << "\n=====================================\n\n";
}


void PrintClientData(stClient NewClient)
{
	cout << "\n-----------------------------------\n";
	cout << "Account number: ";
	cout << NewClient.AccountNumber << "\n";

	cout << "Pin code      : ";
	cout << NewClient.PinCode << "\n";

	cout << "Full Name     : ";
	cout << NewClient.FullName << "\n";

	cout << "Phone number  : ";
	cout << NewClient.PhoneNumber << "\n";

	cout << "Balance       : ";
	cout << NewClient.Balance << "\n";
	cout << "-----------------------------------\n\n";
}


bool IsClientExisted(string accountNumber, int& pos)
{
	AddClientsDataFromFileToClientsVector();

	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].AccountNumber == accountNumber)
		{
			pos = i;
			return true;
		}

	}

	pos = -1;
	return false;
}



#pragma endregion



#pragma region Show All clients functions



void PrintClientTableHeader()
{
	cout << "--------------------------------------------------------------------------------------------------------\n\n";

	cout << " | " << left << setw(15) << "Account Number"
		<< " | " << left << setw(10) << "Pin Code"
		<< " | " << left << setw(30) << "Client Name"
		<< " | " << left << setw(15) << "Phone Number"
		<< " | " << left << setw(10) << "Balance"
		<< " \n\n";

	cout << "--------------------------------------------------------------------------------------------------------\n";
}


void PrintAllClientsRecords()
{
	for (int i = 0; i < vClients.size(); i++)
	{

		cout << " | " << left << setw(15) << vClients[i].AccountNumber
			<< " | " << left << setw(10) << vClients[i].PinCode
			<< " | " << left << setw(30) << vClients[i].FullName
			<< " | " << left << setw(15) << vClients[i].PhoneNumber
			<< " | " << left << setw(10) << vClients[i].Balance
			<< "\n";
	}

	cout << "\n-----------------------------------------------------------------------------------------------------------\n\n";
}


void ShowClientsList()
{
	system("cls");
	AddClientsDataFromFileToClientsVector();

	PrintClientTableHeader();


	PrintAllClientsRecords();

	PressAnyKeyToGetBackToMainMenu();

}

#pragma endregion



#pragma region Add a new client functions

stClient FillNewClientInfo()
{
	stClient NewClient;

	NewClient.AccountNumber = ReadString("Enter the account number");

	NewClient.PinCode = ReadString("Enter the pin code");

	NewClient.FullName = ReadString("Enter the full name");

	NewClient.PhoneNumber = ReadString("Enter the phone number");

	NewClient.Balance = validateInputIsNumberfloat("Enter the balance amount");

	return NewClient;
}


void AddNewClient()
{
	ScreenHeader("New Client Form");

	stClient NewClient;
	string NewClientRecord;

	NewClient = FillNewClientInfo();

	NewClientRecord = ConvertClientToRecord(NewClient);

	if (ReadAnswerYesOrNO("\nAre you sure you want to add it [Y] [N] ? "))
	{
		AddSingleRecordToFile(FileNamePath, NewClientRecord);

		cout << "\nA new client has been added successfully! \n";


		if (ReadAnswerYesOrNO("\nDo you want to add another client [Y] [N] ? "))
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			AddNewClient();
		}
		else
			PressAnyKeyToGetBackToMainMenu();
	}
	else
		PressAnyKeyToGetBackToMainMenu();


}

#pragma endregion



#pragma region Exit function

void ShowExitScreen()
{
	system("cls");

	cout << "\n=============================\n";
	cout << "   Program has ended!\n";
	cout << "        Thank you\n";
	cout << "=============================\n";

}

#pragma endregion





void ShowFindClientByAccountNumberScreen()
{
	string AccountNumber;
	int Pos = -99;

	ScreenHeader("Search for a client");


	AccountNumber = ReadString("Enter the client's account number");

	if (IsClientExisted(AccountNumber,Pos))
		PrintClientData(vClients[Pos]);
	else
		cout << "\nUnfortunately, this account number does not exist in our system!\n\n";

	if (ReadAnswerYesOrNO("Do you want to search for another client [Y] [N] ?"))
		ShowFindClientByAccountNumberScreen();
	else
		PressAnyKeyToGetBackToMainMenu();

}


#pragma region Main Menu Functions

enMenuOptions ReadUserOption()
{
	int Option = ReadNumberInRange("What do you want to do? Choose an option [1 to 6]? ", 1, 6);

	return (enMenuOptions)Option;
}


void ApplyUserOption(enMenuOptions Option)
{
	switch (Option)
	{
	case enMenuOptions::enAddNewClient:
		AddNewClient();
		break;
	case enMenuOptions::enShowClientList:
		ShowClientsList();
		break;
	case enMenuOptions::enExit:
		ShowExitScreen();
		break;
	case enMenuOptions::enFindClient:
		ShowFindClientByAccountNumberScreen();
		break;

	}

}


void ShowMainMenuScreen()
{
	system("cls");
	cout << "========================================================";
	cout << "\n\t\t  Main Menu Screen \n";
	cout << "========================================================\n";

	cout << "\t\t[1] Show all clients  \n";
	cout << "\t\t[2] Add a new client \n";
	cout << "\t\t[3] Delete clients \n";
	cout << "\t\t[4] Update clients info \n";
	cout << "\t\t[5] Search for a client \n";
	cout << "\t\t[6] Exit \n";

	cout << "========================================================\n";

	ApplyUserOption(ReadUserOption());
}


#pragma endregion



#pragma endregion


int main()
{
	cout << "Hey";
	ShowMainMenuScreen();
}
 