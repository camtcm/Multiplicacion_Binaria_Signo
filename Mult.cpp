#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void mult(string&, string&, string&);
void shift(string&, string&, int&);
string sum(string, string);
string complement(string);
string decimalToBinary(string);

int main() {
    string M, Q;
    int formato;
    cout << "Formato para agregar los números: " << endl;
    cout << "1) Binario" << endl;
    cout << "2) Decimal" << endl;
    cin >> formato;

    cout << "Ingrese el multiplicando (M): ";
    cin >> M;

    cout << "Ingrese el multiplicador (Q): ";
    cin >> Q;

    if (!formato) {
        M = decimalToBinary(M);
        Q = decimalToBinary(Q);
    }

    string A(Q.length(), '0');
    mult(M, Q, A);
    cout << "Respuesta: " << A << Q;
}

string complement(string binario) {
    string complement;
    string temp(binario.length(), '0');
    temp.back() = '1';

    for (char bit : binario) {
        if (bit == '1') {
            complement += '0';
        }
        else if (bit == '0') {
            complement += '1';
        }
    }
    complement = sum(complement, temp); // Sumar uno 
    return complement;
}

string sum(string binary1, string binary2) {
    string resultado(binary1.length(), '0');
    int acarreo = 0;

    for (int i = binary1.length() - 1; i >= 0; i--) {
        int bit1 = stoi(string(1, binary1[i]));
        int bit2 = stoi(string(1, binary2[i]));

        int suma = bit1 + bit2 + acarreo;

        resultado[i] = to_string(suma % 2)[0];

        acarreo = suma / 2;
    }
    return resultado;
}

void shift(string& A, string& Q, int& Q_1) {
    Q_1 = stoi(string(1,Q.back()));

    Q = A.back() + Q.substr(0, Q.length() - 1);
    A = A[0] + A.substr(0, A.length() - 1);
}

string decimalToBinary(string str) {
    string bin;
    int decimal = stoi(str);
    int residuo;

    bool neq = (decimal < 0) ? true : false;
    decimal = abs(decimal);

    while (decimal > 0) {
        residuo = decimal % 2;
        bin += to_string(residuo);
        decimal = decimal / 2;
    }

    bin += "0"; // Auxiliar
    reverse(bin.begin(),bin.end());
    if (neq) {
        bin = complement(bin);
    }
    
    return bin;
}

void mult(string& M, string& Q, string& A) {
    int count = Q.length();
    int Q_1 = 0;
    int lastDigit_Q;
    while (count != 0) {
        lastDigit_Q = stoi(string(1,Q[Q.length() - 1]));

        if (lastDigit_Q == Q_1) {
            shift(A, Q, Q_1);
        }
        else if (lastDigit_Q == 0 && Q_1 == 1) {
            // A + M 
            A = sum(A, M);
            shift(A, Q, Q_1);
        }
        else {
            // A - M
            A = sum(A, complement(M));
            shift(A, Q, Q_1);
        }
        count--;
    }
}

