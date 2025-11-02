#pragma once
#include "Pachet.h"
#include "Carte.h"
#include <map>

using namespace std;

class Jucatori
{

public:
	map<int, vector<Carte>> maini;
	stack<Carte> gramada;

	Jucatori(Pachet& p)
	{
		const int nrJucatori = 2;
		for (int k = 0; k < 5; k++)
			for (int ID = 0; ID < nrJucatori; ID++)
			{
				Carte trasa = extrageCarteDinPachet(ID, p); 
				maini[ID].push_back(trasa);
			}
	}

	Carte* gasesteCarte(int jucatorID, const Carte& c)
	{
		auto it = maini.find(jucatorID);
		if (it == maini.end())
			return nullptr; // jucător inexistent

		for (auto& carte : it->second)
			if (carte == c)
				return &carte; // returnăm pointer la carte

		return nullptr; // cartea nu există în mână
	}

	void startJoc(Pachet& p)
	{
		if (!p.teanc.empty()) 
		{
			Carte prima = extrageCarteDinPachet(-1, p); // -1 = nu contează jucător
			gramada.push(prima);
		}
	}

	void stergeCarte(int jucatorID, const Carte& c)
	{
		auto it = maini.find(jucatorID);
		if (it == maini.end())
			return; // jucător inexistent

		for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
		{
			if (*iter == c)  // folosim operator== definit în Carte
			{
				it->second.erase(iter);
				break; // ștergem doar prima apariție
			}
		}
	}

	Carte extrageCarteDinPachet(int jucator, Pachet& p)
	{
		if (p.teanc.empty())
		{
			cout << "Teancul s-a golit, reimprospatam teancul...\n";

			Carte ultima = gramada.top();
			gramada.pop();

			while (!gramada.empty())
			{
				Carte c = gramada.top();
				gramada.pop();
				p.teanc.push(c);
			}

			gramada.push(ultima);
			p.amestecare();
		}

		Carte trasa = p.teanc.top();
		p.teanc.pop();
		return trasa;
	}


	void afisareManaJucator()
	{
		int jucatorID = 0; // tu ești jucătorul 0
		cout << "Cartile tale actuale:\n";
		for (auto& c : maini[jucatorID])
			cout << c;
		cout << "\n";
	}

	void afisareManaAI()
	{
		int jucatorID = 1; // tu ești jucătorul 0
		cout << "Cartile tale actuale:\n";
		for (auto& c : maini[jucatorID])
			cout << c;
		cout << "\n";
	}

	void adaugaCarte(int jucatorID, const Carte& c)
	{
		maini[jucatorID].push_back(c);
	}

	bool aCastigat(int jucatorID)  // verifică dacă jucătorul a rămas fără cărți
	{
		return maini[jucatorID].empty();
	}
};