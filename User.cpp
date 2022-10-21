#include "User.h"
#include "FileClass.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
User::User(int ID, std::string fname, std::string lname, std::string userN, std::string passw, int balance) {
	this->ID = ID;
	this->fName = fname;
	this->lName = lname;
	this->userN = userN;
	this->passw = passw;
	this->balance = balance;
}
bool User::WithDraw(int amount) {
	if (balance - amount < 0) {
		return false;
	}
	balance -= amount;

	SaveInfo();

	return true;
}
bool User::Deposit(int amount) {
	balance += amount;

	SaveInfo();
	return true;
}
void User::SaveInfo() {
	FileClass::DeleteUser(ID);
	std::hash<std::string> hasher;
	std::ofstream file;
	file.open("users.txt", std::ios::app);
	//Begin writing to stream
	file << "{ \n"
		<< "ID: " << ID << "\n"
		<< "FIRSTNAME: " << fName << "\n"
		<< "LASTNAME: " << lName << "\n"
		<< "USERNAME: " << userN << "\n"
		<< "PASSWORD: " << hasher(passw) << "\n"
		<< "BALANCE: " << balance << "\n"
		<< "} \n";
	file.close();
}
void User::SendTo(std::string to, unsigned int amount) {
	if (WithDraw(amount) == false) {
		std::cout << "You dont have enough money to send that amount" << std::endl;
		return;
	}
	if (!FileClass::userNameExist(to)) {
		std::cout << "Invalid username" << std::endl;
	}
	std::string lineToSearch = "USERNAME: " + to;
	int count = FileClass::FindLine(lineToSearch, "users.txt");
	User other = FileClass::getUserByID(std::stoi(FileClass::getValue(FileClass::GetLine(count - 3, "users.txt"))));
	if (other.Deposit(amount)) {
		SaveTransaction(Transaction(ID, other.ID, amount));
	}
}
void User::SaveTransaction(Transaction transaction) {
	std::ofstream file;
	file.open("transactions.txt", std::ios::app);
	//Begin writing to stream
	file << "{ \n"
		<< "FROM: " << transaction.fromID<<"\n"
		<< "TO: " << transaction.toID << "\n"
		<< "AMOUNT: " << transaction.amount << "\n"
		<< "} \n";
	file.close();
}