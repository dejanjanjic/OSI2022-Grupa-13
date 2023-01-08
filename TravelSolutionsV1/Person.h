#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "validate.h"

class Person
{
protected:
	std::string name;
	std::string surname;
	std::string username;
	std::string password;
	//std::string user_type;

public:

	Person() { this->name = ""; this->surname = ""; this->username = ""; this->password = "";}
	Person(std::string name, std::string surname, std::string username, std::string password) 
		: name(name), surname(surname), username(username), password(password){}
	//virtual void set_user_type() = 0;
	//virtual std::string get_user_type() = 0;
	virtual std::string get_name() { return this->name; }
	virtual std::string get_surname() { return this->surname; }
	virtual std::string get_username() { return this->username; }
	virtual std::string get_password() { return this->password; }

};