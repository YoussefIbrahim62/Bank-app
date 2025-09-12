
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


void PressAnyKeyToGetBackToMainMenu()
{
	cout << ("\n\nPress any key to go back to the Main Menu...\t");
	system("pause > 0");

	ShowMainMenuScreen();
}


#pragma endregion



#pragma region Show All clients functions


void AddClientListToVector()
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
	AddClientListToVector();

	PrintClientTableHeader();


	PrintAllClientsRecords();

	PressAnyKeyToGetBackToMainMenu();

}

#pragma endregion



#pragma region Add a new client functions

stClient FillNewClientInfo()
{
	stClient NewClient;

	cout << "\n================================\n";
	cout << "\tNew Client Form";
	cout << "\n================================\n\n";

	NewClient.AccountNumber = ReadString("Enter the account number");

	NewClient.PinCode = ReadString("Enter the pin code");

	NewClient.FullName = ReadString("Enter the full name");

	NewClient.PhoneNumber = ReadString("Enter the phone number");

	NewClient.Balance = validateInputIsNumberfloat("Enter the balance amount");

	return NewClient;
}


void AddNewClient()
{
	system("cls");

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
 