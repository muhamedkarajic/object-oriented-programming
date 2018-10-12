#include <iostream>
using namespace std;

class Date
{
	int *_day;
	int *_month;
	int *_year;

public:

	void setDay(const int &day) { *_day = day; }
	void setMonth(const int &month) { *_month = month; }
	void setYear(const int &year) { *_year = year; }

	const char* getDateChar() const
	{
		if (_day == nullptr || _month == nullptr || _year == nullptr)
			return nullptr;

		char day[3], month[3], year[5];

		_itoa_s(*_day, day, 10);
		_itoa_s(*_month, month, 10);
		_itoa_s(*_year, year, 10);

		int len = 3;//date 11.10.2018

		len += strlen(day);
		len += strlen(month);
		len += strlen(year);


		char *temp = new char[len];
		strcpy_s(temp, len, day);
		strcat_s(temp, len, ".");
		strcat_s(temp, len, month);
		strcat_s(temp, len, ".");
		strcat_s(temp, len, year);

		return temp;
	}

	Date() { _day = _month = _year = nullptr; }
	
	Date(const int &day, const int &month, const int &year) {
		_day = new int(day);
		_month = new int(month);
		_year = new int(year);
	}
	
	bool leapYear() const { return *_year % 4 == 0 || *_year % 100 == 0 || *_year % 400 == 0; }

	int MonthDays(const int &month) const
	{
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			return 31;
		else if (month == 2)
			return 28 + leapYear();
		return 30;
	}

	bool ValiDate(const int &day, const int &month, const int &year) 
		{ return day >= 1 && day <= MonthDays(month) && month >= 1 && month <= 12 && year >= 2000; }

	Date(const Date &date)
	{
		_day = new int(*date._day);
		_month = new int(*date._month);
		_year = new int(*date._year);
	}

	void operator=(const Date &date)
	{
		_day = new int(*date._day);
		_month = new int(*date._month);
		_year = new int(*date._year);
	}

	Date AddDays(int day)//11.10.2018
	{
		Date newDate = *this;//operator=

		if (ValiDate(*newDate._day + day, *newDate._month, *newDate._year))
		{
			*newDate._day += day;
			return newDate;
		}

		int daysLeft;
		while (day > 0)
		{
			daysLeft = MonthDays(*newDate._month) - *newDate._day + 1;
			if (day >= daysLeft) {
				day -= daysLeft;
				(*newDate._month)++;
				*newDate._day = 1;
				if (*newDate._month > 12)
				{
					*newDate._month -= 12;
					(*newDate._year)++;
				}
			}
			else
			{
				(*newDate._day) += day;
				day = 0;
			}
		}

		(*newDate._day) += day;
		return newDate;
	}
};

int main()
{
	int day;
	Date date(11, 10, 2018);
	do
	{
		cin >> day;
		
		date.setDay(11);
		date.setMonth(10);
		date.setYear(2018);

		cout << date.AddDays(day).getDateChar() << endl;
	} while (day != 0);
	
	system("PAUSE>0");
}