#include <iostream>
#include "Driver.h"
#include "Admin.h"
#include "Person.h"
#include "User.h"
#include <fstream>
#include <cstdlib>
#include "validate.h"
#include "manipulate.h"

//METODU ZA REGISTRACIJU, PARAMETAR TYPE ODREDJUJE KAKAV NALOG CE SE NAPRAVITI "1" ZA KORISNICKI, "2" ZA ADMIN, "3" ZA VOZACKI, UNUTRA IMAJU SVE VALIDACIJE ITD
bool Register(std::string type)
{
	int counter = 0;
	std::string name, surname, password, username;

	do
	{
		
		
		std::cout << "Unesite ime: " << std::endl;
		std::cin >> name;
		std::cout << "Unesite prezime: " << std::endl;
		std::cin >> surname;
		std::cout << "Unesite korisnicko ime: " << std::endl;
		std::cin >> username;
		std::cout << "Unesite lozinku: " << std::endl;
		std::cin >> password;

		system("cls");

		if (!check_name_or_surname(name)) { std::cout << "Ime nije u odgovarajucem formatu"<<std::endl; counter = 0; }
		else { counter++; }
		if (!check_name_or_surname(surname)) { std::cout << "Prezime nije u odgovarajucem formatu"<<std::endl; counter = 0; }
		else { counter++; }
		if (!check_password(password)) { std::cout << "Lozinka nije u odgovarajucem formatu"<<std::endl; counter = 0; }
		else { counter++; }
		if (!check_username(username)) { std::cout << "Korisnicko ime vec postoji ili je prekratko" << std::endl; counter = 0; }
		else { counter++; }
		
		if (counter != 4) { std::cout << std::endl << "Probajte ponovo\n" << std::endl; }

	} while (counter != 4);



	std::fstream file("Users.txt", std::ios::in | std::ios::out | std::ios::app);

	file << name << " " << surname << " " << username << " " << password << " " << type << " " << "false"<<"\n";
	return 1;

}

//METODA ZA LOGIN KOJA VRACA ODREDJENI OBJEKAT NA OSNOVU TIPA
template<typename T>
T Login(std::string username, std::string password)
{
	
	std::fstream file("Users.txt", std::ios::in);
	int n = num_of_lines("Users.txt");		
	
	std::string out;
    std::string name, surname,type;

	for (int i = 0; i < n; i++)
	{
		int check = 0;

		for (int j = 0; j < 5; j++)
		{
			file >> out;
			if (j == 0) { name = out; }
			
			if (j == 1) { surname = out; }

			if (j == 4) { type = out; }

			if ((j == 2) && (out == username))
			{
				check++;
			}
		
			if ((j == 3) && (out == password))
			{
				check++;
			}

		}
			if (check == 2) 
			{ 
				  return T(name, surname, username, password); 
			}
			
	}

	return T("#", "#", "#", "#");
	
}

//METODA KOJA DAJE POCETNI EKRAN PRI PALJENJU APLIKACIJE
int StartPage()
{
	std::cout << "Dobrodosli, vas TravelSolutions\n";
	std::cout << "\nIzaberite unosenjem broja zeljenu opciju: \n\n";
	std::cout << "1.) Prijava\n";
	std::cout << "2.) Registracija\n\n";
	std::cout << "--> ";
	int option;
	std::cin >> option;
	return option;
}



int main()
{
	std::cout << num_of_lines("Users.txt");
	int option = StartPage();
	std::string username, password;
	system("cls");

	User current_user;
	Admin current_admin;
	Driver current_driver;

	int stop_login = 0;

	// OPTION 1: LOGIN
	//NAKON STO SE PRAVILNO UNESU PODACI IZ METODE LOGIN SE DOBIJAJU SVI POTREBNI PODACI O ULOGOVANOM KORISNIKI
	//ONA TRI NAVEDENA TIPA SU RASPODELJENA U 3 IF-A DOLE
	//SVE STO SE RADI ZA VOZACA TREBA DA IDE U IF TYPE==3, ZA ADMINA IF TYPE==2 I KORISNIKA TYPE==1
	//OVO JE OBAVEZNO JER VAM PROMENJIVE CURRENT_DRIVER, CURRENT_ADMIN I CURRENT_USER IMAJU ZIVOTNI VIJEK SAMO
	//U SVOM IF-U
	if (option == 1)
	{
		do
		{
			
			std::cout << "Unesite vase korisnicko ime: \n";
			std::cin >> username;
			std::cout << "Unesite vasu lozinku: \n";
			std::cin >> password;

			if ((username == "admin") && (password == "admin") && (num_of_lines("Users.txt") == 1)) { delete_line("admin"); option = 2; system("cls"); break; }

			std::string type = getUserType(username);
			if (type == "1")
			{
				system("cls");
			    current_user = Login<User>(username, password);
				if (current_user.get_username() != "#")
				{
					current_user.set_user_type();
					stop_login++;
					std::cout << current_user.get_name() << std::endl << current_user.get_user_type();
				}
				

			}
			if (type == "2")
			{
				system("cls");
				current_admin = Login<Admin>(username, password);
				if (current_admin.get_username()!= "#")
				{
					current_admin.set_user_type();
					stop_login++;

					int option_admin;

					std::cout << "Dobrodosli nazad, admine\n\n\n";
					std::cout << "Izaberite neku od datih opcija: \n\n";
					std::cout << "1.) Kreiranje naloga za vozace\n";
					std::cout << "2.) Brisanje naloga\n";
					std::cout << "3.) Deaktivacija naloga\n";
					std::cout << "4.) Aktivacija nalog\n";
					std::cout << "\n--> ";
					std::cin >> option_admin;

					system("cls");
					if (option_admin == 1)
					{
						Register("3");
					}
					if (option_admin == 2)
					{
						std::cout << "Unesite korisnicko ime naloga koji zelite obrisati: ";
						std::string delete_name;
						std::cin >> delete_name;
						if (manipulate_at(delete_name) != 0)
						{
							system("cls");
							std::cout <<"Korisnik "<< delete_name << " je uspjesno izbrisan iz baze\n";
							delete_line(delete_name);
						}
						else
						{
							system("cls");
							std::cout << "Korisnik ne postoji ili pokusavate izbrisati administratorski nalog\n";
						}
					}
					if (option_admin == 3)
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
					}
					if (option_admin == 4)
					{
						std::cout << "Unesite korisnicko ime naloga koji zelite aktivirati: ";
						std::string activate_name;
						std::cin >> activate_name;
						if ((manipulate_at(activate_name) != 0) && (suspend_at(activate_name) != 0))
						{
							system("cls");
							std::cout << "Korisnik " << activate_name << " je uspjesno aktiviran\n";
						}
						else
						{
							system("cls");
							std::cout << "Korisnik ne postoji ili pokusavate aktivirati nesuspendovan nalog\n";
						}
					}
				}
				

			}
			if (type == "3")
			{
				system("cls");
			    current_driver = Login<Driver>(username, password);
				if (current_driver.get_username() != "#")
				{
					current_driver.set_user_type();
					stop_login++;
					std::cout << current_driver.get_name() << std::endl << current_driver.get_user_type();
				}
				

			}
			
			if (stop_login == 0)
			{
			  system("cls");
              std::cout << "Pogresno korisnicko ime ili lozinka, probajte ponovo!\n\n";
			  
			}
			
				
		} while (stop_login==0);
		
		 
	
	}
	//OPTION 2
	//REGISTER
	//PROSTO SAMO INTERFEJS ZA METODU REGISTER
	//TAKODJE IMA ODRADJEN I SLUCAJ AKO JE ADMINU PRVA PRIJAVA
	//DA MU SE TRAZI PRVA REGISTRACIJA 
	if (option == 2)
	{
		bool passed;

		if (num_of_lines("Users.txt") == 0)
		{
			passed = Register("2");
		}
		else
		{
			passed = Register("1");
		}
	    

		if (passed)
		{
			system("cls");
			std::cout << "\n\nUspjesno ste se registrovali!!\n";
			std::cout << "   Za ulazak na sistem nakon registracije, neophodno ga je ponovno pokrenuti!!\n\n";
			return 0;
			
		}
		
	}//moze se dodati da se ide na prijavu posle registracije odmah

	
	

}