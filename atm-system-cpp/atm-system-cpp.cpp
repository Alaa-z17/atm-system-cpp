#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

// =====================
// Enums
// =====================

enum enMainMenuOptions
{
    eQuickWithdraw = 1,
    eNormalWithdraw = 2,
    eDeposit = 3,
    eCheckBalance = 4,
    eExit = 5
};

// =====================
// Structs
// =====================

struct stClient
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

// =====================
// Global Variables
// =====================

const string ClientsFileName = "Clients.txt";
stClient CurrentClient;
 
// =====================
// Forward Declarations
// =====================

void ShowMainMenu();
void Login();
void ShowQuickWithdrawScreen();
void ShowNormalWithdrawScreen();
void ShowDepositScreen();
vector<stClient> SaveClientsToFile(string FileName,
    vector<stClient> vClients);

// =====================
// String Utility
// =====================

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    string::size_type pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
            vString.push_back(sWord);
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
        vString.push_back(S1);

    return vString;
}

// =====================
// Convert Functions
// =====================

stClient ConvertLineToRecord(string Line,
    string Separator = "#//#")
{
    stClient Client;
    vector<string> vData = SplitString(Line, Separator);

    if (vData.size() < 5)
    {
        Client.AccountNumber = vData.size() > 0 ? vData[0] : "";
        Client.PinCode = vData.size() > 1 ? vData[1] : "";
        Client.Name = vData.size() > 2 ? vData[2] : "";
        Client.Phone = vData.size() > 3 ? vData[3] : "";
        Client.AccountBalance = 0;
        return Client;
    }

    Client.AccountNumber = vData[0];
    Client.PinCode = vData[1];
    Client.Name = vData[2];
    Client.Phone = vData[3];

    try
    {
        Client.AccountBalance = stod(vData[4]);
    }
    catch (const exception&)
    {
        Client.AccountBalance = 0;
    }

    return Client;
}

string ConvertRecordToLine(stClient Client,
    string Separator = "#//#")
{
    string Line = "";
    Line += Client.AccountNumber + Separator;
    Line += Client.PinCode + Separator;
    Line += Client.Name + Separator;
    Line += Client.Phone + Separator;
    Line += to_string(Client.AccountBalance);
    return Line;
}

// =====================
// File Functions
// =====================

vector<stClient> LoadClientsFromFile(string FileName)
{
    vector<stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            if (Line != "")
                vClients.push_back(ConvertLineToRecord(Line));
        }
        MyFile.close();
    }
    return vClients;
}

vector<stClient> SaveClientsToFile(string FileName,
    vector<stClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (stClient& C : vClients)
        {
            if (!C.MarkForDelete)
                MyFile << ConvertRecordToLine(C) << endl;
        }
        MyFile.close();
    }
    return vClients;
}
// =====================
// Authentication
// =====================

bool FindClientByAccountAndPin(string AccountNumber,
    string PinCode, stClient& Client)
{
    vector<stClient> vClients = LoadClientsFromFile(ClientsFileName);

    if (vClients.empty())
    {
        stClient InitialClient;
        InitialClient.AccountNumber = "101";
        InitialClient.PinCode = "1234";
        InitialClient.Name = "Admin Client";
        InitialClient.Phone = "0000000";
        InitialClient.AccountBalance = 5000;
        InitialClient.MarkForDelete = false;
        vClients.push_back(InitialClient);
        SaveClientsToFile(ClientsFileName, vClients);
        vClients = LoadClientsFromFile(ClientsFileName);
    }

    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber &&
            C.PinCode == PinCode)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool LoadClientInfo(string AccountNumber, string PinCode)
{
    return FindClientByAccountAndPin(AccountNumber,
        PinCode, CurrentClient);
}

void Login()
{
    bool LoginFailed = false;
    string AccountNumber, PinCode;

    do
    {
        system("cls");
        cout << "\n---------------------------------\n";
        cout << "\t    ATM Login Screen\n";
        cout << "---------------------------------\n";

        if (LoginFailed)
            cout << "Invalid Account Number or Pin Code!\n\n";

        cout << "Enter Account Number: ";
        cin >> AccountNumber;

        cout << "Enter Pin Code: ";
        cin >> PinCode;

        LoginFailed = !LoadClientInfo(AccountNumber, PinCode);

    } while (LoginFailed);

    ShowMainMenu();
}
// =====================
// Transaction Functions
// =====================

bool DepositToClient(string AccountNumber, double Amount,
    vector<stClient>& vClients)
{
    char Answer = 'N';
    cout << "\nAre you sure you want to perform this transaction? Y/N? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        for (stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveClientsToFile(ClientsFileName, vClients);
                cout << "\nDone! New Balance: " << C.AccountBalance << "\n";
                return true;
            }
        }
    }
    return false;
}

double ReadDepositAmount()
{
    double Amount = 0;
    do
    {
        cout << "\nEnter Deposit Amount (positive): ";
        cin >> Amount;
    } while (Amount <= 0);
    return Amount;
}

int ReadWithdrawAmount()
{
    int Amount = 0;
    do
    {
        cout << "\nEnter Withdraw Amount (multiple of 5): ";
        cin >> Amount;
    } while (Amount % 5 != 0);
    return Amount;
}

void PerformDepositOption()
{
    double DepositAmount = ReadDepositAmount();
    vector<stClient> vClients = LoadClientsFromFile(ClientsFileName);
    DepositToClient(CurrentClient.AccountNumber,
        DepositAmount, vClients);
    CurrentClient.AccountBalance += DepositAmount;
}

void PerformNormalWithdrawOption()
{
    int WithdrawAmount = ReadWithdrawAmount();

    if (WithdrawAmount > CurrentClient.AccountBalance)
    {
        cout << "\nAmount exceeds your balance!\n";
        cout << "Press any key to continue...";
        system("pause>0");
        ShowNormalWithdrawScreen();
        return;
    }

    vector<stClient> vClients = LoadClientsFromFile(ClientsFileName);
    DepositToClient(CurrentClient.AccountNumber,
        WithdrawAmount * -1, vClients);
    CurrentClient.AccountBalance -= WithdrawAmount;
}

short GetQuickWithdrawAmount(short Option)
{
    switch (Option)
    {
    case 1: return 20;
    case 2: return 50;
    case 3: return 100;
    case 4: return 200;
    case 5: return 400;
    case 6: return 600;
    case 7: return 800;
    case 8: return 1000;
    default: return 0;
    }
}

short ReadQuickWithdrawOption()
{
    short Choice = 0;
    do
    {
        cout << "\nChoose [1-9]: ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 9);
    return Choice;
}

void PerformQuickWithdrawOption(short Option)
{
    if (Option == 9)
        return;

    short WithdrawAmount = GetQuickWithdrawAmount(Option);

    if (WithdrawAmount > CurrentClient.AccountBalance)
    {
        cout << "\nAmount exceeds your balance!\n";
        cout << "Press any key to continue...";
        system("pause>0");
        ShowQuickWithdrawScreen();
        return;
    }

    vector<stClient> vClients = LoadClientsFromFile(ClientsFileName);
    DepositToClient(CurrentClient.AccountNumber,
        WithdrawAmount * -1, vClients);
    CurrentClient.AccountBalance -= WithdrawAmount;
}
// =====================
// Quick Withdraw Screen
// =====================

void ShowQuickWithdrawScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tQuick Withdraw\n";
    cout << "===========================================\n";
    cout << "\t[1]  20\t\t[2]  50\n";
    cout << "\t[3]  100\t[4]  200\n";
    cout << "\t[5]  400\t[6]  600\n";
    cout << "\t[7]  800\t[8]  1000\n";
    cout << "\t[9]  Exit\n";
    cout << "===========================================\n";
    cout << "\tYour Balance: $" << CurrentClient.AccountBalance << "\n";
    cout << "===========================================\n";

    PerformQuickWithdrawOption(ReadQuickWithdrawOption());
}
// =====================
// Normal Withdraw Screen
// =====================

void ShowNormalWithdrawScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tNormal Withdraw\n";
    cout << "===========================================\n";
    cout << "\tYour Balance: $" << CurrentClient.AccountBalance << "\n";
    cout << "===========================================\n";

    PerformNormalWithdrawOption();
}

// =====================
// Deposit Screen
// =====================

void ShowDepositScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tDeposit Screen\n";
    cout << "===========================================\n";
    cout << "\tYour Balance: $" << CurrentClient.AccountBalance << "\n";
    cout << "===========================================\n";

    PerformDepositOption();
}

// =====================
// Check Balance Screen
// =====================

void ShowCheckBalanceScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tCheck Balance\n";
    cout << "===========================================\n";
    cout << "\tAccount Number : " << CurrentClient.AccountNumber << "\n";
    cout << "\tName           : " << CurrentClient.Name << "\n";
    cout << "\tBalance        : $" << CurrentClient.AccountBalance << "\n";
    cout << "===========================================\n";
}
int main()
{
    return 0;
}