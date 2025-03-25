
#include <iostream>
#include <string>
using namespace std;

class Persoana {
protected:
	string nume;
	int varsta;

public:
	Persoana(string nume, int varsta) {
		this->nume = nume;
		this->varsta = varsta;
	}

	void afiseaza_informatii()
	{
		cout << "Nume: " << nume << ", Varsta: " << varsta << endl;
	}

	//definim 2 functii care returneaza numele si varsta unui student
	string getNume() const {
		return nume;
	}
	int getVarsta() const {
		return varsta;
	}

};

//clasa derivata (student)
class Student : public Persoana {
private:
	float medie;
	//clasa prietena
	friend class Admin;
public:
	Student(string nume, int varsta, float medie) : Persoana(nume, varsta) {
		this->medie = medie;
	}

	void afiseaza_informatii()
	{
		cout << "Nume: " << nume << ", Varsta: " << varsta << ", Medie: " << medie << endl;
	}

	//suprascrierea operatorului >
	bool operator>(const Student& celalalt_obiect) const {
		return this->medie > celalalt_obiect.medie;
	}
};

//folosim "&" inseamna ca lucram cu o referinta adica alias pt o variabila existenta - NU O COPIE
class Admin {
public:
	void modifica_medie(Student& s, float nouaMedie) {
		cout << "Modific media pentru " << s.nume << " de la " << s.medie << " la " << nouaMedie << endl;
		s.medie = nouaMedie;
	}

	void afiseaza_detalii_student(const Student& s) {
		cout << "ASMIN -> STUDENT: " << s.nume << ", Varsta: " << s.varsta << ", Medie: " << s.medie << endl;
	}
};

int main() {
	//cream 2 obiecte
	Student s1("Mihai", 20, 7.5);
	Student s2("Victor", 21, 10);
	//afisam informatii despre obiecte
	s1.afiseaza_informatii();
	s2.afiseaza_informatii();
	//adminul modifica media
	Admin admin;
	admin.modifica_medie(s2, 5);
	admin.afiseaza_detalii_student(s2);

	//verificam comparatia
	if (s1 > s2) {
		cout << s1.getNume() << " are media mai mare ca " << s2.getNume() << endl;
	}
	else {
		cout << s2.getNume() << " are media mai mare ca " << s1.getNume() << endl;
	}


}
