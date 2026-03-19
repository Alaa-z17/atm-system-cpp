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

int main()
{
    return 0;
}