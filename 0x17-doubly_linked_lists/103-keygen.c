#include <stdio.h>
#include <string.h>

void generate_key(char *username) {
    int len = strlen(username);
    int i;
    char key[7];

    for (i = 0; i < len; i++)
        key[i] = username[i] ^ len;
    
    for (; i < 7; i++)
        key[i] = '\0';

    printf("%s\n", key);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s username\n", argv[0]);
        return 1;
    }

    generate_key(argv[1]);
    return 0;
}
