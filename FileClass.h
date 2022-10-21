#pragma once
#include <string>
#include "User.h"
#include <vector>
class FileClass {
public:
	static std::string getValue(std::string line);
	static void DeleteLine(int start, int count, std::string fileName);
	static int getAutoInc();
	static void updateAutoInc();

public:
	static bool userExist(std::string username, std::string password);
	static bool userNameExist(std::string username);
	static User getUserByID(int Id);
	static int FindLine(std::string line, std::string fileName);
	static void DeleteUser(int ID);
	static std::string GetLine(int count, std::string fileName);
	static void setCurrentUser(int ID);
	static int getCurrentUser();
	static std::vector<Transaction> getTransactions(int ID);
};