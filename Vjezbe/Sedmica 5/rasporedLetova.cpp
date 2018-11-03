#include<iostream>

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
	int getSati() const { return *_sati; }
	int getSekunde() const { return *_sekunde; }
	int getMinute() const { return *_minute; }

	void operator=(const Vrijeme& vrijeme) {
		*_sati = *vrijeme._sati;
		*_minute = *vrijeme._minute;
		*_sekunde = *vrijeme._sekunde;
	}

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
	//Preklopiti operator << za ispis objekata tipa Vrijeme
	friend ostream &operator<<(ostream &cout, const Vrijeme& vrijeme) {
		cout << *vrijeme._sati << ":" << *vrijeme._minute << ":" << *vrijeme._sekunde << " ";
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
	~Let() { 
		cout << _kasnjenje << endl;
		
		delete[] _odrediste; _odrediste = nullptr; }

	/*Preklopiti operator + na način da omogućava sabiranje objekata tipa "Let" i cijelog broja, pri
	čemu se kao rezultat dobiva novi objekat tipa "Let", u kojem je vrijeme polijetanja pomjereno
	unaprijed za iznos određen drugim sabirkom (računato u minutama).
	Također preklopiti i operator "+=" koji osigurava da izraz oblika "X += Y uvijek ima isto značenje kao i izraz
	"X = X + Y" */
	Let operator+(int minute) {
		minute += _vrijemePolijetanja.getMinute();
		int sati = minute / 60;
		minute %= 60;
		
		return (Let(_oznaka, _odrediste, _brIzlazneKapije, _trajanje, _kasnjenje, 
			Vrijeme(sati + _vrijemePolijetanja.getSati(), minute, _vrijemePolijetanja.getSekunde())));
	}

	Vrijeme getVrijeme() const { return _vrijemePolijetanja; }


	/*Preklopiti operator "<<" koji treba da podrži ispis objekata tipa "Let" na ekran. 
	U slučaju da se radi o polijetanju bez kašnjenja, ispis bi trebao da izgleda kako slijedi:

	JFK 156 Atalanta    12:50   19:30   5

	Podaci predstavljaju redom: oznaku leta, naziv odredišta, vrijeme polijetanja, očekivano
	vrijeme slijetanja i broj izlazne kapije.

	U slučaju da se radi o letu koji kasni, ispis bi trebao izgledati kako slijedi:

	ZGK 932 Zagreb    15:50 (Planirano 15:30, Kasni 20 min)*/
	friend ostream& operator<<(ostream &cout, const Let& let) {
		cout << let._oznaka << " " << let._odrediste << let._vrijemePolijetanja << let._brIzlazneKapije << " ";
		return cout;
	}


	//Potrebne konstruktor i destruktor funkcije
	Let(const char *oznaka, const char *odrediste, const int& brIzlazneKapije, 
		const int& trajanje, const int& kasnjenje, const Vrijeme& vrijemePolijetanja = { 0,0,0 })
		:_vrijemePolijetanja(vrijemePolijetanja) {

		strncpy_s(_oznaka, 10, oznaka, _TRUNCATE);
		_odrediste = AlocirajChar(odrediste);
		_brIzlazneKapije = brIzlazneKapije;
		_trajanje = trajanje;
		_kasnjenje = kasnjenje;
	}



	//Funkciju sa jednim parametrom koja postavlja informaciju o eventualnom kašnjenju na vrijednost zadanu parametrom.
	void setKasnjenje(const int& kasnjenje) { _kasnjenje = kasnjenje; }

	/*Preklopiti unarni operator "!" putem kojeg je moguće saznati da li odgovarajući let kasni ili ne (vratiti logičku
	vrijednost "true" u slučaju kašnjenja, u suprotnom vratiti "false").*/
	bool operator!() const { return _kasnjenje > 0; }

	//Funkciju koja kao rezultat vraća trajanje leta.
	int getTrajanje() const { return _trajanje; }

	
	
	/* Funkciju kojom je moguće saznati očekivano vrijeme polijetanja kada se uračuna iznos kašnjenja
	u odnosu na predviđeno vrijeme polijetanja (preklopiti operator + u klasi Vrijeme). */

	//Funkciju koja vraća očekivano vrijeme slijetanja

	/*Preklopiti operator "++" na način da pomijera vrijeme polaska za jedan sat unaprijed.
	  Potrebno je podržati i prefiksnu i postfiksnu verziju ovog operatora.*/

	  /*Preklopiti relacione operatore "<" i ">" koji ispituju koji let nastupa ranije, odnosno kasnije.
		Operator "<" vraća logičku vrijednost "true" ukoliko polijetanje leta sa lijeve strane nastupa
		prije polijetanje leta sa desne strane, a u suprotnom vraća logičku vrijednost "false".
		Analogno vrijedi za operator ">". Prilikom upoređivanja treba uzeti u obzir i očekivano vrijeme kašnjenja,
		a ne samo planirano vrijeme polijetanja.*/

		
};


class RasporedLetova
{
	int _brojRegistrovanihLetova;
	const int _maksimalanBrojLetova;
	Let** _letovi;

public:
	RasporedLetova(int maksimalanBrojLetova) : _maksimalanBrojLetova(maksimalanBrojLetova),
		_letovi(new Let*[_maksimalanBrojLetova]), _brojRegistrovanihLetova(0)
	{

	}

	/*Preklopiti operator "+=" na način da registruje novi let u raspored. Raspored letova u svakom momentu treba biti sortiran
	  prema vremenu polijetanja. Voditi računa o maksimalnom broju letova.  Za potrebe poređenja vremena polaska letova preklopiti odgovarajuće operatore u klasi Vrijeme.*/

	  /*Preklopiti operator "-=" na način da ukljanja registrovani let sa oznakom definisanom putem desnog operanda.
	   Pri tome sačuvati redoslijed prethodno registrovanih letova. */

	   //Preklopiti operator "[]" na način da vraća objekat tipa Let na osnovu proslijeđene pozicije u rasporedu (pozicije kreću od 1).

	   /*Preklopiti operator "()" na način da letu sa definisanom oznakom pomjeri vrijeme polijetanja za vrijednost drugog parametra izraženog
		u minutama. */


		//Funkciju koja daje prosječno trajanje svih pohranjenih letova.


		/*Preklopiti operator "<<" koji ispisuje kompletan spisak svih letova, sortiran po očekivanim vremenima polazaka.
		  Za potrebe poređenja vremena polaska letova preklopiti odgovarajuće operatore u klasi Vrijeme. */

};

int main()
{
	Let let("A11234567893999", "xy", 0, 0, 0, {12,50,30 });
	cout << let << endl;

	Let let2(let + 1000);
	cout << let + 110 << endl;
	let2.setKasnjenje(2);
	Let let3(let2);
	let3.setKasnjenje(3);

	cout << let3 << endl << "kraj";

	system("pause>0");
	return 0;
}


