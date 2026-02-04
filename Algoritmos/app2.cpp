#include <iostream>
using namespace std;

#define pi 3.14
#define valeu cout << "Obrigado por usar nosso programa!" << endl;

int contagemregressiva(int n);

int main (){
    int a=6;
    int b=3;

    valeu;
    cout << "Soma: " << a + b << endl;
    cout << "Subtracao: " << a - b << endl;
    cout << "Multiplicacao: " << a * b << endl;
    cout << "Divisao: " << a / b << endl;
    cout << "Resto: " << a % b << endl;

    cout << "------------------" << endl;
    cout << "Digite os segundos para contagem regressiva: ";
    int n;
    cin >> n;
    contagemregressiva(n);
    return 0;
}

int contagemregressiva(int n){
    for (int i=n; i>=0; i--) {
        cout << i << endl;
    }
    return 0;
}