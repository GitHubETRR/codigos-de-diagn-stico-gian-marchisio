#include <iostream>
#include <cmath>
using namespace std;

unsigned long long factorial(int n) {
    if (n < 0) return 0; 
    unsigned long long r = 1;
    for (int i = 2; i <= n; i++) r *= (unsigned long long)i;
    return r;
}

int main() {
    int op;
    do {
        cout << "\n===== CALCULADORA =====\n";
        cout << "1) Suma\n";
        cout << "2) Resta\n";
        cout << "3) Multiplicacion\n";
        cout << "4) Division\n";
        cout << "5) Raiz cuadrada\n";
        cout << "6) Potencia (a^b)\n";
        cout << "7) Exponencial (e^x)\n";
        cout << "8) Factorial (n!)\n";
        cout << "9) Resolvente (ax^2 + bx + c = 0)\n";
        cout << "10) Modulo (a % b) [enteros]\n";
        cout << "11) Logaritmo (ln y log10)\n";
        cout << "0) Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch (op) {
            case 1: {
                double a, b; cout << "a: "; cin >> a; cout << "b: "; cin >> b;
                cout << "a + b = " << (a + b) << "\n";
            } break;

            case 2: {
                double a, b; cout << "a: "; cin >> a; cout << "b: "; cin >> b;
                cout << "a - b = " << (a - b) << "\n";
            } break;

            case 3: {
                double a, b; cout << "a: "; cin >> a; cout << "b: "; cin >> b;
                cout << "a * b = " << (a * b) << "\n";
            } break;

            case 4: {
                double a, b; cout << "a (dividendo): "; cin >> a; cout << "b (divisor): "; cin >> b;
                if (b == 0) cout << "Error: Imposible dividir por 0.\n";
                else cout << "a / b = " << (a / b) << "\n";
            } break;

            case 5: {
                double x; cout << "x: "; cin >> x;
                if (x >= 0) cout << "sqrt(x) = " << sqrt(x) << "\n";
                else cout << "Raiz de negativo: " << sqrt(-x) << " * i\n";
            } break;

            case 6: {
                double a, b; cout << "Base a: "; cin >> a; cout << "Exponente b: "; cin >> b;
                cout << "a^b = " << pow(a, b) << "\n";
            } break;

            case 7: {
                double x; cout << "x: "; cin >> x;
                cout << "e^x = " << exp(x) << "\n";
            } break;

            case 8: {
                int n; cout << "n (entre 0 y 20): "; cin >> n;
                if (n < 0) cout << "No existe factorial de negativo.\n";
                else cout << "n! = " << factorial(n) << "\n";
            } break;

            case 9: {
                double a, b, c; cout << "a: "; cin >> a; cout << "b: "; cin >> b; cout << "c: "; cin >> c;
                if (a == 0) {
                    cout << "a no puede ser 0.\n";
                } else {
                    double D = b*b - 4*a*c;
                    cout << "Discriminante = " << D << "\n";
                    if (D > 0) {
                        double x1 = (-b + sqrt(D)) / (2*a);
                        double x2 = (-b - sqrt(D)) / (2*a);
                        cout << "x1 = " << x1 << "\n";
                        cout << "x2 = " << x2 << "\n";
                    } else if (D == 0) {
                        double x = (-b) / (2*a);
                        cout << "x = " << x << " (raiz doble)\n";
                    } else {
                        double real = (-b) / (2*a);
                        double imag = sqrt(-D) / (2*a);
                        cout << "x1 = " << real << " + " << imag << "i\n";
                        cout << "x2 = " << real << " - " << imag << "i\n";
                    }
                }
            } break;

            case 10: {
                long long a, b; cout << "a (entero): "; cin >> a; cout << "b (entero, !=0): "; cin >> b;
                if (b == 0) cout << "Error: modulo por cero.\n";
                else cout << "a % b = " << (a % b) << "\n";
            } break;

            case 11: {
                double x; cout << "x (>0): "; cin >> x;
                if (x <= 0) cout << "Error: log no definido para x<=0.\n";
                else {
                    cout << "ln(x)     = " << log(x)   << "\n";
                    cout << "log10(x)  = " << log10(x) << "\n";
                }
            } break;

            case 0:
                cout << "Gracias!\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }
    } while (op != 0);

    return 0;
}
