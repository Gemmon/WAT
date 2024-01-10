#!/bin/bash

echo " Podaj jakas liczbe "
read X

if [ "$#" -eq "0" ]
then
    echo "Skrypt wywolano bez parametrow"
elif [ "$#" -eq "1" ]
then
    echo "Skrypt wywolano z jednym parametrem"
else
    echo "Skrypt wywolano z $# parametrami"
echo "$*"
fi

if "x" -ge "$#"