#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

string extensor(string, int);
void mult(string&, string&, string&);
void shift(string&, string&, int&);
string sum(string, string);
string complement(string);
string decimalToBinary(string); // Complemento a dos
int binaryToDecimal(string);

int main() {
    string M, Q;
    int formato;
    cout << "--- Menu --- " << endl;
    cout << "1) Binario" << endl;
    cout << "2) Decimal" << endl;
    cout << "Elija un formato para los numeros: ";
    cin >> formato;

    if (formato != 2 && formato != 1) {
        cout << "Opcion invalida";
        return 0; 
    }

    cout << "Ingrese el multiplicando (M): ";
    cin >> M;

    cout << "Ingrese el multiplicador (Q): ";
    cin >> Q;

    if (formato == 2) {
        cout << endl << "--- Conversion --- " << endl <<"M: ";
        M = decimalToBinary(M);
        cout << M << endl << "Q: ";
        Q = decimalToBinary(Q);
        cout << Q << endl;
    } else {
        // cout << "M decimal: " << M << " | " << binaryToDecimal(M) << endl;
        // cout << "Q decimal: " << Q << " | " << binaryToDecimal(Q) << endl;
        cout << endl << "M decimal: " << binaryToDecimal(M);
        cout << endl << "Q decimal: " << binaryToDecimal(Q) << endl;
    }

    if (M.length() != Q.length()) {
        cout << endl << "--- Extension --- " << endl << "M: ";
        M = extensor(M, max(M.length(), Q.length()));
        cout << M << endl << "Q: ";
        Q = extensor(Q, max(M.length(), Q.length()));
        cout << Q << endl;
    }

    string A(Q.length(), '0'); // Cadena auxiliar
    mult(M, Q, A);
    cout << endl <<"Respuesta binario: " << A << Q;
    cout << endl <<"Respuesta decimal: " << binaryToDecimal(A+Q);
}

string complement(string binario) {
    string complement;
    string temp(binario.length(), '0');
    temp.back() = '1';

    for (char bit : binario) { // Negar
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
    Q_1 = stoi(string(1, Q.back()));

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

    bin += "0"; // signo
    reverse(bin.begin(), bin.end());
    if (neq) {
        bin = complement(bin);
    }

    return bin;
}

void mult(string& M, string& Q, string& A) {
    int count = Q.length();
    int Q_1 = 0;
    int lastDigit_Q;

    cout << endl <<"--- Inicio de la multiplicacion --- " << endl;
    cout << "A: " << A << ", Q: " << Q << ", Q_1: " << Q_1 << ", M: " << M << endl;

    while (count != 0) {
        lastDigit_Q = stoi(string(1, Q[Q.length() - 1])); // cadena a entero

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
        cout << "A: " << A << ", Q: " << Q << ", Q_1: " << Q_1 << ", M: " << M <<  endl;
    }
}

string extensor(string bin, int len) {
    while (bin.length() != len) {
        bin = bin[0] + bin;
    }
    return bin;
}

int binaryToDecimal(string binary) {
    int decimal = 0;
    int power = 0;
    bool neq = false;

    if (binary[0] == '1') {
        neq = true;
    }

    for(int i = binary.length() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += pow(2,power);
        }
        power++;
    }

    if (neq) {
        decimal = decimal - pow(2, binary.length());
    }

    return decimal;
}
