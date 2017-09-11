#include<stdio.h>

typedef struct student
{
	char name[20];
	int eng;
	int math;
	int phys;
}STUDENT;


int main(int argc, char const *argv[])
{
	STUDENT data[]={
    	{"Tuan", 82, 72, 58},
    	{"Nam", 77, 82, 79},
    	{"Khanh", 52, 62, 39},
    	{"Phuong", 61, 82, 88}
	};
	STUDENT *p;
	p=data;
	for (p=data ; p < data+4 ; p++)
	{
		printf("Name: %s Eng: %d Math: %d Phys: %d\n",p->name, p->eng, p->math, p->phys);
	}
	return 0;
}