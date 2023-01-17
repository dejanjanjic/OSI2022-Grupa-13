#pragma once
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "Person.h"

class Driver : public Person
{
private:
	bool suspended;
	bool isBusy;
public:
	//using Person::Person;
	Driver(std::string username)
	{
		std::ifstream file("Users.txt");
		int n = num_of_lines("Users.txt");

		std::string firstName, lastName, userName, pass, type, isSuspended, busy;

		for (int i = 0; i < n; i++)
		{
			file >> firstName;
			file >> lastName;
			file >> userName;
			file >> pass;
			file >> type;
			file >> isSuspended;
			file >> busy;
			if (username == userName)
			{
				this->name = firstName;
				this->surname = lastName;
				this->username = userName;
				this->password = pass;
				if (isSuspended == "true") this->suspended = true;
				else this->suspended = false;
				if (busy == "true") this->isBusy = true;
				else this->isBusy = false;
			}
		}
	}

	int menu()
	{
		printNextForDriver();
		std::string option;
		do
		{
			std::cout << "Izaberite unosenjem broja zeljenu opciju:\n";
			std::cout << "1.) Pregled zavrsenih voznji\n";
			std::cout << "2.) Prijava incidenta\n";
			std::cout << "3.) Dodavanje izvjestaja\n";
			std::cout << "4.) Odjavi se\n";
			std::cout << "-->";
			std::cin >> option;
			if (option == "1")
			{
				std::string option1;
				system("cls");
				printPastForDriver();
				do
				{
					std::cout << "\nUnesite 1 za povratak nazad\n";
					std::cout << "-->";
					std::cin >> option1;
					if (option == "1")
					{
						system("cls");
						menu();
					}
				} while (option1 != "1");
			}
			else if (option == "2")
			{
				system("cls");
				std::string option3;
				bool odvezeno = printPastForDriver();
				prijaviIncident(odvezeno);
				do
				{
					std::cout << "\nUnesite 1 za povratak nazad\n";
					std::cout << "-->";
					std::cin >> option3;
					if (option3 == "1")
					{
						system("cls");
						menu();
					}
				} while (option3 != "1");
			}

			else if (option == "3")
			{
				std::string option2;
				system("cls");
				bool odvezeno = printPastForDriver();
				dodajIzvjestaj(odvezeno);
				do
				{
					std::cout << "\nUnesite 1 za povratak nazad\n";
					std::cout << "-->";
					std::cin >> option2;
					if (option2 == "1")
					{
						system("cls");
						menu();
					}
				} while (option2 != "1");
			}
			else if (option == "4")
			{
				system("cls");
				return 1;
			}
			else
			{
				std::cout << "Nepostojeca opcija. Pokusajte ponovo.\n";
			}
		} while (option != "1" && option != "2" && option != "3");
	}

	void dodajIzvjestaj(bool odvezeno)
	{
		if (odvezeno == false)
		{
			std::cout << "Nemoguce dodati izvjestaj.\n";
		}
		else
		{
			std::cout << "Unesite ID voznje za koju zelite da dodate izvjestaj.\n";
			std::string ID, line, tekst;
			std::cout << "-->";
			std::cin >> ID;
			std::fstream dfile("Drive.txt", std::ios::in | std::ios::out);
			std::fstream ifile;
			if (dfile.is_open())
			{
				long long pos = dfile.tellg();
				while (getline(dfile, line))
				{
					if (line.find(ID) != std::string::npos)
					{
						std::string driveID, tourID, driver, busID, date1, time1, date2, time2, price, numSeats, izvjestaj;
						std::stringstream ss(line);
						ss >> driveID >> tourID >> driver >> busID >> date1 >> time1 >> date2 >> time2 >> price >> numSeats >> izvjestaj;
						if ((ID == driveID) && (izvjestaj == "0"))
						{
							ifile.open("Reports.txt", std::ios::app);
							ifile << ID << " ";
							std::cout << "Unesite izvjestaj:\n";
							std::cin.ignore();
							getline(std::cin, tekst);
							ifile << tekst << std::endl;
							ifile.close();

							std::string format_datuma = "%d.%m.%Y.";
							std::string format_vremena = "%H:%M";

							std::tm datum2 = {};
							std::istringstream ss_datum2(date2);
							ss_datum2 >> std::get_time(&datum2, format_datuma.c_str());

							std::tm vrijeme2 = {};
							std::istringstream ss_vrijeme2(time2);
							ss_vrijeme2 >> std::get_time(&vrijeme2, format_vremena.c_str());

							datum2.tm_hour = vrijeme2.tm_hour;
							datum2.tm_min = vrijeme2.tm_min;

							std::time_t unix_time2 = std::mktime(&datum2);
							std::chrono::system_clock::time_point time_point2 = std::chrono::system_clock::from_time_t(unix_time2);

							auto current_time = std::chrono::system_clock::now();
							auto time_diff = std::chrono::duration_cast<std::chrono::hours>(current_time - time_point2);

							if (time_diff.count() > 24)
							{
								std::cout << "Izvjestaj nije dodan u naredna 24h od datuma i vremena voznje.\n";
							}
							else
							{
								// promjena zadnjeg stringa u liniji
								std::string lastString;
								std::stringstream ss(line);
								while (ss >> lastString);
								pos += line.rfind(lastString);
								dfile.seekp(pos);
								dfile << "1";
								break;
								std::cout << "Izvjestaj je uspjesno dodan.\n";
							}
						}
						else if (izvjestaj == "1")
						{
							std::cout << "Nemoguce je ponovo dodati izvjestaj.\n";
						}
					}
					pos = dfile.tellg();
				}
			}
			dfile.close();
		}
	}


	void prijaviIncident(bool odvozeno)
	{
		if (odvozeno == false)
		{
			std::cout << "\nNiste odvezli nijednu voznju. Ne mozete da prijavite incident.\n";
		}
		else
		{
			std::cout << "Unesite ID voznje za koju zelite da prijavite incident.\n";
			std::string ID, line, tekst;
			std::cout << "-->";
			std::cin >> ID;
			bool check = check_idDrive_exist(ID);
			if (check == false)
			{
				std::fstream dfile("Drive.txt");
				std::fstream ifile;
				if (dfile.is_open())
				{
					while (getline(dfile, line))
					{
						if (line.find(ID) != std::string::npos)
						{
							std::string driveID;
							std::stringstream ss(line);
							ss >> driveID;
							if (ID == driveID)
							{
								ifile.open("Incidentes.txt", std::ios::app);
								ifile << ID << " ";
								std::cout << "Unesite podatke o incidentu:\n";
								std::cin.ignore();
								getline(std::cin, tekst);
								ifile << tekst << std::endl;
								ifile.close();
							}
							std::cout << "Uspjesno ste dodali incident.\n";
						}
					}
				}dfile.close();
			}
			else
				std::cout << "Pogresan ID. Pokusajte ponovo.\n";
		}
	}

	bool printPastForDriver()
	{
		bool odvozeno;
		std::string line1, locations, inside_string;
		std::fstream dfile("Drive.txt", std::ios::in);
		if (dfile.is_open())
		{
			while (getline(dfile, line1))
			{
				odvozeno = true;
				if (line1.find(this->username) != std::string::npos)
				{
					std::string driveID, tourID, busID, date1, date2, time1, time2, driver, price, numSeats, izvjestaj;
					std::stringstream ss(line1);
					ss >> driveID >> tourID >> driver >> busID >> date1 >> time1 >> date2 >> time2 >> price >> numSeats >> izvjestaj;
					std::fstream uFile("Tours.txt", std::ios::in);
					if (uFile.is_open())
					{
						std::string id2;
						while (getline(uFile, id2, ',') && getline(uFile, locations, ',') && getline(uFile, inside_string))
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
							std::string line1;
							if (tourID == id2)
							{
								std::stringstream ss(line1);
								ss >> driveID >> tourID >> driver >> busID >> date1 >> time1 >> date2 >> time2 >> price >> numSeats >> izvjestaj;
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
								if (time_point < current_time)
								{
									std::cout << "\nImali ste voznju " << driveID << " \n";
									std::cout << inside_string;
									std::cout << std::endl;
									std::cout << "Datum i vrijeme polaska: " << date1 << " " << time1 << std::endl;
									std::cout << "Datum i vrijeme dolaska: " << date2 << " " << time2 << std::endl;
									std::cout << "Putovanje je ";
									if (last_number == 1) std::cout << "bilo unutar granica drzave. Pasos nije bio neophodan.\n";
									else if (last_number == 0) std::cout << "bio izvan granica drzave. Pasos je bio neophodan.\n";
									if (izvjestaj == "0")
									{
										std::cout << "Niste dodali izvjestaj za ovu voznju.\n\n";
									}
									else std::cout << "Izvjestaj za ovu voznju je dodat.\n";
								}
							}
						}
					}uFile.close();
				}
				else
				{
					odvozeno = false;
				}

			}
		}dfile.close();
		if (odvozeno == false)
		{
			std::cout << "\nNemate prethodnih voznji.";
		}
		return odvozeno;

	}

	void printNextForDriver()
	{
		std::string driveID, line1, locations, inside_string;
		std::fstream dfile("Drive.txt", std::ios::in);
		if (dfile.is_open())
		{
			while (getline(dfile, line1))
			{
				if (line1.find(this->username) != std::string::npos)
				{
					std::string driveID, tourID, date1, date2, time1, time2, driver, busID, price, izvjestaj, numSeats;
					std::stringstream ss(line1);
					ss >> driveID >> tourID >> driver >> busID >> date1 >> time1 >> date2 >> time2 >> price >> numSeats >> izvjestaj;
					std::fstream uFile("Tours.txt", std::ios::in);
					if (uFile.is_open())
					{
						std::string id2;
						while (getline(uFile, id2, ',') && getline(uFile, locations, ',') && getline(uFile, inside_string))
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
							std::string line1;
							if (tourID == id2)
							{
								std::stringstream ss(line1);
								ss >> driveID >> tourID >> driver >> busID >> date1 >> time1 >> date2 >> time2 >> price >> izvjestaj;
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
									std::cout << "\nPostoji sljedeca voznja: " << driveID << "\n";
									std::cout << inside_string;
									std::cout << std::endl;
									std::cout << "Datum i vrijeme polaska: " << date1 << " " << time1 << std::endl;
									std::cout << "Datum i vrijeme dolaska: " << date2 << " " << time2 << std::endl;
									std::cout << "Putovanje je ";
									if (last_number == 1) std::cout << "unutar granica drzave. Pasos nije neophodan.\n\n";
									else if (last_number == 0) std::cout << "izvan granica drzave. Pasos je neophodan.\n\n";
								}
							}
						}
					}uFile.close();
				}
			}
		}dfile.close();
	}

	/*void set_user_type() override
	{
		this->user_type = "3";
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