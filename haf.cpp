#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;
struct Uzel
{
    string key; int p=0;
    Uzel *left=NULL,*right=NULL,*next=NULL;

};
struct Tree
{
    Uzel *first=NULL, *last=NULL; 
};


void addbyaski(int* mas, Tree* b, int &n) 
{
    for (int i = 0; i < 256; i++) {
        if (mas[i] != 0) {
            Uzel* list = new Uzel; 
            list->key=(char) i;
            list->p = mas[i];
            list->right = NULL;
            list->left = NULL;
            if (b->first == NULL)
            {
                b->first = list;
                b->last = list;
                n++;
            }
            else
            {
                b->last->next = list;
                b->last = list;
                n++;
            }
        }
    }
}

void sort(Tree* b, int &n)
{
    int f,i,j,p1;
    string key1;
    Uzel* i1, *j1;
    for (i = 0,f=1,i1=b->first;i<n&&f;i++,i1->next)
    for (j = 0,f = 0,j1=b->first;j < n - 1 - i;j++,j1->next) {
        if (j1->p > i1->p) {
            p1 = j1->p; j1->p = i1->p; i1->p = p1;
            key1= j1->key; j1->key = i1->key; i1->key = key1;
            f = 1;
        }
    }
    Uzel* nov = new Uzel; 
    nov->p = b->first->p + b->first->next->p;
    nov->key = b->first->key+b->first->next->key;
    nov->left = b->first; nov->right = b->first->next;
    b->first = nov; b->first->next = nov->right;
    n--;
}

void outputlevel(Tree* b) 
{
    for (Uzel* i = b->first; i != b->last; i=i->next)
    {
        cout << i->key << ':' << i->p<<' ';
    }
}

int main()
{
    int aski[256]; char x;
    for (int i = 0; i < 256; i++) aski[i] = 0;
    ifstream a("text.txt");
    if (!a) { cout << "Ошибка открытия файла"; return 0; };
    a >> x;
    while (a) {
        aski[(int)x]++; a >> x;
    }
    for (int i = 0; i < 256; i++) cout << aski[i] << ' ';
    a.close(); 
    Tree* willbe = new Tree;
    int n = 0;
    addbyaski(aski, willbe,n);
    outputlevel(willbe);
    while(n>1)
    sort(willbe,n);
    outputlevel(willbe);
}