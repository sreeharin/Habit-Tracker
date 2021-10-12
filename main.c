#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "src/tools.h"
#include "src/date.h"

void help(void);
void update(char *);
void view(void);

int
main(int argc, char **argv)
{
	int vflag = -1;
	int uflag = -1;

	int opt;

	char *user_date = (char *)malloc(11 * sizeof(user_date));
	while((opt = getopt(argc, argv, "u:v")) != -1)
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
			case '?':
				break;
			default:
				abort();
		}
	}

	if(vflag == -1 && uflag == -1)
	{
		help();
	}

	if(vflag == 0)
	{
		view();
	}
	else if(uflag == 0)
	{
		update(user_date);
	}

	return 0;
}

void
help(void)
{
	printf("usage : tracker [-v view] [-u update [t today] [[dd/mm/yyyy]]\n");
}

void
view(void)
{
	struct Date tmp;
	readData(&tmp);

	struct Date t = today(); 
	int diff = diffDate(tmp, t);
	
	printf(
	"It has been %d days since %d/%d/%d\n"
	"Keep going\n",
	diff, tmp.day, tmp.month, tmp.year
	);
}

void
update(char * date)
{
	if(strcmp(date, "t") == 0)
	{
		struct Date tmp_today = today();
		updateData(tmp_today);
		
		printf("Log has been updated\n");
	}
	else
	{
		struct Date tmp_date;
		processDate(date, &tmp_date);
		
		if(isValid(tmp_date)==0)
		{
			updateData(tmp_date);
			printf("Log has been updated\n");
		}
	}
}
