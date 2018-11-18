#include <iostream>
using namespace std;


/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAĐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
6. ZA POTREBE TESTIRANJA, UNUTAR MAIN FUNKCIJE MOZETE DODAVATI NOVE TESTNE PODATKE
****************************************************************************/
//narednu liniju code-a ignorisite, osim u slucaju da vam bude predstavljala smetnje u radu
#pragma warning(disable:4996)

const char * crt = "\n----------------------------------------------------\n";

char* AlocirajNizKaraktera(const char* sadrzaj)
{
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Datum {
	int * _dan, *_mjesec, *_godina;
public:
	Datum(int d, int m, int g) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}
	Datum(const Datum &datum) {
		_dan = new int(*datum._dan);
		_mjesec = new int(*datum._mjesec);
		_godina = new int(*datum._godina);
	}
	void operator=(const Datum &datum) {
		if (this != &datum) {
			*_dan = *datum._dan;
			*_mjesec = *datum._mjesec;
			*_godina = *datum._godina;
		}
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream & operator<<(ostream & COUT, Datum obj) {
		COUT << *obj._dan << "/" << *obj._mjesec << "/" << *obj._godina << " ";
		return COUT;
	}
};

template<class T, int velicina>
class FITArray {
	T _niz[velicina];
	int _trenutno;
	bool _dozvoliDupliciranje;

	bool JelPun() const { return _trenutno == velicina; }
	bool JelPrazan() const { return _trenutno == 0; }

public:
	//OSTALE FUNKCIJE CLANICE DEFINISATI VAN TEMPLATE KLASE
	void operator=(const FITArray& fitArray);
	bool operator+=(const T&);
	bool operator-=(const T&);
	const T& GetElement(int lokacija) const { return _niz[lokacija]; }
	friend ostream& operator<< <>(ostream &COUT, const FITArray& fitArray);
	FITArray<T, velicina> operator()(const int& OD, const int& DO);

	FITArray(bool dozvoliDupliciranje = true) { _dozvoliDupliciranje = dozvoliDupliciranje; _trenutno = 0; }
	FITArray(const FITArray& fitArray) {
		_trenutno = fitArray._trenutno;
		for (int i = 0; i < _trenutno; i++)
			_niz[i] = fitArray._niz[i];
		_dozvoliDupliciranje = fitArray._dozvoliDupliciranje;
	}

	int GetTrenutno() const { return _trenutno; }
	T * GetNiz() { return _niz; }

	bool GetDozvoljenoDupliciranje() const { return _dozvoliDupliciranje; }
	void SetDozvoljenoDupliciranje(const bool& dozvoliDupliciranje) { _dozvoliDupliciranje = dozvoliDupliciranje; }
	void SetTrenutno(const int& trenutno) { _trenutno = trenutno; }
};

template<class T, int velicina>
void FITArray<T, velicina>::operator=(const FITArray& fitArray) {
	_trenutno = fitArray._trenutno;
	for (int i = 0; i < _trenutno; i++)
		_niz[i] = fitArray._niz[i];
	_dozvoliDupliciranje = fitArray._dozvoliDupliciranje;
}

template<class T, int velicina>
FITArray<T, velicina> FITArray<T, velicina>::operator()(const int& OD, const int& DO) {
	FITArray<T, velicina> temp;
	if (OD >= _trenutno) return temp;
	for (int i = OD; i <= DO && i < _trenutno; i++)
		temp += _niz[i];
	return temp;
}

template<class T, int velicina>
bool FITArray<T, velicina>::operator-=(const T& element) {
	if (JelPrazan()) return false;
	for (int i = 0; i < _trenutno; i++)
		if (_niz[i] == element)
		{
			_niz[i] = _niz[--_trenutno];
			if (!_dozvoliDupliciranje) return true;
		}
	return false;
}


template<class T, int velicina>
bool FITArray<T, velicina>::operator+=(const T& element) {
	if (JelPun()) return false;
	if (!_dozvoliDupliciranje)
		for (int i = 0; i < _trenutno; i++)
			if (_niz[i] == element)
				return false;
	_niz[_trenutno++] = element;
	return true;
}

template<class T, int velicina>
ostream& operator<< <>(ostream &COUT, const FITArray<T, velicina>& fitArray) {
	for (int i = 0; i < fitArray._trenutno; i++)
		COUT << fitArray._niz[i] << endl;
	return COUT;
}


class PolozeniPredmet {
	char * _naziv;
	int _ocjena;
	Datum _datumPolaganja;
public:
	PolozeniPredmet(const Datum& datum = { 0,0,0 }, const char* naziv = nullptr, int ocjena = 0) :_datumPolaganja(datum) {
		_naziv = AlocirajNizKaraktera(naziv);
		_ocjena = ocjena;
	}

	PolozeniPredmet(const PolozeniPredmet& predmet): _datumPolaganja(predmet._datumPolaganja) {
		_naziv = AlocirajNizKaraktera(predmet._naziv);
		_ocjena = predmet._ocjena;
	}

	~PolozeniPredmet() { delete[] _naziv; _naziv = nullptr; }

	int getOcjena()const {
		return _ocjena;
	}

	bool operator==(const PolozeniPredmet& predmet) {
		if (strcmp(_naziv, predmet._naziv) == 0)
			return false;
		return true;
	}

	void operator=(const PolozeniPredmet& predmet) {
		delete[]_naziv;
		_naziv = AlocirajNizKaraktera(predmet._naziv);
		_ocjena = predmet._ocjena;
		_datumPolaganja = predmet._datumPolaganja;
	}

	friend ostream & operator<<(ostream & COUT, const PolozeniPredmet & obj) {
		COUT << obj._naziv << "(" << obj._ocjena << ")" << obj._datumPolaganja << endl;
		return COUT;
	}

	friend ostream & operator<<(ostream & COUT, const PolozeniPredmet * obj) {
		COUT << obj->_naziv << "(" << obj->_ocjena << ")" << obj->_datumPolaganja << endl;
		return COUT;
	}
};

class Student {
	static int _indeksCounter; //sluzi za odredjivanje narednog broja indeksa koji ce biti dodijeljen studentu, pocevsi od 160000
	const int _indeks;
	char * _imePrezime;
	FITArray<PolozeniPredmet *, 40> _polozeniPredmeti;
public:
	Student(const char* imePrezime) :_indeks(_indeksCounter++) {
		_imePrezime = AlocirajNizKaraktera(imePrezime);

		for (int i = 0; i < 40; i++)
			_polozeniPredmeti.GetNiz()[i] = nullptr;
	}
	
	Student(Student& student) : _indeks(_indeksCounter++) {
		_imePrezime = AlocirajNizKaraktera(student._imePrezime);

		int vel = student._polozeniPredmeti.GetTrenutno();
		for (int i = 0; i < vel; i++)
			_polozeniPredmeti += new PolozeniPredmet(*student._polozeniPredmeti.GetNiz()[i]);
	}


	~Student() {
		delete[] _imePrezime; _imePrezime = nullptr;
		int vel = _polozeniPredmeti.GetTrenutno();
		for (int i = 0; i < vel; i++)
			delete _polozeniPredmeti.GetNiz()[i];
	}

	float GetProsjek() {
		float suma = 0;
		for (int i = 0; i < _polozeniPredmeti.GetTrenutno(); i++) {
			suma += _polozeniPredmeti.GetNiz()[i]->getOcjena();
		}
		return suma / _polozeniPredmeti.GetTrenutno();
	}

	void DodajPredmet(const PolozeniPredmet &predmet) {
		_polozeniPredmeti += new PolozeniPredmet(predmet);
	}

	void operator=(Student& student) {
		_imePrezime = AlocirajNizKaraktera(student._imePrezime);
		int vel = _polozeniPredmeti.GetTrenutno();
		for (int i = 0; i < vel; i++)
			delete _polozeniPredmeti.GetNiz()[i];

		vel = student._polozeniPredmeti.GetTrenutno();
		_polozeniPredmeti.SetTrenutno(0);
		for (int i = 0; i < vel; i++)
			_polozeniPredmeti += new PolozeniPredmet(*student._polozeniPredmeti.GetNiz()[i]);
	}
	
	friend ostream & operator<<(ostream & COUT, const Student & obj) {
		COUT << obj._indeks << " " << obj._imePrezime << endl << obj._polozeniPredmeti;
		return COUT;
	}
};

int Student::_indeksCounter = 160000;

void main() {
	const int max = 20;

	Datum jucer(20, 11, 2017), danas(21, 11, 2017), sutra(22, 11, 2017);
	cout << jucer << danas << sutra << endl;
	jucer = danas;
	cout << jucer << danas << sutra << endl;

	//parametar tipa bool odredjuje da li je u nizu dozvoljeno dupliciranje elemenata
	FITArray<int, max> nizIntegera(false);

	for (size_t i = 0; i < max - 1; i++)
		nizIntegera += i;//dodaje novog clana niza

	if (!(nizIntegera += 6))//pokusavamo dodati dupli clan niza
		cout << "Element nije dodan u niz" << endl;

	cout << crt << nizIntegera << crt; //ispisuje sve clanove niza

	nizIntegera -= 9; //uklanja clan niza sa vrijednoscu 9
	nizIntegera -= 17;

	FITArray<int, max> noviNizIntegera(nizIntegera);

	cout << crt << noviNizIntegera << crt;

	/*parametri odredjuju lokacije (indekse u nizu) elemenata OD - DO koje je potrebno vratiti. u slucaju da u nizu ne postoji trazeni broj elemenata funkcija treba da vrati sve element od lokacije OD pa do posljednje dostupnog elementa */
	cout << "Clanovi niza od lokacije 2 do lokacije 5 su -> " << noviNizIntegera(2, 5) << crt;

	Student adel("Adel Handzic"), jasmin("Jasmin Azemovic");

	PolozeniPredmet prI(jucer, "PRI", 10), prII(jucer, "PRII", 8), prIII(sutra, "PRIII", 7);

	adel.DodajPredmet(prII);
	adel.DodajPredmet(prIII);
	cout << adel << endl;
	//vraca prosjecnu ocjenu studenta
	cout << "Prosjecna ocjena -> " << adel.GetProsjek() << crt;

	jasmin = adel;
	jasmin.DodajPredmet(prI);

	cout << jasmin << endl;
	cout << "Prosjecna ocjena -> " << jasmin.GetProsjek() << crt;
	system("PAUSE>0");
}