#include<windows.h>
#include<stdio.h>
char testdir[100];
DWORD WINAPI Fun1(LPVOID lpParameter)
{
    strcpy(testdir, "This is a test dir");
    MessageBox(NULL, testdir, "Ïß³Ì", 0);
    return 0;
}
main()
{
    HANDLE thread1;
    thread1 = CreateThread(NULL, 0, Fun1, NULL, 0, NULL);
    CloseHandle(thread1);
    printf("this is just a test:ok!");
    Sleep(4000);

    //	getchar();
}