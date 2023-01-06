#pragma once
#include <iostream>
#include <string>
#include <fstream>

//BIBLIOTEKA SA VALIDACIJAMA POTREBNIM ZA LOGIN I REGISTER

//PROVJERAVA BROJ LINIJA U FAJLU "USERS.TXT"
int num_of_lines(std::string file)
{
	int n = 0;
	std::string line;
	std::ifstream myfile(file);

	while (std::getline(myfile, line)) { ++n; }

	return n;
}

//PROVJERAVA VALIDNOST IMENA I PREZIMENA
bool check_name_or_surname(std::string forcheck)
{
	if ((islower(forcheck[0])) || (forcheck.size() > 15) || forcheck.size() < 3) { return 0; }
	else { return 1; }
}

//PROVJERAVA VALIDNOST KORISNICKOG IMENA
bool check_username(std::string forcheck)
{
	std::fstream file("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");

	std::string out;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			file >> out;
			if ((j == 2) && (out == forcheck))
			{
				return 0;
			}
		}
	}
	if (forcheck.size() < 4) { return 0; }
	return 1;

}

//PROVJERAVA VALIDNOST LOZINKE
bool check_password(std::string forcheck)
{

	for (int i = 0; i < forcheck.size(); i++)
	{
		if ((isdigit(forcheck[i])) && (forcheck.size() > 7))
		{
			return 1;
		}
	}
	return 0;
}

//VRACA TIP KORISNIKA( DRIVER, ADMIN, USER)
std::string getUserType(std::string username)
{
	std::fstream file("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");

	std::string out;

	for (int i = 0; i < n; i++)
	{
		int check = 0;
		for (int j = 0; j < 6; j++)
		{
			file >> out;
			if ((j == 2) && (out == username))
			{
				check++;
			}
			if ((j == 4) && (check == 1))
			{
				return out;
			}
		}
	}

	return "0";
}
