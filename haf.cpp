#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
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


void addbyaski(int* mas, Tree* b, int& n, map<char, vector<bool>>& mp)
{
    ofstream a1("D:/chst.txt");
    a1 << ' ';
    for (int i = 0; i < 256; i++) {
        if (mas[i] != 0) {
            vector<bool> pust;
            mp.insert(pair<char, vector<bool>>((char)i, pust));
            Uzel* list = new Uzel;
            list->key = (char)i;
            list->p = mas[i];
            a1 << char(i); a1 << mas[i];
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

        }
    }
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


void dapmap(map<char, vector<bool>>& mp, Uzel* b, char k)
{
    Uzel* t = b;
    if (t->right || t->left)
    {

        if (t->left && t->left->key.find(k) != -1)
        {
            mp[k].push_back(0);
            t = t->left;

        }
        if (t->right && t->right->key.find(k) != -1)
        {
            mp[k].push_back(1);
            t = t->right;

        }
        dapmap(mp, t, k);
        cout << endl;
    }
}

int main()
{
    int aski[256]; char x;
    map<char, vector<bool>> babamapa;
    for (int i = 0; i < 256; i++) aski[i] = 0;
    ifstream a("D:/text.txt");
    if (!a) { cout << "Ошибка открытия файла"; return 0; };
    a >> x;
    while (a) {
        aski[(int)x]++; a.get(x);
    }
    for (int i = 0; i < 256; i++) cout << aski[i] << ' ';
    a.close();
    Tree* willbe = new Tree;
    int n = 0;
    addbyaski(aski, willbe, n, babamapa);
    sort(willbe, n);
    while (n > 0)
    {
        find(willbe, n);
    }
    outputlevel(willbe);
    map<char, vector<bool>>::iterator it;
    for (it = babamapa.begin(); it != babamapa.end(); it++)
    {
        dapmap(babamapa, willbe->first, it->first);
        cout << it->first << '-';
        for (int i = 0; i < babamapa[it->first].size(); i++)
            cout << babamapa[it->first][i];
        cout << endl;
    }
    a.open("D:/text.txt"); ofstream b("D:/2.txt"); fstream b1("D:/chst.txt");
    char sim = 0; int size = 7;
    a.get(x); it = babamapa.begin();
    n = 0;
    while (a) {
        it = babamapa.find(x);
        for (int i = 0; i < babamapa[it->first].size(); i++)
        {
            cout << babamapa[it->first][i];
            sim |= babamapa[it->first][i] << size;
            size--;
            if (size < 0) {
                cout << '-' << int(sim) << endl; size = 7; b << sim;
                sim = 0; n++;
            }
        }
        a.get(x);
    }
    
    b << sim; 
    if (size == 7) size = -1;
    b1 << size+1;
    cout << endl;
    cout << n << endl;
    _fcloseall();
}