#include <iostream>
using namespace std;
int main() {
    float nota1;
    float nota2;
    float nota3;

    cout << "Digite a primeira nota: ";
    cin >> nota1;
    cout << "Digite a segunda nota: ";
    cin >> nota2;
    cout << "Digite a terceira nota: ";
    cin >> nota3;
    float media = (nota1 + nota2 + nota3) / 3;
    cout << "Sua media eh: " << media << endl;

    //Para ser aprovado a media deve ser maior ou igual a 6
    //Se a nota for igual a 0 , tirou F
    //Se a nota for menor que 6 , tirou D
    //Se a nota for entre 6 e 7 , tirou C
    //Se a nota for entre 7 e 8.5 , tirou B
    //Se a nota for entre que 8.5 e 10, tirou A
    if(media == 0){
        cout << "Reprovado! Sua nota eh F, estude mais!" << endl;
    } else if(media < 6){
        cout << "Reprovado! Sua nota eh D, estude mais!" << endl;
    } else if(media>=6 && media < 7){
        cout << "Sua nota eh C! Passou por pouco, estude mais!" << endl;
    } else if(media < 8.5){
        cout << "Sua nota eh B! Parabens!" << endl;
    } else if(media <= 10){
        cout << "Sua nota eh A! Excelente trabalho!" << endl;
    }

}