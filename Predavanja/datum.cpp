#include <iostream>
using namespace std;

class Datum
{
	int *_dan;
	int *_mjesec;
	int *_godina;

public:

	void setDan(const int &dan) { *_dan = dan; }
	void setMjesec(const int &mjesec) { *_mjesec = mjesec; }
	void setGodinu(const int &godina) { *_godina = godina; }

	const char* getDatumChar() const
	{
		if (_dan == nullptr || _mjesec == nullptr || _godina == nullptr)
			return nullptr;

		char dan[3], mjesec[3], godina[5];

		_itoa_s(*_dan, dan, 10);
		_itoa_s(*_mjesec, mjesec, 10);
		_itoa_s(*_godina, godina, 10);

		int vel = 3;//datum 11.10.2018

		vel += strlen(dan);
		vel += strlen(mjesec);
		vel += strlen(godina);


		char *temp = new char[vel];
		strcpy_s(temp, vel, dan);
		strcat_s(temp, vel, ".");
		strcat_s(temp, vel, mjesec);
		strcat_s(temp, vel, ".");
		strcat_s(temp, vel, godina);

		return temp;
	}

	Datum() { _dan = _mjesec = _godina = nullptr; }
	
	Datum(const int &dan, const int &mjesec, const int &godina) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	
	bool PrestupnaGodina() const { return *_godina % 4 == 0 || *_godina % 100 == 0 || *_godina % 400 == 0; }

	int DaniMjeseca(const int &mjesec) const
	{
		if (mjesec == 1 || mjesec == 3 || mjesec == 5 || mjesec == 7 || mjesec == 8 || mjesec == 10 || mjesec == 12)
			return 31;
		else if (mjesec == 2)
			return 28 + PrestupnaGodina();
		return 30;
	}

	bool ValidanDatum(const int &dan, const int &mjesec, const int &godina) 
		{ return dan >= 1 && dan <= DaniMjeseca(mjesec) && mjesec >= 1 && mjesec <= 12 && godina >= 2000; }

	Datum(const Datum &datum)
	{
		_dan = new int(*datum._dan);
		_mjesec = new int(*datum._mjesec);
		_godina = new int(*datum._godina);
	}

	void operator=(const Datum &datum)
	{
		_dan = new int(*datum._dan);
		_mjesec = new int(*datum._mjesec);
		_godina = new int(*datum._godina);
	}

	Datum DodajDane(int dani)//11.10.2018
	{
		Datum noviDatum = *this;//operator=

		if (ValidanDatum(*noviDatum._dan + dani, *noviDatum._mjesec, *noviDatum._godina))
		{
			*noviDatum._dan += dani;
			return noviDatum;
		}

		int razlika;
		while (dani > 0)
		{
			razlika = DaniMjeseca(*noviDatum._mjesec) - *noviDatum._dan + 1;
			if (dani >= razlika) {
				dani -= razlika;
				(*noviDatum._mjesec)++;
				if (*noviDatum._mjesec > 12)
				{
					*noviDatum._mjesec -= 12;
					(*noviDatum._godina)++;
				}
				*noviDatum._dan = 1;
			}
			else
			{
				(*noviDatum._dan) += dani;
				dani = 0;
			}
		}

		(*noviDatum._dan) += dani;
		return noviDatum;
	}
};

int main()
{
	int dani;
	Datum datum(11, 10, 2018);
	do
	{
		cin >> dani;
		
		datum.setDan(11);
		datum.setMjesec(10);
		datum.setGodinu(2018);

		cout << datum.DodajDane(dani).getDatumChar() << endl;
	} while (dani != 0);
	
	system("PAUSE>0");
}