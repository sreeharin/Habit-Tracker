#include "date.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void
processDate(char str_date[], struct Date *D)
{
	int count = 0;
	char *token;
	while((token = strsep(&str_date, "/")) != NULL)
	{
		int tmp = atoi(token);
		if(count == 0)
		{
			D->day = tmp;
		}
		else if(count == 1)
		{
			D->month = tmp;
		}
		else if(count == 2)
		{
			D->year = tmp;
		}
		else
		{
			break;
		}
		count++;
	}
}

void
updateData(struct Date D, char * comment)
{
	FILE *tmp_data = fopen("/home/shn/Works/tracker/data/temp.dat", "w");
	fprintf(tmp_data, "%d/%d/%d\n", D.day, D.month, D.year);
	fclose(tmp_data);

	FILE *tmp_log = fopen("/home/shn/Works/tracker/data/log.csv", "a");
	fprintf(tmp_log, "%d/%d/%d,%s,\n", D.day, D.month, D.year, comment);
	fclose(tmp_data);
}

void
readData(struct Date *D)
{
	FILE *tmp_data = fopen("/home/shn/Works/tracker/data/temp.dat", "r");
	char date[11];
	fgets(date, 11, tmp_data);
	processDate(date, D);
	fclose(tmp_data);
}
