#include <iostream>
#include <string>
using namespace std;
//Clase
int v[100];

class student {
private:
	string nume;
	int varsta;
	float medie;
public:
	//Constructori cu var aux
	student(string nume_student, int varsta_student, float medie_student)
	{
		nume = nume_student;
		varsta = varsta_student;
		medie = medie_student;
		cout << "Constructorul a fost apelat pentru: " << nume << endl;
	}
	//Constructor folosind This
	/*student(string nume, int varsta, float medie) {
		this->nume = nume;
		this-> varsta = varsta;
		this->medie = medie;
		cout << "C0nstructul a fost apelat pentru: " << nume << endl;
	}*/
	~student()
	{
		cout << "Destructorul a fost apelat pentru:" << nume << endl;
	}
	void afisare_informatii()
	{
		cout << "nume: " << nume << " Varsta: " << varsta << " Medie: " << medie << endl;
	}
	float mmedie()
	{
		return medie;
	}
};

int main()
{
	int i, k;
	int cmedie = -1, z;
	int n = 0;
	cout << "Introduceti numarul de studenti "; cin >> k;
	n = k;
	student** studenti = new student * [n];
	for (int i = 0; i < n; i++)
	{
		string nume;
		int varsta;
		float medie;
		cout << "Introdu numele studentului " << i + 1 << ": "; cin >> nume;
		cout << "Introdu varsta studentului " << i + 1 << ": "; cin >> varsta;
		cout << "Introdu media studentului " << i + 1 << ": "; cin >> medie;
		if (medie > cmedie)
			cmedie = -1, z = i;
		studenti[i] = new student(nume, varsta, medie);

	}

	for (int i = 0; i < n; i++)
	{
		studenti[i]->afisare_informatii();
	}

	cout << "Studentul cu cea mai mare medie este: ";
	studenti[z]->afisare_informatii();
	cout << endl;


	//sortare studenti dupa medie
	bool ok = 0;
	do
	{
		ok = 1;
		for (int i = 0; i < n; i++)
			if (studenti[i]->mmedie() > studenti[i + 1]->mmedie())
			{
				student* aux = studenti[i];
				studenti[i] = studenti[i + 1];
				studenti[i + 1] = aux;
				ok = 0;
			}
	} while (!ok);

	cout << endl << endl;
	for (int i = 0; i < n; i++)
	{
		studenti[i]->afisare_informatii();
	}

	for (int i = 0; i < n; i++)
	{
		delete studenti[i];
	}


	return 0;
}