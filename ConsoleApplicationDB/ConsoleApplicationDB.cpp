#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

#include <fstream>

#define N 4000
//#define _CRT_SECURE_NO_WARNINGS

using namespace std;

struct record
{
	char FIO[32];
	char Post[22];
	short int Number;
	short int Apt;
	char Date[10];
} *main_mas[N];

struct Quene {
	struct record* data;
	struct Quene* next;
} searchQuene;

struct Quene* Head;
struct Quene* Tail;

struct tVertex {
	struct record* data_q;
	int w;
	struct tVertex* left;
	struct tVertex* right;
};

struct tVertex* Root;

int w = 0;

bool a = 1;

short int CompareStr(char str1[], char str2[], int k) { // 0 - равны, 1 - str1 > str2, 2 - str1 < str2
	for (int i = 0; i < k; i++) {
		if (str1[i] > str2[i]) {
			return 1;
		}
		else if (str1[i] < str2[i]) {
			return 2;
		}
	}
	return 0;
}

short int mainCompare(char str1[], char str2[], int k, int bld1, int bld2) {
	if (CompareStr(str1, str2, k) == 0) {
		if (bld1 > bld2) {
			return 1;
		}
		else if (bld1 < bld2) {
			return 2;
		}
		else {
			return 0;
		}
	}
	else {
		return CompareStr(str1, str2, k);
	}
}

void PrintHead() {
	cout << "FIO \t\t\t\t\tDoljnost\t\tNomerOtdela\tData rojdeniya" <<
		endl << "------------------------------------------------------------------------------------------------\n";
}



void PrintRecord(int num, struct record* BD) {
	cout << num << ". " << BD->FIO << "\t" << BD->Post << "\t"
		<< BD->Number << "\t" << BD->Apt << "\t" << BD->Date << endl;
}


void PrintBD(struct record** BD, int n, int* index) {

	int kol = 0;
	int ans;
	PrintHead();
	for (int j = 0; j < n; j++) {
		kol++;
		PrintRecord(j + 1, BD[index[j]]);
		/*if ((kol == 20) && (j != n-1)) {
			cout << "Prodoljity vivod (1/0)? ";
			cin >> ans;
			if (ans == 0) break;
			else {
				kol = 0;
				system("cls");
			}
		}*/
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


void quickSort_main(struct record** a, int L, int R, int* ind) {
	int i, j, buf, bld;
	char st[18];
	for (int g = 0; g < 18; g++) {
		st[g] = a[ind[L - 1]]->Post[g];
	}
	bld = a[ind[L - 1]]->Number;
	i = L;
	j = R;
	while (i <= j) {
		while (mainCompare(a[ind[i - 1]]->Post, st, 18, a[ind[i - 1]]->Number, bld) == 2) {
			i++;
		}
		while (mainCompare(a[ind[j - 1]]->Post, st, 18, a[ind[j - 1]]->Number, bld) == 1) {
			j--;
		}
		if (i <= j) {
			buf = ind[i - 1];
			ind[i - 1] = ind[j - 1];
			ind[j - 1] = buf;
			i++;
			j--;
		}
	}
	if (L < j) {
		quickSort_main(a, L, j, ind);
	}
	if (i < R) {
		quickSort_main(a, i, R, ind);
	}
}


void quickSort(struct record** ar, int kol, int* ind) {
	int L = 1;
	int R = kol;
	quickSort_main(ar, L, R, ind);
}


void addInQuene(struct record* newitem) {
	struct Quene* newQ;
	newQ = (struct Quene*)malloc(sizeof(Quene));
	newQ->data = newitem;
	newQ->next = NULL;
	if (Head) {
		Tail->next = newQ;
	}
	else {
		Head = newQ;
	}
	Tail = newQ;
}


int Search_m(struct record** A, int kol, int* ind, char ch[]) {
	Head = (struct Quene*)malloc(sizeof(Quene));
	Head = NULL;
	Tail = (struct Quene*)&Head;
	int num = 0;
	int L = 1;
	int R = kol;
	int m;
	while (L < R) {
		m = (L + R) / 2;
		if (CompareStr(A[ind[m - 1]]->Post, ch, 3) == 2) {
			L = m + 1;
		}
		else {
			R = m;
		}
	}
	if (CompareStr(A[ind[R - 1]]->Post, ch, 3) == 0) {
		L = R - 1;
		num++;
		addInQuene(A[ind[L]]);
		L++;
		if (L < 4000) {
			while ((CompareStr(A[ind[L]]->Post, ch, 3) == 0)) {
				num++;
				addInQuene(A[ind[L]]);
				L++;
				if (L == 4000) break;
			}
		}
	}
	system("cls");
	cout << "Naydeno zapisey: " << num << endl;
	return num;
}


int Search(struct record** A, int kol, int* ind) {
	char c[4];
	c[3] = '\0';
	cout << endl << "Vvedite god rojdenia: ";
	cin >> c;
	return Search_m(A, kol, ind, c);
}


void PrintQuene() {
	struct Quene* buf;
	buf = Head;
	int k = 0;
	int ans, kol = 0;
	cout << endl;
	PrintHead();
	while (buf) {
		k++; kol++;
		PrintRecord(k, buf->data);
		buf = buf->next;
		if (kol == 20) {
			cout << "Prodoljity vivod (1/0)? ";
			cin >> ans;
			if (ans == 0) break;
			else {
				kol = 0;
			}
		}
	}
}


void fillArray(struct tVertex* A, int n) {
	struct Quene* buf;
	buf = Head;
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		A[i].data_q = buf->data;
		A[i].w = 1 + rand() % 50;
		buf = buf->next;
	}
}

void quickSortW(struct tVertex* a, int L, int R, int* b) {
	int x, i, j, buf;
	x = a[b[L - 1]].w;
	i = L;
	j = R;
	while (i <= j) {
		while (a[b[i - 1]].w > x) {
			i++;
		}

		while (a[b[j - 1]].w < x) {
			j--;
		}
		if (i <= j) {
			buf = b[i - 1];
			b[i - 1] = b[j - 1];
			b[j - 1] = buf;
			i++;
			j--;
		}

	}
	if (L < j) {
		quickSortW(a, L, j, b);
	}
	if (i < R) {
		quickSortW(a, i, R, b);
	}
}


void addSDP(struct tVertex D) {

	struct tVertex** p = &Root;
	while (*p != NULL) {
		if (mainCompare(D.data_q->FIO, (*p)->data_q->FIO, 32, D.data_q->Apt, (*p)->data_q->Apt) == 2) p = &(*p)->left;
		else if (mainCompare(D.data_q->FIO, (*p)->data_q->FIO, 32, D.data_q->Apt, (*p)->data_q->Apt) == 1) p = &(*p)->right;
		else {
			break;
		}
	}
	if (*p == NULL) {
		*p = (struct tVertex*)malloc(sizeof(tVertex));
		(*p)->data_q = D.data_q;
		(*p)->right = NULL;
		(*p)->left = NULL;
		(*p)->w = D.w;
	}
}

void makeDOP1(struct tVertex* A, int n, int* ind) {
	Root = (struct tVertex*)malloc(sizeof(tVertex));
	Root->data_q = A[ind[0]].data_q;
	Root->left = NULL;
	Root->right = NULL;
	Root->w = A[ind[0]].w;
	for (int i = 1; i < n; i++) {
		addSDP(A[ind[i]]);
	}
}

void leftToRight(struct tVertex* p) {
	static int k = 0;
	if (a == 1) {
		if (p != NULL) {
			leftToRight(p->left);
			k++;
			if (w == 20 && a == 1) {
				cout << "Prodoljity vivod (1/0)? ";
				cin >> a;
				if (a == 0)
					return;
				else {
					w = 1;
					PrintRecord(k, p->data_q);
					leftToRight(p->right);
				}
			}
			else if (a == 1) {
				w++;
				PrintRecord(k, p->data_q);
				leftToRight(p->right);

			}
		}
	}
}


void leftToRightf(struct tVertex* p, char st[]) {
	static int z = 0;
	if (p != NULL) {
		leftToRightf(p->left, st);
		if (CompareStr(p->data_q->FIO, st, 4) == 0) {
			z++;
			PrintRecord(z, p->data_q);
		}
		leftToRightf(p->right, st);

	}
}


void searchInTree(struct tVertex* p) {
	cout << endl << "Vvedite pervie 4 bukvi familii: ";
	char f[5];
	f[4] = '\0';
	cin >> f;
	while (p != NULL) {
		if (CompareStr(p->data_q->FIO, f, 4) == 2) {
			p = p->right;
		}
		else if (CompareStr(p->data_q->FIO, f, 4) == 1) {
			p = p->left;
		}
		else {
			break;
		}
	}
	if (p != NULL) {
		system("cls");
		cout << "Rezultaty poiska: " << endl << endl;
		PrintHead();
		leftToRightf(Root, f);
	}
	else {
		cout << "Takih zapisey ne obnaruzheno!" << endl;
	}
}


int main()
{
	int kol = 0;
	readFromFile();
	int* main_ind_arr = makeIndexArray(N);
	quickSort(main_mas, N, main_ind_arr);
	PrintBD(main_mas, N, main_ind_arr);
	kol = Search(main_mas, N, main_ind_arr);
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
	}
	system("pause");
}