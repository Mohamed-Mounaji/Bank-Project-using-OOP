#pragma warning(disable: 4996)
#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include <ctime>

using namespace std;
class clsDate
{
private:
	short _Day = 0;
	short _Month = 0;
	short _Year = 0;
public:
	clsDate()
	{
		*this = GetSystemDate();
	}
	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(string DateText)
	{
		*this = StringToDate(DateText);
	}
	clsDate(short DayOrderInYear, short Year)
	{
		*this = GetDateFromDayOrderInYear(DayOrderInYear, Year);
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}
	short GetDay()
	{
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month)
	{
		_Month = Month;
	}
	short GetMonth()
	{
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{
		_Year = Year;
	}
	short GetYear()
	{
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	void Print()
	{
		cout << ConvertDateToString();
	}

	static clsDate StringToDate(string DateText)
	{
		vector <string> DateSplitted = clsString::Split(DateText, "/");
		clsDate Date;
		Date.Day = stoi(DateSplitted.at(0));
		Date.Month = stoi(DateSplitted.at(1));
		Date.Year = stoi(DateSplitted.at(2));
		return Date;
	}

	static clsDate GetSystemDate()
	{
		short Day, Month, Year;
		time_t t = time(0);
		tm* now = localtime(&t);

		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;
		return clsDate(Day, Month, Year);
	}

	static string GetSystemDateTimeText()
	{
		time_t sTime = time(0);
		tm* CurrTime = localtime(&sTime);
		short Day, Month, Year, Hour, Minute, Second;

		Year = CurrTime->tm_year + 1900;
		Month = CurrTime->tm_mon + 1;
		Day = CurrTime->tm_mday;
		Hour = CurrTime->tm_hour;
		Minute = CurrTime->tm_min;
		Second = CurrTime->tm_sec;

		return to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) +
			" - " + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second);
	}

	static string ConvertDateToString(clsDate Date)
	{
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}
	string ConvertDateToString()
	{
		return ConvertDateToString(*this);
	}

	static bool isLeapYear(int Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}
	bool isLeapYear()
	{
		return isLeapYear(_Year);
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12)
			return 0;

		short Arr31Days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2 && isLeapYear(Year)) ? 29 : Arr31Days[Month];
	}

	static clsDate GetDateFromDayOrderInYear(short DayOrderInYear, short Year)
	{
		clsDate Date(0, 0, 0);
		short RemainingDays = DayOrderInYear;
		short MonthsDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthsDays = NumberOfDaysInAMonth(Date.Month, Year);

			if (RemainingDays > MonthsDays)
			{
				RemainingDays -= MonthsDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	static bool isDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}
	bool isDateBeforeDate2(clsDate Date2)
	{
		return isDate1BeforeDate2(*this, Date2);
	}

	static bool isLastDayInMonth(clsDate Date)
	{
		return Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year);
	}
	bool isLastDayInMonth()
	{
		return isLastDayInMonth(*this);
	}

	static bool isLastMonthInYear(short Month)
	{
		return (Month == 12);
	}
	bool isLastMonthInYear()
	{
		return isLastMonthInYear(_Month);
	}

	static clsDate IncreaseDateByOneDay(clsDate Date)
	{
		if (isLastDayInMonth(Date))
		{
			if (isLastMonthInYear(Date.Month))
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}
	void IncreaseDateByOneDay()
	{
		*this = IncreaseDateByOneDay(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;

		TempDate.Day = Date1.Day;
		TempDate.Month = Date1.Month;
		TempDate.Year = Date1.Year;

		Date1.Day = Date2.Day;
		Date1.Month = Date2.Month;
		Date1.Year = Date2.Year;

		Date2.Day = TempDate.Day;
		Date2.Month = TempDate.Month;
		Date2.Year = TempDate.Year;

	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SwapFlagValue = 1;

		if (!isDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}
		while (isDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return (IncludeEndDay) ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return  (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
	}
	bool IsDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (short i = 1; i < Month; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}

		TotalDays += Day;

		return TotalDays;
	}
	static short NumberOfDaysFromTheBeginingOfTheYear(clsDate Date)
	{
		return NumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);
	}
	short NumberOfDaysFromTheBeginingOfTheYear()
	{
		return NumberOfDaysFromTheBeginingOfTheYear(this->Day, this->Month, this->Year);
	}

	static clsDate AddDaysToDate(short Days, clsDate Date)
	{

		short DaysOrderInYear = NumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);
		short RemainingDays = DaysOrderInYear + Days;

		short MonthsDays = 0;
		Date.Month = 1;

		while (true)
		{
			MonthsDays = NumberOfDaysInAMonth(Date.Month, Date.Year);

			if (RemainingDays > MonthsDays)
			{
				RemainingDays -= MonthsDays;
				Date.Month++;

				if (Date.Month > 12)
				{
					Date.Month = 1;
					Date.Year++;
				}

			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;

	}
	void AddDays(short Days)
	{
		*this = AddDaysToDate(Days, *this);
	}

	static short DayOrderInTheWeek(short Day, short Month, short Year)
	{
		int A = (14 - Month) / 12;
		int Y = Year - A;
		int M = Month + (12 * A) - 2;

		return (Day + Y + (Y / 4) - (Y / 100) + (Y / 400) + (31 * M / 12)) % 7;
	}
	static short DayOrderInTheWeek(clsDate Date)
	{
		return DayOrderInTheWeek(Date.Day, Date.Month, Date.Year);
	}
	short DayOrderInTheWeek()
	{
		return DayOrderInTheWeek(*this);
	}

	static string MonthShortName(short MonthNumber)
	{
		string ArrMonthName[13] = { "","Jan","Feb","Mar","Apr"
			,"May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };

		return ArrMonthName[MonthNumber];
	}
	string MonthShortName()
	{
		return MonthShortName(this->Month);
	}

	static void PrintMonthCalendar(short Month, short Year)
	{

		short NumberOfDays = NumberOfDaysInAMonth(Month, Year);
		short current = DayOrderInTheWeek(1, Month, Year);

		printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());

		short i = 0;
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		for (i; i < current; i++)
		{
			printf("     ");
		}
		for (short j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);
			if (++i == 7)
			{
				i = 0;
				cout << endl;
			}
		}

		printf("\n  _________________________________\n");
	}
	void PrintMonthCalendar()
	{
		PrintMonthCalendar(this->_Month, this->_Year);
	}

	static void PrintYearCalendar(short Year)
	{

		printf("\n  _________________________________\n\n");
		printf("\t    Calendar %d", Year);
		printf("\n  _________________________________\n");

		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}
	}
	void PrintYearCalendar()
	{
		PrintYearCalendar(this->_Year);
	}

	static bool isEndOfWeek(short Day, short Month, short Year)
	{
		return (DayOrderInTheWeek(Day, Month, Year) == 0);

	}
	static bool isEndOfWeek(clsDate Date)
	{
		return isEndOfWeek(Date.Day, Date.Month, Date.Year);
	}
	bool isEndOfWeek()
	{
		return isEndOfWeek(this->Day, this->Month, this->Year);
	}

	static bool isWeekEnd(short Day, short Month, short Year)
	{
		short DayOrder = DayOrderInTheWeek(Day, Month, Year);
		return DayOrder == 6 || DayOrder == 0;
	}
	static bool isWeekEnd(clsDate Date)
	{
		return isWeekEnd(Date.Day, Date.Month, Date.Year);
	}
	bool isWeekEnd()
	{
		return isWeekEnd(*this);
	}

	static bool isBusinessDay(short Day, short Month, short Year)
	{
		return !isWeekEnd(Day, Month, Year);
	}
	static bool isBusinessDay(clsDate Date)
	{
		return isBusinessDay(Date.Day, Date.Month, Date.Year);
	}
	bool isBusinessDay()
	{
		return isBusinessDay(*this);
	}

	static short RemainingDaysInTheWeek(clsDate Date)
	{
		return 6 - DayOrderInTheWeek(Date);
	}
	static short RemainingDaysInTheWeek(short Day, short Month, short Year)
	{
		return RemainingDaysInTheWeek(clsDate(Day, Month, Year));
	}
	short RemainingDaysInTheWeek()
	{
		return RemainingDaysInTheWeek(*this);
	}

	static short RemainingDaysInMonth(clsDate Date)
	{
		clsDate EndOfMonthDate;
		EndOfMonthDate.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
		EndOfMonthDate.Month = Date.Month;
		EndOfMonthDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfMonthDate, true);
	}
	static short RemainingDaysInMonth(short Day, short Month, short Year)
	{
		return RemainingDaysInMonth(clsDate(Day, Month, Year));
	}
	short RemainingDaysInMonth()
	{
		return RemainingDaysInMonth(*this);
	}

	static short RemainingDaysInYear(clsDate Date)
	{
		clsDate EndOfYearDate;
		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfYearDate, true);
	}
	static short RemainingDaysInYear(short Day, short Month, short Year)
	{
		return RemainingDaysInYear(clsDate(Day, Month, Year));
	}
	short RemainingDaysInYear()
	{
		return RemainingDaysInYear(*this);
	}

	static short NumberOfHoursInAMonth(short Year, short Month)
	{
		return NumberOfDaysInAMonth(Year, Month) * 24;
	}

	static int NumberOfMinuteInAMonth(short Year, short Month)
	{
		return  NumberOfHoursInAMonth(Year, Month) * 60;
	}

	static int NumberOfSecondsInAMonth(short Year, short Month)
	{
		return NumberOfMinuteInAMonth(Year, Month) * 60;

	}

	static short NumberOfDaysInAYear(short Year)
	{
		return isLeapYear(Year) ? 366 : 365;
	}
	short NumberOfDaysInAYear()
	{
		return NumberOfDaysInAYear(this->_Year);
	}

	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}
	short  NumberOfHoursInAYear()
	{
		return NumberOfHoursInAYear(this->Year);
	}

	static int NumberOfMinuteInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}
	int NumberOfMinuteInAYear()
	{
		return NumberOfMinuteInAYear(this->Year);
	}

	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinuteInAYear(Year) * 60;
	}
	int NumberOfSecondsInAYear()
	{
		return NumberOfSecondsInAYear(this->Year);
	}

	static clsDate IncreaseDateByXDays(short Days, clsDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByXDays(short Days)
	{
		*this = IncreaseDateByXDays(Days, *this);
	}

	static clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(short Weeks, clsDate Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void IncreaseDateByXWeeks(short Weeks)
	{
		*this = IncreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}

		return Date;
	}
	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(short Months, clsDate Date)
	{

		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void IncreaseDateByXMonths(short Months)
	{
		*this = IncreaseDateByXMonths(Months, *this);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		Date.Year++;
		return Date;
	}
	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(short Years, clsDate Date)
	{
		Date.Year += Years;
		return Date;
	}
	void IncreaseDateByXYears(short Years)
	{
		*this = IncreaseDateByXYears(Years, *this);
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date)
	{
		Date.Year += 10;
		return Date;
	}
	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(short Decades, clsDate Date)
	{
		Date.Year += Decades * 10;
		return Date;
	}
	void IncreaseDateByXDecades(short Decades)
	{
		*this = IncreaseDateByXDecades(Decades, *this);
	}

	static clsDate IncreaseDateByOneCentury(clsDate Date)
	{
		Date.Year += 100;
		return Date;
	}
	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate Date)
	{
		Date.Year += 1000;
		return Date;
	}
	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Day = 31;
				Date.Year--;

			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
			}
		}
		else
		{
			Date.Day--;
		}

		return Date;
	}
	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(short Days, clsDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByXDays(short Days)
	{
		*this = DecreaseDateByXDays(Days, *this);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void DecreaseDateByXWeeks(short Weeks)
	{
		*this = DecreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
		{
			Date.Month--;
			if (Date.Day > NumberOfDaysInAMonth(Date.Month, Date.Year))
				Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
		}
		return Date;
	}
	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(short Months, clsDate Date)
	{

		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonths(short Months)
	{
		*this = DecreaseDateByXMonths(Months, *this);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date)
	{
		Date.Year--;
		return Date;
	}
	void DecreaseDateByOneYear()
	{
		*this = DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(short Years, clsDate Date)
	{
		Date.Year -= Years;
		return Date;
	}
	void DecreaseDateByXYears(short Years)
	{
		*this = DecreaseDateByXYears(Years, *this);
	}

	static clsDate DecreaseDateByOneDecade(clsDate Date)
	{
		Date.Year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade()
	{
		*this = DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(short Decades, clsDate Date)
	{
		Date.Year -= Decades * 10;
		return Date;
	}
	void DecreaseDateByXDecades(short Decades)
	{
		*this = DecreaseDateByXDecades(Decades, *this);
	}

	static clsDate DecreaseDateByOneCentury(clsDate Date)
	{
		Date.Year -= 100;
		return Date;
	}
	void DecreaseDateByOneCentury()
	{
		*this = DecreaseDateByOneCentury(*this);
		//this->Year -= 100;
	}

	static clsDate DecreaseDateByOneMillennium(clsDate Date)
	{
		Date.Year -= 1000;
		return Date;
	}
	void DecreaseDateByOneMillennium()
	{
		*this = DecreaseDateByOneMillennium(*this);
		//this->Year -= 1000;
	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		short DaysCounter = 0;
		while (isDate1BeforeDate2(DateFrom, DateTo))
		{
			if (isBusinessDay(DateFrom))
				DaysCounter++;
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return DaysCounter;
	}

	static clsDate GetReturnDateFromVacation(clsDate DateFrom, short Days)
	{
		short WeekendCounter = 0;

		for (short i = 1; i <= Days; i++)
		{
			if (isWeekEnd(DateFrom))
				WeekendCounter++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		for (short i = 1; i <= WeekendCounter; i++)
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		while (isWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DateFrom;
	}

	static bool isDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!isDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}
	bool isDate1AfterDate2(clsDate Date2)
	{
		return isDate1AfterDate2(*this, Date2);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };
	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (isDate1AfterDate2(Date1, Date2))
			return enDateCompare::After;

		if (isDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		return enDateCompare::Equal;

	}

	static bool isValidDate(clsDate Date)
	{
		if (Date.Month < 1 || Date.Month > 12)
			return false;
		if (Date.Day > NumberOfDaysInAMonth(Date.Month, Date.Year) || Date.Day < 1)
			return false;
		if (Date.Year < 1)
			return false;
		return true;
	}
	bool isValide()
	{
		return isValidDate(*this);
	}

	static string FormatDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormattedDateString = "";

		FormattedDateString = clsString::ReplaceWord(DateFormat, "dd", to_string(Date.Day), false);
		FormattedDateString = clsString::ReplaceWord(FormattedDateString, "mm", to_string(Date.Month), false);
		FormattedDateString = clsString::ReplaceWord(FormattedDateString, "yyyy", to_string(Date.Year), false);

		return FormattedDateString;
	}
	string FormatDate(string DateFormat = "dd/mm/yyyy")
	{
		return FormatDate(*this, DateFormat);
	}
};
