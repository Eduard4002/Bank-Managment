// BankManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

#include "SceneManager.h"
#include "FileClass.h"
#include "BankManagment.h"
int main()
{
    if (FileClass::getCurrentUser() != -1) {
        SceneManager::MainMenu();
    }
    else {
        int choice = 0;
        std::cout << "Do you want to [1]LOGIN or [2]SIGNUP: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            if (SceneManager::Login()) {
                //Succesfull login, give acces to account
                SceneManager::ResetConsole();
                SceneManager::MainMenu();
            }
            else {
                SceneManager::ResetConsole();
                main();
            }
            break;
        case 2:
            if (SceneManager::SignUp()) {
                //Succesfull sign up, give access to account
                SceneManager::ResetConsole();
                SceneManager::MainMenu();
            }
            else {
                SceneManager::ResetConsole();
                main();
            }
            break;
        }
    }
    
}

