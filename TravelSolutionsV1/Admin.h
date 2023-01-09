#pragma once
#include <cstdlib>
#include "Person.h"
#include "validate.h"

class Admin : public Person
{
public:
	//using Person::Person;
	Admin(std::string username)
	{
		std::fstream file("Users.txt", std::ios::in);
		int n = num_of_lines("Users.txt");

		std::string firstName, lastName, userName, pass, type;

		for (int i = 0; i < n; i++)
		{
			file >> firstName;
			file >> lastName;
			file >> userName;
			file >> pass;
			file >> type;
			if (username == userName)
			{
				this->name = firstName;
				this->surname = lastName;
				this->username = userName;
				this->password = pass;
			}
		}
	}

	void addTour()
	{
		std::string startLocation, endLocation, startTime, endTime, withinBorder;
		bool check1, check2;
		system("cls");
		std::fstream file;

		file.open("Tours.txt", std::ios::app);
		if (file.is_open()) {
			do {
				std::cout << "Unesite pocetnu lokaciju ture:\n";
				std::cin >> startLocation;
				std::cout << "Unesite krajnju lokaciju ture:\n";
				std::cin >> endLocation;
				check1 = checkStartLocation(startLocation);
				if (check1 == true)
					file << startLocation << " - ";
				else {
					system("cls");
					std::cout << "Unesena lokacija se ne moze dodati u turu. " << std::endl;
				}

				check2 = checkEndLocation(endLocation);
				if (check2 == true)
					file << endLocation << "  ";
				else {
					system("cls");
					std::cout << "Unesena lokacija se ne moze dodati u turu. " << std::endl;
				}
			} while (check1 == false && check2 == false);

			std::cout << "Unesite vrijeme polaska:\n";
			std::cin >> startTime;
			std::cout << "Unesite vrijeme dolaska:\n";
			std::cin >> endTime;
			std::cout << "Da li je tura unutar granice drzave? (Unesite Da ili Ne) \n";
			std::cin >> withinBorder;

			file << startTime << " - " << endTime << "  ";

			if (withinBorder == "Da") {
				file << "Tura je unutar granice drzave!" << std::endl;
			}
			else {
				file << "Tura je izvan granice drzave!" << std::endl;
			}
			file.close();
		}
	}

	void addBus()
	{
		std::string model, hasWifi, hasWc;
		int numOfSeats;
		system("cls");
		std::cout << "Unesite model autobusa:\n";
		std::cin >> model;
		std::cout << "Unesite broj sjedista:\n";
		std::cin >> numOfSeats;
		std::cout << "Da li autobus ima wifi? (Unesite Da ili Ne.)\n";
		std::cin >> hasWifi;
		std::cout << "Da li autobus ima wc? (Unesite Da ili Ne.)\n";
		std::cin >> hasWc;
		std::fstream file;
		file.open("Bus.txt", std::ios::app);
		if (file.is_open()) {
			file << model << "  " << numOfSeats << "  ";
			if (hasWifi == "Da") {
				file << "Autobus ima wifi." << "  ";
			}
			else
				file << "Autobus nema wifi." << "  ";

			if (hasWc == "Da") {
				file << "Autobus ima wc." << std::endl;
			}
			else
				file << "Autobus nema wc." << std::endl;

			file.close();
		}
	}

	void addLocation()
	{
		system("cls");
		std::string startLocation, endLocation;
		bool check1, check2;
		do {
			std::cout << "Unesite pocetnu lokaciju:\n";
			std::cin >> startLocation;
			check1 = checkStartLocation(startLocation);
			if (check1 == false) {
				std::fstream file;
				file.open("startLocations.txt", std::ios::app);
				if (file.is_open()) {
					file << startLocation;
					file.close();
				}
			}
			else
			{
				system("cls");
				std::cout << "Lokacija vec postoji." << std::endl;
			}

			std::cout << "Unesite krajnju lokaciju:\n";
			std::cin >> endLocation;
			check2 = checkEndLocation(endLocation);
			if (check2 == false) {
				std::fstream file;
				file.open("endLocations.txt", std::ios::app);
				if (file.is_open()) {
					file << endLocation;
					file.close();
				}
			}
			else {
				system("cls");
				std::cout << "Lokacija vec postoji." << std::endl;
			}


		} while (check1 == true && check2 == true);
	}

	void addDrive()
	{
		system("cls");
		std::string tour, driver, bus;
		std::fstream file;
		bool check = false;
		do
		{
			std::cout << "Unesite turu:\n";
			std::cin >> tour;
			std::string line;
			file.open("Tours.txt", std::ios::in);
			if (file.is_open()) {
				while (getline(file, line))
				{
					if (tour == line) {
						check = true;
						file.open("Drive.txt", std::ios::app);
						file << tour << "  "; break;
					}
				}
				file.close();
			}
		} while (check==false);
		bool check1 = false;
		do
		{
			std::cout << "Unesite vozaca:\n";
			std::cin >> driver;
			std::string line;
			file.open("Users.txt", std::ios::in);
			if (file.is_open()) {
				std::string line;
				while (getline(file, line))
				{
					if (driver == line) {
						check1 = true;
						file.open("Drive.txt", std::ios::app);
						file << driver << "  "; break;
					}
				}
				file.close();
			}
		} while (check1 == false);
		bool check2 = false;
		do
		{
			std::cout << "Unesite autobus:\n";
			std::cin >> bus;
			std::string line;
			file.open("Bus.txt", std::ios::in);
			if (file.is_open()) {
				while (getline(file, line))
				{
					if (bus == line) {
						file.open("Drive.txt", std::ios::app);
						file << bus << "\n"; break;
					}

				}
				file.close();
			}
		} while (check2==false);
	}

	void addCoupon()
	{
		char alpha[73] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n','o', 'p', 'q', 'r',
		's', 't', 'u', 'v', 'w', 'x', 'y', 'z' , 'A' , 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
		'N','O', 'P', 'Q', 'R','S', 'T','U', 'V', 'W','X','Y','Z', '0', '1','2','3','4','5','6','7','8','9', '/',
		'*','-','+','(', ')', '%', '&', '=', '!', '?'};

		std::string result = "", value;
		for (int i = 0; i < 10; i++)
			result = result + alpha[rand() % 73];
		std::cout << "Unesite vrijednost bona:\n";
		std::cin >> value;
		std::fstream file;
		file.open("Bonovi.txt", std::ios::app);
		if (file.is_open()) {
			file << result << "  " << value << "\n";
			file.close();
		}
	}


	void menu()
	{
		std::string option;
		do
		{
			std::cout << "\nIzaberite unosenjem broja zeljenu opciju:\n\n";
			std::cout << "1.) Dodaj podatke\n";
			std::cout << "2.) Pregledaj podatake i obavjestenja\n";
			std::cout << "3.) Upravljaj nalozima\n";
			std::cout << "--> ";
			std::cin >> option;
			if (option == "1")
			{
				std::string option1;
				system("cls");
				do
				{
					std::cout << "\nIzaberite unosenjem broja zeljenu opciju za dodavanje podataka:\n\n";
					std::cout << "1) Dodaj turu\n";
					std::cout << "2) Dodaj autobus\n";
					std::cout << "3) Dodaj lokaciju\n";
					std::cout << "4) Dodaj voznju\n";
					std::cout << "5) Dodaj poklon bon\n";
					std::cout << "--> ";
					std::cin >> option1;

					if (option1 == "1")
					{
						system("cls");
						addTour();
					}
					else if (option1 == "2")
					{
						system("cls");
						addBus();
					}
					else if (option1 == "3")
					{
						system("cls");
						addLocation();
					}
					else if (option1 == "4")
					{
						system("cls");
						addDrive();
					}
					else if (option1 == "5")
					{
						system("cls");
						addCoupon();
					}
					else
					{
						system("cls");
						std::cout << "Izabrali ste nepostojecu opciju. Pokusajte ponovo: " << std::endl;
					}
				} while (option1 != "1" && option1 != "2" && option1 != "3" && option1 != "4" && option1 != "5");
			}
			else if (option == "2")
			{  
				std::string option2;
				system("cls");
				do
				{
					std::cout << "\nIzaberite unosenjem broja zeljenu opciju za pregled podataka:\n\n";
					std::cout << "1) Pregled tura\n";
					std::cout << "2) Pregled autobusa\n";
					std::cout << "3) Pregled lokacija\n";
					std::cout << "4) Pregled voznji\n";
					std::cout << "5) Pregled poklon bonova\n";
					std::cout << "6) Pregled obavjestenja\n";
					std::cout << "--> ";
					std::cin >> option2;
					if (option2 == "1")
					{
						system("cls");
						//tourOverview();
					}
					else if (option2 == "2")
					{
						system("cls");
						//busOverview();
					}
					else if (option2 == "3")
					{
						system("cls");
						//locationOverview();
					}
					else if (option2 == "4")
					{
						system("cls");
						//driveOverview();
					}
					else if (option2 == "5")
					{
						system("cls");
						//couponOverview();
					}
					else if (option2 == "6")
					{
						system("cls");
						//notificationOverview();
					}
					else
					{
						system("cls");
						std::cout << "Izabrali ste nepostojecu opciju. Pokusajte ponovo: " << std::endl;
					}
				} while (option2 != "1"&& option2!="2" && option2 !="3" && option2!="4" && option2 !="5" && option2!="6");
			} 
			//else {}

		} while (option != "1" && option != "2" && option != "3");

	}

	/*void set_user_type() override
	{
		this->user_type = "2";
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