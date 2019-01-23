#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <regex>
#include <exception>
#include <mutex>

using namespace std;

const char *crt = "\n-----------------------------------------------\n";

enum Status { ZAHTJEV_ZAPRIMLJEN, ODUSTAO, ODBIJENA, IZDATA, ISTEKLA, PONISTENA };
enum Sortiranje { RASTUCI, OPADAJUCI };
enum Drzava { SAD, AUSTRALIJA, ENGLESKA };

class Datum {
	int *_dan, *_mjesec, *_godina;
public:

	bool operator<(const Datum& datum)
	{
		if (*_godina > *datum._godina)
			return false;
		else if (*_godina == *datum._godina)
			if (*_mjesec > *datum._mjesec)
				return false;
			else if (*_mjesec == *datum._mjesec)
				if (*_dan >= *datum._dan)
					return false;
		return true;
	}

	bool operator>(const Datum& datum)
	{
		if (*_godina < *datum._godina)
			return false;
		else if (*_godina == *datum._godina)
			if (*_mjesec < *datum._mjesec)
				return false;
			else if (*_mjesec == *datum._mjesec)
				if (*_dan <= *datum._dan)
					return false;
		return true;
	}

	int BrojGodina(const Datum& danas)
	{
		int godina = *danas._godina - *_godina - 1;
		if (*danas._mjesec > *_mjesec)
			godina++;
		else if (*danas._mjesec == *_mjesec)
			if (*danas._dan >= *_dan)
				godina++;
		return godina;
	}


	bool operator==(const Datum& datum)
	{
		return *_dan == *datum._dan && *_mjesec == *datum._mjesec && *_godina == *datum._godina;
	}

	bool operator!=(const Datum& datum)
	{
		return !(*this == datum);
	}


	void operator=(const Datum& datum)
	{
		*_dan = *datum._dan;
		*_mjesec = *datum._mjesec;
		*_godina = *datum._godina;
	}

	Datum(const Datum& datum)
	{
		_dan = new int(*datum._dan);
		_mjesec = new int(*datum._mjesec);
		_godina = new int(*datum._godina);
	}

	Datum& operator++()
	{
		*_dan += 1;
		return *this;
	}

	Datum operator++(int)
	{
		Datum datum(*this);
		*_dan += 1;
		return datum;
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
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
		return COUT;
	}
};

template<class T1, class T2, int max>
class FITKolekcija {
	T1 * _elementi1[max];
	T2 * _elementi2[max];
	int _trenutno;
public:

	T1 GetElement1(int lokacija)
	{
		return *_elementi1[lokacija];
	}

	//NA KOJI NAČIN ĆE SE VRŠITI SORTIRANJE PRVENSTVENO ZAVISI OD VRIJEDNOSTI PARAMETRA, 
	//A VRŠI SE NA OSNOVU VRIJEDNOSTI TIPA T1
	void Sortiraj(const Sortiranje tipSotiranja)
	{
		int l;

		for (int i = 0; i < _trenutno-1; i++)
		{
			l = i;
			for (int j = i+1; j < _trenutno; j++)
				if (tipSotiranja == OPADAJUCI && *_elementi1[j] > *_elementi1[l])
					l = j;
				else if(tipSotiranja == RASTUCI && *_elementi1[j] < *_elementi1[l])
					l = j;
			if (l != i)
			{
				swap(*_elementi1[i], *_elementi1[l]);
				swap(*_elementi2[i], *_elementi2[l]);
			}
		}
	}




	void Dodaj(const T1& e1, const T2& e2)
	{
		if (_trenutno == max)
			throw exception("Maksimalan broj elemenata se nalazi u nizu!");
		_elementi1[_trenutno] = new T1(e1);
		_elementi2[_trenutno++] = new T2(e2);
	}

	FITKolekcija() {
		for (size_t i = 0; i < max; i++) {
			_elementi1[i] = nullptr;
			_elementi2[i] = nullptr;
		}
		_trenutno = 0;
	}
	~FITKolekcija() {
		for (size_t i = 0; i < max; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
	}
	T1 ** GetT1() { return _elementi1; }
	T2 ** GetT2() { return _elementi2; }
	int GetTrenutno() { return _trenutno; }

	friend ostream& operator<< (ostream &COUT, FITKolekcija &obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
COUT << *obj._elementi1[i] << " " << *obj._elementi2[i] << endl;
return COUT;
	}
};


class Viza {
protected:
	Drzava _drzava;
	Datum _vazenjeOD;
	Datum _vazenjeDO;
	char * _napomena;
	// string se odnosi na razlog promjene statusa, a moguće je samo 10 izmjena statusa
	FITKolekcija<Status, string, 10> _statusi;
public:
	friend ostream& operator<<(ostream& cout, Viza* viza)
	{
		cout << "Drzava: " << viza->_drzava << endl;
		cout << "Vazenje: " << viza->_vazenjeOD << " - " << viza->_vazenjeDO << endl;
		if (viza->_napomena != nullptr)
			cout << "Napomena: " << viza->_napomena << endl;
		return cout;
	}
	void IzmjeniNapomenuStatusa(string pojam, string noviPojam)
	{
		string* s;
		regex reg(pojam);
		for (int i = 0; i < _statusi.GetTrenutno(); i++)
		{
			s = _statusi.GetT2()[i];
			*s = regex_replace(*s, reg, noviPojam);
		}
	}

	bool DodajStatus(Status status, string napomena)
	{
		/*STATUSI SE MOGU DODAVATI SAMO U REDOSLIJEDU U KOJEM SE NALAZE U ENUMERACIJI NPR.
		- NIJE MOGUĆE ODBITI VIZU AKO PRETHODNO NIJE IMALA STATUS DA JE ZAHTJEV_ZAPRIMLJEN;
		- NIJE MOGUĆE PONIŠTITI VIZU KOJA PRETHODNO NIJE IZDATA*/

		if (status == ODBIJENA && GetZadnjiStatus() != ZAHTJEV_ZAPRIMLJEN)
			return false;
		else if (status == PONISTENA && GetZadnjiStatus() != IZDATA)
			return false;

		_statusi.Dodaj(status, napomena);
		return true;
	}

	int GetZadnjiStatus()
	{
		int lokacija = _statusi.GetTrenutno() - 1;
		if (lokacija == -1)
			return -1;
		return _statusi.GetElement1(lokacija);
	}

	Drzava GetDrzava() {
		return _drzava;
	}

	Viza(const Viza& viza) :
		_vazenjeDO(viza._vazenjeDO), _vazenjeOD(viza._vazenjeOD)
	{
		if (viza._napomena != nullptr) {
			_napomena = new char[strlen(viza._napomena) + 1];
			strcpy_s(_napomena, strlen(viza._napomena) + 1, viza._napomena);
		}
		else
			_napomena = nullptr;
		_drzava = viza._drzava;
	}


	Viza(Drzava drzava, Datum _OD, Datum _DO, const char * napomena = nullptr) :
		_vazenjeDO(_DO), _vazenjeOD(_OD)
	{
		if (napomena != nullptr) {
			_napomena = new char[strlen(napomena) + 1];
			strcpy_s(_napomena, strlen(napomena) + 1, napomena);
		}
		else
			_napomena = nullptr;
		_drzava = drzava;
	}
	~Viza() { delete[] _napomena; _napomena = nullptr; }
	Datum GetVazenjeOD() { return _vazenjeOD; }
	Datum GetVazenjeDO() { return _vazenjeDO; }
	char * GetNapomena() { return _napomena; }
	FITKolekcija<Status, string, 10> & GetStatuse() { return _statusi; }
	virtual void Info() = 0;
};



class PoslovnaViza :public Viza {
	string _kompanija; //naziv kompanije koja potvrđuje da posluje sa aplikantom
public:
	PoslovnaViza(Drzava drzava, Datum _OD, Datum _DO, string kompanija, const char * napomena = nullptr) :
		Viza(drzava, _OD, _DO, napomena) {
		_kompanija = kompanija;
	}

	void Info()
	{
		cout << "Kompanija: " << _kompanija << endl;
		cout << "Drzava: " << _drzava << endl;
		cout << "Vazenje: " << _vazenjeOD << " - " << _vazenjeDO << endl;
		if (_napomena != nullptr)
			cout << "Napomena: " << _napomena << endl;
	}

	friend ostream & operator << (ostream & COUT, PoslovnaViza & obj) {
		COUT << obj._drzava << " " << obj._vazenjeOD << " " << obj._vazenjeDO << " " << obj._kompanija << endl;
		COUT << ((obj._napomena != nullptr) ? obj._napomena : "") << endl;
		COUT << "STATUSI -> " << obj._statusi << endl;
		return COUT;

	}

};

mutex mojGuard;


class TuristickaViza : public Viza {
	string _adresa; //adresa hotele ili drugog smještaja na kojoj će aplikant boraviti
public:

	string GetAdresa()
	{
		return _adresa;
	}

	TuristickaViza(Drzava drzava, Datum _OD, Datum _DO, string adresa, char * napomena = nullptr) : Viza(drzava, _OD, _DO, napomena) {
		_adresa = adresa;
	}
	friend ostream & operator << (ostream & COUT, TuristickaViza & obj) {
		COUT << obj._drzava << " " << obj._vazenjeOD << " " << obj._vazenjeDO << " " << obj._adresa << endl;
		COUT << ((obj._napomena != nullptr) ? obj._napomena : "") << endl;
		COUT << "STATUSI -> " << obj._statusi << endl;
		return COUT;
	}

	void Info()
	{
		mojGuard.lock();
		cout << "Adresa: " << _adresa << endl;
		this_thread::sleep_for(chrono::seconds(1));
		cout << "Drzava: " << _drzava << endl;
		cout << "Vazenje: " << _vazenjeOD << " - " << _vazenjeDO << endl;
		if(_napomena != nullptr)
			cout << "Napomena: " << _napomena << endl;
		mojGuard.unlock();

	}
};


class Aplikant {
	char * _imePrezime;
	Datum * _datumRodjenja;
	char * _brojPasosa;
	vector<Viza *> _vize;
public:
	friend ostream & operator << (ostream & COUT, Aplikant & obj) {
		COUT << obj._imePrezime << " " << obj._datumRodjenja << " " << obj._brojPasosa << endl;
		COUT << "VIZE -> " << endl;
		for (int i = 0; i < obj._vize.size(); i++)
			obj._vize[i]->Info();

		return COUT;
	}


	//U ZASEBNOJ NITI URADITI PRINTANJE VIZE... KORISTITI METODU SLEEP_FOR
	void PrintajVizu(Viza *viza)
	{
		
		for (int i = 0; i < _vize.size(); i++)
			if (_vize[i] == viza)
			{
				thread nThread(&Viza::Info, viza);
				nThread.join();
				return;
			}
	}


	//UNUTAR NAPOMENE MIJENJA SADRŽAJ "nemaju informaciju" SA "su upoznti sa" - KORISTITI REGEX
	void ZamijeniRijec(string pronadjiRijeci, string noveRijeci)
	{
		string pravilo = "(" + pronadjiRijeci + ")";
		std::regex e(pravilo);
		for (int i = 0; i < _vize.size(); i++)
			if (_vize[i]->GetNapomena() != nullptr)
				_vize[i]->IzmjeniNapomenuStatusa(pronadjiRijeci, noveRijeci);
	}

	//VRAĆA PODATKE O SVIM VIZAMA KOJE SU IZDATE ZA ODREĐENU DRŽAVU, A KOJE SU IMALE ODREĐENI STATUS
	vector<Viza *> GetVizeByDrzava(Drzava drzava, Status status)
	{
		vector<Viza *> vize;

		for (int i = 0; i < _vize.size(); i++)
			if (_vize[i]->GetDrzava() == drzava && _vize[i]->GetZadnjiStatus() == status)
				vize.push_back(_vize[i]);
		return vize;
	}



	/*
	STATUSI SE MOGU DODAVATI SAMO U REDOSLIJEDU U KOJEM SE NALAZE U ENUMERACIJI NPR.
	- NIJE MOGUĆE ODBITI VIZU AKO PRETHODNO NIJE IMALA STATUS DA JE ZAHTJEV_ZAPRIMLJEN;
	- NIJE MOGUĆE PONIŠTITI VIZU KOJA PRETHODNO NIJE IZDATA
	*/
	bool DodajStatus(Viza* viza, Status status, string napomena = "")
	{
		for (int i = 0; i < _vize.size(); i++)
			if(viza->GetVazenjeDO() == _vize[i]->GetVazenjeDO() && viza->GetVazenjeOD() == _vize[i]->GetVazenjeOD())
				return _vize[i]->DodajStatus(status, napomena);
		return false;
	}
	bool ImaPonistenaViza()
	{
		for (int i = 0; i < _vize.size(); i++)
			if (_vize[i]->GetZadnjiStatus() == PONISTENA)
				return true;
		return false;
	}

	/*NOVA VIZA SE NE MOŽE DODATI UKOLIKO:
	- JE APLIKANT MLAĐI OD 10 GODINA
	- U TOM PERIODU (ODNOSI SE NA PERIOD VIZE OD - DO) NE POSTOJI VAŽEĆA
	(POJAM VAŽEĆA PODRAZUMIJEVA DA JE POSLJEDNJI STATUS VIZE BIO IZDATA TJ.
	DA VIZA NIJE PONIŠTENA ILI ISTEKLA) VIZA ZA TU DRŽAVU, BEZ OBZIRA NA NJENU VRSTU.
	- JE NEKA OD RANIJIH VIZA PONIŠTENA (OVO SE ODNOSI SAMO NA VIZE ZA DRŽAVU: SAD)*/
	bool DodajVizu(Viza *viza)
	{
		int godina = _datumRodjenja->BrojGodina(viza->GetVazenjeOD());
		if (godina < 10)
			return false;

		//Status ZAHTJEV_ZAPRIMLJEN, ODUSTAO, ODBIJENA, IZDATA, ISTEKLA, PONISTENA
		//Drzava SAD, AUSTRALIJA, ENGLESKA

		for (int i = 0; i < _vize.size(); i++)
			if (_vize[i]->GetVazenjeDO() < viza->GetVazenjeOD() && viza->GetDrzava() == _vize[i]->GetDrzava())
				return false;
			else if (_vize[i]->GetDrzava() == SAD && ImaPonistenaViza())
				return false;

		TuristickaViza* tViza = dynamic_cast<TuristickaViza*>(viza);
		if (tViza != nullptr)
			_vize.push_back(new TuristickaViza(*tViza));

		PoslovnaViza* pViza = dynamic_cast<PoslovnaViza*>(viza);
		if (pViza != nullptr)
			_vize.push_back(new PoslovnaViza(*pViza));
	}



	Aplikant(const char * imePrezime, Datum datumRodjenja, const char * brPasosa) {
		int vel = strlen(imePrezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, imePrezime);
		vel = strlen(brPasosa) + 1;
		_brojPasosa = new char[vel];
		strcpy_s(_brojPasosa, vel, brPasosa);
		_datumRodjenja = new Datum(datumRodjenja);
	}
	~Aplikant() {
		delete[]_imePrezime; _imePrezime = nullptr;
		delete[]_brojPasosa; _brojPasosa = nullptr;
		delete _datumRodjenja; _datumRodjenja = nullptr;
		for (size_t i = 0; i < _vize.size(); i++)
		{
			delete _vize[i]; _vize[i] = nullptr;
		}
	}
	

	vector<Viza*> GetVize() { return _vize; }
};

void main() {

	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/



	Datum danas(15, 2, 2017);
	Datum sutra(++danas); // inkrementiranjem se uvecava dan za 1
	cout << sutra << endl;
	Datum prekosutra;
	Datum dat15022017(15, 2, 2017), dat18082017(18, 8, 2017), dat11052018(11, 5, 2018), dat11122017(11, 12, 2017);


	prekosutra = danas;
	if (prekosutra == danas)
		cout << "Datumi su jednaki" << endl;
	cout << danas << endl << sutra << endl << prekosutra << crt;

	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;

	FITKolekcija<int, int, 7> brojevi;
	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v13, v32);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v63, v13);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(197, 7);

	cout << brojevi << crt;
	//NA KOJI NAČIN ĆE SE VRŠITI SORTIRANJE PRVENSTVENO ZAVISI OD VRIJEDNOSTI PARAMETRA, 
	//A VRŠI SE NA OSNOVU VRIJEDNOSTI TIPA T1
	brojevi.Sortiraj(RASTUCI);
	cout << brojevi << crt;
	brojevi.Sortiraj(OPADAJUCI);
	cout << brojevi << crt;

	try
	{
		//U SLUČAJU PREKORAČENJA DEFINISANE VELIČINE KOLEKCIJE, POTREBNO JE BACITI IZUZETAK
		brojevi.Dodaj(v13, v196);
	}
	catch (exception & err)
	{
		cout << "Error -> " << err.what() << endl;
	}

	Aplikant jasmin("Jasmin Azemovic", Datum(15, 5, 1979), "BS6985645");
	PoslovnaViza poslovna(SAD, dat15022017, dat18082017, "Microsoft","nemaju informaciju");

	/*
	NOVA VIZA SE NE MOŽE DODATI UKOLIKO:
	- JE APLIKANT MLAĐI OD 10 GODINA
	- U TOM PERIODU (ODNOSI SE NA PERIOD VIZE OD - DO) NE POSTOJI VAŽEĆA 
	(POJAM VAŽEĆA PODRAZUMIJEVA DA JE POSLJEDNJI STATUS VIZE BIO IZDATA TJ. 
	DA VIZA NIJE PONIŠTENA ILI ISTEKLA) VIZA ZA TU DRŽAVU, BEZ OBZIRA NA NJENU VRSTU.
	- JE NEKA OD RANIJIH VIZA PONIŠTENA (OVO SE ODNOSI SAMO NA VIZE ZA DRŽAVU: SAD)
	*/
	if (jasmin.DodajVizu(&poslovna))
		cout << "Podaci o vizi uspješno zaprimljeni" << endl;
	
	if (jasmin.DodajStatus(&poslovna, ZAHTJEV_ZAPRIMLJEN, "provjeriti >>> nemaju informaciju <<< navode sa predstavnicima kompanije Microsoft"))
		cout << "Status vize uspijesno promijenjen" << endl;
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;


	if (jasmin.DodajStatus(&poslovna, PONISTENA, "predstavnicima kompanije Microsoft nemaju informaciju o posjeti navedenog aplikanta"))
		cout << "Status vize uspijesno promijenjen" << endl;
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;

	TuristickaViza turisticka(ENGLESKA, dat18082017, dat11122017, "Whitehall Pl, London SW1A 2BD, UK");


	jasmin.DodajVizu(&turisticka);
	if (jasmin.DodajStatus(&turisticka, ZAHTJEV_ZAPRIMLJEN))
		cout << "Status vize uspijesno promijenjen" << endl;
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;

	if (jasmin.DodajStatus(&turisticka, IZDATA)) {
		cout << "Status vize uspijesno promijenjen" << endl;
		//U ZASEBNOJ NITI URADITI PRINTANJE VIZE...KORISTITI METODU SLEEP_FOR
		jasmin.PrintajVizu(&turisticka);
	}
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;
	//VRAĆA PODATKE O SVIM VIZAMA KOJE SU IZDATE ZA ODREĐENU DRŽAVU, A KOJE SU IMALE ODREĐENI STATUS
	vector<Viza *> jasminVize = jasmin.GetVizeByDrzava(SAD, PONISTENA);

	//UNUTAR NAPOMENE MIJENJA SADRŽAJ "	" SA "su upoznti sa" - KORISTITI REGEX
	cout << "NAPOMNA: " << *jasmin.GetVize()[0]->GetStatuse().GetT2()[0] << endl;
	jasmin.ZamijeniRijec("nemaju informaciju", "su upoznti sa");
	cout << "NAPOMNA: " << *jasmin.GetVize()[0]->GetStatuse().GetT2()[0] << endl;
	system("PAUSE>0");
}