#include<iostream>
#include <exception>
using namespace std;

auto crt = "----------------------------------------------------\n";

char* AlocirajChar(const char *sadrzaj)
{
	if (sadrzaj == nullptr)
		return nullptr;

	int vel = strlen(sadrzaj) + 1;
	char *temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Vrijeme
{
	int* _sati;
	int* _minute;
	int* _sekunde;
public:
	~Vrijeme() {
		delete _sati; delete _minute; delete _sekunde;
		_sati = nullptr; _minute = nullptr; _sekunde = nullptr;
	}

	Vrijeme(int sati, int minute, int sekunde = 0) {
		_sati = new int(sati);
		_minute = new int(minute);
		_sekunde = new int(sekunde);
	}
	
	Vrijeme(const Vrijeme& v)
	{
		_sati = new int(*v._sati);
		_minute = new int(*v._minute);
		_sekunde = new int(*v._sekunde);
	}

	int getSati() const { return *_sati; }
	int getSekunde() const { return *_sekunde; }
	int getMinute() const { return *_minute; }

	int getVrijemeUSekundama() const { return ((*_sati) * 60 + *_minute) * 60 + *_sekunde; }

	void operator=(const Vrijeme& vrijeme) {
		*_sati = *vrijeme._sati;
		*_minute = *vrijeme._minute;
		*_sekunde = *vrijeme._sekunde;
	}

	bool operator<(const Vrijeme& vrijeme) const {
		if (*_sati < *vrijeme._sati)
			return true;
		else if (*_sati == *vrijeme._sati)
			if (*_minute < *vrijeme._minute)
				return true;
			else if (*_minute == *vrijeme._minute)
				if (*_sekunde < *vrijeme._sekunde)
					return true;
		return false;
	}

	bool operator<=(const Vrijeme& vrijeme) const {
		if (*this < vrijeme)
			return true;
		else if (*_sekunde <= *vrijeme._sekunde)
			return true;

		return false;
	}

	bool operator>(const Vrijeme& vrijeme) const {
		if (vrijeme < *this)
			return true;
		return false;
	}

	bool operator>=(const Vrijeme& vrijeme) const {
		if (*this > vrijeme)
			return true;
		else if (*_sekunde >= *vrijeme._sekunde)
			return true;
		return false;
	}

	Vrijeme operator++() {
		(*_sati)++;
		return *this;
	}

	Vrijeme operator++(int) {
		Vrijeme temp(*this);
		(*_sati)++;
		return temp;
	}

	Vrijeme operator+=(int minute) const {
		minute += *_minute;

		*_sati = minute / 60 + *_sati;
		*_minute = minute % 60;
	}


	Vrijeme operator+(int minute) const {
		minute += *_minute;
		int sati = minute / 60;
		minute %= 60;
		return Vrijeme(sati + *_sati, minute, *_sekunde);
	}

	//Preklopiti operator << za ispis objekata tipa Vrijeme
	friend ostream &operator<<(ostream &cout, const Vrijeme& vrijeme) {
		cout << *vrijeme._sati << ":" << *vrijeme._minute << /*":" << *vrijeme._sekunde << */" ";
		return cout;
	}
};


class Let
{
	static const  int _oznakaSize = 10;
	char _oznaka[_oznakaSize];
	char* _odrediste;
	int _brIzlazneKapije;
	Vrijeme _vrijemePolijetanja; //sati i minute
	int _trajanje; //izraženo u minutama
	int _kasnjenje; //izraženo u minutama

public:
	//Potrebne konstruktor i destruktor funkcije
	Let(const Let& let) :
		_vrijemePolijetanja(let._vrijemePolijetanja),
		_trajanje(let._trajanje),
		_kasnjenje(let._kasnjenje),
		_brIzlazneKapije(let._brIzlazneKapije)
	{
		strncpy_s(_oznaka, 10, let._oznaka, _TRUNCATE);
		_odrediste = AlocirajChar(let._odrediste);
	}

	Let(const char *oznaka = nullptr, const char *odrediste = nullptr, const int& brIzlazneKapije = 0,
		const int& trajanje = 0, const int& kasnjenje = 0, const Vrijeme& vrijemePolijetanja = { 0,0,0 }) :
		_vrijemePolijetanja(vrijemePolijetanja),
		_trajanje(trajanje),
		_kasnjenje(kasnjenje),
		_brIzlazneKapije(brIzlazneKapije)
	{
		if (oznaka == nullptr)
			_oznaka[0] = '\0';
		else
			strncpy_s(_oznaka, 10, oznaka, _TRUNCATE);

		_odrediste = AlocirajChar(odrediste);
	}

	~Let() { delete[] _odrediste; _odrediste = nullptr; }

	Vrijeme getVrijeme() const { return _vrijemePolijetanja; }

	//Funkciju koja kao rezultat vraća trajanje leta.
	int getTrajanje() const { return _trajanje; }

	const char* getOznakaLeta() const { return _oznaka; }

	//Funkciju koja vraća očekivano vrijeme slijetanja
	Vrijeme vrijemeSlijetanja()  const { return _vrijemePolijetanja + _trajanje + _kasnjenje; }

	/* Funkciju kojom je moguće saznati očekivano vrijeme polijetanja kada se uračuna iznos kašnjenja
	u odnosu na predviđeno vrijeme polijetanja (preklopiti operator + u klasi Vrijeme). */
	Vrijeme vrijemeKasnjenja() const { return _vrijemePolijetanja + _kasnjenje; }

	//Funkciju sa jednim parametrom koja postavlja informaciju o eventualnom kašnjenju na vrijednost zadanu parametrom.
	void setKasnjenje(const int& kasnjenje) { _kasnjenje = kasnjenje; }

	//Dodao za klasu RasporedLetova
	void operator=(const Let& let){
		delete[] _odrediste;
		_odrediste = nullptr;

		_vrijemePolijetanja = let._vrijemePolijetanja;
		_trajanje = let._trajanje;
		_kasnjenje = let._kasnjenje;
		_brIzlazneKapije = let._brIzlazneKapije;
		strcpy_s(_oznaka, let._oznaka);
		_odrediste = AlocirajChar(let._odrediste);
	}

	/*Preklopiti operator + na način da omogućava sabiranje objekata tipa "Let" i cijelog broja, pri
	čemu se kao rezultat dobiva novi objekat tipa "Let", u kojem je vrijeme polijetanja pomjereno
	unaprijed za iznos određen drugim sabirkom (računato u minutama).
	Također preklopiti i operator "+=" koji osigurava da izraz oblika "X += Y uvijek ima isto značenje kao i izraz
	"X = X + Y" */
	Let operator+(int minute) { return Let(_oznaka, _odrediste, _brIzlazneKapije, _trajanje, _kasnjenje, _vrijemePolijetanja + minute); }


	Let operator+=(int minute) { 
		_vrijemePolijetanja = _vrijemePolijetanja+minute;
		return *this; 
	
	}

	/*Preklopiti unarni operator "!" putem kojeg je moguće saznati da li odgovarajući let kasni ili ne (vratiti logičku
	vrijednost "true" u slučaju kašnjenja, u suprotnom vratiti "false").*/
	bool operator!() const { return _kasnjenje > 0; }

	/*Preklopiti relacione operatore "<" i ">" koji ispituju koji let nastupa ranije, odnosno kasnije.
	Operator "<" vraća logičku vrijednost "true" ukoliko polijetanje leta sa lijeve strane nastupa
	prije polijetanje leta sa desne strane, a u suprotnom vraća logičku vrijednost "false".
	Analogno vrijedi za operator ">". Prilikom upoređivanja treba uzeti u obzir i očekivano vrijeme kašnjenja,
	a ne samo planirano vrijeme polijetanja.*/

	bool operator<(const Let& let) const { return _vrijemePolijetanja < let._vrijemePolijetanja; }
	bool operator>(const Let& let) const { return _vrijemePolijetanja > let._vrijemePolijetanja; }

	/*Preklopiti operator "++" na način da pomijera vrijeme polaska za jedan sat unaprijed.
	Potrebno je podržati i prefiksnu i postfiksnu verziju ovog operatora.*/
	Let operator++(int) {//let++
		Let temp(*this);
		_vrijemePolijetanja++;
		return temp;
	}

	Let operator++() {//++let
		++_vrijemePolijetanja;
		return *this;
	}

	/*Preklopiti operator "<<" koji treba da podrži ispis objekata tipa "Let" na ekran.
	U slučaju da se radi o polijetanju bez kašnjenja, ispis bi trebao da izgleda kako slijedi:

	JFK 156 Atalanta    12:50   19:30   5

	Podaci predstavljaju redom: oznaku leta, naziv odredišta, vrijeme polijetanja, očekivano
	vrijeme slijetanja i broj izlazne kapije.

	U slučaju da se radi o letu koji kasni, ispis bi trebao izgledati kako slijedi:

	ZGK 932 Zagreb    15:50 (Planirano 15:30, Kasni 20 min)*/
	friend ostream& operator<<(ostream &cout, const Let& let) {
		if (let._kasnjenje == 0)
			cout << let._oznaka << " " << let._odrediste << let._vrijemePolijetanja + let._kasnjenje << " " << let.vrijemeSlijetanja() << let._brIzlazneKapije << " ";
		else
			cout << let._oznaka << " " << let._odrediste << " " << let._vrijemePolijetanja + let._kasnjenje
			<< "(Planirano " << let._vrijemePolijetanja << "Kasni " << let._kasnjenje << " min" << ") ";

		return cout;
	}
};


class RasporedLetova
{
	int _brojRegistrovanihLetova;
	const int _maksimalanBrojLetova;
	Let** _letovi;

	bool Pun() const { return _maksimalanBrojLetova == _brojRegistrovanihLetova; }

public:
	RasporedLetova(int maksimalanBrojLetova) : _maksimalanBrojLetova(maksimalanBrojLetova),
		_letovi(new Let*[_maksimalanBrojLetova]), _brojRegistrovanihLetova(0) {}

	/*Preklopiti operator "+=" na način da registruje novi let u raspored. Raspored letova u svakom momentu treba biti sortiran
	prema vremenu polijetanja. Voditi računa o maksimalnom broju letova.  
	Za potrebe poređenja vremena polaska letova preklopiti odgovarajuće operatore u klasi Vrijeme.*/
	bool operator+=(const Let& let) {
		if (Pun())
			return false;

		Let **t = new Let*[_brojRegistrovanihLetova+1];

		bool smjesten = false;
		for (int i = 0; i < _brojRegistrovanihLetova+smjesten; i++)
		{
			if (!smjesten && let < *_letovi[i])
			{
				t[i] = new Let(let);
				smjesten = true;
				continue;
			}
			t[i] = _letovi[i - smjesten];
			_letovi[i - smjesten] = nullptr;
		}
		delete[] _letovi;
		_letovi = t;
		if (!smjesten)
			t[_brojRegistrovanihLetova] = new Let(let);

		_brojRegistrovanihLetova++;
		return true;
	}

	/*Preklopiti operator "-=" na način da ukljanja registrovani let sa oznakom definisanom putem desnog operanda.
	Pri tome sačuvati redoslijed prethodno registrovanih letova. */
	void operator-=(const char* oznakaLeta) {
		for (int i = 0; i < _brojRegistrovanihLetova; i++)
			if (strcmp(oznakaLeta, _letovi[i]->getOznakaLeta()) == 0)
			{
				delete _letovi[i];
				for (int j = i; j < _brojRegistrovanihLetova - 1; j++)
					_letovi[j] = _letovi[j + 1];
				return;
			}
		_letovi[--_brojRegistrovanihLetova] = nullptr;
	}

	//Preklopiti operator "[]" na način da vraća objekat tipa Let na osnovu proslijeđene pozicije u rasporedu (pozicije kreću od 1).
	Let &operator[](const int& lokacija) {
		if (lokacija >= 1 && lokacija <= _brojRegistrovanihLetova)
			return *_letovi[lokacija - 1];
		
		throw exception("Let nije pronadjen.");
	}

	/*Preklopiti operator "()" na način da letu sa definisanom oznakom pomjeri vrijeme polijetanja za vrijednost drugog 
	parametra izraženog u minutama. */
	void operator()(const char* oznakaLeta, const int& minute)//valjda samo dodati minute na trenutno vrijeme polijetanja
	{
		for (int i = 0; i < _brojRegistrovanihLetova; i++)
			if (strcmp(oznakaLeta, _letovi[i]->getOznakaLeta()) == 0)
			{
				*_letovi[i] += minute;
				return;
			}
	}

	//Funkciju koja daje prosječno trajanje svih pohranjenih letova.
	Vrijeme ProsjecnoTrajanjeLetova()
	{
		int sekunde = 0;
		for (int i = 0; i < _brojRegistrovanihLetova; i++)
			sekunde += _letovi[i]->getVrijeme().getVrijemeUSekundama();
		
		sekunde /= _brojRegistrovanihLetova;
		int minute = sekunde / 60;
		sekunde %= 60;
		int sati = minute / 60;
		minute %= 60;

		return Vrijeme(sati,minute,sekunde);
	}

	/*Preklopiti operator "<<" koji ispisuje kompletan spisak svih letova, sortiran po očekivanim vremenima polazaka.
	Za potrebe poređenja vremena polaska letova preklopiti odgovarajuće operatore u klasi Vrijeme. */
	friend ostream& operator<<(ostream &cout, const RasporedLetova& rasporedLetova) {
		cout << ">>\t\tRaspored letova\t\t<<" << endl;
		for (int i = 0; i < rasporedLetova._brojRegistrovanihLetova; i++)
			cout << *rasporedLetova._letovi[i] << endl;
		cout << "\n>>\t\t--------------\t\t<<\n" << endl;
		return cout;
	}
};

int main()
{
	//JFK 156 Atalanta    12:50   19 : 30   5
	Vrijeme vrijeme(12,50,0);

	Let let("JFK 156", "Atlanta ", 5, (6 * 60 + 40), 0, { 12,50,10 });
	//ZGK 932 Zagreb 15:50 (Planirano 15:30, Kasni 20 min)* /
	Let zagreb("ZGK 932", "Zagreb ", 5, (6 * 60 + 40), 20, { 15, 30, 10 });
	let += 110;
	cout << let << endl;

	RasporedLetova letovi(5);

	letovi += zagreb;
	letovi += let;
	cout << letovi << endl;

	try {
		cout << "Prosjecno trajanje letova: " << letovi[1].getVrijeme() << " - " << letovi[2].getVrijeme() << " -> " << letovi.ProsjecnoTrajanjeLetova() << endl;
	}
	catch (const std::exception& error) { cout << error.what() << endl; }

	letovi -= "JFK 156";

	cout << letovi << endl;

	system("pause>0");
	return 0;
}


