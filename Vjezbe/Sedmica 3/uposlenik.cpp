#include<iostream>
using namespace std;

const char* crt = "\n-----------------------------\n";
char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

int sifra = 0;

class Uposlenik {

	const int _sifra; //Automatski uvecavati za 1 za svakog novog uposlenika.
	char _ime[30];
	char _prezime[30];
	char* _radnoMjesto;

public:
	char* getRadnoMjesto()const { return _radnoMjesto; }
	const char* getIme() const { return _ime; }
	const char* getPrezime() const { return _prezime; }
	const int getSifra() const { return _sifra; }


	//Implementirati potrebne konstruktor i destruktor funkcije
	Uposlenik(const char* ime, const char* prezime, const char* radnoMjesto, int SIFRA = (sifra++)) : _sifra(SIFRA)
	{
		strncpy_s(_ime, ime, _TRUNCATE);
		strncpy_s(_prezime, prezime, _TRUNCATE);

		_radnoMjesto = AlocirajNizKaraktera(radnoMjesto);

	}

	~Uposlenik()
	{
		delete[] _radnoMjesto;
		_radnoMjesto = NULL;
	}

	//Ostale funkcije dodati po potrebi
	void Info() { cout << "(" << _sifra << ") " << _ime << " " << _prezime << " -> " << _radnoMjesto << endl; }

};


class Aktivnost {
	char* _naziv;
	bool _zavrsena;
	int* _trajanje; //Izrazeno u danima (KOMENTAR -> ja sam koristio kao sate)
	Uposlenik* _uposlenici[5];

public:
	void setNaziv(const char* naziv)
	{
		delete[] _naziv;
		_naziv = AlocirajNizKaraktera(naziv);
	}

	bool getZavrsena() const { return _zavrsena; }

	Uposlenik *getUposlenik(const int &sifra) const
	{
		for (int i = 0; i < 5; i++)
			if (_uposlenici[i] != nullptr && _uposlenici[i]->getSifra() == sifra)
				return _uposlenici[i];
		return nullptr;
	}

	//POMOCNA FUNKCIJA
	Uposlenik** getUposlenik() { return _uposlenici; }

	void setZavrsena(const bool &zavrsena = true) { _zavrsena = zavrsena; }
	char* getNaziv()const { return _naziv; }

	//POMOCNA FUNKCIJA
	void KopirajAktivnost(const Aktivnost& aktivnost)
	{
		delete[] _naziv;

		_naziv = AlocirajNizKaraktera(aktivnost._naziv);
		_zavrsena = aktivnost._zavrsena;
		
		*_trajanje = *aktivnost._trajanje;

		UkloniSveUposlenike();

		for (int i = 0; i < 5; i++)
			if (aktivnost._uposlenici[i] != nullptr)
				DodajUposlenika(*aktivnost._uposlenici[i]);

	}

	//POMOCNA FUNKCIJA
	bool PrediAktivnost(const Aktivnost& aktivnost) const
	{
		if (strcmp(aktivnost._naziv, _naziv) == 0)
			return true;
		return false;
	}

	void Info()
	{
		cout << _naziv << " (";
		if (_zavrsena)
			cout << "ZAVRSENA)" << endl;
		else
			cout << "AKTIVNA)" << endl;
		cout << "Trajanje od " << *_trajanje << " sata." << endl << endl;
		cout << "Uposlenici: " << endl;
		for (int i = 0; i < 5; i++)
			if(_uposlenici[i] != nullptr)
				_uposlenici[i]->Info();
		cout << crt;
	}

	//Implementirati potrebne konstruktor i destruktor funkcije
	Aktivnost(const char* naziv = "default", const int &trajanje = 0) {
		_naziv = AlocirajNizKaraktera(naziv);
		_zavrsena = false;
		_trajanje = new int(trajanje);
		for (int i = 0; i < 5; i++)
			_uposlenici[i] = nullptr;
	}


	//Funkciju koja omogucava angazovanje uposlenika na projektnoj aktivnosti. Funkcija treba da vrati vrijednost tipa
	//bool za uspjesno, odnosno neuspjesno dodavanje uposlenika. Nije moguce dodati istog uposlenika vise puta. Nije moguce
	//angazovati uposlenike na vec zavrsenoj aktivnosti.
	bool DodajUposlenika(const Uposlenik& uposlenik)
	{
		if (_zavrsena)
			return false;

		for (int i = 0; i < 5; i++)
			if (_uposlenici[i] != nullptr)
			{
				if (_uposlenici[i]->getSifra() == uposlenik.getSifra())
					return false;
			}
			else
			{
				_uposlenici[i] = new Uposlenik(uposlenik.getIme(), uposlenik.getPrezime(), uposlenik.getRadnoMjesto(), uposlenik.getSifra());
				return true;
			}
		return false;
	}


	//Funkciju koja uklanja uposlenika na aktivnosti sa sifrom proslijedjenom kao parametar.
	bool UkloniUposlenika(const int &sifra)
	{

		for (int i = 0; i < 5; i++)
			if (_uposlenici[i] != nullptr && sifra == _uposlenici[i]->getSifra())
			{
				delete _uposlenici[i];
				_uposlenici[i] = nullptr;
				int l = i;
				for (int j = i+1; j < 5; j++)
					if (_uposlenici[j] != nullptr)
						l = j;
				_uposlenici[i] = _uposlenici[l];
				_uposlenici[l] = nullptr;
				
				return true;
			}
		return false;
	}


	//Funkciju koja uklanja sve uposlenike angazovane na aktivnosti.
	void UkloniSveUposlenike() {
		for (int i = 0; i < 5; i++)
			if (_uposlenici[i] != nullptr)
			{
				delete _uposlenici[i];
				_uposlenici[i] = nullptr;
			}
	}
};

class Projekat {
	char* _naziv;
	char* _oblast;
	int _trajanje; //Izrazeno u mjesecima
	Aktivnost* _aktivnosti;
	int _brojAktivnosti;

public:
	Aktivnost *getAktivnosti() const { return _aktivnosti; }
	int getBrojAktivnosti() const { return _brojAktivnosti; }



	//Funkciju koja pronalazi 3 uposlenika koja su angazovana na najvecem broju nezavrsenih aktivnosti.
	Uposlenik **Naj3Uposlenika() // -> RADI
	{
		int *aktivnostiUposlenika = new int[sifra] {0};
		int tempSifra = 0;

		while (tempSifra != sifra)
		{
			aktivnostiUposlenika[tempSifra] = brojAngazmanaUposlenika(tempSifra, true);
			tempSifra++;
		}

		Uposlenik **uposlenici = new Uposlenik*[3];
		int max;
		for (int i = 0; i < 3; i++)
		{
			max = 0;
			for (int j = 1; j < sifra; j++)
				if (aktivnostiUposlenika[max] < aktivnostiUposlenika[j])
					max = j;

			Uposlenik *tempUposlenik = nullptr;
			for (int j = 0; j < _brojAktivnosti; j++)
			{
				tempUposlenik = _aktivnosti[j].getUposlenik(max);
				if (tempUposlenik != nullptr)
				{
					uposlenici[i] = tempUposlenik;
					aktivnostiUposlenika[max] = -1;
					break;
				}
			}
		}
		return uposlenici;
	}

	//POMOCNA
	void Info() const // -> RADI
	{
		cout << _naziv << "(" << _oblast << ")" << " -> " << _trajanje << " dana." << crt;
		cout << "Aktivnosti(" << _brojAktivnosti << "): " << crt;
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			cout << i + 1 << ": " << endl;
			_aktivnosti[i].Info();
		}
	}

	int vremenskiAngazmanaUposlenika(const int &sifra) const // -> RADI
	{
		int brojac = 0;
		for (int i = 0; i < _brojAktivnosti; i++)
			for (int j = 0; j < 5; j++)
				if (_aktivnosti[i].getUposlenik()[j] == nullptr)
					break;
				else if (_aktivnosti[i].getUposlenik()[j]->getSifra() == sifra && _aktivnosti[i].getZavrsena() == true)
					brojac++;

		return brojac;
	}



	int brojAngazmanaUposlenika(const int &sifra, bool samoZavrsene = false) const // -> RADI
	{
		int brojac = 0;
		for (int i = 0; i < _brojAktivnosti; i++)
			for (int j = 0; j < 5; j++)
				if (_aktivnosti[i].getUposlenik()[j] == nullptr)
					break;
				else if (_aktivnosti[i].getUposlenik()[j]->getSifra() == sifra)
					if (samoZavrsene && _aktivnosti[i].getZavrsena() == true)
						brojac++;
					else
						brojac++;

		return brojac;
	}

	//Funkciju koja pronalazi uposlenika sa najvecim brojem angazmana na aktivnostima.
	Uposlenik *NajUposlenik() // -> RADI
	{
		int *sviUposlenici = new int[sifra] {0};
		int tempSifra = 0;

		while (tempSifra != sifra)
		{
			sviUposlenici[tempSifra] = brojAngazmanaUposlenika(tempSifra);//true
			tempSifra++;
		}

		int max = 0;
		for (int i = 1; i < sifra; i++)
			if (sviUposlenici[max] < sviUposlenici[i])
				max = i;


		tempSifra = max;
		Uposlenik *tempUposlenik = nullptr;
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			tempUposlenik = _aktivnosti[i].getUposlenik(tempSifra);
			if (tempUposlenik != nullptr)
				return tempUposlenik;
		}
		return tempUposlenik;
	}

	//Funkciju koja ispisuje sve zavrsene aktivnosti na projektu.
	void IspisAktivnosti(const bool &zavrsene = true) // -> RADI
	{
		cout << "Ispis aktivnosti ";
		if (!zavrsene)
			cout << "ne";
		cout << "zavrsenih: " << endl;

		for (int i = 0; i < _brojAktivnosti; i++)
			if (_aktivnosti[i].getZavrsena() == zavrsene)
				_aktivnosti[i].Info();
	}

	//Funkciju koja uklanja sve uposlenike angazovane na aktivnosti sa nazivom proslijedjenim kao parametar.
	void UkloniUposlenikeSveUAktivnosti(const char* naziv) // -> RADI
	{
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(naziv, _aktivnosti[i].getNaziv()) == 0)
				_aktivnosti[i].UkloniSveUposlenike();
	}

	//Funkciju koja uklanja odredjenog uposlenika na aktivnosti. Ulazni parametri funkcije su naziv aktivnosti i sifra uposlenika.
	void UkloniUposlenikaUAktivnosti(const char* naziv, const int &sifra) // -> RADI
	{
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(naziv, _aktivnosti[i].getNaziv()) == 0)
				_aktivnosti[i].UkloniUposlenika(sifra);
	}

	//Funkciju koja treba da vrati sve uposlenike angazovane na odredjenoj aktivnosti. Ulazni parametar je naziv aktivnosti.
	Uposlenik** getUposlenici(const char* naziv) // -> RADI
	{
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(naziv, _aktivnosti[i].getNaziv()) == 0)
				return _aktivnosti[i].getUposlenik();
		return nullptr;
	}

	//Funkciju koja treba da postojecoj aktivnosti dodijeli novog uposlenika.
	bool DodajAktivnostiUposleniku(const char* naziv, const Uposlenik& uposlenik) // -> RADI 
	{
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(_aktivnosti[i].getNaziv(), naziv) == 0)
			{
				_aktivnosti[i].DodajUposlenika(uposlenik);
				return true;
			}
		return false;
	}

	//Funkciju koja oznacava aktivnost kao zavrsenu. Funkcija kao parametar prima naziv aktivnosti.
	void OznaciKaoZavrseno(const char* naziv) // -> RADI
	{
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(naziv, _aktivnosti[i].getNaziv()) == 0)
				_aktivnosti[i].setZavrsena();
	}

	//Funkciju za dodavanje projektnih aktivnosti. Sprijeciti dodavanje vise aktivnosti sa istim nazivom.
	//Za potrebe poredjenja aktivnosti kreirati funkciju unutar klase Aktivnosti.
	bool DodajAktivnost(const Aktivnost& aktivnost)// -> RADI
	{
		for (int i = 0; i < _brojAktivnosti; i++)
			if (_aktivnosti[i].PrediAktivnost(aktivnost))
				return false;

		Aktivnost* t = new Aktivnost[_brojAktivnosti + 1];
		for (int i = 0; i < _brojAktivnosti; i++)
			t[i].KopirajAktivnost(_aktivnosti[i]);

		delete[] _aktivnosti;
		_aktivnosti = t;

		_aktivnosti[_brojAktivnosti].KopirajAktivnost(aktivnost);
		_brojAktivnosti++;
	}

	//Implementirati potrebne konstruktor i destruktor funkcije.
	Projekat(const char* naziv, const char* oblast, const int& trajanje): _brojAktivnosti(0), _aktivnosti(0), _trajanje(trajanje) {
		_naziv = AlocirajNizKaraktera(naziv);
		_oblast = AlocirajNizKaraktera(oblast);
	}
};


/*Kreirati globalnu funkciju koja pronalazi najuspjesnijeg usposlenika na projektima proslijedjenim kao parametar.
Uposlenik se smatra najuspjesnijim ako je angazovan na najvecem broju zavrsenih aktivnosti. Ako vise uposlenika
ima isti broj zavrsenih aktivnosti, uspjesnijim se smatra onaj cije su aktivnosti trajale duze.
*/
//Funkciju koja pronalazi uposlenika sa najvecim brojem angazmana na aktivnostima.
Uposlenik *NajUposlenikSaTrajanjem(const Projekat& projekat) // -> RADI
{
	int *sviUposlenici = new int[sifra] {0};
	int *sviUposleniciVrijeme = new int[sifra] {0};
	int tempSifra = 0;

	while (tempSifra != sifra)
	{
		sviUposlenici[tempSifra] = projekat.brojAngazmanaUposlenika(tempSifra, true);//true
		sviUposleniciVrijeme[tempSifra] = projekat.vremenskiAngazmanaUposlenika(tempSifra);
		tempSifra++;
	}

	int max = 0;
	for (int i = 1; i < sifra; i++)
		if (sviUposlenici[max] < sviUposlenici[i])
			max = i;
		else if (sviUposlenici[max] == sviUposlenici[i] && sviUposleniciVrijeme[max] < sviUposleniciVrijeme[i])
			max = i;

	tempSifra = max;
	Uposlenik *tempUposlenik = nullptr;
	int vel = projekat.getBrojAktivnosti();
	for (int i = 0; i < vel; i++)
	{
		tempUposlenik = projekat.getAktivnosti()[i].getUposlenik(tempSifra);
		if (tempUposlenik != nullptr)
			return tempUposlenik;
	}
	return tempUposlenik;
}

int main()
{
	//Testirati sve dostupne funkcionalnosti
	Uposlenik uposlenik0("Keanu", "Reeves", "Programer");
	Uposlenik uposlenik1("Carrie‑Anne", "Moss", "Developer");
	Uposlenik uposlenik2("Laurence", "Fishburne", "Hacker");
	Uposlenik uposlenik3("Treba", "Ukloniti", "Bot");

	Aktivnost aktivnost("Pisanje programa", 3);
	aktivnost.DodajUposlenika(uposlenik0);
	aktivnost.DodajUposlenika(uposlenik1);
	aktivnost.DodajUposlenika(uposlenik2);//nije dodalo ponovo radi
	aktivnost.DodajUposlenika(uposlenik2);
	aktivnost.DodajUposlenika(uposlenik3);//potrebno ukloniti
	aktivnost.Info();

	system("PAUSE>0");
	system("CLS");
	aktivnost.UkloniUposlenika(3);//uklonjeno...
	aktivnost.Info();

	system("PAUSE>0");
	system("CLS");
	cout << "Get uposlenik0: " << endl;
	aktivnost.getUposlenik(0)->Info();//radi ispravno

	system("PAUSE>0");
	system("CLS");
	Projekat projekat("Izrada programa", "Programiranje", 5);
	projekat.Info();

	system("PAUSE>0");
	system("CLS");

	projekat.DodajAktivnost(aktivnost);
	Aktivnost aktivnost2;
	aktivnost2.KopirajAktivnost(aktivnost);
	aktivnost2.setZavrsena(true);
	aktivnost2.UkloniSveUposlenike();
	aktivnost2.DodajUposlenika(uposlenik3);//nece dodati jer je zavrsena
	aktivnost2.setZavrsena(false);
	aktivnost2.DodajUposlenika(uposlenik3);//dodaje...

	projekat.DodajAktivnost(aktivnost2);//nece dodati jer je naziv isti
	aktivnost2.setNaziv("Spam poruke");
	projekat.DodajAktivnost(aktivnost2);//treba dodati...
	projekat.Info();

	system("PAUSE>0");
	system("CLS");

	Aktivnost aktivnost3;
	projekat.DodajAktivnost(aktivnost3);//defaultni konstruktor
	projekat.Info();

	system("PAUSE>0");
	system("CLS");

	projekat.OznaciKaoZavrseno("default");//zavrseno...
	projekat.Info();//radi...

	system("PAUSE>0");
	system("CLS");

	Uposlenik uposlenik4("Novi", "Bot", "Web");
	
	projekat.DodajAktivnostiUposleniku("Spam poruke", uposlenik4);//radi
	projekat.Info();

	system("PAUSE>0");
	system("CLS");
	
	cout << "Uposlenici na aktivnosti (Pisanje programa) su:" << endl;

	Uposlenik** uposlenici = projekat.getUposlenici("Pisanje programa");
	for (int i = 0; i < 5; i++)
		if (uposlenici[i] != nullptr)
			uposlenici[i]->Info();
	cout << crt;
	system("PAUSE>0");
	system("CLS");

	projekat.UkloniUposlenikaUAktivnosti("Pisanje programa", 0);
	cout << "Uposlenici (bez mene) na aktivnosti (Pisanje programa) su:" << endl;
	for (int i = 0; i < 5; i++)
		if (uposlenici[i] != nullptr)
			uposlenici[i]->Info();
	cout << crt;

	system("PAUSE>0");
	system("CLS");
	
	projekat.UkloniUposlenikeSveUAktivnosti("Pisanje programa");
	cout << "Uposlenici (bez kolega) na aktivnosti (Pisanje programa) su:" << endl;
	for (int i = 0; i < 5; i++)
		if (uposlenici[i] != nullptr)
			uposlenici[i]->Info();
	cout << crt;
	cout << "Zao mi je kolege..." << endl;

	system("PAUSE>0");
	system("CLS");

	projekat.DodajAktivnostiUposleniku("Pisanje programa", uposlenik0);
	projekat.DodajAktivnostiUposleniku("Pisanje programa", uposlenik1);
	projekat.DodajAktivnostiUposleniku("Spam poruke", uposlenik2);
	projekat.DodajAktivnostiUposleniku("Spam poruke", uposlenik0);

	projekat.Info();

	system("PAUSE>0");
	system("CLS");

	cout << "Zaposlenik koji je najvise angazovan je: ";
	projekat.NajUposlenik()->Info(); //radi...
	
	system("PAUSE>0");
	system("CLS");

	cout << "Tri uposlenika koja su najvise bila angazovana: " << endl;
	Uposlenik **triUposlenika = projekat.Naj3Uposlenika();//izgleda da radi
	for (int i = 0; i < 3; i++)
		triUposlenika[i]->Info();

	system("PAUSE>0");
	system("CLS");

	projekat.OznaciKaoZavrseno("Spam poruke");//zavrseno...
	projekat.UkloniUposlenikaUAktivnosti("Spam poruke", 0);//Ukloniti uposlenika0 (mene)
	cout << "Uposlenik koji je najvise radio na projektima koji su sada zavrseni je: ";
	Uposlenik *noviUposlenik = NajUposlenikSaTrajanjem(projekat);//radi...
	noviUposlenik->Info();

	system("pause>0");
	return 0;
}