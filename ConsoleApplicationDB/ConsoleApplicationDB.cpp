#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include <cstdio>
#include <string>

#include <fstream>

#define N 4000
//#define _CRT_SECURE_NO_WARNINGS

using namespace std;

 struct myDate {
	short int day;
	short int moth;
	short int year;
};
struct record
{
	char FIO[32];
	char Post[22];
	short int Number;
	short int Apt;
	char Date[10];
	myDate mydate;
}* main_mas[N];



void PrintHead() {
	cout << "FIO \t\t\t\t\tDoljnost\t\tNomerOtdela\tData rojdeniya" <<
		endl << "------------------------------------------------------------------------------------------------\n";
}



void PrintRecord(int num, struct record* BD) {
	cout << num << ". " << BD->FIO << "\t" << BD->Post << "\t"
		<< BD->Number << "\t\t" << BD->mydate.day << "-"<<BD->mydate.moth << "-" << BD->mydate.year  << endl;
}


void PrintBD(struct record** BD, int n, int* index) {

	
	PrintHead();
	for (int j = 0; j < n; j++) {
		
		PrintRecord(j, BD[index[j]]);

		if ((j != 0) && (j % 20 == 0))
		{
		
			cout << "Next 20 cout 1:Yes 0:No" << endl;
			int identif;
			cin >> identif;
			if (identif == 0)
			{
				break;
			}
		}
		
	}
}





void readFromFile() {


	FILE *fp;
	fopen_s(&fp,"BASE2.dat", "rb");

	if (fp == NULL)
	{
		cout << "File not open!!!";
	}
	else
	{
		int i;
		for (i = 0; i < N; i++) free(main_mas[i]);
		for (i = 0; i < N; i++)
		{
			main_mas[i] = (record*)malloc(sizeof(record));
			fgets(main_mas[i]->FIO, 32, fp);
			fgetc(fp);
			fgets(main_mas[i]->Post, 18, fp);
			fgetc(fp);
			main_mas[i]->Number = fgetc(fp);
			fgetc(fp);
			main_mas[i]->Apt = fgetc(fp);
			fgetc(fp);
			fgets(main_mas[i]->Date, 10, fp);
			fgetc(fp);


			//Конвертация массива дат в структуру для последующего сравнения 
			string day = "";
			day = day + main_mas[i]->Date[0] + main_mas[i]->Date[1];
			string moth = "";
			moth = moth + main_mas[i]->Date[3] + main_mas[i]->Date[4];
			string year = "";
			year = year+  main_mas[i]->Date[6] + main_mas[i]->Date[7];

			main_mas[i]->mydate.day = stoi(day);
			main_mas[i]->mydate.moth = stoi(moth);
			main_mas[i]->mydate.year = stoi(year);
		}
		
		fclose(fp);
		

	}

	
	
}


int* makeIndexArray(int k) {
	int* in = (int*)malloc(sizeof(int) * k);
	for (int i = 0; i < k; i++) {
		in[i] = i;
	}
	return in;
}




bool cmp(myDate& a, myDate& b) {

	if (a.year < b.year) 
	{ 
		return true; 
	}
	else
	{
		if ((a.year == b.year) && (a.moth < b.moth))
		{
			return true;
		}
		else
		{
			if ((a.year == b.year) && (a.moth == b.moth) && (a.day < b.day))
			{
				return true;
			}
			else
			{
				if ((a.year == b.year) && (a.moth == b.moth) && (a.day == b.day))
				{
					return true;
				}

				else
				{
					return false;
				}
			}
		}
	}
	
	
	


	
	return (a.year == b.year) && (a.moth == b.moth) && (a.day < b.day);
}
void hoarasort(struct record** a, int first, int last)
{
	cout << "1";
	int i = first, j = last;
	myDate tmp, x =  a[(first + last) / 2]->mydate;

	do {
	while (cmp(a[i]->mydate,x))
		i++;
	while (cmp(x, a[j]->mydate))
		j--;

	if (i <= j)
	{
	if (i < j)
	{
	a[(first + last) / 2] = a[i];
	a[i] = a[j];
	a[j] = a[(first + last) / 2];
	}
	i++;
	j--;
	}
	} while (i <= j);

	if (i < last)
	hoarasort(a, i, last);
	if (first < j)
	hoarasort(a, first, j);
}




int main()
{

	readFromFile();

	
	
	int* main_ind_arr = makeIndexArray(N);
	hoarasort(main_mas,0,N-1);
	
	//quickSort(main_mas, N, main_ind_arr);
	PrintBD(main_mas, N, main_ind_arr);
	
	/*kol = Search(main_mas, N, main_ind_arr);
	if (kol > 0) {
		struct tVertex* array = new struct tVertex[kol];
		PrintQuene();
		system("cls");
		fillArray(array, kol);
		int* tree_ind_arr = makeIndexArray(kol);
		quickSortW(array, 1, kol, tree_ind_arr);
		makeDOP1(array, kol, tree_ind_arr);
		cout << "Stroim derevo" << endl << endl;
		PrintHead();
		leftToRight(Root);
		searchInTree(Root);
	}*/
	system("pause");
}