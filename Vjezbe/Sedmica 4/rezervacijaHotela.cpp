#include<iostream>
using namespace std;

char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

const char* crt = "\n----------------------------------------------\n";

class Datum
{
	int _dan;
	int _mjesec;
	int _godina;
public:

	int Dani() {
		return _dan + _mjesec*30 + _godina*365;
	}

	bool istiDatumi(const Datum& datum) const {
		return _dan == datum._dan && _godina == datum._godina && _mjesec == datum._mjesec;
	}
	void Kopiraj(const Datum &datum)
	{
		_dan = datum._dan;
		_mjesec = datum._mjesec;
		_godina = datum._godina;
	}

	Datum(int d, int m, int g) : _dan(d), _mjesec(m), _godina(g) {}
	
	void Info() const {//dodaj const
		cout << _dan << "." << _mjesec << "." << _godina << endl;
	}

	bool JeVeci(const Datum& datum) const
	{
		if (_godina > datum._godina)
			return true;
		else if (_godina == datum._godina)
			if (_mjesec > datum._mjesec)
				return true;
			else if (_mjesec == datum._mjesec)
				if (_dan > _dan)
					return true;
		return false;
	}


};

enum TipNaplate { PoOsobi, Jednokratno, PoNocenju };
class Usluga
{
	char* _naziv;
	double _cijena;
	TipNaplate _tipNaplate;
public:

	TipNaplate getTipNaplate() const { return _tipNaplate; }
	double getCijena() const { return _cijena; }

	void Kopiraj(const Usluga& usluga)
	{ 
		_cijena = usluga._cijena; 
		_tipNaplate = usluga._tipNaplate;
		_naziv = AlocirajNizKaraktera(usluga._naziv);
	}

	Usluga() : _naziv(nullptr), _cijena(0), _tipNaplate(TipNaplate(0)) {}
	Usluga(const char* naziv, int cijena, TipNaplate tipNaplate) :
		_cijena(cijena), _tipNaplate(tipNaplate)
	{
		_naziv = AlocirajNizKaraktera(naziv);
	}

	~Usluga()
	{
		delete[] _naziv;
		_naziv = nullptr;
	}

	void Info()
	{
		cout << "Naziv usluge: " << _naziv << endl;
		cout << "Cijena: " << _cijena << endl;
	}
};

enum TipSmjestaja { StudioApartman, SingleRoom, DoubleRoom, SuperiorApartman };
const char* TipSmjestajaString[] = { "StudioApartman", "SingleRoom", "DoubleRoom", "SuperiorApartman" };

class Smjestaj
{
	int _broj; //Broj sobe, apartmana
	TipSmjestaja* _tipSmjestaja;
	int _maxBrojOsoba;
	double _cijenaPoOsobi;
public:
	int getMaxBrojOsoba() const { return _maxBrojOsoba; }
	double getCijenaPoOsobi() const { return _cijenaPoOsobi; }
	int getBroj() const { return _broj; }

	Smjestaj(const Smjestaj &smjestaj) {
		_broj = smjestaj._broj;
		_tipSmjestaja = new TipSmjestaja(*smjestaj._tipSmjestaja);
		_maxBrojOsoba = smjestaj._maxBrojOsoba;
		_cijenaPoOsobi = smjestaj._cijenaPoOsobi;
	}



	void Kopiraj(const Smjestaj &smjestaj) {
		_broj = smjestaj._broj;
		delete _tipSmjestaja;
		_tipSmjestaja = new TipSmjestaja(*smjestaj._tipSmjestaja);
		_maxBrojOsoba = smjestaj._maxBrojOsoba;
		_cijenaPoOsobi = smjestaj._cijenaPoOsobi;
	}

	Smjestaj(int broj = 0, TipSmjestaja tip = TipSmjestaja(0), int maxBrojOsoba = 0, double cijenaPoOsobi = 0):
		_broj(broj), _tipSmjestaja(new TipSmjestaja(tip)), _maxBrojOsoba(maxBrojOsoba), _cijenaPoOsobi(cijenaPoOsobi) {}

	~Smjestaj()
	{
		delete _tipSmjestaja;
		_tipSmjestaja = nullptr;
	}

	void Info() const
	{
		cout << "Broj sobe: " << _broj << endl;
		cout << "Tip smjestaja: " << TipSmjestajaString[*_tipSmjestaja] << endl;
		cout << "Kapacitet smjestaja: " << _maxBrojOsoba << endl;
		cout << "Cijena po osobi: " << _cijenaPoOsobi << endl;

	}

};

class Gost
{
	char* _imePrezime;
	char* _kontakTelefon;
public:
	bool IstiGost(const Gost& gost) {
		if (!(strcmp(_imePrezime, gost._imePrezime) == 0))
			return false;
		else if (!(strcmp(_kontakTelefon, gost._kontakTelefon) == 0))//moglo bi mozda samo telefon
			return false;
		return true;
	}


	void Kopiraj(const Gost& gost) {

		delete[] _imePrezime;
		delete[] _kontakTelefon;

		_imePrezime = AlocirajNizKaraktera(gost._imePrezime);
		_kontakTelefon = AlocirajNizKaraktera(gost._kontakTelefon);
	}


	Gost(const Gost& gost) {
		_imePrezime = AlocirajNizKaraktera(gost._imePrezime);
		_kontakTelefon = AlocirajNizKaraktera(gost._kontakTelefon);
	}


	Gost(const char* imePrezime, const char* kontaktTelefon)
	{
		_imePrezime = AlocirajNizKaraktera(imePrezime);
		_kontakTelefon = AlocirajNizKaraktera(kontaktTelefon);
	}

	void Info()
	{
		cout << "Ime i prezime: " << _imePrezime << endl;
		cout << "Kontakt telefon: " << _kontakTelefon << endl;
	}

};

enum StatusRezervacije { Aktivna, Potvrdjena, BoravakUToku, Otkazana };
const char* StatusRezervacijeChar[] = { "Aktivna", "Potvrdjena", "BoravakUToku", "Otkazana" };
class Rezervacija
{
	Datum _pocetakBoravka;
	Datum _krajBoravka;
	Gost* _gost; //Gost koji je rezervisao smještaj
	Smjestaj _smjestaj;
	int _brojOsoba; //Ukupan broj osoba koji boravi u smjestaju
	Usluga* _usluge; //Dodatne usluge koje je gost koristio tokom boravka
	int _brojUsluga;
	double _ukupanIznos;
	StatusRezervacije _status;
public:

	Gost* getGost() const { return _gost; }

	double getUkupanIznos() const { return _ukupanIznos; }
	Usluga* getUsluge() const { return _usluge; }
	int getBrojUsluga() const { return _brojUsluga; }


	StatusRezervacije getStatus() const { return _status; }
	void setStatus(const StatusRezervacije& status) { _status = status; }

	bool IsteRezervacije(const Rezervacija& rezervacija) const {
		if (!_pocetakBoravka.istiDatumi(rezervacija._pocetakBoravka) || !_krajBoravka.istiDatumi(rezervacija._krajBoravka))
			return false;
		//else if (_brojOsoba != rezervacija._brojOsoba)
		//	return false;
		//else if (_smjestaj.getBroj() != rezervacija._smjestaj.getBroj())
		//	return false;
		// else if (!_gost->IstiGost(*rezervacija._gost))
		// 	return false;
		//else if (_brojUsluga != rezervacija._brojUsluga)
		//	return false;
		//else if (_ukupanIznos != rezervacija._ukupanIznos)
		//	return false;
		//else if (_status != rezervacija._status)//vraca mi false jer se salje rezervacija
		//	return false;
		return true;
	}

	Rezervacija() :_pocetakBoravka(0, 0, 0), _krajBoravka(0, 0, 0) {};

	int getBrojOsoba() const { return _brojOsoba; }


	void Kopiraj(const Rezervacija& rezervacija) {
		_pocetakBoravka.Kopiraj(rezervacija._pocetakBoravka);
		_krajBoravka.Kopiraj(rezervacija._krajBoravka);
		_gost = new Gost(*rezervacija._gost);
		_smjestaj.Kopiraj(rezervacija._smjestaj);
		_brojOsoba = rezervacija._brojOsoba;
		_brojUsluga = rezervacija._brojUsluga;
		_usluge = new Usluga[_brojUsluga];
		for (int i = 0; i < _brojUsluga; i++)//rezervacija._brojUsluga da ne mora dobavljati iz rezervacije...
			_usluge[i] = rezervacija._usluge[i];
		_ukupanIznos = rezervacija._ukupanIznos;
		_status = rezervacija._status;
	}


	void Info() const {
		cout << "OD: "; _pocetakBoravka.Info();
		cout << "DO: "; _krajBoravka.Info();
		cout << "Gost: ";
		_gost->Info();
		cout << "Smjestaj: ";
		_smjestaj.Info();
		cout << "Broj osoba: " << _brojOsoba << endl;
		for (int i = 0; i < _brojUsluga; i++)
			_usluge[i].Info();
		cout << "Ukupan iznos: " << _ukupanIznos << endl;
		cout << "Status: " << StatusRezervacijeChar[_status] << crt;
	}


	void RezervisiUslugu(const Usluga& u)
	{
		Usluga* temp = new Usluga[_brojUsluga + 1];
		for (size_t i = 0; i < _brojUsluga; i++)
			temp[i].Kopiraj(_usluge[i]);//koristim kopiraj zbog *naziv

		delete[] _usluge;
		_usluge = temp;

		_usluge[_brojUsluga++].Kopiraj(u);

		double cijena = u.getCijena();
		//enum TipNaplate { PoOsobi, Jednokratno, PoNocenju };
		TipNaplate tip = u.getTipNaplate();
		cout << "TIP: " << tip << endl;
		if (tip == 0)
			cijena *= _brojOsoba;
		else if(tip == 3)
			cijena *= _krajBoravka.Dani() - _pocetakBoravka.Dani() - 1;

		_ukupanIznos += cijena;
	}


	Rezervacija(const Datum& OD, const Datum& DO, const Gost& gost, const Smjestaj& smjestaj, const int& brojOsoba)
	: _pocetakBoravka(OD), _krajBoravka(DO), _gost(new Gost(gost)), _smjestaj(smjestaj), _brojOsoba(brojOsoba) {
		_usluge = nullptr;
		_brojUsluga = 0;
		_ukupanIznos = smjestaj.getCijenaPoOsobi() * brojOsoba;//mislim da ovako ide
		_status = Aktivna;//na pocetku je sve aktivno
	}

	int getBrojSmjestaja() const { return _smjestaj.getBroj(); }

	Datum getKrajBoravka() const { return _krajBoravka; }
	Datum getPocetakBoravka() const { return _pocetakBoravka; }

	

};

class Hotel
{
	char* _naziv;
	//Ponuda smještaja
	Smjestaj* _smjestaji;
	int _brojSmjestaja;
	//Rezervacije hotela (protekle, aktivne i nadolazeće)
	Rezervacija* _rezervacije;
	int _brojRezervacija;
	static int _stopaPDV;
public:

	Gost PronadjiVIPGosta() {//mora postojati barem jedna rezervacija...
		//if (_brojRezervacija != 0)
		//{
		int max = 0;
		double ukupanTrosak = _rezervacije[max].getUkupanIznos(), temp;
		for (int i = 1; i < _brojRezervacija; i++) {//ovo radi al ako isti gost vise puta bukira onda nije realno
			temp = _rezervacije[i].getUkupanIznos();
			if (ukupanTrosak < temp) {
				ukupanTrosak = temp;
				max = i;
			}
		}
		return *_rezervacije[max].getGost();
		//}
		//else throw ...exception
	}


	//Pronalazi i vraća podatke o najtraženijem smještaju hotela (onaj koji je najviše puta rezervisan u datom periodu)
	Smjestaj GetNajTrazenijiSmjestaj(const Datum &OD, const Datum &DO) {



		int *suma = new int[_brojSmjestaja] {0};
		for (int i = 1; i <= _brojSmjestaja; i++)
			for (int j = 0; j < _brojRezervacija; j++)
				if (_rezervacije[j].getBrojSmjestaja() == i)
					if(_rezervacije[j].getPocetakBoravka().JeVeci(OD) && DO.JeVeci(_rezervacije[j].getPocetakBoravka()))
						suma[i-1]++;

		int max = 0;
		for (int i = 1; i < _brojSmjestaja; i++)
			if (suma[max] < suma[i])
				max = i;

		return _smjestaji[max];
	}



	/*	Vrši ispis računa sa svim stavkama rezervacije (posebno stavka za smještaj, a posebno za sve usluge sa
		pripadajućim cijenama, te ukupnim iznosom računa na kraju). 
		Parametar tipa bool govori da li je potrebno obračunati
		PDV po utvrđenoj stopi na ukupan iznos računa te na sve stavke pojedinačno.*/
	void CheckOut(const Rezervacija& rezervacija, const bool& uslovZaPDV) {
		for (int i = 0; i < _brojRezervacija; i++)
		{
			if (rezervacija.IsteRezervacije(rezervacija))
			{
				cout << "Broj smjestaja: " << _rezervacije[i].getBrojSmjestaja() << endl;
				cout << "Broj osoba: " << _rezervacije[i].getBrojOsoba() << endl;
				_rezervacije[i].getPocetakBoravka().Info();
				_rezervacije[i].getKrajBoravka().Info();
				cout << "Status: " << StatusRezervacijeChar[_rezervacije[i].getStatus()] << endl;
				int vel = _rezervacije[i].getBrojUsluga();
				Usluga *nizUsluga = _rezervacije[i].getUsluge();
				cout << "Usluge: " << endl;
				for (int j = 0; j < vel; j++)
					nizUsluga[j].Info();
				double iznos = _rezervacije[i].getUkupanIznos();

				if (uslovZaPDV)
					iznos += iznos * _stopaPDV/100;
				cout << "Ukupan iznos je: " << iznos << "KM" << crt;
			}

		}
	}
	void CheckIn(const Rezervacija& rezervacija) {
		for (int i = 0; i < _brojRezervacija; i++)
			if (rezervacija.IsteRezervacije(_rezervacije[i]))//pa pošto se promjenio status vraca false nije isto...
				if (_rezervacije[i].getStatus() == Potvrdjena)
					_rezervacije[i].setStatus(BoravakUToku);
				else
					break;
	}

	void PotvrdiRezervaciju(const Rezervacija& rezervacija)
	{
		for (int i = 0; i < _brojRezervacija; i++)
		{
			if (rezervacija.IsteRezervacije(_rezervacije[i]))
			{
				_rezervacije[i].setStatus(Potvrdjena);
				break;
			}
		}
	}


	void ProsiriRezervaciju(const Rezervacija &rezervacija)
	{
		Rezervacija* t = new Rezervacija[_brojRezervacija + 1];
		for (int i = 0; i < _brojRezervacija; i++)
			t[i].Kopiraj(_rezervacije[i]);
		delete _rezervacije;
		_rezervacije = t;
		_rezervacije[_brojRezervacija++].Kopiraj(rezervacija);
	}

	//Funkcija kojom se dodaje nova rezervacija pod uslovom da smjestaj nije zauzet u trazenom periodu 
	//i da kapacitet smještaja nije manji od broja osoba. Funkcija treba da ispiše sve uslove koje rezervacija
	//ne ispunjava.
	bool DodajRezervaciju(const Rezervacija &rezervacija) {
		bool test = true;

		for (int i = 0; i < _brojSmjestaja; i++)
		{
			if (_smjestaji[i].getBroj() == rezervacija.getBrojSmjestaja())
			{
				if (_smjestaji[i].getMaxBrojOsoba() < rezervacija.getBrojOsoba())
				{
					cout << "Nije moguće ovoliko osoba smjestiti u ovaj smjestaj." << endl;
					cout << "U smjestaj je maksimalno moguće: " << _smjestaji[i].getMaxBrojOsoba() << endl;
					cout << "Potrebno smjestaja: " << rezervacija.getBrojOsoba() << crt;
					test = false;
				}
			}
		}


		for (int i = 0; i < _brojRezervacija; i++)
		{
			if (_rezervacije[i].getBrojSmjestaja() == rezervacija.getBrojSmjestaja())
			{
				if (IzmedjuPocetkaIKraja(rezervacija.getPocetakBoravka(), rezervacija.getKrajBoravka(), _rezervacije[i].getPocetakBoravka(), _rezervacije[i].getKrajBoravka()))
				{
					test = false;
					cout << "Smjestaj je u tom periodu zauzet: ";
					_rezervacije[i].getBrojSmjestaja();
					cout << "Pocetak: ";
					_rezervacije[i].getPocetakBoravka();
					cout << "Kraj: ";
					_rezervacije[i].getKrajBoravka();
				}

			}
		}


		if (test)
			ProsiriRezervaciju(rezervacija);

		return test;
	}


	bool IzmedjuPocetkaIKraja(const Datum& OD, const Datum& DO, const Datum& pocetak, const Datum& kraj) const {
		return (OD.JeVeci(pocetak) || OD.JeVeci(kraj)) && (kraj.JeVeci(DO) || kraj.JeVeci(DO));
	}

	bool RezervisanSmjestaj(const int broj, const Datum &OD, const Datum &DO) const {
		for (int i = 0; i < _brojRezervacija; i++)
			if (broj == _rezervacije[i].getBrojSmjestaja()) {
				if (IzmedjuPocetkaIKraja(OD, DO, _rezervacije[i].getPocetakBoravka(), _rezervacije[i].getKrajBoravka())) {
					return true;
				}
				else break;
			}
		return false;
	}

	

	//Funkcija koja vrši ispis podataka o svim slobodnim smještajima hotela u zadatom periodu.
	void IspisiSlobodneSmjestaje(const Datum &OD, const Datum &DO)
	{
		for (int i = 0; i < _brojSmjestaja; i++) {
			if (!RezervisanSmjestaj(_smjestaji[i].getBroj(),OD,DO)) {
				_smjestaji[i].Info();
			}
		}
	}



	void DodajSmjestaj(const Smjestaj &smjestaj)
	{
		for (int i = 0; i < _brojSmjestaja; i++)
			if (smjestaj.getBroj() == _smjestaji[i].getBroj())
				return;

		Smjestaj* t = new Smjestaj[_brojSmjestaja + 1];//broj Smjestaja(0,0,0,0)
		for (int i = 0; i < _brojSmjestaja; i++)
		{
			t[i].Kopiraj(_smjestaji[i]);
		}
		delete[] _smjestaji;
		t[_brojSmjestaja].Kopiraj(smjestaj);
		
		_smjestaji = t;
		
		_brojSmjestaja++;
	}

	Hotel(const char* naziv) : _smjestaji(nullptr), _brojSmjestaja(0),
		_rezervacije(nullptr), _brojRezervacija(0)
	{
		_naziv = AlocirajNizKaraktera(naziv);
	}

};

int Hotel::_stopaPDV = 17;


int main()
{

#pragma region Hotel

	const int brojUsluga(5);
	Hotel hotel1("Hotel Mostar");

	Usluga* usluge[brojUsluga];
	usluge[0] = new Usluga("Parking", 5, TipNaplate(1));
	usluge[1] = new Usluga("Dorucak", 10, TipNaplate(0));
	cout << "U1 INFO: " << endl;
	cout << usluge[1]->getTipNaplate() << endl;
	cout << crt;
	usluge[2] = new Usluga("Rucak", 15, TipNaplate(0));
	usluge[3] = new Usluga("Wellness & SPA", 40, TipNaplate(2));
	usluge[4] = new Usluga("Veseraj", 10, TipNaplate(2));

	Smjestaj apartman(1, TipSmjestaja(0), 5, 30);
	Smjestaj soba1(2, TipSmjestaja(1), 2, 20);
	Smjestaj soba2(3, TipSmjestaja(2), 4, 20);
	Smjestaj soba3(1, TipSmjestaja(0), 2, 15);

	//Funkciju za dodavanje smjestajnih kapaciteta hotela. Hotel ne moze imati više smještaja
	//pod istim brojem.
	hotel1.DodajSmjestaj(apartman);
	hotel1.DodajSmjestaj(soba1);
	hotel1.DodajSmjestaj(soba2);
	hotel1.DodajSmjestaj(soba3); //Neće se dodati radi zauzetosti broja smještaja RADI

	//Funkcija koja vrši ispis podataka o svim slobodnim smještajima hotela u zadatom periodu.
	hotel1.IspisiSlobodneSmjestaje(Datum(24, 10, 2018), Datum(1, 11, 2018));//mislim da je ispravno implementirano

	//Ispis dodatnih usluga
	for (size_t i = 0; i < brojUsluga; i++) { //Ovo radi već ?
		usluge[i]->Info();
	}

#pragma endregion

#pragma region RezervacijaGost1

	Gost gost1("Marija Perić", "033/222-555");
	cout << crt;
	cout << "REZERVACIJA: " << endl;
	Rezervacija rezervacija1(Datum(28, 10, 2018), Datum(2, 11, 2018), gost1, apartman, 3);
	rezervacija1.RezervisiUslugu(*usluge[0]); //Parking
	rezervacija1.RezervisiUslugu(*usluge[1]); //Doručak za 3 osobe
	rezervacija1.Info();

	//Funkcija kojom se dodaje nova rezervacija pod uslovom da smjestaj nije zauzet u trazenom periodu 
	//i da kapacitet smještaja nije manji od broja osoba. Funkcija treba da ispiše sve uslove koje rezervacija
	//ne ispunjava.
	if (hotel1.DodajRezervaciju(rezervacija1))
		cout << "Uspjesno ste rezervisali smjestaj." << endl;
	else
		cout << "Rezervacija smjestaja nije uspjela." << endl;

	hotel1.PotvrdiRezervaciju(rezervacija1); //Prije nego se gosti prijave u hotel rezervacija mora biti potvrđena.
	hotel1.CheckIn(rezervacija1); //Mijenja status rezervacije na BoravakUToku, pod uslovom da je ista prethodno potvrđena.

	
	/*Vrši ispis računa sa svim stavkama rezervacije (posebno stavka za smještaj, a posebno za sve usluge sa
		pripadajućim cijenama, te ukupnim iznosom računa na kraju). Parametar tipa bool govori da li je potrebno obračunati
		PDV po utvrđenoj stopi na ukupan iznos računa te na sve stavke pojedinačno.*/
	hotel1.CheckOut(rezervacija1, true);

#pragma endregion

#pragma region RezervacijaGost2
	Gost gost2("Adijan Marić", "066/111-333");
	Rezervacija rezervacija2(Datum(29, 10, 2018), Datum(5, 11, 2018), gost2, apartman, 6);

	if (hotel1.DodajRezervaciju(rezervacija2))
		cout << "Uspjesno ste rezervisali smjestaj." << endl;
	else
		cout << "Rezervacija smjestaja nije uspjela." << endl;
	


#pragma endregion

	//Napomena: Za potrebe testiranje funkcija u nastavku dopuniti testni program.

	//Pronalazi i vraća podatke o najtraženijem smještaju hotela (onaj koji je najviše puta rezervisan u datom periodu)
	cout << "Naj trazeniji smjestaj: " << endl;
	hotel1.GetNajTrazenijiSmjestaj(Datum(1, 1, 2018), Datum(24, 1, 2018)).Info();//pa ne treba ispisati jer ima samo jedna rezervacija? Trik funkcija...
	cout << crt;
	//Pronalazi i ispisuje podate o VIP gostu (onaj koji je u sumi utrošio najviše novca u hotelu u trenutnoj godini - 2018).
	cout << "VIP GOST: " << endl;
	hotel1.PronadjiVIPGosta().Info();
	cout << crt;
	for (size_t i = 0; i < brojUsluga; i++)
		delete usluge[i];

	system("pause>0");

	return 0;
}