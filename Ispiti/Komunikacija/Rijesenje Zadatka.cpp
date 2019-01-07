#include<iostream>
#include<string>
#include<vector>
#include<exception>
using namespace std;

const char *crt = "\n-------------------------------------------\n";
enum stringFormat { DDMMGG, DDMMGGGG, DDMMGGSSMM, DDMMGGGGSSMM };
enum prikazPoruka { SVE_PORUKE, SAKRIJ_POBRISANE, PRIKAZI_SAMO_POBRISANE };
vector<string> nedozvoljeneRijeci;
/*
DDMMGG - 29.8.17
DDMMGGGG - 29.8.2017
DDMMGGGGSSMM - 29.8.2017 10:15
*/

char* AlocirajNizKaraktera(const char* sadrzaj)
{
	if (sadrzaj == nullptr)
		return nullptr;
	char* temp = nullptr;
	int vel = strlen(sadrzaj)+1;
	temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Kolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int * _trenutno;
public:
	Kolekcija()
	{
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = new int(0);
	}

	Kolekcija(T1 elem1, T2 elem2)
	{
		_elementi1 = new T1(elem1);
		_elementi2 = new T2(elem2);
		_trenutno = new int(1);
	}

	Kolekcija & operator=(const Kolekcija<T1, T2> & orig)
	{
		if (this != &orig)
		{
			delete[]_elementi1;
			delete[]_elementi2;

			_elementi1 = new T1[*orig._trenutno];
			_elementi2 = new T2[*orig._trenutno];
			*_trenutno = *orig._trenutno;

			for (int i = 0; i < *_trenutno; i++)
			{
				_elementi1[i] = orig._elementi1[i];
				_elementi2[i] = orig._elementi2[i];
			}
		}
		return *this;
	}

	bool AddElement(T1 elem1, T2 elem2)
	{
		T1 * temp1 = new T1[*_trenutno + 1];
		T2 * temp2 = new T2[*_trenutno + 1];

		for (int i = 0; i < *_trenutno; i++) {
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;

		_elementi1[*_trenutno] = elem1;
		_elementi2[*_trenutno] = elem2;
		(*_trenutno)++;
		return true;
	}
	~Kolekcija()
	{
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
		delete _trenutno; _trenutno = nullptr;
	}

	T1 * getElementi1Pok() const { return _elementi1; }
	T2 * getElementi2Pok() const { return _elementi2; }
	T1 & getElement1(int lokacija) const { return _elementi1[lokacija]; }
	T2 & getElement2(int lokacija) const { return _elementi2[lokacija]; }
	int getTrenutno() const { return *_trenutno; }


//	Kolekcija<T1, T2> operator[](const int& lokacija)
//	{
//		if (lokacija < 0 || lokacija >= *_trenutno)
//			throw exception("Lokacija ne postoji.");
//		return Kolekcija<T1, T2>(_elementi1[lokacija], _elementi2[lokacija]);
//	}

	T1& operator[](const int& lokacija)
	{
		if (lokacija < 0 || lokacija >= *_trenutno)
			throw exception("Lokacija ne postoji.");
		return _elementi1[lokacija];
	}


	friend ostream & operator<<(ostream & COUT, const Kolekcija<T1, T2> & obj)
	{
		for (size_t i = 0; i < *obj._trenutno; i++)
		{
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		}
		return COUT;
	}
};
class DatumVrijeme {
	int *_dan, *_mjesec, *_godina, *_sati, *_minuti;
public:

	int Dani() const { return *_dan + *_mjesec*100 + *_godina*10000; }

//	int operator-(const DatumVrijeme& datum) {
//		return Dani() - datum.Dani();
//	}
	
	int operator-(const DatumVrijeme& datum) {
		const int minuteA = *_minuti + *_sati * 60;
		const int minuteB = *datum._minuti + *datum._sati * 60;

		return minuteA - minuteB;
	}


	void operator=(const DatumVrijeme& datum) {
		if (this != &datum)
		{
			*_dan = *datum._dan;
			*_mjesec = *datum._mjesec;
			*_godina = *datum._godina;
			*_sati = *datum._sati;
			*_minuti = *datum._minuti;
		}
	}



	DatumVrijeme(const DatumVrijeme& datum) {
		_dan = new int(*datum._dan);
		_mjesec = new int(*datum._mjesec);
		_godina = new int(*datum._godina);
		_sati = new int(*datum._sati);
		_minuti = new int(*datum._minuti);
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
	//vraca string: 19.6.2017
	string ToString(stringFormat format)
	{
		//DDMMGG, DDMMGGGG, DDMMGGSSMM, DDMMGGGGSSMM
		string datumString = to_string(*_dan) + '.'  + to_string(*_mjesec) + '.';

		if (format == DDMMGGGG || format == DDMMGGGGSSMM)
			datumString += to_string(*_godina);
		else
			datumString += to_string(*_godina % 100);

		if (format != DDMMGGGG && format != DDMMGG)
			datumString += ' ' + to_string(*_sati) + ':' + to_string(*_minuti);

		return datumString;
	}

	friend ostream & operator<< (ostream & COUT, DatumVrijeme & obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti;
		return COUT;
	}
};
class Poruka {
	string _posiljalac;
	string _primalac;
	string _sadrzaj;
	DatumVrijeme _vrijeme;
public:
	DatumVrijeme& GetDatumVrijeme() { return _vrijeme; }

	void operator=(const Poruka& poruka)
	{
		_vrijeme = poruka._vrijeme;
		_posiljalac = poruka._posiljalac;
		_primalac = poruka._primalac;
		_sadrzaj = poruka._sadrzaj;
	}

	Poruka()
	{
		_posiljalac = _primalac = _sadrzaj = "";
	}

	Poruka(string posiljalac, string primalac, string sadrzaj, DatumVrijeme vrijeme) :_vrijeme(vrijeme)
	{
		_posiljalac = posiljalac;
		_primalac = primalac;
		_sadrzaj = sadrzaj;
	}
	friend ostream & operator<< (ostream & COUT, Poruka & obj) {
		COUT << "(" << obj._vrijeme << ") " << obj._posiljalac << " -> ";
		COUT << obj._sadrzaj;
		return COUT;
	}
	string getPrimalac() { return _primalac; }
	string getPosiljalac() { return _posiljalac; }
	string getSadrzaj() { return _sadrzaj; }
};
class Komunikacija {
	string _naslov;
	int _ocjena; //ocjena komunikacije 1 - 5 se automatski izracunava
	Kolekcija<Poruka, bool> _poruke;//bool se odnosi na podatak da li je poruka pobrisana tj. nece biti vidljiva u prikazu ukoliko se drugacije ne navede
public:
	void SetOcjena(const int& ocjena)
	{
		_ocjena = ocjena;
	}
//	vector<Poruka*> GetSvePoruke()//backup
//	{
//		int vel = _poruke.getTrenutno();
//		vector<Poruka*> poruke;
//		for (int i = 0; i < vel; i++)
//			poruke.push_back(&_poruke[i]);
//		return poruke;
//	}


	vector<Poruka*> GetSvePoruke()
	{
		int vel = _poruke.getTrenutno();
		vector<Poruka*> poruke;
		
		for (int i = 0; i < vel; i++)
		{
			poruke.push_back(&_poruke[i]);
		}
		return poruke;
	}

	vector<Poruka*> GetPoruke(const string& korisnickoIme)
	{
		int vel = _poruke.getTrenutno();
		vector<Poruka*> poruke;
		for (int i = 0; i < vel; i++)
			if (/*_poruke[i].getPosiljalac() == korisnickoIme ||*/ _poruke[i].getPrimalac() == korisnickoIme)
				poruke.push_back(&_poruke[i]);
		return poruke;
	}

	void IspisPoruka(const prikazPoruka& nacinPrikaza)
	{
		int vel = _poruke.getTrenutno();
		for (int i = 0; i < vel; i++)
			if (nacinPrikaza == PRIKAZI_SAMO_POBRISANE && _poruke.getElement2(i))
				cout << "PORUKA IZBRISANA: " << _poruke[i] << endl;
			else if (nacinPrikaza == SAKRIJ_POBRISANE && !_poruke.getElement2(i))
				cout << _poruke[i] << endl;
			else
				cout << _poruke[i] << endl;
	}

	void DodajPoruku(const Poruka& poruka) {
		_poruke.AddElement(poruka, false);
	}


	Komunikacija(const string& naslov, const Poruka& poruka)
	{
		_naslov = naslov;
		_ocjena = -1;
		DodajPoruku(poruka);
	}
	void operator=(const Komunikacija& komunikacija)
	{
		_naslov = komunikacija._naslov;
		_ocjena = komunikacija._ocjena;
		_poruke = komunikacija._poruke;
	}



	Komunikacija(const Komunikacija& komunikacija)
	{
		_naslov = komunikacija._naslov;
		_ocjena = komunikacija._ocjena;
		_poruke = komunikacija._poruke;
	}

	Komunikacija(string naslov = "") {
		_naslov = naslov;
		_ocjena = -1;
	}
	friend ostream & operator<< (ostream & COUT, Komunikacija & obj) {
		COUT << "(" << obj._ocjena << ") " << obj._naslov << " -> ";//_nazivGrupre
		for (int i = 0; i < obj._poruke.getTrenutno(); i++)//_size
			COUT << obj._poruke[i] << endl;
		return COUT;
	}
	Kolekcija<Poruka, bool> * getPoruke() { return &_poruke; }
	int getOcjena() const { return _ocjena; }
	string getNaslov() const { return _naslov; }
};

class Korisnik {
	string _korisnickoIme;
	char * _imePrezime;
	//char * - se odnosi na naziv predmeta ili tema gdje će se čuvati kompletna komunikacija sa nastavnim osobljem ili korisnikom na određenom predmetu/temi
	Kolekcija<char *, Komunikacija> _komunikacija;
public:
	Poruka* PorukaOsobe(vector<Poruka*>& poruke, const string& posiljaoc)
	{
		Poruka* poruka = nullptr;
		for (int i = 0; i < poruke.size(); i++)
			if (poruke[i]->getPosiljalac() == posiljaoc && poruke[i]->getPrimalac() == _korisnickoIme)
			{
				poruka = poruke[i];
				while (poruke[i]->getPosiljalac() == posiljaoc)
				{
					poruke.erase(poruke.begin() + i);
					if (i >= poruke.size())
						break;
				}

				return poruka;
			}
		return poruka;
	}

	/*formira ocjenu na nivou komunikacije na nacin da izracunava prosjecno vrijeme odgovora
		drugog ucesnika izrazeno u minutama i to prema sljedecoj skali
		prosjek > 20 minuta = ocjena 1
		prosjek > 15 minuta = ocjena 2
		prosjek > 10 minuta = ocjena 3
		prosjek > 5 minuta = ocjena 4
		prosjek <=5 minuta = ocjena 5*/
	void OcijeniKomunikaciju(const string& naslov)
	{
		Komunikacija* komunikacija = GetKomunikacija(naslov);
		vector<Poruka*> poruke = komunikacija->GetSvePoruke();

		int minute = 0;
		int brojac = 0;
		for (int i = 0; i < poruke.size(); i++)
			if (poruke[i]->getPosiljalac() == _korisnickoIme)
			{
				if(i+1 < poruke.size())
					while (poruke[i+1]->getPosiljalac() == _korisnickoIme)
						poruke.erase(poruke.begin() + i);

				Poruka * porukaPosiljaoca = poruke[i];

				Poruka * porukaPrimaoca = PorukaOsobe(poruke, poruke[i]->getPrimalac());
				i = 0;
				if (porukaPrimaoca != nullptr)
				{
					minute += porukaPrimaoca->GetDatumVrijeme() - porukaPosiljaoca->GetDatumVrijeme();
					brojac++;
				}
				else break;
			}

		float prosjek = minute / (float)brojac;

		int ocjena = 5;
		if (prosjek > 20)
			ocjena = 1;
		else if (prosjek > 15)
			ocjena = 2;
		else if (prosjek > 10)
			ocjena = 3;
		else if (prosjek > 5)
			ocjena = 4;

		komunikacija->SetOcjena(ocjena);

		cout << "Ocjena komunikacije: " << komunikacija->getOcjena() << crt;
	}

	/*funkcija prikazuje sve poruke sa korisnikom cije korisnicko ime je definisano parametrom, 
	te vraca ukupan broj (razmijenjenih poruka sa tim korisnikom)*/
	int PrikaziKomunikacijuSaKorisnikom(const string& korisnickoIme)
	{
		int vel = _komunikacija.getTrenutno();
		vector<Poruka *> poruke;
		int brojac = 0;
		for (int i = 0; i < vel; i++)
		{
			poruke = _komunikacija.getElement2(i).GetPoruke(korisnickoIme);
			brojac += poruke.size();
			for (int j = 0; j < poruke.size(); j++)
				cout << *poruke[j] << endl;
		}
		return brojac;
	}

	/*ispisuje sve poruke koje je korisnik razmijenio pod naslovom definisanim parametrom. 
	ispis komunikacije treba biti organizovan po datumu na nacin 
	da se prvo prikaze datum, a nakon toga sve poruke koje su razmijenjene tog datuma.
	Na mjestima pobrisanih poruka prikazati tekst "PORUKA IZBRISANA"
	*/
	void PrikaziKomunikacijuPoNaslovu(const string& naslov, const prikazPoruka& nacinPrikaza)
	{
		Komunikacija* komunikacija = GetKomunikacija(naslov);
		komunikacija->IspisPoruka(nacinPrikaza);
	}

	void DodajNovuKomunikaciju(const Komunikacija& komunikacija) 
	{
		_komunikacija.AddElement(AlocirajNizKaraktera(komunikacija.getNaslov().c_str()), komunikacija);
	}

	Komunikacija* GetKomunikacija(const string& naslov)
	{
		int vel = _komunikacija.getTrenutno();
		for (int i = 0; i < vel; i++)
			if (_komunikacija.getElement2(i).getNaslov() == naslov)
				return &_komunikacija.getElement2(i);
		return nullptr;
	}

	Korisnik(const char * korisnickoIme, const char * imePrezime)
	{
		int vel = strlen(imePrezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, imePrezime);
		_korisnickoIme = korisnickoIme;
	}

	Korisnik(Korisnik & original) :_komunikacija(original._komunikacija)
	{
		int vel = strlen(original._imePrezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, original._imePrezime);
		_korisnickoIme = original._korisnickoIme;
	}

	~Korisnik()
	{
		delete[] _imePrezime; _imePrezime = nullptr;
	}

	friend ostream & operator<< (ostream &COUT, Korisnik &obj)
	{
		COUT << obj._imePrezime << endl << obj._komunikacija << endl;
		return COUT;
	}
	Kolekcija<char*, Komunikacija> * GetKomunikacija() { return &_komunikacija; }
	string getKorisnickoIme() { return _korisnickoIme; }
};

/*
	sve poruke se cuvaju u komunikaciji posiljaoca i primaoca tako da u svakom momentu oba ucesnika u komunikaciji
	posjeduju kompletnu historiju poruka. poruke se grupisu na osnovu naslova, pa ce poruke pod naslovom "Sastanak"
	izmedju dva korisnika sadrzavati sve poruke koje su razmijenjene na tu temu
	u slucaju da posiljalac ili primalac ne postoje funkcija treba baciti izuzetak sa odgovarajucom porukom. takodjer,
	koristeci regex sve poruke koje sadrze neku od zabranjenih rijeci trebaju biti oznacene kao
	*/
void PosaljiPoruku
( 
	Korisnik** korisnici, int max, string naslov, 
	string primalac, string posiljalac,
	string sadrzaj, const DatumVrijeme& vrijeme
) 
{
	for (int i = 0; i < nedozvoljeneRijeci.size(); i++)
		if (strstr(sadrzaj.c_str(), nedozvoljeneRijeci[i].c_str()) != nullptr)
			return;

	bool pronadjen = false;
	Komunikacija *komunikacija;
	Poruka poruka(primalac, posiljalac, sadrzaj, vrijeme);
	for (int i = 0; i < max; i++)
		if (korisnici[i]->getKorisnickoIme() == primalac || korisnici[i]->getKorisnickoIme() == posiljalac)
		{
			komunikacija = korisnici[i]->GetKomunikacija(naslov);
			
			if (komunikacija != nullptr)
				komunikacija->DodajPoruku(poruka);
			else
				korisnici[i]->DodajNovuKomunikaciju(Komunikacija(naslov, poruka));
			pronadjen = true;
		}
	if(!pronadjen)
		throw exception("Korisnici nisu pronadjenji.", __LINE__);
}




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


	/*riječi koje su zabranjene u komunikaciji*/
	nedozvoljeneRijeci.push_back("ubiti");
	nedozvoljeneRijeci.push_back("mrzim");
	nedozvoljeneRijeci.push_back("rat");

	DatumVrijeme temp,
		datum19062017_1015(19, 6, 2017, 10, 15),
		datum19062017_1016(19, 6, 2017, 10, 16),
		datum19062017_1020(19, 6, 2017, 10, 20),
		datum19062017_1021(19, 6, 2017, 10, 21),
		datum19062017_1030(19, 6, 2017, 10, 30),
		datum19062017_1037(19, 6, 2017, 10, 37),
		datum19062017_1055(19, 6, 2017, 10, 55);

	cout << datum19062017_1015.ToString(DDMMGGGG) << endl;//vraca string: 19.6.2017
	cout << datum19062017_1015.ToString(DDMMGGGGSSMM) << endl;//vraca string: 19.6.2017 10:15


	const int max = 3;
	Korisnik * korisnici[max];
	korisnici[0] = new Korisnik("jasmin", "Jasmin Azemovic");
	korisnici[1] = new Korisnik("adel", "Adel Handzic");
	korisnici[2] = new Korisnik("denis", "Denis Music");
	
	PosaljiPoruku(korisnici, max, "Sastanak",
		korisnici[0]->getKorisnickoIme(), korisnici[1]->getKorisnickoIme(),
		"Danas imamo sastanak u 10h!", datum19062017_1015);

	PosaljiPoruku(korisnici, max, "Sastanak",
		korisnici[0]->getKorisnickoIme(), korisnici[1]->getKorisnickoIme(),
		"Izmjene sastanak je u 11h!", datum19062017_1016);


	PosaljiPoruku(korisnici, max, "Sastanak",
		korisnici[1]->getKorisnickoIme(), korisnici[0]->getKorisnickoIme(),
		"Naravno, vidimo se u sali za sastanke!", datum19062017_1020);

	PosaljiPoruku(korisnici, max, "Sastanak",
		korisnici[0]->getKorisnickoIme(), korisnici[1]->getKorisnickoIme(),
		"Sa sobom ponesi radni materijal!", datum19062017_1021);

	PosaljiPoruku(korisnici, max, "Sastanak",
		korisnici[1]->getKorisnickoIme(), korisnici[0]->getKorisnickoIme(),
		"Naravno!", datum19062017_1030);


	PosaljiPoruku(korisnici, max, "Sastanak",
		korisnici[0]->getKorisnickoIme(), korisnici[1]->getKorisnickoIme(),
		"Sa sobom ponesi radni materijal!", datum19062017_1037);

	PosaljiPoruku(korisnici, max, "Sastanak",
		korisnici[1]->getKorisnickoIme(), korisnici[0]->getKorisnickoIme(),
		"Naravno!", datum19062017_1055);


	korisnici[0]->PrikaziKomunikacijuPoNaslovu("Sastanak", SVE_PORUKE);
	cout << crt;
	int ukupnoPoruka = korisnici[0]->PrikaziKomunikacijuSaKorisnikom("adel");

	cout << "Ukupno poruka: " << ukupnoPoruka << endl;
	korisnici[0]->OcijeniKomunikaciju("Sastanak");

	for (size_t i = 0; i < max; i++)
	{
		delete korisnici[i];
		korisnici[i] = nullptr;
	}

	system("PAUSE>0");
}