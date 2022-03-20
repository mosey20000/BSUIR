#include <stdlib.h>
#include <stdio.h>

#define MAXLEN 256

FILE *fl;

struct myData {
    char strings[MAXLEN];
};

char filename1[] = "test1.txt";
char filename2[] = "test2.txt";

int strCounter() {
    int count = 0;

    while (!feof(fl)) {
        if ((fgetc(fl)) == '\n') {
            count++;
        }
    }

    return count + 1;
}

int main() {

    if ((fl = fopen(filename2, "r+t")) == NULL) {
        printf("Ошибка при открытии файла.");
        exit(-1);
    }

    int stringCount = strCounter();
    printf("strings : %d", stringCount);

    struct myData *ptr = (struct myData*) malloc (stringCount * sizeof(struct myData));

    rewind(fl);
    for (int i = 0; i < stringCount; i++) {
        fscanf(fl, "%s", ptr[i].strings);
    }

    printf("\n");
    for (int i = 0; i < stringCount; i++) {
        printf("Str #%d: %s\n", i+1, ptr[i].strings);
    }


    bool uniqueWord = true;
    for (int checkingWord = 0; checkingWord < stringCount - 1; checkingWord++) {
        for (int comparableWord = checkingWord + 1; comparableWord < stringCount; comparableWord++) {
            for (int checkingChar = 0; ptr[checkingWord].strings[checkingChar] != '\0'; checkingChar++) {
                for (int comparableChar = 0; ptr[comparableWord].strings[comparableChar] != '\0' ; comparableChar++) {
                    if (ptr[checkingWord].strings[checkingChar] == ptr[comparableWord].strings[comparableChar]) {
                        uniqueWord = false;
                    }
                }
            }
        }

        if (uniqueWord == true) {
            printf("Strings: %s | Unique", ptr[checkingWord].strings);
        }

        if (uniqueWord == false) {
            uniqueWord = true;
        }
    }


    fclose(fl);

    return 0;
}
