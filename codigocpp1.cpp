#include <iostream>
using namespace std;

float sumar(float a, float b);
float restar(float a, float b);
float multiplicar(float a, float b);
float dividir(float a, float b);

int main() {
    float num1, num2, resultado;
    int opcion;

    cout << "Calculadora básica en C++" << endl;
    cout << "Ingrese el primer número: ";
    cin >> num1;
    cout << "Ingrese el segundo número: ";
    cin >> num2;

    cout << "Seleccione la operación:" << endl;
    cout << "1. Suma" << endl;
    cout << "2. Resta" << endl;
    cout << "3. Multiplicación" << endl;
    cout << "4. División" << endl;
    cout << "Opción: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            resultado = sumar(num1, num2);
            cout << "Resultado: " << resultado << endl;
            break;
        case 2:
            resultado = restar(num1, num2);
            cout << "Resultado: " << resultado << endl;
            break;
        case 3:
            resultado = multiplicar(num1, num2);
            cout << "Resultado: " << resultado << endl;
            break;
        case 4:
            resultado = dividir(num1, num2);
            cout << "Resultado: " << resultado << endl;
            break;
        default:
            cout << "Opción no válida." << endl;
    }

    return 0;
}

float sumar(float a, float b) {
    return a + b;
}

float restar(float a, float b) {
    return a - b;
}

float multiplicar(float a, float b) {
    return a * b;
}

float dividir(float a, float b) {
    if (b == 0) {
        cout << "Error: División por cero." << endl;
        return 0;
    }
    return a / b;
}
