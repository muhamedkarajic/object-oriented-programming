#include <iostream>
#include <string>
#include <vector>
using namespace std;

#pragma warning(disable:4996)
const char *crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
const float minimalan_prosjek = 4.5;

char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Kolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int * _trenutno;
public:

	//od najvece prema najmanjoj vrijednosti
	void SortOpadajuciByT2()
	{
		int vel = getTrenutno();
		int lokacija = 0;
		for (int i = 0; i < vel-1; i++)
		{
			lokacija = i;


			for (int j = i+1; j < vel; j++)
				if (getElement2(lokacija) < getElement2(j))
					lokacija = j;

			if (i != lokacija)
			{
				swap(_elementi2[lokacija], _elementi2[i]);
				swap(_elementi1[lokacija], _elementi1[i]);
			}
		}
	}



	Kolekcija(const Kolekcija &kolekcija)
	{
		_trenutno = new int(0);
		for (int i = 0; i < kolekcija.getTrenutno(); i++)
			AddElement(kolekcija.getElement1(i), kolekcija.getElement2(i));
	}

	void operator=(const Kolekcija &kolekcija)
	{
		for (int i = 0; i < kolekcija.getTrenutno(); i++)
			AddElement(kolekcija.getElement1(i), kolekcija.getElement2(i));
	}


	void AddElement(const T1 &element1, const T2 &element2) 
	{
		T1 * t1 = _elementi1;
		T2 * t2 = _elementi2;

		t1 = new T1[*_trenutno + 1];
		t2 = new T2[*_trenutno + 1];

		for (int i = 0; i < *_trenutno; i++)
		{
			t1[i] = _elementi1[i];
			t2[i] = _elementi2[i];
		}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = t1;
		_elementi2 = t2;

		_elementi1[*_trenutno] = element1;
		_elementi2[*_trenutno] = element2;

		(*_trenutno)++;
	}

	Kolekcija() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = new int(0);
	}
	~Kolekcija() {
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
		delete _trenutno; _trenutno = nullptr;
	}
	T1& getElement1(int lokacija) const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) const { return _elementi2[lokacija]; }
	int getTrenutno() const { return *_trenutno; }
	friend ostream& operator<< (ostream &COUT, Kolekcija &obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
};

class DatumVrijeme {
	int *_dan, *_mjesec, *_godina, *_sati, *_minuti;
public:

	bool operator>(const DatumVrijeme &datumVrijeme) const
	{
		if (*_godina > *datumVrijeme._godina)
			return true;
		else if (*_godina == *datumVrijeme._godina)
			if (*_mjesec > *datumVrijeme._mjesec)
				return true;
			else if (*_mjesec == *datumVrijeme._mjesec)
				if (*_dan > *datumVrijeme._dan)
					return true;
				else if (*_dan == *datumVrijeme._dan)
					if (*_sati > *datumVrijeme._sati)
						return true;
					else if (*_sati == *datumVrijeme._sati)
						if (*_minuti > *datumVrijeme._minuti)
							return true;
		return false;
	}


	void operator=(const DatumVrijeme &datumVrijeme)
	{
		_dan = new int(*datumVrijeme._dan);
		_mjesec = new int(*datumVrijeme._mjesec);
		_godina = new int(*datumVrijeme._godina);
		_sati = new int(*datumVrijeme._sati);
		_minuti = new int(*datumVrijeme._minuti);
	}


	//funkcija ToCharArray vraca datum i vrijeme kao char *//treba ispisati: 19.6.2018 10:15
	char* ToCharArray()
	{
		int vel = 5;
		char dan[3], mjesec[3], godina[5], sati[3], minuti[3];
		
		_itoa_s(*_dan, dan, 10);
		_itoa_s(*_mjesec, mjesec, 10);
		_itoa_s(*_godina, godina, 10);
		_itoa_s(*_sati, sati, 10);
		_itoa_s(*_minuti, minuti, 10);

		vel += strlen(dan);
		vel += strlen(mjesec);
		vel += strlen(godina);
		vel += strlen(sati);
		vel += strlen(minuti);

		char *temp = new char[vel];

		strcpy_s(temp, vel, dan);
		strcat_s(temp, vel, ".");
		strcat_s(temp, vel, mjesec);
		strcat_s(temp, vel, ".");
		strcat_s(temp, vel, godina);
		strcat_s(temp, vel, " ");
		strcat_s(temp, vel, sati);
		strcat_s(temp, vel, ":");
		strcat_s(temp, vel, minuti);


		return temp;
	}

	DatumVrijeme(const DatumVrijeme &datumVrijeme) {
		_dan = new int(*datumVrijeme._dan);
		_mjesec = new int(*datumVrijeme._mjesec);
		_godina = new int(*datumVrijeme._godina);
		_sati = new int(*datumVrijeme._sati);
		_minuti = new int(*datumVrijeme._minuti);
	}

	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	friend ostream& operator<< (ostream &COUT, const DatumVrijeme &obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}
};

class Predmet {
	char * _naziv;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char * naziv, int ocjena, string napomena = "") :_ocjena(ocjena), _napomena(napomena) {
		_naziv = AlocirajNizKaraktera(naziv);
	}

	Predmet(const Predmet &predmet):_ocjena(predmet._ocjena), _napomena(predmet._napomena)
	{
		_naziv = AlocirajNizKaraktera(predmet.GetNaziv());
	}
	void operator=(const Predmet &predmet)
	{
		_ocjena = predmet._ocjena;
		_napomena = predmet._napomena;
		_naziv = AlocirajNizKaraktera(predmet.GetNaziv());
	}

	~Predmet() {
		delete[] _naziv; _naziv = nullptr;
	}
	friend ostream& operator<< (ostream &COUT, Predmet &obj) {
		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
		return COUT;
	}

	friend ostream& operator<< (ostream &COUT, Predmet *&obj) {
		COUT << obj->_naziv << " (" << obj->_ocjena << ") " << obj->_napomena << endl;
		return COUT;
	}


	char * GetNaziv() const { return _naziv; }
	string GetNapomena() const { return _napomena; }
	void DodajNapomenu(string napomena) {
		_napomena += " " + napomena;
	}
};
struct Uspjeh {
	eRazred _razred;
	//datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Kolekcija<Predmet*, DatumVrijeme> * _predmeti;
public:

	void AddPredmet(Predmet *predmet, const DatumVrijeme &datum)
	{
		_predmeti->AddElement(predmet, datum);
	}

	Uspjeh(eRazred razred) :_razred(razred), _predmeti(nullptr) {}

	~Uspjeh() {
		delete[] _predmeti; _predmeti = nullptr;
	}

	Kolekcija<Predmet*, DatumVrijeme> * GetPredmeti() { return _predmeti; }

	friend ostream& operator<< (ostream &COUT, const Uspjeh &obj) {
		COUT << obj._razred << ". razred, predmeti:\n"<< *obj._predmeti << endl;
		return COUT;
	}
};

class Kandidat {
	char * _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh *> _uspjeh;
public:

	Uspjeh * operator()(const eRazred &razred)
	{
		for (int i = 0; i < _uspjeh.size(); i++)
			if (_uspjeh[i]->_razred == razred)
				return _uspjeh[i];
		return nullptr;
	}


	/*
	uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	tom prilikom onemoguciti:
	- dodavanje vise od 6 predmeta za jedan razred
	- dodavanje istoimenih predmeta na nivou jednog razreda,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta 
	mora biti najmanje minut).
	razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II
	razred, pa onda za I razred i sl.). Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	bool AddPredmet(const eRazred &razred, Predmet &predmet, const DatumVrijeme &datum)//razred pocinje od 1
	{
		const int velRazreda = _uspjeh.size();
		for (int i = 0; i < velRazreda; i++)
			if (_uspjeh[i]->_razred == razred)
			{
				const int velPredmeta = _uspjeh[i]->_predmeti->getTrenutno();
				if (velPredmeta == 6)
					return false;

				for (int j = 0; j < velPredmeta; j++)
					if (strcmp(_uspjeh[i]->_predmeti->getElement1(j)->GetNaziv(), predmet.GetNaziv()) == 0)
						return false;



				if (!(datum > _uspjeh[i]->_predmeti->getElement2(velPredmeta - 1)))
					return false;

				_uspjeh[i]->AddPredmet(&predmet, datum);
				return true;
			}

		_uspjeh.push_back(new Uspjeh(razred));
		if (_uspjeh[velRazreda]->_predmeti == nullptr) { _uspjeh[velRazreda]->_predmeti = new Kolekcija<Predmet*, DatumVrijeme>; }
		_uspjeh[velRazreda]->AddPredmet(&predmet, datum);
		return true;
	}

	Kandidat(const char * imePrezime, string emailAdresa, string brojTelefona) :_emailAdresa(emailAdresa), _brojTelefona(brojTelefona) {
		_imePrezime = AlocirajNizKaraktera(imePrezime);
	}

	~Kandidat() {
		delete[] _imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < _uspjeh.size(); i++) {
			delete _uspjeh[i];
			_uspjeh[i] = nullptr;
		}
	}

	friend ostream& operator<< (ostream &COUT, Kandidat &obj) {
		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
		for (size_t i = 0; i < obj._uspjeh.size(); i++)
			COUT << *obj._uspjeh[i] << endl;
		return COUT;
	}

	vector<Uspjeh *> GetUspjeh() { return _uspjeh; }
};

void main() {
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ÆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOÐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUÈAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOÆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
	****************************************************************************/

	DatumVrijeme temp,
		datum19062018_1015(19, 6, 2018, 10, 15),
		datum20062018_1115(20, 6, 2018, 11, 15),
		datum30062018_1215(30, 6, 2018, 12, 15),
		datum05072018_1231(5, 7, 2018, 12, 31),
		datum20062018_1115_Copy(datum20062018_1115);
	//funkcija ToCharArray vraca datum i vrijeme kao char *
	cout << datum19062018_1015.ToCharArray() << endl;//treba ispisati: 19.6.2018 10:15//CURENJE MEMORIJE
	temp = datum05072018_1231;
	cout << temp.ToCharArray() << endl;//treba ispisati: 5.7.2018 12:31
	cout << datum20062018_1115_Copy.ToCharArray() << endl;//treba ispisati: 20.6.2018 11:15

	const int kolekcijaTestSize = 10;
	Kolekcija<int, int> kolekcija1;
	for (size_t i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i + 1, i * i);
	cout << kolekcija1 << endl;

	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	Kolekcija<int, int> kolekcija3;
	kolekcija3 = kolekcija1;
	kolekcija3.SortOpadajuciByT2(); //od najvece prema najmanjoj vrijednosti
	cout << kolekcija3 << crt;

	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
	Fizika("Fizika", 5),
	Hemija("Hemija", 2),
	Engleski("Engleski", 5);
	Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh"); // dodaje novu napomenu zadrzavajuci ranije dodane
	cout << Matematika << endl;

	Kandidat jasmin("Jasmin Azemovic", "jasmin@gmail.com", "033 281 172");
	Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");

	/*
	uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	tom prilikom onemoguciti:
	- dodavanje vise od 6 predmeta za jedan razred
	- dodavanje istoimenih predmeta na nivou jednog razreda,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje minut).
	razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II
	razred, pa onda za I razred i sl.). Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	if (jasmin.AddPredmet(DRUGI, Fizika, datum20062018_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(DRUGI, Hemija, datum30062018_1215))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Engleski, datum19062018_1015))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Matematika, datum20062018_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Matematiku jer je vec dodana u prvom razredu
	if (jasmin.AddPredmet(PRVI, Matematika, datum05072018_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	
	//ne treba dodati Fiziku jer nije prosao minut od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(PRVI, Fizika, datum05072018_1231))
		cout << "Predmet uspjesno dodan!" << crt;

	/*pretpostavka je da na nivou jednog razreda kandidati imaju 6 predmeta.
	upravo zbog toga, nakon evidentiranja 6 predmeta na nivou jednog razreda kandidatu se salje mail
	sa porukom: "evidentirali ste uspjeh za X razred". ukoliko je prosjek na nivou tog razreda veci od minimalan_prosjek
	kandidatu se salje SMS sa porukom: "svaka cast za uspjeh 4.X". slanje poruka i emailova implemenitrati koristeci
	zasebne thread-ove.
	*/

	Uspjeh * u = jasmin(PRVI);//vraca uspjeh kandidata ostvaren u prvom razredu
	if (u != nullptr)
		cout << *u << endl;


	system("pause>0");
}