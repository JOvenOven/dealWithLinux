#!/bin/bash
echo "Seleccione una opción"
echo "1. adivinar el PID del Script"
echo "2. adivinar un número introducido por el usuario"
echo "3. adivinar un número aleatorio del sistema"
read -p " " op

if [ $op -eq 1 ]; then
	echo "PID: $$"
	read -p "Ingresa el PID: " intento
	while [ $intento -ne $$ ]; do
		if [ $intento -gt $$ ]; then
			echo "El número introducido es mayor que el PID"
		fi
		if [ $intento -lt $$ ]; then
			echo "El número introducido es menor que el PID"
		fi
		read -p "Ingresa el PID: " intento
		cont=$(($cont+1))
	done
	echo "Se necesitaron " $cont "intentos para terminar"
fi

if [ $op -eq 2 ]; then
	read -p "Ingrese el numero correcto: " num
	read -p "Ingresa el numero intento: " intento
	while [ $intento -ne $num ]; do
		if [ $intento -gt $num ]; then
			echo "El número introducido es mayor"
		fi
		if [ $intento -lt $num ]; then
			echo "El número introducido es menor"
		fi
		read -p "Ingresa el numero intento: " intento
		cont=$(($cont+1))
	done
	echo "Se necesitaron " $cont "intentos para terminar"
fi

if [ $op -eq 3 ]; then
	echo "PID: $$"
	numalea=$((RANDOM%1000))
	echo "numero aleatorio: " $numalea
	read -p "Ingresa el intento: " intento
	while [ $intento -ne $numalea ]; do
		if [ $intento -gt $numalea ]; then
			echo "El número introducido es mayor"
		fi
		if [ $intento -lt $numalea ]; then
			echo "El número introducido es menor"
		fi
		read -p "Ingresa el intento: " intento
		cont=$(($cont+1))
	done
	echo "Se necesitaron " $cont "intentos para terminar"
fi


