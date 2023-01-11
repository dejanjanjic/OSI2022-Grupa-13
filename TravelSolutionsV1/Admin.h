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
		std::string id, startTime, endTime, withinBorder;
		int num;
		bool check, checkId;
		std::fstream tourFile;
		std::cout << "Unesite jedinstveni ID ture:\n";
		std::cin >> id;
		do {
			checkId = check_id_tour(id);
			if (checkId == true) {
				tourFile.open("Tours.txt", std::ios::app);
				tourFile << id << " ";
			}
			else {
				std::cout << "Zahtijeva se ponovni unos ID-a:\n";
				std::cin >> id;
			}
		} while (checkId == false);
		std::cout << "Unesite koliko lokacija ce imati tura:\n";
		std::cin >> num;
		tourFile << num << " ";
		system("cls");
		do {
			std::string location;
			std::cout << "Unesite lokaciju koju zelite da dodate u turu:\n";
			std::cin >> location;
			check = checkLocation(location);
			if (check == true) {
				tourFile << location << " ";
				num--;
			}
			else
				std::cout << "Lokaciju nije moguce dodati u turu.\n";
		} while (num);

		std::cout << "Unesite vrijeme polaska:\n";
		std::cin >> startTime;
		std::cout << "Unesite vrijeme dolaska:\n";
		std::cin >> endTime;
		std::cout << "Da li je tura unutar granice drzave? (Unesite Da ili Ne) \n";
		std::cin >> withinBorder;
		tourFile << startTime << "  " << endTime << "  ";
		if (withinBorder == "Da") {
			tourFile << "1" << std::endl;
		}
		else {
			tourFile << "0" << std::endl;
		}
		tourFile.close();
	}

	void addBus()
	{
		std::string id, model, hasWifi, hasWc, isAvailable = "true";
		int numOfSeats;
		bool checkId;
		std::fstream busFile;
		std::cout << "Unesite jedinstveni ID busa:\n";
		std::cin >> id;
		do {
			checkId = check_id_bus(id);
			if (checkId == true) {
				busFile.open("Bus.txt", std::ios::app);
				busFile << id << " ";
			}
			else {
				std::cout << "Zahtijeva se ponovni unos id-a:\n";
				std::cin >> id;
			}
		} while (checkId == false);
		std::cout << "Unesite model autobusa:\n";
		std::cin >> model;
		std::cout << "Unesite broj sjedista:\n";
		std::cin >> numOfSeats;
		std::cout << "Da li autobus ima wifi? (Unesite Da ili Ne)\n";
		std::cin >> hasWifi;
		std::cout << "Da li autobus ima wc? (Unesite Da ili Ne)\n";
		std::cin >> hasWc;
		busFile << model << "  " << numOfSeats << "  ";
		if (hasWifi == "Da") {
			busFile << "1" << "  ";
		}
		else
			busFile << "0" << "  ";

		if (hasWc == "Da") {
			busFile << "1" << " " << isAvailable << std::endl;
		}
		else
			busFile << "0" << " " << isAvailable << std::endl;

		busFile.close();
	}

	void addLocation()
	{
		std::string location;
		bool check;
		std::fstream locationFile;
		do {
			std::cout << "Unesite lokaciju koju zelite da dodate:\n";
			std::cin >> location;
			check = checkLocation(location);
			if (check == false) {
				locationFile.open("Locations.txt", std::ios::app);
				if (locationFile.is_open())
					locationFile << location << "\n";
			}
		} while (check == true);
	}

	void addDrive()
	{
		std::string idTour, username, idBus;
		std::fstream file1, file2, file3;
		bool checkId1, checkId2, checkId3;
		do
		{
			std::cout << "Unesite jedinstveni ID ture:\n";
			std::cin >> idTour;
			checkId1 = check_idTour_exist(idTour);
			if (checkId1)
			{
				file1.open("Drive.txt", std::ios::app);
				file1 << idTour << " ";

			}
			else
				std::cout << "Uneseni ID ne postoji." << std::endl;

		} while (checkId1 == false);

		do
		{
			std::cout << "Unesite username vozaca:\n";
			std::cin >> username;
			checkId2 = (check_username_exist(username) && check_is_driver_available(username));
			if (checkId2)
			{
				file2.open("Drive.txt", std::ios::app);
				file2 << username << " ";
				driverIsBusy(username);
			}
			else
				std::cout << "Uneseni username ne postoji." << std::endl;
		} while (checkId2 == false);

		do
		{
			std::cout << "Unesite jedinstveni ID busa:\n";
			std::cin >> idBus;
			checkId3 = (check_idBus_exist(idBus) && check_is_bus_available(idBus));
			if (checkId3)
			{
				file3.open("Drive.txt", std::ios::app);
				file3 << idBus << std::endl;
				busIsBusy(idBus);
			}
			else
				std::cout << "Uneseni ID ne postoji." << std::endl;

		} while (checkId3 == false);

	}

	void addCoupon()
	{
		char alpha[73] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n','o', 'p', 'q', 'r',
		's', 't', 'u', 'v', 'w', 'x', 'y', 'z' , 'A' , 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N','O', 'P', 'Q', 'R','S', 'T','U', 'V', 'W','X','Y','Z', '0', '1','2','3','4','5','6','7','8','9', '/',
		'*','-','+','(', ')', '%', '&', '=', '!', '?' };

		std::string result = "", value;
		for (int i = 0; i < 10; i++)
			result = result + alpha[rand() % 73];
		std::cout << "Unesite vrijednost bona:\n";
		std::cin >> value;
		std::fstream couponFile;
		couponFile.open("Coupons.txt", std::ios::app);
		if (couponFile.is_open()) {
			couponFile << result << "  " << value << "\n";
			couponFile.close();
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
						std::cout << "Izabrali ste nepostojecu opciju. Pokusajte ponovo " << std::endl;
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
						std::cout << "Izabrali ste nepostojecu opciju. Pokusajte ponovo " << std::endl;
					}
				} while (option2 != "1" && option2 != "2" && option2 != "3" && option2 != "4" && option2 != "5" && option2 != "6");
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