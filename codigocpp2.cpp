#include <iostream>
using namespace std;

float calcularPromedio(int vector[], int tam);
void mostrarDatos(int vector[], int tam);

int main() {
    int n;
    do {
        cout << "¿Cuántos números desea ingresar? ";
        cin >> n;
        if (n > 100 || n <= 0) {
            cout << "Error: Debe ingresar un número mayor que 0 y menor o igual a 100." << endl;
        }
    } while (n > 100 || n <= 0);

    int vector[100];

    for (int i = 0; i < n; i++) {
        cout << "Ingrese el número " << i + 1 << ": ";
        cin >> vector[i];
    }

    mostrarDatos(vector, n);

    return 0;
}

float calcularPromedio(int vector[], int tam) {
    int suma = 0;
    for (int i = 0; i < tam; i++) {
        suma += vector[i];
    }
    return (float)suma / tam;
}

void mostrarDatos(int vector[], int tam) {
    cout << "Cantidad de números ingresados: " << tam << endl;
    cout << "Números: ";
    for (int i = 0; i < tam; i++) {
        cout << vector[i];
        if (i < tam - 1) cout << ", ";
    }
    cout << endl;
    float promedio = calcularPromedio(vector, tam);
    cout << "El promedio es: " << promedio << endl;
}
