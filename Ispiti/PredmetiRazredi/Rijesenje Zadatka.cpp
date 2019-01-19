#include<iostream>
#include<vector>
#include<regex>
#include<string>
using namespace std;
enum Predmeti { Matematika, Historija, Geografia, Hemija, Biologija, Engleski, Muzicko, Fizicko };
enum Razredi { I1, I2, I3, II1, II2, II3, III1, III2, III3, IV1, IV2, IV3 };
const char * ispisPredmeti[] = { "Matematika", "Historija", "Geografia", "Hemija", "Biologija", "Engleski", "Muzicko", "Fizicko" };
const char * ispisRazredi[] = { "I1", "I2", "I3", "II1", "II2", "II3", "III1", "III2", "III3", "IV1", "IV2", "IV3" };

const char* crt = "\n-----------------------------------\n";

template<class T1, class T2>
class Kolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int _trenutno;
public:

	bool operator==(const Kolekcija<T1, T2>& kolekcija)
	{
		if (kolekcija.GetTrenutno() != _trenutno)
			return false;
		for (int i = 0; i < _trenutno; i++)
			if (kolekcija.GetElement1(i) != _elementi1[i] || kolekcija.GetElement2(i) != _elementi2[i])
				return false;
		return true;
	}
	bool operator!=(const Kolekcija<T1, T2>& kolekcija)
	{
		return !(*this == kolekcija);
	}


	int GetTrenutno() const { return _trenutno; }

	Kolekcija(const Kolekcija<T1,T2>& kolekcija)
	{
		if (this == &kolekcija)
			return;
		
		_trenutno = kolekcija._trenutno;
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];

		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = kolekcija._elementi1[i];
			_elementi2[i] = kolekcija._elementi2[i];
		}
	}


	void operator=(const Kolekcija<T1, T2>& kolekcija)
	{
		if (this == &kolekcija)
			return;

		delete[] _elementi1;
		delete[] _elementi2;

		_trenutno = kolekcija._trenutno;
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];

		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = kolekcija._elementi1[i];
			_elementi2[i] = kolekcija._elementi2[i];
		}
	}



	
	friend ostream& operator<<(ostream& cout, const Kolekcija<T1, T2>& kolekcija) 
	{
		for (int i = 0; i < kolekcija._trenutno; i++)
			cout << kolekcija.GetElement1(i) << " - " << kolekcija.GetElement2(i) << endl;
		return cout;
	}

	T1& GetElement1(const int& lokacija) const
	{
		if (lokacija < 0 || lokacija >= _trenutno)
			throw exception("Lokacije ne postoji.");

		return _elementi1[lokacija];
	}

	T2& GetElement2(const int& lokacija) const
	{
		if (lokacija < 0 || lokacija >= _trenutno)
			throw exception("Lokacije ne postoji.");

		return _elementi2[lokacija];
	}

	//uklanja element na osnovu lokacije
	void RemoveElement(const int& lokacija)
	{
		if (lokacija < 0 || lokacija >= _trenutno)
			throw exception("Lokacije ne postoji.");
		T1 * t1 = new T1[_trenutno - 1];
		T2 * t2 = new T2[_trenutno - 1];

		bool pronadjen = false;
		for (int i = 0; i < _trenutno; i++)
		{
			if (lokacija == i)
			{
				pronadjen = true;
				continue;
			}
			t1[i - pronadjen] = _elementi1[i];
			t2[i - pronadjen] = _elementi2[i];
		}
		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = t1;
		_elementi2 = t2;
		
		_trenutno--;
	}


	void AddElement(const T1& e1, const T2& e2)
	{
		T1 * t1 = new T1[_trenutno+1];
		T2 * t2 = new T2[_trenutno+1];

		for (int i = 0; i < _trenutno; i++)
		{
			t1[i] = _elementi1[i];
			t2[i] = _elementi2[i];
		}
		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = t1;
		_elementi2 = t2;

		_elementi1[_trenutno] = e1;
		_elementi2[_trenutno] = e2;

		_trenutno++;
	}


	Kolekcija()
	{
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
	~Kolekcija()
	{
		delete[]_elementi1;
		delete[]_elementi2;
	}

};
class Datum {
	int *_dan, *_mjesec, *_godina;
public:
	bool operator==(const Datum& datum) { return *_dan == *datum._dan && *_mjesec == *datum._mjesec && *_godina == *datum._godina; }

	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}

	Datum(const Datum& obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}


	void operator=(const Datum& obj) {
		*_dan = *obj._dan;
		*_mjesec = *obj._mjesec;
		*_godina = *obj._godina;
	}

	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}

	friend ostream& operator<< (ostream &COUT, const Datum &obj) {
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}
};
/*Globalna funkcija, broj telefona treba biti u formatu: +387(61)-222-333 */
bool ProvjeriValidnostBrojaTelefona(string telefon) {
	string pravilo;
	pravilo += "(\\+)";
	pravilo += "\\d{3}";
	pravilo += "\\(";
	pravilo += "\\d{2}";
	pravilo += "\\)";
	pravilo += "\\-";
	pravilo += "\\d{3}";
	pravilo += "\\-";
	pravilo += "\\d{3}";
	regex r(pravilo);
	return regex_match(telefon, r);
}
class Osoba {
protected:
	char * _imePrezime;
	Datum * _datumRodjenja;
	string _brojTelefona;
public:
	friend ostream& operator<<(ostream& cout, const Osoba& osoba)
	{
		cout << "Ime i prezime: " << osoba._imePrezime << endl;
		cout << "Datum rodjenja: " << *osoba._datumRodjenja << endl;
		cout << "Broj telefona: " << osoba._brojTelefona << endl;
		return cout;
	}

	bool operator==(const Osoba& osoba)
	{
		return strcmp(_imePrezime, osoba._imePrezime) == 0 && *_datumRodjenja == *osoba._datumRodjenja && _brojTelefona == osoba._brojTelefona;
	}

	bool operator!=(const Osoba& osoba)
	{
		return !(*this == osoba);
	}

	Osoba(const char * imePrezime,const Datum& datum) {
		_imePrezime = new char[strlen(imePrezime) + 1];
		strcpy_s(_imePrezime, strlen(imePrezime) + 1, imePrezime);
		_datumRodjenja = new Datum(datum);
		_brojTelefona = "";

	}
	Osoba(const Osoba& obj) :_brojTelefona(obj._brojTelefona) {
		_imePrezime = new char[strlen(obj._imePrezime) + 1];
		strcpy_s(_imePrezime, strlen(obj._imePrezime) + 1, obj._imePrezime);
		_datumRodjenja = new Datum(*obj._datumRodjenja);
	}
	~Osoba() { delete[]_imePrezime; delete _datumRodjenja; }

	bool setBrojTelefona(string brojTelefona) {
		if (ProvjeriValidnostBrojaTelefona(brojTelefona)) {
			_brojTelefona = brojTelefona;
			return true;
		}
		return false;
	}

};

char* AlocirajString(const char* sadrzaj)
{
	if (sadrzaj == nullptr)
		return nullptr;

	int vel = strlen(sadrzaj)+1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Nastavnik :public Osoba {
	Kolekcija<Predmeti, Razredi> * _predmetiRazredi;

public:
	const char* getImePrezime() const { return _imePrezime; }

	bool PredajePredmet(const Predmeti predmet)
	{
		for (int i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
			if (_predmetiRazredi->GetElement1(i) == predmet)
				return true;
		return false;
	}
	bool PosjedujeRazred(const Razredi razred)
	{
		for (int i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
			if (_predmetiRazredi->GetElement2(i) == razred)
				return true;
		return false;
	}

	Kolekcija<Predmeti, Razredi>& getPredmetiRazredi()
	{
		return *_predmetiRazredi;
	}


	void operator=(const Nastavnik& nastavnik)
	{
		delete[] _imePrezime;
		delete _datumRodjenja;
		_imePrezime = AlocirajString(nastavnik._imePrezime);
		_datumRodjenja = new Datum(*nastavnik._datumRodjenja);
		_brojTelefona = nastavnik._brojTelefona;

		delete _predmetiRazredi;
		_predmetiRazredi = new Kolekcija<Predmeti, Razredi>;
		for (int i = 0; i < nastavnik._predmetiRazredi->GetTrenutno(); i++)
			_predmetiRazredi->AddElement(nastavnik._predmetiRazredi->GetElement1(i), nastavnik._predmetiRazredi->GetElement2(i));
	}


	Nastavnik(const Nastavnik& nastavnik) : Osoba(nastavnik)
	{
		_predmetiRazredi = new Kolekcija<Predmeti, Razredi>;
		for (int i = 0; i < nastavnik._predmetiRazredi->GetTrenutno(); i++)
			_predmetiRazredi->AddElement(nastavnik._predmetiRazredi->GetElement1(i), nastavnik._predmetiRazredi->GetElement2(i));
	}

	bool operator==(const Nastavnik& nastavnik)
	{
		if (&nastavnik == this)
			return true;
		else if ((Osoba&)(nastavnik) != (Osoba&)(*this))
			return false;
		else if (*nastavnik._predmetiRazredi != *_predmetiRazredi)
			return false;
		return true;
	}
	bool operator!=(const Nastavnik& nastavnik)
	{
		return !(*this == nastavnik);
	}

	bool RemovePredmetRazred(const Predmeti& predmet)
	{
		bool pronadjen = false;
		for (int i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
			if (_predmetiRazredi->GetElement1(i) == predmet)
			{
				_predmetiRazredi->RemoveElement(i);
				pronadjen = true;
			}
		return pronadjen;
	}



	/*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I 
	NAJVISE U DVA RAZREDA (NA DVIJE RAZLICITE GODINE)*/
	bool AddPredmetRazred(const Predmeti& predmet, Razredi razred)
	{
		//"Matematika", "Historija", "Geografia", "Hemija", "Biologija", "Engleski", "Muzicko", "Fizicko"
		//"I1", "I2", "I3", "II1", "II2", "II3", "III1", "III2", "III3", "IV1", "IV2", "IV3"

		int l = -1;
		for (int i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
			if (_predmetiRazredi->GetElement1(i) == predmet)
				if (_predmetiRazredi->GetElement2(i) == razred)
					return false;
				else if (l != -1)
					return false;
				else
					l = i;

		_predmetiRazredi->AddElement(predmet, razred);
		return true;
	}

	Nastavnik(const char* imePrezime, const Datum& datum) : Osoba(imePrezime,datum)
	{
		_predmetiRazredi = new Kolekcija<Predmeti, Razredi>;
	}

	~Nastavnik()
	{
		delete _predmetiRazredi;
		_predmetiRazredi = nullptr;
	}

};

class Ucenik : public Osoba {
	int _brojUDnevniku;
	Razredi _razred;
	vector<Nastavnik *> _nastavnici;
	Kolekcija<Predmeti, int> _predmetiOcjene;
public:
	friend ostream& operator<<(ostream &cout, const Ucenik& ucenik)
	{
		cout << (Osoba&)(ucenik);
		cout << ucenik._brojUDnevniku << endl;
		cout << ispisRazredi[ucenik._razred] << endl;
		cout << "Nastavnici: " << endl;
		for (int i = 0; i < ucenik._nastavnici.size(); i++)
			cout << "-> " << ucenik._nastavnici[i]->getImePrezime() << endl;
		cout << "Predmeti sa ocjenama: " << endl;
		cout << ucenik._predmetiOcjene << endl;
		return cout;
	}


	vector<Nastavnik*>& getNastavnici() { return _nastavnici; }

	Kolekcija<Predmeti, int> & getPredmetiOcjene() { return _predmetiOcjene; };

	Nastavnik* GetNastavnikaByImePrezime(const char* imePrezime)
	{
		for (int i = 0; i < _nastavnici.size(); i++)
			if (strcmp(_nastavnici[i]->getImePrezime(), imePrezime) == 0)
				return _nastavnici[i];
		return nullptr;
	}

	float GetProsjekByNastavnik(const char* imePrezime)
	{
		int suma = 0, brojac = 0;
		Nastavnik* nastavnik = GetNastavnikaByImePrezime(imePrezime);
		if(nastavnik != nullptr)
			for (int i = 0; i < _predmetiOcjene.GetTrenutno(); i++)
				if (nastavnik->PredajePredmet(_predmetiOcjene.GetElement1(i)))
				{
					suma += _predmetiOcjene.GetElement2(i);
					brojac++;
				}
		if (brojac == 0)
			return 0;
		return suma / (float)brojac;
	}

	/*DA BI SE DODALA OCJENA ZA ODREDJENI PREDMET UCENIK MORA POSJEDOVATI NASTAVNIKA KOJI PREDAJE TAJ PREDMET*/
	bool AddPredmetOcjenu(const Predmeti predmet, const int& ocjena)
	{
		for (int i = 0; i < _nastavnici.size(); i++)
			if (_nastavnici[i]->PredajePredmet(predmet))
			{
				_predmetiOcjene.AddElement(predmet, ocjena);
				return true;
			}
		return false;
	}

	/*VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE INFORMACIJE O NASTAVNICIMA
	U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET*/
	/*ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU */
	/*ONEMOGUCITI DODAVANJE ISTIH NASTAVNIKA; POJAM ISTI PODRAZUMIJEVA IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA*/
	bool AddNastavnik(Nastavnik& nastavnik)
	{
		if (!nastavnik.PosjedujeRazred(_razred))
			return false;

		for (int i = 0; i < _nastavnici.size(); i++)
			if (*_nastavnici[i] == nastavnik)
				return false;

		_nastavnici.push_back(&nastavnik);
		return true;
	}

	Ucenik(const char* imePrezime, const Datum& datum, const int& brojUDnevniku, Razredi razred) :Osoba(imePrezime, datum)
	{
		_brojUDnevniku = brojUDnevniku;
		_razred = razred;
	}
};

void main() {

	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
	3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
	5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.
	6. NIJE POTREBNO BACATI IZUZETKE. SVE FUNKCIJE VRACAJU TRUE ILI FALSE
	****************************************************************************/

#pragma region TestiranjeDatuma
//	Datum danas(26, 11, 2015);
//	Datum sutra(danas);
//	Datum prekosutra;
//	prekosutra = danas;
//	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
//	Kolekcija<int, int> kolekcija1;
//	int brojElemenata = 15;
//	for (size_t i = 0; i < brojElemenata; i++)
//		kolekcija1.AddElement(i, i);
//	kolekcija1.RemoveElement(0);//uklanja element na osnovu lokacije
//	cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
//	cout << kolekcija1 << endl;
//	Kolekcija<int, int> kolekcija2;
//	kolekcija2 = kolekcija1;
//	cout << kolekcija2 << crt;
//	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
//		cout << "ISTI BROJ ELEMENATA" << endl;
//	Kolekcija<int, int> kolekcija3(kolekcija2);
//	cout << kolekcija3 << crt;
#pragma endregion
#pragma region TestiranjeNastavnika
	Nastavnik jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
	Nastavnik adel("Adel Handzic", Datum(15, 10, 1981));
	/*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA RAZREDA (NA DVIJE RAZLICITE GODINE)*/
	if (jasmin.AddPredmetRazred(Matematika, I1))
		cout << "Predmeti dodan" << endl;
	if (jasmin.AddPredmetRazred(Historija, I1))
		cout << "Predmeti dodan" << endl;

	if (jasmin.AddPredmetRazred(Geografia, I1))
		cout << "Predmeti dodan" << endl;

	if (jasmin.AddPredmetRazred(Geografia, I2))
		cout << "Predmeti dodan" << endl;

	if (adel.AddPredmetRazred(Historija, III1))
		cout << "Predmeti dodan" << endl;

//	if (adel.RemovePredmetRazred(Historija)) //da testiram ostalo dio koda
//		cout << "Predmet uklonjen!" << endl;
	Nastavnik goran(adel);

	if (goran == adel)
		cout << "Nastavnici identicni" << endl;
	goran = jasmin;
	if (goran == jasmin)
		cout << "Nastavnici identicni" << endl;

	Kolekcija<Predmeti, Razredi> & predmetiRazredi = jasmin.getPredmetiRazredi();

	if (!jasmin.setBrojTelefona("+38761111222"))
		cout << "Broj telefona nije dodan!" << endl;
	if (!jasmin.setBrojTelefona("+387-61-111-222"))
		cout << "Broj telefona nije dodan!" << endl;
	if (jasmin.setBrojTelefona("+387(61)-111-222"))
		cout << "Broj telefona uspjesno dodan!" << endl;
#pragma endregion

#pragma region TestiranjeUcenika
	Ucenik denis("Denis Music", Datum(8, 10, 1990), 3, III1);
	Ucenik elmin("Elmin Sudic", Datum(15, 6, 1993), 1, I1);
	Ucenik adil("Adil Joldic", Datum(13, 8, 1992), 2, II1);
	/*VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE INFORMACIJE O NASTAVNICIMA U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET*/
	/*ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU */
	if (denis.AddNastavnik(jasmin))
		cout << "Nastavnik uspjesno dodan" << endl;
	/*ONEMOGUCITI DODAVANJE ISTIH NASTAVNIKA; POJAM ISTI PODRAZUMIJEVA IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA*/
 	if (denis.AddNastavnik(adel))
		cout << "Nastavnik uspjesno dodan" << endl;
	/*DA BI SE DODALA OCJENA ZA ODREDJENI PREDMET UCENIK MORA POSJEDOVATI NASTAVNIKA KOJI PREDAJE TAJ PREDMET*/
	if (denis.AddPredmetOcjenu(Matematika, 3))
		cout << "Ocjena uspjesno dodana" << endl;
	if (denis.AddPredmetOcjenu(Historija, 4))
		cout << "Ocjena uspjesno dodana" << endl;

	vector<Nastavnik*> & nastavnici = denis.getNastavnici();
	cout << "Ucenik Denis ima dodijeljena " << nastavnici.size() << " nastavnika" << endl;

	Kolekcija<Predmeti, int> & uspjeh = denis.getPredmetiOcjene();
	cout << "Denis ima " << uspjeh.GetTrenutno() << " polozenih predmeta" << endl;
	cout << "Prosjecna ocjena kod nastavnika Jasmin Azemovic je " << denis.GetProsjekByNastavnik("Jasmin Azemovic") << endl;

	Ucenik denis2(denis);
	cout << denis2 << endl;

#pragma endregion
	system("pause");

}