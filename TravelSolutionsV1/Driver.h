#pragma once
#include "Person.h"

class Driver : public Person
{
private:
	bool suspended;
	bool isBusy;
public:
	//using Person::Person;
	Driver(std::string username)
	{
		std::ifstream file("Users.txt");
		int n = num_of_lines("Users.txt");

		std::string firstName, lastName, userName, pass, type, isSuspended, busy;

		for (int i = 0; i < n; i++)
		{
			file >> firstName;
			file >> lastName;
			file >> userName;
			file >> pass;
			file >> type;
			file >> isSuspended;
			file >> busy;
			if (username == userName)
			{
				this->name = firstName;
				this->surname = lastName;
				this->username = userName;
				this->password = pass;
				if (isSuspended == "true") this->suspended = true;
				else this->suspended = false;
				if (busy == "true") this->suspended = true;
				else this->suspended = false;
			}
		}
	}

	void menu()
	{
		std::cout << "OK";
	}
	/*void set_user_type() override
	{
		this->user_type = "3";
	}
	virtual std::string get_user_type() override
	{
		if (this->user_type == "0")
		{
			std::cout << "User type still not defined";
		}
		return this->user_type;
	}*/

};