#include <stdio.h>
#include <string.h>
int main() {
    char flag[100];
    scanf("%s", flag);
    int len = strlen(flag);
    char key[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; i++)
        flag[i] ^= key[i % 26];
    for (int i = 0; i < len; i++)
        printf("%d,", flag[i]);
}
