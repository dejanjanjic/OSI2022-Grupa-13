#pragma once
#include <fstream>
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
	
	void menu()
	{
		std::string option;
		do
		{
			std::cout << "\nIzaberite unosenjem broja zeljenu opciju:\n\n";
			std::cout << "1.) Pretrazivanje voznji\n";
			std::cout << "2.) Unos poklon bona\n";
			std::cout << "--> ";
			std::cin >> option;
			if (option == "1")
			{
				std::cout << "Kasnije" <<std::endl;
			}
			else if (option == "2")
			{
				insertCoupon();
			}

		} while (option != "1" && option != "2");
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
				}while(option != "1" || option != "2");

			}

		}
	}
};