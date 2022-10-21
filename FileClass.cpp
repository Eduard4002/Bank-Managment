#include "FileClass.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
std::string FileClass::getValue(std::string line) {
    std::string value;
    size_t position = line.find(' ');
    //loop through the whole line from the position of empty space
    for (size_t i = position + 1;i < line.size(); i++) {
        //add to value
        value.append(1, line[i]);
    }
    return value;
}
int FileClass::FindLine(std::string _line, std::string fileName) {
    std::fstream file;
    file.open(fileName);
    std::string line = "";
    //keeping a count
    int count = 0;
    while (!file.eof()) {
        if (line == _line) {
            //once we find the line we return count
            return count;
        }
        std::getline(file, line);
        count++;
    }
    return -1;
}
std::string FileClass::GetLine(int count, std::string fileName) {
    std::ifstream file;
    file.open(fileName);
    std::string line = "";
    //keeps a count
    int currentCount = 1;
    while (!file.eof()) {
        std::getline(file, line);
        if (currentCount == count) {
            //once we are at the neccessery count, return the line we are on
            return line;
        }
        currentCount++;
    }
    return "";
}
void FileClass::DeleteLine(int start, int count, std::string fileName) {
    std::ifstream input;
    //open the input file
    input.open(fileName);
    
    //This will be our output file
    std::ofstream temp;
    temp.open("temp.txt");

    int currCount = 0;
    std::string line;
    while (!input.eof()) {
        if (!((currCount >= start) && (currCount <= (start + count)))) {
            if (line != "") {
                //write to temp file
                temp << line << "\n";
            }
           
        }
        currCount++;
        std::getline(input, line);
    }
    input.close();
    temp.close();

    remove(fileName.c_str());
    if (rename("temp.txt", fileName.c_str()) != 0)
        std::cout << "Error renaming file \n";
}
void FileClass::DeleteUser(int ID) {
    //find position with the ID
    std::string id = "ID: " + std::to_string(ID);
    int position = FindLine(id, "users.txt");
    if (position != -1) {
        //delete every line containing info about user
        DeleteLine(position - 1, User::variableAmount + 2, "users.txt");
    }
}
void FileClass::setCurrentUser(int ID) {
    //deleting second line
    FileClass::DeleteLine(2, 1, "data.txt");
    std::fstream file;
    file.open("data.txt", std::ios::app);
    //adding new value to second line
    file << "CURR_USER: " << ID << "\n";
    file.close();
}
int FileClass::getCurrentUser() {
    //returning value at line '2'
    std::string line = FileClass::GetLine(2, "data.txt");
    return std::stoi(getValue(line));

}
int FileClass::getAutoInc() {
    //returning value at line '1'
    std::string line = FileClass::GetLine(1, "data.txt");
    return line != "" ? std::stoi(getValue(line)) : -999;

}
void FileClass::updateAutoInc() {
    int current = getAutoInc();
    std::ofstream file;
    //deleting first line
    FileClass::DeleteLine(1,2, "data.txt");
    file.open("data.txt");
    //adding new value to first line
    file << "AUTO_INC: " << current + 1 << "\n";
    file.close();
}

bool FileClass::userExist(std::string username, std::string password) {
    std::fstream file;
    std::hash<std::string> hasher;
    file.open("users.txt");
    std::string line;
    //used to check if both are true
    bool userN = false; 
    bool passw = false;
    std::string userLine = "USERNAME: " + username;
    std::string passwLine = "PASSWORD: " + std::to_string(hasher(password));
    while (!file.eof()) {
        std::getline(file, line);
        //found user with same username
        if (line == userLine) {
            userN = true;
        }
        //found user with same password
        if (line == passwLine) {
            passw = true;
        }
        //return true or reset
        if (line == "}") {
            if (userN && passw) {
                return true;
            }
            else {
                userN = false;
                passw = false;
            }
            
        }
    }
    if (userN && passw) {
        return true;
    }
    else {
        return false;
    }
    return false;
    file.close();
}
bool FileClass::userNameExist(std::string username) {
    //if we find a username return true
    std::string lineToSearch = "USERNAME: " + username;
    if (FileClass::FindLine(lineToSearch, "users.txt") == -1) {
        return false;
    }
    return true;
}
User FileClass::getUserByID(int ID) {
    std::fstream file;
    file.open("users.txt");
    std::string lineToSearch = "ID: " + std::to_string(ID);
    std::string line = "";
    std::string outputArray[User::variableAmount];
    while (!file.eof()) {
        std::getline(file, line);
        if (line == lineToSearch) {
            //Found a user with specific ID
            break;
        }
    }
    //add all info to output array 
    std::string current = line;
    int count = 0;
    while (current.find("}") == std::string::npos) {
        if (count == 0) {
            outputArray[0] = getValue(current);
        }else if (count == 1) {
            outputArray[1] = getValue(current);
        }else if (count == 2) {
            outputArray[2] = getValue(current);
        }else if (count == 3) {
            outputArray[3] = getValue(current);
        }else if (count == 4) {
            outputArray[4] = getValue(current);
        }else if (count == 5) {
            outputArray[5] = getValue(current);
        }
        std::getline(file, current);
        count++;
    }
    file.close();
    //create new user with output array info
    User user = User(std::stoi(outputArray[0]), outputArray[1], outputArray[2], outputArray[3], outputArray[4], std::stoi(outputArray[5]));
    return user;
}
std::vector<Transaction> FileClass::getTransactions(int ID) {
    std::vector<Transaction> transactions;
    std::ifstream file;
    file.open("transactions.txt");
    std::string currentLine;
    std::string lineToFind = "FROM: " + std::to_string(ID);
    unsigned int count = 1;
    while (!file.eof()) {
        if (currentLine == lineToFind) {
            //create new transaction
            Transaction transaction = Transaction(ID, std::stoi(FileClass::getValue(FileClass::GetLine(count, "transactions.txt"))),
                                                      std::stoi(FileClass::getValue(FileClass::GetLine(count + 1, "transactions.txt"))));
            //add to vector array
            transactions.push_back(transaction);
        }
        std::getline(file, currentLine);
        count++;

    }
    return transactions;
}