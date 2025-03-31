//3 modificatori
// 1.private: datele sunt accesibile doar in aceeasi clasa
// 3.protected: datele sunt accesibile in aceeasi clasa si in clasele derivate
// 2.public: datele sunt accesibile in aceeasi clasa in clasele derivate (mostenite) si in exterior

#include <iostream>
#include <string>
using namespace std;

class Persoana {
protected:
	string nume;
	int varsta;

public:
	//cream constructor
	Persoana(string nume, int varsta)
	{
		this->nume = nume;
		this->varsta = varsta;
	}

	//metoda de afisare
	void afisare_detalii()
	{
		cout << "Nume: " << nume << ", Varsta: " << varsta << endl;
	}
};

//cream o clasa derivata/mostenita din Clasa Persoana
class Student : public Persoana {
private:
	float medie;

public:
	//constructor:
	Student(string nume, int varsta, float medie) :Persoana(nume, varsta)
	{
		this->medie = medie;
	}

	//suprascrierea metodei de afisare
	
	void afiseaza_informatii()
	{
		cout << "Nume: " << nume << ", Varsta: " << varsta << ", Medie: " << medie << endl;
	}

};

int main()
{
	//cream un obiect de tip student
	Student s("ion", 21, 10);
	s.afiseaza_informatii();

	//cititi de la tastatura un nr de studenti (n)
	//stocati informatiile
	//media tuturor mediilor si afisati o
	int n;
	cout << "Introduceti un numar de studenti: " << endl;
	cin >> n;
	float suma_medii = 0.0;

	Student** studenti = new Student * [n];

	for (int i = 0; i < n; i++) {
		string nume;
		int varsta;
		float medie;

		cout << "Introduceti numele: " << i + 1 << endl;
		cin >> nume;
		cout << "Introduceti varsta: " << i + 1 << endl;
		cin >> varsta;
		cout << "Introduceti media: " << i + 1 << endl;
		cin >> medie;

		studenti[i] = new Student(nume, varsta, medie);

		suma_medii = suma_medii + medie;
	}

	cout << "Studentii introdusi sunt: " << endl;
	for (int i = 0; i < n; i++) {
		studenti[i]->afiseaza_informatii();
	}

	float media_mediilor = suma_medii / n;
	cout << "Media tuturor mediilor este: " << media_mediilor << endl;

	for (int i = 0; i < n; i++)
	{
		delete studenti[i];
	}

	return 0;
}

