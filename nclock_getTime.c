#include <nclock.h>
#include <time.h>

MyTime nclock_getTime()
{
    MyTime t;
    

    time_t et = time(NULL);
    struct tm *tmptr = localtime(&et);
    t.sec = tmptr->tm_sec;
    t.min = tmptr->tm_min;
    t.hr  = tmptr->tm_hour;

    return t;
}
