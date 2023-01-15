#pragma once
#include <cstdlib>
#include "Person.h"
#include "validate.h"
#include "manipulate.h"
#include <random>

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
		file.close();
	}

	void addTour()
	{
		std::string id, withinBorder;
		int num;
		bool check, checkId, checkidTourExist;
		std::fstream tourFile;
		do {
			std::cout << "Unesite jedinstveni ID ture. ID moze da bude kombinacija slova i cifara duzine vece od 4.\n";
			std::cin >> id;
			checkId = check_id_tour(id);
			checkidTourExist = check_idTour_exist(id);
			if (checkId == true && checkidTourExist == false) {
				tourFile.open("Tours.txt", std::ios::app);
				tourFile << id << ",";
			}
			else {
				std::cout << "Tura vec postoji ili nije dodana u pravilnom obliku.\n\n";
			}
		} while (checkId == false || checkidTourExist == true);
		std::cout << "Unesite koliko lokacija ce imati tura:\n";
		std::cin >> num;
		tourFile << num << ",";
		system("cls");
		std::string location;
		int st = 0;
		for (int i = 1; i <= num; i++) {
			st++;
			std::cout << "Unesite " << i << ".lokaciju koju zelite da dodate u turu : \n";
			if (st == 1) {

				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			}
			std::getline(std::cin, location);
			check = checkLocation(location);
			if (check == true) {
				tourFile << location << ",";
			}
			else {
				std::cout << "Lokaciju nije moguce dodati u turu.\n\n";
				i--;
			}

		}
		std::cout << "Da li je lokacija unutar granica drzave? (Unesite Da ako jeste, a Ne ako nije.)\n";
		std::cin >> withinBorder;
		if (withinBorder == "Da") {
			tourFile << "1" << std::endl;
		}
		else {
			tourFile << "0" << std::endl;
		}
		tourFile.close();
		system("cls");
		menu();
	}

    //radi
	void addBus()
	{
		std::string id, model, hasWifi, hasWc, isAvailable = "true";
		int numOfSeats;
		bool checkId;
		std::fstream busFile;
		std::cout << "Unesite jedinstveni ID busa:\n";
		std::cin >> id;
		do {
			checkId = check_id_bus(id) && !check_idBus_exist(id);
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

	//radi
	void addLocation()
	{
		std::string location;
		bool check = false;
		std::fstream locationFile;
		int i = 0;
		do
		{
			i++;
			std::cout << "Unesite lokaciju koju zelite da dodate:\n";
			if (i == 1)
			{
				std::cin.ignore();
			}
			getline(std::cin, location);
			check = checkLocation(location);
			if (check == false) {

				locationFile.open("Locations.txt", std::ios::app);
				locationFile << location << "\n";
				locationFile.close();
			}
			else
			{
				std::cout << "Nije moguce unijeti trazenu lokaciju, ona vec postoji.\n\n";
			}
		} while (check == true);
		system("cls");
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
				file1 << username << " ";
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
				file1 << idBus << std::endl;
				busIsBusy(idBus);
			}
			else
				std::cout << "Uneseni ID ne postoji." << std::endl;

		} while (checkId3 == false);

		system("cls");
		menu();
	}


	//helper za addCoupon
	std::string generate_random_string() 
	{
		std::string random_string;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 25); 
		for (int i = 0; i < 15; i++) {
			char c = 'a' + dis(gen);
			random_string += c;
		}
		return random_string;
	}

	//radi
	void addCoupon()
	{
		std::string result, value;
		std::cout << "Unesite vrijednost bona:\n";
		std::cin >> value;
		result = generate_random_string();
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
			std::cout << "1.) Dodavanje podataka\n";
			std::cout << "2.) Pregled podataka i obavjestenja\n";
			std::cout << "3.) Upravljanje nalozima\n";
			std::cout << "--> ";
			std::cin >> option;
			if (option == "1")
			{
				addData();
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
					std::cout << "7) Vrati nazad\n";
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
					else if (option2 == "7")
					{
						system("cls");
						menu();
					}
					else
					{
						system("cls");
						std::cout << "Izabrali ste nepostojecu opciju. Pokusajte ponovo " << std::endl;
					}
				} while (option2 != "1" && option2 != "2" && option2 != "3" && option2 != "4" && option2 != "5" && option2 != "6");
			}
			else if (option == "3")
			{
			manipulate();
			}

		} while (option != "1" && option != "2" && option != "3");

	}

	void manipulate()
	{
		system("cls");
		std::string option_admin;
		do
		{
			std::cout << "\nIzaberite unosenjem broja zeljenu opciju:\n\n";
			std::cout << "1.) Kreiranje naloga za vozace\n";
			std::cout << "2.) Brisanje naloga\n";
			std::cout << "3.) Deaktivacija naloga\n";
			std::cout << "4.) Aktivacija naloga\n";
			std::cout << "5.) Vrati nazad\n";
			std::cout << "--> ";
			std::cin >> option_admin;
			system("cls");
			if (option_admin == "1")
			{
				registration("3");
				manipulate();
			}
			else if (option_admin == "2")
			{
				std::cout << "Unesite korisnicko ime naloga koji zelite obrisati: ";
				std::string delete_name;
				std::cin >> delete_name;
				if (manipulate_at(delete_name) != 0)
				{
					system("cls");
					std::cout << "Korisnik " << delete_name << " je uspjesno izbrisan iz baze\n";
					delete_line(delete_name);
				}
				else
				{
					system("cls");
					std::cout << "Korisnik ne postoji ili pokusavate izbrisati administratorski nalog\n";
				}
				manipulate();
			}
			else if (option_admin == "3")
			{
				std::cout << "Unesite korisnicko ime naloga koji zelite suspendovati: ";
				std::string suspend_name;
				std::cin >> suspend_name;
				if ((manipulate_at(suspend_name) != 0) && (suspend_at(suspend_name) != 0))
				{
					system("cls");
					std::cout << "Korisnik " << suspend_name << " je uspjesno suspendovan\n";
				}
				else
				{
					system("cls");
					std::cout << "Korisnik ne postoji ili pokusavate suspendovati administratorski nalog\n";
				}
				manipulate();
			}
			else if (option_admin == "4")
			{
				std::cout << "Unesite korisnicko ime naloga koji zelite aktivirati: ";
				std::string activate_name;
				std::cin >> activate_name;
				if ((manipulate_at(activate_name) != 0) && (activate_at(activate_name) != 0))
				{
					system("cls");
					std::cout << "Korisnik " << activate_name << " je uspjesno aktiviran\n";
				}
				else
				{
					system("cls");
					std::cout << "Korisnik ne postoji ili pokusavate aktivirati nesuspendovan nalog\n";
				}
				manipulate();
			}
			else if (option_admin == "5")
			{
				system("cls");
				menu();
			}
		} while (option_admin != "1" && option_admin != "2" && option_admin != "3" && option_admin != "4");

	}
	void addData()
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
			std::cout << "6) Vrati nazad\n";
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
				system("cls");
				int o;
				std::cout << "Bus uspjesno dodan\n\n";
				do
				{
					std::cout << "Zelite li dodati jos buseva, ili povratak nazad?\n";
					std::cout << "1.) Dodavanje busa\n";
					std::cout << "2.) Povratak nazad\n";

					std::cin >> o;
					if (o == 1)
					{
						system("cls");
						addBus();
					}
					else if (o == 2)
					{
						system("cls");
						addData();
					}
					else
					{
						system("cls");
						std::cout << "Nepoznata opcija, probajte ponovo!\n";
					}
				} while (o != 2);
			}
			else if (option1 == "3")
			{
				system("cls");
				addLocation();
				system("cls");
				int o;
				std::cout << "Lokacija uspjesno dodata\n\n";
				do
				{
					std::cout << "Zelite li dodati jos lokacija, ili povratak nazad?\n";
					std::cout << "1.) Dodavanje lokacija\n";
					std::cout << "2.) Povratak nazad\n";

					std::cin >> o;
					if (o == 1)
					{
						system("cls");
						addLocation();
					}
					else if (o == 2)
					{
						system("cls");
						addData();
					}
					else
					{
						system("cls");
						std::cout << "Nepoznata opcija, probajte ponovo!\n";
					}
				} while (o != 2);
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
				system("cls");
				int o;
				std::cout << "Bon uspjesno dodat\n\n";
				do
				{
					std::cout << "Zelite li dodati jos bonova, ili povratak nazad?\n";
					std::cout << "1.) Dodavanje bona\n";
					std::cout << "2.) Povratak nazad\n";
					
					std::cin >> o;
					if (o == 1)
					{
						system("cls");
						addCoupon();
					}
					else if (o == 2)
					{
						system("cls");
						addData();
					}
					else
					{
						system("cls");
						std::cout << "Nepoznata opcija, probajte ponovo!\n";
					}
				} while (o != 2);
				

			}
			else if (option1 == "6")
			{
			system("cls");
			menu();
            }
			else
			{
				system("cls");
				std::cout << "Izabrali ste nepostojecu opciju. Pokusajte ponovo " << std::endl;
			}
			//addData();
		} while (option1 != "1" && option1 != "2" && option1 != "3" && option1 != "4" && option1 != "5");
	}
};