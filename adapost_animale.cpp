#include <iostream>
#include <string>
using namespace std;

class Animal {
protected:
	string nume;
	int varsta;
public:
	Animal(string nume, int varsta) {
		this->nume = nume;
		this->varsta = varsta;
	}
	~Animal() {
		cout << "Animalul " << nume << " a fost scos din evidenta." << endl;
	}
	void afiseaza_detalii() {
		cout << "Animal: " << nume << ", Varsta: " << varsta << " ani" << endl;
	}
	friend class Ingrijitor;
	friend class Persoana;
};

class Caine :public Animal {
protected:
	string rasa;
	float greutate;
	string talie;
public:
	Caine(string nume, int varsta, string rasa, float greutate, string talie) :Animal(nume, varsta) {
		this->rasa = rasa;
		this->greutate = greutate;
		this->talie = talie;
	}
	void afiseaza_detalii() {
		cout << "Caine: " << nume << ", Varsta: " << varsta << " ani, Rasa: " << rasa << ", Greutate: " << greutate << ", Talie: " << talie << endl;
	}
};

class Pisica :public Animal {
protected:
	string culoare;
	bool sterilizata;
	bool blana;
public:
	Pisica(string nume, int varsta, string culoare, bool sterilizata, bool blana) :Animal(nume, varsta) {
		this->culoare = culoare;
		this->sterilizata = sterilizata;
		this->blana = blana;
	}
	void afiseaza_detalii() {
		cout << "Pisica: " << nume << ", Varsta: " << varsta << " ani, Culoare: " << culoare << ", Sterilizata: " << (sterilizata ? "Da" : "Nu") << ", Blana: " << (blana ? "Da" : "Nu") << endl;
	}
};

class Ingrijitor {
public:
	void hraneste(Animal* animalH) {
		cout << animalH->nume << " a fost hranit" << endl;
	}
};

class Persoana {
public:
	void adopta(Animal*& animalA) {
		cout << animalA->nume << " a fost adoptat" << endl;
		delete animalA;
		animalA = nullptr;
	}
};

int main() {
	int n;
	cout << "Introduceti numarul de animale din adapost: ";
	cin >> n;
	Animal** animale = new Animal * [n];

	for (int i = 0; i < n; i++) {
		int tip;
		cout << "Alegeti tipul animalului (1 - Caine, 2 - Pisica): ";
		cin >> tip;
		string nume;
		int varsta;
		cout << "Introduceti numele: ";
		cin >> nume;
		cout << "Introduceti varsta: ";
		cin >> varsta;

		if (tip == 1) {
			string rasa;
			cout << "Introduceti rasa: ";
			cin >> rasa;
			float greutate;
			cout << "Introduceti greutatea (kg): ";
			cin >> greutate;
			string talie;
			cout << "Introduceti talia: ";
			cin >> talie;
			animale[i] = new Caine(nume, varsta, rasa, greutate, talie);
		}
		else {
			string culoare;
			cout << "Introduceti culoarea: ";
			cin >> culoare;
			bool sterilizata;
			cout << "Introduceti sterilizata(1-Da, 0-Nu): ";
			cin >> sterilizata;
			bool blana;
			cout << "Introduceti daca are blana(1-Da, 0-Nu): ";
			cin >> blana;
			animale[i] = new Pisica(nume, varsta, culoare, sterilizata, blana);
		}
	}

	cout << endl << "Lista animalelor:" << endl;
	for (int i = 0; i < n; i++) {
		if (animale[i]) {
			cout << "Index " << i << ": ";
			animale[i]->afiseaza_detalii();
		}
	}
	Ingrijitor ingrijitor;
	Persoana persoana;
	int actiune;
	do {
		cout << endl << "Ce doriti sa faceti?" << endl;
		cout << "1. Hraniti un animal" << endl;
		cout << "2. Adoptati un animal" << endl;
		cout << "3. Iesiti" << endl;
		cout << "Alegeti o actiune (1/2/3): ";
		cin >> actiune;

		if (actiune == 1 || actiune == 2) {
			cout << "Alegeti indexul animalului (de la 0 la " << n - 1 << "): ";
			int index;
			cin >> index;

			if (index >= 0 && index < n) {
				if (actiune == 1) {
					ingrijitor.hraneste(animale[index]);
				}
				else {
					persoana.adopta(animale[index]);
					animale[index] = nullptr;
				}
			}
			else {
				cout << "Index invalid!" << endl;
			}
		}
	} while (actiune != 3);
	return 0;
}