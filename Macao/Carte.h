#pragma once
#include <iostream>
#include <string>
#include "Pachet.h"

using std::string;

class Carte
{
private:
	string valoare;
	char simbol;
	bool isJoker;

public:
	Carte() : valoare(""), simbol('?'), isJoker(false) {} //constructor implicit

	Carte(const string& s) //constructor cu parametru pentru citire
	{
		if (s == "Joker")
		{
			valoare = "Joker";
			simbol = '\0';
			isJoker = true;
		}
		else if (s.size() == 3)
		{
			valoare = s.substr(0, 2);
			simbol = s[2];
			isJoker = false;
		}
		else
		{
			valoare = s.substr(0, 1);
			simbol = s[1];
			isJoker = false;
		}
	}

	bool getIsJoker() const 
	{
		return isJoker;
	}

	string getValoare() const
	{
		return valoare;
	}

	char getSimbol() const
	{
		return simbol;
	}

	void setSimbol(char s) 
	{ 
		simbol = s; 
	}

	bool poateFiJucata(const Carte& topGramada, bool obligativUmflat = false) const
	{
		if (obligativUmflat)
			return (valoare == "2" || valoare == "3" || isJoker);

		if (isJoker || valoare == "7")
			return true;

		if (topGramada.isJoker)
			return true;

		return (valoare == topGramada.valoare || simbol == topGramada.simbol);
	}

	bool esteCarteValida(const Carte& ultima, int cartiDeTras) const
	{
		bool obligativUmflat = (cartiDeTras > 0);
		return poateFiJucata(ultima, obligativUmflat);
	}

	bool operator==(const Carte& other) const
	{
		return valoare == other.valoare && simbol == other.simbol;
	}

	friend std::ostream& operator<<(std::ostream& out, Carte& c)
	{
		out << c.valoare << c.simbol << " ";
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Carte& c)
	{
		string s;
		in >> s;
		if (s == "Joker")
		{
			c.valoare = "Joker";
			c.simbol = '\0';
			c.isJoker = true;
		}
		else if (s.size() == 3)
		{
			c.valoare = s.substr(0, 2);
			c.simbol = s[2];
			c.isJoker = false;
		}
		else
		{
			c.valoare = s.substr(0, 1);
			c.simbol = s[1];
			c.isJoker = false;
		}
		return in;
	}

};