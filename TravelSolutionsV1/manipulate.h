#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "validate.h"

//BIBLIOTEKA ZA MANIPULACIJU OBJEKTIMA


bool registration(std::string type)
{
	int counter;
	std::string name, surname, password, username;

	do
	{
		counter = 0;
		std::cout << "Unesite ime: " << std::endl;
		std::cin >> name;
		std::cout << "Unesite prezime: " << std::endl;
		std::cin >> surname;
		std::cout << "Unesite korisnicko ime: " << std::endl;
		std::cin >> username;
		std::cout << "Unesite lozinku: " << std::endl;
		std::cin >> password;

		system("cls");

		if (!check_name_or_surname(name)) { std::cout << "Ime nije u odgovarajucem formatu" << std::endl; }
		else { counter++; }
		if (!check_name_or_surname(surname)) { std::cout << "Prezime nije u odgovarajucem formatu" << std::endl; }
		else { counter++; }
		if (!check_password(password)) { std::cout << "Lozinka nije u odgovarajucem formatu" << std::endl; }
		else { counter++; }
		if (!check_username(username)) { std::cout << "Korisnicko ime vec postoji ili je prekratko" << std::endl; }
		else { counter++; }

		if (counter != 4) { std::cout << std::endl << "Probajte ponovo\n" << std::endl; }

	} while (counter != 4);

	//Upis u datoteku na osnovu tipa osobe. Svaka osoba se drugacuje upisuje u datoteku, u zavisnosti od podataka koji se trebaju cuvati.
	std::fstream file("Users.txt", std::ios::in | std::ios::out | std::ios::app);
	if (type == "1")
	{
		file << name << " " << surname << " " << username << " " << password << " " << type << " " << "false" << " " << "0.0" << "\n";

	}
	else if (type == "2")
	{
		file << name << " " << surname << " " << username << " " << password << " " << type << " 0 0\n";
	}
	else if (type == "3")
	{
		file << name << " " << surname << " " << username << " " << password << " " << type << " " << "false" << " " << "false" << "\n";
	}
	return 1;

}

//VRACA LINIJU U KOJOJ SE NALAZE INFORMACIJE O KORISNIKU USERNAME
int manipulate_at(std::string username)
{
	std::fstream file("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");

	std::string out;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 7; j++)
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

	std::fstream oldFile("Users.txt", std::ios::in);
	std::fstream newFile("TempName.txt", std::ios::out);
	int n = num_of_lines("Users.txt");

	std::string out;

	int line = manipulate_at(username);

	getline(oldFile, out);
	newFile << out << std::endl;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			oldFile >> out;
			if ((i == line) && (j == 5) && (out == "false"))
			{
				newFile << "true";
				check++;
			}
			else
				newFile << out;
			if (j != 6)
				newFile << " ";
		}
		newFile << std::endl;
	}
	oldFile.close();
	newFile.close();

	remove("Users.txt");

	rename("TempName.txt", "Users.txt");



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

	std::fstream oldFile("Users.txt", std::ios::in);
	std::fstream newFile("TempName.txt", std::ios::out);
	int n = num_of_lines("Users.txt");

	std::string out;

	int line = manipulate_at(username);

	getline(oldFile, out);
	newFile << out << std::endl;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			oldFile >> out;
			if ((i == line) && (j == 5) && (out == "true"))
			{
				newFile << "false";
				check++;
			}
			else
				newFile << out;
			if (j != 6)
				newFile << " ";
		}
		newFile << std::endl;
	}
	oldFile.close();
	newFile.close();

	remove("Users.txt");

	rename("TempName.txt", "Users.txt");



	if (check != 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}