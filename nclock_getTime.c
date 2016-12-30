#include <nclock.h>
#include <time.h>

MyTime nclock_getTime()
{
    MyTime t;
    
    time_t et = time(NULL);
    struct tm *tmptr = localtime(&et);
	t.day = tmptr->tm_mday;
	t.month = tmptr->tm_mon + 1; //tm_mon counts months since january
	t.year = tmptr->tm_year % 100; //want two digits, counts years since 1900
    t.sec = tmptr->tm_sec;
    t.min = tmptr->tm_min;
    t.hr  = tmptr->tm_hour;

    return t;
}
