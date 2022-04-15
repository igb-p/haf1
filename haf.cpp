#include <iostream>
#include <fstream>
using namespace std;
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
}