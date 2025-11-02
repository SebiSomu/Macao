#include "Pachet.h"
#include "Carte.h"
#include "Jucatori.h"
#include <cstdlib>

using namespace std;

//Macao single player: Utilizator vs AI
void Joc()
{
    srand(time(0));

    Pachet p;
    Jucatori j(p);
    j.startJoc(p);

    const int jucatorUm = 0;
    const int jucatorAI = 1;

    int cartiDeTras = 0; // pt 2/3/Joker
    bool pauza = false;  // pt As
    bool jocInDesfasurare = true;

    while (jocInDesfasurare)
    {
        // --- TURA JUCĂTOR ---
        if (!pauza)
        {
            j.afisareManaJucator();
            cout << "Ultima carte pe gramada: " << j.gramada.top() << "\n";

            bool carteValida = false;
            while (!carteValida)
            {
                cout << "Alege cartea/cartile de jucat sau scrie 'trag': ";
                string input;
                cin >> input;

                if (input == "trag")
                {
                    for (int i = 0; i < max(1, cartiDeTras); i++)
                    {
                        Carte trasa = j.extrageCarteDinPachet(jucatorUm, p);
                        j.adaugaCarte(jucatorUm, trasa);
                        cout << "Ai tras cartea: " << trasa << "\n";
                    }
                    cartiDeTras = 0; // reset după tras
                    carteValida = true;
                    continue;
                }
                else
                {
                    Carte alegere(input);
                    Carte* carteGasita = j.gasesteCarte(jucatorUm, alegere);
                    if (!carteGasita)
                    {
                        cout << "Nu ai aceasta carte in mana!\n";
                        continue;
                    }

                    if (!carteGasita->esteCarteValida(j.gramada.top(), cartiDeTras))
                    {
                        cout << "Carte invalida! Alege alta carte.\n";
                        continue;
                    }

                    if (carteGasita->getValoare() == "2")
                        cartiDeTras += 2;
                    else if (carteGasita->getValoare() == "3") 
                        cartiDeTras += 3;
                    else if (carteGasita->getValoare() == "Joker") 
                        cartiDeTras += 5;
                    else if (carteGasita->getValoare() == "7")
                    {
                        char simbolNou;
                        cout << "Ai jucat 7! Alege simbolul (T/R/N/C): ";
                        cin >> simbolNou;
                        carteGasita->setSimbol(simbolNou);
                    }
                    else if (carteGasita->getValoare() == "A") 
                        pauza = true;

                    j.gramada.push(*carteGasita);
                    j.stergeCarte(jucatorUm, *carteGasita);

                    while (true)
                    {
                        bool maiExista = false;
                        for (auto& c : j.maini[jucatorUm])
                            if (c.getValoare() == alegere.getValoare())
                            {
                                maiExista = true;
                                break;
                            }

                        if (!maiExista) 
                            break;

                        cout << "Doresti sa mai pui o carte cu aceeasi valoare? (da/nu): ";
                        string raspuns;
                        cin >> raspuns;
                        if (raspuns != "da") 
                            break;

                        // citim următoarea carte de același tip exact la fel
                        for (auto& c : j.maini[jucatorUm])
                        {
                            if (c.getValoare() == alegere.getValoare())
                            {
                                // aplicăm efectele
                                if (c.getValoare() == "2")
                                    cartiDeTras += 2;
                                else if (c.getValoare() == "3") 
                                    cartiDeTras += 3;
                                else if (c.getValoare() == "Joker") 
                                    cartiDeTras += 5;
                                else if (c.getValoare() == "7")
                                {
                                    char simbolNou;
                                    cout << "Ai jucat 7! Alege simbolul (T/R/N/C): ";
                                    cin >> simbolNou;
                                    c.setSimbol(simbolNou);
                                }
                                else if (c.getValoare() == "A")
                                    pauza = true;

                                j.gramada.push(c);
                                j.stergeCarte(jucatorUm, c);
                                break; // punem o singură carte per iterație
                            }
                        }
                    }
                    carteValida = true;
                }
            }
            if (j.aCastigat(jucatorUm))
            {
                cout << "Ai castigat!\n";
                break;
            }
        }
        else
        {
            cout << "Tura ta este sarita datorita unui As!\n";
            pauza = false;
        }

        // --- TURA AI ---
        cout << "\n--- Tura AI ---\n";
        if (!pauza)
        {
            j.afisareManaAI();
            map<string, vector<Carte>> grupare;
            for (auto& c : j.maini[jucatorAI])
            {
                if (c.esteCarteValida(j.gramada.top(), cartiDeTras))
                    grupare[c.getValoare()].push_back(c);
            }

            vector<Carte> deJucat;
            for (auto& [val, v] : grupare)
                if (v.size() > deJucat.size())
                    deJucat = v;

            if (!deJucat.empty())
            {
                for (auto& c : deJucat)
                {
                    if (c.getValoare() == "2")
                        cartiDeTras += 2;
                    else if (c.getValoare() == "3")
                        cartiDeTras += 3;
                    else if (c.getValoare() == "Joker") 
                        cartiDeTras += 5;
                    else if (c.getValoare() == "7")
                    {
                        Carte copie = c;
                        map<char, int> frecventaSimboluri;
                        for (auto& carte : j.maini[jucatorAI])
                            frecventaSimboluri[carte.getSimbol()]++;

                        char simbolNou = 'T';
                        int maxCount = -1;
                        for (auto& [simbol, count] : frecventaSimboluri)
                        {
                            if (count > maxCount)
                            {
                                maxCount = count;
                                simbolNou = simbol;
                            }
                        }

                        if (maxCount <= 0)
                        {
                            char simbolNoues[] = { 'T','R','N','C' };
                            simbolNou = simbolNoues[rand() % 4];
                        }
                        
                        copie.setSimbol(simbolNou);
                        cout << "AI a jucat 7 si a ales simbolul: " << copie.getSimbol() << "\n";

                        j.gramada.push(copie);       
                        j.stergeCarte(jucatorAI, c); 
                        continue;
                    }
                    else if (c.getValoare() == "A") 
                        pauza = true;

                    j.gramada.push(c);
                    j.stergeCarte(jucatorAI, c);
                    continue;
                }
                cout << "AI a jucat: ";
                for (auto& c : deJucat)
                    cout << c;
                cout << "\n";
            }
            else
            {
                for (int i = 0; i < max(1, cartiDeTras); i++)
                {
                    Carte trasa = j.extrageCarteDinPachet(jucatorAI, p);
                    j.adaugaCarte(jucatorAI, trasa);
                }
                cout << "AI a tras " << max(1, cartiDeTras) << " carte/carti.\n";
                cartiDeTras = 0;
            }

            if (j.aCastigat(jucatorAI))
            {
                cout << "AI a castigat!\n";
                jocInDesfasurare = false; // ieșim din while principal
            }
        }
        else
        {
            cout << "Tura AI este sarita datorita unui As!\n";
            pauza = false;
        }
    }
}

int main()
{
    Joc();
    return 0;
}
