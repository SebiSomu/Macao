#pragma once
#include "Carte.h"
#include <fstream>
#include <vector>
#include <stack>
#include <array>
#include <ctime>
#include <algorithm>

using namespace std;

class Pachet
{
private:
	array<Carte, 54> pachet;

public:
	stack<Carte> teanc; //folosit in timpul jocului
	Pachet()
	{
		citirePachet();
		amestecare();
		taiere();
		for (int i = pachet.size() - 1; i >= 0; i--)
			teanc.push(pachet[i]);
	}

	void citirePachet()
	{
		string s;
		ifstream fin("pachet.txt");
		int i = 0;
		while (fin >> s && i < 54)
		{
			pachet[i] = Carte(s);
			i++;
		}
	}

	void amestecare()
	{
		srand(time(0));
		for (int i = pachet.size() - 1; i > 0; i--)
		{
			int j = rand() % (i + 1);
			swap(pachet[i], pachet[j]);
		}
	}

	bool esteGol() const
	{
		return pachet.empty();
	}

	void taiere()
	{
		int j = rand() % pachet.size();
		rotate(pachet.begin(), pachet.begin() + j, pachet.end());
	}

	void afisarePachet()
	{
		stack<Carte> copie = teanc;
		while (!copie.empty())
		{
			Carte c = copie.top();
			cout << c;
			copie.pop();
		}
		cout << "\n";
	}

	void adaugaCarte(const Carte& c)
	{
		teanc.push(c);
	}
};
