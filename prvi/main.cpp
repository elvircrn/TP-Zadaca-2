#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <exception>
#include <cstdio>
#include <stdexcept>
#include <complex>
#include <climits>
#include <string>
#include <sstream>
#include <cctype>

bool parseNumber(std::string text, int &number)
{
	number = 0;
	int index = text.length() - 1, pow = 1;
	while (isdigit (text [index]))
	{
		number += (pow * (text [index] - '0'));
		index--;
		pow *= 10;
	}

	if (text [index] == '-')
	{
		number = -number;
		index--;
	}

	if (index == 0 && text [index] == 'I')
		return true;
	else
		return false;
}

std::string clearTraling(const std::string &text)
{
	std::string ret;
	int left, right;

	for (left = 0; left < text.length(); left++)
		if (text [left] != ' ' && text [left] != '\n')
			break;

	for (right = text.length() - 1; right > -1 && right >= left; right--)
		if (text [right] != ' ' && text [right] != '\n')
			break;

	return text.substr(left, (right - left + 1));
}

template <typename T>
std::string toString (const T &n)
{
	std::ostringstream stmc;
	stmc << n;
	return stmc.str();
}

std::string toString(int x, int y)
{
	return "(" + toString(x) + "," + toString(y) + ")";
}

enum class Smjer { Nalijevo, Nadesno };
enum class Pravci { Sjever, Istok, Jug, Zapad };
enum class Komande { Aktiviraj, Deaktiviraj, Nalijevo, Nadesno, Idi, Kraj };
enum class KodoviGresaka { PogresnaKomanda, NedostajeParametar, SuvisanParametar, NeispravanParametar };
enum class Status { Aktivan, Neaktivan };

Status currentStatus;

void rotate(Pravci &p)
{
	if (p == Pravci::Sjever)
		p = Pravci::Istok;
	else if (p == Pravci::Istok)
		p = Pravci::Jug;
	else if (p == Pravci::Jug)
		p = Pravci::Zapad;
	else if (p == Pravci::Zapad)
		p = Pravci::Sjever;
}

std::string toString (Status s)
{
	if (s == Status::Aktivan)
		return "aktivan";
	else if (s == Status::Neaktivan)
		return "neaktivan";
}

std::string toString(Pravci s)
{
	if (s == Pravci::Sjever)
		return "sjever";
	else if (s == Pravci::Istok)
		return "istok";
	else if (s == Pravci::Jug)
		return "jug";
	else if (s == Pravci::Zapad)
		return "zapad";
	else
		return "wut";
}

bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske)
{
	std::cout << "Unesi komandu: ";

	std::string input;
	std::getline(std::cin, input);
	input = clearTraling(input);

	if (input == "A+")
	{
		komanda = Komande::Aktiviraj;
		return true;
	}
	else if (input == "A-")
	{
		komanda = Komande::Deaktiviraj;
		return true;
	}
	else if (input.substr(0, 2) == "A+" || input.substr(0, 2) == "A-")
    {
        kod_greske = KodoviGresaka::SuvisanParametar;
        return false;
    }
	else if (input == "A")
	{
		kod_greske = KodoviGresaka::NedostajeParametar;
		return false;
	}
	else if (input [0] == 'A')
	{
		kod_greske = KodoviGresaka::NeispravanParametar;
		return false;
	}
	else if (input == "D")
	{
		komanda = Komande::Nadesno;
		return true;
	}
	else if (input [0] == 'D')
    {
        kod_greske = KodoviGresaka::SuvisanParametar;
        return false;
    }
	else if (input == "L")
	{
		komanda = Komande::Nalijevo;
		return true;
	}
	else if (input [0] == 'L')
    {
        kod_greske = KodoviGresaka::SuvisanParametar;
        return false;
    }
	else if (input == "K")
	{
		komanda = Komande::Kraj;
		return true;
	}
    else if (input [0] == 'K')
    {
        kod_greske = KodoviGresaka::SuvisanParametar;
        return false;
    }
    else if (input == "I")
    {
        kod_greske = KodoviGresaka::NedostajeParametar;
        return false;
    }
	else if (input [0] == 'I')
	{
		if (parseNumber(input, parametar) == false)
		{
		 	kod_greske = KodoviGresaka::NeispravanParametar;
			return false;
		}
		komanda = Komande::Idi;
		return true;
	}

	if (input [0] != 'A' && input [0] != 'L' && input [0] != 'K' && input [0] != 'I' && input [0] != 'D')
		kod_greske = KodoviGresaka::PogresnaKomanda;

	return false;
}

void AktivirajRobota()
{
	currentStatus = Status::Aktivan;
}

void DeaktivirajRobota()
{
	currentStatus = Status::Neaktivan;
}

void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu)
{
	if (na_koju_stranu == Smjer::Nadesno)
	{
		if (orijentacija == Pravci::Sjever)
			orijentacija = Pravci::Istok;
		else if (orijentacija == Pravci::Istok)
			orijentacija = Pravci::Jug;
		else if (orijentacija == Pravci::Jug)
			orijentacija = Pravci::Zapad;
		else if (orijentacija == Pravci::Zapad)
			orijentacija = Pravci::Sjever;
	}
	else
	{
		if (orijentacija == Pravci::Sjever)
			orijentacija = Pravci::Zapad;
		else if (orijentacija == Pravci::Istok)
			orijentacija = Pravci::Sjever;
		else if (orijentacija == Pravci::Jug)
			orijentacija = Pravci::Istok;
		else if (orijentacija == Pravci::Zapad)
			orijentacija = Pravci::Jug;
	}
}

void Idi(int &x, int &y, Pravci orijentacija, int korak)
{
	if (orijentacija == Pravci::Sjever)
		y += korak;
	else if (orijentacija == Pravci::Jug)
		y -= korak;
	else if (orijentacija == Pravci::Zapad)
		x -= korak;
	else if (orijentacija == Pravci::Istok)
		x += korak;
}

void IspisiPoziciju(int x, int y, Pravci orijentacija)
{
	std::cout << "Robot je trenutno " << toString (currentStatus) << ", nalazi se na poziciji " << toString (x, y) << " i gleda na " << toString (orijentacija) << "." << std::endl;
}

void PrijaviGresku(KodoviGresaka kod_greske)
{
	if (kod_greske == KodoviGresaka::PogresnaKomanda)
		std::cout << "Nerazumljiva komanda!" << std::endl;
	else if (kod_greske == KodoviGresaka::NedostajeParametar)
		std::cout << "Komanda trazi parametar koji nije naveden!" << std::endl;
	else if (kod_greske == KodoviGresaka::NeispravanParametar)
		std::cout << "Parametar komande nije ispravan!" << std::endl;
	else if (kod_greske == KodoviGresaka::SuvisanParametar)
		std::cout << "Zadan je suvisan parametar nakon komande!" << std::endl;
}

void finish()
{
	std::cout << "Dovidjenja!\n";
	exit(0);
}

void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija)
{
	if (komanda == Komande::Aktiviraj)
		AktivirajRobota();
	else if (komanda == Komande::Deaktiviraj)
		DeaktivirajRobota();
	else if (komanda == Komande::Kraj)
		finish();

	if (currentStatus == Status::Neaktivan)
        return;

	if (komanda == Komande::Nalijevo)
		Rotiraj(orijentacija, Smjer::Nalijevo);
	else if (komanda == Komande::Nadesno)
		Rotiraj(orijentacija, Smjer::Nadesno);
	else if (komanda == Komande::Idi)
		Idi(x, y, orijentacija, parametar);
}

int main()
{
	int x = 0, y = 0, param;
	Pravci orijentacija = Pravci::Sjever;
	Komande komanda;
	KodoviGresaka gr;

	currentStatus = Status::Aktivan;
    IspisiPoziciju(x, y, orijentacija);

	while (true)
	{
		if (UnosKomande(komanda, param, gr) == false)
            PrijaviGresku(gr);
		else
        {
            IzvrsiKomandu(komanda, param, x, y, orijentacija);
            IspisiPoziciju(x, y, orijentacija);
        }
	}

	return 0;
}





