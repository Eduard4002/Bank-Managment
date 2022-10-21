#include "SceneManager.h"
#include "FileClass.h"
#include <iostream>
#include <Windows.h>
#include "BankManagment.h"
#include <vector>

#define Print(x) (std::cout << x << "\n")
void SceneManager::ResetConsole() {
    system("CLS");
}
bool SceneManager::Login() {
    SceneManager::ResetConsole();
    std::string userN, passw;
    Print("Please enter username: ");
    std::cin >> userN;
    Print("Please enter password: ");
    std::cin >> passw;
    //Successfull login
    if (FileClass::userExist(userN, passw)) {
        std::string lineToFind = "USERNAME: " + userN;
        int pos = FileClass::FindLine(lineToFind, "users.txt");
        int ID = std::stoi(FileClass::getValue(FileClass::GetLine(pos - 3, "users.txt")));
        FileClass::setCurrentUser(ID);
        return true;
    }
    else {
        char choice = 'N';
        Print("We haven't found a user :( , would you like to try again? [Y/N]: ");
        std::cin >> choice;
        if (choice == 'Y') {
            Login();
        }
        else {
            return false;
        }
    }
    return false;
}
bool SceneManager::SignUp() {
    SceneManager::ResetConsole();

    std::string output[User::variableAmount - 2];
    Print("First Name: ");
    std::cin >> output[0];
    Print("Last Name:");
    std::cin >> output[1];
    Print("Username: ");
    std::cin >> output[2];
    Print("Password: ");
    std::cin >> output[3];
    if (FileClass::userNameExist(output[2])) {
        char choice = 'N';
        Print("That username already exist, would you like to try again?[Y/N]");
        std::cin >> choice;
        if (choice == 'Y') {
            SignUp();
        }
        else {
            return false;
        }
    }
    else {
        int autoID = FileClass::getAutoInc();
        User input = User(autoID, output[0], output[1], output[2], output[3], 0);
        input.SaveInfo();
        FileClass::updateAutoInc();

        std::string lineToFind = "USERNAME: " + output[2];
        int pos = FileClass::FindLine(lineToFind, "users.txt");
        int currID = std::stoi(FileClass::getValue(FileClass::GetLine(pos - 3, "users.txt")));
        FileClass::setCurrentUser(currID);
    }
    
}
void SceneManager::MainMenu() {
    User currentUser = FileClass::getUserByID(FileClass::getCurrentUser());
    std::vector<Transaction> transactions = FileClass::getTransactions(FileClass::getCurrentUser());
    unsigned int choice;
    std::string line;
    Print("WELCOME: " + currentUser.fName);
    std::cout << "BALANCE: " << currentUser.balance << "\n";
    Print("");
    Print("::    Withdraw[1]   ::");
    Print("::    Deposit[2]    ::");
    Print("::    Send To[3]    ::");
    Print("::  Transactions[4] ::");
    Print("::Account Details[5]::");
    Print("::   Log Out[6]     ::");
    Print("Please select an option:");
    std::cin >> choice;
    ResetConsole();
    switch (choice) {
    case 1:
        Print("Please enter amount: ");
        std::cin >> choice;
        if (!currentUser.WithDraw(choice)) {
            Print("You can not withdraw that much money!");
            std::cout << "Maximum is: " << std::dec << currentUser.balance << "\n";
        }
        else {
            Print("Money has been succesfully been drawn out");
            Sleep(1000);
            ResetConsole();
            MainMenu();
        }
        break;
    case 2:
        Print("Please enter amount: ");
        std::cin >> choice;
        if (currentUser.Deposit(choice)) {
            Print("Money has been deposited");
            Sleep(1000);
            ResetConsole();
            MainMenu();
        }
    case 3:
        ResetConsole();
        Print("Please enter username to send:");
        std::cin >> line;
        Print("Please enter amount: ");
        std::cin >> choice;
        currentUser.SendTo(line, choice);
        Sleep(1000);
        ResetConsole();
        MainMenu();
        break;
    case 4:
        ResetConsole();
        if (transactions.size() == 0) {
            Print("You have no transactions right now :(");
            Sleep(4000);
            ResetConsole();
            MainMenu();
        }
        for (int i = 0; i < transactions.size(); i++) {
            Print("-------------------");
            std::cout << "TO: " << transactions[i].toID << std::endl;;
            std::cout << "AMOUNT: " << transactions[i].amount << std::endl;;
            Print("-------------------");
        }
        Print("GO BACK [1]");
        std::cin >> choice;

        ResetConsole();
        MainMenu();
        break;
    case 5:
        Print("::INFO::");
        Print("First Name: " + currentUser.fName);
        Print("Last Name: " + currentUser.lName);
        Print("Username: " + currentUser.userN);
        Print("Password: " + currentUser.passw);
        std::cout << "BALANCE: " << currentUser.balance << "\n";
        Print("GO BACK[1]");
        std::cin >> choice;

        ResetConsole();
        MainMenu();
        break;
    case 6:
        FileClass::setCurrentUser(-1);
        Print("LOGGING OFF...");
        Sleep(1000);
        ResetConsole();
        main();
        break;
    default:
        ResetConsole();
        MainMenu();
    }

}
