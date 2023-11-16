#include <stdio.h>

int main(void)
{
    char str;
    int index = 32, hex_index = 0x20;
    str = (char)index;
    printf("이름:서형종\nASCII TABLE\n");
    printf("==========================================================\n");
    printf("|  DEC  HEX  CHAR  |  DEC  HEX  CHAR  |  DEC  HEX  CHAR  |\n");
    printf("==========================================================\n");

    for (int i = 0; i <= 20; i++)
    {
        printf("%5d %5x %5c  |  %3d %5x %5c  | %3d %5x %5c |\n",
            index, hex_index, index,
            index + 32, hex_index + 32, index + 32,
            index + 64, hex_index + 64, index + 64);
        index += 1;
        hex_index += 1;

    }
    return 0;
}