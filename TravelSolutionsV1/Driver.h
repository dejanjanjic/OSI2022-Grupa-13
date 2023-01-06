#pragma once
#include "Person.h"

class Driver : public Person
{
public:
	using Person::Person;
	void set_user_type() override
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
	}

};