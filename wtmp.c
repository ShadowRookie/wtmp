#include <stdio.h>
#include <string.h>
#include <utmp.h>
#include <stdio.h>
#include <fcntl.h>
#include <utmpx.h>
#include <syslog.h>
#include <time.h>

#define FILENAME "/var/log/wtmp"

int main()
{
	
	openlog("wtmp_program", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL0);
	syslog(LOG_INFO,"Program started by User %d", getuid());

	struct utmp log;
	FILE *f = fopen(FILENAME, "r");
	char *date=0;
	time_t t =0;

	if(f == 0)
	{
		syslog(LOG_ERR,"Error fopen");
		perror("blad");
		return 1;
	}

	while(fread(&log,sizeof(struct utmp),1,f)!=0)
	{
		t=log.ut_tv.tv_sec;
		printf("%-10s %-5d %-5s %-20s %-10d %-15s %-25s  %-10ld",
		log.ut_user, log.ut_pid, log.ut_line, log.ut_id, log.ut_type,
		log.ut_host, ctime(&t), log.ut_session);
	}
	
	//nie wyswietlam wszystkich pol, poniewaz nie mieszcza sie na ekranie 
	//interesujace nas rekordy mozemy odnalezc w man wtmp i za pomoca struktury utmp log
	//dopisac je w petli while

	closelog();
	return 0;
}
