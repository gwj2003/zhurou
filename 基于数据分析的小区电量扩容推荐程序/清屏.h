#include<stdio.h>
#include<Windows.h>
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

void MyCls(HANDLE hConsole);
inline void clrscr(void);
