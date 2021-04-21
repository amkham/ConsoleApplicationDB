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

struct tnode {
	char* field;   
	int count; 
	struct tnode *left;  
	struct tnode *right; 
}*tN;

struct recordQueue
{
	struct record* r;
	int first, last;
} *rQ;


void PrintHead();
void PrintRecord(int num, struct record* BD);
void PrintBD(struct record** BD, int n, int* index);
void readFromFile();
int* makeIndexArray(int k);
bool cmp(myDate& a, myDate& b);
void hoarasort(struct record** a, int left, int right);


struct recordQueue* SeachPuchQ(int targetYear, struct record** a);
void initQ(struct recordQueue* q, int len);
void deleteQ();
void insertQ(struct recordQueue* q, record* r);
void printQ(struct recordQueue* q);


void treeprint(struct tnode* tree);
struct tnode* addnode(struct record *r, struct tnode* tree);
bool cmpChar(char* c1, char* c2);
void treeFind(struct tnode* tree, char target);


//////////////// MAIN///////////////////////


int main()
{
	readFromFile();
	int* main_ind_arr = makeIndexArray(N);
	hoarasort(main_mas, 0, N-1);
	PrintBD(main_mas, N, main_ind_arr);

	int y = 0;
	rQ = (recordQueue*)malloc(sizeof(recordQueue));
	while (y != -1)
	{
		cout <<endl<< "/////////////QUEUE//////////////" << endl;
		cout << "Find year (-1 for exit): ";
		cin >> y;
		if (SeachPuchQ(y, main_mas) != NULL)
		{
			printQ(rQ);			

		}
		else if (y != -1)
			cout << "Don't find..." << endl;
	}

	cout <<endl<< "/////////////TREE//////////////" << endl;
	
	for (int i = 0; i < rQ->last; i++)
	{
		tN = addnode(&rQ->r[i], tN);
	}


	treeprint(tN);

	char t = '0';
	cout << "Find for first simbol in surname: ";
	cin >> t;
	treeFind(tN, t);

	//deleteQ();

	cin;
}
/// <summary>
/// /////////////////////////////////////////////////////////////////
/// </summary>

void deleteQ()
{
	
		delete &main_mas;
	
	
		delete &rQ->r;
	
	delete &rQ;
	
}




bool cmpChar(char* c1, char* c2)
{
	int i = 0;
	while (c1[i] == c2[i])
	{
		i++;
	}
	
	return c1[i] > c2[i];

}


struct tnode* addnode(struct record* r, struct tnode* tree) {

	if (tree == NULL) 
	{
		
		tree = (struct tnode*)malloc(sizeof(struct tnode));
		tree->field = &r->FIO[0];
		tree->left = tree->right = NULL;
		
		
	}
	else 
	{
		
			if (cmpChar(tree->field, r->FIO))
				tree->left = addnode(r, tree->left);
			else
				tree->right = addnode(r, tree->right);
		
		
	}
	
	return(tree);
	
}

void treeprint(struct tnode* tree) {
	if (tree != NULL) { 
		
		cout << tree->field << endl;
		treeprint(tree->left); 
		treeprint(tree->right);
	}
}
void treeFind(struct tnode* tree, char target) {
	if (tree != NULL)  {
		treeFind(tree->left, target);
		treeFind(tree->right, target);
		if (tree->field[0]==target) cout << tree->field << endl;
	}
}

void printQ(struct recordQueue *q)
{
	for (int i = q->first; i < q->last; i++)
	{
		PrintRecord(i, &q->r[i]);
	}
}


void insertQ(struct recordQueue* q, record* r)
{
	if (q->first == q->last)
	{
		
		q->r[0] = *r;
		q->last++;
	}
	else
	{
		q->r[q->last] = *r;
		q->last++;
	}

	
}

void initQ(struct recordQueue* q, int len)
{
	
	q->r = new record[len];
	q->first = 0;
	q->last = 0;
	
}
void initT(struct tnode* tree)
{
	tree = (struct tnode*)malloc(sizeof(struct tnode));
	tree->field = new char;
	tree->left = NULL;
	tree->right = NULL;

}

struct recordQueue* SeachPuchQ(int targetYear, struct record** a)
{
	int l, r;
	int i_key = 0, j = N - 1, m;
	while (i_key < j)
	{
		m = (i_key + j) / 2;
		if (a[m]->mydate.year < targetYear) i_key = m + 1;
		else j = m;
	}
	l = i_key;
	r = j;
	while ((a[l]->mydate.year == targetYear)&&(l>0)) l--;
	while ((a[r]->mydate.year == targetYear) && (r < N)) r++;
	if (a[i_key]->mydate.year != targetYear) return NULL;
	else
	{
		initQ(rQ, r);
		for (int i = l; i < r; i++)
		{
			if (a[i]->mydate.year == targetYear)
			{
				insertQ(rQ, a[i]);
			}
				
			
			
		}
	}

	return rQ;

};


void PrintHead() {
	cout << "FIO \t\t\t\t\tDoljnost\t\tNomerOtdela\tData rojdeniya" <<
		endl << "------------------------------------------------------------------------------------------------\n";
}

void PrintRecord(int num, struct record* BD) {
	cout << num << ". " << BD->FIO << "\t" << BD->Post << "\t"
		<< BD->Number << "\t\t" << BD->Date << endl;
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


	FILE* fp;
	fopen_s(&fp, "BASE2.dat", "rb");

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
			year = year + main_mas[i]->Date[6] + main_mas[i]->Date[7];

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

bool cmp(myDate &a, myDate &b) {

	int d1 = a.year * 10000 + a.moth * 100 + a.day;
	int d2 = b.year * 10000 + b.moth * 100 + b.day;

	return d1 >= d2 ;
}

void hoarasort(struct record** a, int left, int right)
{
	int i = left;
	int j = right;


	record* tmp;

	while (i <j)
	{
		while ((cmp(a[left]->mydate, a[i]->mydate)) && (i < right)) i++;
		while ((cmp(a[j]->mydate, a[left]->mydate)) && (j > left)) j--;

		if (i < j)
		{
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			
		}
	}

	tmp = a[j];
	a[j] = a[left];
	a[left] = tmp;

	if (i < right)
		hoarasort(a, j + 1, right);
	if (left < j)
		hoarasort(a, left, j - 1);
}

