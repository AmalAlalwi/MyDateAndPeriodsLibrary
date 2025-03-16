#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include<vector>
#include <string>
#include "clsString.h"
using namespace std;
class clsDate
{
	short _Year;
	short _Month;
	short _Day;
public:
	void setYear(short Year) {
		_Year = Year;
	}
	void setMonth(short Month) {
		_Month = Month;
	}
	void setDay(short Day) {
		_Day = Day;
	}
	short getYear() {
		return _Year;
	}
	short getMonth() {
		return _Month;
	}
	short getDay() {
		return _Day;
	}
	__declspec(property(get = getYear, put = setYear))short Year;
	__declspec(property(get = getMonth, put = setMonth))short Month;
	__declspec(property(get = getDay, put = setDay))short Day;
	clsDate() {
		time_t t = time(0);
		tm* now = localtime(&t);
		_Year = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day = now->tm_mday;
	}
	clsDate(int Day, int Month, int Year) {
		_Year = Year;
		_Month = Month;
		_Day = Day;
	}
	clsDate(string Date, string delim = "/") {
		vector<string>Date1 = clsString::SplitString(Date, delim);
		_Day = stoi(Date1[0]);
		_Month = stoi(Date1[1]);
		_Year = stoi(Date1[2]);
	}
	clsDate(short DayOrderInYear, short Year) {
		short i = 0;
		for (i = 1; i <= 12; i++) {
			if (DayOrderInYear > NumberOfDaysInMonth(Year, i)) {
				DayOrderInYear -= NumberOfDaysInMonth(Year, i);
			}
			else break;
		}
		_Year = Year;
		_Month = i;
		_Day = DayOrderInYear;
	}
	static bool IsLeapYear(int Year) {
		return (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0));

	}
	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}
	static short NumberOfDaysInYear(short Year) {
		return (IsLeapYear(Year) ? 366 : 365);
	}
	short NumberOfDaysInYear() {
		return NumberOfDaysInYear(_Year);
	}
	static short NumberOfHoursInYear(short Year) {
		return NumberOfDaysInYear(Year) * 24;
	}
	short NumberOfHoursInYear() {
		return NumberOfHoursInYear(_Year);
	}
	static int NumberOfMinutesInYear(int Year) {
		return NumberOfDaysInYear(Year) * 24 * 60;
	}
	int NumberOfMinutesInYear() {
		return NumberOfMinutesInYear(_Year);
	}
	static int NumberOfSecondsInYear(int Year) {
		return NumberOfDaysInYear(Year) * 24 * 60 * 60;
	}
	int NumberOfSecondsInYear() {
		return NumberOfSecondsInYear(_Year);
	}
	static short NumberOfDaysInMonth(short Year, short Month) {
		if (Month < 1 && Month>12) {
			return 0;
		}
		int NumberOfDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : (NumberOfDays[Month - 1]);
	}
	int  NumberOfDaysInMonth() {
		return NumberOfDaysInMonth(_Year, _Month);
	}
	static short NumberOfHoursInMonth(short Year, short Month) {
		return NumberOfDaysInMonth(Year, Month) * 24;
	}
	short NumberOfHoursInMonth() {
		return NumberOfHoursInMonth(_Year, _Month);
	}
	static int NumberOfMinutesInMonth(short Year, int Month) {
		return NumberOfHoursInMonth(Year, Month) * 60;
	}
	int NumberOfMinutesInMonth() {
		return NumberOfMinutesInMonth(_Year, _Month);
	}
	static int NumberOfSecondsInMonth(short Year, int Month) {
		return NumberOfMinutesInMonth(Year, Month) * 60;
	}
	int NumberOfSecondsInMonth() {
		NumberOfSecondsInMonth(_Year, _Month);
	}
	static short DayOfWeekOrder(clsDate Date) {
		short a = (14 - Date.Month) / 12;
		Date.Year = Date.Year - a;
		Date.Month = Date.Month + 12 * a - 2;
		return (Date.Day + Date.Year + Date.Year / 4 - Date.Year / 100 + Date.Year / 400 + ((31 * Date.Month) / 12)) % 7;

	}
	short DayOfWeekOrder() {
		return DayOfWeekOrder(*this);
	}
	static string NameOfDay(clsDate Date) {
		string arr[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
		return arr[DayOfWeekOrder(Date)];
	}
	string NameOfDay() {
		return NameOfDay(*this);
	}
	static string DayShortName(short DayOfWeekOrder)
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[DayOfWeekOrder];

	}
	static string NameOfMonth(short Month) {
		string arr[] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		return arr[Month - 1];
	}
	string NameOfMonth() {
		return NameOfMonth(_Month);
	}
	static void Calander(clsDate Date) {
		short StartDay = DayOfWeekOrder(Date);
		short NumDayInMonth = NumberOfDaysInMonth(Date.Year, Date.Month);
		cout << "___________" << NameOfMonth(Date.Month) << "_____________\n\n";
		cout << "Sun " << "Mon " << "Tus " << "Wed " << "The " << "Fri " << "Sat " << endl;
		short i = 0;
		for (i = 0; i < StartDay; i++)cout << "    ";

		for (short j = 1; j <= NumDayInMonth; j++) {
			if (j < 10)
				cout << j << "   ";
			else cout << j << "  ";
			if (++i > 6) {
				i = 0;
				cout << "\n";
			}

		}
		cout << "\n___________________________\n\n";
	}
	void Calander() {
		Calander(*this);
	}
	static void PrintYearCalander(short Year) {
		cout << "\n___________________________\n\n";
		cout << "        Calander: " << Year << "\n";
		cout << "\n___________________________\n\n";
		for (short i = 1; i <= 12; i++) {
			clsDate Date;
			Date.Year = Year;
			Date.Month = i;
			Date.Day = 1;
			Calander(Date);
		}
	}
	void PrintYearCalander() {
		PrintYearCalander(_Year);
	}
	static short NumberOfDaysFromTheBeginingOfTheYear(clsDate Date) {
		short SumDays = 0;
		for (int i = 1; i < Date.Month; i++) {
			SumDays += NumberOfDaysInMonth(Date.Year, i);
		}
		return SumDays + Date.Day;
	}
	static clsDate GetDateFromDayOrderInYear(short DayOrderInYear, short Year) {
		clsDate Date;
		short i = 0;
		for (i = 1; i <= 12; i++) {
			if (DayOrderInYear > NumberOfDaysInMonth(Year, i)) {
				DayOrderInYear -= NumberOfDaysInMonth(Year, i);
			}
			else break;
		}
		Date.Year = Year;
		Date.Month = i;
		Date.Day = DayOrderInYear;
		return Date;
	}
	void GetDateFromDayOrderInYear(short DayOrderInYear) {
		*this = GetDateFromDayOrderInYear(DayOrderInYear, _Year);
	}
	static clsDate DateAddDays(short DaysToAdd, clsDate& Date) {
		DaysToAdd += NumberOfDaysFromTheBeginingOfTheYear(Date);
		while (DaysToAdd > 366) {
			if (IsLeapYear(Date.Year + 1)) {
				DaysToAdd -= 366;
				Date.Year += 1;
			}
			else {
				DaysToAdd -= 365;
				Date.Year += 1;
			}
		}

	Date=GetDateFromDayOrderInYear(DaysToAdd, Date.Year);
	return Date;
	}
	void  DateAddDays(short DaysToAdd) {
		*this=DateAddDays(DaysToAdd, *this);
	}
	static bool CheckIfDate1EqualeDate2(clsDate Date1, clsDate date2) {
		return (Date1.Year == date2.Year && Date1.Month == date2.Month && Date1.Day == date2.Day);
	}
	bool CheckIfDate1EqualeDate2(clsDate Date1) {
		return  CheckIfDate1EqualeDate2(Date1, *this);
	}
	static bool CheckIfDate1SmallerThanDate2(clsDate Date1, clsDate Date2) {
		return (Date1.Year < Date2.Year) ? true : (Date1.Year == Date2.Year && Date1.Month < Date2.Month) ? true : (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day) ? true : false;
	}
	bool CheckIfDate1SmallerThanDate2(clsDate Date1) {
		return CheckIfDate1SmallerThanDate2(Date1, *this);
	}
	static bool CheckIfDayIsLastDayInMonth(clsDate date) {
		short NumDaysInMonth = NumberOfDaysInMonth(date.Year, date.Month);
		return (NumDaysInMonth == date.Day);
	}
	bool CheckIfDayIsLastDayInMonth() {
		return CheckIfDayIsLastDayInMonth(*this);
	}
	static bool CheckIfMonthIsLastMonthInYear(short Month) {
		return (Month == 12);
	}
	bool CheckIfMonthIsLastMonthInYear() {
		CheckIfMonthIsLastMonthInYear(_Month);
	}
	static clsDate AddOneDay(clsDate& date) {
		short NumDayInMonth = NumberOfDaysInMonth(date.Year, date.Month);
		if (CheckIfDayIsLastDayInMonth(date)) {
			if (CheckIfMonthIsLastMonthInYear(date.Month)) {
				date.Day = 1;
				date.Month = 1;
				date.Year++;
			}
			else {
				date.Day = 1;
				date.Month++;
			}
		}
		else {
			date.Day++;
		}
		return date;
	}
	void AddOneDay() {
		*this = AddOneDay(*this);
	}
	static void SwapDates(clsDate& date1, clsDate& date2) {
		clsDate TempDate = date1;
		TempDate.Year = date1.Year;
		TempDate.Month = date1.Month;
		TempDate.Day = date1.Day;

		date1.Year = date2.Year;
		date1.Month = date2.Month;
		date1.Day = date2.Day;

		date2.Year = TempDate.Year;
		date2.Month = TempDate.Month;
		date2.Day = TempDate.Day;

	}
	void SwapDates(clsDate& date1) {
		return SwapDates(date1, *this);
	}
	static int GetDifferenceInDays(clsDate date1, clsDate date2, bool EndDay = 0) {
		int DiffDate = 0, IsSwap = 1;
		if (!CheckIfDate1SmallerThanDate2(date1, date2)) {
			SwapDates(date1, date2);
			IsSwap = -1;
		}
		while (CheckIfDate1SmallerThanDate2(date1, date2)) {
			DiffDate++;
			AddOneDay(date1);
		}
		DiffDate *= IsSwap;
		return (EndDay) ? ++DiffDate * IsSwap : DiffDate * IsSwap;

	}
	int GetDifferenceInDays(clsDate Date1, bool EndDay = 0) {
		return GetDifferenceInDays(Date1, *this, EndDay);
	}
	static clsDate GetSystemDate() {
		clsDate date;
		time_t t = time(0);
		tm* now = localtime(&t);
		date.Year = now->tm_year + 1900;
		date.Month = now->tm_mon + 1;
		date.Day = now->tm_mday;
		return date;
	}
	static clsDate IncreaseDateByXDays(short Days, clsDate& Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByXDays(short Days) {
		*this = IncreaseDateByXDays(Days, *this);
	}
	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByOneWeek() {
		*this = IncreaseDateByOneWeek(*this);
	}
	static clsDate IncreaseDateByXWeeks(short Weeks, clsDate& Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void IncreaseDateByXWeeks(short Weeks) {
		*this = IncreaseDateByXWeeks(Weeks, *this);
	}
	static clsDate IncreaseDateByOneMonth(clsDate& Date) {
		if (Date.Month == 12) {
			Date.Month = 1;
			Date.Year += 1;
		}
		else {
			Date.Month++;
		}
		short NumOfDayInMonth = NumberOfDaysInMonth(Date.Year, Date.Month);
		if (Date.Day > NumOfDayInMonth) {
			Date.Day = NumOfDayInMonth;
		}
		return Date;
	}
	void IncreaseDateByOneMonth() {
		*this = IncreaseDateByOneMonth(*this);
	}
	static clsDate IncreaseDateByXMonths(clsDate Date, short Months) {
		for (int i = 1; i <= Months; i++) {
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void IncreaseDateByXMonths(short Months) {
		*this = IncreaseDateByXMonths(*this, Months);
	}
	static clsDate IncreaseDateByOneYear(clsDate date) {
		date.Year++;
		return date;
	}
	void IncreaseDateByOneYear() {
		*this = IncreaseDateByOneYear(*this);
	}
	static clsDate IncreaseDateByXYearsFaster(clsDate date, short Years) {
		date.Year += Years;
		return date;
	}
	void IncreaseDateByXYearsFaster(short Years) {
		*this = IncreaseDateByXYearsFaster(*this, Years);
	}
	static clsDate IncreaseDateByOneDecade(clsDate date) {
		date.Year += 10;
		return date;
	}
	void IncreaseDateByOneDecade() {
		*this = IncreaseDateByOneDecade(*this);
	}
	static clsDate IncreaseDateByXDecades(clsDate date, short Decades) {
		date.Year += 10 * Decades;
		return date;
	}
	void IncreaseDateByXDecades(short Decades) {
		*this = IncreaseDateByXDecades(*this, Decades);
	}
	static clsDate IncreaseDateByOneCentury(clsDate date) {
		date.Year += 100;
		return date;
	}
	void IncreaseDateByOneCentury() {
		*this = IncreaseDateByOneCentury(*this);
	}
	static clsDate IncreaseDateByOneMillennium(clsDate date) {
		date.Year += 1000;
		return date;
	}
	void IncreaseDateByOneMillennium() {
		*this = IncreaseDateByOneMillennium(*this);
	}
	static clsDate DecreaseDateByOneDay(clsDate Date) {
		short NumbetOfDay = NumberOfDaysInMonth(Date.Year, Date.Month);
		if (Date.Day == 1) {
			if (Date.Month == 1) {
				Date.Day = 31;
				Date.Month = 12;
				Date.Year -= 1;
			}
			else {
				Date.Day = NumbetOfDay;
				Date.Month -= 1;
			}
		}
		else {
			Date.Day--;
		}

		return Date;
	}
	void DecreaseDateByOneDay() {
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
	void DecreaseDateByXDays(short Days) {
		*this = DecreaseDateByXDays(Days, *this);
	}
	static clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByOneWeek() {
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
	void DecreaseDateByXWeeks(short Weeks) {
		*this = DecreaseDateByXWeeks(Weeks, *this);
	}
	static clsDate DecreaseDateByOneMonth(clsDate Date) {
		if (Date.Month == 1) {
			Date.Month = 12;
			Date.Year -= 1;
		}
		else {
			Date.Month--;
		}
		short NumOfDayInMonth = NumberOfDaysInMonth(Date.Year, Date.Month);
		if (Date.Day > NumOfDayInMonth) {
			Date.Day = NumOfDayInMonth;
		}
		return Date;
	}
	void DecreaseDateByOneMonth() {
		*this = DecreaseDateByOneMonth(*this);
	}
	static clsDate DecreaseDateByXMonths(clsDate Date, short Months) {
		for (int i = 1; i <= Months; i++) {
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonths(short Months) {
		*this = DecreaseDateByXMonths(*this, Months);
	}
	static clsDate DecreaseDateByOneYear(clsDate date) {
		date.Year--;
		return date;
	}
	void DecreaseDateByOneYear() {
		*this = DecreaseDateByOneYear(*this);
	}
	static clsDate DecreaseDateByXYearsFaster(clsDate date, short Years) {
		date.Year -= Years;
		return date;
	}
	void DecreaseDateByXYearsFaster(short Years) {
		*this = DecreaseDateByXYearsFaster(*this, Years);
	}
	static clsDate DecreaseDateByOneDecade(clsDate date) {
		date.Year -= 10;
		return date;
	}
	void DecreaseDateByOneDecade() {
		*this = DecreaseDateByOneDecade(*this);
	}
	static clsDate DecreaseDateByXDecades(clsDate date, short Decades) {
		date.Year -= 10 * Decades;
		return date;
	}
	void DecreaseDateByXDecades(short Decades) {
		*this = DecreaseDateByXDecades(*this, Decades);
	}
	static clsDate DecreaseDateByOneCentury(clsDate date) {
		date.Year -= 100;
		return date;
	}
	void DecreaseDateByOneCentury() {
		*this = DecreaseDateByOneCentury(*this);
	}
	static clsDate DecreaseDateByOneMillennium(clsDate date) {
		date.Year -= 1000;
		return date;
	}
	void DecreaseDateByOneMillennium() {
		*this = DecreaseDateByOneMillennium(*this);
	}
	static bool IsWeekEnd(clsDate date) {
		short Index = DayOfWeekOrder(date);
		return(Index == 5 || Index == 6);
	}
	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}
	static bool IsEndOfWeek(clsDate date) {
		return (DayOfWeekOrder(date) == 6);
	}
	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}
	static bool IsBusinessDay(clsDate date) {
		return (!IsWeekEnd(date));
	}
	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}
	static short DaysUntilEndOfWeek(clsDate date) {
		return 6 - DayOfWeekOrder(date);
	}
	short DaysUntilEndOfWeek() {
		return DaysUntilEndOfWeek(*this);
	}
	static short DaysUntilEndOfMonth(clsDate date) {
		return NumberOfDaysInMonth(date.Year, date.Month) - date.Day;

	}
	short DaysUntilEndOfMonth() {
		return DaysUntilEndOfMonth(*this);
	}
	static short DaysUntilEndOfYear(clsDate date) {
		return NumberOfDaysInYear(date.Year) - NumberOfDaysFromTheBeginingOfTheYear(date);
	}
	short DaysUntilEndOfYear() {
		return DaysUntilEndOfYear(*this);
	}
	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo) {
		clsDate date = DateFrom;
		short Sum = 0;
		while (!CheckIfDate1EqualeDate2(date, DateTo)) {
			if (!IsWeekEnd(date))Sum++;
			date = AddOneDay(date);
		}
		return Sum;
	}
	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays) {
		short WeekEndCounter = 0;

		//in case the data  is weekend keep adding one day util you reach business day
		//we get rid of all weekends before the first business day
		while (IsWeekEnd(DateFrom))
		{
			DateFrom = AddOneDay(DateFrom);
		}

		//here we increase the vacation dates to add all weekends to it.

		for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
		{

			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneDay(DateFrom);
		}

		//in case the return date is week end keep adding one day util you reach business day
		while (IsWeekEnd(DateFrom))
		{
			DateFrom = AddOneDay(DateFrom);
		}

		return DateFrom;
	}
	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {
		return (!CheckIfDate1EqualeDate2(Date1, Date2) && !(CheckIfDate1SmallerThanDate2(Date1, Date2)));
	}
	bool IsDate1AfterDate2(clsDate Date1) {
		return IsDate1AfterDate2(Date1, *this);
	}
	enum enCompareDates { After = 1, Equal = 0, Before = -1 };
	static enCompareDates CompareBetweenDate1AndDate2(clsDate Date1, clsDate Date2) {
		return(CheckIfDate1SmallerThanDate2(Date1, Date2) ? enCompareDates::Before : (CheckIfDate1EqualeDate2(Date1, Date2) ? enCompareDates::Equal : enCompareDates::After));
	}
	enCompareDates CompareBetweenDate1AndDate2(clsDate Date1) {
		return CompareBetweenDate1AndDate2(Date1, *this);
	}
	static bool IsValidDate(clsDate date) {
		short NumOfDayInMonth = NumberOfDaysInMonth(date.Year, date.Month);
		return ((date.Day <= NumOfDayInMonth && date.Day > 0) && (date.Month > 0 && date.Month < 13));
	}
	bool IsValidDate() {
		return IsValidDate(*this);
	}
	static clsDate StringToDate(string s, string delim = "/") {
		vector<string>vDates = clsString::SplitString(s, delim);
		clsDate Date;
		Date.Day = stoi(vDates[0]);
		Date.Month = stoi(vDates[1]);
		Date.Year = stoi(vDates[2]);
		return Date;
	}
	void StringToDate(string s) {
		*this = StringToDate(s, "/");
	}
	string DateToString(clsDate Date, string delim = "/") {
		string date = "";
		date += to_string(Date.Day) + delim;
		date += to_string(Date.Month) + delim;
		date += to_string(Date.Year);
		return date;
	}
	string DateToString() {
		return DateToString(*this, "/");
	}
	void Print()
	{
		cout << DateToString() << endl;
	}
	static string FormateDate(clsDate Date, string DateFormat = "dd/mm/yyyy") {
		string FormattedDateString = "";
		FormattedDateString = clsString::ReplaceWordInStringUsingBuildInFunction(DateFormat, "dd", to_string(Date.Day));
		FormattedDateString = clsString::ReplaceWordInStringUsingBuildInFunction(FormattedDateString, "mm", to_string(Date.Month));
		FormattedDateString = clsString::ReplaceWordInStringUsingBuildInFunction(FormattedDateString, "yyyy", to_string(Date.Year));
		return FormattedDateString;
	}
	string FormateDate(string DateFormat = "dd/mm/yyyy") {
		return FormateDate(*this,DateFormat);
	}
	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{

		short Days = 0;
		while (CheckIfDate1SmallerThanDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}

		return Days;

	}
	static short CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
	}
};

