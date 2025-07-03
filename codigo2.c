#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ESTUDIANTES 100
#define MAX_MATERIAS 10
#define MAX_NOMBRE 50
#define ARCHIVO_DATOS "notas_estudiantes.dat"

// Estructura para almacenar la información de un estudiante
typedef struct {
    char nombre[MAX_NOMBRE];
    float notas[MAX_MATERIAS];
    int cantidad_materias;
} Estudiante;

// Prototipos de funciones
void ingresar_estudiantes(Estudiante *estudiantes, int *cantidad, int max_materias);
void guardar_en_archivo(Estudiante *estudiantes, int cantidad, int max_materias);
void mostrar_estudiantes(Estudiante *estudiantes, int cantidad, int max_materias);
int cargar_desde_archivo(Estudiante *estudiantes, int max_materias);

int main() {
    Estudiante estudiantes[MAX_ESTUDIANTES];
    int cantidad_estudiantes = 0;
    int max_materias = 0;
    int opcion;

    // Intentar cargar datos previos
    cantidad_estudiantes = cargar_desde_archivo(estudiantes, MAX_MATERIAS);
    if (cantidad_estudiantes > 0) {
        max_materias = estudiantes[0].cantidad_materias;
        printf("Se cargaron %d estudiantes desde el archivo.\n", cantidad_estudiantes);
    }

    do {
        printf("\n--- Sistema de Gestión de Notas ---\n");
        printf("1. Ingresar estudiantes y notas\n");
        printf("2. Mostrar estudiantes y notas\n");
        printf("3. Guardar y salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer

        switch (opcion) {
            case 1:
                printf("Ingrese la cantidad de materias: ");
                scanf("%d", &max_materias);
                getchar();
                if (max_materias > MAX_MATERIAS || max_materias <= 0) {
                    printf("Cantidad de materias inválida.\n");
                    break;
                }
                ingresar_estudiantes(estudiantes, &cantidad_estudiantes, max_materias);
                break;
            case 2:
                mostrar_estudiantes(estudiantes, cantidad_estudiantes, max_materias);
                break;
            case 3:
                guardar_en_archivo(estudiantes, cantidad_estudiantes, max_materias);
                printf("Datos guardados. Saliendo...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 3);

    return 0;
}

void ingresar_estudiantes(Estudiante *estudiantes, int *cantidad, int max_materias) {
    int n, i, j;
    printf("¿Cuántos estudiantes desea ingresar? ");
    scanf("%d", &n);
    getchar();
    for (i = 0; i < n; i++) {
        if (*cantidad >= MAX_ESTUDIANTES) {
            printf("Se alcanzó el máximo de estudiantes.\n");
            break;
        }
        printf("\nEstudiante #%d\n", *cantidad + 1);
        printf("Nombre: ");
        fgets(estudiantes[*cantidad].nombre, MAX_NOMBRE, stdin);
        estudiantes[*cantidad].nombre[strcspn(estudiantes[*cantidad].nombre, "\n")] = '\0';
        estudiantes[*cantidad].cantidad_materias = max_materias;
        for (j = 0; j < max_materias; j++) {
            printf("Nota de la materia #%d: ", j + 1);
            scanf("%f", &estudiantes[*cantidad].notas[j]);
        }
        getchar(); // Limpiar buffer
        (*cantidad)++;
    }
}

void mostrar_estudiantes(Estudiante *estudiantes, int cantidad, int max_materias) {
    int i, j;
    if (cantidad == 0) {
        printf("No hay estudiantes para mostrar.\n");
        return;
    }
    printf("\nListado de estudiantes y notas:\n");
    for (i = 0; i < cantidad; i++) {
        printf("\nEstudiante #%d: %s\n", i + 1, estudiantes[i].nombre);
        float suma = 0;
        for (j = 0; j < estudiantes[i].cantidad_materias; j++) {
            printf("  Materia #%d: %.2f\n", j + 1, estudiantes[i].notas[j]);
            suma += estudiantes[i].notas[j];
        }
        printf("  Promedio: %.2f\n", suma / estudiantes[i].cantidad_materias);
    }
}

void guardar_en_archivo(Estudiante *estudiantes, int cantidad, int max_materias) {
    FILE *f = fopen(ARCHIVO_DATOS, "wb");
    if (!f) {
        printf("Error al abrir el archivo para guardar.\n");
        return;
    }
    fwrite(&cantidad, sizeof(int), 1, f);
    fwrite(&max_materias, sizeof(int), 1, f);
    fwrite(estudiantes, sizeof(Estudiante), cantidad, f);
    fclose(f);
}

int cargar_desde_archivo(Estudiante *estudiantes, int max_materias) {
    FILE *f = fopen(ARCHIVO_DATOS, "rb");
    if (!f) return 0;
    int cantidad = 0, materias = 0;
    fread(&cantidad, sizeof(int), 1, f);
    fread(&materias, sizeof(int), 1, f);
    fread(estudiantes, sizeof(Estudiante), cantidad, f);
    fclose(f);
    // Actualizar la cantidad de materias en cada estudiante
    for (int i = 0; i < cantidad; i++) {
        estudiantes[i].cantidad_materias = materias;
    }
    return cantidad;
} 