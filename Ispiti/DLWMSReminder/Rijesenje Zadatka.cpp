#include<iostream>
#include<string>
#include<vector>
#include<exception>
using namespace std;

const char* crt = "\n-----------------------------\n";

class Datum {
	int *_dan, *_mjesec, *_godina;
public:
	int Dani() const {
		return *_dan + *_mjesec * 100 + *_godina * 10000;
	}


	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	Datum(const Datum &dat) {
		_dan = new int(*dat._dan);
		_mjesec = new int(*dat._mjesec);
		_godina = new int(*dat._godina);
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}

	void operator=(const Datum &dat) {
		if (this != &dat)
		{
			*_dan = *dat._dan;
			*_mjesec = *dat._mjesec;
			*_godina = *dat._godina;
		}
	}

	friend ostream &operator<<(ostream &COUT, const Datum &obj) {
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}

};
class Izuzetak : public exception {
	string _funkcija;
public:
	Izuzetak(const char* opis, const char* funkcija): exception(opis), _funkcija(funkcija) {}
	friend ostream& operator<<(ostream& cout, const Izuzetak& izuzetak)
	{
		cout << "Opis: " << izuzetak.what() << endl;
		cout << "Funkcija: " << izuzetak._funkcija << endl;
		return cout;
	}
};

template <class T1, class T2>
class Kolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int _trenutnoElemenata;
	bool _omoguciDupliranjeElemenata;
public:
	Kolekcija(const Kolekcija& kolekcija) {
		_trenutnoElemenata = kolekcija._trenutnoElemenata;
		_omoguciDupliranjeElemenata = kolekcija._omoguciDupliranjeElemenata;
		_elementi1 = new T1[_trenutnoElemenata];
		_elementi2 = new T2[_trenutnoElemenata];
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			_elementi1[i] = kolekcija.GetElement1(i);
			_elementi2[i] = kolekcija.GetElement2(i);
		}
	}


	void operator=(const Kolekcija& kolekcija) {
		if (this != &kolekcija)
		{
			delete[] _elementi1;
			delete[] _elementi2;

			_trenutnoElemenata = kolekcija._trenutnoElemenata;
			_omoguciDupliranjeElemenata = kolekcija._omoguciDupliranjeElemenata;

			_elementi1 = new T1[_trenutnoElemenata];
			_elementi2 = new T2[_trenutnoElemenata];

			for (int i = 0; i < _trenutnoElemenata; i++)
			{
				_elementi1[i] = kolekcija.GetElement1(i);
				_elementi2[i] = kolekcija.GetElement2(i);
			}
		}
	}

	Kolekcija(bool omoguciDupliranjeElemenata = false) {
		_trenutnoElemenata = 0;
		_omoguciDupliranjeElemenata = omoguciDupliranjeElemenata;
		_elementi1 = nullptr;
		_elementi2 = nullptr;
	}

	~Kolekcija() {
		delete[]_elementi2; _elementi2 = nullptr;
		delete[]_elementi1; _elementi1 = nullptr;
		_trenutnoElemenata = 0;
	}

	/*AddElement :: omogucava dodavanje novog elementa u kolekciju. 
	Ukoliko je moguce, osigurati automatsko prosiranje kolekcije 
	prilikom dodavanja svakog novog elementa, 
	te onemoguciti ponavljanje elemenata*/
	bool AddElement(const T1& e1, const T2&e2) {
		if (!_omoguciDupliranjeElemenata)
			for (int i = 0; i < _trenutnoElemenata; i++)
				if (e1 == _elementi1[i] && e2 == _elementi2[i])
					return false;

		T1 * t1 = new T1[_trenutnoElemenata+1];
		T2 * t2 = new T2[_trenutnoElemenata+1];

		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			t1[i] = _elementi1[i];
			t2[i] = _elementi2[i];
		}

		t1[_trenutnoElemenata] = e1;
		t2[_trenutnoElemenata++] = e2;

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = t1;
		_elementi2 = t2;

		return true;
	}

	
	/*RemoveElement::na osnovu parametra tipa T1 uklanja elemente iz kolekcije i 
	ukoliko je moguce smanjuje velicinu niza / kolekcije.
	Prilikom uklanjanja elemenata ocuvati redoslijed njihovog dodavanja
	*/
	void RemoveElement(const T1& e1) {
		int lokacija = -1;
		for (int i = 0; i < _trenutnoElemenata; i++)
			if (e1 == _elementi1[i])
			{
				lokacija = i;
				T1 * t1 = new T1[_trenutnoElemenata - 1];
				T2 * t2 = new T2[_trenutnoElemenata - 1];

				bool pronadjen = false;
				for (int i = 0; i < _trenutnoElemenata; i++)
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

				_trenutnoElemenata--;

				if (!_omoguciDupliranjeElemenata)
					return;
		}
		if (lokacija == -1)
			throw Izuzetak("Element ne postoji.", __FUNCTION__);
	}



	int GetTrenutno() const { return _trenutnoElemenata; }
	T1& GetElement1(int lokacija) const
	{
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw Izuzetak("Nepostojeca lokacija", __FUNCTION__);
		return _elementi1[lokacija];
	}

	T2& GetElement2(int lokacija) const
	{
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw Izuzetak("Nepostojeca lokacija", __FUNCTION__);
		return _elementi2[lokacija];
	}

	friend ostream &operator<<(ostream &COUT, const Kolekcija &obj) {
		for (size_t i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		return COUT;
	}
};

class Dogadjaj
{
	char *_naziv;
	Datum _datumOdrzavanja;
	Kolekcija<string, bool> * _obaveze; //cuva informaciju o obavezama koje je potrebno ispuniti prije samog dogadjaja, string se odnosi na opis, a bool na izvrsenje te obaveze (da li je zavrsena ili ne)
	int _notificirajPrije; //(brojDana) oznacava broj dana prije samog dogadjaja kada ce krenuti notifikacija/podsjetnik
	bool _rekurzivnaNotifikacija; //ako je vrijednost true onda se korisnik notificira svaki dan do _datumaOdrzavanja dogadjaja, a pocevsi prije dogadjaja za _brojDanaZaNotifikaciju
public:
	Datum GetDatumOdrzavanja() const { return _datumOdrzavanja; }
	int GetNotificirajPrije() const { return _notificirajPrije; }
	float ObavezeProcenat()
	{
		int brojac = 0;
		for (int i = 0; i < _obaveze->GetTrenutno(); i++)
			if (_obaveze->GetElement2(i))
				brojac++;
		return ((float)brojac / _obaveze->GetTrenutno()) * 100.0;
	}

	int DatumNotificiranja()
	{
		return _datumOdrzavanja.Dani() - _notificirajPrije;
	}

	/*void operator=(const Dogadjaj& dogadjaj) {
		delete[] _naziv;
		delete[] _obaveze;
		
		_datumOdrzavanja = dogadjaj._datumOdrzavanja;
		
		_naziv = new char[strlen(dogadjaj._naziv) + 1];
		strcpy_s(_naziv, strlen(dogadjaj._naziv) + 1, dogadjaj._naziv);

		_notificirajPrije = dogadjaj._notificirajPrije;
		_rekurzivnaNotifikacija = dogadjaj._rekurzivnaNotifikacija;
		_obaveze = new Kolekcija<string, bool>(dogadjaj._obaveze);
	}*/


	bool operator==(const Dogadjaj& dogadjaj) {
		return _datumOdrzavanja.Dani() == dogadjaj._datumOdrzavanja.Dani() && strcmp(_naziv,dogadjaj._naziv) == 0;
	}

	bool operator<(const Dogadjaj& dogadjaj) {
		return _datumOdrzavanja.Dani() < dogadjaj._datumOdrzavanja.Dani() && strcmp(_naziv, dogadjaj._naziv) == 0;
	}

	bool operator>(const Dogadjaj& dogadjaj) {
		return _datumOdrzavanja.Dani() > dogadjaj._datumOdrzavanja.Dani() && strcmp(_naziv, dogadjaj._naziv) == 0;
	}



	/*po vlasitom izboru definisati listu zabranjenih rijeci koje ce onemoguciti dodavanje odredjene obaveze.
	Prilikom provjere koristiti regex*/
	//onemoguciti dupliranje obaveza
	bool AddObavezu(const string& obaveza)
	{
		if (_obaveze == nullptr)
			_obaveze = new Kolekcija<string, bool>;

		return _obaveze->AddElement(obaveza, false);
	}

	Dogadjaj(Datum datumOdrzavanja, const char *naziv, int brojDana = 1,
		bool rekurzivnaNotifikacija = false) : _datumOdrzavanja(datumOdrzavanja)
	{
		_naziv = new char[strlen(naziv) + 1];
		strcpy_s(_naziv, strlen(naziv) + 1, naziv);

		_notificirajPrije = brojDana;
		_rekurzivnaNotifikacija = rekurzivnaNotifikacija;
		_obaveze = nullptr;
	}

	Dogadjaj(const Dogadjaj &obj) : _datumOdrzavanja(obj._datumOdrzavanja)
	{
		_naziv = new char[strlen(obj._naziv) + 1];
		strcpy_s(_naziv, strlen(obj._naziv) + 1, obj._naziv);

		_notificirajPrije = obj._notificirajPrije;
		_rekurzivnaNotifikacija = obj._rekurzivnaNotifikacija;
		_obaveze = new Kolekcija<string, bool>(*obj._obaveze);
		
	}
	~Dogadjaj()
	{
		delete[] _naziv;
		_naziv = nullptr;
		delete _obaveze;
		_obaveze = nullptr;
	}

	
	char *GetNaziv() { return _naziv; }
	Kolekcija<string, bool> *GetObaveze() { return _obaveze; }
};

class Student
{
	int _indeks;
	string _imePrezime;
	vector<Dogadjaj> _dogadjaji;
public:

	string GetImePrezime() const { return _imePrezime; }

	Student(const Student& student)
	{
		_indeks = student._indeks;
		_imePrezime = student._imePrezime;
		int vel = student._dogadjaji.size();
		for (int i = 0; i < vel; i++)
			_dogadjaji.push_back(student._dogadjaji[i]);
	}
	bool operator==(const Student& student) {
		return _indeks == student._indeks;
	}
	bool AddDogadjaj(const Dogadjaj& dogadjaj)
	{
		/*for (int i = 0; i < _dogadjaji.size(); i++)
			if (_dogadjaji[i] == dogadjaj)
				return false;*/

		vector<Dogadjaj>::iterator it = _dogadjaji.begin();

		while (it != _dogadjaji.end())
			if (*it == dogadjaj)
				return false;
			else
				it++;
		_dogadjaji.push_back(dogadjaj);
		return true;
	}


	Student(int indeks, string imePrezime) : _indeks(indeks), _imePrezime(imePrezime) {}

	int GetIndeks() const { return _indeks; }

	vector<Dogadjaj>& GetDogadjaji() { return _dogadjaji; }

	friend ostream &operator<<(ostream &COUT, const Student &obj)
	{
		COUT << obj._imePrezime << " (" << obj._indeks << ")" << endl;
		return COUT;
	}
};

class DLWMSReminder
{
	vector<Student> _reminiderList;
public:
	/*metodi PosaljiNotifikacije se salje trenutni datum na osnovu cega ona pretrazuje sve studente koje
	treba podsjetiti/notoficirati o dogadjajima koji se priblizavaju.
	Koristeci multithread-ing, svim studentima se salju notifikacije sa sljedecim sadrzajem:
	-------------------------------------------------------------------------
	Postovani Jasmin Azemovic,
	Dogadjaj Ispit iz PRIII je zakazan za 3 dana, a do sada ste obavili 56% obaveza vezanih za ovaj dogadjaj. 
	Neispunjene obaveze su:
	1.Preraditi ispitne zadatke
	2.Samostalno vjezbati
	Predlazemo Vam da ispunite i ostale planirane obaveze.
	FIT Reminder
	-------------------------------------------------------------------------
	Dakle, notifikacije ce biti poslane svim studentima koji su dodali dogadjaj za 30.01.2018. godine i oznacili
	da zele da budu podsjecani ponovo/rekurzivno najmanje 2 dana prije samog dogadjaja (podaci se odnose na konkretan
	dogadjaj: Ispit iz PRIII)*/

	//funkcija vraca broj poslatih podsjetnika/notifikacija
	int PosaljiNotifikacije(const Datum &datum)
	{
		int brojac = 0;
		for (int i = 0; i < _reminiderList.size(); i++)
			for (int j = 0; j < _reminiderList[i].GetDogadjaji().size(); j++)
				if (_reminiderList[i].GetDogadjaji()[j].DatumNotificiranja() == datum.Dani())
				{
					cout << crt;

					cout << "Postovani " << _reminiderList[i].GetImePrezime() << endl;
					cout << "Dogadjaj " << _reminiderList[i].GetDogadjaji()[j].GetNaziv() << " je zakazan za " 
						 << _reminiderList[i].GetDogadjaji()[j].GetNotificirajPrije()
						 << " dana, a do sada ste obavili " << _reminiderList[i].GetDogadjaji()[j].ObavezeProcenat()
						 << " obaveza vezanih za ovaj dogadjaj." << endl;
					cout << "Neispunjene obaveze su : " << endl;

					int br = 1;
					for (int k = 0; k < _reminiderList[i].GetDogadjaji()[j].GetObaveze()->GetTrenutno(); k++)
						if (!_reminiderList[i].GetDogadjaji()[j].GetObaveze()->GetElement2(k))
						{
							cout << br++ << ". " << _reminiderList[i].GetDogadjaji()[j].GetObaveze()->GetElement1(k) << endl;
							brojac++;
						}
				}
		return brojac;
	}






	//da bi bila oznacena kao zavrsena, obaveza mora postojati i mora biti oznacena kao nezavrsena (false)
	bool OznaciObavezuKaoZavrsenu(const int& brojIndeksa, const char* nazivDogadjaja, const string& opisObaveze)
	{
		vector<Student>::iterator reminderListIt = _reminiderList.begin();

		while(reminderListIt != _reminiderList.end())
			if ((*reminderListIt).GetIndeks() == brojIndeksa)
			{
				vector<Dogadjaj>::iterator dogadjajiIt = (*reminderListIt).GetDogadjaji().begin();
				while (dogadjajiIt != (*reminderListIt).GetDogadjaji().end())
					if (strcmp(dogadjajiIt->GetNaziv(), nazivDogadjaja) == 0)
					{
						Kolekcija<string, bool> *obaveze = dogadjajiIt->GetObaveze();
						int vel = obaveze->GetTrenutno();
						for (int x = 0; x < vel; x++)
							if (obaveze->GetElement1(x) == opisObaveze && !obaveze->GetElement2(x))
								return obaveze->GetElement2(x) = true;
						dogadjajiIt++;
					}
					else dogadjajiIt++;

				reminderListIt++;
			}
			else reminderListIt++;
		return false;
	}

	void AddStudent(Student jasmin)
	{
		int vel = _reminiderList.size();
		for (int i = 0; i < vel; i++)
			if (jasmin == _reminiderList[i])
				throw Izuzetak("Nije moguce dodati istog studenta!", __FUNCTION__);

		_reminiderList.push_back(jasmin);
	}


};

void main() {

	/**************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
	3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_ParcijalniII.TXT
	5. NAZIVI FUNKCIJA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI PO ŽELJI.
	****************************************************************************/

#pragma region Datum

	Datum danas(28, 1, 2018), sutra(29, 1, 2018);
	Datum datumIspitaPRIII(30, 1, 2018), datumIspitBPII(31, 1, 2018);
	Datum prekosutra(danas);
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;

#pragma endregion

#pragma region Kolekcija

	/*
	AddElement :: omogucava dodavanje novog elementa u kolekciju. Ukoliko je moguce, osigurati automatsko prosiranje kolekcije prilikom dodavanja svakog novog elementa, te onemoguciti ponavljanje elemenata
	RemoveElement :: na osnovu parametra tipa T1 uklanja elemente iz kolekcije i ukoliko je moguce smanjuje velicinu niza/kolekcije. Prilikom uklanjanja elemenata ocuvati redoslijed njihovog dodavanja
	*/
	const int brElemenata = 10;
	Kolekcija<int, float> kolekcija1;
	for (size_t i = 0; i < brElemenata; i++)
		if (!kolekcija1.AddElement(i, i + (0.6 * i)))
			cout << "Elementi " << i << " i " << i + (0.6 * i) << " nisu dodati u kolekciju" << endl;

	cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << crt;
	cout << kolekcija1 << crt;

	kolekcija1.RemoveElement(1);

	try { kolekcija1.RemoveElement(100); } catch (const Izuzetak& err) { cout << err << crt; }

	Kolekcija<int, float> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;

	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
		cout << "ISTI BROJ ELEMENATA" << crt;

	Kolekcija<int, float> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;

#pragma endregion

#pragma region Dogadjaj

	Dogadjaj ispitPRIII(datumIspitaPRIII, "Ispit iz PRIII", 2, true),
			 ispitBPII(datumIspitBPII, "Ispit iz BPII", 7, true);
	/*po vlasitom izboru definisati listu zabranjenih rijeci koje ce onemoguciti dodavanje odredjene obaveze. 
	Prilikom provjere koristiti regex*/
	if (ispitPRIII.AddObavezu("Preraditi pdf materijale"))cout << "Obaveza dodana!" << endl;
	//onemoguciti dupliranje obaveza
	if (!ispitPRIII.AddObavezu("Preraditi pdf materijale"))cout << "Obaveza nije dodana!" << endl;
	if (ispitPRIII.AddObavezu("Pregledati video materijale"))cout << "Obaveza dodana!" << endl;
	if (ispitPRIII.AddObavezu("Preraditi ispitne zadatke"))cout << "Obaveza dodana!" << endl;
	if (ispitPRIII.AddObavezu("Samostalno vjezbati"))cout << "Obaveza dodana!" << endl;

	if (ispitBPII.AddObavezu("Preraditi knjigu SQL za 24 h"))cout << "Obaveza dodana!" << endl;
	if (ispitBPII.AddObavezu("Pregledati video materijale"))cout << "Obaveza dodana!" << endl;
	if (ispitBPII.AddObavezu("Napraviti bazu za konkretnu aplikaciju"))cout << "Obaveza dodana!" << endl;

	Student jasmin(150051, "Jasmin Azemovic"), adel(160061, "Adel Handzic");

	if (jasmin.AddDogadjaj(ispitPRIII) && jasmin.AddDogadjaj(ispitBPII))
		cout << "Dogadjaj uspjesno dodan!" << endl;
	


	if (adel.AddDogadjaj(ispitPRIII) && adel.AddDogadjaj(ispitBPII))
		cout << "Dogadjaj uspjesno dodan!" << endl;
	//onemoguciti dupliranje dogadjaja
	if (!adel.AddDogadjaj(ispitPRIII))
		cout << "Dogadjaj nije uspjesno dodan!" << endl;

	DLWMSReminder reminder;

	try
	{
		reminder.AddStudent(jasmin);
		reminder.AddStudent(adel);
		//u slucaju dupliranja studenata funkcija baca izuzetak tipa Izuzetak
		reminder.AddStudent(jasmin);
	}
	catch (const Izuzetak& err)
	{
		cout << err << endl;
	}

	catch (exception &err)
	{
		cout << "Greska: " << err.what() << endl;
	}

	//da bi bila oznacena kao zavrsena, obaveza mora postojati i mora biti oznacena kao nezavrsena (false)
	if (reminder.OznaciObavezuKaoZavrsenu(150051, "Ispit iz PRIII", "Pregledati video materijale"))
		cout << "Obaveza oznacena kao zavrsena" << endl;

	/*metodi PosaljiNotifikacije se salje trenutni datum na osnovu cega ona pretrazuje sve studente koje 
	treba podsjetiti/notoficirati o dogadjajima koji se priblizavaju.
	Koristeci multithread-ing, svim studentima se salju notifikacije sa sljedecim sadrzajem:
	-------------------------------------------------------------------------
	Postovani Jasmin Azemovic,
	Dogadjaj Ispit iz PRIII je zakazan za 3 dana, a do sada ste obavili 56% obaveza vezanih za ovaj dogadjaj. Neispunjene obaveze su:
	1.Preraditi ispitne zadatke
	2.Samostalno vjezbati
	Predlazemo Vam da ispunite i ostale planirane obaveze.
	FIT Reminder
	-------------------------------------------------------------------------
	Dakle, notifikacije ce biti poslane svim studentima koji su dodali dogadjaj za 30.01.2018. godine i oznacili 
	da zele da budu podsjecani ponovo/rekurzivno najmanje 2 dana prije samog dogadjaja (podaci se odnose na konkretan 
	dogadjaj: Ispit iz PRIII)

	*/
	int poslato = 0;
	//funkcija vraca broj poslatih podsjetnika/notifikacija
	poslato = reminder.PosaljiNotifikacije(danas);
	cout << "Za " << danas << " poslato ukupno " << poslato << " podsjetnika!" << endl;
	poslato = reminder.PosaljiNotifikacije(sutra);
	cout << "Za " << sutra << " poslato ukupno " << poslato << " podsjetnika!" << endl;

#pragma endregion

	system("pause>0");
}