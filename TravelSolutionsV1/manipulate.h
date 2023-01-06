#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "validate.h"

//BIBLIOTEKA ZA MANIPULACIJU OBJEKTIMA


//VRACA LINIJU U KOJOJ SE NALAZE INFORMACIJE O KORISNIKU USERNAME
int manipulate_at(std::string username)
{
	std::fstream file("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");

	std::string out;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			file >> out;
			if (out == username)
			{
				return i;
			}
		}
	}
	return 0;
}

//NA OSNOVU FUNKCIJE DELETE_AT BRISE DATU LINIJU
bool delete_line(std::string username)
{
	int n = manipulate_at(username);

	std::ifstream is("Users.txt");


	std::ofstream ofs;
	ofs.open("temp.txt", std::ofstream::out);


	char c;
	int line_no = 0;
	while (is.get(c))
	{
		if (c == '\n')
			line_no++;

		if (line_no != n)
			ofs << c;
	}

	ofs.close();

	is.close();

	remove("Users.txt");

	rename("temp.txt", "Users.txt");

	return 1;
}

//SUSPENDUJE IZABRANOG KORISNIKA
bool suspend_at(std::string username)
{
	int check = 0;

	std::fstream file("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");

	std::string out;
	int line = manipulate_at(username);
	std::ofstream ofs;
	ofs.open("temp.txt", std::ofstream::out);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			file >> out;
	
			if ((i == line) && (j == 5) && (out=="false"))
			{
				
					ofs << "true";
					check++;
				
			}
			else
			{
				ofs << out <<" ";
			}
			
		}
		ofs << "\n";
	}

	ofs.close();

	file.close();

	remove("Users.txt");

	rename("temp.txt", "Users.txt");

	if (check != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

//AKTIVIRA SUSPEDNOVANI NALOG
bool activate_at(std::string username)
{

	int check = 0;

	std::fstream file("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");

	std::string out;
	int line = manipulate_at(username);
	std::ofstream ofs;
	ofs.open("temp.txt", std::ofstream::out);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			file >> out;
			if ((i== line) && (j == 5))
			{
					ofs << "false";
					check++;		
			}
			else
			{
				ofs << out << " ";
			}

		}
		ofs << std::endl;
	}

	ofs.close();

	file.close();

	remove("Users.txt");

	rename("temp.txt", "Users.txt");

	if (check != 0) 
	{
		return true; 
	}
	else
	{
		return false;
	}
}