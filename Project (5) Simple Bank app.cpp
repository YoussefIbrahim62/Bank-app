
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

string FileNamePath;

#pragma endregion


#pragma region MainFunctions


void MainMenuScreen()
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


enMenuOptions AskUserForOption()
{
	int Option = ReadNumberInRange("What do you want to do? Choose an option [1 to 6]? ", 1, 6);

	return (enMenuOptions) Option;
}

void ShowMainMenuScreen()
{
	MainMenuScreen();
	AskUserForOption();
}



#pragma endregion


int main()
{
	cout << "Hey";

	ShowMainMenuScreen();
}
 