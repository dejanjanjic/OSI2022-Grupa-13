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
				file.close();
				return 0;
			}
		}
	}
	file.close();
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

//PROVJERA VALIDNOSTI ID-A VOZNJE
bool check_idDrive_exist(std::string forcheck)
{
	if (forcheck.size() == 5)
	{
		for (int i = 0; i < forcheck.size(); i++)
		{
			if (!isdigit(forcheck[i]))
			{
				return true;
			}
		}
		std::fstream tFile("Drive.txt", std::ios::in);
		int n = num_of_lines("Drive.txt");
		std::string out, out1;
		while (n) {
			getline(tFile, out, ',');
			getline(tFile, out1);
			if (out == forcheck)
				return true;
			n--;
		}
		tFile.close();
		return false;
	}

	return true;
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
	std::string out, out1;
	while (n) {
		getline(tFile, out, ',');
		getline(tFile, out1);
		if (out == id)
			return true;
		n--;
	}
	tFile.close();

	return false;
}

//PROVJERA DA LI VOZAC POSTOJI U SISTEMU
bool check_username_exist(std::string username)
{
	std::fstream uFile("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");
	std::string out;
	getline(uFile, out);
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
	uFile.close();
	return false;
}

///PROVJERA DA LI BUS POSTOJI
bool check_idBus_exist(std::string id)
{
	std::fstream bFile("Bus.txt", std::ios::in);
	int n = num_of_lines("Bus.txt");
	std::string out;
	for (int i = 0; i < n; i++)
	{
		int check = 0;
		for (int j = 0; j < 6; j++)
		{
			bFile >> out;
			if ((j == 0) && (out == id))
				check++;
			if (check == 1)
				return true;
		}
	}
	bFile.close();
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
	std::string out, tmp;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			aFile >> out;
			if (j == 0 && out == id)
				tmp = out;
			if ((j == 5) && (out == "false") && tmp == id)
				return true;
		}
	}
	aFile.close();
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

// VRACA LINIJU U KOJOJ SE NALAZE INFORMACIJE O VOZACU
int getLineWithDriver(std::string username)
{
	std::fstream filedriver("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");

	std::string out;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			filedriver >> out;
			if (out == username)
			{
				return i;
			}
		}
	}
	filedriver.close();
	return 0;
}


//VRACA LINIJU U KOJOJ SE NALAZE INFORMACIJE O BUSU
int getLineWithBus(std::string id)
{
	std::fstream filebus("Bus.txt", std::ios::in);
	int n = num_of_lines("Bus.txt");

	std::string out;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			filebus >> out;
			if (out == id)
			{
				return i;
			}
		}
	}
	filebus.close();
	return 0;
}

//POSTAVLJA STANJE VOZACA NA ZAUZETO
void driverIsBusy(std::string username)
{
	std::fstream oldfiles("Users.txt", std::ios::in);
	std::fstream newfiles("TempDriver.txt", std::ios::app);
	int n = num_of_lines("Users.txt");
	int line = getLineWithDriver(username);
	std::string out;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			oldfiles >> out;
			if ((i == line) && (j == 6))
			{
				newfiles << "true";
			}
			else
				newfiles << out;
			if (j != 6)
				newfiles << " ";
		}
		newfiles << std::endl;
	}

	oldfiles.close();
	newfiles.close();
	remove("Users.txt");
	rename("TempDriver.txt", "Users.txt");

}

//POSTAVLJA BUS NA ZAUZETO
void busIsBusy(std::string id)
{
	std::fstream oldfile("Bus.txt", std::ios::in);
	std::fstream newfile("TempBus.txt", std::ios::app);
	int n = num_of_lines("Bus.txt");
	int line = getLineWithBus(id);
	std::string out;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			oldfile >> out;
			if ((i == line) && (j == 5))
			{
				newfile << "true";
			}
			else
				newfile << out;
			if (j != 5)
				newfile << " ";
		}
		newfile << std::endl;
	}
	oldfile.close();
	newfile.close();
	remove("Bus.txt");
	rename("TempBus.txt", "Bus.txt");
}


//VRACA BROJ MJESTA U BUSU KOJI CE BITI ISKORISTENI ZA DODAVANJE VOZNJE
std::string numberOfFreePlaces(std::string id)
{
	std::fstream dat("Bus.txt", std::ios::in);
	int n = num_of_lines("Bus.txt");
	int numOfLine = getLineWithBus(id);
	std::string out;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			dat >> out;
			if ((i == numOfLine) && (j == 2))
				return out;
		}
	}
	dat.close();
}


