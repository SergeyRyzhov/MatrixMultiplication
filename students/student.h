#ifndef STUDENT_H
#define STUDENT_H

typedef struct 
{
    char* FirstName;
    char* SecondName;
    char* ThirdName;

    char Sex;

    char Day;
    char Month;
    short Year;
    
    int Age;

    char* City;

    short Group;

    int* Marks;

    double AverageMark;

} Student;


Student* NewStudent(int maxLenght, int markAmount);

void DepartStudent(Student* student);

void PrintStudent(Student* student);

#endif
