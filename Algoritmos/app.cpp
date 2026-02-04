#include <iostream>
#include <cmath>

using namespace std;
int main() {
    int idade;
    cout << "Qual sua idade?" << endl;
    cin >> idade;
    cout << "Voce tem " << idade << " anos." << endl;

    int idadepai;
    cout << "Qual a idade do seu pai?" << endl;
    cin >> idadepai;
    cout << "Seu pai eh " << idadepai - idade << " anos mais velho que voce." << endl;

    return 0;
}
