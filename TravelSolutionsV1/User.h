#pragma once
#include <fstream>
#include <ctime>
#include <sstream>
#include <chrono>
#include<iomanip>
#include "Person.h"

class User : public Person
{
private:
	bool suspended;
	double balance;
public:
	User(std::string username)
	{
		std::fstream file("Users.txt", std::ios::in);
		int n = num_of_lines("Users.txt");

		std::string firstName, lastName, userName, pass, type, isSuspended, bal;

		for (int i = 0; i < n; i++)
		{
			file >> firstName;
			file >> lastName;
			file >> userName;
			file >> pass;
			file >> type;
			file >> isSuspended;
			file >> bal;
			if (username == userName)
			{
				this->name = firstName;
				this->surname = lastName;
				this->username = userName;
				this->password = pass;
				if (isSuspended == "true") this->suspended = true;
				else this->suspended = false;
				this->balance = std::stod(bal);
			}
		}
		file.close();
	}

	int menu()
	{
		std::cout << "Vase stanje na racunu: " << this->balance << "KM" << std::endl << std::endl;
		printDrives();
		std::string option;
		do
		{
			std::cout << "\nIzaberite unosenjem broja zeljenu opciju:\n\n";
			std::cout << "1.) Pretrazivanje voznji\n";
			std::cout << "2.) Unos poklon bona\n";
			std::cout << "3.) Kupi kartu\n";
			std::cout << "4.) Odjavi se\n";

			std::cout << "--> ";
			std::cin >> option;
			if (option == "1")
			{
				searchDrive();
				std::string option2;
				do
				{
					std::cout << "\n\nOdaberite opciju unosem broja:\n";
					std::cout << "1.) Vrati nazad\n";
					std::cin >> option2;
					if (option2 == "1")
					{
						system("cls");
						menu();
					}
				} while (option2 != "1");
			}
			else if (option == "2")
			{
				insertCoupon();
			}
			else if (option == "3")
			{
				buyTicket();
			}
			else if (option == "4")
			{
				system("cls");
				return 1;
			}

		} while (option != "1" && option != "2" && option != "3" && option != "4");

	}

	void printDrives()
	{
		std::string id, line, locations, inside_string;
		bool inside;
		std::fstream uFile("Tours.txt", std::ios::in);
		if (uFile.is_open())
		{
			while (getline(uFile, id, ',') && getline(uFile, locations, ',') && getline(uFile, inside_string))
			{
				int num_locations = atoi(locations.c_str());
				//std::cout << id;
				int last_number;
				if (isdigit(inside_string[inside_string.size() - 1]))
				{
					last_number = stoi(std::string(1, inside_string[inside_string.size() - 1]));
				}
				if (inside_string.size() > 1)
				{
					inside_string.erase(inside_string.size() - 2, 2);
				}

				std::fstream  dfile("Drive.txt", std::ios::in);
				std::string line1;
				if (dfile.is_open())
				{
					while (getline(dfile, line1))
					{
						if (line1.find(id) != std::string::npos)
						{
							std::string driveID, tourID, date1, date2, time1, time2, driver, busID, price, numSeats;
							std::stringstream ss(line1);
							ss >> driveID >> tourID >> driver >> busID >> date1 >> time1 >> date2 >> time2 >> price >> numSeats;
							std::string format_datuma = "%d.%m.%Y.";
							std::string format_vremena = "%H:%M";

							std::tm datum = {};
							std::istringstream ss_datum(date1);
							ss_datum >> std::get_time(&datum, format_datuma.c_str());

							std::tm vrijeme = {};
							std::istringstream ss_vrijeme(time1);
							ss_vrijeme >> std::get_time(&vrijeme, format_vremena.c_str());

							datum.tm_hour = vrijeme.tm_hour;
							datum.tm_min = vrijeme.tm_min;

							std::time_t unix_time = std::mktime(&datum);
							std::chrono::system_clock::time_point time_point = std::chrono::system_clock::from_time_t(unix_time);

							auto current_time = std::chrono::system_clock::now();
							if (time_point > current_time)
							{
								std::cout << "\nID voznje: " << driveID << std::endl;
								std::cout << inside_string;
								std::cout << std::endl;
								std::cout << "Datum i vrijeme polaska: " << date1 << " " << time1 << std::endl;
								std::cout << "Datum i vrijeme dolaska: " << date2 << " " << time2 << std::endl;
								std::cout << "Putovanje je ";
								if (last_number == 1) std::cout << "unutar granica drzave. Pasos nije neophodan.\n";
								else if (last_number == 0) std::cout << "izvan granica drzave. Pasos je neophodan.\n";
								std::cout << "Cijena karte: " << price << "KM\n";
								if (numSeats == "0") std::cout << "Nema slobodnih mjesta.\n";
								else std::cout << "Preostalih mjesta: " << numSeats;
								std::cout << std::endl;
							}
						}
					}
				}
				dfile.close();
			}

		}
		uFile.close();
	}

	void searchDrive()
	{
		system("cls");
		std::string Ilocation;
		std::cout << "Unesite lokaciju za pretragu:\n";
		std::cout << "-->";
		std::cin.ignore();
		getline(std::cin, Ilocation);
		bool check = checkLocation(Ilocation);
		if (check == true)
		{
			std::string id, line, locations, inside_string;
			bool inside;
			std::fstream uFile("Tours.txt", std::ios::in);
			if (uFile.is_open())
			{
				while (getline(uFile, id, ',') && getline(uFile, locations, ',') && getline(uFile, inside_string))
				{
					int num_locations = atoi(locations.c_str());
					//std::cout << id;
					int last_number;
					if (isdigit(inside_string[inside_string.size() - 1]))
					{
						last_number = stoi(std::string(1, inside_string[inside_string.size() - 1]));
					}
					if (inside_string.size() > 1)
					{
						inside_string.erase(inside_string.size() - 2, 2);
					}
					if (inside_string.find(Ilocation) != std::string::npos)
					{
						std::fstream  dfile("Drive.txt", std::ios::in);
						std::string line1;
						if (dfile.is_open())
						{
							while (getline(dfile, line1))
							{

								if (line1.find(id) != std::string::npos)
								{
									std::string  driveID, tourID, date1, date2, time1, time2, driver, busID, price, numSeats;
									std::stringstream ss(line1);
									ss >> driveID >> tourID >> driver >> busID >> date1 >> time1 >> date2 >> time2 >> price >> numSeats;
									std::string format_datuma = "%d.%m.%Y.";
									std::string format_vremena = "%H:%M";

									std::tm datum = {};
									std::istringstream ss_datum(date1);
									ss_datum >> std::get_time(&datum, format_datuma.c_str());

									std::tm vrijeme = {};
									std::istringstream ss_vrijeme(time1);
									ss_vrijeme >> std::get_time(&vrijeme, format_vremena.c_str());

									datum.tm_hour = vrijeme.tm_hour;
									datum.tm_min = vrijeme.tm_min;

									std::time_t unix_time = std::mktime(&datum);
									std::chrono::system_clock::time_point time_point = std::chrono::system_clock::from_time_t(unix_time);

									auto current_time = std::chrono::system_clock::now();
									if (time_point > current_time)
									{

										std::cout << "\nID voznje:" << driveID << "\n";
										std::cout << inside_string;
										std::cout << std::endl;
										std::cout << "Datum i vrijeme polaska: " << date1 << " " << time1 << std::endl;
										std::cout << "Datum i vrijeme dolaska: " << date2 << " " << time2 << std::endl;
										std::cout << "Putovanje je ";
										if (last_number == 1) std::cout << "unutar granica drzave. Pasos nije neophodan.\n";
										else if (last_number == 0) std::cout << "izvan granica drzave. Pasos je neophodan.\n";
										std::cout << "Cijena jedne karte: " << price << "KM\n";
										if (numSeats == "0") std::cout << "Nema slobodnih mjesta.\n";
										else std::cout << "Prostalih mjesta: " << numSeats;
										std::cout << std::endl;
									}

								}
							}
						}
						dfile.close();

					}

				}

			}
			uFile.close();
		}
		else
		{
			std::cout << "Ne postoji takva lokacija\n";
		}
	}

	void insertCoupon()
	{
		int check = 0;
		std::string userInput;
		std::string value;
		double dValue;
		std::string coupon;
		std::cout << "Unesite odgovarajuci kod: ";
		std::cin >> userInput;
		std::ifstream couponFile("Coupons.txt");
		std::ofstream newCouponFile("TempCoupons.txt");
		int n = num_of_lines("Coupons.txt");
		int lineOfCoupon = -1;
		if (couponFile.is_open())
		{
			for (size_t i = 0; i < n; i++)
			{
				couponFile >> coupon;
				couponFile >> value;
				//ako je korisnik unio ispravan kod
				if (coupon == userInput)
				{
					lineOfCoupon = i;
					check++;
					//cita se vrijednost bona

					dValue = stod(value);
					this->balance += dValue;

					//otvaranje fajla sa korisnicima kako bi se promijenio iznos na racunu
					std::fstream oldFile("Users.txt", std::ios::in);
					std::fstream newFile("TempName.txt", std::ios::out);
					int num = num_of_lines("Users.txt");

					//string pomocu kojeg citamo iz fajla
					std::string out;

					int line = manipulate_at(this->username);

					//trazimo liniju gdje se nalazi korisnik i mjesto gdje je odredjeno za stanje na racunu azuriramo
					for (int i = 0; i < num; i++)
					{
						for (int j = 0; j < 7; j++)
						{
							oldFile >> out;
							if ((i == line) && (j == 6))
							{
								newFile << balance;
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

				}
				else
				{
					newCouponFile << coupon << " " << value;
					if (i != n - 1)
						newCouponFile << std::endl;
				}

			}
			couponFile.close();
			newCouponFile.close();

			remove("Coupons.txt");

			rename("TempCoupons.txt", "Coupons.txt");
			if (check)
			{
				system("cls");
				std::cout << "Poklon bon je uspjesno unesen. Stanje na racunu je azurirano." << std::endl;
				menu();
			}
			else
			{

				std::string option;
				do
				{
					system("cls");
					std::cout << "Unijeli ste pogresan kod." << std::endl;
					std::cout << "1) Pokusaj ponovo" << std::endl;
					std::cout << "2) Vrati se nazad" << std::endl;
					std::cout << "--> ";
					std::cin >> option;
					if (option == "1")
					{
						system("cls");
						insertCoupon();
					}
					else if (option == "2")
					{
						system("cls");
						menu();
					}
				} while (option != "1" || option != "2");

			}

		}
	}

	void buyTicket()
	{
		bool existID = false;
		std::string idDrive;
		std::ifstream driveFile("Drive.txt");
		int n = num_of_lines("Drive.txt");

		std::cout << "Unesite ID voznje za koju zelite kupiti karte: " << std::endl;
		std::cout << "--> ";
		std::cin >> idDrive;

		std::string out, out1;
		int numOfFreeSeats;
		double price = 0;

		while (n)
		{
			driveFile >> out;
			if (out == idDrive)
			{
				existID = true;
				for (int i = 0; i < 8; i++) //citamo cijenu jedne karte
					driveFile >> out;
				price = stod(out);
				driveFile >> out;
				numOfFreeSeats = stoi(out);
				break;
			}
			getline(driveFile, out1);
			n--;
		}
		driveFile.close();

		if (!existID)
		{
			system("cls");
			std::cout << "Unijeli ste nepostojeci broj." << std::endl << std::endl;
			menu();
		}
		std::string numOfTickets;
		int numberOfTickets;
		std::cout << "Unesite broj karti koje zelite kupiti: ";
		std::cin >> numOfTickets;
		numberOfTickets = stoi(numOfTickets);

		if (numberOfTickets > numOfFreeSeats)
		{
			system("cls");
			std::cout << "Oprostite, ali nema dovoljno mjesta." << std::endl << std::endl;
			menu();
		}
		else if (numberOfTickets * price > this->balance)
		{
			system("cls");
			std::cout << "Nemate dovoljan iznos na racunu." << std::endl << std::endl;
			menu();
		}
		else
		{
			system("cls");
			std::cout << "Transakcija je uspjesna. Kodove za karte sacuvajte:" << std::endl;
			for (int i = 0; i < numberOfTickets; i++)
			{
				generateTicket(idDrive);
			}
			system("pause");
			system("cls");
			balance = balance - numberOfTickets * price;
			//otvaranje fajla sa korisnicima kako bi se promijenio iznos na racunu
			std::fstream oldFile("Users.txt", std::ios::in);
			std::fstream newFile("TempName.txt", std::ios::out);
			int num = num_of_lines("Users.txt");

			//string pomocu kojeg citamo iz fajla
			std::string out;
			int line = manipulate_at(this->username);

			//trazimo liniju gdje se nalazi korisnik i mjesto gdje je odredjeno za stanje na racunu azuriramo
			for (int i = 0; i < num; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					oldFile >> out;
					if ((i == line) && (j == 6))
					{
						newFile << balance;
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
			//otvaranje fajla sa voznjama kako bi se promijenio broj slobodnih mjesta
			std::fstream oldFile2("Drive.txt", std::ios::in);
			std::fstream newFile2("TempName.txt", std::ios::out);
			int num2 = num_of_lines("Drive.txt");
			//string pomocu kojeg citamo iz fajla
			std::string out2;
			std::string currID;

			//trazimo liniju gdje se nalazi voznja i mjesto gdje je odredjeno za broj slobodnih mjesta azuriramo
			for (int i = 0; i < num2; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					oldFile2 >> out2;
					if (j == 0)
						currID = out2;
					if ((currID == idDrive) && (j == 9))
					{
						newFile2 << numOfFreeSeats - numberOfTickets;
					}
					else
						newFile2 << out2;
					if (j != 10)
						newFile2 << " ";
				}
				newFile2 << std::endl;
			}
			oldFile2.close();
			newFile2.close();

			remove("Drive.txt");
			rename("TempName.txt", "Drive.txt");

			menu();
		}
	}

	void generateTicket(std::string driveID)
	{
		std::ofstream ticketFile("Tickets.txt", std::ios::in | std::ios::app);
		std::string ticket;
		ticket = generate_random_string();
		ticketFile << ticket << " " << driveID << " " << username << std::endl;
		std::cout << ticket << std::endl;
		ticketFile.close();
	}

	std::string generate_random_string()
	{
		std::string random_string;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 25);
		for (int i = 0; i < 10; i++) 
		{
			char c = 'a' + dis(gen);
			random_string += c;
		}
		return random_string;
	}
};