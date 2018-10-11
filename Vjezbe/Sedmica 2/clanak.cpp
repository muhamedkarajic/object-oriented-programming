#include<iostream>

using namespace std;

const char* crt = "\n--------------------------------------\n";
class Vrijeme {
	int _sati;
	int _minute;
	int _sekunde;
public:
	//Konstruktor bez parametara
	Vrijeme() { _sati = _minute = _sekunde = 0; }
	//Konstruktor sa 3 parametra (sati, minute i sekunde)

	Vrijeme(int sati, int minute, int sekunde)
	{
		_sati = sati;
		_minute = minute;
		_sekunde = sekunde;
	}

	//Konstruktor sa 2 parametra (sati i minute)

	Vrijeme(int sati, int minute)
	{
		_sati = sati;
		_minute = minute;
		_sekunde = 0;
	}

	//Funkciju Info sa neobaveznim parametrom tipa bool koji određuje da li će vrijeme biti ispisano u punom formatu
	//(hh:mm:ss) ili u skraćenom formatu (hh:mm). Default-no funkcija vrši ispis u punom formatu.
	void Info(bool uslov = true)
	{
		if (uslov) cout << _sati << ":" << _minute << ":" << _sekunde << endl;
		else cout << _sati << ":" << _minute << endl;
	}

	//Funkciju Add koja kao rezultat vraća novi objekat tipa vrijeme koji predstavlja 
	//sumu vremena poslijeđenog kao parametar i instance this.
	Vrijeme Add(const Vrijeme &vrijeme)
	{
		Vrijeme temp = vrijeme;
		temp._sati += _sati;
		temp._minute += _minute;
		temp._sekunde += _sekunde;
		return temp;
	}

	//Funkciju Add koja kao rezultat vraća novi objekat tipa vrijeme koji predstavlja 
	//sumu parametra izraženog u minutama i vremena instance this.
	Vrijeme Add(const int &minute)
	{
		Vrijeme temp = *this;

		temp._sati += minute / 60;
		temp._minute += minute % 60;
		while(temp._minute >= 60)
		{
			temp._minute -= 60;
			temp._sati++;
		}

		return temp;
	}

	//Funkciju CompareTo koja vraća vrijednost tipa int u zavisnosti od toga da li je vrijeme instance this prije, jednako ili poslije
	//vremena proslijeđenog kao parametar.
	//Moguće povratne vrijednosti:
	//-1 - vrijeme instance this nastupa prije vremena v2
	// 0 - vrijeme instance this je jednako vremenu v2
	// 1 - vrijeme instance this nastupa nakon vremena v2

	int CompareTo(const Vrijeme & vrijeme)
	{
		int sekundeVrijeme = ((vrijeme._sati * 24) + vrijeme._minute) * 60 + vrijeme._sekunde;
		int sekunde = ((_sati * 24) + _minute) * 60 + _sekunde;

		if (sekunde < sekundeVrijeme)
			return -1;
		else if (sekunde == sekundeVrijeme)
			return 0;
		return 1;
	}
};


/*
Potrebno je kreirati aplikaciju za dijeljenje znanja putem razmjene članaka među korisnicima.

Izdvojene su sljedeće funkcionalnosti:
- Administrator sistema je zadužen za upravljanje korisničkim nalozima (Ime, Prezime, Email, DatumRegistracije, KorisnickoIme, Lozinka).
- Svaki članak (Naslov, Sadrzaj, Datum, Satnica, BrojPregleda) može sadržavati više tagova, ali pripada samo jednoj oblasti.
- Članke mogu dodavati svi registrovani korisnici.
- Korisnici aplikacije također mogu ostaviti komentar (Tekst, Datum, Popularnost) na određeni članak.
*/

/*
Na osnovu datih klasa implementirati opisane funkcionalnosti sistema. Po potrebi dopuniti klase novim atributima i/ili funkcijama.
*/

class Datum
{
	int _dan;
	int _mjesec;
	int _godina;
public:
	//Potrebne konstruktor i destruktor funkcije
	Datum(const int &dan = 1, const int &mjesec = 1, const int &godina = 2000)
	{
		_dan = dan;
		_mjesec = mjesec;
		_godina = godina;
	}

	//Funkciju Info
	void Info() { cout << _dan << "/" << _mjesec << "/" << _godina << endl; }
};

enum TipKorisnika { Administrator, Guest };
const char* TipKorisnikaChar[] = { "Administrator", "Guest" };

class Korisnik
{
	char _ime[30];
	char _korisnickoIme[20];
	char* _lozinka;
	TipKorisnika _tipKorisnika; //Administrator, Guest

public:
	const char* getIme() const { return _ime; }
	const char* getKorisnickoIme() const { return _korisnickoIme; }
	const char* getLozinka() const { return _lozinka; }
	TipKorisnika getTipKorisnika() const { return _tipKorisnika; }

	//Funkciju Info
	void Info()
	{
		cout << "Ime: " << _ime << endl;
		cout << "Korisnicko ime: " << _korisnickoIme << endl;
		cout << "Lozinka: " << _lozinka << endl;
		cout << "Tip korisnika: " << TipKorisnikaChar[_tipKorisnika] << endl;
	}

	Korisnik() { _lozinka = nullptr; }

	//Potrebne konstruktor i destruktor funkcije
	Korisnik(const char *ime, const char* korisnickoIme, const char* lozinka, const TipKorisnika &tipKorisnika)
	{

		strcpy_s(_ime, 30, ime);
		strcpy_s(_korisnickoIme, 20, korisnickoIme);

		int vel = strlen(lozinka)+1;
		_lozinka = new char[vel];
		strcpy_s(_lozinka, vel, lozinka);
	
		_tipKorisnika = tipKorisnika;
	}

	//Funkciju za promjenu korisničke lozinke
	void setLozinka(const char* lozinka)
	{
		delete[] _lozinka;
		int vel = strlen(lozinka) + 1;
		_lozinka = new char[vel];
		strcpy_s(_lozinka, vel, lozinka);
	}
};

class Komentar
{
	char* _tekst;
	Datum _datum;
	Vrijeme _satnica;
	int _popularnost;
	Korisnik* _autor;
public:
	void KopirajKomentar(const Komentar &komentar)
	{
		int vel = strlen(komentar._tekst) + 1;
		_tekst = new char[vel];
		strcpy_s(_tekst, vel, komentar._tekst);
		_datum = komentar._datum;
		_satnica = komentar._satnica;
		_popularnost = komentar._popularnost;
		_autor = new Korisnik(komentar._autor->getIme(), komentar._autor->getKorisnickoIme(), komentar._autor->getLozinka(), komentar._autor->getTipKorisnika());
	}

	//Funkciju Info
	void Info()
	{
		cout << "Tekst: " << _tekst << endl;
		cout << "Datum: ";
		_datum.Info();
		cout << "Satnica: ";
		_satnica.Info();
		cout << "POPULARNOST: " << _popularnost << endl;
		cout << "AUTOR: " << endl;
		_autor->Info();

	}

	//Potrebne konstruktor i destruktor funkcije
	Komentar() { _tekst = nullptr; _autor = nullptr; }

	Komentar(const char* tekst, const Datum &datum, const Vrijeme &satnica, const Korisnik &autor)
	{
		int vel = strlen(tekst)+1;
		_tekst = new char[vel];
		strcpy_s(_tekst, vel, tekst);

		_datum = datum;
		_satnica = satnica;

		_popularnost = 0;
		_autor = new Korisnik(autor.getIme(), autor.getKorisnickoIme(), autor.getLozinka(), autor.getTipKorisnika());
	}

	~Komentar()
	{
		delete[] _tekst;
		delete _autor; 
	}

	//Funkciju za izmjenu popularnosti komentara
	void setPopularnost(const int& popularnost) { _popularnost = popularnost; }
};

class Clanak
{
	char _naslov[150];
	char* _sadrzaj;
	Datum _datum;
	Vrijeme _satnica;
	int _brojPregleda;
	char* _tagovi[10];//cpp c++, ...
	char _oblast[100];//IT Informatika
	Korisnik* _autor;
	Komentar* _komentari; //ne treba na pocetku
	int _brojKomentara;
public:
	//Funkciju Info
	void Info()
	{
		cout << crt;
		cout << ">>\t\t" <<_naslov << "\t\t<<" << endl;
		cout << _sadrzaj << endl;
		cout << crt;
		_datum.Info();
		cout << "Pregledi: " << _brojPregleda << endl;
		cout << crt;
		for (int i = 0; i < 10; i++)
		{
			if (_tagovi[i] != nullptr)
				cout << _tagovi[i] << "   ";
			else
				break;
		}
		cout << crt;
		for (int i = 0; i < _brojKomentara; i++)
		{
			_komentari[i].Info();
			cout << "  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  " << endl;
		}

	}

	/*Funkciju za promjenu sadržaja i vremena promjene članka. 
	Kao verifikaciju dozvole potrebno je proslijediti korisničko ime autora članka.
	Samo kreator članka ima permisije da mijenja njegov sadržaj.
	*/
	void PromjeniSadrzaj(const char *sadrzaj, const Vrijeme& satnica, const char* korisnickoIme)
	{
		if (!strcmp(korisnickoIme, _autor->getKorisnickoIme()) == 0)
			return;

		_satnica = satnica;
		setSadrzaj(sadrzaj);
	}

	//Funkciju za dodavanje komentara
	void DodajKomentar(const Komentar &komentar)
	{
		Komentar* t = new Komentar[_brojKomentara + 1];
		
		for (int i = 0; i < _brojKomentara; i++)
			t[i].KopirajKomentar(_komentari[i]);

		t[_brojKomentara].KopirajKomentar(komentar);
		
		delete[] _komentari;
		_komentari = t;

		_brojKomentara++;

	}
	
	//POMOCNA FUNKCIJA
	void setTag(const char* tag, const int &lokacija)
	{
		if (lokacija >= 0 && lokacija <= 10)
		{
			delete[] _tagovi[lokacija];

			int vel = strlen(tag) + 1;
			_tagovi[lokacija] = new char[vel];
			strcpy_s(_tagovi[lokacija], vel, tag);
		}
	}

	//Funkciju za dodavanje tagova za članak
	void DodajTag(const char *tag)
	{
		for (int i = 0; i < 10; i++)
			if (_tagovi[i] == nullptr)
			{
				setTag(tag, i);
				return;
			}
	}

	void setSadrzaj(const char* sadrzaj)
	{
		delete[] _sadrzaj;

		int vel = strlen(sadrzaj) + 1;
		_sadrzaj = new char[vel];
		strcpy_s(_sadrzaj, vel, sadrzaj);
	}


	Clanak()
	{
		_sadrzaj = nullptr;
		for (int i = 0; i < 10; i++)
			_tagovi[i] = nullptr;
		_komentari = nullptr;
		_brojKomentara = 0;
	}

	Clanak(const char* naslov, const char *sadrzaj, const Datum& datum, const Vrijeme& satnica, const char* oblasti, const Korisnik& autor)
	{
		strcpy_s(_naslov, 150, naslov);

		_sadrzaj = nullptr;
		setSadrzaj(sadrzaj);

		_datum = datum;

		_satnica = satnica;

		_brojPregleda = 0;

		for (int i = 0; i < 10; i++)
			_tagovi[i] = nullptr;

		strcpy_s(_oblast, 100, oblasti);

		_autor = new Korisnik(autor.getIme(), autor.getKorisnickoIme(), autor.getLozinka(), autor.getTipKorisnika());

		_komentari = nullptr;
		_brojKomentara = 0;
	}
};

int main()
{
	//Kreirati testni program koji demonstrira implementirane funckionalnosti
	Vrijeme vrijemeTrenutno(11, 53, 25);
	Vrijeme vrijemeNakonSat(12, 53, 25);
	Vrijeme vrijemePrijeSat(10, 53, 25);

	switch (vrijemeTrenutno.CompareTo(vrijemeNakonSat))
	{
		case -1:
			cout << "-1 - vrijeme instance this nastupa prije vremena v2" << endl;
			break;
		case 0:
			cout << "0 - vrijeme instance this je jednako vremenu v2" << endl;
			break;
		case 1:
			cout << "1 - vrijeme instance this nastupa nakon vremena v2" << endl;
			break;
	}

	Datum danasnjiDatum(11, 10, 2018);

	Korisnik autor("Muhamed Karajic", "muhamedkarajic", "ovoTrebaRaditi", Administrator);
	Komentar komentar1("Ovo je moj komentar za dodajKomentar", danasnjiDatum, vrijemeTrenutno.Add(3), autor);
	Clanak clanak("Muhamedov Clanak", "Uspio rijesiti do kraja sata ovaj zadatak!", danasnjiDatum, vrijemeTrenutno, "Programiranje 3", autor);
	
	clanak.DodajKomentar(komentar1);
	autor.setLozinka("novaLozinka");
	Komentar komentar2("Ovo je moj drugi komentar za dodajKomentar", danasnjiDatum, vrijemeTrenutno.Add(10), autor);
	clanak.DodajKomentar(komentar2);
	
	clanak.DodajTag("Cpp");
	clanak.DodajTag("C++");
	clanak.DodajTag("c plus plus");
	
	clanak.PromjeniSadrzaj("Uspio rijesiti vecinu zadatka na satu programiranja 3. \nNadam se da je sad sve ispravno, koristiti heder filove je zamorno, \nmozda za vikend pogledam.", { 4,28,55 }, "muhamedkarajic");
	clanak.Info();

	system("PAUSE>0");
	return 0;
}
