#pragma once
#include "clsDate.h"
#include <iostream>
using namespace std;
class clsPeriod
{
public:
	clsDate StartDate;
	clsDate EndDate;
	clsPeriod(clsDate StartDate, clsDate EndDate) {
		this->StartDate = StartDate;
		this->EndDate = EndDate;
	}
	static bool OverlapsDates(clsPeriod Period1, clsPeriod Period2) {
		if (clsDate::CompareBetweenDate1AndDate2(Period2.EndDate, Period2.StartDate) == clsDate::enCompareDates::Before || clsDate::CompareBetweenDate1AndDate2(Period2.StartDate, Period1.EndDate) == clsDate::enCompareDates::After)
			return 1;
		else 0;
	}
	bool OverlapsDates(clsPeriod Period2) {
		return OverlapsDates(*this, Period2);
	}
	static int PeriodLengthInDay(clsPeriod Period, bool IncludeEndDay = 0) {
		return clsDate::GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDay);

	}
	int PeriodLengthInDay(bool IncludeEndDay = 0) {
		return PeriodLengthInDay(*this, IncludeEndDay);
	}
	static bool IsDateInPeriod(clsPeriod Period, clsDate Date) {
		return (clsDate::CompareBetweenDate1AndDate2(Period.StartDate, Date) == clsDate::enCompareDates::Before && clsDate::CompareBetweenDate1AndDate2(Period.EndDate, Date) == clsDate::enCompareDates::After);
	}
	bool IsDateInPeriod(clsDate Date) {
		return IsDateInPeriod(*this, Date);
	}
	static int CountOverlapDays(clsPeriod Period1, clsPeriod Period2) {
		int LengthPeriod1 = PeriodLengthInDay(Period1, 1);
		int LengthPeriod2 = PeriodLengthInDay(Period2, 1);
		int CountOverlap = 0;
		if (!OverlapsDates(Period1, Period2)) {
			return 0;
		}
		if (LengthPeriod1 < LengthPeriod2) {
			while (clsDate::IsDate1AfterDate2(Period1.EndDate, Period1.StartDate)) {
				if (IsDateInPeriod(Period2, Period1.StartDate)) {
					CountOverlap++;
				}
				Period1.StartDate = clsDate::AddOneDay(Period1.StartDate);
			}
		}
		else {
			while (clsDate::IsDate1AfterDate2(Period2.EndDate, Period2.StartDate)) {
				if (IsDateInPeriod(Period1, Period2.StartDate)) {
					CountOverlap++;
				}
				Period2.StartDate = clsDate::AddOneDay(Period2.StartDate);
			}
		}
		return CountOverlap;
	}
	int CountOverlapDays(clsPeriod Period2) {
		return CountOverlapDays(*this, Period2);
	}
};

