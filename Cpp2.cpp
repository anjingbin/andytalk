#include <stdio.h>
#include <string.h>
#include <windows.h>

int main()
{
   int   i;
   for(i=0;i<100;++i)
      {
        printf("\nThis is speaker beep number %d... \n\7", i+1);
		Sleep(500);
//	   ::MessageBeep(-1);
//	   Sleep(500);
      }
   return 0;
}
