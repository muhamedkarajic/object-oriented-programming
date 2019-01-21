#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <thread>
#include <mutex>
using namespace std;
const char *crt = "\n---------------------------------------\n";
mutex mojGuard;

class DatumVrijeme {
	int *_dan, *_mjesec, *_godina, *_sati, *_minuti;
public:
	bool operator==(const DatumVrijeme& datumVrijeme)
	{
		return *datumVrijeme._dan == *_dan && *datumVrijeme._mjesec == *_mjesec && *datumVrijeme._godina == *_godina && *datumVrijeme._sati == *_sati;
	}

	bool operator!=(const DatumVrijeme& datumVrijeme) { return !(*this == datumVrijeme); }
	
	void operator=(const DatumVrijeme& datumVrijeme)
	{
		


		*_dan = *datumVrijeme._dan;
		*_mjesec = *datumVrijeme._mjesec;
		*_godina = *datumVrijeme._godina;
		*_sati = *datumVrijeme._sati;
		*_minuti = *datumVrijeme._minuti;
	}

	DatumVrijeme(const DatumVrijeme& datumVrijeme)
	{
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

	friend ostream& operator<< (ostream &COUT, DatumVrijeme &obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti;
		return COUT;
	}
};

template<class T1, class T2 = int>
class FITKolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int _trenutno;
public:

	void UkloniSveElemente()
	{
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi1 = nullptr;

		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}

	void operator=(const FITKolekcija<T1, T2>& kolekcija)
	{
		if (this != &kolekcija)
		{
			if (_trenutno == kolekcija._trenutno)
			{
				for (int i = 0; i < kolekcija._trenutno; i++)
				{
					_elementi1[i] = kolekcija._elementi1[i];
					_elementi2[i] = kolekcija._elementi2[i];
				}
			}

			delete[] _elementi1;
			delete[] _elementi2;

			_trenutno = kolekcija._trenutno;

			_elementi1 = new T1[_trenutno];
			_elementi2 = new T2[_trenutno];

			for (int i = 0; i < kolekcija._trenutno; i++)
			{
				_elementi1[i] = kolekcija._elementi1[i];
				cout << _elementi1[i] << endl;
				_elementi2[i] = kolekcija._elementi2[i];
				cout << _elementi1[i] << endl;
			}
		}
	}

	void operator=(const FITKolekcija<T1,T2>*& kolekcija)
	{
		if (this != &kolekcija)
		{
			if (_trenutno == kolekcija._trenutno)
			{
				for (int i = 0; i < kolekcija._trenutno; i++)
				{
					_elementi1[i] = kolekcija._elementi1[i];
					_elementi2[i] = kolekcija._elementi2[i];
				}
			}

			delete[] _elementi1;
			delete[] _elementi2;

			_trenutno = kolekcija._trenutno;

			_elementi1 = new T1[_trenutno];
			_elementi2 = new T2[_trenutno];

			for (int i = 0; i < kolekcija._trenutno; i++)
			{
				_elementi1[i] = kolekcija._elementi1[i];
				_elementi2[i] = kolekcija._elementi2[i];
			}
		}
	}


	bool Sadrzi(const T1& e1, const T1& e2)
	{
		for (int i = 0; i < _trenutno; i++)
			if (e1 == _elementi1[i] && e2 == _elementi2[i])
				return true;
		return false;
	}

	/*METODA GetJedinstveni VRAĆA LISTU JEDINSTVENIH ELEMENATA TJ. ELEMENATA KOJI NE SADRŽE DUPLIKATE 
	(POJAM DUPLIKAT SE ODNOSI NA ISTE VRIJEDNOSTI ELEMENATA T1 I T2). ELEMENTI KOJI SE DUPLIRAJU SE U 
	OVOJ LISTI TREBAJU POJAVITI SAMO JEDNOM.*/
	FITKolekcija<T1, T2> * GetJedinstveni()
	{
		FITKolekcija<T1, T2>* kolekcija = new FITKolekcija<int, int>;
		for (int i = 0; i < _trenutno; i++)
			if (!kolekcija->Sadrzi(_elementi1[i], _elementi2[i]))
				kolekcija->Dodaj(_elementi1[i], _elementi2[i]);
		return kolekcija;
	}

	//BROJ 2 SE ODNOSI NA LOKACIJU/INDEKS UNUTAR LISTE NA KOJI JE POTREBNO DODATI NOVE ELEMENTE
	void DodajNaLokaciju(const T1& e1, const T2& e2, int lokacija)
	{
		if (lokacija < 0 || lokacija > _trenutno)
			throw exception("Ova lokacija ne postoji, ili nije nova sljedeca lokacija.");

		T1 * t1 = new T1[_trenutno + 1];
		T2 * t2 = new T2[_trenutno + 1];

		bool pronadjen = false;
		for (int i = 0; i <= _trenutno; i++)
			if (i == lokacija)
			{
				t1[i] = e1;
				t2[i] = e2;
				pronadjen = true;
				continue;
			}
			else
			{
				t1[i] = _elementi1[i - pronadjen];
				t2[i] = _elementi2[i - pronadjen];
			}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = t1;
		_elementi2 = t2;

		_trenutno++;
	}


	//SORTIRANJE ČLANOVA KOLEKCIJE SE VRŠI U RASTUĆEM REDOSLIJEDU NA OSNOVU VRIJEDNOSTI ELEMENTA TIPA T1
	void Sortiraj()
	{
		int l;
		for (int i = 0; i < _trenutno-1; i++)
		{
			l = i;
			for (int j = i+1; j < _trenutno; j++)
				if (_elementi1[l] > _elementi1[j])
					l = j;
			if (l != i)
			{
				swap(_elementi1[i], _elementi1[l]);
				swap(_elementi2[i], _elementi2[l]);
			}
		}
	}



	void Dodaj(const T1& e1, const T2& e2)
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
		_elementi2[_trenutno++] = e2;
	}

	FITKolekcija() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
	~FITKolekcija() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
	}
	T1 * GetT1() { return _elementi1; }
	T2 * GetT2() { return _elementi2; }
	int GetTrenutno() { return _trenutno; }

	friend ostream& operator<< (ostream &COUT, FITKolekcija &obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		return COUT;
	}
};

enum vrstaDokumenta { PDF, DOC, TXT, HTML };

class Dokument {
	vrstaDokumenta _vrsta;
	string _naziv;
	string _sadrzaj;
	int _brojStranica;
public:
	void PrintajDokument()
	{
		int vel = _sadrzaj.size();
		mojGuard.lock();
		cout << _naziv << endl;
		for (int i = 0; i < vel; i++)
			if (i % 30 == 0)
				cout << endl;
			else
				cout << _sadrzaj[i];
		cout << endl;
		mojGuard.unlock();
	}

	//BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODREĐUJE PRILIKOM DODAVANJA SADRŽAJA. 
	//ZA POTREBE ISPITA PRETPOSTAVLJAMO DA NA JEDNU STRANICU MOŽE STATI 30 ZNAKOVA UKLJUČUJUĆI I RAZMAKE
	void DodajSadrzaj(const string& sadrzaj)
	{
		_sadrzaj += sadrzaj;
		int vel = _sadrzaj.size();
		_brojStranica =  vel / 30;
		if (vel % 30)
			_brojStranica++;
	}

	Dokument() { _brojStranica = 0; }
	Dokument(vrstaDokumenta vrsta, string naziv) {
		_naziv = naziv; _vrsta = vrsta; _brojStranica = 0;
	}
	string GetNaziv() { return _naziv; };
	string GetSadrzaj() { return _sadrzaj; };
	vrstaDokumenta GetVrsta() { return _vrsta; };
	void UvecajBrojStranica() { _brojStranica++; }
	int GetBrojStranica() { return _brojStranica; }
	friend ostream & operator<<(ostream&COUT, Dokument & obj) {
		COUT << obj._naziv << "." << obj._vrsta << " (" << obj._brojStranica << ")\n" << obj._sadrzaj << endl;
		return COUT;
	}
};
class Uredjaj {
protected:
	char * _proizvodjac;
	char * _model;
public:
	Uredjaj(const char * proizvodjac, const char * model) {
		int vel = strlen(proizvodjac) + 1;
		_proizvodjac = new char[vel];
		strcpy_s(_proizvodjac, vel, proizvodjac);
		vel = strlen(model) + 1;
		_model = new char[vel];
		strcpy_s(_model, vel, model);
	}

	Uredjaj(const Uredjaj& u) {
		int vel = strlen(u._proizvodjac) + 1;
		_proizvodjac = new char[vel];
		strcpy_s(_proizvodjac, vel, u._proizvodjac);
		vel = strlen(u._model) + 1;
		_model = new char[vel];
		strcpy_s(_model, vel, u._model);
	}

	~Uredjaj() {
		delete[] _proizvodjac; _proizvodjac = nullptr;
		delete[] _model; _model = nullptr;
	}
	friend ostream & operator<<(ostream&COUT, Uredjaj & obj) {
		COUT << obj._proizvodjac << "." << obj._model << endl;
		return COUT;
	}
};

//1. NAZIV DOKUMENTA MORA BITI U SLJEDEĆEM FORMATU npr : ispitPRIII.doc
//NAZIV DOKUMENTA MOŽE SADRŽAVATI SAMO SLOVA(NAJMANJE 5, NAJVIŠE 15), A EKSTENZIJA MOŽE
//BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
bool validnostNazivaDokumenta(string nazivDokumenta)
{
	string pravilo = "([A-Za-z]{5,15})\\.(doc|pdf|txt|html)";
	return regex_match(nazivDokumenta, regex(pravilo));
}

class Printer : public Uredjaj {
	FITKolekcija<DatumVrijeme, Dokument> _printaniDokumenti;
	vector<string> _zabranjeneRijeci;
	


	//2. SADRŽAJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEČ
	bool sadrziZabranjenuRijec(Dokument& dokument)
	{
		string pravilo = "";
		int vel = _zabranjeneRijeci.size() - 1;
			for (int i = 0; i < vel; i++)
				pravilo += _zabranjeneRijeci[i] + '|';
			pravilo += _zabranjeneRijeci[vel];
			
			if (regex_search(dokument.GetSadrzaj(), regex(pravilo)))
				return true;

		return false;
	}

public:
	FITKolekcija<DatumVrijeme, Dokument> & GetPrintaniDokumenti() { return _printaniDokumenti; };
	vector<string> & GetZabranjeneRijeci() { return _zabranjeneRijeci; };

	//UKLANJA SVE DOKUMENTE KOJI NISU ZADOVOLJILI USLOVE ZA PRINTANJE
	void UkloniDokumente()
	{
		_printaniDokumenti.UkloniSveElemente();
	}

	Printer(const Printer& p) : Uredjaj(p)
	{
		_printaniDokumenti = p._printaniDokumenti;
		_zabranjeneRijeci = p._zabranjeneRijeci;
	}

	string GetTopZabranjenuRijec()
	{
		int vel = _zabranjeneRijeci.size();

		if (vel == 0)
			throw exception("Niz zabranjenje rijeci je prazan!");

		int *suma = new int[vel];
		for (int i = 0; i < vel; i++)
			for (int j = 0; j < _printaniDokumenti.GetTrenutno(); j++)
				if (_printaniDokumenti.GetT2()[j].GetSadrzaj().find(_zabranjeneRijeci[i]))
					suma[i]++;

		int max = 0;
		for (int i = 1; i < vel; i++)
			if (suma[i] > suma[max])
				max = i;

		return _zabranjeneRijeci[max];
	}


	//KOD POREĐENJA DATUMA PRINTANJA NIJE POTREBNO POREDITI MINUTE, SAMO DATUM I SATE
	float GetProsjecanBrojStranicaPoDatumu(const DatumVrijeme& datumVrijeme)
	{
		int brojac = 0, suma = 0;
		for (int i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
			if (_printaniDokumenti.GetT1()[i] == datumVrijeme)
			{
				brojac++;
				suma += _printaniDokumenti.GetT2()[i].GetBrojStranica();
			}
		return suma / (float)brojac;
	}
		
	/*
	DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDEĆA PRAVILA:
	UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
	ODGOVARAJUĆOM PORUKOM, ALI ĆE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
	UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
	SADRŽAJ DOKUMENTA KOJI SE PRINTA
	*/
	void Printaj(const DatumVrijeme& datum, Dokument& dokument)
	{
		if (!validnostNazivaDokumenta(dokument.GetNaziv()))
		{
			_printaniDokumenti.Dodaj(datum, dokument);
			throw exception("Naziv dokumenta nije ispravan.");
		}
		else if (sadrziZabranjenuRijec(dokument))
		{
			_printaniDokumenti.Dodaj(datum, dokument);
			throw exception("Dokument sadrzi u svom sadrzaju neke od zabranjenih rijeci.");
		}

		/*
		IMPLEMENTIRATI PRINTANJE U ZASEBNIM NITIMA UZ KORIŠTENJE sleep_for FUNKCIJE
		VODITI RAČUNA O DIJELJENJU ZAJEDNIČKIH RESURSA
		*/
		thread mojThread(&Dokument::PrintajDokument, &dokument);
		mojThread.join();
	}

	Printer(const char* proizvodjac, const char* model): Uredjaj(proizvodjac, model) {}

	// ONEMOGUĆITI PONAVLJANJE ZABRANJENIH RIJEČI, KORISTITI ITERATORE
	void DodajZabranjenuRijec(string zabranjenaRijec)
	{
		vector<string>::iterator i = _zabranjeneRijeci.begin();
		while (i != _zabranjeneRijeci.end())
			if (*i == zabranjenaRijec)
				return;
			else
				i++;
		_zabranjeneRijeci.push_back(zabranjenaRijec);
	}
};

void main()
{
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/

#pragma region TestiranjeDatumVrijeme
	{
		DatumVrijeme danas(1, 2, 2017, 10, 15);
		DatumVrijeme sutra(danas);
		DatumVrijeme prekosutra;
		prekosutra = danas;
		cout << danas << endl << sutra << endl << prekosutra << crt;
	}

	DatumVrijeme danas(1, 2, 2017, 10, 15);
	DatumVrijeme sutra(danas);
	DatumVrijeme prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;

#pragma endregion
#pragma region FITKolekcija
	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;

	FITKolekcija<int, int> brojevi;
	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v13, v32);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v63, v13);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v196, v6);

	cout << brojevi << crt;
	//SORTIRANJE ČLANOVA KOLEKCIJE SE VRŠI U RASTUĆEM REDOSLIJEDU NA OSNOVU VRIJEDNOSTI ELEMENTA TIPA T1
	brojevi.Sortiraj();
	cout << brojevi << crt;
	//BROJ 2 SE ODNOSI NA LOKACIJU/INDEKS UNUTAR LISTE NA KOJI JE POTREBNO DODATI NOVE ELEMENTE
	brojevi.DodajNaLokaciju(v109, v6, 2);
	cout << brojevi << crt;
	brojevi.Sortiraj();
	cout << brojevi << crt;
	/*METODA GetJedinstveni VRAĆA LISTU JEDINSTVENIH ELEMENATA TJ. ELEMENATA KOJI NE SADRŽE DUPLIKATE (POJAM DUPLIKAT SE ODNOSI NA ISTE VRIJEDNOSTI ELEMENATA T1 I T2). ELEMENTI KOJI SE DUPLIRAJU SE U OVOJ LISTI TREBAJU POJAVITI SAMO JEDNOM.*/
	FITKolekcija<int, int> * jedinstveni = brojevi.GetJedinstveni();
	cout << *jedinstveni << crt;
	cout << "*jedinstveni = brojevi" << crt;
	*jedinstveni = brojevi;
	cout << *jedinstveni << crt;

	Dokument ispitPRIII(DOC, "ispitPRIII.doc");



	//BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODREĐUJE PRILIKOM DODAVANJA SADRŽAJA. ZA POTREBE ISPITA PRETPOSTAVLJAMO DA NA JEDNU STRANICU MOŽE STATI 30 ZNAKOVA UKLJUČUJUĆI I RAZMAKE
	ispitPRIII.DodajSadrzaj("NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO RE");
	cout << "Broj stranica -> " << ispitPRIII.GetBrojStranica() << endl;
	//cout << ispitPRIII << endl;
	Dokument ispitBaze(DOC, "ispitBaze.doc");
	ispitBaze.DodajSadrzaj("PROGRAMSKI CODE SE TAKODER NALAZI U FAJLU CODE.TXT");
	cout << ispitBaze << endl;//ISPISUJE SVE DOSTUPNE PODATKE O DOKUMENTU

	Printer hp3200("HP", "3200");
	//PRINTER NEĆE DOZVOLITI PRINTANJE DOKUMENATA U ČIJEM SADRŽAJU SE NALAZI NEKA OD ZABRANJENIH RIJEČI
	// ONEMOGUĆITI PONAVLJANJE ZABRANJENIH RIJEČI, KORISTITI ITERATORE
	hp3200.DodajZabranjenuRijec("RE");// :)
	hp3200.DodajZabranjenuRijec("RAT");
	hp3200.DodajZabranjenuRijec("UBITI");
	hp3200.DodajZabranjenuRijec("RE");// ONEMOGUĆITI PONAVLJANJE ZABRANJENIH RIJEČI, KORISTITI ITERATORE
	hp3200.DodajZabranjenuRijec("MRZITI");
	try
	{
		/*
		DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDEĆA PRAVILA:
		1. NAZIV DOKUMENTA MORA BITI U SLJEDEĆEM FORMATU npr: ispitPRIII.doc
		NAZIV DOKUMENTA MOŽE SADRŽAVATI SAMO SLOVA (NAJMANJE 5, NAJVIŠE 15), A EKSTENZIJA MOŽE
		BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
		2. SADRŽAJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEČ
		UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
		ODGOVARAJUĆOM PORUKOM, ALI ĆE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
		UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
		SADRŽAJ DOKUMENTA KOJI SE PRINTA
		*/
		hp3200.Printaj(danas, ispitBaze);
		hp3200.Printaj(danas, ispitPRIII);



	}
	catch (exception& err)
	{
		cout << err.what() << endl;
	}

	//KOD POREĐENJA DATUMA PRINTANJA NIJE POTREBNO POREDITI MINUTE, SAMO DATUM I SATE
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp3200.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp3200.GetTopZabranjenuRijec() << crt;

	Printer hp4000(hp3200);
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp4000.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp4000.GetTopZabranjenuRijec() << crt;
	hp4000.UkloniDokumente();//UKLANJA SVE DOKUMENTE KOJI NISU ZADOVOLJILI USLOVE ZA PRINTANJE
	cout << hp4000 << crt;

#pragma endregion
	system("PAUSE>0");
}