#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "date.h"

void help(void);
void update(char *, char *);
void view(void);

int
main(int argc, char **argv)
{
	int vflag = -1;
	int uflag = -1;
	int cflag = -1;
	int opt;

	char *user_date = (char *)malloc(11 * sizeof(char));
	char *comment = (char *)malloc(1024 * sizeof(char));

	while((opt = getopt(argc, argv, "u:vc:")) != -1)
	{
		switch(opt)
		{
			case 'u':
				memcpy(user_date, optarg, strlen(optarg));
				uflag = 0;
				break;
			case 'v':
				vflag = 0;
				break;
			case 'c':
				cflag = 0;
				memcpy(comment, optarg, strlen(optarg));
				break;
			case '?':
				break;
			default:
				abort();
		}
	}

	if(vflag == -1 && uflag == -1 && cflag == -1)
	{
		help();
	}
	else if(vflag == 0)
	{
		view();
	}
	else if(uflag == 0 && cflag == 0)
	{
		update(user_date, comment);
	}
	else
	{
		help();
	}

	return 0;
}

void
help(void)
{
	printf("usage : tracker [-v view]\n" 
		   "\t\t[-u update [t today] [dd/mm/yyyy] " 
		   "[-c \"comment\"]]\n");
}

void
view(void)
{
	struct Date tmp;
	readData(&tmp);

	struct Date t = today(); 
	int diff = diffDate(tmp, t);
	
	printf(
	"\nIt has been %d days since %d/%d/%d\n"
	"Keep going\n\n",
	diff, tmp.day, tmp.month, tmp.year
	);
}

void
update(char * date, char * comment)
{
	if(strcmp(date, "t") == 0)
	{
		struct Date tmp_today = today();
		updateData(tmp_today, comment);
		
		printf("Log has been updated\n");
	}
	else
	{
		struct Date tmp_date;
		processDate(date, &tmp_date);
		
		if(isValid(tmp_date)==0)
		{
			updateData(tmp_date, comment);
			printf("Log has been updated\n");
		}
	}
}
