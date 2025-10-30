import os
import csv
from datetime import datetime
from zoneinfo import ZoneInfo  

archivo = "gastos.csv"

if not os.path.exists(archivo):
    with open(archivo, mode="w", newline="") as f:
        escritor = csv.writer(f)
        escritor.writerow(["Fecha", "Descripción", "Monto"])

descripcion = input("Ingrese la descripción del gasto: ")
monto = float(input("Ingrese el monto ($): "))

zona_arg = ZoneInfo("America/Argentina/Buenos_Aires")
fecha = datetime.now(zona_arg).strftime("%d/%m/%Y %H:%M")

with open(archivo, mode="a", newline="") as f:
    escritor = csv.writer(f)
    escritor.writerow([fecha, descripcion, monto])

print(f"\n Gasto registrado correctamente en '{archivo}'.")

total = 0
with open(archivo, mode="r") as f:
    lector = csv.DictReader(f)
    for fila in lector:
        total += float(fila["Monto"])

print(f" Total gastado hasta ahora: ${total:.2f}")
