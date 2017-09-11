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
}

char hangsv(double point){
	if ((90<=point)&&(point<=100)) return 'S';
	else if ((80<=point)&&(point<90)) return 'A';
	else if ((70<=point)&&(point<80)) return 'B';
	else if ((60<=point)&&(point<70)) return 'C';
	else if (point<60) return 'D';
	else 
		printf("Diem dua vao khong hop le\n");
	return '-';
}
void show_hang_sinh_vien (struct student *s){
	for (int i = 0; i < 4; i++)
	{
		char h=hangsv(s[i].mean);
		printf("Ten: %s - diem TB: %f - Hang SV: %c \n", s[i].name, s[i].mean, h);
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
	diem_trung_binh(data);
	printf("Diem TB va Hang cua cac sinh vien: \n");
	show_hang_sinh_vien(data);
	return 0;
}