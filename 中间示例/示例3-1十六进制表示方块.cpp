#include<graphics.h>
#include<stdio.h>


void change(WORD name)
{
    int i;
    WORD b, c;

    b = name;
    c = 0x8000;

    // printf("%d ", ((b & c)) > 0);
    for(i = 0; i < 16; i++)
    {
        if(i % 4 == 0)printf("\n");
        printf("(%d %d)%d ", i % 4, i / 4, ((b & c)) > 0);

        b <<= 1;
    }

}

int main()
{
    WORD name;

    name = 0x44c0;//������ı䷽���ʮ��������

    printf("0x%x��ת�������", name);
    change(name);
    printf("\n");

    return 0;
}
