#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_ESTUDIANTES 100
#define MAX_MATERIAS 20
#define MAX_INSCRIPCIONES (MAX_ESTUDIANTES * MAX_MATERIAS)
#define MAX_NOMBRE 50
#define ARCHIVO_ESTUDIANTES "estudiantes.txt"
#define ARCHIVO_MATERIAS "materias.txt"
#define ARCHIVO_INSCRIPCIONES "inscripciones.txt"
#define CLAVE_XOR "clave123"

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
} Materia;

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
} Estudiante;

typedef struct {
    int id_estudiante;
    int id_materia;
    float nota;
} Inscripcion;


void menu(Estudiante *estudiantes, int *cant_estudiantes, Materia *materias, int *cant_materias, Inscripcion *inscripciones, int *cant_inscripciones);
void alta_estudiante(Estudiante *estudiantes, int *cant_estudiantes);
void alta_materia(Materia *materias, int *cant_materias);
void inscribir_estudiante(Inscripcion *inscripciones, int *cant_inscripciones, Estudiante *estudiantes, int cant_estudiantes, Materia *materias, int cant_materias);
void cargar_nota(Inscripcion *inscripciones, int cant_inscripciones);
void mostrar_estudiantes(Estudiante *estudiantes, int cant_estudiantes);
void mostrar_materias(Materia *materias, int cant_materias);
void mostrar_inscripciones(Inscripcion *inscripciones, int cant_inscripciones, Estudiante *estudiantes, int cant_estudiantes, Materia *materias, int cant_materias);
void reporte_promedios(Inscripcion *inscripciones, int cant_inscripciones, Estudiante *estudiantes, int cant_estudiantes, Materia *materias, int cant_materias);
void guardar_datos(Estudiante *estudiantes, int cant_estudiantes, Materia *materias, int cant_materias, Inscripcion *inscripciones, int cant_inscripciones);
void cargar_datos(Estudiante *estudiantes, int *cant_estudiantes, Materia *materias, int *cant_materias, Inscripcion *inscripciones, int *cant_inscripciones);
void xor_cifrar(char *data, size_t len, const char *clave);

int main() {
    Estudiante estudiantes[MAX_ESTUDIANTES];
    Materia materias[MAX_MATERIAS];
    Inscripcion inscripciones[MAX_INSCRIPCIONES];
    int cant_estudiantes = 0, cant_materias = 0, cant_inscripciones = 0;

    cargar_datos(estudiantes, &cant_estudiantes, materias, &cant_materias, inscripciones, &cant_inscripciones);
    menu(estudiantes, &cant_estudiantes, materias, &cant_materias, inscripciones, &cant_inscripciones);
    guardar_datos(estudiantes, cant_estudiantes, materias, cant_materias, inscripciones, cant_inscripciones);
    printf("\nDatos guardados. Saliendo...\n");
    return 0;
}

void menu(Estudiante *estudiantes, int *cant_estudiantes, Materia *materias, int *cant_materias, Inscripcion *inscripciones, int *cant_inscripciones) {
    int opcion;
    do {
        printf("\n--- Sistema de Gestión Académica ---\n");
        printf("1. Alta de estudiante\n");
        printf("2. Alta de materia\n");
        printf("3. Inscribir estudiante a materia\n");
        printf("4. Cargar nota\n");
        printf("5. Mostrar estudiantes\n");
        printf("6. Mostrar materias\n");
        printf("7. Mostrar inscripciones\n");
        printf("8. Reporte de promedios\n");
        printf("9. Guardar y salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();
        switch (opcion) {
            case 1:
                alta_estudiante(estudiantes, cant_estudiantes);
                break;
            case 2:
                alta_materia(materias, cant_materias);
                break;
            case 3:
                inscribir_estudiante(inscripciones, cant_inscripciones, estudiantes, *cant_estudiantes, materias, *cant_materias);
                break;
            case 4:
                cargar_nota(inscripciones, *cant_inscripciones);
                break;
            case 5:
                mostrar_estudiantes(estudiantes, *cant_estudiantes);
                break;
            case 6:
                mostrar_materias(materias, *cant_materias);
                break;
            case 7:
                mostrar_inscripciones(inscripciones, *cant_inscripciones, estudiantes, *cant_estudiantes, materias, *cant_materias);
                break;
            case 8:
                reporte_promedios(inscripciones, *cant_inscripciones, estudiantes, *cant_estudiantes, materias, *cant_materias);
                break;
            case 9:
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 9);
}

void alta_estudiante(Estudiante *estudiantes, int *cant_estudiantes) {
    if (*cant_estudiantes >= MAX_ESTUDIANTES) {
        printf("No se pueden agregar más estudiantes.\n");
        return;
    }
    Estudiante nuevo;
    nuevo.id = *cant_estudiantes + 1;
    printf("Nombre del estudiante: ");
    fgets(nuevo.nombre, MAX_NOMBRE, stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0';
    estudiantes[*cant_estudiantes] = nuevo;
    (*cant_estudiantes)++;
    printf("Estudiante agregado con ID %d.\n", nuevo.id);
}

void alta_materia(Materia *materias, int *cant_materias) {
    if (*cant_materias >= MAX_MATERIAS) {
        printf("No se pueden agregar más materias.\n");
        return;
    }
    Materia nueva;
    nueva.id = *cant_materias + 1;
    printf("Nombre de la materia: ");
    fgets(nueva.nombre, MAX_NOMBRE, stdin);
    nueva.nombre[strcspn(nueva.nombre, "\n")] = '\0';
    materias[*cant_materias] = nueva;
    (*cant_materias)++;
    printf("Materia agregada con ID %d.\n", nueva.id);
}

void inscribir_estudiante(Inscripcion *inscripciones, int *cant_inscripciones, Estudiante *estudiantes, int cant_estudiantes, Materia *materias, int cant_materias) {
    if (*cant_inscripciones >= MAX_INSCRIPCIONES) {
        printf("No se pueden agregar más inscripciones.\n");
        return;
    }
    int id_est, id_mat;
    printf("ID del estudiante: ");
    scanf("%d", &id_est);
    printf("ID de la materia: ");
    scanf("%d", &id_mat);
    getchar();
    if (id_est < 1 || id_est > cant_estudiantes || id_mat < 1 || id_mat > cant_materias) {
        printf("ID inválido.\n");
        return;
    }
    for (int i = 0; i < *cant_inscripciones; i++) {
        if (inscripciones[i].id_estudiante == id_est && inscripciones[i].id_materia == id_mat) {
            printf("El estudiante ya está inscripto en esa materia.\n");
            return;
        }
    }
    Inscripcion nueva = {id_est, id_mat, -1};
    inscripciones[*cant_inscripciones] = nueva;
    (*cant_inscripciones)++;
    printf("Inscripción realizada.\n");
}

void cargar_nota(Inscripcion *inscripciones, int cant_inscripciones) {
    int id_est, id_mat;
    printf("ID del estudiante: ");
    scanf("%d", &id_est);
    printf("ID de la materia: ");
    scanf("%d", &id_mat);
    getchar();
    for (int i = 0; i < cant_inscripciones; i++) {
        if (inscripciones[i].id_estudiante == id_est && inscripciones[i].id_materia == id_mat) {
            printf("Ingrese la nota: ");
            scanf("%f", &inscripciones[i].nota);
            getchar();
            printf("Nota cargada.\n");
            return;
        }
    }
    printf("Inscripción no encontrada.\n");
}


void mostrar_estudiantes(Estudiante *estudiantes, int cant_estudiantes) {
    printf("\n--- Estudiantes ---\n");
    for (int i = 0; i < cant_estudiantes; i++) {
        printf("ID: %d | Nombre: %s\n", estudiantes[i].id, estudiantes[i].nombre);
    }
}

void mostrar_materias(Materia *materias, int cant_materias) {
    printf("\n--- Materias ---\n");
    for (int i = 0; i < cant_materias; i++) {
        printf("ID: %d | Nombre: %s\n", materias[i].id, materias[i].nombre);
    }
}

void mostrar_inscripciones(Inscripcion *inscripciones, int cant_inscripciones, Estudiante *estudiantes, int cant_estudiantes, Materia *materias, int cant_materias) {
    printf("\n--- Inscripciones ---\n");
    for (int i = 0; i < cant_inscripciones; i++) {
        int idx_est = inscripciones[i].id_estudiante - 1;
        int idx_mat = inscripciones[i].id_materia - 1;
        printf("Estudiante: %s | Materia: %s | Nota: ", estudiantes[idx_est].nombre, materias[idx_mat].nombre);
        if (inscripciones[i].nota >= 0)
            printf("%.2f\n", inscripciones[i].nota);
        else
            printf("(sin nota)\n");
    }
}

void reporte_promedios(Inscripcion *inscripciones, int cant_inscripciones, Estudiante *estudiantes, int cant_estudiantes, Materia *materias, int cant_materias) {
    printf("\n--- Promedios por estudiante ---\n");
    for (int i = 0; i < cant_estudiantes; i++) {
        float suma = 0;
        int cuenta = 0;
        for (int j = 0; j < cant_inscripciones; j++) {
            if (inscripciones[j].id_estudiante == estudiantes[i].id && inscripciones[j].nota >= 0) {
                suma += inscripciones[j].nota;
                cuenta++;
            }
        }
        if (cuenta > 0)
            printf("%s: %.2f\n", estudiantes[i].nombre, suma / cuenta);
        else
            printf("%s: (sin notas)\n", estudiantes[i].nombre);
    }
    printf("\n--- Promedios por materia ---\n");
    for (int i = 0; i < cant_materias; i++) {
        float suma = 0;
        int cuenta = 0;
        for (int j = 0; j < cant_inscripciones; j++) {
            if (inscripciones[j].id_materia == materias[i].id && inscripciones[j].nota >= 0) {
                suma += inscripciones[j].nota;
                cuenta++;
            }
        }
        if (cuenta > 0)
            printf("%s: %.2f\n", materias[i].nombre, suma / cuenta);
        else
            printf("%s: (sin notas)\n", materias[i].nombre);
    }
}

void guardar_datos(Estudiante *estudiantes, int cant_estudiantes, Materia *materias, int cant_materias, Inscripcion *inscripciones, int cant_inscripciones) {
    FILE *f;
    char buffer[8192];
    int len = sprintf(buffer, "%d\n", cant_estudiantes);
    for (int i = 0; i < cant_estudiantes; i++) {
        len += sprintf(buffer + len, "%d,%s\n", estudiantes[i].id, estudiantes[i].nombre);
    }
    xor_cifrar(buffer, len, CLAVE_XOR);
    f = fopen(ARCHIVO_ESTUDIANTES, "wb");
    if (f) {
        fwrite(buffer, 1, len, f);
        fclose(f);
    }
    len = sprintf(buffer, "%d\n", cant_materias);
    for (int i = 0; i < cant_materias; i++) {
        len += sprintf(buffer + len, "%d,%s\n", materias[i].id, materias[i].nombre);
    }
    xor_cifrar(buffer, len, CLAVE_XOR);
    f = fopen(ARCHIVO_MATERIAS, "wb");
    if (f) {
        fwrite(buffer, 1, len, f);
        fclose(f);
    }
    len = sprintf(buffer, "%d\n", cant_inscripciones);
    for (int i = 0; i < cant_inscripciones; i++) {
        len += sprintf(buffer + len, "%d,%d,%.2f\n", inscripciones[i].id_estudiante, inscripciones[i].id_materia, inscripciones[i].nota);
    }
    xor_cifrar(buffer, len, CLAVE_XOR);
    f = fopen(ARCHIVO_INSCRIPCIONES, "wb");
    if (f) {
        fwrite(buffer, 1, len, f);
        fclose(f);
    }
}

void cargar_datos(Estudiante *estudiantes, int *cant_estudiantes, Materia *materias, int *cant_materias, Inscripcion *inscripciones, int *cant_inscripciones) {
    FILE *f;
    char buffer[8192];
    size_t len;
    f = fopen(ARCHIVO_ESTUDIANTES, "rb");
    if (f) {
        len = fread(buffer, 1, sizeof(buffer) - 1, f);
        fclose(f);
        xor_cifrar(buffer, len, CLAVE_XOR);
        buffer[len] = '\0';
        char *ptr = buffer;
        sscanf(ptr, "%d\n", cant_estudiantes);
        ptr = strchr(ptr, '\n');
        if (ptr) ptr++;
        for (int i = 0; i < *cant_estudiantes; i++) {
            sscanf(ptr, "%d,%49[^\n]\n", &estudiantes[i].id, estudiantes[i].nombre);
            ptr = strchr(ptr, '\n');
            if (ptr) ptr++;
        }
    }
    f = fopen(ARCHIVO_MATERIAS, "rb");
    if (f) {
        len = fread(buffer, 1, sizeof(buffer) - 1, f);
        fclose(f);
        xor_cifrar(buffer, len, CLAVE_XOR);
        buffer[len] = '\0';
        char *ptr = buffer;
        sscanf(ptr, "%d\n", cant_materias);
        ptr = strchr(ptr, '\n');
        if (ptr) ptr++;
        for (int i = 0; i < *cant_materias; i++) {
            sscanf(ptr, "%d,%49[^\n]\n", &materias[i].id, materias[i].nombre);
            ptr = strchr(ptr, '\n');
            if (ptr) ptr++;
        }
    }
    f = fopen(ARCHIVO_INSCRIPCIONES, "rb");
    if (f) {
        len = fread(buffer, 1, sizeof(buffer) - 1, f);
        fclose(f);
        xor_cifrar(buffer, len, CLAVE_XOR);
        buffer[len] = '\0';
        char *ptr = buffer;
        sscanf(ptr, "%d\n", cant_inscripciones);
        ptr = strchr(ptr, '\n');
        if (ptr) ptr++;
        for (int i = 0; i < *cant_inscripciones; i++) {
            sscanf(ptr, "%d,%d,%f\n", &inscripciones[i].id_estudiante, &inscripciones[i].id_materia, &inscripciones[i].nota);
            ptr = strchr(ptr, '\n');
            if (ptr) ptr++;
        }
    }
}

void xor_cifrar(char *data, size_t len, const char *clave) {
    size_t clave_len = strlen(clave);
    for (size_t i = 0; i < len; i++) {
        data[i] ^= clave[i % clave_len];
    }
}
