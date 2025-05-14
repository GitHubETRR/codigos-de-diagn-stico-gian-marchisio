#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM_TXT 50
#define CAPACIDAD 100
#define PRECIO_ASIENTO 1000

typedef struct {
    int dia;
    int mes;
    int anio;
} fecha_venta_t;

typedef struct {
    char nombre[TAM_TXT];
    char apellido[TAM_TXT];
    fecha_venta_t fecha_venta;
    int numero_asiento; 
    bool estado;     
} reservas_t;

typedef struct nodo {
    reservas_t reserva;
    struct nodo* siguiente;
} nodo_t;

void registrar_venta(nodo_t** inicio);
void mostrar_asientos_disponibles(nodo_t* inicio);
void consultar_asiento(nodo_t* inicio);
void cerrar_ventas(nodo_t* inicio);
void liberar_lista(nodo_t* inicio);
bool asiento_ocupado(nodo_t* inicio, int numero);

int main() {
    nodo_t* lista = NULL;
    int opcion;
    
    do {
        printf("\n--- GESTIÓN DE RESERVAS DE ASIENTOS ---\n");
        printf("1. Registrar la venta de un asiento\n");
        printf("2. Mostrar los asientos disponibles\n");
        printf("3. Consultar asientos\n");
        printf("4. Cerrar ventas\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrar_venta(&lista);
                break;
            case 2:
                mostrar_asientos_disponibles(lista);
                break;
            case 3:
                consultar_asiento(lista);
                break;
            case 4:
                cerrar_ventas(lista);
                break;
            case 5:
                liberar_lista(lista);
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 5);

    return 0;
}

bool asiento_ocupado(nodo_t* inicio, int numero){
    while (inicio != NULL){
        if (inicio->reserva.estado && inicio->reserva.numero_asiento == numero) {
            return true;
        }
    inicio = inicio->siguiente;
    }
    return false;
}


void registrar_venta(nodo_t** inicio) {
    int asiento;
    
    do {
        printf("Ingrese un numero de asiento (0-99): ");
        scanf("%d", &asiento);
        
        if (asiento >= 100 || asiento < 0) {
            printf("Asiento invalido");
        }else if (asiento_ocupado(*inicio, asiento)) {
            printf("Asiento %d ocupado.", asiento);
        }else{
            break;
        }
    } while (true);

    nodo_t* nuevo = malloc(sizeof(nodo_t));
    if (!nuevo) {
        printf("Juan se gasto la memoria");
        return;
    }
    
    printf("Nombre");
    scanf("%s", nuevo->reserva.nombre);
    printf("Apellido");
    scanf("%s", nuevo->reserva.apellido);
    printf("Fecha de venta (dd mm aaaa): ");
    scanf("%d %d %d", &nuevo->reserva.fecha_venta.dia, &nuevo->reserva.fecha_venta.mes, &nuevo->reserva.fecha_venta.anio);
    
    nuevo->reserva.numero_asiento = asiento;
    nuevo->reserva.estado = true;
    nuevo->siguiente = *inicio;
    *inicio = nuevo;
}


void mostrar_asientos_disponibles(nodo_t* inicio) {
    int disponibles = 0, ocupados = 0, total_recaudado = 0;
    int asientos_por_grupo = 2;
    int asientos_por_fila = 4;
    bool ocupados_vector[CAPACIDAD] = {false};

    nodo_t* actual = inicio;
    while (actual != NULL) {
        if (actual->reserva.estado) {
            ocupados_vector[actual->reserva.numero_asiento] = true;
        }
        actual = actual->siguiente;
    }

    printf("Asientos: \n");
    for (int i = 0; i < CAPACIDAD; i++) {
        if (i % asientos_por_fila == 0) {
            printf("  ");
        }

        if (!ocupados_vector[i]) {
            printf("\033[32m%2d \033[0m", i);  
            disponibles++;
        } else {
            printf("\033[31m%2d \033[0m", i); 
            ocupados++;
            total_recaudado += PRECIO_ASIENTO;
        }

        if ((i + 1) % asientos_por_grupo == 0 && i != 99) {
            printf("    ");
        }

        if ((i + 1) % asientos_por_fila == 0) {
            printf("\n");
        }
    }

    if (CAPACIDAD % asientos_por_fila != 0) {
        printf("\n");
    }

    printf("Total de asientos disponibles: %d\n", disponibles);
    printf("Total de asientos ocupados: %d\n", ocupados);
    printf("Total recaudado: $%d\n", total_recaudado);
}

void consultar_asiento(nodo_t* inicio) {
    char apellido[TAM_TXT];
    int encontrados = 0;

    printf("Consultar por apellido\n");
    printf("Ingrese el apellido: ");
    scanf("%s", apellido);

    printf("Asientos comprados por personas con apellido '%s':\n", apellido);
    while (inicio != NULL) {
        if (inicio->reserva.estado && strcmp(inicio->reserva.apellido, apellido) == 0) {
            printf("Asiento %d: %s %s, Fecha: %02d/%02d/%04d\n", 
                inicio->reserva.numero_asiento, 
                inicio->reserva.nombre, 
                inicio->reserva.apellido,
                inicio->reserva.fecha_venta.dia, 
                inicio->reserva.fecha_venta.mes, 
                inicio->reserva.fecha_venta.anio);
            encontrados++;
        }
        inicio = inicio->siguiente;
    }
    if (encontrados == 0) {
        printf("No se encontraron asientos vendidos a personas con el apellido '%s'.\n", apellido);
    }
}

void cerrar_ventas(nodo_t* inicio) {
    int vendidos = 0, total_recaudado = 0;

    while (inicio != NULL) {
        if (inicio->reserva.estado){
            vendidos++;
            total_recaudado += PRECIO_ASIENTO;
            inicio->reserva.estado = false;
        }
    }

    printf("Total recaudado: $%d\n", total_recaudado);
    printf("%d Ventas hechas", vendidos);
}

void liberar_lista(nodo_t* inicio){
    nodo_t* memo;
    while (inicio != NULL){
        memo = inicio;
        inicio = inicio->siguiente;
        free(memo);
    }
}
