#!/bin/bash
read -p "ingrese la ruta: " ruta

if [ -d  $ruta ]; then
echo "La ruta existe y es un directorio"
fi

if [ -e $ruta ]; then
echo "La ruta existe sea el elemento que sea"
fi

if [ -f $ruta ]; then
echo "La ruta existe y es un fichero normal"
fi

if [ -r $ruta ]; then
echo "La ruta existe y se puede leer"
fi

if [ -w $ruta ]; then
echo "La ruta existe y se puede escribir"
fi

if [ -x $ruta ]; then
echo "La ruta existe y es ejecutable"
fi

if [ -s $ruta ]; then
echo "La ruta existe y su tamaño es mayor que cero"
fi

