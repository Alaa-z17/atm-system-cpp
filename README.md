# 🏧 ATM System — C++

A console-based ATM System built in **C++** demonstrating
core concepts of **Functional & Procedural Programming**.

---
## 🎬 Video Walkthrough

[![ATM System in C++](https://img.youtube.com/vi/-nfSH6qTxwU/0.jpg)](https://youtu.be/-nfSH6qTxwU)

> Click the image above to watch the full project walkthrough on YouTube.

## 🎯 Learning Objectives

- Structuring a program using functions (Procedural Programming)
- Global variables for session management
- File I/O for persistent client data
- Login and authentication system
- Exception handling in data parsing
- Forward declarations for circular dependencies
- Vectors for dynamic data management

---

## 🕹️ Features

- 🔐 Login with Account Number and Pin Code
- ⚡ Quick Withdraw (preset amounts)
- 💸 Normal Withdraw (multiples of 5)
- 💵 Deposit
- 💰 Check Balance
- 🚪 Logout

---

## 🏗️ Project Architecture
```
main()
 └── Login()
      └── ShowMainMenu()
           ├── ShowQuickWithdrawScreen()
           │    └── PerformQuickWithdrawOption()
           │         └── GetQuickWithdrawAmount()
           ├── ShowNormalWithdrawScreen()
           │    └── PerformNormalWithdrawOption()
           │         └── ReadWithdrawAmount()
           ├── ShowDepositScreen()
           │    └── PerformDepositOption()
           │         └── ReadDepositAmount()
           ├── ShowCheckBalanceScreen()
           └── Logout → Login()
```

---

## 💡 Key Concepts

| Concept | Where in Code |
|---|---|
| Enums | `enMainMenuOptions` |
| Structs | `stClient` |
| Global Variables | `CurrentClient`, `ClientsFileName` |
| File I/O | `LoadClientsFromFile()`, `SaveClientsToFile()` |
| Exception Handling | `ConvertLineToRecord()` |
| Forward Declarations | `ShowMainMenu()`, `Login()` |
| Login System | `FindClientByAccountAndPin()` |

---

## 🔧 Build & Run

**Open in Visual Studio**
```
double click: atm-system-cpp.slnx
Ctrl + F5
```

**Default Client Credentials**
```
Account Number: 101
Pin Code      : 1234
Balance       : $5000
```

---

## 📁 File Structure
```
atm-system-cpp/
├── .gitignore
├── README.md
├── LICENSE
├── atm-system-cpp.slnx
└── atm-system-cpp/
    ├── atm-system-cpp.cpp
    ├── atm-system-cpp.vcxproj
    └── atm-system-cpp.vcxproj.filters
```

> 📝 `Clients.txt` is auto-generated at first login.
> It is excluded from version control via `.gitignore`.

---

## 👤 Author

Built as a learning exercise in C++ Procedural Programming.

---

## 📄 License

MIT License