#include <iostream>
#include <string>
using namespace std;

// Clasa de baza Animal
class Animal {
protected:  ///pot fi accesate in interiorul aceleasi clase clasei
    string nume;
    int varsta;

public: // pot fi accesate si din afara clasei
    // Constructor
    Animal(string nume, int varsta) {
        this->nume = nume;
        this->varsta = varsta;
    }

    // Metoda pentru afisarea informatiilor
    void afiseaza_informatii() {
        cout << "Nume: " << nume << ", Varsta: " << varsta << endl;
    }

    // Metoda pentru returnarea varstei
    int getVarsta() {
        return varsta;
    }

    // Metoda pentru returnarea numelui
    string getNume() {
        return nume;
    }
};

// Clasa derivata Pasare, mosteneste clasa Animal
class Pasare : public Animal {
private:
    float lungime_aripi;
    int durata_viata;

public:
    // Constructor
    Pasare(string nume, int varsta, float lungime_aripi, int durata_viata) : Animal(nume, varsta) {
        this->lungime_aripi = lungime_aripi;
        this->durata_viata = durata_viata;
    }

    //metoda de afisare
    void afiseaza_informatii() {
        cout << "Pasare - Nume: " << nume << ", Varsta: " << varsta << ", Lungime aripi: " << lungime_aripi << " cm, Durata de viata: " << durata_viata << " ani" << endl;
    }
};

// Clasa derivata Caine, mosteneste clasa Animal
class Caine : public Animal {
private:
    string rasa;
    string tip;

public:
    // Constructor
    Caine(string nume, int varsta, string rasa, string tip)
        : Animal(nume, varsta) {
        this->rasa = rasa;
        this->tip = tip;
    }

    // metoda de afisare
    void afiseaza_informatii() {
        cout << "Caine - Nume: " << nume << ", Varsta: " << varsta
            << ", Rasa: " << rasa << ", Tip: " << tip << endl;
    }
};

int main() {
    int n;
    cout << "Introduceti numarul de animale: ";
    cin >> n;

    // Alocam dinamic un array de pointeri pentru animale
    Animal** gradinaZoologica = new Animal * [n];

    Animal* cel_mai_invarsta = NULL;
    Animal* cel_mai_tanar = NULL;

    // Parcurgem fiecare pozitie din array pentru a introduce un animal
    for (int i = 0; i < n; i++) {
        int tip_animal;
        cout << "Introduceti tipul animalului (1 - Pasare, 2 - Caine): ";
        cin >> tip_animal;

        string nume;
        int varsta;

        cout << "Introduceti numele: ";
        cin >> nume;
        cout << "Introduceti varsta: ";
        cin >> varsta;

        // Verificam ce tip de animal este si cream obiectul corespunzator
        if (tip_animal == 1) {
            float lungime_aripi;
            int durata_viata;
            cout << "Introduceti lungimea aripilor: ";
            cin >> lungime_aripi;
            cout << "Introduceti durata de viata: ";
            cin >> durata_viata;

            // Cream un obiect de tip Pasare și il adaugam în array
            gradinaZoologica[i] = new Pasare(nume, varsta, lungime_aripi, durata_viata);
        }
        else {
            string rasa, tip;
            cout << "Introduceti rasa: ";
            cin >> rasa;
            cout << "Introduceti tipul (vanatoare/ajutor etc.): ";
            cin >> tip;

            // Cream un obiect de tip Caine si il adaugam în array
            gradinaZoologica[i] = new Caine(nume, varsta, rasa, tip);
        }

        // Verificăm cel mai în vârstă și cel mai tânăr animal
        if (cel_mai_invarsta == NULL || gradinaZoologica[i]->getVarsta() > cel_mai_invarsta->getVarsta()) {
            cel_mai_invarsta = gradinaZoologica[i];
        }

        if (cel_mai_tanar == NULL || gradinaZoologica[i]->getVarsta() < cel_mai_tanar->getVarsta()) {
            cel_mai_tanar = gradinaZoologica[i];
        }
    }

    // Afisam informatiile despre animale
    cout << "\nAnimalele din gradina zoologica:" << endl;
    for (int i = 0; i < n; i++) {
        gradinaZoologica[i]->afiseaza_informatii();
    }

    // Eliberam memoria alocata dinamic
    for (int i = 0; i < n; i++) {
        delete gradinaZoologica[i];
    }

    return 0;
}


/*
-Clasă(Class)
Este un "șablon" sau "plan" pentru crearea de obiecte 
Definește caracteristicile(date / atribute)și comportamentele(metode) pe care le vor avea obiectele create din
acea clasă, În exemplul nostru, Animal esteo clasă de bază, iar Pasare și Caine sunt clase derivate
-Constructor
O metodă specială care se apelează automat când se creează un obiect nou
Inițializează datele membrilor clasei
În cod, metodele Animal(string nume, int varsta), Pasare(...) și Caine(...) sunt constructori
-Moștenire (Inheritance)
Permite unei clase să preia caracteristici și comportamente de la o altă clasă
În cod, Pasare : public Animal înseamnă că Pasare moștenește caracteristicile lui Animal
Cuvântul cheie public indică modul de moștenire
-Modificatori de acces
private: Membrii sunt accesibili doar în interiorul aceleiași clase
protected: Membrii sunt accesibili în clasa curentă și în clasele derivate
public: Membrii sunt accesibili de oriunde
-Pointeri
Variabile care stochează adresa de memorie a altei variabile
Animal** gradinaZoologica este un pointer la un array de pointeri către obiecte Animal
Permite manipularea dinamică a obiectelor
-Destructorul:
Este o metodă specială care se apelează automat atunci când un obiect este distrus sau iese din domeniul său de vizibilitate
Are rolul de a elibera resursele alocate dinamic de obiect (memorie, fișiere deschise, conexiuni etc.)
În C++, se definește cu simbolul ~ urmat de numele clasei
Este util pentru a preveni memory leak-urile și a elibera resurse
-Un array este un container care stochează un număr fix de elemente de același tip
 */

