#include<stdio.h>

struct student
{
	char name[20];
	int eng;
	int math;
	int phys;
	double mean;
};

void diem_trung_binh(struct student *s){
	for (int i = 0; i < 4; i++){
		s[i].mean=(float)(s[i].eng + s[i].math + s[i].phys)/3;
	}
	for (int i = 0; i < 4; i++)
	{
		printf("Ten: %s - eng: %d - math: %d - phys: %d -> avg: %f\n",s[i].name, s[i].eng, s[i].math, s[i].phys, s[i].mean);
	}
}

int main(int argc, char const *argv[])
{
	static struct student data[]=
	{
		{"Tuan", 82, 72, 58, 0.0},
    	{"Nam", 77, 82, 79, 0.0},
    	{"Khanh", 52, 62, 39, 0.0},
    	{"Phuong", 61, 82, 88, 0.0}
	};
	printf("Diem va diem TB cua cac sinh vien: \n");
	diem_trung_binh(data);
	return 0;
}