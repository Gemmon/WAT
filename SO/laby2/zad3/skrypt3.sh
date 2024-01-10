
echo "min = " `cat liczby.txt| sort -n| head -1`

echo "max = " `cat liczby.txt| sort -n| tail -1`

for i in `cat liczby.txt`
do
    suma=`expr $suma + $i`
done
echo "suma = $suma" 

