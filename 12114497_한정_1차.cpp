#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#include<stack>
#include <fstream>
#include <time.h>
#define BLACK 1
#define RED 0
#define Level_0 3000000
#define Level_1 30000000
#define Level_2 300000000
using namespace std;
char inp;
/*Max_val�� ���ȸ�� ������ �� ���ݾװ� key�� ��� �����Դϴ�*/
vector<pair<int, int> > Max_val;
/******************************************************************
Log�� ��ǰ���� ������ ��� ����ü �Դϴ�. when : ���� what : ������
howmuch : �󸶳� ����� ��忡 ����ϴ�. prev�� ���� Log next�� ����
�α׸� ����ŵ�ϴ�.
*******************************************************************/
struct Log {
	long long when;
	string what;
	long long howmuch;
	Log *prev;
	Log *next;
};
/******************************************************************
Client�� �� ������ ������ ��� ����ü �Դϴ�. key : ���� key��
name, phone : �̸�, ��ȭ��ȣ x,y : ���� x,y��ǥ level : �����
total : �� ��뷮 , color : Ʈ�� �󿡼� ����� �� �� ����ϴ�.
prev : �θ���, right : ������ ��� , left : ���ʳ�� �� ����ŵ�ϴ�.
start, end : �� ���� ���� �α��� ���� �� �ּҸ� ����ŵ�ϴ�.
*******************************************************************/
struct Client {
	int key;
	string name;
	string phone;
	int x;
	int y;
	int level = 0;
	long long total = 0;
	int color = 0;
	Client *prev = 0;
	Client *right = 0;
	Client *left = 0;
	Log *start = 0;
	Log *end = 0;
};
/******************************************************************
root�� ��� private������ �ֽ��ϴ�. �������� �� ������Ʈ���� ����ϴ�
�Լ��� �Դϴ�.
*******************************************************************/
class RBtree {
private:
	Client *root;
public:
	void rbtree();
	void insertItem(int Flag, int Key, string Name, string Phone, 
		int X, int Y, int Level, long long Total);
	bool isDoubleRed(Client *node);
	void recoloring(Client *node, Client *uncle);
	void restructuring(Client *node);
	void Rerestructuring(Client *node);
	int Find_depth(Client *node);
	void FindNode();
	void Find_info();
	void Insertgoods(Client *node, Log *temp);
	void Find_RecentLog();
};
void RBtree::rbtree() {
	root = 0;
}
/******************************************************************
 �Լ���: Find_info()
 ����ð�: O(h)
 ����: key���� �Է� �ް� ��Ʈ���� key���� ���� ���鼭 ��带 ã���ϴ�.
	  ã�� ���� ���·� leaf������ ������ ��� Ʈ�� ���� �ش� ��尡
	  ���� ���� �ǹ��ϹǷ� Not found!�� ����մϴ�.
	  ���� ��� �̸�, ��ȭ��ȣ, x, y��ǥ, ���, �� ������, ������ ���
	  �ϰ� �˴ϴ�. ���⼭ depth�� ����ϴ� �Լ� ���� O(h)�ð����� ����
	  �˴ϴ�.
*******************************************************************/
void RBtree::Find_info() {
	int key;
	cin >> key;
	if (root == 0) {
		puts("Not found!");
		return;
	}
	Client *ptr = root;
	while (1) {
		if (ptr->key == key) {
			cout << ptr->name << " " << ptr->phone << " " << ptr->x << " " << ptr->y << " "
				<< ptr->level << " " << ptr->total << " " << Find_depth(ptr) << endl;
			break;
		}
		if (ptr->key > key) {
			if (ptr->left == 0) {
				printf("Not found!\n");
				break;
			}
			else ptr = ptr->left;
		}
		else {
			if (ptr->right == 0) {
				printf("Not found!\n");
				break;
			}
			else ptr = ptr->right;
		}
	}
}
/******************************************************************
 �Լ���: FindNode()
 ����ð�: O(h)
 ����: ���ο� ��ǰ ���������� �߰��ϴ� �Լ��Դϴ�. ���� �� key���� ����
	��带 ã���ϴ�. �� �� level�� �� �� �ѵ��� �Ǵ��Ͽ� �ѵ��� �Ѿ��
	��� �α׸� �߰���Ű�� �ʽ��ϴ�. ���� �ѵ����� ���� ��� ���ȸ����
	�Ǵ��ϴ� ������ ��ģ �� Insertgoods�Լ��� �����ϰ� �˴ϴ�.
*******************************************************************/
void RBtree::FindNode() {
	int Key, val;
	long long E;
	string goods;
	cin >> Key >> E >> goods >> val;
	if (root == 0) {
		puts("Not found!");
		return;
	}
	Client *ptr = root;
	while (1) {
		/*��ġ�� ��� �ѵ��� �Ǵ��ϰ� �˴ϴ�. �Ѿ ��� depth�� ����ϰ�
		while���� ���������� �˴ϴ�.*/
		if (ptr->key == Key) {
			if (ptr->level == 0) {
				if ((ptr->total) + val > Level_0) {
					printf("%d 0\n", Find_depth(ptr));
					break;
				}
			}
			else if (ptr->level == 1) {
				if ((ptr->total) + val > Level_1) {
					printf("%d 0\n", Find_depth(ptr));
					break;
				}
			}
			else if (ptr->level == 2) {
				if ((ptr->total) + val > Level_2) {
					printf("%d 0\n", Find_depth(ptr));
					break;
				}
			}
			/*�ѵ��� ���� �ʾ��� ���*/
			ptr->total += val;
			/***************************************************************
			���ȸ���� �Ǵ��ϴ� �κ��Դϴ�. 
			���� �� ���Ϳ� �ƹ��� ���� ������� �ʴٸ� �Է��� ���ݴϴ�. 
			����� 1���� ū��� ���ͳ��� �̹� �� key���� ������ �ִٸ� ������
			�ƴҰ�� ���� �ּҰ��� ���Ͽ� �߰��� ���ִ� ������� �����Ͽ����ϴ�.
			****************************************************************/
			if (Max_val.size() == 0)
				Max_val.push_back(make_pair(ptr->total, ptr->key));
			else if (Max_val.size() < 3){
				bool isthere = false;
				for (int i = 0; i < Max_val.size(); i++){
					if (ptr->key == Max_val[i].second){
						isthere = true;
						Max_val[i].first = ptr->total;
						break;
					}
				}
				if (!isthere)
					Max_val.push_back(make_pair(ptr->total, ptr->key));
				sort(Max_val.begin(), Max_val.end());
			}
			else{
				if (Max_val[0].first < ptr->total){
					bool isthere = false;
					for (int i = 0; i < Max_val.size(); i++){
						if (ptr->key == Max_val[i].second){
							isthere = true;
							Max_val[i].first = ptr->total;
							break;
						}
					}
					if (!isthere){
						Max_val[0].first = ptr->total;
						Max_val[0].second = ptr->key;
					}
					sort(Max_val.begin(), Max_val.end());
				}
			}
			/*���ο� �α׸� ����� �߰������ݴϴ�.*/
			Log *temp = new Log();
			temp->howmuch = val;
			temp->when = E;
			temp->what = goods;
			Insertgoods(ptr, temp);
			printf("%d 1\n", Find_depth(ptr));
			break;
		}
		if (ptr->key > Key) {
			if (ptr->left == 0) {
				puts("Not found!");
				break;
			}
			else ptr = ptr->left;
		}
		else {
			if (ptr->right == 0) {
				puts("Not found!");
				break;
			}
			else ptr = ptr->right;
		}
	}
}
/******************************************************************
�Լ���: Insertgoods(Client *node, Log *temp)
����ð�: O(1)
����: �Ѱܹ��� �ش� ���� temp��� ���� ���� �α� ������ �޾� �����մϴ�.
	�αװ� ó�� �Է� �� ���� ���� ��츦 �����Ͽ� �Է��մϴ�.
	���� ��� end�� start�� temp�� �������ݴϴ�.
	������� end�� next�� �Է��� �� �� end�� temp�� �����մϴ�.
*******************************************************************/
void RBtree::Insertgoods(Client *node, Log *temp) {
	//�αװ� ���� ���
	if (node->start == 0) {
		node->start = temp;
		node->end = temp;
		temp->prev = 0;
		temp->next = 0;
		return;
	}
	//���� ���
	Log *st = node->end;
	st->next = temp;
	temp->prev = st;
	node->end = temp;
}
/******************************************************************
 �Լ���: Find_RecentLog()
 ����ð�: O(h)
 ����: key���� �������� �ش� ��带 ã���ϴ�. ��带 ��ã�� leaft������
	������ ��� Not found!�� ����մϴ�. ��带 ã���� ��� �ش� �����
	�α��� end���� Size��ŭ ���ʴ�� ����ϸ鼭 ��尣 �̵��� �մϴ�.
*******************************************************************/
void RBtree::Find_RecentLog() {
	int Key, Size;
	cin >> Key >> Size;
	if (root == 0) {
		puts("Not found!");
		return;
	}
	Client *ptr = root;
	bool isDone = false;
	while (1) {
		if (ptr->key > Key) {
			if (ptr->left == 0) {
				puts("Not found!");
				return;
			}
			else ptr = ptr->left;
		}
		else if (ptr->key < Key) {
			if (ptr->right == 0) {
				puts("Not found!");
				return;
			}
			else ptr = ptr->right;
		}
		else {
			if (ptr->end == 0) {
				puts("0");
				break;
			}
			Log *st = ptr->end;
			for (int i = 0; i < Size; i++) {
				cout << st->when << " " << st->what << " " << st->howmuch << endl;
				if (st == ptr->start)
					return;
				st = st->prev;
				isDone = true;	//��� �� Ż���� ���� flag�Դϴ�. 
			}
		}
		if (isDone) return;//����� �Ϸ���� ��� ���̻� while���� ���� �ʽ��ϴ�.
	}
}
/******************************************************************
�Լ���: Find_depth(Client *node)
����ð�: O(h)
����: �ش� ������ root���� �̵��� �ϸ� dep�̶�� ������ �������� �ݴϴ�.
	root�� �������� ��� �� ������ dep�� ��ȯ�մϴ�.
*******************************************************************/
int RBtree::Find_depth(Client *node) {
	int dep = 0;
	if (root == 0) return 0;
	Client *ptr = node;
	while (1) {
		if (ptr == root) break;
		ptr = ptr->prev;
		dep++;
	}
	return dep;
}
/******************************************************************
�Լ���: isDoubleRed(Client *node)
����ð�: O(1)
����: �ڽ��� ���� �θ� ��带 ���Ͽ� �� ��� ��� Ʈ���� RED�� ���
	true�� ��ȯ�ϰ� �˴ϴ�.
*******************************************************************/
bool RBtree::isDoubleRed(Client *node) {
	if (node->prev == root) return 0;
	if (node == root) return 0;
	return (node->color == RED && node->prev->color == RED);
}
/******************************************************************
�Լ���: recoloring(Client *node, Client *uncle)
����ð�: O(1)
����: �����尡 �߻��߰� uncle��尡 RED�϶� recoloring�� �����ϰ� 
	�˴ϴ�. ���� �θ� ���� ���� ����� ���� black���� ������ְ�
	grandparent ��尡 root�� �ƴҰ�� RED�� ������ �ϰ� �˴ϴ�.
	���� root�� �ƴҰ�� �����尡 �� �߻��� �� �����Ƿ� �Ǵ��� �ϴ�
	�Լ��� �ٽ� ��������� �����ϰ� �˴ϴ�.
*******************************************************************/
void RBtree::recoloring(Client *node, Client *uncle) {
	node->prev->color = BLACK;
	uncle->color = BLACK;
	node = node->prev->prev;
	if (node == root) return;
	node->color = RED;
	if (isDoubleRed(node))
		Rerestructuring(node);
	return;
}
/*******************************************************************************************************
�Լ���:insertItem(int Flag, int Key, string Name, string Phone, int X, int Y, int Level, long long Total)
����ð�: O(h)
����: temp��� ���ο� ��带 ����� �Է¹��� �����͸� �ֽ��ϴ�. �� �� key���� ���ϸ鼭 �������� �˴ϴ�.
	leaf������ ���� �� �� ������ ���θ� �Ǵ��Ͽ� recoloring Ȥ�� restructuring �� �Ǵ��ϴ� �Լ��� �����ϰ�
	�˴ϴ�. ���� flag�� 1�ϰ�� ó�� memberlist�� �Է¹��� ���� �ƴϹǷ� depth�� ����ϰ� �˴ϴ�.
*********************************************************************************************************/
void RBtree::insertItem(int Flag, int Key, string Name, string Phone, 
	int X, int Y, int Level, long long Total) {
	Client *temp = new Client();
	temp->key = Key;
	temp->name = Name;
	temp->phone = Phone;
	temp->x = X;
	temp->y = Y;
	temp->level = Level;
	temp->total = Total;
	temp->color = RED;
	if (root == 0) {
		root = temp;
		temp->color = BLACK;
		return;
	}
	else {
		Client *ptr = root;
		while (1) {
			if (ptr->key > temp->key) {
				if (ptr->left == 0) {
					ptr->left = temp;
					temp->prev = ptr;
					break;
				}
				else
					ptr = ptr->left;
			}
			else if (ptr->key < temp->key) {
				if (ptr->right == 0) {
					ptr->right = temp;
					temp->prev = ptr;
					break;
				}
				else
					ptr = ptr->right;
			}
			else {
				cout << Find_depth(ptr) << " 0" << endl;
				return;
			}
		}
	}
	if (isDoubleRed(temp))
		Rerestructuring(temp);
	if (Flag == 1) cout << Find_depth(temp) << " 1" << endl;
}
/******************************************************************
�Լ���: Rerestructuring(Client *node)
����ð�: O(h)
����: ó������ uncle��带 grandparent ����� ��ġ�� �ø� �� 
	�� �� ��忡 �θ��尡 �ִ��� �Ǵ� �� �� �� �ݴ� ���⿡ ���� ��� 
	��ġ�� ���� �ϰ� �˴ϴ�. �� �Լ��� ������ �ϰ� �Ȱ� �̹� �����尡
	�߻��� ���̱� ������ uncle�� ���� �� �� RED�� recoloring, BLACK�̸�
	restructuring�� �����ϰ� �˴ϴ�.
*******************************************************************/
void RBtree::Rerestructuring(Client *node) {
	Client *uncle = node->prev->prev;
	if (uncle->left == node->prev)
		uncle = uncle->right;
	else
		uncle = uncle->left;
	if (uncle == 0)
		restructuring(node);
	else if (uncle->color == RED)
		recoloring(node, uncle);
	else
		restructuring(node);
}
/******************************************************************
�Լ���: restructuring(Client *node)
����ð�: O(1)
����: 3���� ��带 ���� �и��Ͽ� ũ������ mid, right, left��带 ����
	�Ͽ� �ݴϴ�. �� ��忡 �޴޸� ��带 ���� ������� T1,T2,T3,T4�� �ϸ�
	����Ʈ��ó���� �ϰ� �� ��� T1, T4�� ������ �ȹް� T2, T3�� Left, Right
	�� �޴޾� �ֱ⸸ �ϸ� �ǹǷ� ���� 4���� ��츦 �и��Ͽ� �����Ͽ����ϴ�.
	���� �� mid�� ���� BLACK �������� RED�� �� �� �Լ��� ����ǰ�
	�˴ϴ�. ���� mid�� root�� �� ��� root���� ������ ���ְ� �ƴҰ��
	�� ���� ��忡 �����ϰ� �˴ϴ�.
*******************************************************************/
void RBtree::restructuring(Client *node) {
	Client *parent = node->prev;
	Client *grand = node->prev->prev;
	Client  *T2, *T3, *mid, *Left, *Right, *Prev;
	int LeftRight = 0, isroot = 0;//0�̸� Left, 1�̸� Right, root�� 0 �ƴϸ� 1
	if (grand != root) {
		Prev = grand->prev;
		isroot = 1;
		if (grand->prev->right == grand)
			LeftRight = 1;
	}
	if (node->key > parent->key) {
		if (node->key > grand->key) {
			T2 = parent->left, T3 = node->left;
			mid = parent, Left = grand, Right = node;
		}
		else {
			T2 = node->left, T3 = node->right;
			mid = node, Left = parent, Right = grand;
		}
	}
	else {
		if (node->key > grand->key) {
			T2 = node->left, T3 = node->right;
			mid = node, Left = grand, Right = parent;
		}
		else {
			T2 = node->right, T3 = parent->right;
			mid = parent, Left = node, Right = grand;
		}
	}
	mid->left = Left, mid->right = Right;
	Left->prev = mid, Right->prev = mid;
	mid->color = BLACK, Left->color = RED, Right->color = RED;
	Left->right = T2, Right->left = T3;
	if (T2 != 0) Left->right->prev = Left;
	if (T3 != 0) Right->left->prev = Right;
	if (isroot == 1) {
		mid->prev = Prev;
		if (LeftRight == 1)
			Prev->right = mid;
		else
			Prev->left = mid;
	}
	else {
		root = mid;
		root->prev = 0;
	}
	return;
}
int main() {
//#ifdef _CONSOLE
	freopen("query_10k.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
//#endif
	std::ios::sync_with_stdio(false);
	string filename;
	printf("�Է������� �̸��� �Է��ϼ���: ");
	getline(cin, filename, '\n');
	ifstream fin;
	fin.open(filename.c_str(), ios::out);
	/*****************************************************************
	����� Ʈ���� ������ �ݴϴ�. ������ �� �� root�� 0���� �ʱ�ȭ �մϴ�.
	******************************************************************/
	RBtree rbtree;
	rbtree.rbtree();
	int Key, X, Y, Level; long long Total = 0;
	string Name, Phone;
	/***************************************************************************
	ó�� memberlist���� �Է��� �޽��ϴ�. insertItem�� ù��° ������ flag�� 0�ϰ��
	Insert�� �Ͼ�� ������ �Ǵ��� depth�� ������ ����� �ʿ䰡 �����Ƿ�
	flag�� ���� �Ǵ��Ͽ� ����� ���ϰ� �˴ϴ�
	***************************************************************************/
	while (fin >> Key >> Name >> Phone >> X >> Y >> Level >> Total)
		rbtree.insertItem(0, Key, Name, Phone, X, Y, Level, Total);
	while (cin >> inp) {
		/******************************************************
		flag�� 1�̹Ƿ� Insert�� �Ͼ�� ������ �Ǵ��� depth��
		������ ����ϰ� �˴ϴ�. O(h)�� ����ð��� �����ϴ�.
		******************************************************/
		if (inp == 'I') {
			cin >> Key >> Name >> Phone >> X >> Y;
			rbtree.insertItem(1, Key, Name, Phone, X, Y, 0, 0);
		}
		/*********************************************************
		ȸ���� �ִ��� ������ ã���ִ� �Լ� �Դϴ�. �Լ� ������ �Է���
		�޽��ϴ�. Key�� �������� ã�� ������ Not found, ������ �ش�
		������ ������ݴϴ�. O(h)�� ����ð��� �����ϴ�.
		**********************************************************/
		else if (inp == 'P')
			rbtree.Find_info();
		/*************************************************************
		Key�� �Է¹޾� �� Ű�� ���� ��尡 �ִ��� ���� ã���ϴ�. �������
		�� Ű�� ���Ͽ� ������ �߰� ��Ű�� �Լ��� �����մϴ�.
		**************************************************************/
		else if (inp == 'A')
			rbtree.FindNode();
		/*********************************************************************
		Max_val�̶� vector���� ������������ �ִ� 3���� ��� ȸ���� ����ֽ��ϴ�.
		��û�� ���� ��� ��¸� ���ָ� �ǹǷ� O(1)�Դϴ�.
		***********************************************************************/
		else if (inp == 'F'){
			for (int i = Max_val.size() - 1; i >= 0; i--)
				printf("%d ", Max_val[i].first);
			puts("");
		}
		/*********************************************************
		�ֱ� ���������� ��ȸ�ϹǷ� ���� Key�� �Է¹޾� �� ��尡 �ִ���
		ã���ϴ�. �� �� �� ����� �α��� end���� �Է��� ���� ����ŭ
		����� �ϰ� �˴ϴ�. O(h)�� ����ð��� �����ϴ�.
		***********************************************************/
		else if (inp == 'R')
			rbtree.Find_RecentLog();
		/**********************************
		Q�� ���� ��� �Լ��� ������ �ݴϴ�.
		**********************************/
		else if (inp == 'Q')
			return 0;
	}
}