
#include "MySideFunctionsLib.h"

using namespace AllLibs;


#pragma region enums, structs and Global variables

enum enMenuOptions
{
	ShowClientList = 1,
	AddNewClient = 2,
	DeleteClient = 3,
	UpdateClientInfo = 4,
	FindClient = 5,
	Exit = 6
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



#pragma region Main Menu Functions


void ShowMainMenuScreen()
{
	system("cls");
	cout << "========================================================";
	cout << "\n\t\t  Main Menu Screen \n";
	cout << "========================================================\n";

	cout << "\t\t[1] Show clients list \n";
	cout << "\t\t[2] Add a new client \n";
	cout << "\t\t[3] Delete clients \n";
	cout << "\t\t[4] Update clients info \n";
	cout << "\t\t[5] Search for a client \n";
	cout << "\t\t[6] Exit \n";

	cout << "========================================================\n";
}


#pragma endregion




#pragma region Secondary Functions


enMenuOptions AskUserForOption()
{
	int Option = ReadNumberInRange("What do you want to do? Choose an option [1 to 6]? ", 1, 6);

	return (enMenuOptions)Option;
}


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

	cout << ("\n\nPress any key to go back to the Main Menu...\t");
	system("pause > 0");

}

#pragma endregion




#pragma endregion


int main()
{
	cout << "Hey";

	ShowClientsList();
}
 