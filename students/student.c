#include "student.h"
#include <malloc.h>
#include <memory.h>
#include <stdio.h>

Student* NewStudent(int maxLenght, int markAmount)
{
    Student* student;
    student = (Student*)malloc(sizeof(Student));

    student->FirstName = (char*)malloc(sizeof(char)*maxLenght);
    student->SecondName = (char*)malloc(sizeof(char)*maxLenght);
    student->ThirdName = (char*)malloc(sizeof(char)*maxLenght);

    student->Marks = (int*)malloc(sizeof(int)*markAmount);


    return student;
}

void DepartStudent(Student* student)
{
    free(student->Marks);

    free(student->FirstName);
    free(student->SecondName);
    free(student->ThirdName);

    free(student);
}

void PrintStudent(Student* student)
{
    printf("%s ",student->FirstName);
    printf("%s ",student->SecondName);
    printf("%s ",student->ThirdName);
    printf("%d ",student->Group);
    printf("%f ",student->AverageMark);
    printf("\n");
}
