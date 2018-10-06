#include <iostream>
#include <string>
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
class Datum {
	int * _dan, *_mjesec, *_godina;
public:
	bool operator==(const Datum &d) const
	{
		return *_dan == *d._dan && *_mjesec == *d._mjesec && *_godina == *d._godina;
	}
	Datum()
	{
		_dan = _mjesec = _godina = nullptr;
	}
	Datum(int d, int m, int g) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	Datum(const Datum &d) {
		_dan = new int(*d._dan);
		_mjesec = new int(*d._mjesec);
		_godina = new int(*d._godina);

	}
	void operator=(const Datum &d)
	{
		if (&d != this)
		{
			if (_dan != nullptr)
			{
				delete[] _dan;
				delete[] _mjesec;
				delete[] _godina;
			}


			_dan = new int(*d._dan);
			_mjesec = new int(*d._mjesec);
			_godina = new int(*d._godina);
		}
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
public:
	/*parametri odredjuju lokacije (indekse u nizu) elemenata OD - DO koje je potrebno vratiti.
	u slucaju da u nizu ne postoji trazeni broj elemenata funkcija treba da vrati sve element od lokacije OD pa do posljednje dostupnog elementa */
	const string operator()(const int &begin, const int &end)
	{
		string COUT = "";
		for (int i = begin; i < end && i < _trenutno; i++)
			COUT +=to_string(_niz[i]) + ", ";
		return COUT;
	}





	//OSTALE FUNKCIJE CLANICE DEFINISATI VAN TEMPLATE KLASE
	FITArray(bool dozvoliDupliciranje = true) 
	{ 
		_dozvoliDupliciranje = dozvoliDupliciranje; 
		_trenutno = 0; 
	}
	int GetTrenutno() const { return _trenutno; }
	const T * GetNiz() const { return _niz; }

	bool getDozboliDupliciranje() const
	{
		return _dozvoliDupliciranje;
	}

	FITArray(const FITArray &fit)
	{
		_trenutno = fit.GetTrenutno();
		_dozvoliDupliciranje = fit.getDozboliDupliciranje();
		for (int i = 0; i < fit.GetTrenutno(); i++)
			_niz[i] = fit.GetNiz()[i];
	}

	void operator-=(const T &element)
	{
		for (int i = 0; i < _trenutno; i++)
			if (element == _niz[i])
			{
				_trenutno--;
				_niz[i] = _niz[_trenutno];
				return;
			}
	}





	bool operator+=(const T &element)
	{
		if (_trenutno == velicina)
			return false;
		else if(_dozvoliDupliciranje == false)
			for (int i = 0; i < _trenutno; i++)
				if (element == _niz[i])
					return false;

		_niz[_trenutno] = element;
		_trenutno++;
		return true;
	}
	friend ostream & operator<<(ostream & COUT, const FITArray<T, velicina> &f) {
		for (int i = 0; i < f.GetTrenutno(); i++)
			COUT << f.GetNiz()[i] << endl;

		return COUT;
	}


	
};


class PolozeniPredmet {
	char * _naziv;
	int _ocjena;
	Datum _datumPolaganja;
public:
	
	void operator=(const PolozeniPredmet &p)
	{
		setNaziv(p._naziv);
		_ocjena = p._ocjena;
		_datumPolaganja = p._datumPolaganja;
	}

	int getOcjena() const
	{
		return _ocjena;
	}

	void setNaziv(const char* naziv)
	{
		if (_naziv != nullptr)
			delete[] _naziv;

		int vel = strlen(naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, naziv);
	}

	bool operator==(const PolozeniPredmet &p) const
	{
		if (strcmp(p._naziv, _naziv) == 0)
			if (p._datumPolaganja == _datumPolaganja)
				return true;
		return false;
	}

	PolozeniPredmet()
	{
		_naziv = nullptr;
		_ocjena = 0;
	}


	PolozeniPredmet(const Datum &datumPolaganja, const char* naziv, const int &ocjena): _datumPolaganja(datumPolaganja)
	{
		_naziv = nullptr;
		setNaziv(naziv);

		_ocjena = ocjena;
	}

	PolozeniPredmet(const PolozeniPredmet &p) : _datumPolaganja(p._datumPolaganja)
	{
		_naziv = nullptr;
		setNaziv(p._naziv);

		_ocjena = p._ocjena;
	}


	~PolozeniPredmet() { delete[] _naziv; _naziv = nullptr; }
	friend ostream & operator<<(ostream & COUT, const PolozeniPredmet & obj) {
		COUT << obj._naziv << "(" << obj._ocjena << ")" << obj._datumPolaganja << endl;
		return COUT;
	}
};

class Student {
	static int _indeksCounter; //sluzi za odredjivanje narednog broja indeksa koji ce biti dodijeljen studentu, pocevsi od 160000
	const int _indeks;
	char * _imePrezime;
	FITArray<PolozeniPredmet, 40> _polozeniPredmeti;
public:

	Student(const Student &s) :_indeks(s._indeksCounter++)
	{
		setImePrezime(s._imePrezime);
		for (int i = 0; i < s._polozeniPredmeti.GetTrenutno(); i++)
			_polozeniPredmeti += s._polozeniPredmeti.GetNiz()[i];


	}



	void operator=(const Student &s)
	{
		setImePrezime(s._imePrezime);
		for (int i = 0; i < s._polozeniPredmeti.GetTrenutno(); i++)
			_polozeniPredmeti += s._polozeniPredmeti.GetNiz()[i];

	}

	float GetProsjek()
	{
		int suma = 0;
		for (int i = 0; i < _polozeniPredmeti.GetTrenutno(); i++)
		{
			suma += _polozeniPredmeti.GetNiz()[i].getOcjena();
		}

		return suma / (float)(_polozeniPredmeti.GetTrenutno());
	}

	void DodajPredmet(const PolozeniPredmet &p)
	{
		_polozeniPredmeti += p;
	}

	void setImePrezime(const char* imePrezime)
	{
		if (_imePrezime != nullptr)
			delete[] _imePrezime;

		int vel = strlen(imePrezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, imePrezime);
	}

	Student(const char* imePrezime) :_indeks(_indeksCounter++)
	{
		_imePrezime = nullptr;
		setImePrezime(imePrezime);

	}


	~Student() {
		delete[] _imePrezime; _imePrezime = nullptr;
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
	cout << "Novi niz:" << endl;
	cout << crt << noviNizIntegera << crt;

	/*parametri odredjuju lokacije (indekse u nizu) elemenata OD - DO koje je potrebno vratiti. 
	u slucaju da u nizu ne postoji trazeni broj elemenata funkcija treba da vrati sve element od lokacije OD pa do posljednje dostupnog elementa */
	cout << "Clanovi niza od lokacije 2 do lokacije 5 su -> " << noviNizIntegera(2, 5) << crt;
	Student adel("Adel Handzic"), jasmin("Jasmin Azemovic");
	cout << adel << endl;
	cout << jasmin << endl;
	PolozeniPredmet prII(jucer, "PRII", 8), prIII(sutra, "PRIII", 7);

	adel.DodajPredmet(prII);
	adel.DodajPredmet(prIII);
	cout << adel << endl;
	//vraca prosjecnu ocjenu studenta
	cout << "Prosjecna ocjena -> " << adel.GetProsjek() << crt;

	jasmin = adel;
	cout << jasmin << endl;
	cout << "Prosjecna ocjena -> " << jasmin.GetProsjek() << crt;

	system("PAUSE");
}