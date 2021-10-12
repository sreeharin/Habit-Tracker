#ifndef DATE_H
#define DATE_H

struct Date 
{
	int day;
	int month;
	int year;
};

int isLeap(int);
int isValid(struct Date);
int diffDate(struct Date, struct Date);
struct Date today(void);

#endif
