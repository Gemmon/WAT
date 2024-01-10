#!/bin/bash

if [ $# -eq "0" ]
then
	for i in `ls`
	do
		if test -d "${i}"
		then
			echo "${i}"
		fi
	done
else
	for i
	do
		if test -d $i
		then
			cd $i
			echo "Podkatalogi katalogu $i: "	
			for j in `ls`
			do
				if test -d "$j"
				then
					echo "$j"
				fi
			done
			cd ..
			echo ""
		fi

	done
fi