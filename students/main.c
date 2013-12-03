#include <stdio.h>
#include "student.h"
#include <malloc.h>

int main(int argc, char **argv)
{
    FILE* file;
    char** lines;
    int a;
    int b;
    int i;
    int index = 0;
    const int amountLines = 5;//142400;
    const int length = 180;
    Student** students;

    lines = (char**)malloc(sizeof(char*)*amountLines);

    students = (Student**)malloc(sizeof(Student*)*amountLines);

    for (i = 0; i < amountLines; i++)
    {
        lines[i] = (char*)malloc(sizeof(char)*length);
    }

    if(argc > 1)
    {
        file = fopen(argv[1],"r");
    }
    else
    {
        return 1;
    }
    while (!feof(file) && index < amountLines)
    {        
        fgets(lines[index++],length,file);
    }

    for (i = 0; i < amountLines; i++)
    {
        students[i] = NewStudent(15,50);
        PrintStudent(students[i]);
    }

    for (i = 0; i < amountLines; i++)
    {
        free(lines[i]);
    }
    for (i = 0; i < amountLines; i++)
    {
        DepartStudent( students[i] );
    }
    free(students);
    free(lines);
    fclose(file);
    return 0;
}