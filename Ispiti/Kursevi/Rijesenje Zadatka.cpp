#include <iostream>
#include <vector>
#include <string>
#include <exception>
using namespace std;
const char *crt = "\n---------------------------------------\n";

char* AlocirajKaraktere(const char* karakteri)
{
	if (karakteri == nullptr)
		return nullptr;

	int vel = strlen(karakteri) + 1;
	char *temp = new char[vel];
	strcpy_s(temp, vel, karakteri);
	return temp;
}

class Datum {
	int *_dan, *_mjesec, *_godina;
public:

	bool operator>=(const Datum &datum)
	{
		if (*_godina > *datum._godina)
			return true;
		else if (*_godina == *datum._godina)
			if (*_mjesec > *datum._mjesec)
				return true;
			else if (*_mjesec == *datum._mjesec)
				if (*_dan > *datum._dan)
					return true;
				else if (*_dan == *datum._dan)
					return true;
		return false;
	}

	bool operator==(const Datum &datum) const
	{
		return *_dan == *datum._dan && *_mjesec == *datum._mjesec && *_godina == *datum._godina;
	}

	bool operator!=(const Datum &datum)const
	{
		return !(*this == datum);
	}

	char* ToString() const
	{
		char dan[3], mjesec[3], godina[5];
		_itoa_s(*_dan, dan, 10);
		_itoa_s(*_mjesec, mjesec, 10);
		_itoa_s(*_godina, godina, 10);

		int vel = strlen(dan) + strlen(mjesec) + strlen(godina) + 1 + 3;

		char* temp = new char[vel];
		strcpy_s(temp, vel, dan);
		strcat_s(temp, vel, "/");
		strcat_s(temp, vel, mjesec);
		strcat_s(temp, vel, "/");
		strcat_s(temp, vel, godina);
		strcat_s(temp, vel, " ");

		return temp;
	}

	void operator=(const Datum &datum)
	{
		*_dan = *datum._dan;
		*_mjesec = *datum._mjesec;
		*_godina = *datum._godina;
	}

	Datum(const Datum &datum)
	{
		_dan = new int(*datum._dan);
		_mjesec = new int(*datum._mjesec);
		_godina = new int(*datum._godina);
	}

	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream& operator<< (ostream &COUT, Datum &obj) {
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}
};

class Izuzetak :public exception {
	Datum _datum;//KORISTITE DANASNJI DATUM
	string _funkcija;//FUNKCIJA U KOJOJ JE NASTAO IZUZETAK
	int _linija;//LINIJA CODE-A U KOJOJ JE NASTAO IZUZETAK

public:
	Izuzetak(const string &funkcija, const int &linija, const char* poruka) :exception(poruka) {
		_funkcija = funkcija;
		_linija = linija;
	}

	Izuzetak(const Izuzetak &izuzetak) :exception(izuzetak.what()) {
		_datum = izuzetak._datum;
		_funkcija = izuzetak._funkcija;
		_linija = izuzetak._linija;
	}

	friend ostream & operator<<(ostream &cout, const Izuzetak &izuzetak) {
		//cout << "Datum: " << izuzetak._datum << endl;
		cout << "Funkcija: " << izuzetak._funkcija << endl;
		cout << "Linija: " << izuzetak._linija << endl;
		cout << izuzetak.what() << endl;
		return cout;
	}

};

template<class T1, class T2, int max>
class Kolekcija {
	T1 _elementi1[max];
	T2 _elementi2[max];
	int * _trenutno;

public:

	bool operator==(const Kolekcija &kolekcija)const 
	{
		int vel = *_trenutno;
		if (vel != *kolekcija.GetTrenutno())
			return false;

		for (int i = 0; i < vel; i++)
			if (_elementi1[i] != kolekcija.GetElement1(i) || _elementi2[i] != kolekcija.GetElement2(i))
				return false;

		return true;
	}

	bool operator!=(const Kolekcija &kolekcija)const
	{
		return !(*this == kolekcija);
	}


	T1 &operator[](const int &lokacija)
	{
		return _elementi1[lokacija];
	}


	int size() const
	{
		return max;
	}


	friend ostream &operator<<(ostream &cout, const Kolekcija &kolekcija)
	{
		int vel = *kolekcija.GetTrenutno();
		
		for (int i = 0; i < vel; i++)
			cout << kolekcija.GetElement1(i) << " - " << kolekcija.GetElement2(i) << endl;
		cout << crt;
		
		return cout;
	}

	int *GetTrenutno() const { return _trenutno; }


	void operator=(const Kolekcija &kolekcija)
	{
		int vel = *kolekcija.GetTrenutno();
		for (int i = 0; i < vel; i++)
			AddElement(kolekcija.GetElement1(i), kolekcija.GetElement2(i));
	}


	Kolekcija() { _trenutno = new int(0); }

	T1 GetElement1(const int &lokacija) const
	{
		if (lokacija >= 0 && lokacija < *_trenutno)
			return _elementi1[lokacija];
		else
			throw Izuzetak(/*__DATE__*/ __FUNCTION__, __LINE__, "Element ne postoji na ovoj lokaciji.");
	}
	T2 GetElement2(const int &lokacija) const
	{
		if (lokacija >= 0 && lokacija < *_trenutno)
			return _elementi2[lokacija];
		else
			throw Izuzetak(/*__DATE__*/ __FUNCTION__, __LINE__, "Element ne postoji na ovoj lokaciji.");
	}

	void AddElement(const T1 &element1, const T2 &element2)
	{
		if (*_trenutno < max)
		{
			_elementi1[*_trenutno] = element1;
			_elementi2[*_trenutno] = element2;
			(*_trenutno)++;
		}
		else
			throw Izuzetak(/*__DATE__*/__FUNCTION__, __LINE__, "Nema mjesta za dodavanje novih elemenata.");
	}

	int GetMax() const
	{
		return max;
	}

};



enum enumKursevi { HtmlCSSJavaScript, SoftwareEngeneeringFundamentals, MasteringSQL, WindowsSecurity };
const char *enumKurseviChar[] = { "HtmlCSSJavaScript", "SoftwareEngeneeringFundamentals", "MasteringSQL", "WindowsSecurity" };
class Kurs {
	enumKursevi _kurs;
	Datum _pocetak;
	Datum _kraj;
	char * _imePredavaca;
public:

	enumKursevi getKurs()const
	{
		return _kurs;
	}

	char* getImePredavaca()const
	{
		return _imePredavaca;
	}

	Kurs()
	{
		_imePredavaca = nullptr;
	}


	Datum getPocetak() const
	{
		return _pocetak;
	}
	Datum getKraj() const
	{
		return _kraj;
	}

	void operator=(const Kurs &kurs)
	{
		_kurs = kurs._kurs;
		_pocetak = kurs._pocetak;
		_kraj = kurs._kraj;
		_imePredavaca = AlocirajKaraktere(kurs._imePredavaca);
	}
	
	bool operator==(const Kurs &kurs) const
	{
		if (_kurs != kurs._kurs)
			return false;
		else if (!(strcmp(_imePredavaca, kurs._imePredavaca) == 0))
			return false;
		else if (_pocetak != kurs._pocetak)
			return false;
		else if (_kraj != kurs._kraj)
			return false;
		return true;
	}


Kurs(const enumKursevi &kurs, const char* imePredavaca, const Datum &pocetak, const Datum &kraj)
{
	_kurs = kurs;
	_pocetak = pocetak;
	_kraj = kraj;
	_imePredavaca = AlocirajKaraktere(imePredavaca);
}
friend ostream &operator<<(ostream &cout, const Kurs &kurs)
{
	cout << "Ime predavaca: " << kurs._imePredavaca << endl;

	char *temp = kurs._pocetak.ToString();
	cout << "Pocetak: " << temp << endl;
	temp = kurs._kraj.ToString();
	cout << "Kraj: " << temp << endl;
	delete[] temp;

	cout << "Kurs: " << enumKurseviChar[kurs._kurs] << endl;
	return cout;
}


};
class Polaznik {
	static int ID;
	const int _polaznikID;
	//SVAKOM NOVOM POLAZNIKU AUTOMATSKI DODIJELITI NOVI ID (AUTOINCREMENT) POCEVSI OD BROJA 1
	char * _imePrezime;
	string _kontaktTelefon; //BROJ TELEFONA TREBA BITI U FORMATU (06X)XXX-XXX 
	Kolekcija<Kurs *, int, 10> _uspjesnoOkoncaniKursevi;
	//INT PREDSTAVLJA OSTVARENI PROCENAT NA ISPITU, A JEDAN POLAZNIK MOZE POLOZITI NAJVISE 10 KURSEVA
public:

	void AddUspjenoOkoncaniKurs(Kurs *kurs, const int &uspjeh)
	{
		_uspjesnoOkoncaniKursevi.AddElement(kurs, uspjeh);
	}

	int getPolaznikID() const { return _polaznikID; }

	bool operator==(const Polaznik &polaznik) const
	{
		if (!(strcmp(polaznik._imePrezime, _imePrezime) == 0))
			return false;
		else if (_uspjesnoOkoncaniKursevi != polaznik._uspjesnoOkoncaniKursevi)
			return false;

		return true;
	}

	bool operator!=(const Polaznik &polaznik)const { return !(*this == polaznik); }


	friend ostream& operator<<(ostream &cout, const Polaznik &polaznik)
	{
		cout << "Ime i prezime: " << polaznik._imePrezime << endl;
		cout << "Polaznik ID: " << polaznik._polaznikID << endl;
		cout << "Kontakt telefon: " << polaznik._kontaktTelefon << endl;
		int vel = *polaznik._uspjesnoOkoncaniKursevi.GetTrenutno();
		for (int i = 0; i < vel; i++)
			cout << polaznik._uspjesnoOkoncaniKursevi;
		cout << crt;
		return cout;
	}

	void operator=(const Polaznik &polaznik)
	{
		_imePrezime = AlocirajKaraktere(polaznik._imePrezime);
		_kontaktTelefon = polaznik._kontaktTelefon;
		int vel = *polaznik._uspjesnoOkoncaniKursevi.GetTrenutno();
		for (int i = 0; i < vel; i++)
			_uspjesnoOkoncaniKursevi.AddElement(polaznik._uspjesnoOkoncaniKursevi.GetElement1(i), polaznik._uspjesnoOkoncaniKursevi.GetElement2(i));

	}


	Polaznik(const char * imePrezime, string telefon) :_polaznikID(ID++) {
		int size = strlen(imePrezime) + 1;
		_imePrezime = new char[size];
		strcpy_s(_imePrezime, size, imePrezime);
		_kontaktTelefon = telefon;
	}
	~Polaznik() {
		delete[] _imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < _uspjesnoOkoncaniKursevi.size(); i++)
		{
			delete _uspjesnoOkoncaniKursevi[i];
			_uspjesnoOkoncaniKursevi[i] = nullptr;
		}
	}
};

int Polaznik::ID = 0;

class SkillsCentar {
	string _nazivCentra;
	vector<Kurs> _kursevi;//KURSEVI KOJE NUDI ODREDJENI CENTAR
	Kolekcija<Kurs, Polaznik *, 150> _aplikanti;
public:

	friend ostream &operator<<(ostream &cout, const SkillsCentar &skillCentar)
	{
		cout << "Nazivo centra: " << skillCentar._nazivCentra << endl;
		cout << "Aplikanti: \n" << skillCentar._aplikanti << endl;
		cout << "Kursevi: " << endl;
		int vel = skillCentar._kursevi.size();
		for (int i = 0; i < vel; i++)
			cout << skillCentar._kursevi[i] << endl;
		cout << crt;
		return cout;
	}


	//void operator=(const SkillsCentar &skillCentar)
	//{
	//	_nazivCentra = skillCentar._nazivCentra;
	//	int vel = skillCentar._kursevi.size();
	//	for (size_t i = 0; i < vel; i++)
	//		_kursevi.push_back(skillCentar._kursevi[i]);

	//	vel = *skillCentar._aplikanti.GetTrenutno();

	//	for (int i = 0; i < vel; i++)
	//		AddAplikaciju(_aplikanti.GetElement1(i), *_aplikanti.GetElement2(i));
	//}
/*
	SkillsCentar(const SkillsCentar &skillCentar)
	{
		_nazivCentra = skillCentar._nazivCentra;
		int vel = skillCentar._kursevi.size();
		for (size_t i = 0; i < vel; i++)
			_kursevi.push_back(skillCentar._kursevi[i]);

		vel = *skillCentar._aplikanti.GetTrenutno();

		for (int i = 0; i < vel; i++)
			AddAplikaciju(_aplikanti.GetElement1(i), *_aplikanti.GetElement2(i));
	}*/

	//ONEMOGUCITI UKLANJANJE KURSA KOJI SU VEC PRIJAVILI NEKI OD POLAZNIKA
	/*void RemoveKurs(const Kurs &kurs)
	{

	}*/



	//VRACA INFORMACIJE O POLAZNICIMA KOJI SU KOD ODREDJENOG PREDAVACA USPJESNO OKONCALI ODREDJENI KURS
	vector<Polaznik> GetPolazniciByPredavac(const char* imePolaznika, const enumKursevi &enumKurs)
	{
		const int vel = *_aplikanti.GetTrenutno();
		vector<Polaznik> temp;

		for (int i = 0; i < vel; i++)
			if (_aplikanti.GetElement1(i).getKurs() == enumKurs && strcmp(_aplikanti.GetElement1(i).getImePredavaca(), imePolaznika) == 0)
				temp.push_back(*_aplikanti.GetElement2(i));

		return temp;
	}

	//BROJ 1 OZNACAVA ID POLAZNIKA. FUNKCIJA JE ZADUZENA DA POLAZNIKU DODA INFORMACIJU O USPJESNO POLOZENOM KURSU 
	//KOJI JE POSLAN KAO PARAMETAR. 
	//PREDUSLOV ZA DODAVANJE JE DA JE POLAZNIK PRETHODNO APLICIRAO ZA TAJ KURS, 
	//TE DA JE NA ISPITU OSTVARIO VISE OD 55%
	void DodajUspjesnoOkoncanKurs(const int &idPolaznika, Kurs &kurs, const float &uspjeh)
	{
		if (uspjeh < 55)
			return;
		int vel = *_aplikanti.GetTrenutno();
		for (int i = 0; i < vel; i++)
			if (_aplikanti.GetElement2(i)->getPolaznikID() == idPolaznika)
				_aplikanti.GetElement2(i)->AddUspjenoOkoncaniKurs(&kurs, uspjeh);
	}

	//ONEMOGUCITI APLICIRANJE ZA KURSEVE KOJI NISU REGISTROVANI U CENTRU
	void AddAplikaciju(const Kurs &kurs, Polaznik &polaznik)
	{
		int vel = *_aplikanti.GetTrenutno();
		for (int i = 0; i < vel; i++)
		{
			if (_aplikanti.GetElement2(i)->getPolaznikID() == polaznik.getPolaznikID() && kurs == _aplikanti.GetElement1(i))
				throw Izuzetak(__FUNCTION__, __LINE__, "Pokusaj dodavanje istog polaznika na isti kurs.");
		}

		vel = _kursevi.size();
		for (int i = 0; i < vel; i++)
			if (kurs == _kursevi[i])
			{
				cout << "Aplikacija dodana. " << endl;
				_aplikanti.AddElement(kurs, &polaznik);
			}
	}

	void AddKurs(const Kurs &kurs) { _kursevi.push_back(kurs); }

	bool ProvjeriKoliziju(const Kurs &kurs)
	{
		for (int i = 0; i < _kursevi.size(); i++)
		{
			if (_kursevi[i] == kurs)
				throw Izuzetak(__FUNCTION__, __LINE__, "Pokusaj dodavanje identicnog kursa.");

			if (_kursevi[i].getKraj() >= kurs.getPocetak())
				return false;
		}
		return true;
	}


	SkillsCentar(string naziv) { _nazivCentra = naziv; }
	SkillsCentar(const SkillsCentar & obj) :_kursevi(obj._kursevi), _aplikanti(obj._aplikanti) {
		_nazivCentra = obj._nazivCentra;
	}
};
void main()
{
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas);
	Datum prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
	Kolekcija<int, int, 10> kolekcija1;
	try {
		for (size_t i = 0; i < kolekcija1.GetMax(); i++)
			kolekcija1.AddElement(i, i + 2);
	//FUNKCIJA TREBA BACITI IZUZETAK U SLUCAJ DA NEMA VISE PROSTORA ZA DODAVANJE NOVIH ELEMENATA
		
	cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
	cout << kolekcija1.GetElement1(20) << " " << kolekcija1.GetElement2(20) << endl;
	//FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO ELEMENT NA ZAHTIJEVANOJ LOKACIJI NE POSTOJI
	}
	
	catch (Izuzetak & err)
	{
		cout << "Greska -> " << err << endl;
	}

	cout << kolekcija1 << endl;
	Kolekcija<int, int, 10> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	if (*kolekcija1.GetTrenutno() == *kolekcija2.GetTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;
	Kolekcija<int, int, 10> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion
#pragma region TestiranjeKursa
	Kurs sef(SoftwareEngeneeringFundamentals, "Jasmin Azemovic", Datum(28, 1, 2016), Datum(15, 2, 2016));
	cout << sef << endl;
	Kurs msql(MasteringSQL, "Adel Handzic", Datum(28, 2, 2016), Datum(15, 3, 2016));
	sef = msql;
	if (sef == msql)//KURSEVI SU ISTI AKO POSJEDUJU IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA
		cout << "ISTI SU KURSEVI" << endl;
	Kurs msql2(msql);
	cout << msql2 << endl;
#pragma endregion
#pragma region TestiranjePolaznika
	string telefon1 = "(061)111-111";
	string telefon2 = "(061)111222";
	string telefon3 = "(061)111-333";

//	if (!ProvjeriFormatTelefona(telefon1))
//		cout << "Broj " << telefon1 << " nije validan" << endl;
//	if (!ProvjeriFormatTelefona(telefon2))
//		cout << "Broj " << telefon2 << " nije validan" << endl;
//	if (!ProvjeriFormatTelefona(telefon3))
//		cout << "Broj " << telefon3 << " nije validan" << endl;


	Polaznik denis("Denis Music", telefon1);
	Polaznik denis2("Denis2 Music2", telefon3);

#pragma endregion

#pragma region TestiranjeCentra
	try {
		SkillsCentar mostar("Skills Center Mostar");
		if (mostar.ProvjeriKoliziju(sef))
			//JEDAN KURS NE SMIJE POCETI DOK DRUGI TRAJE TJ. VRIJEME ODRZAVANJA KURSA SE NE SMIJE POKLAPATI
			mostar.AddKurs(sef);
		if (mostar.ProvjeriKoliziju(msql))
			mostar.AddKurs(msql);
		if (mostar.ProvjeriKoliziju(msql2))
			mostar.AddKurs(msql2);
		//ONEMOGUCITI DODAVANJE IDENTICNIH KURSEVA. FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO SE POKUSA DODATI IDENTICAN KURS
		mostar.AddAplikaciju(sef, denis);
		//ONEMOGUCITI APLICIRANJE ZA KURSEVE KOJI NISU REGISTROVANI U CENTRU
		mostar.AddAplikaciju(msql, denis);
		mostar.AddAplikaciju(msql, denis);
		//ONEMOGUCITI APLICIRANJE ZA ISTI KURS. FUNKCIJA BAZA IZUZETAK
		cout << denis2 << endl;
		denis2 = denis;
		if (denis == denis2)
			//POLAZNICI SU ISTI AKO POSJEDUJU ISTO IME I AKO SU POHADJALI ISTE KURSEVE
			cout << "ISTI SU" << endl;

		mostar.DodajUspjesnoOkoncanKurs(1, sef, 60);//BROJ 1 OZNACAVA ID POLAZNIKA. FUNKCIJA JE ZADUZENA DA POLAZNIKU DODA INFORMACIJU O USPJESNO POLOZENOM KURSU KOJI JE POSLAN KAO PARAMETAR. PREDUSLOV ZA DODAVANJE JE DA JE POLAZNIK PRETHODNO APLICIRAO ZA TAJ KURS, TE DA JE NA ISPITU OSTVARIO VISE OD 55%
		mostar.DodajUspjesnoOkoncanKurs(1, msql, 83);
		vector<Polaznik> listaPolaznika = mostar.GetPolazniciByPredavac("Jasmin Azemovic", SoftwareEngeneeringFundamentals);//VRACA INFORMACIJE O POLAZNICIMA KOJI SU KOD ODREDJENOG PREDAVACA USPJESNO OKONCALI ODREDJENI KURS

//		if (mostar.RemoveKurs(sef))//ONEMOGUCITI UKLANJANJE KURSA KOJI SU VEC PRIJAVILI NEKI OD POLAZNIKA
//			cout << "Kurs " << sef << " uspjesno uklonjen iz centra " << mostar << endl;

		SkillsCentar sarajevo = mostar;
		cout << sarajevo << endl;
	}
	catch (Izuzetak & err) {
		cout << err << endl;
	}
//#pragma endregion
	system("PAUSE>0");
}