#include <iostream>
#include <iomanip>
using namespace std;
/*
u nastavku je prikazan primjer ispitnog zapisnika (izvještaj o održanom ispitu) sa detaljima/stavkama

-------------------------------------------
Datum ispita: 07.09.2018
Predmet: Programiranje II
-------------------------------------------
IZVJESTAJ O ODRZANOM ISPITU
-------------------------------------------
Br indeksa  Ime prezime   Komisijsko***  Ocjena
16001        A. Joldic        DA        5
15251        D. Music        NE        7 Ponisteno
16014        E. Babovic        DA        8
-------------------------------------------
UKUPNO POLOZILO:    2
PROSJECNA OCJENA:    6.67
-------------------------------------------
*** komisijski ispit: ako student pristupa èetvrti put i dalje (raèunajuæi i poništene rezultate)
*/
const char * crt = "\n-------------------------------------------\n";
const int MAX = 100;

char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Datum {
	int _dan, _mjesec, _godina;

public:
	Datum(const int &dan = 2000, const int &mjesec = 1, const int &godina = 1) {
		_dan = dan;
		_mjesec = mjesec;
		_godina = godina;
	}

	Datum(const Datum &datum) {
		_dan = datum._dan;
		_mjesec = datum._mjesec;
		_godina = datum._godina;
	}

	friend ostream &operator<<(ostream &COUT, const Datum &datum) { COUT << datum._dan << "." << datum._mjesec << "." << datum._godina << " "; return COUT;  }
};
class Student {
	char * _imePrezime;
	int _brojIndeksa;
	int _polozioECTS;

public:

	void operator=(const Student &student)
	{
		if(this != &student)
		{
			setImePrezime(student._imePrezime);
			setBrojIndeksa(student._brojIndeksa);
			setPolozioECTS(student._polozioECTS);
		}
	}

	void setImePrezime(const char* imePrezime) { delete[] _imePrezime; _imePrezime = AlocirajNizKaraktera(imePrezime); }
	void setBrojIndeksa(const int &brojIndeksa) { _brojIndeksa = brojIndeksa; }
	void setPolozioECTS(const int &polozioECTS)	{ _polozioECTS = polozioECTS; }

	char* getImePrezime() const { return _imePrezime; }
	int getBrojIndeksa() const { return _brojIndeksa; }
	int getPolozioECTS() const { return _polozioECTS; }

	Student() { _imePrezime = nullptr; }

	Student(const char* imePrezime, float brojIndeksa) {
		_imePrezime = nullptr;
		setImePrezime(imePrezime);
		setBrojIndeksa(brojIndeksa);
		_polozioECTS = 0;
	}

	Student(const Student &student) {
		setImePrezime(student.getImePrezime());
		setBrojIndeksa(student.getBrojIndeksa());
		setPolozioECTS(student.getPolozioECTS());
	}

	void operator+=(const float &ects) { _polozioECTS += ects; }
	void operator-=(const float &ects) { _polozioECTS -= ects; }

	void DodajECTS(float ects) { _polozioECTS += ects; }
	void UmanjiECTS(float ects) { _polozioECTS -= ects; }

	~Student() { delete[] _imePrezime; _imePrezime = nullptr; }

	friend ostream &operator<<(ostream &COUT, const Student &student){
		COUT << student.getImePrezime() << ", Indeks: " << student.getBrojIndeksa() << ", ECTS: " << student.getPolozioECTS() << " " << endl;
		return COUT;
	}
};

class ZapisnikStavka {
	int _ocjena;
	//ZapisnikStavka æe pokazivati na objekat tipa 
	//student koji se nalazi u instanci tipa Fakultet, 
	//pa nije potrebno vršiti nove alokacije
	Student* _student;
	bool _ponisteno;
	bool _komisijskoPolaganje;

public:

	void setPonisteno(const bool &uslov) { _ponisteno = uslov; }

	void setOcjena(const int &ocjena, const int &ects = 0) { 
	
		if (_ocjena == 5 && ocjena > 5)
			_student->DodajECTS(ects);
		_ocjena = ocjena; 
	}

	Student *getStudent() const { return _student; }
	bool getPonisteno() const { return _ponisteno; }
	bool getKomisijskoPolaganje() const { return _komisijskoPolaganje; }
	int getOcjena() const { return _ocjena; }
	
	ZapisnikStavka()
	{
		_ocjena = 0;
		_student = nullptr;
		_ponisteno = false;
		_komisijskoPolaganje = false;
	}

	void operator=(const ZapisnikStavka &zapisnikStavka)
	{
		_ocjena = zapisnikStavka._ocjena;
		_student = zapisnikStavka._student;
		_ponisteno = zapisnikStavka._ponisteno;
		_komisijskoPolaganje = zapisnikStavka._komisijskoPolaganje;
	}

	ZapisnikStavka(const ZapisnikStavka &zapisnikStavka)
	{
		_ocjena = zapisnikStavka._ocjena;
		_student = zapisnikStavka._student;
		_ponisteno = zapisnikStavka._ponisteno;
		_komisijskoPolaganje = zapisnikStavka._komisijskoPolaganje;
	}

	ZapisnikStavka(Student* student, int ocjena, bool komisijskoPolaganje, bool ponisteno = false) {
		_ocjena = ocjena;
		_student = student;
		_komisijskoPolaganje = komisijskoPolaganje;
		_ponisteno = ponisteno;
	}

	friend ostream &operator<<(ostream &COUT, const ZapisnikStavka &zapisnikStavka) {
		COUT << zapisnikStavka._student->getImePrezime() << "\t" << zapisnikStavka._ocjena << "\t" << zapisnikStavka._student->getBrojIndeksa() << "\t";
		if (zapisnikStavka._ponisteno)
			COUT << " Ponisteno";
		COUT << endl;
		return COUT;
	}
};
class IspitniZapisnik {
	Datum _datum;
	ZapisnikStavka * _stavke;//svaki put se dodaje po jedna stavka
	int _brojStavki;
	int _ects;
	char * _predmet;
public:

	int getEcts() const { return _ects; }
	char* getPredmet() const { return _predmet; }
	Datum getDatum() const { return _datum; }
	int getBrojStavki() const { return _brojStavki; }
	ZapisnikStavka * getStavke(const int &lokacija) const { return &_stavke[lokacija]; }

	ZapisnikStavka* GetStavkuSaStudentom(int brojIndeksa)
	{
		for (int i = 0; i < _brojStavki; i++)
			if (_stavke[i].getStudent()->getBrojIndeksa() == brojIndeksa)
				return &_stavke[i];

		return nullptr;
	}

	bool ValidneStavke()
	{
		for (int i = 0; i < _brojStavki; i++)
			if (_stavke->getPonisteno() != true)
				return true;
		return false;
	}

	friend ostream &operator<<(ostream &COUT, const IspitniZapisnik &zapisnikStavka)
	{
		COUT << zapisnikStavka._predmet << endl;
		COUT << "Datum: " << zapisnikStavka._datum << endl;
		COUT << "ECTS BODOVI: " << zapisnikStavka._ects << endl;
		for (int i = 0; i < zapisnikStavka._brojStavki; i++)
			COUT << zapisnikStavka._stavke[i] << endl;
		return COUT;
	}


	IspitniZapisnik(const Datum & datum, const char* predmet, int ects) {
		_datum = datum;
		_brojStavki = 0;
		_stavke = nullptr;
		_ects = ects;
		_predmet = AlocirajNizKaraktera(predmet);
	}
	~IspitniZapisnik() {
		delete[] _predmet; _predmet = nullptr;
		delete[] _stavke; _stavke = nullptr;
	}

	void DodajStavku(Student* s, int ocjena)
	{
		ZapisnikStavka* temp = new ZapisnikStavka[_brojStavki + 1];
		for (size_t i = 0; i < _brojStavki; i++) { temp[i] = _stavke[i]; }

		delete[] _stavke;
		_stavke = temp;
		_stavke[_brojStavki++] = ZapisnikStavka(s,ocjena,false,false);//Treba voditi racuna o broju izlazaka

	}
	/*U prosjek raèunati i poništene rezultate (stavke)*/
	float GetProsjecnaOcjena() { 
		if(_brojStavki == 0)
			return 0;
		int suma = 0;
		for (int i = 0; i < _brojStavki; i++)
			suma += _stavke[i].getOcjena();
		return suma/(float)_brojStavki; 
	}
};

/*unutar objekta tipa Fakultet ce se cuvati podaci o svim studentima i ispitnim zapisnicima, a dodaju se pomocu globalnih funkcija*/
class Fakultet {
	//umjesto brojaca koristiti default.ne vrijednosti
	Student* _studenti[MAX];/*= { nullptr };*/
	IspitniZapisnik* _zapisnici[MAX];/*= { nullptr };*/
public:
	friend ostream &operator<<(ostream &cout, const Fakultet &fakultet)
	{
		IspitniZapisnik *z = fakultet.GetPosljednjiZapisnik();
		cout << crt;
		cout << z->getDatum();
		cout << z->getPredmet();
		cout << crt;
		cout << "IZVJESTAJ O ODRZANOM ISPITU" << crt;
		const int vel = z->getBrojStavki();
		cout << "Br indeksa  Ime prezime   Komisijsko***  Ocjena" << endl;
		for (int i = 0; i < vel; i++)
		{
			ZapisnikStavka *stavke = z->getStavke(i);
			Student *s = stavke->getStudent();
			cout << s->getBrojIndeksa() << setw(17) << s->getImePrezime() << setw(14);
			if (stavke->getKomisijskoPolaganje())
				cout << "DA";
			else
				cout << "NE";
			cout << setw(6) << stavke->getOcjena() << " ";
			if (stavke->getPonisteno())
				cout << "Ponisteno";
			cout << endl;
		}
		cout << crt;
		return cout;

	}
	/* funkcija printaj prikazuje posljednji ispitni zapisnik u formatu prikazanom na pocetku zadatka.
	zapisnik se nece prikazati ukoliko ne posjeduje niti jednu stavku ili su sve stavke poništene. Prilikom kreiranja zapisnika
	iskoristiti funkciju GetProsjecnaOcjena.*/
	bool printaj()
	{
		IspitniZapisnik *z = GetPosljednjiZapisnik();
		if (!z->ValidneStavke())
			return false;


		cout << crt;
		cout << z->getDatum();
		cout << z->getPredmet();
		cout << crt;
		cout << "IZVJESTAJ O ODRZANOM ISPITU" << crt;
		const int vel = z->getBrojStavki();
		cout << "Br indeksa  Ime prezime   Komisijsko***  Ocjena" << endl;
		for (int i = 0; i < vel; i++)
		{
			ZapisnikStavka *stavke = z->getStavke(i);
			Student *s = stavke->getStudent();
			cout << s->getBrojIndeksa() << setw(17) << s->getImePrezime() << setw(14);
			if (stavke->getKomisijskoPolaganje())
				cout << "DA";
			else
				cout << "NE";
			cout << setw(6) << stavke->getOcjena() << " ";
			if (stavke->getPonisteno())
				cout << "Ponisteno";
			cout << endl;
		}
		cout << crt;
		return true;
		
	}

	bool operator-=(const int &brojIndeksa)
	{
		IspitniZapisnik *z = GetPosljednjiZapisnik();

		ZapisnikStavka *stavka = z->GetStavkuSaStudentom(brojIndeksa);
		if (stavka == nullptr)
			return false;

		stavka->setPonisteno(true);
		return true;
	}

	bool ponisti_stavku_rezultat(const int &brojIndeksa)
	{
		IspitniZapisnik *z = GetPosljednjiZapisnik();

		ZapisnikStavka *stavka = z->GetStavkuSaStudentom(brojIndeksa);
		if (stavka == nullptr)
			return false;

		stavka->setPonisteno(true);
		return true;
		
	}
	bool dodaj_stavku_na_zapisnik(int brojIndeksa, int ocjena)
	{
		IspitniZapisnik* z = GetPosljednjiZapisnik();
		if (z == nullptr)
			return false;

		ZapisnikStavka* stavka = z->GetStavkuSaStudentom(brojIndeksa);
		if (stavka != nullptr)
		{
			stavka->setOcjena(ocjena, z->getEcts());
			return false;
		}

		Student *s = GetStudent(brojIndeksa);
		if (s == nullptr)
			return false;

		if (ocjena > 5)
			s->DodajECTS(z->getEcts());

		z->DodajStavku(s, ocjena);

		return true;

	}

	void kreiraj_zapisnik(int d, int m, int g, const char* predmet, int ects)
	{
		int i = 0;
		while (i < MAX)
		{
			if (_zapisnici[i] == nullptr)
			{
				_zapisnici[i] = new IspitniZapisnik({ d, m, g }, predmet, ects);
				return;
			}

			i++;
		}
	}

	bool operator+=(const Student &student)
	{
		if (PostojiStudent(student.getBrojIndeksa()))
			return false;

		int i = 0;
		while (i < MAX)
		{
			if (_studenti[i] == nullptr)
			{
				_studenti[i] = new Student(student);
				return true;
			}

			i++;
		}
		return false;
	}
	
	void dodaj_student(const char* imePrezime, int brojIndeksa)
	{
		if (PostojiStudent(brojIndeksa))
			return;

		int i = 0;
		while (i < MAX)
		{
			if (_studenti[i] == nullptr)
			{
				_studenti[i] = new Student(imePrezime, brojIndeksa);
				return;
			}

			i++;
		}
	}
	
	Fakultet()
	{
		for (int i = 0; i < MAX; i++)
		{
			_studenti[i] = nullptr;
			_zapisnici[i] = nullptr;
		}
	}

	Student *getStudent(const int &lokacija) const { return _studenti[lokacija]; }
	IspitniZapisnik *getZapisnici(const int &lokacija) const { return _zapisnici[lokacija]; }

	~Fakultet() {
		for (size_t i = 0; i < MAX; i++) {
			delete _studenti[i]; _studenti[i] = NULL;
			delete _zapisnici[i]; _zapisnici[i] = NULL;
		}
	}

	bool PostojiStudent(int brojIndeksa)
	{
		for (int i = 0; i < MAX; i++)
			if (_studenti[i] != nullptr && getStudent(i)->getBrojIndeksa() == brojIndeksa)
				return true;

		return false;
	}

	Student* GetStudent(int brojIndeksa)
	{
		for (int i = 0; i < MAX; i++)
			if (_studenti[i] != nullptr && getStudent(i)->getBrojIndeksa() == brojIndeksa)
				return _studenti[i];

		return nullptr;
	}

	IspitniZapisnik* GetPosljednjiZapisnik() const
	{
		int i = 0, poz = -1;
		while (i < MAX)
		{
			if (_zapisnici[i] == nullptr)
			{
				poz = i - 1;
				break;
			}
			i++;
		}

		if (i == MAX - 1)
			poz = i;

		if (poz != -1)
			return _zapisnici[poz];

		return nullptr;
	}
};

int main() {
	Fakultet fakultet;

	/*dodaje podatke o novom studentu u fakultet */
	//fakultet, imePrezime, broj indeksa

	fakultet += Student("A. Joldic", 16001);
	cout << "Testiranje += operatora: " << *fakultet.getStudent(0) << endl;
	fakultet.dodaj_student("D. Music", 15251);
	fakultet.dodaj_student("E. Babovic", 16014);
	fakultet.dodaj_student("E. Junuz", 16015);
	fakultet.dodaj_student("J. Azemovic", 16014);//ne dodaje studenta jer je broj indeksa zauzet

	/*kraira novi zapisnik*/
	//fakultet, datum, predmet, ects krediti
	fakultet.kreiraj_zapisnik(6, 9, 2018, "Programiranje II", 7);

	/*dodaje stavku na posljednji kreiran zapisnik,
	a ects studenta (_polozioECTS) uveæa ako je student
	položio ispit. */

	if (fakultet.dodaj_stavku_na_zapisnik(16001, 5))
		cout << "Stavka (rezultat) uspjesno dodata!" << endl;

	cout << *fakultet.getZapisnici(0) << endl;
	cout << "Ects: " << fakultet.getStudent(0)->getPolozioECTS() << endl;

	/*ako je student vec dodat u zapisnik, onda se vrsi samo modifikacija njegove ocjene*/
	if(!fakultet.dodaj_stavku_na_zapisnik(16001, 6))
		cout << "Student vec dodat na zapisnik. Ocjena je ispravljena!" << endl;

	cout << *fakultet.getZapisnici(0) << endl;
	cout << "Ects: " << fakultet.getStudent(0)->getPolozioECTS() << endl;
	fakultet.dodaj_stavku_na_zapisnik(15251, 5);
	fakultet.dodaj_stavku_na_zapisnik(16015, 6);
	fakultet.dodaj_stavku_na_zapisnik(16014, 8);

	fakultet.kreiraj_zapisnik(7, 9, 2018, "Racunarske mreze", 5);
	//naredne stavke se dodaju na novi zapisnik
	fakultet.dodaj_stavku_na_zapisnik(16015, 5);
	fakultet.dodaj_stavku_na_zapisnik(16014, 10);


	/*u posljednjem zapisniku stavku za studenta 16001 ponistiti, a studentu umanjiti ects bodove.
	funkcija vraca false u slucaju da se student ne nalazi na posljednjem zapisniku*/

	if (fakultet.ponisti_stavku_rezultat(16001))//16014
		cout << "Stavka (rezultat) uspjesno ponisten!" << endl;

	if (!(fakultet -= (19001)))
		cout << "Student nije pronadjen!" << endl;

	/* funkcija printaj prikazuje posljednji ispitni zapisnik u formatu prikazanom na pocetku zadatka.
	zapisnik se nece prikazati ukoliko ne posjeduje niti jednu stavku ili su sve stavke poništene. Prilikom kreiranja zapisnika
	iskoristiti funkciju GetProsjecnaOcjena.*/


	//if (fakultet.printaj())
	//	cout << "Ispitni zapisnik uspjesno prikazan!" << endl;

	cout << fakultet << endl;
	//ZADATAK: Sve strukture prevesti u klase
	//Globalne metode prepoznati kao članice odg. klasa 
	//Unaprijediti rješenje pristupom bez NULLPTR kao indikatora kraja niza (uvesti brojace)

	system("pause>0");
	return 0;
}
