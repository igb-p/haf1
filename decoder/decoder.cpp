#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
using namespace std;
struct Uzel
{
    string key; int p = 0;
    Uzel* left = NULL, * right = NULL, * next = NULL;

};
struct Tree
{
    Uzel* first = NULL, * last = NULL;
};
void addbyfile(Tree* b, int& n, int& h, float& nu)
{
    ifstream a1("D:/chst.txt");
    a1.seekg(0, ios::beg);
    char x;
    int y;
    a1 >> h;
    cout << h;
    a1.get(x); cout << x << endl;
    a1 >> y;
    nu = 0; nu += y;
    while (a1)
    {
        Uzel* list = new Uzel;
        list->key = x;
        list->p = y;
        list->right = NULL;
        list->left = NULL;
        if (b->first == NULL)
        {
            b->first = list;
            b->last = list;

        }

        else
        {
            b->last->next = list;
            b->last = list;
        }
        n++;
        a1.get(x); cout << x << endl;
        a1 >> y; nu += y; cout << y << endl;
    }
    a1.close();
}

void outputlevel(Tree* b)
{
    for (Uzel* i = b->first; i != NULL; i = i->next)
    {
        cout << i->key << ':' << i->p << ' ';
    }
}

void swap(Tree* t, Uzel* a, Uzel* b) {
    Uzel* f;
    if (a != t->first) {
        for (f = t->first; f->next != a; f = f->next);
        f->next = b;
    }
    a->next = b->next;
    if (b == t->last) {
        t->last = a;
    }
    if (a == t->first) t->first = b;
    b->next = a;
}

void sort(Tree* b, int& n)
{
    int i, j, p1, f;
    string key1;
    Uzel* i1, * j1;
    for (i = 0, f = 1; i < n - 1; i++) {
        for (j = 1, f = 0, j1 = b->first; j <= n - 1 - i; j++, j1 = j1->next) {
            Uzel* j2 = j1->next;
            if (j1->p > j1->next->p) {
                swap(b, j1, j1->next);
                j1 = j2; f = 1;
            }

        }

    }
    outputlevel(b);
    cout << endl;
    n--;
}

void find(Tree* b, int& n)
{
    Uzel* nov = new Uzel;
    nov->p = b->first->p + b->first->next->p;
    nov->key = b->first->key + b->first->next->key;
    nov->left = b->first; nov->right = b->first->next;
    Uzel* it;

    for (it = b->first->next; it != b->last && it->next->p < nov->p; it = it->next);
    if (it != b->last) nov->next = it->next; it->next = nov;
    if (it == b->last) b->last = nov;
    if (b->first->next != b->last) {
        b->first = b->first->next->next;
    }
    else
        b->first = nov;
    outputlevel(b); cout << endl;
    n--;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    Tree* b = new Tree;
    int n = 0, h; float nu;
    addbyfile(b, n, h, nu);
    cout << b->first->p << endl;
    outputlevel(b);
    cout << endl;
    int t = n * 2 + 2;
    sort(b, n);
    while (n > 0)
    {
        find(b, n);
    }
    outputlevel(b);
    float num = 0;
    