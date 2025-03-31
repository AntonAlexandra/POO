#include <iostream>
#include <string>

using namespace std;

// Clasa pentru data si timp
class DataOra {
private:
    int zi;
    int luna;
    int an;
    int ora;
    int minut;

public:
    // Constructor
    DataOra() {
        zi = 1;
        luna = 1;
        an = 2025;
        ora = 0;
        minut = 0;
    }

    // Constructor
    DataOra(int z, int l, int a, int o, int m) {
        zi = z;
        luna = l;
        an = a;
        ora = o;
        minut = m;
    }

    void citeste() {
        cout << "Ziua: ";
        cin >> zi;
        cout << "Luna: ";
        cin >> luna;
        cout << "Anul: ";
        cin >> an;
        cout << "Ora: ";
        cin >> ora;
        cout << "Minutul: ";
        cin >> minut;
    }

    // Metoda pentru afisare
    void afiseaza() const {
        cout << zi << "/" << luna << "/" << an << " " << ora << ":" << minut;
    }

    // Metoda pentru calcularea diferentei in minute
    int diferentaMinute(const DataOra& alt) const {
        // Convertim totul in minute pentru calcul simplu
        int minuteAcest = ((an * 365 + luna * 30 + zi) * 24 + ora) * 60 + minut;
        int minuteAlt = ((alt.an * 365 + alt.luna * 30 + alt.zi) * 24 + alt.ora) * 60 + alt.minut;
        return minuteAlt - minuteAcest;
    }
};

// Clasa pentru vehicul
class Vehicul {
private:
    string numar;
    DataOra sosire;
    bool esteInParcare;

public:
    // Constructor
    Vehicul() {
        numar = "";
        esteInParcare = false;
    }

    // Constructor
    Vehicul(string nr, DataOra sos) {
        numar = nr;
        sosire = sos;
        esteInParcare = true;
    }

    // Getter pentru numar - getter -> permite citirea valorii unui atribut privat fără a permite modificarea acestuia
    string getNumar() const {
        return numar;
    }

    // Getter pentru sosire
    DataOra getSosire() const {
        return sosire;
    }

    // Getter pentru stare
    bool getEsteInParcare() const {
        return esteInParcare;
    }

    // Setter pentru numar - setter -> ofera acces controlat la atributele private
    void setNumar(string nr) {
        numar = nr;
    }

    // Setter pentru sosire
    void setSosire(DataOra sos) {
        sosire = sos;
    }

    // Setter pentru stare
    void setEsteInParcare(bool stare) {
        esteInParcare = stare;
    }

    // Getter + Setter -> ofera un mod controlat de a interactiona cu starea interna a unui obiect
 
    // Metoda pentru afisarea informatiilor despre vehicul
    void afiseaza() const {
        cout << "Numar inmatriculare: " << numar << " | Ora sosirii: ";
        sosire.afiseaza();
    }
};

// Clasa pentru istoricul iesirilor din parcare
class IstoricIesire {
private:
    string numar;
    DataOra sosire;
    DataOra plecare;
    double cost;

public:
    // Constructor
    IstoricIesire() : sosire(), plecare () {
        numar = "";
        cost = 0.0;
    }

    // Constructor
    IstoricIesire(string nr, DataOra sos, DataOra ple, double c) {
        numar = nr;
        sosire = sos;
        plecare = ple;
        cost = c;
    }

    // Metoda pentru afisarea informatiilor despre iesire
    void afiseaza() const {
        cout << "Numar inmatriculare: " << numar << " | Cost: " << cost << " RON";
    }
};

// Clasa pentru parcare
class Parcare {
private:
    int numarTotalLocuri = 0;
    int locuriDisponibile = 0;
    double tarifPeOra = 0.0;
    Vehicul* vehiculeParcate;
    IstoricIesire* istoric;
    int maxVehicule;
    int numarVehiculeParcate;
    int numarIstoric;

public:
    // Constructor
    Parcare(int locuri, double tarif, int maxVeh)
        : numarTotalLocuri(locuri), locuriDisponibile(locuri),
        tarifPeOra(tarif), maxVehicule(maxVeh), numarVehiculeParcate(0), numarIstoric(0) {

        vehiculeParcate = new Vehicul[maxVehicule](); // Inițializare cu valori default
        istoric = new IstoricIesire[maxVehicule]();
    }

    // Destructor pentru eliberarea memoriei
    ~Parcare() {
        delete[] vehiculeParcate;
        delete[] istoric;
    }

    void afiseazaStatistici() const {
        cout << "Locuri disponibile: " << locuriDisponibile << "/" << numarTotalLocuri << "\n";
    }

    void adaugaVehicul(string numar, DataOra sosire) {
        if (locuriDisponibile > 0) {
            vehiculeParcate[numarVehiculeParcate] = Vehicul(numar, sosire);
            numarVehiculeParcate++;
            locuriDisponibile--;
            cout << "Vehicul adaugat cu succes!\n";
        }
        else {
            cout << "Nu mai sunt locuri disponibile!\n";
        }
    }

    void scoateVehicul(string numar, DataOra plecare) {
        for (int i = 0; i < numarVehiculeParcate; i++) {
            if (vehiculeParcate[i].getNumar() == numar) {
                int durataMinute = vehiculeParcate[i].getSosire().diferentaMinute(plecare);
                double cost = (durataMinute / 60.0) * tarifPeOra;

                istoric[numarIstoric++] = IstoricIesire(numar, vehiculeParcate[i].getSosire(), plecare, cost);

                // Mutăm ultimul vehicul în locul celui scos
                vehiculeParcate[i] = vehiculeParcate[numarVehiculeParcate - 1];
                numarVehiculeParcate--;
                locuriDisponibile++;

                cout << "Vehicul scos din parcare. Cost total: " << cost << " RON\n";
                return;
            }
        }
        cout << "Vehiculul nu a fost gasit in parcare!\n";
    }
};

int main() {
    Parcare parcare(100, 5.0, 200); // 100 locuri, tarif 5 RON/oră
    int optiune = 0;

    do {
        cout << "\n=== SISTEM MANAGEMENT PARCARE ===\n";
        cout << "1. Afiseaza statistici\n";
        cout << "2. Adauga vehicul in parcare\n";
        cout << "3. Scoate vehicul din parcare\n";
        cout << "0. Iesire\n";
        cout << "Alegeti o optiune: ";
        cin >> optiune;

        switch (optiune) {
        case 1:
            parcare.afiseazaStatistici();
            break;
        case 2: {
            string numar;
            DataOra sosire;
            cout << "Introduceti numarul de inmatriculare: ";
            cin >> numar;
            cout << "Introduceti data si ora sosirii:\n";
            sosire.citeste();
            parcare.adaugaVehicul(numar, sosire);
            break;
        }
        case 3: {
            string numar;
            DataOra plecare;
            cout << "Introduceti numarul de inmatriculare: ";
            cin >> numar;
            cout << "Introduceti data si ora plecarii:\n";
            plecare.citeste();
            parcare.scoateVehicul(numar, plecare);
            break;
        }
        case 0:
            cout << "La revedere!\n";
            break;
        default:
            cout << "Optiune invalida!\n";
        }
    } while (optiune != 0);

    return 0;
}

