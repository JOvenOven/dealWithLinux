#!/bin/bash
let numero1=$1%2
let numero2=$2%2
let numero3=$3%2
if [ $numero1 -eq 0 ]; then
	echo "El primer valor es par"
else
	echo "El primer valor es impar"
fi

if [ $numero2 -eq 0 ]; then
	echo "El segundo valor es par"
else
	echo "El segundo valor es impar"
fi

if [ $numero3 -eq 0 ]; then
	echo "El tercer valor es par"
else
	echo "El tercer valor es impar"
fi
