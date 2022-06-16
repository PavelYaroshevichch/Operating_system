#include "stdio.h"
#include "stdlib.h"

struct employee
{
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    FILE* in;
    FILE* out;
    employee s;
    char* nameOfBinFile = argv[1];
    char* nameOfTxtFile = argv[2];
    double paymentPerHour = atof(argv[3]);

    if (!(in = fopen(nameOfBinFile, "rb")))
    {
        printf("Opening bin file failed.\n");
        return 1;
    }
    if (!(out = fopen(nameOfTxtFile,"w"))) {
        printf("Opening txt file failed.\n");
        return 1;
    }

    fprintf(out, "%s: %s\n", "Report of file", nameOfBinFile);
    fprintf(out,"%s", "Number        Name           Hours        Salary\n");
    for(int i = 0; ; i++){
        fseek(in, i*sizeof(struct employee), SEEK_SET);
        if (!fread(&s, sizeof(employee), 1, in)){
            break;
        }
        fprintf(out,"%d\t\t%s\t\t%lf\t\t%lf\n", s.num, s.name, s.hours, s.hours * paymentPerHour);
    }
    fclose(in);
    return 0;
}