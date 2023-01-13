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
		for (int j = 0; j < 7; j++)
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

//PROVJERA VALIDNOSTI ID-A TURE
bool check_id_tour(std::string forcheck)
{
	for (int i = 0; i < forcheck.size(); i++)
	{
		if (((isdigit(forcheck[i])) || (isalpha(forcheck[i]))) && (forcheck.size() > 4))
		{
			return 1;
		}
		return 0;
	}
}

//PROVJERA VALIDNOSTI ID-A BUSA
bool check_id_bus(std::string forcheck)
{
	for (int i = 0; i < forcheck.size(); i++)
	{
		if ((isdigit(forcheck[i])) && (forcheck.size() < 3))
		{
			return 1;
		}
		return 0;
	}
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
		for (int j = 0; j < 7; j++)
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

bool userExist(std::string username, std::string password)
{
	std::fstream file("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");

	std::string out;

	for (int i = 0; i < n; i++)
	{
		int check = 0;
		for (int j = 0; j < 7; j++)
		{
			file >> out;
			if ((j == 2) && (out == username))
			{
				check++;
			}
			if ((j == 3) && (out == password))
			{
				check++;
			}
			if (check == 2) return true;
		}
	}

	return false;
}

//PROVJERA DA LI TURA POSTOJI 
bool check_idTour_exist(std::string id)
{
	std::fstream tFile("Tours.txt", std::ios::in);
	int n = num_of_lines("Tours.txt");
	std::string out1, out2, out3;
	for (int i = 0; i < n; i++)
	{
		tFile >> out1;
		if (out1 == id)
			return true;
		tFile >> out2;
		int x = stoi(out2);
		int y = x + 3;
		for (int j = 0; j < y; j++)
		{
			tFile >> out3;
		}
	}
	return false;
}

//PROVJERA DA LI VOZAC POSTOJI U SISTEMU
bool check_username_exist(std::string username)
{
	std::fstream uFile("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");
	std::string out;
	for (int i = 0; i < n; i++)
	{
		int check = 0;
		for (int j = 0; j < 7; j++)
		{
			uFile >> out;
			if ((j == 2) && (out == username))
			{
				check++;
			}
			if (check == 1)
				return true;
		}
	}
	return false;
}

//PROVJERA DA LI BUS POSTOJI
bool check_idBus_exist(std::string id)
{
	std::fstream bFile("Bus.txt", std::ios::in);
	int n = num_of_lines("Bus.txt");
	std::string out;
	for (int i = 0; i < n; i++)
	{
		int check = 0;
		for (int j = 0; j < 7; j++)
		{
			bFile >> out;
			if ((j == 0) && (out == id))
				check++;
			if (check == 1)
				return true;
		}
	}
	return false;

}

//PROVJERA DA LI JE VOZAC DOSTUPAN
bool check_is_driver_available(std::string username)
{
	std::fstream dFile("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");
	std::string out;
	for (int i = 0; i < n; i++)
	{
		int check = 0;
		for (int j = 0; j < 7; j++)
		{
			dFile >> out;
			if ((j == 2) && (username == out))
				check++;
			if ((j == 6) && (out == "false"))
				check++;
			if (check == 2)
				return true;
		}
	}
	return false;
}

//PROVJERA DA LI JE BUS DOSTUPAN
bool check_is_bus_available(std::string id)
{
	std::fstream aFile("Bus.txt", std::ios::in);
	int n = num_of_lines("Bus.txt");
	std::string out;
	for (int i = 0; i < n; i++)
	{
		int check = 0;
		for (int j = 0; j < 7; j++)
		{
			aFile >> out;
			if ((j == 5) && (id == "true"))
				return true;
		}
	}
	return false;
}

//PROVJERA DA LI LOKACIJA POSTOJI U SISTEMU
bool checkLocation(std::string location)
{
	std::fstream lFile;
	std::string line;
	bool check = false;
	lFile.open("Locations.txt", std::ios::in);
	if (lFile.is_open()) {

		while (getline(lFile, line))
		{
			if (line == location)
				check = true;
		}
	}
	lFile.close();
	return check;
}

//POSTAVLJA STANJE VOZACA NA ZAUZETO
void driverIsBusy(std::string username)
{
	std::fstream drFile("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");
	std::string string1, string2, string3, string4, string5, string6, string7;
	bool check = false;
	for (int i = 0; i < n; i++)
	{
		drFile >> string1;
		drFile >> string2;
		drFile >> string3;
		if (string3 == username)
			check = true;
		drFile >> string4;
		drFile >> string5;
		drFile >> string6;
		drFile >> string7;
		drFile << string1;
		drFile << string2;
		drFile << string3;
		drFile << string4;
		drFile << string5;
		drFile << string6;
		if (check)
			drFile << "true";
		drFile << string7;

	}
}

//POSTAVLJA BUS NA STANJE GDJE JE NEDOSTUPAN
void busIsBusy(std::string id)
{
	std::fstream bFile("Bus.txt", std::ios::in);
	int n = num_of_lines("Bus.txt");
	std::string s1, s2, s3, s4, s5, s6;
	bool check = false;
	for (int i = 0; i < n; i++)
	{

		bFile >> s1;
		if (s1 == id)
			check == true;
		bFile >> s2;
		bFile >> s3;
		bFile >> s4;
		bFile >> s5;
		bFile >> s6;
		bFile << s1;
		bFile << s2;
		bFile << s3;
		bFile << s4;
		bFile << s5;
		if (check)
			bFile << "false";
		else
			bFile << s6;

	}
}



