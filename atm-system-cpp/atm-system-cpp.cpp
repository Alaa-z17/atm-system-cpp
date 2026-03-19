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

int main()
{
    return 0;
}