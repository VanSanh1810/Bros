#include<iostream>
#include <string>
#include<stdlib.h>
#include <fstream>
#include <string.h>
#include<vector>
using namespace std;
struct MP {
	string MMHP;
	int Diem = 0;
	MP* pNext = 0;
};

struct sinhvien {
	string MSHV, HTHV, MMH1, MMH2;
	int DM1 = 0, DM2 = 0;
};

struct Node
{
	sinhvien data;
	Node* link = 0;
	MP* pMHP = 0;
};

struct List
{
	Node* pHead = 0;
	Node* pTail = 0;
};



void KhoiTaoList(List& l) {
	l.pHead = l.pTail = NULL;
}

void inThongtin(sinhvien& sv);
void themSV(List& l, Node* p);
void Show(List l);
void showNode(Node* k);
void xoaSV(List& l);
void ChucNang(List& l);
void sortedInsert(struct Node** head_ref, struct Node* new_node);
void insertionSort(struct Node** head_ref);
void sortedInsertM2(struct Node** head_ref, struct Node* new_node);
void insertionSortM2(struct Node** head_ref);
Node* KhoiTaoNode();

void DocFile(List& l);
void GhiFile(List l);
void ThemMonPhu(List& l);
void ThemMP(MP*& mp);
void DiemMonPhu(List& l);
void ThemDMP(string x, MP*& mp);
void FreeVungNho(Node*& a);


int main() {
	List l;
	KhoiTaoList(l);
	ChucNang(l);
	return 0;
}
// Nhap thong tin cua sinh vien 
void inThongtin(sinhvien& sv)
{

	cout << "Nhap ma so sinh vien : \n";
	getline(cin, sv.MSHV);
	cout << "Nhap ten sinh vien: \n";
	getline(cin, sv.HTHV);
	cout << "Nhap ma mon hoc 1 :\n";
	getline(cin, sv.MMH1);
	cout << "Nhap ma mon hoc 2:\n";
	getline(cin, sv.MMH2);
	cout << "Nhap diem mon 1:\n ";
	cin >> sv.DM1;
	cout << "Nhap diem mon 2: \n ";
	cin >> sv.DM2;
}

void DiemMonPhu(List& l) {
	while (true) {
		string mshv;
		cout << "Nhap ma sv can them diem mon phu(Nhap -1 de ket thuc): ";
		cin >> mshv;
		int t = atoi(mshv.c_str());
		if (t == -1) {
			break;
		}
		for (Node* k = l.pHead; k; k = k->link) {
			if (k->data.MSHV == mshv) {
				string temp;
				cout << "Nhap ma mon phu can them diem: ";
				cin >> temp;
				ThemDMP(temp, k->pMHP);
				goto END;
			}
		}
		cout << "Khong tim thay HV nay" << endl;
	END:
		cout << endl;
	}
}

void ThemDMP(string x, MP*& mp) {
	if (!mp) {
		cout << "Chua DK mon nay" << endl;
	}
	else {
		if (mp->MMHP == x) {
			cout << "Nhap diem cho mon " << x << " :";
			int temp;
			cin >> temp;
			mp->Diem = temp;
		}
		else {
			ThemDMP(x, mp->pNext);
		}
	}
}

void ThemMonPhu(List& l) {
	while (true) {
		string mshv;
		cout << "Nhap ma sv can them mon phu(Nhap -1 de ket thuc): ";
		cin >> mshv;
		int t = atoi(mshv.c_str());
		if (t == -1) {
			break;
		}
		for (Node* k = l.pHead; k; k = k->link) {
			if (k->data.MSHV == mshv) {
				ThemMP(k->pMHP);
				goto END;
			}
		}
		cout << "Khong tim thay HV nay" << endl;
	END:
		cout << endl;
	}
}

void ThemMP(MP*& mp) {
	if (!mp) {
		mp = new MP;
		string temp;
		cout << "Nhap ten mon phu: ";
		cin >> temp;
		mp->MMHP = temp;
	}
	else {
		ThemMP(mp->pNext);
	}
}

void DocFile(List& l) {
	fstream fi;
	fi.open("Test.txt");
	Node* p = 0;
	Node* pre = 0;
	while (!fi.eof()) {
		if (!p) {
			p = new Node;
			if (!l.pHead) {
				l.pHead = p;
			}
			else {
				pre = l.pTail;
				pre->link = p;
			}
			fi >> p->data.MSHV;
			fi >> p->data.HTHV;
			fi >> p->data.MMH1;
			fi >> p->data.MMH2;
			string a;
			string b;
			fi >> a;
			fi >> b;
			p->data.DM1 = atoi(a.c_str());
			p->data.DM2 = atoi(b.c_str());
		}
		l.pTail = p;
		pre = p;
		p = p->link;
	}
	fi.close();
}


void GhiFile(List l) {
	fstream fi;
	fi.open("Out.txt", ios::out);
	for (Node* k = l.pHead; k; k = k->link) {
		fi << k->data.MSHV << " ";
		fi << k->data.HTHV << " ";
		fi << k->data.MMH1 << " ";
		fi << k->data.MMH2 << " ";
		fi << k->data.DM1 << " ";
		fi << k->data.DM2 << " ";
		if (k->pMHP) {
			for (MP* z = k->pMHP; z; z = z->pNext) {
				fi << z->MMHP << " ";
				fi << z->Diem << " ";
			}
		}
		fi << "\n";
	}
	fi.close();
}


// khoi tao cac node thanh vien de nhap thong tin
Node* KhoiTaoNode()
{
	sinhvien sv;
	inThongtin(sv);
	Node* p = new Node;
	if (p == NULL) {
		cout << "Day bo nho\n";
		return 0;
	}
	p->data = sv;
	p->link = NULL;
	return p;
}

// tao danh sach sinh vien 
void themSV(List& l, Node* p)
{
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		p->link = l.pHead;
		l.pHead = p;
	}
}

// in ra thong tin sinh vien tiep theo
void Show(List l)
{
	cout << "==============================================\n";
	for (Node* k = l.pHead; k != NULL; k = k->link)
	{
		cout << "MSSV : " << k->data.MSHV << endl;
		cout << "Ten  : " << k->data.HTHV << endl;
		cout << "Ma mon hoc 1  : " << k->data.MMH1 << endl;
		cout << "Ma mon hoc 2 : " << k->data.MMH2 << endl;
		cout << "Diem mon 1 : " << k->data.DM1 << " diem" << endl;
		cout << "Diem mon 2 : " << k->data.DM2 << " diem" << endl;
		if (k->pMHP) {
			for (MP* z = k->pMHP; z; z = z->pNext) {
				cout << "Diem mon phu ma so " << z->MMHP << " :" << z->Diem << endl;
			}
		}
		cout << "==============================================\n";
	}
}

// in ra thong tin sinh vien 
void showNode(Node* k)
{
	cout << "==============================================\n";
	cout << "MSSV : " << k->data.MSHV << endl;
	cout << "Ten  : " << k->data.HTHV << endl;
	cout << "Ma mon hoc 1  : " << k->data.MMH1 << endl;
	cout << "Ma mon hoc 2 : " << k->data.MMH2 << endl;
	cout << "Diem mon 1 : " << k->data.DM1 << " diem" << endl;
	cout << "Diem mon 2 : " << k->data.DM2 << " diem" << endl;
	if (k->pMHP) {
		for (MP* z = k->pMHP; z; z = z->pNext) {
			cout << "Diem mon phu ma so " << z->MMHP << " :" << z->Diem << endl;
		}
	}
	cout << "==============================================\n";
}
// xoa sinh vien ra khoi danh sach
void xoaSV(List& l)
{
	string del;
	cout << "Nhap ma so hoc vien can xoa : \n";
	//getline(cin, del);
	cin >> del;
	Node* temp = 0;
	Node* pre = 0;
	int count = 0;
	for (Node* k = l.pHead; k; k = k->link) {
		if (del == k->data.MSHV) {
			if (count == 0) {
				l.pHead = k->link;
			}
			else {
				pre->link = k->link;
			}
			temp = k;
			FreeVungNho(temp);
			break;
		}
		if (count == 0) {
			pre = l.pHead;
		}
		else {
			pre = pre->link;
		}
		count++;
	}
}

void FreeVungNho(Node*& a) {
	vector<MP*> monphu;
	if (a->pMHP) {
		for (MP* k = a->pMHP; k; k = k->pNext) {
			monphu.push_back(k);
		}
		while (!monphu.empty()) {
			delete monphu.back();
			monphu.pop_back();
		}
		a->pMHP = NULL;
	}
	delete a;
	a = NULL;
}
//sap xep tang dan theo diem so 1
void insertionSort(struct Node** head_ref)
{
	struct Node* sorted = NULL;
	struct Node* current = *head_ref;
	while (current != NULL)
	{
		struct Node* next = current->link;
		sortedInsert(&sorted, current);
		current = next;
	}
	*head_ref = sorted;
}
void sortedInsert(struct Node** head_ref, struct Node* new_node)
{
	struct Node* current;
	if (*head_ref == NULL || (*head_ref)->data.DM1 < new_node->data.DM1)
	{
		new_node->link = *head_ref;
		*head_ref = new_node;
	}
	else
	{
		current = *head_ref;
		while (current->link != NULL &&
			current->link->data.DM1 > new_node->data.DM1)
		{
			current = current->link;
		}
		new_node->link = current->link;
		current->link = new_node;
	}
}
//sap xep theo m2
void insertionSortM2(struct Node** head_ref)
{
	struct Node* sorted = NULL;
	struct Node* current = *head_ref;
	while (current != NULL)
	{
		struct Node* next = current->link;
		sortedInsertM2(&sorted, current);
		current = next;
	}
	*head_ref = sorted;
}
void sortedInsertM2(struct Node** head_ref, struct Node* new_node)
{
	struct Node* current;
	if (*head_ref == NULL || (*head_ref)->data.DM1 < new_node->data.DM1)
	{
		new_node->link = *head_ref;
		*head_ref = new_node;
	}
	else
	{
		current = *head_ref;
		while (current->link != NULL &&
			current->link->data.DM1 > new_node->data.DM1)
		{
			current = current->link;
		}
		new_node->link = current->link;
		current->link = new_node;
	}
}
// in thong tin sinh vien khi biet ma mon hoc

void ChucNang(List& l)
{
	int n;
	cout << "=================Menu===================\n";
	cout << "|1. Nhap 1 sinh vien moi.               " << endl;
	cout << "|2. In danh sach sinh vien. 	         " << endl;
	cout << "|3. Sap xep danh sach sinh vien theo D1." << endl;
	cout << "|4. Sap xep danh sach sinh vien theo D2." << endl;
	cout << "|5. Xoa sinh vien khoi danh sach   	 " << endl;
	cout << "|6. Doc File         			  		 " << endl;
	cout << "|7. Them mon hoc phu  			  		 " << endl;
	cout << "|8. Them diem mon hoc phu       		 " << endl;
	cout << "|9. Ghi File         			  		 " << endl;
	cout << "|0. Thoat chuong trinh. 	         	 " << endl;
	cout << "======================================\n";
	while (1) {
		cout << "Nhap chuc nang : ";
		cin >> n;
		cin.ignore();
		if (n == 1) {
			cout << "1. Nhap thong tin sinh vien. \n";
			Node* p = KhoiTaoNode();
			themSV(l, p);
		}
		if (n == 2) {
			cout << "2. Danh sach sinh vien:  \n";
			Show(l);
		}
		if (n == 3) {
			cout << "3. Sap xep danh sach sinh vien theo D1.\n";
			insertionSort(&l.pHead);
			cout << "Danh sach sinh vien da duoc sap xep!!! \n";
			Show(l);
		}
		if (n == 4) {
			cout << "3. Sap xep danh sach sinh vien theo D2.\n";
			insertionSortM2(&l.pTail);
			cout << "Danh sach sinh vien da duoc sap xep!!! \n";
			Show(l);
		}
		if (n == 5) {
			cout << "5. Xoa sinh vien khoi danh sach \n";
			xoaSV(l);
		}
		if (n == 6) {
			DocFile(l);
		}
		if (n == 7) {
			ThemMonPhu(l);
		}
		if (n == 9) {
			GhiFile(l);
			cout << "Ghi file thanh cong" << endl;
		}
		if (n == 8) {
			DiemMonPhu(l);
		}
		if (n == 0) {
			break;
		}
	}
}




