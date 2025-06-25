#!/bin/bash

MAPS_DIR="maps/maps_err"
EXEC="./so_long"

if [ ! -f "$EXEC" ]; then
	echo "❌ Ejecutable $EXEC no encontrado."
	exit 1
fi

for map in "$MAPS_DIR"/*; do
	echo "=============================="
	echo "🗺️ Probando mapa: $map"
	$EXEC "$map"
	echo ""
done