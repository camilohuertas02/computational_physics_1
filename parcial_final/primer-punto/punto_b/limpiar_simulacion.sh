#!/bin/bash

# Script para eliminar archivos generados por la simulación

# Lista de archivos generados por la simulación
archivos_generados=("box1D_datos.dat" "box1D_grafico.png" "box1D_animacion.gif" "graficar.gp" "animate2D.gnu")

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

