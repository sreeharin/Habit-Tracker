#include "date.h"
#include <time.h>

int
isLeap(int year)
{
	return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0)) ? 0 : -1;		
}

int
isValid(struct Date D)
{
	return (D.month <= 12) ? (D.day <= 31) ? 0 : -1 : -1;
}

/*
*
*
* Function to calculate the difference between two dates
*	
* @param struct Date d1 -> first date
* @param struct Date d2 -> second date
*
*/

int 
diffDate(struct Date d1, struct Date d2)
{
	int year_arr[12] = {31, 28, 31,
			    30, 31, 30,
			    31, 31, 30,
			    31, 30, 31};
	
	if(d1.year == d2.year)
	{
		if(d1.month == d2.month)
		{
			return d2.day-d1.day;
		}
		else
		{
			int rem = year_arr[d1.month-1]-d1.day;
			for(int month = d1.month; month < d2.month-1; month++)
			{
				rem += year_arr[month];
			}
			rem += d2.day;

			return rem;
		}
	}
	else
	{
		int year = 0;
		for(int tmp_year = d1.year+1; tmp_year < d2.year; tmp_year++)
		{
			year += (isLeap(tmp_year)==0) ? 366 : 365;
		}
		
		int rem1 = year_arr[d1.month-1]-d1.day;
		for(int month1 = d1.month; month1 < 12; month1++)
		{
			rem1 += (isLeap(d1.year) && month1==1) ? 29 : year_arr[month1];
		}

		int rem2 = 0;
		for(int month2 = 0; month2 < d2.month-1; month2++)
		{
			rem2 += (isLeap(d2.year) && month2==1) ? 29 : year_arr[month2];
		}
		rem2 += d2.day;

		return year + rem1 + rem2;
	}
	return 0;
}

struct Date
today(void)
{
	time_t curtime = time(NULL);
	struct tm *btime = localtime(&curtime);

	struct Date tmp = {btime->tm_mday,
				btime->tm_mon+1,
				btime->tm_year+1900};
	return tmp;
}
