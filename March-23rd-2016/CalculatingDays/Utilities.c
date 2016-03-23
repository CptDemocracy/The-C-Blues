#include <errno.h>
#include <time.h>
#include <math.h>
#include "Utilities.h"

static int CalculateDaysBetweenFFunc(int year, int month) {
	return (month <= 2) ? year - 1 : year;
}

static int CalculateDaysBetweenGFunc(int month) {
	return (month <= 2) ? month + 13 : month + 1;
}

int CalculateDaysBetween(const struct tm* date1, const struct tm* date2) {
	// Given function is only applicable for dates after March 1, 1900
	// -1 is returned and errno is set to EINVAL if an earlier date is 
	// supplied.
	const int YEAR_LOWER_BOUND = 1900;
	const int MONTH_LOWER_BOUND = MAR;
	const int RETURN_VAL_ON_ERROR = -1;

	// we calculate by the following formula:
	//
	//		N2 - N1 = Days, where
	// N = 1461 * f(year, month) / 4 + 153 * g(month) / 5 + day, where
	//
	//		f(year, month) => (month <= 2) ? year - 1 : year
	//		g(month) => (month <= 2) ? month + 13 : month + 1

	if (!date1) {
		errno = EINVAL;
		return RETURN_VAL_ON_ERROR;
	}

	if (!date2) {
		errno = EINVAL;
		return RETURN_VAL_ON_ERROR;
	}

	if (date1->tm_year < YEAR_LOWER_BOUND || 
			(date1->tm_year == YEAR_LOWER_BOUND && date1->tm_mon < MONTH_LOWER_BOUND)) 
	{
		errno = EINVAL;
		return RETURN_VAL_ON_ERROR;
	}

	if (date2->tm_year < YEAR_LOWER_BOUND ||
			(date2->tm_year == YEAR_LOWER_BOUND && date2->tm_mon < MONTH_LOWER_BOUND))
	{
		errno = EINVAL;
		return RETURN_VAL_ON_ERROR;
	}

	int f1 = CalculateDaysBetweenFFunc(date1->tm_year, date1->tm_mon);
	int g1 = CalculateDaysBetweenGFunc(date1->tm_mon);
	int N1 = 1461 * f1 / 4 + 153 * g1 / 5 + date1->tm_mday;

	int f2 = CalculateDaysBetweenFFunc(date2->tm_year, date2->tm_mon);
	int g2 = CalculateDaysBetweenGFunc(date2->tm_mon);
	int N2 = 1461 * f2 / 4 + 153 * g2 / 5 + date2->tm_mday;

	return (int)labs(N2 - N1);
}
