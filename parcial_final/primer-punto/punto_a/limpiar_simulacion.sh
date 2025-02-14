#!/bin/bash

# -----------------------------------------------------
# Nombre: Camilo Huertas
# Fecha: 14-02-2025
# Descripción: Script para eliminar automáticamente los archivos generados
#              por la simulación de la partícula en un triángulo equilátero.
# -----------------------------------------------------

# Lista de archivos generados por la simulación
archivos_generados=("triangulo_datos.dat" "triangulo_grafico.png" "triangulo_animacion.gif" "graficar.gp" "animate_triangulo.gnu")

# Eliminar cada archivo en la lista
for archivo in "${archivos_generados[@]}"
do
    if [ -f "$archivo" ]; then
        rm "$archivo"
        echo "Archivo $archivo eliminado."
    else
        echo "Archivo $archivo no encontrado."
    fi
done

echo "Limpieza completa."

