#include <iostream>
#include "Driver.h"
#include "Admin.h"
#include "Person.h"
#include "User.h"
#include <fstream>
#include <cstdlib>
#include "validate.h"
#include "manipulate.h"

//FUNKCIJA ZA REGISTRACIJU, PARAMETAR TYPE ODREDJUJE KAKAV NALOG CE SE NAPRAVITI "1" ZA KORISNICKI, "2" ZA ADMIN, "3" ZA VOZACKI, UNUTRA IMAJU SVE VALIDACIJE ITD
bool registration(std::string type);
//FUNKCIJA ZA LOGIN KOJA VRACA ODREDJENI OBJEKAT NA OSNOVU TIPA
void login();
//FUNKCIJA ZA PRVU PRIJAVU
void firstLogin();
//FUNKCIJA KOJA DAJE POCETNI EKRAN PRI PALJENJU APLIKACIJE
void startPage();


int main()
{
	startPage();
	return 0;
}



void login()
{
	std::string username, password;
	system("cls");
	bool correctInput;

	do
	{

		std::cout << "Unesite vase korisnicko ime: \n";
		std::cin >> username;
		std::cout << "Unesite vasu lozinku: \n";
		std::cin >> password;

		correctInput = userExist(username, password); //provjera da li username i password postoje u sistemu
		if (correctInput == false)
		{
			system("cls");
			std::cout << "Pogresno korisnicko ime ili lozinka, probajte ponovo!\n\n";
		}
		else
		{
			std::string type = getUserType(username);
			if (type == "1")
			{
				system("cls");
				//Korisnik se ulogovao na sistem, kreira se objekat
				User user(username);
				user.menu();
			}
			else if (type == "2")
			{
				system("cls");
				//Admin se ulogovao na sistem, kreira se objekat
				Admin admin(username);
				admin.menu();
			}
			else if (type == "3")
			{
				system("cls");
				//Admin se ulogovao na sistem, kreira se objekat
				Driver vozac(username);
				vozac.menu();
			}
		}

	} while (correctInput == false);
}





void firstLogin()
{
	std::string username, password;
	do
	{
		std::cout << "Unesite korisnicko ime: \n";
		std::cin >> username;
		std::cout << "Unesite lozinku: \n";
		std::cin >> password;
		system("cls");
		if (username == "admin" && password == "admin")
		{
			std::ofstream file("Users.txt", std::ios::trunc);
			if (file.is_open()) {
				file.close();
			}
			else {
				std::cout << "Error opening file" << std::endl;
			}
			registration("2");
			startPage();
		}
		else
		{
			system("cls");
			std::cout << "Pogresno ste unijeli podatke. Pokusajte ponovo." << std::endl;
		}
	} while (username != "admin" && password != "admin");
}

//METODA KOJA DAJE POCETNI EKRAN PRI PALJENJU APLIKACIJE
void startPage()
{
	std::ifstream usersFile("Users.txt");
	std::string temp;
	usersFile >> temp;
	//ako je prva prijava na sistem
	if (temp == "admin" && num_of_lines("Users.txt") == 1)
	{
		usersFile.close();
		firstLogin();
	}
	else
	{
		usersFile.close();
		std::cout << "Dobrodosli, vas TravelSolutions\n";
		std::string option;
		do
		{
			std::cout << "\nIzaberite unosenjem broja zeljenu opciju: \n\n";
			std::cout << "1.) Prijava\n";
			std::cout << "2.) Registracija\n";
			std::cout << "3.) Izadji iz aplikacije\n\n";
			std::cout << "--> ";
			std::cin >> option;
			if (option == "1")
			{
				system("cls");
				login();
			}
			else if (option == "2")
			{
				system("cls");
				registration("1");
				startPage();
			}
			else if (option == "3")
				exit(0);
			else
			{
				system("cls");
				std::cout << "Izabrali ste nepostojecu opciju. Pokusajte ponovo:" << std::endl;
			}
		} while (option != "1" && option != "2" && option != "3");
	}
}