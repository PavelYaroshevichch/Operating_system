#include <stdio.h>
#include <stdlib.h>

struct employee
{
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    char* nameOfBinFile = argv[1];
    int numberOfEmployees = atoi(argv[2]);
    FILE* out;
    struct employee s;

    if (!(out = fopen(nameOfBinFile, "wb"))) {
        printf("Opening bin file failed.\n");
        return 1;
    }

    if (numberOfEmployees < 0) return 0;

    printf("Input num, name and hours.\n");
    for (int i = 0; i < numberOfEmployees; ++i) {
        printf("%d> ", i + 1);
        scanf("%d%s%lf", &s.num, &s.name, &s.hours);
        fwrite(&s, sizeof(struct employee), 1, out);
    }

    fclose(out);
    return 0;
}