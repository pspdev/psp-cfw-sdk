extern int tolower(int s);
extern char *strstr(const char *str1, const char *str2);
extern char *strncpy(char *to, const char *from, unsigned int n);

char *stristr(const char *str1, const char *str2) {
    #define MAXLEN 256

    static char temp1[MAXLEN+1], temp2[MAXLEN+1];
    temp1[MAXLEN] = 0;
    temp2[MAXLEN] = 0;

    strncpy(temp1, str1, MAXLEN);
    strncpy(temp2, str2, MAXLEN);

    int i;
    for (i = 0; i < MAXLEN && (temp1[i] != 0); i++) {
        temp1[i] = tolower((int)temp1[i]);
    }

    for (i = 0; i < MAXLEN && (temp2[i] != 0); i++) {
        temp2[i] = tolower((int)temp2[i]);
    }

    const char *pos = strstr(temp1, temp2);
    if (pos) {
        return (char *)(pos - temp1 + str1);
    }

    return 0;
}
