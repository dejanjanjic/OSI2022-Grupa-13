#pragma once
#include <iostream>
#include <string>

class Person
{
protected:
	std::string name;
	std::string surname;
	std::string username;
	std::string password;
	std::string user_type;
	bool suspended;

public:

	Person() { this->name = ""; this->surname = ""; this->username = ""; this->password = ""; this->user_type = ""; this->suspended = false; }
	Person(std::string name, std::string surname, std::string username, std::string password) 
		: name(name), surname(surname), username(username), password(password), user_type("0"),suspended(false) {}
	virtual void set_user_type() = 0;
	virtual std::string get_user_type() = 0;
	virtual std::string get_name() { return this->name; }
	virtual std::string get_surname() { return this->surname; }
	virtual std::string get_username() { return this->username; }
	virtual std::string get_password() { return this->password; }
	virtual bool get_suspended() { return this->suspended; }

};